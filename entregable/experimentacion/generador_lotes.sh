#!/bin/bash

rm -f loteCelular.tsk
rm -f lotePC.tsk
rm -f loteCalc.tsk
rm -f loteRTC.tsk

touch loteCelular.tsk
touch lotePC.tsk
touch loteCalc.tsk
touch loteRTC.tsk

#celular
for i in `seq 1 40`;
do
	echo "TaskConsola 20 1 15" >> loteCelular.tsk
done

#pc
for i in `seq 1 20`;
do
	echo "TaskConsola 40 1 30" >> lotePC.tsk
	echo "TaskCPU 50" >> lotePC.tsk
	echo "TaskBatch 50 $i" >> lotePC.tsk
done

#calculo
for i in `seq 1 50`
do
	if [ $i -lt "40" ];
	then
		echo "TaskCPU 75" >> loteCalc.tsk
	else
		echo "TaskCPU 200" >> loteCalc.tsk

	fi
done


#RTC
for i in `seq 1 100`
do
	echo "TaskBatch 100 40" >> loteRTC.tsk
done
