#ifndef geom_transform_hsolver_h
#define geom_transform_hsolver_h

#include "homography.h"
#include "geom/matrix.h"

namespace _geom{
	namespace homography{
		class H2Solver{
		private:
			matrix XTX;
			matrix3 Cp;
			matrix3 Cq;
			vect x;
			vect XTb;
		public:
			H2Solver();
		public:
			void init();
			void push_pair(const hvect2 & p, const hvect2 & q);
			void setScale_left(const matrix3 & Cp);
			void setScale_right(const matrix3 & Cq);
			H<2,2> solve();
		};
	};
};

#endif
