#ifndef __SCHED_LOTTERY__
#define __SCHED_LOTTERY__

#include <vector>
#include <utility>
#include "basesched.h"

class SchedLottery : public SchedBase {
	public:
		SchedLottery(std::vector<int> argn);
        	~SchedLottery();
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu,const enum Motivo m);

	private:
		//int next(int cpu);
		//int cores;
		//std::vector<int> cpu_quantum;
		void searchDestroyReady(int);
		int searchDestroyBlocked(int);
		int lottery();
		//bool already_blocked(int pid);

		int cores;
		std::vector<int> cpu_quantum;
		int max_quantum;
		
		int cantTickets;
		unsigned int semilla;
		std::vector< std::pair<int,int> > tareasReady; //<pid,cantTickets> 
		std::vector< std::pair<int,int> > tareasBlocked; //<pid,cantTickets> 
};

#endif
