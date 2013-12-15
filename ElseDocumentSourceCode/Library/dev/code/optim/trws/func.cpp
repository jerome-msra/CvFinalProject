#include "func.h"

//#include "debug/logs.h"

namespace maxplus{
	single_func * single_func::f1_temp;

	//________________________hard_continuity_______________________
	/*
	ffloat hard_continuity::q(int j,int k)const{
		if(std::abs(j-k)<=max_d)return 0;
		return -s*(std::abs(j-k)-max_d);
	};
	*/

		//_________________truncated_difference___________________
	/*
	ffloat truncated_difference::q(int j,int k)const{
			//return 0;
			return std::max(ffloat(std::abs(j-k))*s,c);
			//return ffloat(std::abs(j-k))*s;
		};
	*/
	void inline trunc_diff::max_prod(single_func & result, const single_func & val)const{
		int K=result.size();
		//result << val;
		result[0] = val[0];
		ffloat roof = val[0];
		//int i=1;
		for(int i=1;i<K;++i){
			result[i] = std::max(val[i],roof);
			roof = std::max(roof-s,val[i]);
		};
		roof = val[K-1];
		for(int i=K-2;i>=0;--i){
			result[i] = std::max(result[i],roof);
			roof = std::max(roof-s,val[i]);
		};
	};

	void trunc_diff::max_product(single_func & result, const single_func & val)const{
		max_prod(result,val);
		//parent::max_product(result,val);
	};
	void trunc_diff::max_product_transp(single_func & result, const single_func & val)const{
		max_prod(result,val);
		//parent::max_product_transp(result,val);
	};
	
	//_________________reg_trunc_diff___________________
	/*
	double reg_trunc_diff::q(int j,int k)const{
		int d = std::abs(j-k);
		return -std::max((d-max_d)*s+rc,d*rc);
	};
	*/

	void inline reg_trunc_diff::max_prod(single_func & result, const single_func & val)const{
		/*
		int n = result.count();
		if(n>=2){
			result << val;
			for(ffloat * pvm =val.begin(), *pr = result.begin()+1;pr<result.end()-1;++pvm,++pr){
				*pr = std::max(*pr,*pvm-rc);
			};
			for(ffloat *pvp = val.begin()+2, *pr = result.begin()+1;pr<result.end()-1;++pvp,++pr){
				*pr = std::max(*pr,*pvp-rc);
			};
			result[0] = std::max(val[0],val[1]-rc);
			result[n-1] = std::max(val[n-1],val[n-2]-rc);
		}else{
			result << val;
		};
		return;
		*/
		
		//last->
		
		int n = result.count();
		if(n>=2){
			for(int i=1;i<n-1;++i){
				ffloat v = val[i];
				v = std::max(v,val[i+1]-rc);
				v = std::max(v,val[i-1]-rc);
				result[i] = v;
			};
			result[0] = std::max(val[0],val[1]-rc);
			result[n-1] = std::max(val[n-1],val[n-2]-rc);
		}else{
			result << val;
		};
		return;
		

		/*
		//parent::max_product(result,val);
		//return;
		int K=result.size();
		//result << val;
		result[0] = val[0];
		ffloat roof = val[0]-rc;
		//int i=1;
		for(int i=1;i<K;++i){
			result[i] = std::max(val[i],roof);
			roof = std::max(roof-s,val[i]-rc);
		};
		roof = val[K-1]-rc;
		for(int i=K-2;i>=0;--i){
			result[i] = std::max(result[i],roof);
			roof = std::max(roof-s,val[i]-rc);
		};
		*/

		/*
		vect r(K);

		parent::max_product(single_func(r),val);

		for(int i=0;i<K;++i){
			if(result[i]!=r[i]){
				stream<<r<<"\n"<<result<<"\n";
				__asm{int(3)};
			};
		};
		*/
	};

	void reg_trunc_diff::max_product(single_func & result, const single_func & val)const{
		max_prod(result,val);
		//parent::max_product(result,val);
	};
	void reg_trunc_diff::max_product_transp(single_func & result, const single_func & val)const{
		max_prod(result,val);
		//parent::max_product_transp(result,val);
	};

	//__________________hadr_diff_1_reg______________________________
	void inline hard_diff_1_reg::max_prod(single_func & result, const single_func & val)const{
/*
		int n = result.count();
		if(n>=2){
			for(int i=1;i<n-1;++i){
				ffloat v = val[i];
				v = std::max(v,val[i+1]-rc);
				v = std::max(v,val[i-1]-rc);
				result[i] = v;
			};
			result[0] = std::max(val[0],val[1]-rc);
			result[n-1] = std::max(val[n-1],val[n-2]-rc);
		}else{
			result << val;
		};
		return;
*/

		int2 range = val.get_range();
		//result.set_range(std::max(0,range[0]-1),std::min(result.count(),range[1]+1));
		assert(range[1]>range[0]);
		assert(result.size()>=range[1]);
		ffloat * v = val.begin()+range[0];
		ffloat * v_e1 = val.begin()+range[1]-1;
		ffloat * r = result.begin()+range[0]-1;
		if(range[0]>0){
			*r=*v-rc;
			result.set_range_beg(range[0]-1);
		}else{
			result.set_range_end(range[0]);
		};
		++r;
		if(v<v_e1){ //range[1]-range[0]>1
			ffloat v1 = *v;
			++v;
			*r=std::max(v1,*v-rc);
			++r;
			while(v<v_e1){
				ffloat w = *v; 
				++v;
				if(*v>v1)v1=*v;
				v1-=rc;
				if(w>v1)*r=w;
				else *r=v1;
				v1=w;
				++r;
			};
			v1-=rc;
			if(*v>v1)*r=*v;
			else *r=v1;
			++r;
		}else{ //range[1]-range[0]=1
			*r=*v;
			++r;
		};
		if(r<result.end()){
			*r = *v-rc;
			result.set_range_end(range[1]+1);
		}else{
			result.set_range_end(range[1]);
		};

		return;
		/*
		{// check by reliable code
			int2 range = val.get_range();
			assert(result.get_range() == int2(std::max(0,range[0]-1),std::min(result.count(),range[1]+1)));
			ffloat v1, v, v2,w;
			int i=range[0];
			v1 = -ffloat::inf();
			v  = val[i];
			if(i>0){
				assert(result[i-1]==v-rc);
			};
			while(i<range[1]-1){
				v2 = val[i+1];
				w = std::max(v1,v2)-rc;
				w = std::max(v,w);
				assert(result[i] == w);
				v1=v;
				v=v2;
				++i;
			};
			assert(result[i] == std::max(v,v1-rc));
			if(range[1]<val.size()){
				assert(result[i+1] == v-rc);
			};
		};
		return;
		*/
/*
		int2 range = val.get_range();
		result.set_range(std::max(0,range[0]-1),std::min(result.count(),range[1]+1));
		assert(range[1]>range[0]);
		ffloat v1, v, v2,w;
		int i=range[0];
		v1 = -ffloat::inf();
		v  = val[i];
		if(i>0){
			result[i-1]=v-rc;
		};
		while(i<range[1]-1){
			v2 = val[i+1];
			w = std::max(v1,v2)-rc;
			w = std::max(v,w);
			result[i] = w;
			v1=v;
			v=v2;
			++i;
		};
		result[i] = std::max(v,v1-rc);
		if(range[1]<val.size()){
			result[i+1] = v-rc;
		};
		return;
*/
/**/
	};

	void hard_diff_1_reg::max_product(single_func & result, const single_func & val)const{
		max_prod(result,val);
	};
	void hard_diff_1_reg::max_product_transp(single_func & result, const single_func & val)const{
		max_prod(result,val);
	};


//__________________hard_diff_1______________________________
	void inline hard_diff_1::max_prod(single_func & result, const single_func & val)const{
		int2 range = val.get_range();
		assert(range[1]>range[0]);
		assert(result.size()>=range[1]);
		ffloat * v = val.begin()+range[0];
		ffloat * v_e1 = val.begin()+range[1]-1;
		ffloat * r = result.begin()+range[0]-1;
		if(range[0]>0){
			*r=*v;
			result.set_range_beg(range[0]-1);
		}else{
			result.set_range_end(range[0]);
		};
		++r;
		if(v<v_e1){ //range[1]-range[0]>1
			ffloat v1 = *v;
			++v;
			*r=std::max(v1,*v);
			++r;
			while(v<v_e1){
				ffloat w = *v; 
				++v;
				if(*v>v1)v1=*v;
				if(w>v1)*r=w;
				else *r=v1;
				v1=w;
				++r;
			};
			if(*v>v1)*r=*v;
			else *r=v1;
			++r;
		}else{ //range[1]-range[0]=1
			*r=*v;
			++r;
		};
		if(r<result.end()){
			*r = *v;
			result.set_range_end(range[1]+1);
		}else{
			result.set_range_end(range[1]);
		};
	};

	void hard_diff_1::max_product(single_func & result, const single_func & val)const{
		max_prod(result,val);
	};
	void hard_diff_1::max_product_transp(single_func & result, const single_func & val)const{
		max_prod(result,val);
	};
//_______________________potts_pair_model__________________________________
	void inline pots_pair_model::max_prod(single_func & result, const single_func & val)const{	
		int2 range = val.get_range();
		assert(range[1]>range[0]);
		assert(result.size()>=range[1]);
		
		ffloat z = val.max().first-c;
		
//		result<<z;
//		return;

		int i=0;
		for(;i<val.get_range()[0];++i){
			result[i] = z;
		};

		for(;i<val.get_range()[1];++i){
			result[i] = std::max(val[i],z);
		};
		for(;i<val.size();++i){
			result[i] = z;
		};

	};

	void pots_pair_model::max_product(single_func & result, const single_func & val)const{
		max_prod(result,val);
	};
	void pots_pair_model::max_product_transp(single_func & result, const single_func & val)const{
		max_prod(result,val);
	};

//_______________________trunc_potts_pair_model__________________________________
	void inline trunc_pots_pair_model::max_prod(single_func & result, const single_func & val)const{	
		int2 range = val.get_range();
		assert(range[1]>range[0]);
		assert(result.size()>=range[1]);
		
//		ffloat z = val.max().first-c;
		
//		result<<z;
//		return;
		int2 rrange = result.get_range();
		rrange = int2(std::max(rrange[0],range[0]-maxd),std::min(rrange[1],range[1]+maxd));
		result.set_range(rrange);

		int i=rrange[0];
		for(;i<rrange[1];++i){
			ffloat z = -FINF;
			for(int k=-maxd;k<=maxd;++k){
				if(i+k<range[0] || i+k>=range[1])continue;
				z = std::max(z,val[i+k]);
			};
			result[i] = z-c;
		};

		i=rrange[0];
		for(;i<range[0];++i){
//			result[i] = z[i];
		};

		for(;i<range[1];++i){
			result[i] = std::max(val[i],result[i]);
		};
		for(;i<rrange[1];++i){
//			result[i] = z;
		};
	};

	void trunc_pots_pair_model::max_product(single_func & result, const single_func & val)const{
		max_prod(result,val);
	};
	void trunc_pots_pair_model::max_product_transp(single_func & result, const single_func & val)const{
		max_prod(result,val);
	};

};