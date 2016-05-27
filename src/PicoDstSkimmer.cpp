#include "PicoDstSkimmer.h"




bool PicoDstSkimmer::keepEvent(){

	// if ( pico->Tracks_ > 10 )
	// 	return true;

	return true;
}

void PicoDstSkimmer::analyzeEvent(){
	// cout << "Run ID " << pico->Event_mRunId[0] << endl;
}


void PicoDstSkimmer::eventLoop() {

	DEBUG( classname(), "EventLoop" );

	TaskTimer t;
	t.start();

	TaskProgress tp( "Event Loop", nEventsToProcess );
	
	bool doTrackLoop = config.getBool( nodePath + ":track", false );

	// loop over all events 
	Long64_t iEvent = 0;

	chain->SetCacheSize( config.getInt( nodePath + ".TTreeCache:cacheSize", 32000000 ) ); // default = 10 MB
	chain->SetCacheLearnEntries( 100 );

	while (true){ // what could go wrong 
		
		Long64_t iTreeEntry = chain->LoadTree( iEvent );
		Long64_t read = readBranchList( EventBranches, iTreeEntry );

		if ( read <= 0 || (nEventsToProcess >= 0 && iEvent >= nEventsToProcess) ){ // break if we read past end or hit limit
			break;
		}

		if ( showProgress )
			tp.showProgress( iEvent );

		analyzeEventBeforeCuts();

		if ( !keepEvent() ){
			analyzeRejectedEvent();
			iEvent++;
			continue;
		}

		analyzeEvent();

		if ( doTrackLoop ){
			// read the track branches
			read = readBranchList( TrackBranches, iTreeEntry );
			trackLoop();
		}


		iEvent++;
	} // Event Loop
	cout << "iEvent = " << iEvent << endl;
	if ( false == showProgress ){
		INFO( classname(), "Event Loop Completed in " << t.elapsed() );
	}
}


void PicoDstSkimmer::trackLoop(){


	// cout << "There are " << pico->Tracks_ << " Tracks " <<endl;
	if ( pico->BTofPidTraits_ >= 1 ) {

		// cout << "yLocal = " << pico->BTofPidTraits_mBTofYLocal[ 0 ] << endl;
	}

}


void PicoDstSkimmer::analyzeTrack( int iTrack ){

}