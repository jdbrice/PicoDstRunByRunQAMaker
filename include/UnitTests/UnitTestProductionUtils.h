#ifndef UNIT_TEST_PRODUCTION_UTILS_H
#define UNIT_TEST_PRODUCTION_UTILS_H

#include "RunMapFactory.h"
#define UNITTEST_NO_CXX
#include "UnitTest/UnitTest.h"

class UnitTestProductionUtils : public TaskRunner
{
public:
	virtual const char* classname() const { return "UnitTestProductionUtils"; }
	UnitTestProductionUtils() {}
	~UnitTestProductionUtils() {}

	virtual void make(){

		shared_ptr<RunMapFactory> rmf;
		rmf = shared_ptr<RunMapFactory>( new RunMapFactory( "Run15PP200", false ) );

		UnitTest::start( config[ nodePath + ":subject" ] );
		
		UT_TEST( UT_EQ( RunMapFactory::day( 16029023 ), 29 ) , "RunMapFactory::day( 16029023 ) == 29" );
		UT_TEST( UT_EQ( RunMapFactory::run_in_day( 16029023 ), 23 ), "RunMapFactory::run_in_day( 16029023 ) == 23" );
		UT_TEST( UT_TRUE( rmf->isRunBad( 16089002 )  ), "rmf->isRunBad( 16089002 ) == true " );
		UT_TEST( UT_EQ( rmf->indexForRun( 16089002 ), 1431), "indexForRun( 16089002 ) == 1431" );

		INFO( classname(), UnitTest::summary() );

	}
	
};


#endif