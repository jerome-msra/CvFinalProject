#ifndef fixed_vect_h
#define fixed_vect_h

#include "dynamic/fixed_array1.h"
#include "ivector.h"

namespace exttype{
	template <typename type> class fixed_vect : public ivector<fixed_vect<type>, dynamic::fixed_array1<type, dynamic::array_allocator<type> > >{
	private:
		typedef ivector<fixed_vect, dynamic::fixed_array1<type, dynamic::array_allocator<type> > > parent;
	public:
		int count()const{return size();};
		fixed_vect(){};
		explicit fixed_vect(int K){// constructor with initialization
			resize(K);
			for(int i=0;i<size();++i)(*this)[i] = 0;
		};
		//default operator =
		//default copy constructor
	private:
		fixed_vect cpy()const{return fixed_vect(*this);};
	public:
	};

};


#endif