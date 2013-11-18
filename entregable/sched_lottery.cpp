#include <vector>
#include <utility>
#include "sched_lottery.h"
#include "basesched.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

using namespace std;

SchedLottery::SchedLottery(vector<int> argn)
{ // quantum y semilla
	// // Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro (MAX_QUANTUM)
	assert(argn.size() == 3);
	cores = argn[0];
	assert(cores >= 0);
	for(int i=0; i<cores; i++){
		cpu_quantum.push_back(0);
	}
	max_quantum = argn[1];
	semilla = argn[2];
	cantTickets = 0;
}

SchedLottery::~SchedLottery() {

}


void SchedLottery::load(int pid) {
	tareasReady.push_back(make_pair(pid,1));
	cantTickets+=1;
	/** Debug **/
	int n = tareasReady.size();
	int tareas[n];
	int tickets[n];
	/** Debug **/
	for(int i=0; i<n; i++){
		tareas[i] = tareasReady[i].first;	
		tickets[i] = tareasReady[i].second;	
	}
}

void SchedLottery::unblock(int pid) {
	int ticket = searchDestroyBlocked(pid);
	tareasReady.push_back(make_pair(pid,ticket));
	cantTickets+=ticket;
	/** Debug **/
	int n = tareasBlocked.size();
	int tareasB[n];
	int tickets[n];
	for(int i=0; i<n; i++){
		tareasB[i] = tareasBlocked[i].first;		
		tickets[i] = tareasBlocked[i].second;		
	}
	/** Debug **/
}

/* Devuelve la cantidad de tickets con la que deberia empezar la tarea a desbloquear */
int SchedLottery::searchDestroyBlocked(int pid){
	/** Debug **/
	int n = tareasBlocked.size();
	int tareasB[n];
	int tickets[n];
	for(int i=0; i<n; i++){
		tareasB[i] = tareasBlocked[i].first;		
		tickets[i] = tareasBlocked[i].second;		
	}
	/** Debug **/
	int res;
	for(unsigned int i=0;i<tareasBlocked.size();++i){
		if (tareasBlocked[i].first==pid){
			res=tareasBlocked[i].second;
			tareasBlocked.erase(tareasBlocked.begin()+i);
			break;
		}
	}
	return res;
}

void SchedLottery::searchDestroyReady(int pid){
	for(unsigned int i=0;i<tareasReady.size();++i){
		if (tareasReady[i].first==pid){
			tareasReady.erase(tareasReady.begin()+i);
			break;
		}
	}
}

int SchedLottery::tick(int cpu,const enum Motivo m) {
	int actual = current_pid(cpu);
	std::pair<int,int> res; 
	int indice;
	int proximo = actual;
	double frac;
	
	if(m == EXIT){
		cpu_quantum[cpu] = 0;
		if(!tareasReady.empty()){
			res = lottery(); // (pid,i)
			proximo = res.first; indice = res.second;
			cantTickets-=tareasReady[indice].second;
			tareasReady.erase(tareasReady.begin()+indice); //no utilizamos el valor de retorno
		}else{
			proximo = IDLE_TASK;
		}
	}
	
	if(m == TICK){
		if(actual == IDLE_TASK){
			if(!tareasReady.empty()){
				cpu_quantum[cpu] = 0;
				res = lottery(); // (pid,i)
				proximo = res.first; indice = res.second;
				cantTickets-=tareasReady[indice].second;
				tareasReady.erase(tareasReady.begin()+indice); //no utilizamos el valor de retorno
			}
		}else{
			cpu_quantum[cpu]++;	
			if(cpu_quantum[cpu] >= max_quantum){
				tareasReady.push_back(make_pair(proximo,1));
				cantTickets++;
				cpu_quantum[cpu] = 0;
				res = lottery(); // (pid,i)
				proximo = res.first; indice = res.second;
				cantTickets-=tareasReady[indice].second;
				tareasReady.erase(tareasReady.begin()+indice); //no utilizamos el valor de retorno
			}
		}
	}
	
	if(m == BLOCK) {
		cpu_quantum[cpu]++;
		frac = (double)max_quantum/(double)cpu_quantum[cpu];
		frac = ceil(frac);
		tareasBlocked.push_back(make_pair(actual,(int)frac));
					
		if(!tareasReady.empty()){
			cpu_quantum[cpu] = 0;
			res = lottery(); // (pid,i)
			proximo = res.first; indice = res.second;
			cantTickets-=tareasReady[indice].second;
			tareasReady.erase(tareasReady.begin()+indice); //no utilizamos el valor de retorno
		}
	}
	return proximo;
}



std::pair<int,int> SchedLottery::lottery(){
	std::pair<int,int> res;
	int ticketGanador;
	int suma = 0;
	srand(semilla);
	for (unsigned int i=0;i<tareasReady.size();++i){
		suma += tareasReady[i].second;
		if (ticketGanador <= suma){
			res = make_pair(tareasReady[i].first,i);
			break;
		}
	} 

	/** Este if arregla un bug que todavia no terminamos de encontrar **/
	/**
	if (tareasReady.size() == 1){
		res = make_pair(tareasReady[0].first,0);
	}	
	**/	

	return res;
}
