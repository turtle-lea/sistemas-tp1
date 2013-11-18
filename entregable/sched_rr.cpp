#include <vector>
#include <queue>
#include "sched_rr.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedRR::SchedRR(vector<int> argn) {
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro (MAX_QUANTUM)
	
	cores = argn[0];
	for(int i = 1; i <= cores; i++){
		max_quantum.push_back(argn[i]);
		cpu_quantum.push_back(0);
	}
}

SchedRR::~SchedRR() {

}


void SchedRR::load(int pid) {
	tareas.push(pid);
}

void SchedRR::unblock(int pid) {
	tareas.push(pid);
}

int SchedRR::tick(int cpu, const enum Motivo m) {
	int actual = current_pid(cpu);
	
	if(m == EXIT){
		if(!tareas.empty()){
			actual = next(cpu);
		}else{
			actual = IDLE_TASK;
		}
	}
	
	if(m == TICK){
		if(actual == IDLE_TASK){
			if(!tareas.empty()){
				actual = next(cpu);				
			}
		}else{
			cpu_quantum[cpu]++;	
			if(cpu_quantum[cpu] == max_quantum[cpu]){
				tareas.push(actual);
				actual = next(cpu);
			}
		}
	}
	
	if(m == BLOCK) {
		cpu_quantum[cpu]++;			
		if(!tareas.empty()){
			actual = next(cpu);
		}
		else actual=IDLE_TASK; 
	}
		
	return actual;
}
int SchedRR::next(int cpu){
	int prox = tareas.front();
	tareas.pop();
	cpu_quantum[cpu] = 0;
	return prox;
}
