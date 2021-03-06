#ifndef CANDIDATE_MAKER_H
#define CANDIDATE_MAKER_H

#include "XmlRange.h"

//Project
#include "PicoDstSkimmer.h"

#include "CandidateTreeMaker.h"
#include "EventHasher.h"
#include "RunMapFactory.h"
#include "CandidateFilter.h"

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

		if ( "Run15_PP_200_Mtd" == picoDstAdapter ){
			calcEventPlane = false;
		}
		else {
			calcEventPlane = true;
		}

		useRefMultCorr = config.getBool( nodePath + ":rmc", true );

		splitEvents = config.getBool( nodePath + ".EventHash:split" );
		INFO( classname(), "Splitting by Event Hash : " << bts( splitEvents ) );
		
		// Create the TreeMaker
		candidateTree = shared_ptr<CandidateTreeMaker>( new CandidateTreeMaker(  ) );
		candidateTree->createFile( config.getXString( nodePath + ".output.TTree:url" ) );
		candidateTree->setPicoDst( pico );
		makeTree( candidateTree );
	}


protected:
	StRefMultCorr * rmc = nullptr;
	EventHasher eht;
	XmlRange eventHashRange;
	int eventHash;
	bool splitEvents = false;
	// shared_ptr<RunMapFactory> rmf;
	bool useRefMultCorr = false;
	bool calcEventPlane = true;
	
	map< int, shared_ptr<CandidateTreeMaker> > forest;
	shared_ptr<CandidateTreeMaker> candidateTree;

	bool isMuon = false;
	bool isElectron = false;


	/* Creates the CandidateTree with certain branches
	 *
	 * Subclasses should override this to make the branches that they want.
	 *
	 * @_tree 	The CandiateTreeMaker object to act on, set p this way so that it can be used in a forest context
	 * @return void 
	 */
	virtual void makeTree( shared_ptr<CandidateTreeMaker> _tree ) {
		_tree->createTree( );
	}

	/* Applys event level cuts
	 * 
	 * @return 
	 *		True : keep event
	 *		False : reject event
	 */
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
		// if ( rmf->isRunBad( pico->Event_mRunId[0] ) ){
		// 	DEBUG( classname(), pico->Event_mRunId[0]  << " is BAD" );
		// 	return false;
		// }

		return true;
	}

	virtual void analyzeEvent(){
		if ( candidateTree ){


			int bin16 = 0;
			float weight = 1.0;
			float psi2 = 0;
			if ( useRefMultCorr ){
				bin16 = rmc->getCentralityBin16();
				weight = rmc->getWeight();
				if ( weight < 1.0 ) weight = 1.0; // TODO: is this best
				psi2 = calcPsi2();
			}
			candidateTree->fillCandidateEvent( rmf->indexForRun( pico->Event_mRunId[0] ), bin16, weight, psi2 );

			// defaults to not keep tracks
			candidateTree->keepEvent( false );
		}
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

		candidateTree->resetTracks();


		book->cd("eventQA");
		book->fill( "nTracks", pico->Tracks_ );

		TRACE( classname(), "# of Tracks = " << pico->Tracks_ );
		for ( int iTrack = 0; iTrack < pico->Tracks_; iTrack++ ){

			if ( !keepTrack( iTrack ) ) continue;

			CandidateTrack * aTrack = candidateTree->makeCandidateTrack();
			analyzeCandidateTrack( aTrack, iTrack );
			
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
		PicoDstSkimmer::postMake();
		candidateTree->close();
		
	}
	
};


#endif