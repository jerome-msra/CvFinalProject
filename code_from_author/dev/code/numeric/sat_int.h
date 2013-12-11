#ifndef sat_int_h
#define sat_int_h

#include <limits>

namespace exttype{
		template<class inttype> class sat_int{
	private:
		union{
			inttype i;
			struct{
				unsigned inf : 1;
				unsigned digits : std::numeric_limits<inttype>::digits-2;
				unsigned negative : 1;
			}bits;
		}val;
	public:
		static const sat_int inf(){
			return 1;//std::numeric_limits<inttype>::max();
		};
	private:
		sat_int cpy()const{
			return *this;
		};
	public:
		sat_int(){};//uninitialized
		sat_int(const inttype & c){
			val.i = c;
		};

		sat_int(const sat_int & x){
			val.i = x.val.i;
		};
		void operator = (const sat_int & x){
			val.i = x.val.i;
		};
	public:
		bool operator == (const sat_int & x)const{
			return val.i == x.val.i;
		};
		bool operator != (const sat_int & x)const{
			return !operator==(x);
		};
		bool operator >(const sat_int & x)const{
			return(val.i>x.val.i);
		};
		bool operator >=(const sat_int & x)const{
			return(val.i>=x.val.i);
		};
		bool operator <(const sat_int & x)const{
			return(val.i<x.val.i);
		};
		bool operator <=(const sat_int & x)const{
			return(val.i<=x.val.i);
		};

		bool operator >(const inttype & x)const{
			return(val.i>x);
		};
		bool operator >=(const inttype & x)const{
			return(val.i>=x);
		};
		bool operator <(const inttype & x)const{
			return(val.i<x);
		};
		bool operator <=(const inttype & x)const{
			return(val.i<=x);
		};

		bool is_infty()const {return val.bits.inf;};

	public:
		//operator inttype& (){return val.i;};
		//operator const inttype& ()const{return val.i;};
	public:

		sat_int & operator+=(const sat_int & x){
			if(x>0){
				if(x.val.bits.inf) 
			}else{
			};
			return *this;
		};
		sat_int operator+(const sat_int & x)const{
			return cpy()+=x;
		};
		sat_int & operator-=(const sat_int & x){
			if(!x.is_infty()){
			if(!is_infty()){
				val.i-=x.val.i;
			}else{
				val = x.val;
			};
			return *this;
			/*
			__asm{
				jo overflow
			};
			return *this;
			overflow:
				if (x.val.i<0) val.i = inf(); else val.i = -inf();
			return *this;
			*/
		};
		sat_int operator-(const sat_int & x)const{
			return cpy()-=x;
		};
		sat_int operator-()const{
			return -val.i;
		};
		sat_int & operator/=(const sat_int & x){
			val.i/=x.val.i;
			return *this;
		};
		sat_int & operator*=(const sat_int & x){
			val.i*=x.val.i;
			return *this;
		};
		sat_int operator*(const sat_int & x)const{
			return cpy()*=x;
		};
		sat_int operator/(const sat_int & x)const{
			return cpy()/=x;
		};
	public:
		template<typename other> sat_int& operator+=(const other& x){
			return (*this)+=sat_int(x);
		};
		template<typename other> sat_int& operator-=(const other& x){
			return (*this)-=sat_int(x);
		};
		template<typename other> sat_int& operator*=(const other& x){
			return (*this)*=sat_int(x);
		};
		template<typename other> sat_int& operator/=(const other& x){
			return (*this)/=sat_int(x);
		};

		template<typename other> sat_int operator+(const other& x)const{
			return (*this)+sat_int(x);
		};
		template<typename other> sat_int operator-(const other& x)const{
			return (*this)-sat_int(x);
		};
		template<typename other> sat_int operator*(const other& x)const{
			return (*this)*sat_int(x);
		};
		template<typename other> sat_int operator/(const other& x)const{
			return (*this)/sat_int(x);
		};
	};

	//sat_int<int> operator * (const int & a, const sat_int<int> & x);

	template class sat_int<int>;
};

#endif