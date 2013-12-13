#include "performance.h"
#include <afxwin.h>

namespace debug{
	PerformanceCounter::PerformanceCounter(){
		start();
	};
	void PerformanceCounter::start(){
		QueryPerformanceCounter((LARGE_INTEGER*)&t1);
		Dt = 0;
	};
	int PerformanceCounter::tickcount()const{
		__int64 t2;
		QueryPerformanceCounter((LARGE_INTEGER*)&t2);
		return (int)(t2-t1+Dt);
	};
	double PerformanceCounter::time()const{
		__int64 f;
		QueryPerformanceFrequency((LARGE_INTEGER*)&f);
		return double(tickcount())/f;
	};
	void PerformanceCounter::pause(){
		__int64 t2;
		QueryPerformanceCounter((LARGE_INTEGER*)&t2);
		Dt = Dt+(t2-t1);
		t1 = t2;
	};

	void PerformanceCounter::resume(){
		QueryPerformanceCounter((LARGE_INTEGER*)&t1);
	};
	
};
