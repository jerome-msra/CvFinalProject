#include "mgraph.h"

#include "exttype/itern.h"
#include "debug/logs.h"
#include "exttype/itern.h"
#include "data/dataset.h"

namespace datastruct{

	void mgraph::edge_index(){
		intf n_out(nV());
		intf n_in(nV());
		n_out<<0;
		n_in<<0;

		for(int i=0;i<E.size();++i){
			int2 st = E[i];
			++n_out[st[0]];
			++n_in[st[1]];
		};

		out.resize(nV());
		in.resize(nV());
		for(int i=0;i<nV();++i){
			out[i].reserve(n_out[i]);
			in[i].reserve(n_in[i]);
		};

		for(int i=0;i<E.size();++i){
			int2 st = E[i];
			out[st[0]].push_back(i);
			in[st[1]].push_back(i);
		};		
	};

	/*
	void mgraph::create_grid(const int2& sz){
		int n1 = sz[0];
		int n2 = sz[1];
		int nV = n1*n2;
		V.resize(nV);
		for(int i=0;i<nV;++i)V[i]=i;
		int nE = (n1-1)*n2+(n2-1)*n1;
		E.reserve(nE);

		for(iter2 ii(int2(n1-1,n2));ii.allowed();++ii){
			E.push_back(int2(ii[0]+ii[1]*n1,(ii[0]+1)+ii[1]*n1));
		};
		for(iter2 ii(int2(n1,n2-1));ii.allowed();++ii){
			E.push_back(int2(ii[0]+ii[1]*n1,ii[0]+(ii[1]+1)*n1));
		};
		edge_index();
	};
	*/

	template<int rank,bool lastindexfastest> void mgraph::create_grid(const intn<rank>& sz){
		dynamic::LinIndex<rank,lastindexfastest> geometry(sz); 
		int nV = geometry.linsize();
		V.resize(nV);
		int nE=0;
		for(int k=0;k<rank;++k){
			intn<rank> sz1 = sz;
			--sz1[k];
			nE+=sz1.prod();
		};
		E.reserve(nE);
		for(int k=0;k<rank;++k){
			if(sz[k]<1)throw debug_exception("invalid size");
			intn<rank> cc = sz;
			--cc[k];
			for(itern<rank> ii(cc);ii.allowed();++ii){
				intn<rank> jj=ii;
				++jj[k];
				E.push_back(int2(geometry.linindex(ii),geometry.linindex(jj)));
			};
		};
		edge_index();
	};

	int mgraph::edge(int s,int t){
		intf & o = out[s];
		for(int j=0;j<o.size();++j){
			if(E[o[j]][1]==t){
				return o[j];
			};
		};
		throw debug_exception("edge does not exist in the graph.");
	};

	int mgraph::out_edge(int s,int t){
		intf & o = out[s];
		for(int j=0;j<o.size();++j){
			if(E[o[j]][1]==t){
				return o[j];
			};
		};
		throw debug_exception("edge does not exist in the graph.");
	};

	int mgraph::in_edge(int s,int t){
		intf & ee = in[s];
		for(int j=0;j<ee.size();++j){
			if(E[ee[j]][0]==t){
				return ee[j];
			};
		};
		throw debug_exception("edge does not exist in the graph.");
	};

/*
	template<> const fixed_vect<int> & mgraph::dir_in<true>(const int s)const{
		return in[s];
	};
	template<> const fixed_vect<int> & mgraph::dir_in<false>(const int s)const{
		return out[s];
	};
	template<> const fixed_vect<int> & mgraph::dir_out<true>(const int s)const{
		return out[s];
	};
	template<> const fixed_vect<int> & mgraph::dir_out<false>(const int s)const{
		return in[s];
	};
*/
	namespace{
		void make(){
			mgraph G;
			G.create_grid<1,true>(0);
			G.create_grid<2,true>(int2(0,0));
			G.create_grid<3,true>(int3(0,0,0));
			G.create_grid<1,false>(0);
			G.create_grid<2,false>(int2(0,0));
			G.create_grid<3,false>(int3(0,0,0));
		};
	};
};