#ifndef geom_nmmatrix_h
#define geom_nmmatrix_h

#include "geom.h"
#include "exttype/arrays.h"
#include "geom/vectn.h"
#include "geom/imatrix.h"

namespace geom{

	template <int n> class matrixn;
	template <int n> class matrixn_defs{
	public:
		typedef fixedlist2<vectn<n>,double,n> container;
		typedef imatrix<matrixn<n>, container > parent;
		typedef vectn<n> tvectm;
		typedef vectn<n> tvectn;
	};

	//_____________________matrixn<n>______________________________
	template <int n> class matrixn : public matrixn_defs<n>::parent{
	private:
		typedef typename matrixn_defs<n>::parent parent;
		typedef vectn<n> tvect;
	public:
		matrixn(){};
		matrixn(int2 &){};
		matrixn(const tvect& v0,const tvect& v1,const tvect& v2 = tvect(),const tvect& v3 = tvect()){
			set_elements(v0,v1,v2,v3);
		};
	public:
		//default copy constructor
		//default operator = 
	};

	typedef matrixn<2> matrix2;
	typedef matrixn<3> matrix3;
	typedef matrixn<4> matrix4;

	//__________________________
	template <int n,int m> class nmmatrix;
	template <int n,int m> class nmmatrix_defs{
	public:
		typedef fixedlist2<vectn<m>,double,n> container;
		typedef imatrix<nmmatrix<n,m>, container > parent;
		typedef vectn<m> tvectm;
		typedef vectn<n> tvectn;
	};
	//________________________nmmatrix<n,m>____________________________
	template<int n, int m> class nmmatrix : public nmmatrix_defs<n,m>::parent{
	private:
		typedef typename nmmatrix_defs<n,m>::parent parent;
		typedef nmmatrix<n,m> matrix;
	public:
		typedef vectn<m> tvect;
		typedef vectn<n> tvectn;
	public:
		nmmatrix(){};
		nmmatrix(const int2 &){};
		nmmatrix(const tvect & x1, const tvect & x2 = tvect(), const tvect & x3 = tvect(), const tvect & x4 = tvect()){
			if(n>0)(*this)[0] = x1;
			if(n>1)(*this)[1] = x2;
			if(n>2)(*this)[2] = x3;
			if(n>3)(*this)[3] = x4;
		};
		nmmatrix(const matrix & x):parent(x){};
		nmmatrix(const matrixn<n> & x){
			(*this)<<x;
		};
		matrix cpy()const{matrix x ;x = *this; return x;};
		matrix operator *(const matrixn<m>& x)const{
			matrix r; 
			convolution<1,0>(r,(*this),x); 
			return r;
		};
		template <int k> nmmatrix<n,k> operator *(const nmmatrix<m,k> & x)const{
			nmmatrix<n,k> r; 
			convolution<1,0>(r,(*this),x); 
			return r;
		};
		matrixn<n> operator *(const nmmatrix<m,n> & x)const{
			matrixn<n> r; 
			convolution<1,0>(r,(*this),x); 
			return r;
		};

		matrix operator *(const double & k)const{
			return parent::operator*(k);
		};

		vectn<n> operator *(const vectn<m>& x)const{
			vectn<n> r; 
			convolution<1,0>(r,(*this),x); 
			return r;
		};
		nmmatrix<m,n> transp()const{
			nmmatrix<m,n> r;
			for(int i=0;i<count(0);i++)for(int j=0;j<count(1);j++)r[j][i]=(*this)[i][j];
			return r;
		};
	};
};

#endif