#include "deform_match.h"

//#include "debug/performance.h"
#include "debug/logs.h"

#include "subdiv_it.h"

using namespace debug;

namespace maxplus{

	int deform_match::grid_node(const int3 & ii){
		return geometry.linindex(ii);
	};
	int deform_match::z_edge(const int2 & ii){
		return G.edge(grid_node(ii|0),grid_node(ii|1));
	};
	int deform_match::x_edge(const int3 & ii,int dir){
		if(dir){
			return G.edge(grid_node(ii),grid_node(ii+int3(1,0,0)));
		}else{
			return G.edge(grid_node(ii-int3(1,0,0)),grid_node(ii));
		};
	};
	int deform_match::y_edge(const int3 & ii,int dir){
		if(dir){
			return G.edge(grid_node(ii),grid_node(ii+int3(0,1,0)));
		}else{
			return G.edge(grid_node(ii-int3(0,1,0)),grid_node(ii));
		};
	};

	void deform_match::init(){
		geometry.setSize(n|2);
		G.create_grid<3,true>(n|2);
		intf K(G.nV());
		for(iter3 ii(n|2);ii.allowed();++ii){
			K[grid_node(ii)] = maxK[ii[2]];
		};
		energy.init(G,K);
		for(int s=0;s<G.nV();++s){
			energy.f1[s] <<  0;
		};
		//set Q on z-edges
		F2.reserve(G.nE());
		for(iter2 ii(n);ii.allowed();++ii){
			float * pf = Q.get_ptr(int2(0,0)|ii);
			F2.push_back(ppf_matrix<float>(&Q[int2(0,0)|ii],maxK));
			energy.f2[z_edge(ii)] = &F2.back();
		};
		//set regularization on x,y-edges
		m_dx = new hard_diff_1_reg(ffloat(0.001));
		//m_dx = new hard_diff_1();
		int3 cc(n[0]-1,n[1],2);
		for(iter3 ii(cc);ii.allowed();++ii){
			energy.f2[x_edge(ii)] = m_dx;
		};
		cc = int3(n[0],n[1]-1,2);
		for(iter3 ii(cc);ii.allowed();++ii){
			energy.f2[y_edge(ii)] = m_dx;
		};
		//other init
		x.resize(n);
		
		subdiv = 0;
		subdiv_1 = true;
		subdiv_layer = 0;
	};

	deform_match::~deform_match(){
		delete m_dx;
	};

	bool deform_match::all_fixed()const{
		return (2<<subdiv > 2*n.max().first);
	};

	void deform_match::fix_subdivide(){
		int2 size = n;
		if(2<<subdiv > 2*size.max().first)return;
		stream<<"fix_subdivide: level:"<<subdiv<<" v:"<<subdiv_1<<"\n";
		int2 s;
		if(subdiv_1){
			debug::stream<<"v-fixing:";
			for(subdiv_iterator sd(size[0],subdiv);sd.allowed();++sd){
				s[0] = sd.pos;
				debug::stream<<s[0]<<", ";
				for(s[1]=0;s[1]<n[1];++s[1]){
					for(int l=0;l<2;++l){
						int ss = grid_node(s|l);
						trws->node_update<1>(ss,false);
						trws->fix_label(energy.f1[ss],trws->x[ss]);
						trws->fix_label(trws->PHI[ss],trws->x[ss]);
						if(s[1]<n[1]-1)trws->edge_update<1>(y_edge(s|l,1),false);
						if(l==0)trws->edge_update<1>(z_edge(s),false);
					};
				};
				//backward message update
				for(s[1]=size[1]-1;s[1]>=0;--s[1]){
					for(int l=1;l>=0;--l){
						trws->node_update<0>(grid_node(s|l),false);
						if(s[1]>0)trws->edge_update<0>(y_edge(s|l,0),false);
						if(l==1)trws->edge_update<0>(z_edge(s),false);
					};
				};
			};
			debug::stream<<"\n";
		}else{
			debug::stream<<"h-fixing:";
			for(subdiv_iterator sd(size[1],subdiv);sd.allowed();++sd){
				s[1] = sd.pos;
				debug::stream<<s[1]<<", ";
				for(s[0]=0;s[0]<size[0];++s[0]){
					for(int l=0;l<2;++l){
						int ss = grid_node(s|l);
						trws->node_update<1>(ss,false);
						trws->fix_label(energy.f1[ss],trws->x[ss]);
						trws->fix_label(trws->PHI[ss],trws->x[ss]);
						if(s[0]<n[0]-1)trws->edge_update<1>(x_edge(s|l,1),false);
						if(l==0)trws->edge_update<1>(z_edge(s),false);
					};
				};
				//backward message update
				for(s[0]=size[0]-1;s[0]>=0;--s[0]){
					for(int l=1;l>=0;--l){
						trws->node_update<0>(grid_node(s|l),false);
						if(s[0]>0)trws->edge_update<0>(x_edge(s|l,0),false);
						if(l==1)trws->edge_update<0>(z_edge(s),false);
					};
				};
			};
			debug::stream<<"\n";
		};
		//if(++subdiv_layer==2){
		//	subdiv_layer = 0;
			subdiv_1 = !subdiv_1;
			if(subdiv_1)++subdiv;
		//};
		//bw_pass;
	};

	void deform_match::bw_pass(){
		for(int l=1;l>=0;--l){
			//backward
			for(iter2 ii(n);ii.allowed();++ii){
				int3 jj = (n-int2(1,1)-ii)|l;
				int s = grid_node(jj);
				trws->node_update<0>(s,false);
				if(jj[0]>0) trws->edge_update<0>(x_edge(jj,0),false);
				if(jj[1]>0) trws->edge_update<0>(y_edge(jj,0),false);
				if(l==1) trws->edge_update<0>(z_edge(int2(jj[0],jj[1])),false);
			};
		};
	};

	void deform_match::my_run(int niters, int intrait){
		trws->run(10);
		return;

		for(int i=0;i<niters;++i){
			bool last_i = (i==niters-1);
			//layer l
			for(int l=0;l<2;++l){
				// intralayer iterations
				for(int k=0;k<intrait;++k){
					bool last_k = (k==intrait-1);
					//forward
					for(iter2 ii(n);ii.allowed();++ii){
						int s = grid_node(ii|l);
						trws->node_update<1>(s,false);
						if(ii[0]<n[0]-1) trws->edge_update<1>(x_edge(ii|l,1),false);
						if(ii[1]<n[1]-1) trws->edge_update<1>(y_edge(ii|l,1),false);
					};
					//backward
					bool bounds = false;
					if(last_i && last_k && l==1){
						bounds = false;
						trws->iteration_init();
					};
					for(iter2 ii(n);ii.allowed();++ii){
						int3 jj = (n-int2(1,1)-ii)|l;
						int s = grid_node(jj);
						trws->node_update<0>(s,bounds);
						if(jj[0]>0) trws->edge_update<0>(x_edge(jj,0),bounds);
						if(jj[1]>0) trws->edge_update<0>(y_edge(jj,0),bounds);
					};
				};
				//interlayer updates (l)->(!l) 
				bool bounds = false;
				if(last_i && l==1){
					bounds = true;
				};
				for(iter2 ii(n);ii.allowed();++ii){
					int s = grid_node(ii|l);
					if(l==0){
						//trws->node_update<1>(s,false);
						trws->edge_update<1>(z_edge(ii),false);
					}else{
						//trws->node_update<0>(s,bounds);
						trws->edge_update<0>(z_edge(ii),bounds);
					};
				};
			};
		};
		trws->run(1);
	};

	void deform_match::my_run_converge(double eps, int maxit,int intrait){
		//first_iteration();
		bool converged=false;
		bool first_fix=true;
		int it=0;
		int all_it_max = 1000;
		//for(int it=0;it<maxit;++it){
		int all_it=0;
		while(!all_fixed() && all_it<all_it_max){
			//debug::PerformanceCounter c1;
			my_run(10,intrait);
			//stream<<"it"<<10*(it+1)<<"\tLB="<<trws->LB<<" |dM|="<<trws->dM<<" |dPhi|="<<trws->dPhi<<" time/10it="<<txt::String::Format("%3.2f",c1.time())<<"s.\n";
			stream<<"it"<<10*(it+1)<<"\tLB="<<trws->LB<<" |dM|="<<trws->dM<<" |dPhi|="<<trws->dPhi<<"\n";
			if((trws->dM<eps && trws->dPhi<eps) || it==maxit-1){
				if(it==maxit-1){
					stream<<"Maximum number of iterations exceeded ("<<maxit<<"). Forcing subdivide.\n";
				}else{
					stream<<"Step converged to precision "<<eps<<". Subdivide.\n";
				};
				if(first_fix){
					LB = trws->LB;
					first_fix = false;
				};
				fix_subdivide();
				it = 0;
			};
			/*
			if(trws->dM<eps && trws->dPhi<eps){
				stream<<"Converged to precision "<<eps<<".\n";
				converged = true;
				break;
			};
			*/
			++it;
			++all_it;
		};
		if(all_it>=all_it_max){
			stream<<"Maximum number of all iterations exceeded ("<<all_it_max<<").\n";
			trws->last_iteration();
		};

/*
		if(!converged){
			stream<<"Maximum number of iterations exceeded ("<<maxit<<").\n";
		};
*/
		//tmessages sM = M;
//		trws->last_iteration();
		//M = sM;
	};

	dynamic::DataSet<float,2,false> deform_match::solve(dynamic::DataSet<float,2,false> & M_bw0, int fix_strategy){
		trws = new alg_trws(energy);

		if(!M_bw0.is_empty()){
			for(int st=0;st<G.nE();++st){
				for(int j = 0;j<trws->M[st][0].size();++j){
					trws->M[st][0][j] = M_bw0[int2(j,st)];
				};
			};
		};

		if(fix_strategy==1){
			my_run_converge(params.eps,params.maxit,maxK.max().first/4);
		}else{
			trws->run_converge(params.eps,params.maxit);
			LB = trws->LB;
		};
		for(iter2 ii(n);ii.allowed();++ii){
			x[ii] = int2(trws->x[grid_node(ii|0)],trws->x[grid_node(ii|1)]);
		};
		
		dynamic::DataSet<float,2,false> r;
		r.resize(int2(maxK.max().first,G.nE()));
		// must be done before fixing any solutions, otherwise incorrect
		/*
		for(int st=0;st<G.nE();++st){
			for(int j = 0;j<trws->M[st][0].size();++j){
				r[int2(j,st)] = trws->M[st][0][j];
			};
		};
		*/
		delete trws;
		return r;
	};

};