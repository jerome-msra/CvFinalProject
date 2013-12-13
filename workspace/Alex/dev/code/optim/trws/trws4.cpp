#include "trws4.h"

//#include "debug/performance.h"
#include "debug/logs.h"

namespace maxplus{
	using namespace debug;

	//______________________trws_alg________________________________
	void alg_trws::init(){
		M.resize(G.nE()*2);
		PHI.resize(G.nV());
		c0.resize(G.nV());
		for(int i=0;i<G.nV();++i){
			PHI[i].resize(K[i]);
			c0[i] = 0;
		};
		for(int i=0;i<G.nE();++i){
			M[i][0].resize(K[G.E[i][0]]);
			M[i][1].resize(K[G.E[i][1]]);
			M[i][0] << 0;
			M[i][1] << 0;
		};
		maxK = K.max().first;
		//Phi.reserve(maxK);
		Phi1.reserve(maxK);
		M1.reserve(maxK);
		x.resize(G.nV());
		//n_s.resize(G.nV());
		LB1 = 0;
		LB = 0;
		single_func::f1_temp = new single_func(200);
	};
	alg_trws::~alg_trws(){
		delete single_func::f1_temp;
	};

	void alg_trws::iteration_init(){
		LB1 = LB;
		LB = 0;
		dM = 0;
		dPhi = 0;
	};

	template<bool dir> void alg_trws::node_update(int s, bool bounds){
		const intf & in = G.in[s];
		const intf & out = G.out[s];
		func1 & Phi = PHI[s];
		if(bounds){
			Phi1 = Phi;
		};
		int n_in = in.size();
		int n_out = out.size();
		Phi = E.f1[s];
		for(int j = 0;j<n_in;++j){
			Phi+=M[in[j]][1];
		};
		for(int j = 0;j<n_out;++j){
			Phi+=M[out[j]][0];
		};
		//		int n_s = std::min(n_in,n_out)+std::abs(n_in-n_out);
		//		if(n_s==1){
		//			debug::stream<<s<<": in"<<in<<" out"<<out<<"\n";
		//		};
		Phi/=ffloat(n_s(s));
		std::pair<ffloat,int> a = Phi.max();
		ffloat d = a.first;//+c0[s];
		x[s] = a.second;
		Phi-=d;
		//c0[s]=-a.first;
		if(bounds){
			LB+=double(a.first)*n_s(s);
			//stream<<Phi<<"\n";
			dPhi = std::max(dPhi,double((Phi1-=Phi).maxabs().first));
			
			int n_term = n_s(s);
			if(dir){
				n_term-=n_out;
			}else{
				n_term-=n_in;
			};			
			//LB = LB+n_term*double(a.first);
			
			//if(n_term!=0)debug::stream<<"(s:"<<s<<")"<<LB<<"\n";
		};
		//PHI[s] = Phi;
	};

	template<bool dir> void alg_trws::edge_update(int st, bool bounds){
		int s = G.E[st][!dir];
		if(bounds){
			M1 = M[st][dir];
		};
		Phi1 = PHI[s];
		Phi1-= M[st][!dir];
		
		func1 & res = M[st][dir];

		//E.blabla<true>();
		//E.maxfunc<dir>(res,st,Phi1);
		if(dir){ 
			E.f2[st]->max_product_transp(res,Phi1);
		}else{
			E.f2[st]->max_product(res,Phi1);
		};
		
		//stream<<M[st][dir]<<"\n";
		if(bounds){
			M1-=M1.max().first;
			dM = std::max(dM,double(((M1-=M[st][dir])+=M[st][dir].max().first).maxabs().first));
		};
	};

	int alg_trws::n_s(int s){
		int n_in = G.in[s].size();
		int n_out = G.out[s].size();
		return std::min(n_in,n_out)+std::abs(n_in-n_out);
	};

	/*
	void alg_trws::first_iteration(){
	LB=0;
	for(int s=G.nV()-1;s>=0;--s){
	const intf & in = G.in[s];
	const intf & out = G.out[s];
	int n_in = in.size();
	int n_out = out.size();
	n_s[s] = std::min(n_in,n_out)+std::abs(n_in-n_out);
	PHI[s] = E.f1[s];
	Phi[s]/= n_s[s];
	const intf & ee = G.in[s];
	for(int j=0;j<ee.size();++j){
	edge_update<0>(ee[j],bounds);

	};
	};
	};
	*/

	void alg_trws::run(int niters){
		for(int i=0;i<niters;++i){
			bool bounds = (i==niters-1);
			iteration_init();
			for(int s=0;s<G.nV();++s){
				node_update<1>(s,false);
				const intf & ee = G.out[s];
				for(int j=0;j<ee.size();++j){
					edge_update<1>(ee[j],false);
				};
			};
			iteration_init();
			for(int s=G.nV()-1;s>=0;--s){
				node_update<0>(s,bounds);
				const intf & ee = G.in[s];
				for(int j=0;j<ee.size();++j){
					edge_update<0>(ee[j],bounds);
				};				
			};
		};
		dM = dM*G.nE()/std::abs(LB);
		dPhi = dPhi*G.nV()/std::abs(LB);
	};

	/*
	void alg_trws::basic_schedule(int niters){
		schedules.resize(4);
		schedules[0].reserve(nV+nE);
		for(int s=0;s<G.nV();++s){
			// update node
			schedules[0].push_back(schedule_operation(0,s,1,false));
			mgraph::intf & ee = G.out[s];
			for(int j=0;j<ee.size();++j){
				// update outcoming edges
				schedules[0].push_back(schedule_operation(1,ee[j],1,false));
			};				
		};
		schedules[1].reserve(nV+nE);
		for(int s=G.nV()-1;s>=0;--s){
			//update node -- reverse order
			schedules[1].push_back(schedule_operation(0,s,0,false));
			mgraph::intf & ee = G.in[s];
			for(int j=0;j<ee.size();++j){
				//update reverse edges
				schedules[1].push_back(schedule_operation(1,ee[j],0,false));
			};				
		};
		schedules[2].reserve(1);
		schedules[2].push_back(schedule_operation(-1,0,0,false));
		schedules[3].reserve(nV+nE);
		for(int s=G.nV()-1;s>=0;--s){
			//update node -- reverse order
			schedules[3].push_back(schedule_operation(0,s,0,true));
			mgraph::intf & ee = G.in[s];
			for(int j=0;j<ee.size();++j){
				//update reverse edges
				schedules[3].push_back(schedule_operation(1,ee[j],0,true));
			};				
		};
		my_schedule.resize(21);
		int k=0;
		for(int i=0;i<niters;++i){
			if(i==niters-1){
				my_schedule[k] = &schedules[0]; //forwadr
				++k;
				my_schedule[k] = &schedules[2]; //init_bounds
				++k;
				my_schedule[k] = &schedules[3]; //backward_bounds
				++k;
			}else{
				my_schedule[k] = &schedules[0]; //forward
				++k;
				my_schedule[k] = &schedules[1]; //backward
				++k;
			};
		};
	};

	void alg_trws::run_macro_schedule(const tmacro_schedule & mschedule,int niters){
		//for(int i=0;i<niters;++i){
		//bool bounds = (i==niters-1);
		//iteration_init();// todo: how to compute LB correctly with new schedule?
		for(int j=0;j<mschedule.size();++j){
			run_schedule(*mschedule[j]);
		};
		//};
	};


	void alg_trws::run_schedule(const tschedule & schedule){
		//iteration_init();
		for(int i = 0;i<schedule(size);++i){
			int ind = schedule[i].index;
			int op = schedule[i].update_type;
			int dir = schedule[i].dir;
			bool bounds = schedule[i].boundes;
			switch(op){
					case 0: if(dir==1){
								node_update<1>(ind,bounds);
							}else{
								node_update<0>(ind,bounds);
							};
						break;
					case 1: if(dir==1){
								edge_update<1>(ind,bounds);
							}else{
								edge_update<0>(ind,bounds);
							};
							break;
					case -1: iteration_init(); break;
			};
		};
	};
*/

	void alg_trws::fix_label(func1 & v,int k){
		/*
		for(int i=0;i<v.size();++i){
		if(i==k)continue;
		v[i] = -FINF;
		};
		*/
		v.set_range(k,k+1);
	};

	void alg_trws::last_iteration(){
		for(int s=0;s<G.nV();++s){
			node_update<1>(s,false);
			std::pair<ffloat,int> a = PHI[s].max();
			x[s] = a.second;
			fix_label(PHI[s],a.second);
			const intf & ee = G.out[s];
			for(int j=0;j<ee.size();++j){
				edge_update<1>(ee[j],false);
			};
		};
		for(int s=0;s<G.nV();++s){
			PHI[s].set_range(0,PHI[s].size());
		};
	};

	void alg_trws::run_converge(double eps, int maxit){
		//first_iteration();
		bool converged=false;
		for(int it=0;it<maxit;++it){
			//PerformanceCounter c1;
			run(10);
			//stream<<"it"<<10*(it+1)<<"\tLB="<<LB<<" |dM|="<<dM<<" |dPhi|="<<dPhi<<" time/10it="<<txt::String::Format("%3.2f",c1.time())<<"s.\n";
			stream<<"it"<<10*(it+1)<<"\tUB="<<LB<<" |dM|="<<dM<<" |dPhi|="<<dPhi<<"\n";
			if(dM<eps && dPhi<eps){
				stream<<"Converged to precision "<<eps<<".\n";
				converged = true;
				break;
			};
		};
		if(!converged){
			stream<<"Maximum number of iterations exceeded ("<<maxit<<").\n";
		};
		//tmessages sM = M;
		stream<<"LB = "<<LB<<" Q = "<<E.cost(x)<<"\n";
		//stream<<"LB = "<<LB<<" Q = "<<E.cost(x)<<"\n";
		//M = sM;
		//!todo: backward pass to calculate M_bw
	};
};