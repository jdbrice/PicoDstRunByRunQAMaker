#include "PicoDstSkimmer.h"
#include "SharedPicoDstSkimmer.h"

//Data Adapters
#include "PicoDstRun14AuAu200.h"
#include "PicoDstRun15PP200.h"

void PicoDstSkimmer::initialize(){

	// create the picodst interface
	if ( false == sharedTree ){
		INFO( classname(), "Using private PicoDst Interface" );
		picoDstAdapter = config.getString( nodePath + ".input.dst:adapter", "PicoDstRun14AuAu200" );
		INFO( classname(), "PicoDst Adapter : " << picoDstAdapter );
		if ( "PicoDstRun15PP200" == picoDstAdapter )
			pico = shared_ptr<IPicoDst>( new PicoDstRun15PP200( chain ) );
		else 
			pico = shared_ptr<IPicoDst>( new PicoDstRun14AuAu200( chain ) );
	} else {
		picoDstAdapter="";
		INFO( classname(), "Using shared PicoDst Interface" );
		pico = SharedPicoDstSkimmer::getPicoDst();
		assert( pico );
	}

	EventBranches = config.getStringVector( nodePath + ".EventBranches" );//, (vector<string>){ "Event" } );
	TrackBranches = config.getStringVector( nodePath + ".TrackBranches" );//, (vector<string>){"Tracks", "BTofPidTraits", "EmcPidTraits", "MtdPidTraits"} ); 

	vector<string> triggers = config.getStringVector( nodePath + ":triggers" );
	tf.setTriggers( triggers );

	// eventCuts
	eventCuts.init( config, nodePath + ".EventCuts" );
	eventCuts.setDefault( "zVertex", -100, 100 );
	eventCuts.setDefault( "zVertexDelta", 0, 3 );

	INFO( classname(), "" );
	INFO( classname(), "############### Event Cuts ###################"  );
	eventCuts.report();
	INFO( classname(), "" );

}

bool PicoDstSkimmer::keepEvent(){
	DEBUG( classname(), "keepEvent" );
	bool passAllCuts = true;

	double zVertex = pico->vz();
	double zVpd = pico->vzVpd();

	passEventCut( "All", passAllCuts );

	// Trigger selection
	if ( !tf.anyTrigger( pico ) ){
		passAllCuts = false;
	} else {
		passEventCut( "trigger", passAllCuts );
	}

	// zVertex Selection
	if ( !eventCuts[ "zVertex" ]->inInclusiveRange( zVertex ) ){
		passAllCuts = false;
	} else {
		passEventCut( "zVertex", passAllCuts );
	}

	// zVertexDelta
	double zDelta = zVertex - zVpd;
	if ( zDelta > eventCuts[ "zVertexDelta" ]->max ){
		passAllCuts = false;
	} else {
		passEventCut( "zVertexDelta", passAllCuts );
	}

	if ( passAllCuts ){
		book->fill("zVertex", zVertex);
		book->fill( "zVpd", zVpd );
		book->fill( "zVertexDelta", zDelta );
	}

	return passAllCuts;
}

void PicoDstSkimmer::analyzeEvent(){
	// cout << "Run ID " << pico->Event_mRunId[0] << endl;
}


void PicoDstSkimmer::eventLoop() {

	INFO( classname(), "EventLoop" );

	TaskTimer t;
	t.start();

	int totalNumberOfEvents = -1;
	bool showProgress = config.getBool( nodePath + ".EventLoop:progress", false );
	if ( showProgress ){
		totalNumberOfEvents = chain->GetEntries();
	}
	nEventsToProcess = config.getInt( nodePath + ".input.dst:nEvents", totalNumberOfEvents );

	// if neg then process all
	if ( nEventsToProcess < 0 || nEventsToProcess > totalNumberOfEvents  )
		nEventsToProcess = totalNumberOfEvents;
	
	if ( showProgress ){
		INFO( classname(), "Loaded: " << nEventsToProcess << " events " );
	}

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
			INFO( classname(), "Ending event loop on iEvent = " << iEvent );
			break;
		}

		if ( showProgress ){
			tp.showProgress( iEvent );
		}

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