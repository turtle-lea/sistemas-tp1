#! usr/bin/python

import sys
import os

#./simusched <lote.tsk> <num_cores> <costo_cs> <costo_mi> <sched> [<params_sched>]

os.system("mkdir experimento_9")

for i in range(20): 
	os.system("./simusched loteLottery.tsk 1 0 0 SchedLottery 4 9 > test")
	nombre_test = "test_"+str(i)
	os.system("cp test experimento_9/"+nombre_test)
	os.system("python graphsched.py test")
	os.system("cp test.png experimento_9/"+nombre_test+".png")
	
	
