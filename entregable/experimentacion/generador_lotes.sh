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
echo "*40 TaskConsola 20 1 15" >> loteCelular.tsk


#pc
echo "*20 TaskConsola 40 1 30" >> lotePC.tsk
echo "*20 TaskCPU 50" >> lotePC.tsk
echo "*20 TaskBatch 50 $i" >> lotePC.tsk


#calculo
echo "*20 TaskCPU 75" >> loteCalc.tsk
echo "*20 TaskCPU 125" >> loteCalc.tsk
echo "*10 TaskCPU 200" >> loteCalc.tsk


#RTC
echo "*50 TaskBatch 100 40" >> loteRTC.tsk
