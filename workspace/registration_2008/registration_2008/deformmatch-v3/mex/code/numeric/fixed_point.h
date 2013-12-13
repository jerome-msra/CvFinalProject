#ifndef fixed_point_h
#define fixed_point_h

#include <limits>
#include "geom/math.h"
//#include "sat_int.h"

namespace exttype{

	//_____________________Fixed point rationals________________________
	template<typename inttype, int frac_digits = (std::numeric_limits<int>::digits>>2)-1 > class fixed_point{
	public:
		static const int fractional_digits(){return frac_digits;};
		static const int integral_digits(){return std::numeric_limits<int>::digits - fractional_digits()-1;};
		static const int digits(){return integral_digits()+fractional_digits();};
		static const int unit(){return (1<<(fractional_digits()));}; 
	private:
		static const int my_bit_shift(){return fractional_digits();};
		static const int fractional_bitmask(){return ((1<<fractional_digits())-1);}; 
		static const int integral_bitmask(){return ((1<<integral_digits())-1)<<my_bit_shift();};
	public:
		static const fixed_point<inttype,frac_digits> inf(){return set_bits(std::numeric_limits<inttype>::max());};
	public:
		int val;
	public:
		bool is_inf()const{return val==inf() || val==-inf();};
		bool is_finate()const{!is_inf();};
		bool is_pos_inf()const{return val==inf();};
		bool is_neg_inf()const{return val==-inf();};
	private:
		int max_number()const{return inf();};
	public:
		fixed_point(){};
		explicit fixed_point(const int & x){
			*this = x;
		};
		fixed_point(const float & x){
			*this = x;
		};
		explicit fixed_point(const double & x){
			*this = x;
		};
		fixed_point & operator = (const int & x){
			val = x<<my_bit_shift();
			return *this;
		};
		void operator = (const float & x){
			val = inttype(x*unit());
		};
		void operator = (const double & x){
			val = inttype(x*unit());
		};
		const int& getv_bits()const{return val;};

		static fixed_point set_bits(int bits){
			fixed_point r; 
			r.val = bits;
			return r;
		};

		fixed_point & operator +=(const fixed_point & x){
			val+=x.val;
			return *this;
		};

		fixed_point & operator -=(const fixed_point & x){
			val-=x.val;
			return *this;
		};

		fixed_point operator +(const fixed_point & x)const{
			return fixed_point(*this)+=x;
		};

		fixed_point operator -(const fixed_point & x)const{
			return fixed_point(*this)-=x;
		};

		fixed_point operator -()const{
			return set_bits(-val);
		};

		fixed_point& operator *=(const int & x){
			val*=x;
			return *this;
		};

		fixed_point operator * (const int & x)const{
			return fixed_point(*this)*=x;
		};

		fixed_point& operator *=(const fixed_point & x){
			(*this)=(operator float()*x.operator float());
			return *this;
		};

		fixed_point& operator *=(const float & x){
			(*this)=(operator float()*x);
			return *this;
		};

		fixed_point& operator *=(const double & x){
			(*this)=(operator float()*x);
			return *this;
		};


		fixed_point operator * (const fixed_point & x)const{
			return fixed_point(*this)*=x;
		};
		fixed_point operator * (const float & x)const{
			return fixed_point(*this)*=x;
		};
		fixed_point operator * (const double & x)const{
			return fixed_point(*this)*=x;
		};
/*
		template<typename other> fixed_point<inttype,frac_digits> operator*(const other& x)const{
			return fixed_point(float(*this)*x);
		};
*/

		fixed_point & operator /= (const int x){
			val/=x;
			return *this;
		};

		fixed_point & operator /= (const fixed_point & x){
			(*this)=(operator float()/x.operator float());
			return *this;
		};

		fixed_point operator / (const fixed_point & x)const{
			return fixed_point(*this)/=x;
		};

		bool operator == (const fixed_point & x)const{
			return val == x.val;
		};

		bool operator != (const fixed_point & x)const{
			return !operator==(x);
		};

		bool operator <(const fixed_point & z)const{
			return val<z.val; // this < z
		};

		bool operator <=(const fixed_point & z)const{
			return !(z<*this);
		};

		bool operator >(const fixed_point & z)const{
			return (z<*this);
		};

		bool operator >=(const fixed_point & z)const{
			return !(*this<z);
		};

		/*
		template<class other> bool operator >(const other & x)const{
		return(*this>fixed_point(x));
		};
		template<class other> bool operator >=(const other & x)const{
		return(val.f>=fixed_point(x));
		};
		template<class other> bool operator <(const other & x)const{
		return(val.f<fixed_point(x));
		};
		template<class other> bool operator <=(const other & x)const{
		return(val.f<=fixed_point(x));
		};
		*/
		operator float()const{return float(val)/float(unit());};
	};


	namespace safe{//but so far buggy
		//_____________________Fixed point rationals________________________
		template<typename inttype, int frac_digits = (std::numeric_limits<int>::digits>>2)-1 > class fixed_point{
		public:
			static const int fractional_digits(){return frac_digits;};
			static const int integral_digits(){return std::numeric_limits<int>::digits - fractional_digits()-2;};
			static const int digits(){return integral_digits()+fractional_digits();};
			static const int unit(){return (1<<(fractional_digits()+1));}; 
		private:
			static const int my_bit_shift(){return fractional_digits()+1;};
			static const int fractional_bitmask(){return ((1<<fractional_digits())-1)<<1;}; 
			static const int integral_bitmask(){return ((1<<integral_digits())-1)<<my_bit_shift();};
		public:
			//static const fixed_point<inttype,frac_digits> inf(){return setbits(sat_int<int>::inf())
			static const fixed_point<inttype,frac_digits> inf(){return set_bits(1);};
		public:
			union{
				int val;
				struct{
					unsigned inf : 1;
					unsigned digits : std::numeric_limits<unsigned>::digits-2;
					unsigned negative : 1;
				}bits;
			}v;
		public:
			bool is_inf()const{return v.bits.inf;};
			bool is_finate()const{return !v.bits.inf;};
			bool is_pos_inf()const{return v.bits.inf && v.val>0;};
			bool is_neg_inf()const{return v.bits.inf && v.val<0;};
		private:
			int max_number()const{return (1<<(digits()+1))-1;};
		public:
			fixed_point(){};
			fixed_point(const int & x){
				*this = x;
			};
			fixed_point(const float & x){
				*this = x;
			};
			fixed_point(const double & x){
				*this = x;
			};
			fixed_point & operator = (const int & x){
				v.val = x<<my_bit_shift();
				return *this;
			};
			fixed_point & operator = (const float & x){
				float t = x*(1<<fractional_digits());
				if(geom::math::abs(t)<=max_number()){
					v.val = int(t)<<1;
				}else{
					v.val = geom::math::sgn(t);
				};
				return *this;
			};
			fixed_point & operator = (const double & x){
				double t = x*(1<<fractional_digits());
				if(geom::math::abs(t)<=max_number()){
					v.val = int(t)<<1;
				}else{
					v.val = geom::math::sgn(t);
				};
				return *this;
			};
			const int& getv_bits()const{return v.val;};

			static fixed_point set_bits(int bits){
				fixed_point r; 
				r.v.val = bits;
				return r;
			};
			/*
			fixed_point frac()const{
			if(v.val<0)return setv.val(v.val | ~fractional_bitmask());
			return setv.val(v.val & fractional_bitmask());
			};
			*/

			fixed_point & operator +=(const fixed_point & x){
				if(!is_inf()){
					v.val+=x.v.val;
				};
				return *this;
			};

			fixed_point & operator -=(const fixed_point & x){
				if(!is_inf()){
					v.val-=x.v.val;
				};
				return *this;
			};

			fixed_point operator +(const fixed_point & x)const{
				return fixed_point(*this)+=x;
			};

			fixed_point operator -(const fixed_point & x)const{
				return fixed_point(*this)-=x;
			};

			fixed_point operator -()const{
				return set_bits(-v.val);
			};

			fixed_point& operator *=(const int & x){
				if(!is_inf()){
					v.val*=x;
				}else{
					if(x<0)v.val=-v.val;
				};
				return *this;
			};

			fixed_point operator * (const int & x)const{
				return fixed_point(*this)*=x;
			};

			fixed_point& operator *=(const fixed_point & x){
				if(is_finate() && x.is_finate()){
					long long int big = v.val;
					big*=(x.v.val);
					big = big>>my_bit_shift();
					if (geom::math::abs(big) <= max_number()){
						v.val = int(big)&(-2);
					}else{
						v.val = geom::math::sgn(big);
					};
				}else{
					v.val = (v.val>0)^(x.v.val>0)?-inf():inf();
				};
				return *this;
			};

			fixed_point operator * (const fixed_point & x)const{
				return fixed_point(*this)*=x;
			};

			template<typename other> fixed_point<inttype,frac_digits> operator*(const other& x)const{
				return fixed_point(float(*this)*x);
			};
			/*
			fixed_point & operator /= (const int & x){
			v.val/=x;
			return *this;
			};
			*/
			fixed_point & operator /= (const fixed_point & x){
				if(is_finate() && x.is_finate()){
					long long big = ((long long)v.val)<<my_bit_shift();
					big = big/x.v.val;
					if (geom::math::abs(big) <= max_number()){
						v.val = int(big)&(-2);
					}else{
						v.val = geom::math::sgn(big);
					};
				}else{
					v.val = (v.val>0)^(x.v.val>0)?-inf():inf();
				};
				return *this;
			};

			fixed_point operator / (const fixed_point & x)const{
				return fixed_point(*this)/=x;
			};

			/*
			fixed_point operator / (const int & x)const{
			return fixed_point(*this)/=x;
			};
			*/

			/*
			fixed_point & operator >>(const int & n){
			v.val = v.val>>n;
			return *this;
			};

			fixed_point & operator <<(const int & n){
			v.val = v.val<<n;
			return *this;
			};
			*/

			bool operator == (const fixed_point & x)const{
				if(is_inf()){
					if(v.val>0)return x.is_pos_inf();
					else return x.is_neg_inf();
				};
				return v.val == x.v.val;
			};

			bool operator != (const fixed_point & x)const{
				return !operator==(x);
			};

			bool operator <(const fixed_point & z)const{
				if(z.is_inf()){
					if(z.v.val>0)return !is_pos_inf(); // this < +infty
					else return false; // this < -infty
				};
				if(is_finate()){
					return v.val<z.v.val; // this < z
				}else{
					return v.val<0; // this == -infty 
				};
			};

			bool operator <=(const fixed_point & z)const{
				return !(z<*this);
			};

			bool operator >(const fixed_point & z)const{
				return (z<*this);
			};

			bool operator >=(const fixed_point & z)const{
				return !(*this<z);
			};

			/*
			template<class other> bool operator >(const other & x)const{
			return(*this>fixed_point(x));
			};
			template<class other> bool operator >=(const other & x)const{
			return(val.f>=fixed_point(x));
			};
			template<class other> bool operator <(const other & x)const{
			return(val.f<fixed_point(x));
			};
			template<class other> bool operator <=(const other & x)const{
			return(val.f<=fixed_point(x));
			};
			*/
			//		operator short int()const{return v.val>>16;};
			//		operator int()const{return v.val>>16;};
			operator float()const{return float(v.val)/float(unit());};
			//		operator double()const{return double(v.val)/double(1<<16);};
		};
	};

	/*
	fixed_point floor(fixed_point & f);
	inline unsigned int scale2int(const fixed_point & x){
	return static_cast<const unsigned int>(x.getbits());
	};
	inline fixed_point & shr(fixed_point & x,const int & n){
	return x>>n;
	};
	inline fixed_point & shl(fixed_point & x,const int & n){
	return x<<n;
	};
	*/

	/*
	unsigned int scale2int(const float & x);
	float & shr(float & x,const int & n);
	float & shl(float & x,const int & n);
	*/

};

#endif