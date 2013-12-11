#include "dataset.h"

namespace dynamic{
	void test(){
		int3 CC;
		CC[0] = 0;
		CC << 0;
		geom::DataSetTopology<3> topology3;
		geom::DataSetTopology<3>::nb_iterator nbit1(int3(0,0,0),int3(10,10,10));
		geom::DataSetTopology<3>::dir_edge_iterator eit(int3(10,10,10));
		geom::DataSetTopology<3>::ndir_edge_iterator neit(int3(10,10,10));
		++neit;
		DataSet<int,2> data1 (int2(5,5),0);
		data1[int2(0,0)];
		DataSet<int,2,true> data2 (int2(5,5),0);
		data2[int2(0,0)];
	};
};