#include "PicoDstSkimmer.h"
#include "SharedPicoDstSkimmer.h"

//Data Adapters
#include "PicoDstRun14AuAu200.h"
#include "PicoDstRun15PP200.h"

void PicoDstSkimmer::initialize(){

	// create the picodst interface
	if ( false == sharedTree ){
		INFO( classname(), "Using private PicoDst Interface" );
		picoDstAdapter = config.getString( nodePath + ".input.dst:adapter", "Run14_AuAu_200_Mtd" );
		INFO( classname(), "PicoDst Adapter : " << picoDstAdapter );
		if ( "Run15_PP_200_Mtd" == picoDstAdapter )
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
	eventCuts.setDefault( "EventPlane_nTracks", 1, 10000000 );

	INFO( classname(), "" );
	INFO( classname(), "############### Event Cuts ###################"  );
	eventCuts.report();
	INFO( classname(), "" );

	if ( config.exists( nodePath + ".EventPlaneCorr" ) ){
		INFO( classname(), "" );
		INFO( classname(), "############### EventPlaneCorr ###################"  );
		epc.load( config, nodePath + ".EventPlaneCorr" );
	} else {
		WARN( classname(), "No EventPlane Corrections found" );
	}

	config.toXmlFile( "out_config.xml" );

	if ( "Run15_PP_200_Mtd" == picoDstAdapter ){
		rmf = shared_ptr<RunMapFactory>( new RunMapFactory( "Run15PP200", false ) );
	}
	else {
		WARN( classname(), "NO BAD RUN REJECTION FOR AUAU YET" );
		rmf = shared_ptr<RunMapFactory>( new RunMapFactory( ) );
	}

	INFO( classname(), "Making QA :" );
	INFO( classname(), "Event : " << bts( config.getBool( nodePath +".MakeQA:event", false ) ) );
	INFO( classname(), "Track : " << bts( config.getBool( nodePath +".MakeQA:track", false ) ) );

}

bool PicoDstSkimmer::keepEvent(){
	DEBUG( classname(), "keepEvent" );
	bool passAllCuts = true;

	bool makeQA = config.getBool( nodePath +".MakeQA:event", false );

	double zVertex = pico->vz();
	double zVpd = pico->vzVpd();
	// zVertexDelta
	double zDelta = zVertex - zVpd;

	if (makeQA) {
		passEventCut( "All", passAllCuts );
		tf.fillTriggerQA( pico, "all_triggers", "eventQA", book );
		book->fill( "pre_zVertex"         , zVertex);
		book->fill( "pre_zVpd"            , zVpd );
		book->fill( "pre_zVertexDelta"    , zDelta );
		book->fill( "pre_zVertex_vs_zVPD" , zVpd      , zVertex );
		// book->fill( "pre_zVertexDelta_vs_zVertex", zVertex, zDelta );
		// book->fill( "pre_zVertexDelta_vs_zVPD", zVpd, zDelta );

	}
	
	// Trigger selection
	if ( !tf.anyTrigger( pico ) ){
		passAllCuts = false;
	} else if ( makeQA ) {
		passEventCut( "trigger", passAllCuts );
	}

	if ( rmf->isRunBad( pico->Event_mRunId[0] ) ){
		DEBUG( classname(), pico->Event_mRunId[0]  << " is BAD" );
		passAllCuts = false;
	} else if( makeQA ){
		passEventCut( "bad run", passAllCuts );
	}

	// zVertex Selection
	if ( !eventCuts[ "zVertex" ]->inInclusiveRange( zVertex ) ){
		passAllCuts = false;
	} else if ( makeQA ) {
		passEventCut( "zVertex", passAllCuts );
	}

	
	if ( abs(zDelta) > eventCuts[ "zVertexDelta" ]->max ){
		passAllCuts = false;
	} else if ( makeQA ) {
		passEventCut( "zVertexDelta", passAllCuts );
	}

	double nTracks = pico->ntrk();
	if ( "Run15_PP_200_Mtd" != picoDstAdapter && nTracks < eventCuts[ "EventPlane_nTracks" ]->min ){
		passAllCuts = false;
	} else if ( makeQA ) {
		passEventCut( "nEvtPlTrks", passAllCuts );
	}


	if ( passAllCuts && makeQA ){
		tf.fillTriggerQA( pico, "pass_triggers", "eventQA", book );
		book->fill("zVertex", zVertex);
		book->fill( "zVpd", zVpd );
		book->fill( "zVertexDelta", zDelta );
		book->fill( "zVertex_vs_zVPD", zVpd, zVertex );
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