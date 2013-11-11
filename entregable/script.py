#! usr/bin/python

import sys
import time
import os

#./simusched <lote.tsk> <num_cores> <costo_cs> <costo_mi> <sched> [<params_sched>]
os.system("rm -rf experimento")
os.system("mkdir experimento")
wtMin = 1000000
taMin = 1000000
fo = open("wtta.out", "a")
sched = str(sys.argv[1]) #scheduler
lote = str(sys.argv[2]) #lote de tareas
qm = int(sys.argv[3]) #quantumLimite
cores = str(sys.argv[4]) #cores totales

for i in range (1,qm):
	j = str(i)
	#print j
	if (sched=="SchedLottery"):
		os.system("./simusched "+lote+" "+cores+" 1 2 "+sched+" "+j+" "+j+" > test")
	if (sched=="SchedRR" or sched=="SchedRR2"):
		string = "./simusched "+lote+" "+cores+" 1 2 "+sched+" "
		for i in range(0,int(cores)):
			string = string+j+" "
		string = string+"> test"
		#print string		
		os.system(string)
	nombre_test = "test_"+j
	os.system("python graphsched.py test")
	#print("Estoy por calcular wy ta")
	os.system("./wtta < test > tmp")
	#print ("Calcule wt y ta")
	tmp = open("tmp",'r').read()
	ta = open("tmp",'r').readlines()
	ta = ta[1].split()
	ta = float(ta[2]) 
	wt = open("tmp",'r').readline()
	wt = wt.split()
	wt = float(wt[2])
	if (taMin > ta):
		taMin = ta
		quantum1 = i
	if (wtMin > wt):
		wtMin = wt
		quantum2 = i
	fo.write("Quantum: "+j+"\n")
	fo.write(tmp)
	os.system("mv test.png experimento/"+nombre_test+".png")
	os.system("mv test experimento/"+nombre_test+".out")
os.system("rm tmp")
fo.write("\n")
fo.write("Quantum con menor waiting time: "+str(quantum2)+"("+str(wtMin)+")\n")
fo.write("Quantum con menor turnaround time: "+str(quantum1)+"("+str(taMin)+")")
os.system("mv wtta.out experimento/")

#Graficador






	
	
