

import subprocess


def getNumJobs() :
	p = subprocess.Popen( [ "condor_q", "jdb12", "-totals" ], stdout=subprocess.PIPE, stderr=subprocess.PIPE, )

	out, err = p.communicate()
	# print out
	lines = out.split( "\n" )
	line = lines[ -2 ]
	print line[ 0:line.index( "job" ) ]
	return int( line[ 0:line.index( "job" ) ] )

