#ifndef __SCHED_FCFS__
#define __SCHED_FCFS__

#include <vector>
#include <queue>
#include "basesched.h"

class SchedFCFS : public SchedBase {
	public:
		SchedFCFS(std::vector<int> argn);
	        ~SchedFCFS();
		void load(int pid);
		void unblock(int pid);
		int tick(int cpu, const enum Motivo m);
	
	private:
		std::queue<int> tareas;
};

#endif
