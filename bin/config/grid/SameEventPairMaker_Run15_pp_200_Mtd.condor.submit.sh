######################################################################
# 				SameEventPairMaker
######################################################################

# Requirements = ( Machine != "star3.local" && Machine != "star4.local" )

InitialDir = /home/jdb12/work/muonAna/bin/
Executable = /home/jdb12/work/muonAna/bin/prod
Arguments  = /home/jdb12/work/muonAna/bin/config/Tasks/SameEventPairMaker.xml --jobIndex=$(Process) --R:active=Run15_PP_200_Mtd --mod=_LOOSELR_MF1

# Log        = /home/jdb12/work/muonAna/bin/muon_candidates_$(Process).log
# Output     = /home/jdb12/work/muonAna/bin/same_Event_pairs_$(Process).out
# Error      = /home/jdb12/work/muonAna/bin/muon_candidates_$(Process).error

GetEnv     = True

Queue 55