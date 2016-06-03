

// RooBarb
#include "XmlConfig.h"
#include "Engine.h"
using namespace jdb;

// STL
#include <iostream>
#include <exception>

// Project
#include "RunByRunQAMaker.h"
#include "RunByRunReportMaker.h"

#include "PicoDstSkimmer.h"
#include "EventPlaneMaker.h"


int main( int argc, char* argv[] ) {

	// RunByRun QA
	TaskFactory::registerTaskRunner<RunByRunQAMaker>( "RunByRunQAMaker" );
	TaskFactory::registerTaskRunner<RunByRunReportMaker>( "RunByRunReportMaker" );


	TaskFactory::registerTaskRunner<PicoDstSkimmer>( "PicoDstSkimmer" );
	TaskFactory::registerTaskRunner<EventPlaneMaker>( "EventPlaneMaker" );

	Engine engine( argc, argv );

	return 0;
}
