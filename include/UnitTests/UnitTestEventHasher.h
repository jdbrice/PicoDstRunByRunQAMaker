#ifndef UNIT_TEST_EVENT_HASHER_H
#define UNIT_TEST_EVENT_HASHER_H


#include "EventHasher.h"
#include "TaskRunner.h"
#include "CandidateEvent.h"

#include "UnitTest/UnitTest.h"

class UnitTestEventHasher : public TaskRunner
{
public:
	virtual const char * classname() const { return "UnitTestEventHasher"; }
	UnitTestEventHasher() {}
	~UnitTestEventHasher() {}

	virtual void make(){

		UnitTest::start( config[ nodePath + ":subject" ] );
		
		EventHasher ehash;
		// TODO: Import a different TEST set of Mixed Event Bins so that the tests do not depend on the Analysis Mixed event bins
		ehash.load( config, nodePath + ".MixedEventBins" );

		CandidateEvent event;
		event.mPrimaryVertex_mX1 = 0;
		event.mPrimaryVertex_mX2 = 0;
		event.mPrimaryVertex_mX3 = 25;
		event.mGRefMult = 50;
		event.mRunIndex = 630;

		int h = ehash.hash( &event );
		UT_TEST( UT_EQ( h, 186 ), "EventHash = 186" );
		INFO( classname(), "unhash: " );
		
		// TODO : retrieve and test the un-hashing
		ehash.unhash( h );

		ehash.unhash( 61 );


		INFO( classname(), UnitTest::summary() );


	}
	
};


#endif