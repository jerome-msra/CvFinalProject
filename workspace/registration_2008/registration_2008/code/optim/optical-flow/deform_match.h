#ifndef deform_match_h
#define deform_match_h

#include "optim/trws/trws4.h"


namespace maxplus{
	using namespace geom;
	using namespace exttype;

	class deform_match{
	public:
		class tparams{
		public:
			double deform_reg;
			double eps;
			int maxit;
			int maxd;
		public:
			tparams(double deform_reg=0, int maxd=1, double eps=1e-3, int maxit=20){
				this->deform_reg = deform_reg;
				this->maxd = maxd;
				this->maxit = maxit;
				this->eps = eps;
			};
		};
	public:
		dynamic::DataSet<float,4,false> & Q;
		int2 maxK;
		int2 n;
		tparams params;
	public:
		dynamic::LinIndex<3,true> geometry;
		datastruct::mgraph G;
		gibbs_energy energy;
		//alg_trws trws;
	private:
		alg_trws * trws;
	public://outputs:
		double LB;
		typedef dynamic::DataSet<int2,2> labeling2;
		labeling2 x;
	private:
		dynamic::fixed_array1<ppf_matrix<float> > F2;
		func2 * m_dx;
	private:
		int grid_node(const int3 & ii);
		int z_edge(const int2 & ii);
		int x_edge(const int3 & ii,int dir=1);
		int y_edge(const int3 & ii,int dir=1);
	private:
		int last_processed;
		int subdiv;
		int subdiv_1;
		int subdiv_layer;
	public:
		deform_match(dynamic::DataSet<float,4,false> & q, const tparams & _params):Q(q){
			maxK = Q.size().sub<2>();
			n = Q.size().rsub<2>();
			params = _params;
		};
		~deform_match();
		void init();
		dynamic::DataSet<float,2,false> solve(dynamic::DataSet<float,2,false> & M_bw0, int fix_strategy);
	private:
		void my_run_converge(double eps, int maxit, int intrait);
		void my_run(int niters, int intrait);
		void fix_subdivide();
		bool all_fixed()const;
		void bw_pass();
	};
};

#endif