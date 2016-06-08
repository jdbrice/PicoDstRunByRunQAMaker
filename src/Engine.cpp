

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
#include "MuonCandidateMaker.h"
#include "ElectronMuonCandidateMaker.h"
#include "CandidateMaker.h"
#include "EventPlaneMaker.h"

#include "CandidateSkimmer.h"


int main( int argc, char* argv[] ) {


	TaskFactory::registerTaskRunner<SharedTreeAnalyzer>( "SharedTreeAnalyzer" );
	// RunByRun QA
	TaskFactory::registerTaskRunner<RunByRunQAMaker>( "RunByRunQAMaker" );
	TaskFactory::registerTaskRunner<RunByRunReportMaker>( "RunByRunReportMaker" );


	TaskFactory::registerTaskRunner<PicoDstSkimmer>( "PicoDstSkimmer" );
	TaskFactory::registerTaskRunner<CandidateMaker>( "CandidateMaker" );
	TaskFactory::registerTaskRunner<MuonCandidateMaker>( "MuonCandidateMaker" );
	TaskFactory::registerTaskRunner<ElectronMuonCandidateMaker>( "ElectronMuonCandidateMaker" );
	

	TaskFactory::registerTaskRunner<EventPlaneMaker>( "EventPlaneMaker" );
	TaskFactory::registerTaskRunner<CandidateSkimmer>( "CandidateSkimmer" );

	Engine engine( argc, argv );

	return 0;
}
