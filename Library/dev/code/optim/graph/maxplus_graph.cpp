#include "maxplus_graph.h"

namespace maxplus{

	//_______________set_Tau_____________________
	element_tt & set_Tau::new_element(element_t & s, element_t & t){
		int m = size();
		resize(m+1);
		(*this)[m].s = &s;
		(*this)[m].t = &t;
		return (*this)[m];
	};

	//_______________set_Nb_____________________
	void set_Nb::addpair(element_tt & tt){
		int c = (int)v_tt.capacity();
		v_tt.push_back(&tt);
		v_t.push_back(tt.t);
		++n;
	};

	//_______________graph_G____________________
	void graph_G::add_edge(element_t & s, element_t & t){
		Nbs[s].addpair(Tau.new_element(s,t));
		Nbs[t].addpair(Tau.new_element(t,s));
	};

};