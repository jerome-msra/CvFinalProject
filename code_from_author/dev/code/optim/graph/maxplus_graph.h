#ifndef maxplus_graph_h
#define maxplus_graph_h

#include "data/indexset.h"
#include "exttype/intn.h"
#include "debug/except.h"

namespace maxplus{

	class element_t;
	class element_tt;

	typedef indexptr<element_t> t_index;
	typedef indexptr<element_tt> tt_index;

	class element_t : public element<element_t>{
	public:
		//		int2 ii;
	};

	class element_tt : public element<element_tt>{
	public:
		element_t * s;
		element_t * t;
	public:
		element_tt * reversed;
	};

	//____________________________set_Nb_________________________
	class set_Nb{
	private:
		mutable std::vector<element_t*> v_t;
		mutable std::vector<element_tt*> v_tt;
		int n;
	public:
		set_Nb():n(0){};
		int N()const{
			assert(v_t.size()==n && v_tt.size()==n);
			return n;
		};
		void reserve(int n){
			v_t.reserve(n);
			v_tt.reserve(n);
		};
		void addpair(element_tt & tt);
	public:
		element_t & get_t(int i)const{
			return *v_t[i];
		};

		element_tt & operator[](int i)const{
			return *v_tt[i];
		};

		int  index_of(element_t & t)const{
			for(int i=0;i<N();++i){
				element_t * _t = (*this)[i].t;
				if(_t == &t)return i;
			};
			return -1;
			//throw debug_exception("not a neighbor");
		};

		bool is_neighbor(element_t & t)const{
			return(index_of(t)>=0);
		};

		element_tt & find(element_t & t)const{
			int i = index_of(t);
			if(i>=0)return (*this)[index_of(t)];
			throw debug_exception("not a neighbor");
		};
	public:
		void swap(int i,int j){
			std::swap(v_t[i],v_t[j]);
			std::swap(v_tt[i],v_tt[j]);
		};
	};

	//____________________________set_T______________________________
	class set_T : public set<element_t>{
	private:
		typedef set<element_t> set;
	};

	//____________________________set_Tau________________________
	class set_Tau : public set<element_tt>{
	public:
		element_tt & new_element(element_t & s, element_t & t);
	};

	//____________________________subset_T_______________________
	class subset_T : public subset<element_t>{
	};

	//____________________________subset_Tau_____________________
	class subset_Tau : public subset<element_tt>{
	};

	//___________________________subset_asymTau___________________
	class subset_asymTau : public subset_Tau{
	private:
		typedef subset_Tau parent;
	public:
		void init(subset<element_tt> & Tau){
			clear();
			for(tt_index i = Tau.begin();i<Tau.end();++i){
				element_tt & tt = Tau[i];
				tt_index j = tt.reversed->find_index(Tau);
				if(j.isnull() || i<j){
					add(tt);
				};
			};			
		};
	};

	//____________________________graph_G________________________
	class graph_G{
	public:
		set_T T;
		set_Tau Tau;
		subset_asymTau aTau;
		mapping<element_t, set_Nb> Nbs;
	public:
		void init(int n, int max_nb){
			T.resize(n);
			aTau.reserve(n*max_nb);
			Tau.reserve(2*n*max_nb);
			Nbs.init(T);
			for(t_index	u =	T.begin();u<T.end();++u){
				Nbs[u].reserve(max_nb);
			};
		};
		bool has_edge(element_t & s, element_t & t){
			return Nbs[s].is_neighbor(t);
		};

		void add_edge(element_t & s, element_t & t);

		element_tt & edge(element_t & s, element_t & t){
			return Nbs[s].find(t);
		};
		element_tt & edge(t_index s, t_index t){
			return Nbs[s].find(t.getObj());
		};
	};

};

#endif