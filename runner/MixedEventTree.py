
import random
import subprocess
import os
random.seed(0)
max_event_hash = 320
# max_event_hash = 0

condor_submit = "/home/jdb12/work/muonAna/bin/config/AuAuRun14/grid/MixedMuonTreeMaker.condor"

env = dict( os.environ )
r = range( 0, max_event_hash + 1)
random.shuffle( r )
for eh in r :
	env[ "ANA_EVENT_HASH" ] = str( eh )
	print "Event HASH =", eh
	subprocess.call( ["/opt/condor/bin/condor_submit", condor_submit], env=env )
	# subprocess.call( ["/opt/condor/bin/condor_rm", str(eh) ] )