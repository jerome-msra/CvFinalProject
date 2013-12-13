#ifndef mgraph_h
#define mgraph_h

#include "dynamic/array_allocator.h"
#include "dynamic/fixed_array1.h"
#include "dynamic/fixed_array2.h"
#include "exttype/fixed_vect.h"


namespace datastruct{
	using namespace exttype;

	class mgraph{
	public:
		typedef fixed_vect<int> intf;
		typedef dynamic::fixed_array1<int2, dynamic::array_allocator<int2> > tE;
		typedef dynamic::fixed_array1<intf, dynamic::array_allocator<intf > > tmy_vararray;
	public:
		intf V;
		tE E;
		tmy_vararray in;
		tmy_vararray out;
	public:
		//! number of nodes
		int nV()const{return V.size();};
		//! number of edges
		int nE()const{return E.size();};
		//! number of edges adjucent to s
		int nns(int s)const{return in[s].size()+out[s].size();};
	public:
		//void create_grid(const int2& sz);
		template<int rank, bool lastindexfastest> void create_grid(const intn<rank>& sz);
	public:
		void edge_index();
	public:
		int edge(int s,int t);
		int in_edge(int s,int t);
		int out_edge(int s,int t);
	public:
		//template<bool dir> const fixed_vect<int> & dir_in(const int s)const;
		//template<bool dir> const fixed_vect<int> & dir_out(const int s)const;
	};
};

#endif