

import os
import subprocess
import random
import time
import ROOT
import math

from swarmer.DimuonBinMaker import DimuonBinMaker

random.seed(None)
task_submit  = "/home/jdb12/work/muonAna/bin/config/Run15PP/grid/SingleInvMassMaker.condor"
task_fitness = "/home/jdb12/work/muonAna/bin/config/Run15PP/grid/FitnessMaker.condor"
fit_dir = "/data/star2/jdb12/Run15PP200/"
combine_cmd = "hadd -f " + fit_dir + "fit.root " + fit_dir + "fitness*.root"

Niterations = 500
iteration = 1
Nplc = 10
iTask = iteration * Nplc
iFitness = iteration * Nplc

# plcs = []

def getNumJobs() :
	p = subprocess.Popen( [ "condor_q", "jdb12", "-totals" ], stdout=subprocess.PIPE, stderr=subprocess.PIPE, )

	out, err = p.communicate()
	# print out
	lines = out.split( "\n" )
	line = lines[ -2 ]
	# print line[ 0:line.index( "job" ) ]
	return int( line[ 0:line.index( "job" ) ] )


def defaultENV( envIn = None ) :
	env = envIn 
	if None == env :
		env = dict()
	env[ "TRACK_CUT_nHitsRatio_min" ]   = "0.52"
	env[ "TRACK_CUT_nHitsDedx_min" ]    = "10"
	env[ "TRACK_CUT_nHitsFit_min" ]     = "10"
	env[ "TRACK_CUT_nSigmaPion_min" ]   = "-1.5"
	env[ "TRACK_CUT_nSigmaPion_max" ]   = "2.5"
	env[ "TRACK_CUT_gDCA_max" ]         = "10"
	env[ "TRACK_CUT_matchFlagMtd_min" ] = "1"
	env[ "TRACK_CUT_matchFlagMtd_max" ] = "10"
	env[ "TRACK_CUT_dzMtd_min" ]        = "-200"
	env[ "TRACK_CUT_dzMtd_max" ]        = "200"
	env[ "TRACK_CUT_dyMtd_min" ]        = "-200"
	env[ "TRACK_CUT_dyMtd_max" ]        = "200"
	env[ "TRACK_CUT_drMtd_min" ]        = "0"
	env[ "TRACK_CUT_drMtd_max" ]        = "30"
	env[ "TRACK_CUT_dTofMtd_min" ]      = "-0.4"
	env[ "TRACK_CUT_dTofMtd_max" ]      = "0.4"
	return env

def randENV( _env ) :
	_env[ "TRACK_CUT_nHitsDedx_min" ] = str( random.randrange( 10, 40, 1 ) )
	_env[ "TRACK_CUT_nSigmaPion_min" ] = str( random.uniform( -8, 0 ) )
	_env[ "TRACK_CUT_nSigmaPion_max" ] = str( random.uniform( 0, 8 ) )
	dz = random.uniform( 1, 80 )
	dy = random.uniform( 1, 40 )
	dr = math.sqrt( dy*dy + dz*dz )
	_env[ "TRACK_CUT_dzMtd_min" ] = str( -1 * math.fabs( dz ) )
	_env[ "TRACK_CUT_dzMtd_max" ] = str( math.fabs( dz ) )
	_env[ "TRACK_CUT_dyMtd_min" ] = str( -1 * math.fabs( dy ) )
	_env[ "TRACK_CUT_dyMtd_max" ] = str( math.fabs( dy ) )
	_env[ "TRACK_CUT_drMtd_max" ] = str( dr )

	_env[ "TRACK_CUT_nHitsRatio_min" ] = str( random.uniform( 0.52, 0.9 ) )
	_env[ "TRACK_CUT_gDCA_max" ] = str( random.uniform( 1, 20 ) )
	_env[ "TRACK_CUT_dTofMtd_min" ] = str( random.uniform( -2.0, 0.0 ) )
	_env[ "TRACK_CUT_dTofMtd_max" ] = str( random.uniform( 0.0, 2.0 ) )  
	return _env


def submitTask( _env ) :
	global iTask
	variant = "variant_" + str(iTask)
	_env[ "ANA_VARIANT" ] = variant
	subprocess.call( [ "/opt/condor/bin/condor_submit", task_submit ], env=_env )
	iTask = iTask + 1

def submitFitness( _env ) :
	global iFitness
	variant = "variant_" + str(iFitness)
	_env[ "ANA_VARIANT" ] = variant
	_env[ "ANA_ITERATION" ] = str(iFitness)
	subprocess.call( [ "/opt/condor/bin/condor_submit", task_fitness ], env=_env )
	iFitness = iFitness + 1


def combine_results() :
	# subprocess.call( combine_cmd.split(), env=dict(os.environ), shell=True )
	os.system( combine_cmd )

def find_current_best_set( data ) :

	total = data.GetEntries()
	max_score = -999999
	entryNum = -1
	for iEntry in range( 0, total ) :
		data.GetEntry( iEntry )
		if data.score_jpsi > max_score :
			max_score = data.score_jpsi
			entryNum = iEntry
	print "Max of ", max_score, "found in", entryNum
	return entryNum

def find_current_max() :
	f = ROOT.TFile( fit_dir + "fit.root" )
	ftc = f.Get( "trackCuts" )
	ff = f.Get( "fitness" )
	ff.AddFriend( ftc )

	max_jpsi = ff.GetMaximum( "score_jpsi" )
	
	find_current_best_set( ff )
	f.Close()
	return max_jpsi



def submit_iteration() :
	env = defaultENV( dict(os.environ) )
	for i in range( 0, Nplc ) :
		# env = randENV( env )
		env = defaultENV( env )
		print env[ "TRACK_CUT_nHitsDedx_min" ]
		submitTask( env )

	# wait for jobs to finish
	while( getNumJobs() > 0 ) :
		time.sleep( 15 )

	# for i in range( 0, Nplc ) :
		# submitFitness( dict( os.environ ) )

	


for i in range( 0, Niterations ) :
	submit_iteration()
	print "Submitted it", i, "of", Niterations

# combine_results()
# find_current_max()