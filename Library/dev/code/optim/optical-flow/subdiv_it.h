#ifndef subdiv_it_h
#define subdiv_it_h

#include "exttype/intn.h"
#include "exttype/itern.h"

class subdiv_iterator{
	private:
		int size;
		int level;
		int k;
		bool _allowed;
	public:
		int pos;
	private:
		int get_pos(int size,int level, int k){
			if(size<=0)return -10000;
			if(level==0){
				return size/2;
			}else{
				int mid  = (1<<(level-1));
				if( k < mid ){
					return get_pos(size/2,level-1,k);
				}else{
					return size/2+get_pos(size-size/2-1,level-1,k - mid )+1;
				};
			};
		};
		void findallowed(){
			pos = get_pos(size,level,k);
			while(pos<0 && k<(1<<level) ){
				++k;
				pos = get_pos(size,level,k);
			};
			_allowed  = (pos>=0) && (pos<size) && k<(1<<level);
		};
	public:
		subdiv_iterator(int Size,int Level):size(Size),level(Level){
			k = 0;
			findallowed();
		};
		void operator ++(){
			++k;
			findallowed();
			//debug::stream<<"/ max:"<<(1<<level)<<"/" ;
		};

		bool allowed(){
			return _allowed;
		};
		//operator const int &(){return pos;};
	};

#endif