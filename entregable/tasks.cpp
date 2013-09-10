#include "tasks.h"
#include <stdlib.h>
#include <sys/time.h>

using namespace std;

void TaskCPU(int pid, vector<int> params) { // params: n
	uso_CPU(pid, params[0]); // Uso el CPU n milisegundos.
}

void TaskBatch(int pid, vector<int> params) { // params: total_cpu, cant_bloqueos
	int total_cpu = params[0];
	int cant_bloqueos = params[1];		///total_cpu >= cant_bloqueos
		
	total_cpu = total_cpu - cant_bloqueos - 1; //le quito a total_cpu los tiempos de llamada a funcion bloqueante y return.
	/* luego puedo utilizar total_cpu para distribuir mis llamadas bloqueantes */
	/// si total_cpu = 0 hay que ejecutar las bloqueantes al hilo
	
	struct timeval time; 
    gettimeofday(&time,NULL);
    srand((time.tv_sec * 1000) + (time.tv_usec / 1000));
    int r;
    int bmax = 20;
    int bmin = 1;
    
	while(total_cpu > 0 && cant_bloqueos > 0){
		r = bmin + (rand()%(bmax-bmin+1));
		if (r == 5 || r == 8 ||r == 12 ){
			uso_IO(pid,1);
			cant_bloqueos--;
			//bmax = 10;
		}else{
			uso_CPU(pid,1);
			total_cpu--;
			//bmax--;
		}
	} // total_cpu == 0 || cant_bloqueos == 0
	if(total_cpu > 0){
		uso_CPU(pid,total_cpu);
	}
	if(cant_bloqueos > 0){
		for(int i = 0; i < cant_bloqueos; i++) uso_IO(pid,1);
	}
}

void TaskIO(int pid, vector<int> params) { // params: ms_pid, ms_io,
	uso_CPU(pid, params[0]); // Uso el CPU ms_pid milisegundos.
	uso_IO(pid, params[1]); // Uso IO ms_io milisegundos.
}

void TaskAlterno(int pid, vector<int> params) { // params: ms_pid, ms_io, ms_pid, ...
	for(int i = 0; i < (int)params.size(); i++) {
		if (i % 2 == 0) uso_CPU(pid, params[i]);
		else uso_IO(pid, params[i]);
	}
}

void TaskConsola(int pid, vector<int> params) { //params: n, bmin, bmax

    struct timeval time; 
    gettimeofday(&time,NULL);
    srand((time.tv_sec * 1000) + (time.tv_usec / 1000));

	int n = params[0];
	int bmin = params[1];
	int bmax = params[2];
	int r;
	for(int i = 0; i < n; i++){
		r = bmin + (rand()%(bmax-bmin+1));
		uso_IO(pid, r);
	}
}

void tasks_init(void) {
	/* Todos los tipos de tareas se deben registrar acá para poder ser usadas.
	 * El segundo parámetro indica la cantidad de parámetros que recibe la tarea
	 * como un vector de enteros, o -1 para una cantidad de parámetros variable. */
	register_task(TaskCPU, 1);
	register_task(TaskIO, 2);
	register_task(TaskAlterno, -1);
	register_task(TaskConsola, 3);
	register_task(TaskBatch, 2);
}
