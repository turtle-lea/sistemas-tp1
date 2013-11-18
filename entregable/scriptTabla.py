#! usr/bin/python

import sys
import time
import os
import math

name = str(sys.argv[1])
fo = open(name, "r").readlines()
i=0
for j in range (0,3):
	while 1:
		val = fo[i].split()
		if (val[0]=="Quantum:"):
			if (val[1]=="1"):
				contwt = 0
				contta = 0
			breik = val[1]
			val = fo[i+1].split()
			wt = float(val[2])
			contwt = contwt + wt
			val = fo[i+2].split()
			ta = float(val[2])
			contta = contta + ta
			i=i+3
			if (breik=="19"):
				print "Cores: "+str(j+2)
				print "wt :"+str(contwt/19)
				print "ta: "+str(contta/19)
				contwt=0
				contta=0																																
				i=i+4
				break	
