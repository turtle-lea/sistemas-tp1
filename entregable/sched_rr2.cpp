#include "sched_rr2.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedRR2::SchedRR2(vector<int> argn) {
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
	cores = argn[0];
	queue<int> q;
	set<int> s;
	for(int i = 1; i <= cores; i++){
		max_quantum.push_back(argn[i]);
		cpu_quantum.push_back(0);
		tareas.push_back(q);
		tareasBlocked.push_back(s);
	}
}

SchedRR2::~SchedRR2() {

}


void SchedRR2::load(int pid) {
	
	/* Ej dual-core (pid 4)
	 * 0 : [1] 3
	 * 1 : [2] ... 4 
	 * */
		
	int cant_tareas = tareas[0].size() + tareasBlocked[0].size();
	if(current_pid(0) != IDLE_TASK) cant_tareas++;
	int prox_cpu = 0;
	int aux;
	for(int i = 1; i < cores; i++){
		aux = tareas[i].size() + tareasBlocked[i].size();
		if(current_pid(i) != IDLE_TASK) aux++;
		if(aux < cant_tareas){
			cant_tareas = aux;
			prox_cpu = i;
		}
	}	
	tareas[prox_cpu].push(pid);
}

void SchedRR2::unblock(int pid) {
	set<int>::iterator it;
	for(int i = 0; i < cores; i++){
		it = tareasBlocked[i].find(pid);	//busco pid en el iesimo set de tareasBlocked
		if(it != tareasBlocked[i].end()){	//si lo encuentro, borro la tarea del set y la pongo en la iesima cola ready
			tareas[i].push(pid);
			tareasBlocked[i].erase(pid);
		}
	}
}

int SchedRR2::tick(int cpu, const enum Motivo m) {
	int actual = current_pid(cpu);
	
	if(m == EXIT){
		if(!tareas[cpu].empty()){
			actual = next(cpu);
		}else{
			actual = IDLE_TASK;
		}
	}
	
	if(m == TICK){
		if(actual == IDLE_TASK){
			if(!tareas[cpu].empty()){
				actual = next(cpu);				
			}
		}else{
			cpu_quantum[cpu]++;
			if(cpu_quantum[cpu] == max_quantum[cpu]){
				tareas[cpu].push(actual);
				actual = next(cpu);
			}
		}
	}
	
	if(m == BLOCK) {
		cpu_quantum[cpu]++;
		if(!tareas[cpu].empty()){
			tareasBlocked[cpu].insert(actual);
			actual = next(cpu);
		}
	}
		
	return actual;
}

int SchedRR2::next(int cpu) {
	int prox = tareas[cpu].front();
	tareas[cpu].pop();
	cpu_quantum[cpu] = 0;
	return prox;
}
