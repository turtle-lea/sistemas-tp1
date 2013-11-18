import sys 
import os

#./simusched <lote.tsk> <num_cores> <costo_cs> <costo_mi> <sched> [<params_sched>]

for i in range(40): 
        nombre_tsk = "../lotes_lottery/lote1.tsk"
        nombre_in = "../lotes_lottery/datos.in"
        nombre_png = "../lotes_lottery/datos.in.png"
        nombre_test = "../lotes_lottery/datos_"+str(i)+".png"

        os.system("./simusched "+nombre_tsk+" 1 0 0 SchedLottery 5 "+str(3*i)+ " > "+ nombre_in)
        #s.system("cp test experimento_8/"+nombre_test)
        os.system("./wtta2 < "+nombre_in)
	os.system("echo "+str(i)) 
	os.system("echo '\n'") 
        #os.system("mv "+nombre_png+" "+nombre_test)
        #s.system("echo Termine "+str(i))
