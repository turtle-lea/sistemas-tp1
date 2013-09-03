#include <vector>
#include <queue>
#include "sched_fcfs.h"

using namespace std;

SchedFCFS::SchedFCFS(vector<int> argn) {
	// FCFS recibe la cantidad de cores.
}

SchedFCFS::~SchedFCFS() {
}

void SchedFCFS::load(int pid) {
	tareas.push(pid);
}

void SchedFCFS::unblock(int pid) {
}

int SchedFCFS::tick(int cpu, const enum Motivo m) {
	int proxima = current_pid(cpu);
	if (proxima == IDLE_TASK && !tareas.empty()) {
		proxima= tareas.front();
		tareas.pop();
	}

	if (m == EXIT){
		if(tareas.empty()){
			return IDLE_TASK;
		}
		else{
			proxima= tareas.front();
			tareas.pop();
		}		
	}

	return proxima;	
}
