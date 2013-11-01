#! usr/bin/python

import sys
import os

#./simusched <lote.tsk> <num_cores> <costo_cs> <costo_mi> <sched> [<params_sched>]

os.system("mkdir experimento")
 
os.system("./simusched loteLottery.tsk 2 1 2 SchedLottery 5 2 > test")
nombre_test = "test"
#os.system("cp test experimento_8/"+nombre_test)
os.system("python graphsched.py test")
os.system("mv test experimento/")
os.system("mv test.png experimento/"+nombre_test+".png")
#os.system("echo Termine "+str(i))
	
	
