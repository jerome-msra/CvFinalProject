#ifndef array_allocator_h
#define array_allocator_h

#include "block_allocator.h"

namespace dynamic{
	//________________________array_allocator________________________
	//! Implementation of std::allocator for allocation on the block_allocator::global
	template<class T> class array_allocator{
	public:
		typedef int size_type;
		typedef int difference_type;
		typedef T *pointer;
		typedef const T *const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef T value_type;
		pointer address(reference x) const{return &x;};
		const_pointer address(const_reference x) const{return &x;};
	public:
		//default constructor
		//default copy constructor
		//default operator =
	public:
		pointer allocate(size_type n, const void *hint=0){
			if(n==0)throw debug_exception("Invalid to allocate 0 bytes.");
			int size = sizeof(T)*n;
			if(size<sizeof(int))size = sizeof(int);
			char * P = block_allocator::global.allocate(size);
			return (T*)P;
		};

		void deallocate(pointer x, size_type n){
			if(n==0)throw debug_exception("Invalid to deallocate 0 bytes.");
			int size = sizeof(T)*n;
			if(size<sizeof(int))size = sizeof(int);
			if(x==0)throw debug_exception("Invalid pointer.");
			block_allocator::global.deallocate((char*)x,size);
		};

		void construct(pointer p, const T & val){
			new ((void *)p) T(val);
		};

		void destroy(pointer p){
			p->~T();
		};

		size_type max_size() const{
			return block_allocator::MB/sizeof(T);
		};
	public:
		template<class U> struct rebind{
			typedef array_allocator<U> other;
		};
	};
};
#endif