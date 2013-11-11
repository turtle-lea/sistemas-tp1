#! usr/bin/python

import sys
import os

#./simusched <lote.tsk> <num_cores> <costo_cs> <costo_mi> <sched> [<params_sched>]

os.system("mkdir experimento")

for i in range (1,15):
	j = str(i)
	os.system("./simusched loteLottery.tsk 2 1 2 SchedRR "+j+" "+j+" > test")
	nombre_test = "test_"+j
	fo = open("wtta.out", "wb")
	#os.system("cp test experimento/"+nombre_test)
	os.system("python graphsched.py test")
	os.system("./wtta < test > tmp")
		
	os.system("mv test.png experimento/"+nombre_test+".png")
	os.system("mv test experimento/"+nombre_test+".out")

	
	
