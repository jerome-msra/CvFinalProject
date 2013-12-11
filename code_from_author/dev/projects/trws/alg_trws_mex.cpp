#include <mex.h>
#include <string>

#include "optim/trws/trws4.h"
#include "mex/mexargs.h"
#include "debug/logs.h"
#include "files/xfs.h"

namespace maxplus{
	using namespace mexargs;
	using namespace debug;
	using namespace maxplus;

	std::string maxflow_check_args(int nrhs, const mxArray *prhs[]){
		if (nrhs <5 || nrhs>6 )return "5(6) input arguments expected";
		return "";
	};
};

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
	using namespace exttype;
	using namespace maxplus;
	// Check for proper number of arguments. 

	std::string err = maxflow_check_args(nrhs,prhs);
	if(!err.empty()){
		mexErrMsgTxt((std::string("[x LB phi M_bw] = alg_trws_mex(V,E,f1,f2,params,M_bw0=[])::input error:\n")+err+".\n").c_str());
	};
	try{
		MexLogStream log("log/output.txt",false);
		stream.attach(&log);
		MexLogStream err("log/errors.log",false);
		errstream.attach(&err);
		
		mextype<int,1>::DataSet V = dataset<int,1>(prhs[0]);
		mextype<int,2>::DataSet E = dataset<int,2>(prhs[1]);
		mextype<double,2>::DataSet f1 = dataset<double,2>(prhs[2]);
		mextype<double,3>::DataSet f2 = dataset<double,3>(prhs[3]);
		mextype<double,1>::DataSet params = dataset<double,1>(prhs[4]);
		mextype<double,2>::DataSet M_bw0;
		if(nrhs>=6){
			M_bw0 = dataset<double,2>(prhs[5]);
		};

		double eps = params[0];
		int maxit = (int)params[1];
		
		int nV = V.linsize();
		int nE = E.size()[1];
		int maxK = f1.size()[0];

		datastruct::mgraph G;
		G.V << V;
		G.E.resize(nE);
		for(int i=0;i<nE;++i)G.E[i] = int2(E[int2(0,i)],E[int2(1,i)]);
		G.edge_index();
		intf K(nV);
		K<<maxK;
		gibbs_energy energy(G,K);
		for(int i=0;i<nV;++i)energy.f1[i] << f1.get_range(int2(0,i),maxK);
		dynamic::fixed_array1<pf_matrix<ffloat> > F2;
		F2.resize(nE);
		for(int i=0;i<nE;++i){
			pf_matrix<ffloat> & m = F2[i];
			m.resize(int2(maxK,maxK));
			for(iter2 jj(int2(maxK,maxK));jj.allowed();++jj){
				m[jj] = (ffloat)f2[jj|i];
			};
			energy.f2[i] = &m;
		};

		alg_trws trws(energy);
		if(!M_bw0.is_empty()){
			for(int i=0;i<nE;++i){
				trws.M[i][0] << M_bw0.get_pvect(int2(0,i));
			};
		};
		trws.run_converge(eps,maxit);
	
		//mexPrintf("nlhs: %i\n",nlhs);

		//allocate output best labeling
		mextype<int,1>::DataSet r1;
		if(nlhs>=1){
			r1  = create_dataset<int,1>(nV,plhs[0]);
		};

		//output best Lower Bound
		if(nlhs>=2){
			mextype<double,1>::DataSet r2  = create_dataset<double,1>(1,plhs[1]);
			r2[0] = trws.LB;
		};

		//output min-marginals
		if(nlhs>=3){
			mextype<double,2>::DataSet r3  = create_dataset<double,2>(f1.size(),plhs[2]);
			for(int s=0;s<nV;++s){
				for(int j=0;j<maxK;++j){
					r3[int2(j,s)] = trws.PHI[s][j];
				};
			};
		};

		//output best dual solution
		if(nlhs>=4){
			mextype<double,2>::DataSet r4  = create_dataset<double,2>(int2(maxK,nE),plhs[3]);
			for(int st=0;st<nE;++st){
				for(int j=0;j<maxK;++j){
					r4[int2(j,st)] = trws.M[st][0][j];
				};
			};
		};

		trws.last_iteration();

		//output best labeling (changes trws.PHI)
		if(nlhs>=1){
			r1 << trws.x;
		};

		stream.detach();
		errstream.detach();

	}catch(std::exception & e){
		mexPrintf("exception: %s", e.what());
		mexErrMsgTxt("\nterminated.");
	}catch(char * s){
		mexPrintf("exception: %s",s);
		mexErrMsgTxt("\nterminated.");
	}catch(int e){
		mexPrintf("unknown int exception %i",e);
		mexErrMsgTxt("\nterminated.");
	};					 
};