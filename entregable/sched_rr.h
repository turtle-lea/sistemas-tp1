#ifndef __SCHED_RR__
#define __SCHED_RR__

#include <vector>
#include <queue>
#include "basesched.h"

class SchedRR : public SchedBase {
	public:
		SchedRR(std::vector<int> argn);
        ~SchedRR();
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);

	private:
		int next(int cpu);
		int next2(int pid, int cpu);
		
		int cores;
		std::vector<int> cpu_quantum;
		std::vector<int> tareas_quantum;
		
		std::queue<int> tareas;
};

#endif
