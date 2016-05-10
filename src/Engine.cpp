

#include "XmlConfig.h"
#include "Engine.h"
using namespace jdb;

#include <iostream>
#include <exception>

#include "RunByRunQAMaker.h"

int main( int argc, char* argv[] ) {

	TaskFactory::registerTaskRunner<RunByRunQAMaker>( "RunByRunQAMaker" );
	Engine engine( argc, argv );

	return 0;
}
