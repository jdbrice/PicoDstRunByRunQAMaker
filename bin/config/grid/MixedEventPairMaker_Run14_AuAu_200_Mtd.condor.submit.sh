######################################################################
# 				MixedEventPairMaker
######################################################################

InitialDir = /home/jdb12/work/muonAna/bin/
Executable = /home/jdb12/work/muonAna/bin/prod
Arguments  = /home/jdb12/work/muonAna/bin/config/Tasks/MixedEventPairMaker.xml --jobIndex=$(Process) --R:active=Run14_AuAu_200_Mtd

GetEnv     = True

Queue 75