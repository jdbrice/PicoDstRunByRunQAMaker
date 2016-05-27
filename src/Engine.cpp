

// RooBarb
#include "XmlConfig.h"
#include "Engine.h"
using namespace jdb;

// STL
#include <iostream>
#include <exception>

// Project
#include "RunByRunQAMaker.h"
#include "PicoDstSkimmer.h"


int main( int argc, char* argv[] ) {

	TaskFactory::registerTaskRunner<RunByRunQAMaker>( "RunByRunQAMaker" );
	TaskFactory::registerTaskRunner<PicoDstSkimmer>( "PicoDstSkimmer" );

	Engine engine( argc, argv );

	return 0;
}
