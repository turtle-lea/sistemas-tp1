#! usr/bin/python

import sys
import os

#./simusched <lote.tsk> <num_cores> <costo_cs> <costo_mi> <sched> [<params_sched>]

for i in range(40): 
	nombre_tsk = "../lotes_lottery/lote1.tsk"
	nombre_in = "../lotes_lottery/lote1.in"
	nombre_png = "../lotes_lottery/lote1.in.png"
	nombre_test = "../lotes_lottery/test_"+str(i)+".png"

	os.system("./simusched "+nombre_tsk+" 1 1 0 SchedLottery 2 "+str(3*i)+ " > "+ nombre_in)
	os.system("./simusched "+nombre_tsk+" 1 0 0 SchedLottery 8 "+str(3*i)+ " > "+ nombre_in)
	os.system("python graphsched.py "+nombre_in)
	os.system("mv "+nombre_png+" "+nombre_test)
	os.system("echo Termine "+str(i))
	
	
