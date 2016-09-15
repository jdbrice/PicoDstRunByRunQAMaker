#ifndef CANDIDATE_MAKER_H
#define CANDIDATE_MAKER_H

#include "XmlRange.h"

//Project
#include "PicoDstSkimmer.h"

#include "CandidateTreeMaker.h"
#include "EventHasher.h"
#include "RunMapFactory.h"

#include "StRefMultCorr.h"
#include "CentralityMaker.h"


//ROOT
#include "TClonesArray.h"
#include "TVector3.h"
#include "TMath.h"

class CandidateMaker : public PicoDstSkimmer
{
public:
	virtual const char *classname() const { return "CandidateMaker"; }
	CandidateMaker() {}
	~CandidateMaker() {}

	virtual void initialize(){
		INFO( classname(), "" );
		PicoDstSkimmer::initialize();

		book->cd();
		// createTree();

		if ( config.getBool( nodePath + ":rmc", true ) ){
			INFO( classname(), "Setting up RMC" );
			rmc = CentralityMaker::instance()->getgRefMultCorr();
		} else {
			INFO( classname(), "NOT setting up RMC" );
		}


		if ( config.exists( nodePath + ".MixedEventBins" ) ){
			INFO( classname(), "Creating Event Hash" );
			eht.load( config, nodePath + ".MixedEventBins" );
			eventHash = config.getInt( nodePath + ".EventHash", -1 );
		} else {
			WARN( classname(), "Could not find MixedEventBins" );
			eventHash = -1;
		}
		eventHashRange.loadConfig( config, nodePath + ".EventHash" );

		if ( "PicoDstRun15PP200" == picoDstAdapter ){
			calcEventPlane = false;
			rmf = shared_ptr<RunMapFactory>( new RunMapFactory( "Run15PP200", false ) );
		}
		else {
			WARN( classname(), "NO BAD RUN REJECTION FOR AUAU YET" );
			rmf = shared_ptr<RunMapFactory>( new RunMapFactory( ) );
		}

		useRefMultCorr = config.getBool( nodePath + ":rmc", true );

		eventSplit = config.getBool( nodePath + ".EventHash:split" );
		INFO( classname(), "Splitting by Event Hash : " << bts( eventSplit ) );
		makeForest();
	}


protected:
	StRefMultCorr * rmc = nullptr;
	EventHasher eht;
	XmlRange eventHashRange;
	int eventHash;
	bool eventSplit = false;
	shared_ptr<RunMapFactory> rmf;
	bool useRefMultCorr = false;
	bool calcEventPlane = true;
	map< int, shared_ptr<CandidateTreeMaker> > forest;
	shared_ptr<CandidateTreeMaker> candidateTree;

	bool isMuon = false;
	bool isElectron = false;

	virtual void makeForest(  ){
		if ( eventSplit ){
			for ( int i = eventHashRange.min; i < eventHashRange.max; i++ ){
				INFO( classname(), "Creating Tree for EventHash == " << i );
				forest[ i ] = shared_ptr<CandidateTreeMaker>( new CandidateTreeMaker(  ) );
				config.set( nodePath + ".EventHash", ts(i) );
				forest[ i ]->createFile( config.getXString( nodePath + ".EventHash:url" ) );
				forest[ i ]->setPicoDst( pico );
				makeTree( i );
			}
		}
	}

	virtual void makeTree( int iTree ) {
		forest[ iTree ]->createTree( );
	}

	virtual bool keepEvent(){

		bool skeep = PicoDstSkimmer::keepEvent();
		if ( false == skeep )
			return false;
		
		/*********** Initialize the RefMultCorr *************/
		if ( useRefMultCorr ){
			rmc->init( pico->Event_mRunId[0] );
			rmc->initEvent( 
				pico->Event_mGRefMult[0], 
				pico->Event_mPrimaryVertex_mX3[0], 
				pico->Event_mZDCx[0]
			);
		}

		/*********** Initialize the RefMultCorr *************/
		if ( rmf->isRunBad( pico->Event_mRunId[0] ) ){
			INFO( classname(), pico->Event_mRunId[0]  << " is BAD" );
			return false;
		}

		

		return true;
	}

	virtual void analyzeEvent(){

		CandidateEvent * cEvent = new CandidateEvent();
		// TODO : add back switched for RMC and EventPlane
		CandidateTreeMaker::fillCandidateEvent( pico, cEvent, rmf->indexForRun( pico->Event_mRunId[0] ), 0, 1.0, 0.0 );

		// Calculate the event hash
		int evtHash = eht.hash( cEvent );
		candidateTree = nullptr;
		if ( forest.count( evtHash ) >= 1 )
			candidateTree = forest[ evtHash ];
		else {
			// ERROR( classname(), "!!! " << evtHash );
		}

		if ( candidateTree ){
			candidateTree->fillCandidateEvent( rmf->indexForRun( pico->Event_mRunId[0] ), 0, 1.0, 0.0 );

			candidateTree->keepEvent( false );
		}
		
		/*********** Initialize the Event Hash *************/
		// if ( eventHash > -1 ){
			
		// 	DEBUG( classname(), "Event Hash = " << evtHash );
		// 	if ( eventHash != evtHash ){
		// 		return false;
		// 	}
		// } else {
		// 	DEBUG( classname(), "Event" )
		// }

		// fillCandidateEvent()
		// fillCandidateEventPlane();

		// for instance, use to keep only events with pairs of muons
		// default to keep all accepted events
		// keepCandidateEvent = true;
		// and default the track level
		// isMuon = false;
		// isElectron = false;
	}

	

	virtual float calcPsi2(){

		double nTracks = pico->ntrk();
		TRACE( classname(), "mNtrk = " << nTracks );
		if ( nTracks == 0 ) return -99;

		double qx = pico->qx();
		double qy = pico->qy();

		if (qx == 0) return -99;
		if (qy == 0) return -99;

		qx = qx / nTracks;
		qy = qy / nTracks;

		TRACE( classname(), "Qx = " << qx << ", Qy = " << qy );
		double psi = TMath::ATan2( qy, qx ); // raw
		// recenter
		qx = epc.center_qx( qx );
		qy = epc.center_qy( qy );
		psi = TMath::ATan2( qy, qx );
		// TODO: apply flattening

		return psi;

	}

	virtual void trackLoop(){
		
		if ( nullptr == candidateTree ) return;
		// Reset the Tracks TClonesArrays and counters

		// resetTracks();
		// for ( int i = eventHashRange.min; i < eventHashRange.max; i++ ){
		// 	forest[ i ]->resetTracks();
		// }
		
		candidateTree->resetTracks();


		book->cd("eventQA");
		book->fill( "nTracks", pico->Tracks_ );

		TRACE( classname(), "# of Tracks = " << pico->Tracks_ );
		for ( int iTrack = 0; iTrack < pico->Tracks_; iTrack++ ){

			if ( !keepTrack( iTrack ) ) continue;

			 // =  new ((*wTracks)[nCandTracks]) CandidateTrack( );
			CandidateTrack * aTrack = candidateTree->makeCandidateTrack();
			analyzeCandidateTrack( aTrack, iTrack );
			// nCandTracks ++;
		}
		postTrackLoop();
	}

	virtual void postTrackLoop(){
		candidateTree->fillTree();
	}


	virtual void analyzeCandidateTrack( CandidateTrack * aTrack, int iTrack, int nCandTracks ){
		// fillCandidateTrack( aTrack, iTrack );
	}
	virtual void analyzeCandidateTrack( CandidateTrack * aTrack, int iTrack ){
		// fillCandidateTrack( aTrack, iTrack );
	}
	virtual bool keepTrack( int iTrack ){
		return true;
	}

	virtual void postMake(){
		for ( int i = eventHashRange.min; i < eventHashRange.max; i++ ){
			forest[ i ]->close();
		}
	}


	
};


#endif