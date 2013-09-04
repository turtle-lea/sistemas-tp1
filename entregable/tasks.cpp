#include "tasks.h"
#include <stdlib.h>
#include <sys/time.h>

using namespace std;

void TaskCPU(int pid, vector<int> params) { // params: n
	uso_CPU(pid, params[0]); // Uso el CPU n milisegundos.
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

     // microsecond has 1 000 000
     // Assuming you did not need quite that accuracy
     // Also do not assume the system clock has that accuracy.
    srand((time.tv_sec * 1000) + (time.tv_usec / 1000));

     // The trouble here is that the seed will repeat every
     // 24 days or so.

     // If you use 100 (rather than 1000) the seed repeats every 248 days.

     // Do not make the MISTAKE of using just the tv_usec
     // This will mean your seed repeats every second.

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
}
