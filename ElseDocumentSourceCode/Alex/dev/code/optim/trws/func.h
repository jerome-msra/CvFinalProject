#ifndef maxplus_func_h
#define maxplus_func_h

#include <vector>
#include <stack>

#include "geom/math.h"
#include "exttype/pvect.h"
#include "data/dataset.h"
#include "exttype/arrays.h"

//#include "memmanager/static_allocator.h"
#include "dynamic/array_allocator.h"
#include "dynamic/fixed_array1.h"
#include "dynamic/fixed_array2.h"
#include "streams/xstringstream.h"

//#include "class_float.h"
#include "numeric/fixed_point.h"

#include <limits>

namespace maxplus{
	using namespace exttype;
	using namespace geom;
	//	using namespace datamanage;

	//typedef float ffloat;
	//const ffloat FINF = std::numeric_limits<float>::infinity();

	typedef double ffloat;
	const ffloat FINF = std::numeric_limits<double>::infinity();

	//  typedef exttype::class_float ffloat;
	//	const ffloat FINF = exttype::class_float::inf();

	//	typedef exttype::fixed_point<int,16> ffloat;
	//	#define FINF (ffloat::inf())

	//typedef float ffloat;
	//const ffloat FINF = std::numeric_limits<ffloat>::infinity();
	//typedef fixed_16_16::ffloat ffloat;
	//typedef pfield<ffloat> single_func;
	//typedef tvect<ffloat> tvect;

	template <class type> class my_allocator{
	public:
		typedef typename dynamic::fixed_array1<type, dynamic::array_allocator<type> > array;
	};

	//___________________single_func______________________
	//! Univariable function = vector of values
	class single_func : public ivector<single_func, my_allocator<ffloat>::array >{
	private:
		typedef ivector<single_func, my_allocator<ffloat>::array > parent;
	private:
		int2 range;
	public:
		const int2 get_range()const{return range;};
		void set_range(const int2 & n_range){
			if(n_range[1]>count() || n_range[0]<0 || n_range[0]>n_range[1])throw debug_exception("invalid subrange");
			range=n_range;
		};
		void set_range(int r_beg,int r_end){
			set_range(int2(r_beg,r_end));
		};
		void set_range_beg(int r_beg){
			range[0]=r_beg;
		};
		void set_range_end(int r_end){
			range[1]=r_end;
		};
	public:
		int count()const{return size();};
		single_func():range(0,0){};
		explicit single_func(int K):range(0,K){
			resize(K);
			for(int i=0;i<size();++i)(*this)[i] = 0;
		};
		//default operator =
		//default copy constructor
	private:
		single_func cpy()const{return single_func(*this);};
	public:
		static single_func * f1_temp;
	public:
			inline single_func & operator += (const single_func & x){
			range[0] = std::max(range[0],x.range[0]);
			range[1] = std::min(range[1],x.range[1]);
			
			for(int i=range[0];i<range[1];++i){
				(*this)[i]+=x[i];
			};
/*
			int i = range[0];
			while(i<range[1]-1){
				(*this)[i]+=x[i];
				(*this)[i+1]+=x[i+1];
				i+=2;
			};
			if(i<range[1]){
				(*this)[i]+=x[i];
			};
*/

/*			
			ffloat * it = this->begin()+range[0];
			ffloat * e_it = this->begin()+range[1];
			ffloat * r = f1_temp->begin();
			const ffloat * x_it = x.begin()+range[0];
			
			while(it!=e_it){
				*r = *it+*x_it;
				++x_it;
				++it;
				++r;
			};
*/
			/*
			it = this->begin()+range[0];
			r = f1_temp->begin();			
			while(it!=e_it){
				*it = *r;
				++it;
				++r;
			};
			*/
			
			//memcpy(it,temp->begin(),range[1]-range[0]);
			/*
			range[0] = std::max(range[0],x.range[0]);
			ffloat * it = this->begin()+range[0];
			range[1] = std::min(range[1],x.range[1]);
			ffloat * e_it = this->begin()+range[1];
			for(const ffloat * x_it = x.begin()+range[0];it!=e_it;++it,++x_it)(*it)+=(*x_it);
			//set_range(r_beg,r_end);
			*/
			return *this;
		};


		single_func operator+(const single_func & x)const{
			return single_func(*this)+=x;
		};

		single_func & operator -= (const single_func & x){
			range[0] = std::max(range[0],x.range[0]);
			ffloat * it = this->begin()+range[0];
			range[1] = std::min(range[1],x.range[1]);
			ffloat * e_it = this->begin()+range[1];
			for(const ffloat * x_it = x.begin()+range[0];it!=e_it;++it,++x_it)(*it)-=(*x_it);
			//set_range(r_beg,r_end);
			return *this;
		};

		single_func & operator += (const ffloat & k){
			for(int i=range[0];i<range[1];++i){
				(*this)[i]+=k;
			};
			return *this;
		};

		single_func & operator -= (const ffloat & k){
			for(int i=range[0];i<range[1];++i){
				(*this)[i]-=k;
			};
			return *this;
		};

		single_func operator-(const single_func & x)const{
			return single_func(*this)-=x;
		};

		single_func& operator *=(const ffloat k){
			for(int i=range[0];i<range[1];++i)(*this)[i]*=k;
			return *this;
		};

		single_func operator*(const ffloat k)const{
			return single_func(*this)*=k;
		};

		single_func& operator /=(const ffloat k){
			for(int i=range[0];i<range[1];++i)(*this)[i]/=k;
			return *this;
		};

		inline single_func& operator /=(const int k){
			for(int i=range[0];i<range[1];++i)(*this)[i]/=k;
			return *this;
		};

		single_func operator/(const ffloat k)const{
			return single_func(*this)/=k;
		};

		single_func & neg(){
			for(int i=range[0];i<range[1];++i)(*this)[i]=-(*this)[i];
			return *this;
		};

		single_func operator -()const{
			return cpy().neg();
		};

	public:

		ffloat & operator[](int i){
			assert(i>=range[0] && i<range[1]);
			return parent::operator [](i);
		};

		const ffloat & operator[](int i)const{
			assert(i>=range[0] && i<range[1]);
			return parent::operator [](i);
		};

	public:
		std::pair<ffloat,int> min()const{
			if(range[1]<=range[0])throw debug_exception("Empty vector, min is undefined");
			array_entry<ffloat> r((*this)[range[0]],range[0]);
			for(int i=range[0];i<range[1];++i){
				if((*this)[i]<r.value){
					r.value = (*this)[i];
					r.arg = i;
				};
			};
			return r;
		};

		std::pair<ffloat,int> max()const{
			if(range[1]<=range[0])throw debug_exception("Empty vector, min is undefined");
			array_entry<ffloat> r((*this)[range[0]],range[0]);
			for(int i=range[0];i<range[1];++i){
				if((*this)[i]>r.value){
					r.value = (*this)[i];
					r.arg = i;
				};
			};
			return r;
		};
		std::pair<ffloat,int> maxabs()const{
			if(range[1]<=range[0])throw debug_exception("Empty vector, min is undefined");
			array_entry<ffloat> r(std::abs((*this)[range[0]]),range[0]);
			for(int i=range[0];i<range[1];++i){
				ffloat d = std::abs((*this)[i]);
				if(d>r.value){
					r.value = d;
					r.arg = i;
				};
			};
			return r;
		};
	public:
		//! native assignment
		single_func& operator << (const single_func & x){
			if(size()!=x.size())resize(x.size());
			range = x.range;
			ffloat * it = this->begin()+range[0];
			ffloat * e_it = this->begin()+range[1];
			for(ffloat * x_it = x.begin()+range[0];it!=e_it;++it,++x_it)(*it)=(*x_it);
			/*
			*this=y;
			assert(range==y.get_range());
			*/
			return *this;
		};

		//! other assignment
		template <class target2, class base2> single_func& operator << (const ivector<target2, base2> & y){
			int sz = std::min(count(),y.count());
			range=int2(0,sz);
			for(int i=0;i<sz;++i){
				(*this)[i] = telement(y[i]);
			};
			return *this;
		};
		//! assignment
		inline single_func& operator << (const ffloat & c){
			range = int2(0,count());
			for(int i=0;i<count();++i){
				(*this)[i] = c;
			};
			return *this;
		};
	public:
		void resize(int nsize, const ffloat & val=ffloat()){
			//int bsize=size();
			parent::resize(nsize,val);
			//if(nsize<bsize)set_range(range[0],nsize);
			set_range(0,nsize);
		};
		void reserve(int nsize){
			parent::reserve(nsize);
		};
	};

	//______________________func_________________________
	//! Very abstract class for functions of several discrete variables
	class func{
	public:
		virtual ~func(){};
	};

	//______________________funcn________________________
	//! Abstract class for functions of rank discrete variables
	template<int rank> class funcn : public func{
	public:
		typedef fixedlist<single_func*,rank> pargs;
		typedef intn<rank> tindex;
		typedef itern<rank> titerator;
	public:
		virtual ffloat Q(intn<rank> k)=0;
		virtual void max_product(int t, const pargs & args, single_func & result)const=0;
	};

	//_____________________ifuncn________________________
	//! Generic and inefficient implementation of funcn
	/*! 
	requires: target::q(intn<rank>)
	max_product is computed by investigating all configurations
	*/
	template<int rank, class target> class ifuncn : public funcn<rank>{ 
	private:
		typedef funcn<rank> parent;
	private:
		target* self(){return static_cast<target*>(this);};
		const target* self()const{return static_cast<const target*>(this);};
	public:
		typedef typename parent::pargs pargs;
		typedef typename parent::tindex tindex;
	public:
		ifuncn(){};
	public:
		virtual ffloat Q(intn<rank> k){return self()->q(k);};
		//max over all except the t, writes output to result
		virtual void max_product(int t, const pargs & args, single_func & result)const{
			tindex CC;
			tindex cc;
			//			result.set_range(0,result.size());
			//			result<<-FINF;
			result.set_range(args[t]->get_range());
			for(int l=0;l<rank;++l){
				cc[l] = args[l]->get_range()[0];
				CC[l] = args[l]->get_range()[1];
			}
			range_itern<rank> ii(cc,CC);
			//itern<rank> ii(CC);
			do{
				ffloat &a = result[ii[t]];
				a = -FINF;
				do{
					ffloat x = 0;
					for(int l=0;l<rank;++l){
						if(l==t)continue;
						ffloat y = (*args[l])[ii[l]];
						//						if(y==-FINF)goto jump1;
						x+=y;
					};
					x+=self()->q(ii);
					a = std::max(a,x);
					//jump1:;
				}while(ii.iterate_skip_i(t));
				if(a==-FINF)throw debug_exception("func3:: -INF");
			}while(ii.iterate_i(t));
		};
	};
	//_________________max_marger_______________________
	//! Very abstract updater of conditional values
	class max_marger{
	public:
		virtual void update_marg(single_func & result)=0;
	};
	//_____________________max_margern_________________
	//! Abstract updater of conditional values using funcn<rank>
	template<int rank> class max_margern : public max_marger{
	public:
		typename funcn<rank>::pargs args;
		funcn<rank> * func;
		int target;
	public:
		max_margern():func(0){};
		virtual void update_marg(single_func & result){
			if(func)func->max_product(target,args, result);
		};
	};

	//__________________________________________________
	//______________________pairfuncs___________________

	template<class type> class pf_matrix;

	//______________________pair_func___________________
	//! Abstract function of two discrete variables
	class pair_func : public func{
	public:
		virtual ~pair_func(){};
		virtual ffloat Q(const int i, const int j)const=0;
		virtual void max_product(single_func & result, const single_func & val)const=0;
		virtual void max_product_transp(single_func & result, const single_func & val)const=0;
		//virtual pair_func * transp(){return 0;};
		//virtual const pair_func * transp()const{return 0;};
	public:
		virtual void get_matrix(pf_matrix<ffloat> * m)const{};
	};

	//______________________ipair_func___________________
	//! Generic (and inefficient) implementation of pair_func functionality
	/*!
	requires target::q(int,int)
	*/
	template<class target> class ipair_func : public pair_func{
	private:
		/*
		class pair_func_T : public pair_func{
		public:
			pair_func * T;
			pair_func_T(pair_func * f):T(f){};
		public:
			virtual ffloat Q(const int i, const int j)const{
				return T->Q(j,i);
			};
			virtual void max_product(single_func & result, const single_func & val)const{
				T->max_product_transp(result,val);
			};
			virtual void max_product_transp(single_func & result, const single_func & val)const{
				return T->max_product(result,val);
			};
//			virtual void max_product_n(single_func & result, const single_func & val)const{
//				T->max_product_transp_n(result,val);
//			};
//			virtual void max_product_transp_n(single_func & result, const single_func & val)const{
//				return T->max_product_n(result,val);
//			};
			virtual pair_func * transp(){return T;};
			virtual const pair_func * transp()const{return T;};
		private:
			virtual void get_matrix(pf_matrix<ffloat> * m)const{
				throw debug_exception("not implemented");
			};
		};
		pair_func_T T;
		*/
	private:
		target* self(){return static_cast<target*>(this);};
		const target* self()const{return static_cast<const target*>(this);};
	public:
		//ipair_func():T(0){T.T = this;};
		ipair_func(){};
	public:
		virtual ffloat Q(const int i, const int j)const{return self()->q(i,j);};
		virtual void max_product(single_func & result, const single_func & val)const{
			int K = result.size();
			int2 vrange = val.get_range();
			int2 rrange = result.get_range();
			for(int i=rrange[0];i<rrange[1];++i){
				result[i] = -FINF;
				for(int j=vrange[0];j<vrange[1];++j){
					result[i] = std::max(result[i],ffloat(self()->q(i,j))+val[j]);
				};
			};
		};
		virtual void max_product_transp(single_func & result, const single_func & val)const{
			int K = result.size();
			int2 vrange = val.get_range();
			int2 rrange = result.get_range();
			for(int i=rrange[0];i<rrange[1];++i){
				result[i] = -FINF;
				for(int j=vrange[0];j<vrange[1];++j){
					result[i] = std::max(result[i],ffloat(self()->q(j,i))+val[j]);
				};
			};
		};
		virtual void get_matrix(pf_matrix<ffloat> * m)const; //defined lower in the header
		//virtual pair_func * transp(){return &T;};
		//virtual const pair_func * transp()const{return &T;};
	};


	//______________________________________ipf_matrix______________________________________________
	template <class container, class type> class ipf_matrix : public ipair_func<ipf_matrix<container,type> >, public container{
	public:
		//typedef ipair_func<ipf_matrix<container> > parent;
		typedef container parent;
	public:
		ipf_matrix(){};
		ipf_matrix(const int2 & cc):parent(cc){};
	public:
		inline const type & q(const int i, const int j)const{
			return parent::operator[](int2(i,j));
		};
		inline const type & q(const int2 & ii)const{
			return parent::operator[](ii);
		};
		int count(int i=0)const{return parent::size()[i];};
public:
	
	virtual void max_product_transp(single_func & result, const single_func & val)const{
			int2 vrange = val.get_range();
			int2 rrange = result.get_range();

			ffloat * r = result.begin()+rrange[0];
			ffloat * r_e = result.begin()+rrange[1];

			ffloat * v_b = val.begin()+vrange[0];
			ffloat * v_e = val.begin()+vrange[1];

			int2 ii(vrange[0],rrange[0]);

			while(r<r_e){
				ffloat * v = v_b;
				const type * pq = &q(ii);
				*r = *pq+*v;
				++v;
				++pq;
				while(v<v_e){
					ffloat a = *pq+*v;
					++pq;
					if(*r<a){
						*r=a;
					};
					++v;
				};
				++r;
				++ii[1];
			};
		};
	
		virtual void max_product(single_func & result, const single_func & val)const{
			const int C = size()[1];
			int2 vrange = val.get_range();
			int2 rrange = result.get_range();

			ffloat * r_b = result.begin()+rrange[0];
			ffloat * r_e = result.begin()+rrange[1];

			ffloat * v = val.begin()+vrange[0];
			ffloat * v_e = val.begin()+vrange[1];

			int2 ii(rrange[0],vrange[0]);
			
			ffloat * r = r_b;
			const type * pq = &q(ii);
			while(r<r_e){
				*r = *pq+*v; 
				++r;
				++pq;
			};
			++ii[1];
			++v;

			while(v<v_e){
				ffloat * r = r_b;
				const type * pq = &q(ii);
				while(r<r_e){
					ffloat a = *pq+*v;
					++pq;
					if(*r<a){
						*r=a;
					};
					++r;
				};
				++ii[1];
				++v;
			};
		};
	};

	//______________________pf_matrix_________________
	//! Pair function matrix stored as fixed_array2
	template<class type> class pf_matrix : public ipf_matrix<dynamic::fixed_array2<type>,type>{
	private:
		typedef ipf_matrix<dynamic::fixed_array2<type>,type> parent;
	public:
		pf_matrix(){};
		pf_matrix(const int2 & cc):parent(cc){};
	};

//______________________ppf_matrix_________________
	//! Pair function matrix reffering to data via pfixed_array2
	template<class type> class ppf_matrix : public ipf_matrix<dynamic::pfixed_array2<type>,type>{
	private:
		typedef ipf_matrix<dynamic::pfixed_array2<type>,type> parent;
	public:
		ppf_matrix(type * val, const int2 & cc){
			parent::set_ref(val,cc);
		};
	};

/*
	//______________________pf_matrix_________________
	//! Pair function matrix stored as fixed_array2
	template<class type> class pf_matrix : public ipair_func<pf_matrix<type> >, public dynamic::fixed_array2<type>{
	private:
		typedef dynamic::fixed_array2<type> parent;
	public:
		//typedef pvect<type> single_func;
	public:
		pf_matrix(){};
		pf_matrix(const int2 & cc):parent(cc){};
		//default copy constructor
		//default operator =
	public:
		inline type q(const int i, const int j)const{
			return (*this)[int2(i,j)];
		};
		inline type q(const int2 & ii)const{
			return (*this)[ii];
		};
		int count(int i=0)const{return size()[i];};
		virtual void max_product(single_func & result, const single_func & val)const{
			int2 vrange = val.get_range();
			int2 rrange = result.get_range();

			ffloat * r = result.begin()+rrange[0];
			ffloat * r_e = result.begin()+rrange[1];

			ffloat * v_b = val.begin()+vrange[0];
			ffloat * v_e = val.begin()+vrange[1];

			int2 ii(rrange[0],vrange[0]);

			while(r<r_e){
				ffloat * v = v_b;
				const ffloat * pq = &(*this)[ii];
				*r = *pq+*v;
				++v;
				++pq;
				while(v<v_e){
					ffloat a = *pq+*v;
					++pq;
					if(*r<a){
						*r=a;
					};
					++v;
				};
				++r;
				++ii[0];
			};
		};
		virtual void max_product_transp(single_func & result, const single_func & val)const{
			const int C = size()[1];
			int2 vrange = val.get_range();
			int2 rrange = result.get_range();

			ffloat * r_b = result.begin()+rrange[0];
			ffloat * r_e = result.begin()+rrange[1];

			ffloat * v = val.begin()+vrange[0];
			ffloat * v_e = val.begin()+vrange[1];

			int2 ii(vrange[0],rrange[0]);
			
			ffloat * r = r_b;
			const ffloat * pq = &(*this)[ii];
			while(r<r_e){
				*r = *pq+*v; 
				++r;
				++pq;
			};
			++ii[0];
			++v;

			while(v<v_e){
				ffloat * r = r_b;
				const ffloat * pq = &(*this)[ii];
				while(r<r_e){
					ffloat a = *pq+*v;
					++pq;
					if(*r<a){
						*r=a;
					};
					++r;
				};
				++ii[0];
				++v;
			};
		};
	};
*/

template <class type> txt::TextStream& operator <<(txt::TextStream& stream, const pf_matrix<type>& x){
		for(int i=0;i<x.count();i++){
			stream<<"(";
			for(int j=0;j<x.count(1);++j){
				stream<<x[int2(i,j)]<<", ";
			};
			stream<<")\n";
		};
		stream<<"\n";
		return stream;
	};


	template<class target> void ipair_func<target>::get_matrix(pf_matrix<ffloat> * m)const{
		int K = m->size()[0];
		for(int i=0;i<K;++i){
			for(int j=0;j<K;++j){
				m->operator [](int2(i,j)) = self()->q(i,j);
			};
		};
	};


	//________________________abs_difference_______________________
	class abs_difference : public ipair_func<abs_difference>{
	private:
		maxplus::ffloat s;
	public:
		maxplus::ffloat q(int j,int k)const{
			return -maxplus::ffloat(std::abs(j-k))*s;
		};

	public:
		abs_difference(maxplus::ffloat scale):s(scale){};
	};


	//________________________hard_continuity_______________________
	class hard_continuity : public ipair_func<hard_continuity>{
	private:
		maxplus::ffloat s;
		int max_d;
	public:
		inline ffloat q(int j,int k)const{
			return -s*maxplus::ffloat(math::sqr(std::max(0,std::abs(j-k)-max_d)));
		};
	public:
		hard_continuity(maxplus::ffloat scale, int max_diff):s(scale),max_d(max_diff){};
	};

	//________________________trunc_diff_______________________
	class trunc_diff : public ipair_func<trunc_diff>{
	private:
		typedef ipair_func<trunc_diff> parent;
	private:
		maxplus::ffloat s;
		int max_d;
		ffloat c;
	public:
		inline ffloat q(int j,int k)const{
			return -maxplus::ffloat((std::max(std::abs(j-k),max_d)-max_d))*s;
		};
		inline void max_prod(single_func & result, const single_func & val)const;
	public:
		trunc_diff(maxplus::ffloat scale, int max_diff):s(scale),max_d(max_diff),c(max_diff*s){};
		//default copy constructor
		//default operator =
	public:
		virtual void max_product(single_func & result, const single_func & val)const;
		virtual void max_product_transp(single_func & result, const single_func & val)const;
	};

	//________________________reg_trunc_diff_______________________
	class reg_trunc_diff : public ipair_func<reg_trunc_diff>{
	private:
		typedef ipair_func<reg_trunc_diff> parent;
	private:
		maxplus::ffloat s;
		int max_d;
		ffloat c;
		ffloat rc;
	public:
		inline maxplus::ffloat q(int j,int k)const{
			int d = std::abs(j-k);
			return -std::max(maxplus::ffloat(d-max_d)*s+rc,rc*d);
		};
		inline void max_prod(single_func & result, const single_func & val)const;
	public:
		reg_trunc_diff(maxplus::ffloat scale, int max_diff, maxplus::ffloat reg_const):s(scale),max_d(max_diff),c(max_diff*s), rc(reg_const){};
		//default copy constructor
		//default operator =
	public:
		virtual void max_product(single_func & result, const single_func & val)const;
		virtual void max_product_transp(single_func & result, const single_func & val)const;
	};

	//________________________hard_diff_1_reg______________________
	class hard_diff_1_reg : public ipair_func<hard_diff_1_reg>{
		//
		// q(j,k) = 0, j==k; rc, |j-k|<2; -ffloat::inf(), |j-k|>=2 
		//
	private:
		typedef ipair_func<hard_diff_1_reg> parent;
	private:
		ffloat rc;
	public:
		inline maxplus::ffloat q(int j,int k)const{
			int d = std::abs(j-k);
			if(d>1)return -100;//-ffloat::inf();
			if(d>0)return -rc;
			return 0;
		};
		inline void max_prod(single_func & result, const single_func & val)const;
	public:
		hard_diff_1_reg(maxplus::ffloat reg_const):rc(reg_const){};
		//default copy constructor
		//default operator =
	public:
		virtual void max_product(single_func & result, const single_func & val)const;
		virtual void max_product_transp(single_func & result, const single_func & val)const;
	};
	//________________________hard_diff_1_______________________
	class hard_diff_1 : public ipair_func<hard_diff_1>{
		//
		// q(j,k) = 0, |j-k|<2; -ffloat::inf(), |j-k|>=2 
		//
	private:
		typedef ipair_func<hard_diff_1> parent;
	public:
		inline maxplus::ffloat q(int j,int k)const{
			int d = std::abs(j-k);
			if(d>1)return -100;//-ffloat::inf();
			return 0;
		};
		inline void max_prod(single_func & result, const single_func & val)const;
	public:
		hard_diff_1(){};
		//default copy constructor
		//default operator =
	public:
		virtual void max_product(single_func & result, const single_func & val)const;
		virtual void max_product_transp(single_func & result, const single_func & val)const;
	};
	//________________________pots_pair_model__________________________________
	class pots_pair_model : public ipair_func<pots_pair_model>{
		//
		// q(j,k) = 0, if j==k; -c, otherwise 
		//
	private:
		typedef ipair_func<pots_pair_model> parent;
	public:
		ffloat c;
	public:
		inline maxplus::ffloat q(int j,int k)const{
			int d = std::abs(j-k);
			if(d==0)return 0;
			return -c;
		};
		inline void max_prod(single_func & result, const single_func & val)const;
	public:
		pots_pair_model(const ffloat & penalty):c(penalty){};
		//default copy constructor
		//default operator =
	public:
		virtual void max_product(single_func & result, const single_func & val)const;
		virtual void max_product_transp(single_func & result, const single_func & val)const;
	};
	//________________________pots_pair_model__________________________________
	class trunc_pots_pair_model : public ipair_func<trunc_pots_pair_model>{
		//
		// q(j,k) = 0, if j==k; -c, otherwise 
		//
	private:
		typedef ipair_func<pots_pair_model> parent;
	public:
		ffloat c;
		int maxd;
	public:
		inline maxplus::ffloat q(int j,int k)const{
			int d = std::abs(j-k);
			if(d==0)return 0;
			if(d>maxd)return -100;
			return -c;
		};
		inline void max_prod(single_func & result, const single_func & val)const;
	public:
		trunc_pots_pair_model(const ffloat & penalty, int max_dist):c(penalty),maxd(max_dist){};
		//default copy constructor
		//default operator =
	public:
		virtual void max_product(single_func & result, const single_func & val)const;
		virtual void max_product_transp(single_func & result, const single_func & val)const;
	};
	//___________________pf_storage____________________
	class pf_storage : public std::stack<func* >{
	public:
		~pf_storage(){
			while(!empty()){
				delete top();
				pop();
			};
		};
	};

	//_________________shortcuts________________________
	typedef single_func func1;
	typedef pair_func func2;
	typedef funcn<3> func3;
	typedef funcn<4> func4;
	typedef max_margern<2> max_marger2;
	typedef max_margern<3> max_marger3;
	typedef max_margern<4> max_marger4;
};
#endif