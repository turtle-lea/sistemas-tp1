#! usr/bin/python

from matplotlib.pyplot import *
import sys
import time
import os

#./simusched <lote.tsk> <num_cores> <costo_cs> <costo_mi> <sched> [<params_sched>]
os.system("rm -rf experimento")
os.system("mkdir experimento")

#for plotting
ywt=[] #waiting times
yta=[] #ta times
x=[] #quantums

wtMin = 1000000
taMin = 1000000
fo = open("wtta.out", "a") #"wtta.out"
sched = str(sys.argv[1]) #scheduler
lote = str(sys.argv[2]) #lote de tareas
qm = int(sys.argv[3]) #quantumLimite
cores = str(sys.argv[4]) #cores totales

for i in range (1,qm):
	j = str(i)
	print j
	if (sched=="SchedLottery"):
		os.system("./simusched "+lote+" "+cores+" 1 2 "+sched+" "+j+" "+j+" > test")
	if (sched=="SchedRR" or sched=="SchedRR2"):
		string = "./simusched "+lote+" "+cores+" 1 2 "+sched+" "
		for h in range(0,int(cores)):
			string = string+j+" "
		string = string+"> test"		
		os.system(string)
		
	os.system("python graphsched.py test")
	os.system("./wtta < test > tmp")
	
	tmp1 = open("tmp",'r').read()
	tmp = open("tmp",'r').readlines()
	wt = tmp[0].split()
	wt = float(wt[2])	
	ta = tmp[1].split()
	ta = float(ta[2]) 
	
	ywt.append(wt)
	yta.append(ta)
	x.append(i)
	
	if (taMin > ta):
		taMin = ta
		quantum1 = i
	if (wtMin > wt):
		wtMin = wt
		quantum2 = i
		
	fo.write("Quantum: "+j+"\n")
	fo.write(tmp1)
	nombre_test = "test_"+j
	os.system("mv test.png experimento/"+nombre_test+".png")
	os.system("mv test experimento/"+nombre_test+".out")
	
os.system("rm tmp")
fo.write("\n")
fo.write("Quantum con menor waiting time: "+str(quantum2)+"("+str(wtMin)+")\n")
fo.write("Quantum con menor turnaround time: "+str(quantum1)+"("+str(taMin)+")")
os.system("mv wtta.out experimento/")

#Graficador



xlabel("Quantum")
ylabel("Waiting time")
plot(x, ywt, 'ro')
axis([0,qm,0,max(ywt)+2])
savefig("experimento/wt.jpg")

subplot(1,1,1)

xlabel("Quantum")
ylabel("Turnaround time")
plot(x, yta, 'ro')
axis([0,qm,taMin-10,max(yta)+10])
savefig("experimento/ta.jpg")




	
	
