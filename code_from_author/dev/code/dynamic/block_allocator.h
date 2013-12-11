#ifndef block_allocator_h
#define block_allocator_h

#include <list>
#include "assert.h"
#include "debug/except.h"
#include "debug/logs.h"

namespace dynamic{

//____________________block_allocator______________________________
	//! Allocator for local-scope runtime-size memory blocks (small-to-medium)
	/*!
		Blocks are allocated in the stack-like fasion. Deallocation is delayed to match the reverse-stack order.
		If the deallocation occures in the reverse to allocation order it is processed immediately, otherwise
		it is delayed.
		When the scope is left it is guaranteed that all delayed deallocations within the scope are processed.
		Overheads: sizeof(int) for each of the allocated blocks.
		
		block_allocator keeps a stack (list) of large buffers, reserving space for allocation.
		New blocks are allocated at the top of the buffer stack.
		If the top buffer has not space to allocate new block, a new buffer is allocated.
	*/
	class block_allocator{
	private:
		/* buffer format: [block1 block2 ...]
			used block: [... | int used_flag=1 ]
			unused block: [...| int size | int used_flag=0 ]
		*/
		class buffer{
		private:
			mutable char * _beg;
			mutable char * _end;
			mutable char * _capend;
		public:
			char * beg()const{return _beg;};
			char * end()const{return _end;};
			int size()const{
				if(!allocated())return 0;
				return int(_end-_beg);
			};
			int capacity()const{
				if(!allocated())return 0;
				return int(_capend-_beg);
			};
			int cap_free()const{return int(_capend-_end);};
			bool used()const{return (size()>0);};
			bool allocated()const{return (beg()!=0);};
		public:
			buffer(int size):_beg(0){
				//this->size = size;
				try{
					_beg = new char[size];
				}catch(std::bad_alloc){
					debug::errstream<<"Memory allocation failed\n"<<"Requested size: ";
					if(size>=block_allocator::MB){
						debug::errstream<<txt::String::Format("%3.2f",size/double(block_allocator::MB))<<" Mb\n";
					}else{
						debug::errstream<<size<<" bytes\n";
					};
					throw;
				};
				_end = _beg;
				_capend = _beg+size;
			};

			buffer(const buffer & x):_beg(0){
				(*this)=x;
			};

			void operator = (const buffer & x){
				if(used())throw debug_exception("buffer is in use");
				if(allocated())delete[] _beg;
				_beg = x._beg;
				_end = x._end;
				_capend = x._capend;
				x._beg = 0;
				x._end = 0;
				x._capend = 0;
			};

			~buffer(){
				if(allocated())delete[] _beg;
				_beg = 0;
				_end = 0;
				_capend = 0;
			};
		public:
			char * allocate(int size){
				assert(cap_free()>=size);
				char * P = end();
				_end+=size;
				return P;
			};

			bool is_top_object(char * P, int size)const{
				return (end()-size == P);
			};
			void deallocate(char * P, int size){
				assert(P>=beg() && P<end());
				_end = P;
			};
		};
	private:
		int buffer_size;
		mutable std::list<buffer> buffers;
	private:
		void add_buffer(int buffer_size_sp){
			buffers.push_front(buffer(buffer_size_sp));
		};
		void drop_buffer(){
			buffers.erase(buffers.begin());
		};
		void ready(int size){
			if(buffers.empty())add_buffer(std::max(buffer_size,size));
			else{
				buffer & b = buffers.front();
				if(b.cap_free()<size){
					if(size>buffer_size){
						//debug::stream<<"Big allocation "<<size/block_allocator::MB<<" Mb.\n";
						debug::stream<<"Big allocation "<<txt::String::Format("%3.2f",size/double(block_allocator::MB))<<"Mb.\n";
					};
					add_buffer(std::max(buffer_size,size));
				};
			};
		};
		bool is_block_used(char * block_end){
			return(*( (int*)block_end - 1 )==1);
		};
		void mark_block_used(char * P, int size){
			*( (int*)(P+size) - 1 ) = 1;
		};
		void mark_block_unused(char * P, int size){
			*( (int*)(P+size) -1 ) = 0;
			*( (int*)(P+size) -2 ) = size; //store block size
		};
		int block_size(char * block_end){
			return *( (int*)block_end - 2 );
		};
	public:
		const static int KB = 1024;
		const static int MB = 1024*KB;
	public:
		block_allocator(int default_buffer_size=10*MB):buffer_size(default_buffer_size){};
	private:
		block_allocator(const block_allocator & x):buffer_size(x.buffer_size){};
		void operator=(const block_allocator & x){};
	public:
		~block_allocator(){
			if(!buffers.empty()){
				try{
					debug::errstream<<"Memory leaks detected\n";
				}catch(...){
				};
			};
		};
	public:
		char * allocate(int size){
			if(size<sizeof(int))throw debug_exception("can not allocate less then sizeof(int) bytes");
			size+=sizeof(int);
			ready(size);
			char * P = buffers.front().allocate(size);
			mark_block_used(P,size);
			return P;
		};
		void deallocate(char * P, int size){
			size+=sizeof(int);
			if(!buffers.empty() && !buffers.front().used())drop_buffer();
			if(buffers.empty()){
				try{
					debug::errstream<<"Invalid deallocation at"<<P<<", "<<size<<" bytes.\n";
				}catch(...){
				};
				return;
			};
			if(buffers.front().is_top_object(P,size)){
				buffers.front().deallocate(P,size);
				if(!buffers.front().used())drop_buffer();
				while(!buffers.empty() && !is_block_used(buffers.front().end())){
					int size = block_size(buffers.front().end());
					char * P = buffers.front().end()-size;
					buffers.front().deallocate(P,size);
					if(!buffers.front().used())drop_buffer();
				};
			}else{
				mark_block_unused(P,size);
			};
		};
		static block_allocator global;
	};
};

#endif