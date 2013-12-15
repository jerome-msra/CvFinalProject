#include <mex.h>
#include <string>
#include "mex/mexargs.h"
#include "exttype/fixed_vect.h"

using namespace mexargs;
using namespace exttype;

std::string maxflow_check_args(int nrhs, const mxArray *prhs[]){
	if (nrhs !=6 )return "6 input arguments expected";
	return "";
};

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
	using namespace exttype;

	std::string err = maxflow_check_args(nrhs,prhs);
	if(!err.empty()){
		mexErrMsgTxt((std::string("[x LB] = matching_cost_q_mex([int32] I1, [int32] I2,[int32] K,[int32] x0,[int32] block_size, [float] q)::input error:\n")+err+".\n").c_str());
	};
	try{
		if(nlhs==0){
			return;
		};

		mextype<int,2>::DataSet I1 = dataset<int,2>(prhs[0]);
		mextype<int,2>::DataSet I2 = dataset<int,2>(prhs[1]);

		int2 K = int2() << dataset<int,1>(prhs[2]).get_pvect(0);
		int2 x0 = int2() << dataset<int,1>(prhs[3]).get_pvect(0);

		int block_size = dataset<int,1>(prhs[4])[0];
		mextype<float,2>::DataSet q = dataset<float,2>(prhs[5]);

		int2 sz = I1.size();
		int2 sz2 = I2.size();
		int2 n = sz/block_size;

		mextype<float,4>::DataSet r1  = create_dataset<float,4>(K|n,plhs[0]);
		fixed_vect<float> g(n[0]);

		//int * e1 = I1.getBuffer().end();
		int * e2 = I2.getBuffer().end();

		for(iter2 kk(K);kk.allowed();++kk){
			int2 ii1(0,0);
			int2 ii2 = x0+kk;
			for(int i2=0;i2<n[1];++i2){
				g << 0;
				for(int b2 =0;b2<block_size;++b2){
					if(ii2[1]< 0 || ii2[1]> sz2[1]){
						int * pI1 = I1.get_ptr(ii1);
					}else{
						int * pI1 = I1.get_ptr(ii1);
						int * pI2 = I2.get_ptr(ii2);
						float * pg = g.begin();
						while(pg!=g.end()){
							for(int b1=0;b1<block_size;++b1){
								//if(pI2>=e2){
								//	*pg+=q[int2(*pI1,0)];
								//}else{
								*pg+=q[int2(*pI1,*pI2)];
								//};
								++pI1;
								++pI2;
							};
							++pg;
						};
					};
					++ii1[1];
					++ii2[1];
				};
				for(int i=0;i<n[0];++i){
					r1[kk|int2(i,i2)] = g[i];
				};
			};
		};

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