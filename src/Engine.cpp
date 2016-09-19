

// RooBarb
#include "XmlConfig.h"
#include "TaskEngine.h"
#include "SharedTreeAnalyzer.h"
using namespace jdb;

// STL
#include <iostream>
#include <exception>

// Project
#include "RunByRunQAMaker.h"
#include "RunByRunReportMaker.h"
#include "RunByRunCandidateQAMaker.h"

#include "PicoDstSkimmer.h"

// Candidate Makers
#include "CandidateMaker.h"
#include "EventPlaneCandidateMaker.h"
#include "MuonCandidateMaker.h"
#include "ElectronMuonCandidateMaker.h"
#include "ElectronCandidateMaker.h"
#include "MixedEventTreeMaker.h"
#include "MixedEventMassPlotter.h"


#include "EventPlaneHistoMaker.h"
#include "EventPlaneOffsetFitter.h"
#include "SharedPicoDstSkimmer.h"
#include "CandidateSkimmer.h"
#include "InvariantMassMaker.h"
#include "InvariantMassPlotMaker.h"
#include "BackgroundMaker.h"
#include "FitnessMaker.h"

#include "CommandRunner.h"
#include "CandidateMakerProxy.h"

#include "UnitTestProductionUtils.h"


int main( int argc, char* argv[] ) {


	TaskFactory::registerTaskRunner<SharedPicoDstSkimmer>( "SharedPicoDstSkimmer" );
	// RunByRun QA
	TaskFactory::registerTaskRunner<RunByRunQAMaker>( "RunByRunQAMaker" );
	TaskFactory::registerTaskRunner<RunByRunReportMaker>( "RunByRunReportMaker" );
	TaskFactory::registerTaskRunner<RunByRunCandidateQAMaker>( "RunByRunCandidateQAMaker" );


	TaskFactory::registerTaskRunner<PicoDstSkimmer>( "PicoDstSkimmer" );
	TaskFactory::registerTaskRunner<CandidateMaker>( "CandidateMaker" );
	TaskFactory::registerTaskRunner<MixedEventTreeMaker>( "MixedEventTreeMaker" );
	TaskFactory::registerTaskRunner<MuonCandidateMaker>( "MuonCandidateMaker" );
	TaskFactory::registerTaskRunner<ElectronMuonCandidateMaker>( "ElectronMuonCandidateMaker" );
	TaskFactory::registerTaskRunner<ElectronCandidateMaker>( "ElectronCandidateMaker" );
	
	TaskFactory::registerTaskRunner<EventPlaneCandidateMaker>( "EventPlaneCandidateMaker" );
	TaskFactory::registerTaskRunner<EventPlaneHistoMaker>( "EventPlaneHistoMaker" );
	TaskFactory::registerTaskRunner<EventPlaneOffsetFitter>( "EventPlaneOffsetFitter" );
	TaskFactory::registerTaskRunner<CandidateSkimmer>( "CandidateSkimmer" );

	TaskFactory::registerTaskRunner<InvariantMassMaker>( "InvariantMassMaker" );
	TaskFactory::registerTaskRunner<MixedEventMassPlotter>( "MixedEventMassPlotter" );
	TaskFactory::registerTaskRunner<BackgroundMaker>( "BackgroundMaker" );
	TaskFactory::registerTaskRunner<FitnessMaker>( "FitnessMaker" );

	// Plot Makers
	TaskFactory::registerTaskRunner<InvariantMassPlotMaker>( "InvariantMassPlotMaker" );

	//TaskUtils
	TaskFactory::registerTaskRunner<CommandRunner>( "CommandRunner" );
	TaskFactory::registerTaskRunner<CandidateMakerProxy>( "CandidateMakerProxy" );


	// UnitTests
	TaskFactory::registerTaskRunner<UnitTestProductionUtils>( "UnitTestProductionUtils" );

	TaskEngine engine( argc, argv );

	return 0;
}
