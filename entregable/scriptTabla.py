#! usr/bin/python

from matplotlib.pyplot import *
import sys
import time
import os
import math
import matplotlib.pyplot as plt

name = str(sys.argv[1])
fo = open(name, "r").readlines()

for j in range (0,3):
	for i in range(0,20):
		val = fo[i].split()
		if (val[0]=="Quantum: 1"):
			contwt = 0
			contta = 0
			val = fo[i+1].split()
			wt = float(val[2])
			contwt = contwt + wt
			val = fo[i+2].split()
			ta = float(val[2])
			contta = contta + ta
		if (val[0]=="Quantum: 19"):
			val = fo[i+1].split()
			wt = float(val[2])
			contwt = contwt + wt
			print contwt/19
			val = fo[i+2].split()
			ta = float(val[2])
			contta = contta + ta
			print contta/19			
		if (val[0]=="Quantum:"):
			
			contwt = contwt/19
			print contwt
	
	wt = float(wt[2])

for k in range(2,int(cores)+1):
	#print k
	for i in range (1,qm):
		j = str(i)
		print j
		for s in range (0,20):
			if (sched=="SchedLottery"):
				os.system("./simusched "+lote+" "+str(k)+" 1 2 "+sched+" "+j+" "+j+" > test")
			if (sched=="SchedRR" or sched=="SchedRR2"):
				string = "./simusched "+lote+" "+str(k)+" 1 2 "+sched+" "
				for h in range(0,k):
					string = string+j+" "
				string = string+"> test"	
				os.system(string)
			#os.system("python graphsched.py test")
			os.system("./wtta < test > tmp")
			
			tmp1 = open("tmp",'r').read()
			tmp = open("tmp",'r').readlines()
			wt = tmp[0].split()
			wt = float(wt[2])
			ta = tmp[1].split()
			ta = float(ta[2])
			wtProm.append(wt) 
			taProm.append(ta) 
			
		#os.system("python graphsched.py test")		
		wt = sum(wtProm) / float(len(wtProm))
		ta = sum(taProm) / float(len(taProm))
		desvioWt = [(z-wt)*(z-wt) for z in wtProm]
		desvioWt = math.sqrt(sum(desvioWt) / (float(len(desvioWt))-1))
		desviosWt.append(desvioWt)
		desvioTa = [(b-ta)*(b-ta) for b in taProm]
		desvioTa = math.sqrt(sum(desvioTa) / (float(len(desvioTa))-1))
		desviosTa.append(desvioTa)

		wtProm=[]
		taProm=[]	
		
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
		fo.write("Waiting time: "+str(wt)+"\n")
		fo.write("Turnaround time: "+str(ta)+"\n")
		#nombre_test = "test_"+j
		#os.system("mv test.png experimento/"+nombre_test+".png")
		#os.system("mv test experimento/"+nombre_test+".out")
		#os.system("rm test")
		
	fo.write("\n")
	fo.write("Quantum con menor waiting time: "+str(quantum2)+"("+str(wtMin)+")\n")
	fo.write("Quantum con menor turnaround time: "+str(quantum1)+"("+str(taMin)+")")
	#os.system("mv wtta.out experimento/")

	#Graficador

	plt.figure(k)
	plt.xlabel("Quantum")
	plt.ylabel("Waiting time")
	plt.errorbar(x, ywt, yerr=desviosWt, fmt='.', color='black')
	plt.axis([0,qm,0,max(ywt)+2])
	savefig("experimento/cores_"+str(k)+"_wt.jpg")

	plt.figure(k+1)
	plt.xlabel("Quantum")
	plt.ylabel("Turnaround time")
	plt.errorbar(x, yta, yerr=desviosTa, fmt='.', color='black')
	plt.axis([0,qm,taMin-60,max(yta)+60])
	savefig("experimento/cores_"+str(k)+"_ta.jpg")
	
	wtMin = 1000000
	taMin = 1000000	
	ywt=[] #waiting times
	yta=[] #ta times
	x=[] #quantums
	desviosWt=[]
	desviosTa=[]
	
os.system("python graphsched.py test")		
os.system("rm tmp")
#os.system("rm test")	
os.system("mv wtta.out experimento/")
