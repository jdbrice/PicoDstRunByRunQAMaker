######################################################################
# 				SameEventHistoMaker
######################################################################


InitialDir = /home/jdb12/work/muonAna/bin/
Executable = /home/jdb12/work/muonAna/bin/prod
Arguments  = /home/jdb12/work/muonAna/bin/config/Tasks/MixedEventInvMassHistoMaker.xml --jobIndex=$(Process) --R:active=Run15_PP_200_Mtd --IMHM.input.dst:splitBy=1 --mod=_Nominal --l1=-10.4

GetEnv     = True

Queue 20