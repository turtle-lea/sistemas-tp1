#| usr/bin/python

with open("zz") as f:
	data = f.read()

data = data.split('\n')

tarea = 0

for i in range(len(data)):
	data[i] = data[i].split()
	if (data[i][0] == "CPU"):
		if (data[i][2] == str(tarea)):
			print data[i], "\n"
		
		
	
