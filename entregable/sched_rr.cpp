#include <vector>
#include <queue>
#include "sched_rr.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedRR::SchedRR(vector<int> argn) {
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
	
	cores = argn[0];
	for(int i = 1; i <= cores; i++){
		cpu_quantum.push_back(argn[i]);
		tareas_quantum.push_back(0);
	}
}

SchedRR::~SchedRR() {

}


void SchedRR::load(int pid) {
	tareas.push(pid);
}

void SchedRR::unblock(int pid) {
	
}

int SchedRR::tick(int cpu, const enum Motivo m) {
	int actual = current_pid(cpu);
	if(m == EXIT){
		if(!tareas.empty()){
			actual = tareas.front();
			tareas.pop();
			tareas_quantum[cpu] = 0;
		}else{
			actual = IDLE_TASK;
		}
	}else{
		if(actual == IDLE_TASK){
			actual = next2(actual, cpu);
		}
		if(actual != IDLE_TASK){
			tareas_quantum[cpu]++;
			//if(tareas_quantum[cpu] >= cpu_quantum[cpu]){
				actual = next2(actual,cpu);
			//}
		}	
	}
	return actual;
}
int SchedRR::next(int cpu){
	int prox = 0;
	return prox;
}

int SchedRR::next2(int pid, int cpu) {
	int prox;
	if(!tareas.empty()){
		if(pid != IDLE_TASK) tareas.push(pid);
		prox = tareas.front();
		tareas.pop();
		tareas_quantum[cpu] = 0;
	}else{
		prox = IDLE_TASK;
	}
	return prox;
}
