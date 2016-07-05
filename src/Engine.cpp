

// RooBarb
#include "XmlConfig.h"
#include "Engine.h"
#include "SharedTreeAnalyzer.h"
using namespace jdb;

// STL
#include <iostream>
#include <exception>

// Project
#include "RunByRunQAMaker.h"
#include "RunByRunReportMaker.h"

#include "PicoDstSkimmer.h"

// Candidate Makers
#include "CandidateMaker.h"
#include "MuonCandidateMaker.h"
#include "ElectronMuonCandidateMaker.h"
#include "ElectronCandidateMaker.h"
#include "MixedEventTreeMaker.h"


#include "EventPlaneMaker.h"
#include "SharedPicoDstSkimmer.h"
#include "CandidateSkimmer.h"
#include "InvariantMassPlotter.h"


int main( int argc, char* argv[] ) {


	TaskFactory::registerTaskRunner<SharedPicoDstSkimmer>( "SharedPicoDstSkimmer" );
	// RunByRun QA
	TaskFactory::registerTaskRunner<RunByRunQAMaker>( "RunByRunQAMaker" );
	TaskFactory::registerTaskRunner<RunByRunReportMaker>( "RunByRunReportMaker" );


	TaskFactory::registerTaskRunner<PicoDstSkimmer>( "PicoDstSkimmer" );
	TaskFactory::registerTaskRunner<CandidateMaker>( "CandidateMaker" );
	TaskFactory::registerTaskRunner<MixedEventTreeMaker>( "MixedEventTreeMaker" );
	TaskFactory::registerTaskRunner<MuonCandidateMaker>( "MuonCandidateMaker" );
	TaskFactory::registerTaskRunner<ElectronMuonCandidateMaker>( "ElectronMuonCandidateMaker" );
	TaskFactory::registerTaskRunner<ElectronCandidateMaker>( "ElectronCandidateMaker" );
	

	TaskFactory::registerTaskRunner<EventPlaneMaker>( "EventPlaneMaker" );
	TaskFactory::registerTaskRunner<CandidateSkimmer>( "CandidateSkimmer" );

	TaskFactory::registerTaskRunner<InvariantMassPlotter>( "InvariantMassPlotter" );

	Engine engine( argc, argv );

	return 0;
}
