#ifndef trws4_h
#define trws4_h

#include "optim/graph/mgraph.h"

#include "dynamic/array_allocator.h"
#include "dynamic/fixed_array1.h"
#include "dynamic/fixed_array2.h"
#include "exttype/fixed_vect.h"
#include "func.h"

namespace maxplus{
	typedef fixed_vect<int> intf;
	typedef fixedlist<func1,2> func1_pair;
	typedef dynamic::fixed_array1<func1_pair, dynamic::array_allocator<func1_pair> > tmessages;

	//! class representing pairwise energy function over graph G
	class gibbs_energy{
	public:
		//! graph
		datastruct::mgraph G;
		//! label ranges
		intf K;
		//! univariate functions
		dynamic::fixed_array1<func1> f1;
		//! pairwise functions
		dynamic::fixed_array1<func2 *> f2;
	public:
		gibbs_energy(){
		};
		void init(const datastruct::mgraph & G, const intf & K){
			this->G = G;
			this->K = K;
			f2.resize(G.nE());
			f1.resize(G.nV());
			for(int s=0;s<G.nV();++s){
				f1[s].resize(K[s]);
			};
		};
		gibbs_energy(const datastruct::mgraph & G, const intf & K){
			init(G,K);
		};
	public:
		double cost(intf & x)const{
			double r=0;
			for(int s=0;s<G.nV();++s){
				r+=f1[s][x[s]];
			};
			for(int st=0;st<G.nE();++st){
				const int2 & ee = G.E[st];
				r+=f2[st]->Q(x[ee[0]],x[ee[1]]);
			};
			return r;
		};
	public:
		template<bool dir> void blabla()const{};
		template<bool dir> void maxfunc(func1& result, int st, const func1 & q)const{
			if(dir){ 
				f2[st]->max_product_transp(result,q);
			}else{
				f2[st]->max_product(result,q);
			};
		};
		void set_func2(int st, func2 * g_st){
			f2[st] = g_st;
		};
		func2 * get_func2(int st){
			return f2[st];
		};
		const func2 * get_func2(int st)const{
			return f2[st];
		};
	};

	//_________________________alg_trws_________________________________
	//! class representing TRW-S algorithm for energy function E
	class alg_trws{
	public:
		//! schedule
		class schedule_operation{
		public:
			//! update_type: 0 -- vertex; 1 -- edge; -1 -- init_bounds
			int update_type;
			//! index -- node/edge index to update
			int index;
			int dir;
			bool bounds;
		public:
			schedule_operation(int type, int ind, int _dir, bool bnds=false):update_type(type), index(ind), dir(_dir),bounds(bnds){};
		};
/*
		typedef fixed_array1<schedule_operation> tschedule;
		typedef fixed_array1<tschedule*> tmacro_schedule;
		fixed_array1<tschedule> schedules;
		tmacro_schedule my_schedule;
*/
	public:
		//! number of labels in each node
		const intf & K;
		//! pairwise energy
		gibbs_energy & E;
		//! ?
		dynamic::fixed_array1<double> c0;
		//! graph
		const datastruct::mgraph & G;
		//! labeling
		intf x;
		//! max number of labels, currently K[:] = maxK
		int maxK;
		//! messages (variational variables)
		tmessages M;
		//! last pass min-marginals
		dynamic::fixed_array1<func1> PHI;
	public:
		double LLB, LB, LB1, dM, dPhi;
	protected:
		//! some temp intermediate data
		func1 Phi1;
		func1 M1;
	public:

		void basic_schedule();

		void init();

		alg_trws(gibbs_energy & energy):E(energy), G(energy.G), K(energy.K){
			init();
		};
		~alg_trws();

	public:
		void iteration_init();
		template<bool dir> void node_update(int s, bool bounds=true);
		template<bool dir> void edge_update(int st, bool bounds=true);
	
	public:
/*
		void run_schedule(const tschedule & schedule);
		void run_macro_schedule(const tmacro_schedule & mschedule,int niters);
*/
		//void first_iteration();
		//! number of trees sharing s
		int n_s(int s);
		//! fix a label for gradual fixation
		void fix_label(func1 & v,int k);
		//! gradual fixation
		void last_iteration();
		//! do iterations
		void run(int niters);
		//! do controlled iterations
		void run_converge(double eps, int maxit);
	};
};

#endif