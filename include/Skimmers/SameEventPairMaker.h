#ifndef SAME_EVENT_PAIR_MAKER_H
#define SAME_EVENT_PAIR_MAKER_H

//RooBarb
#include "TreeAnalyzer.h"
#include "CutCollection.h"

//ROOT
#include "TLorentzVector.h"

// Project
#include "CandidateSkimmer.h"
#include "CandidateFilter.h"
#include "EventHasher.h"
#include "RunMapFactory.h"
#include "ISameEventPairTreeMaker.h"
#include "PairFilter.h"
#include "CutCollectionTreeMaker.h"



class SameEventPairMaker : public CandidateSkimmer, public ISameEventPairTreeMaker
{
public:
	virtual const char * classname() const { return "SameEventPairMaker"; }
	SameEventPairMaker(){}
	~SameEventPairMaker(){}

	virtual void initialize(){
		CandidateSkimmer::initialize();

		m1 = config.getDouble( nodePath + ".Particles:mass1", 0.0511 );
		m2 = config.getDouble( nodePath + ".Particles:mass2", 0.0511 );

		INFO( classname(), "mass1 = " << m1 );
		INFO( classname(), "mass2 = " << m2 );

		if ( config.exists( nodePath + ".MuonCandidateCuts" ) ){
			trackCuts.init( config, nodePath + ".MuonCandidateCuts" );

			INFO( classname(), "" );
			INFO( classname(), "############### Muon Cuts ###################"  );
			trackCuts.report();
			INFO( classname(), "" );
		}

		if ( config.exists( nodePath + ".SameEventPairCuts" ) ){
			pairCuts.init( config, nodePath + ".SameEventPairCuts" );

			INFO( classname(), "" );
			INFO( classname(), "############### Pair Cuts ###################"  );
			pairCuts.report();
			INFO( classname(), "" );
		}

		eventHash = config.getInt( nodePath + ".EventHash", -1 );
		eht.load( config, nodePath + ".MixedEventBins" );

		INFO( classname(), "EventHash = " << eventHash );

		rmf = shared_ptr<RunMapFactory>( new RunMapFactory( "Run15PP200", false ) );
		INFO( classname(), "BAD == " << rmf->isRunBad( 16055005 ) );

		createSameEventPairTree( "Same Event Muon Pairs" );

	}


protected:

	double m1, m2;
	CutCollection trackCuts;
	CutCollection pairCuts;
	EventHasher eht;
	int eventHash = -1;
	shared_ptr<RunMapFactory> rmf;


	bool keepTrack( CandidateTrack *aTrack ){
		CandidateTrackMtdPidTraits *mtdPid = (CandidateTrackMtdPidTraits *)mtdPidTraits->At( aTrack->mMtdPidTraitsIndex );
		return CandidateFilter::isMuon( aTrack, mtdPid, trackCuts,  makeTrackCutQA ? book : nullptr );
	}

	virtual bool keepEvent(){

		if ( rmf->isRunBad( event->mRunId ) ){
			ERROR( classname(), "Should not be bad runs here!" );
			return false;
		}

		wEvent->copy( event );
		return true;

	}

	virtual void analyzeEvent(){
		
		resetPairs();

		// wEventHash comes from ISameEventPairTreeMaker
		wEventHash = eht.hash( event );

		TRACE( classname(), "current Event = " << wEventHash );
		if ( 0 <= eventHash && eventHash != wEventHash ) return;

		// whether or not to fill teh pair tree
		bool fillTree = false;

		int nTracks = tracks->GetEntries();
		for ( int iTrack = 0; iTrack < nTracks; iTrack++ ){
			CandidateTrack* aTrack = (CandidateTrack*)tracks->At( iTrack );
			if ( !keepTrack( aTrack ) ) continue;

			for ( int jTrack = iTrack; jTrack < nTracks; jTrack++ ){
				if ( iTrack == jTrack ) continue;
				CandidateTrack* bTrack = (CandidateTrack*)tracks->At( jTrack );
				if ( !keepTrack( bTrack ) ) continue;

				TLorentzVector lv1, lv2, lv;
				lv1.SetXYZM( aTrack->mPMomentum_mX1, aTrack->mPMomentum_mX2, aTrack->mPMomentum_mX3, m1 );
				lv2.SetXYZM( bTrack->mPMomentum_mX1, bTrack->mPMomentum_mX2, bTrack->mPMomentum_mX3, m2 );

				lv = lv1 + lv2;

				if ( !PairFilter::keepSameEventPair( pairCuts, lv1, lv2 ) ) continue;
				fillCandidatePair( aTrack, bTrack );
				fillTree = true;

			}
		}


		if ( true == fillTree )
			mSameEventTree->Fill();
	} // analyzeEvent


	virtual void preMake(){

		book->cd();
		CutCollectionTreeMaker::makeCutTree( trackCuts, "trackCuts" );
		CutCollectionTreeMaker::makeCutTree( pairCuts, "pairCuts" );

	}

	virtual void postMake(){
		CandidateSkimmer::postMake();
	}


	virtual void fillCandidatePair( CandidateTrack * aTrack, CandidateTrack * bTrack ){

		CandidatePair * aPair = new ((*wPairs)[nCandPairs]) CandidatePair( );
		
		TLorentzVector lv1, lv2, lv;
		lv1.SetXYZM( aTrack->mPMomentum_mX1, aTrack->mPMomentum_mX2, aTrack->mPMomentum_mX3, m1 );
		lv2.SetXYZM( bTrack->mPMomentum_mX1, bTrack->mPMomentum_mX2, bTrack->mPMomentum_mX3, m2 );

		lv = lv1 + lv2;

		aPair->set( lv.Px(), lv.Py(), lv.Pz(), lv.M(), aTrack->charge() * bTrack->charge() );
		nCandPairs++;
	}

	
};

#endif