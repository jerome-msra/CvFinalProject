#pragma once

namespace debug{
	class Performance{
		public:
	};
	class PerformanceCounter{
		private:
		long long t1;
		long long Dt;
		public:
		PerformanceCounter();
		void start();
		int tickcount()const;
		double time()const;
		void pause();
		void resume();
	};
};
