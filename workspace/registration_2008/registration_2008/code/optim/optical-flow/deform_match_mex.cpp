#include <mex.h>
#include <string>

#include "deform_match.h"
//#include "optim/trws/trws4.h"
#include "mex/mexargs.h"
#include "debug/logs.h"
#include "files/xfs.h"

namespace maxplus{
	using namespace mexargs;
	using namespace debug;
	using namespace maxplus;

	std::string maxflow_check_args(int nrhs, const mxArray *prhs[]){
		if (nrhs <2 || nrhs>3 )return "2(3) input arguments expected";
		return "";
	};
};

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
	using namespace exttype;
	using namespace maxplus;
	// Check for proper number of arguments. 

	std::string err = maxflow_check_args(nrhs,prhs);
	if(!err.empty()){
		mexErrMsgTxt((std::string("[x LB M_bw] = deform_match_mex(Q,params,M_bw0=[])::input error:\n")+err+".\n").c_str());
	};
	try{
		MexLogStream log("log/output.txt",false);
		stream.attach(&log);
		MexLogStream err("log/errors.log",false);
		errstream.attach(&err);
		
		mextype<float,4>::DataSet Q = dataset<float,4>(prhs[0]);
		mextype<double,1>::DataSet params = dataset<double,1>(prhs[1]);

		mextype<float,2>::DataSet M_bw0;
		if(nrhs>=3){
			M_bw0 = dataset<float,2>(prhs[2]);
		};
		if(params.size()!=7){
			throw debug_exception("argument params must be of length 7");
		};

		double deform_reg = params[0];
		double eps = params[1];
		int maxit = (int)params[2];
		int maxd = (int)params[3];
		int fix_strategy = (int)params[4];
		int reg_model = (int)params[5];
		int reg_th = (int)params[6];
		
		deform_match model(Q,deform_match::tparams(deform_reg,maxd,eps,maxit));
		model.init();
		dynamic::DataSet<float,2,false> M_bw;

		M_bw = model.solve(M_bw0,fix_strategy);

		int2 nn = Q.size().rsub<2>();
		//output labeling
		if(nlhs>=1){
			mextype<int,3>::DataSet r1  = create_dataset<int,3>(nn|2,plhs[0]);
			for(iter2 ii(nn);ii.allowed();++ii){
				r1[ii|0] = model.x[ii][0];
				r1[ii|1] = model.x[ii][1];
			};
		};

		//output best Lower Bound
		if(nlhs>=2){
			mextype<double,1>::DataSet r2  = create_dataset<double,1>(1,plhs[1]);
			r2[0] = model.LB;
		};

		if(nlhs>=3){
			mextype<float,2>::DataSet r4  = create_dataset<float,2>(M_bw.size(),plhs[2]);
			r4 << M_bw;
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