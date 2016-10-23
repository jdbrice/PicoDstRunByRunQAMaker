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



class SameEventPairMaker : public CandidateSkimmer
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

		CandidateFilter::setDefaultMuonCuts( trackCuts );
		if ( config.exists( nodePath + ".MuonCandidateCuts" ) ){
			trackCuts.init( config, nodePath + ".MuonCandidateCuts" );

			INFO( classname(), "" );
			INFO( classname(), "############### Muon Cuts ###################"  );
			trackCuts.report();
			INFO( classname(), "" );
		} else {
			WARN( classname(), "No Muon Cuts Found, using defaults" );
			INFO( classname(), "" );
			INFO( classname(), "############### Muon Cuts ###################"  );
			trackCuts.report();
			INFO( classname(), "" );
		}

		PairFilter::setDefaultPairCuts( pairCuts );
		if ( config.exists( nodePath + ".SameEventPairCuts" ) ){
			pairCuts.init( config, nodePath + ".SameEventPairCuts" );

			INFO( classname(), "" );
			INFO( classname(), "############### Pair Cuts ###################"  );
			pairCuts.report();
			INFO( classname(), "" );
		} else {
			WARN( classname(), "No Pair Cuts Found, using defaults" );
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

		// createSameEventPairTree( "Same Event Muon Pairs" );

	}


protected:

	double m1, m2;
	CutCollection trackCuts;
	CutCollection pairCuts;
	EventHasher eht;
	int eventHash = -1;
	int currentEventHash = -1;
	shared_ptr<RunMapFactory> rmf;


	bool keepTrack( CandidateTrack *aTrack ){
		DEBUG( classname(), "("<< aTrack << ")" );
		CandidateTrackMtdPidTraits *mtdPid = (CandidateTrackMtdPidTraits *)mtdPidTraits->At( aTrack->mMtdPidTraitsIndex );
		return CandidateFilter::isMuon( aTrack, mtdPid, trackCuts,  makeTrackCutQA ? book : nullptr );
	}

	virtual bool keepPair( TLorentzVector _lv1, TLorentzVector _lv2 ){
		return PairFilter::keepSameEventPair( pairCuts, _lv1, _lv2 );
	}

	virtual bool keepEvent(){
		bool passAll = CandidateSkimmer::keepEvent();

		if ( rmf->isRunBad( event->mRunId ) ){
			ERROR( classname(), "Should not be bad runs here!" );
			passAll = false;
		}

		return passAll;

	}

	virtual void analyzeEvent(){
		
		if ( event->mBin16 < 0 || event->mBin16 > 50 )
			return;

		// wEventHash comes from ISameEventPairTreeMaker
		currentEventHash = eht.hash( event );
		// wBin16     = event->mBin16;

		TRACE( classname(), "current Event = " << currentEventHash );
		if ( 0 <= eventHash && eventHash != currentEventHash ) return;

		// Pre loop hook
		prePairLoop();

		int nTracks = tracks->GetEntries();
		int nPairs = 0;
		
		if ( book->exists( "pre_nPairs" ) )
			book->get( "pre_nPairs", "pairQA" )->Fill( nTracks * ( nTracks - 1 ) / 2.0 );

		for ( int iTrack = 0; iTrack < nTracks; iTrack++ ){
			CandidateTrack* aTrack = (CandidateTrack*)tracks->At( iTrack );
			if ( !keepTrack( aTrack ) ) continue;

			DEBUG( classname(), "Inner track loop" );
			for ( int jTrack = iTrack; jTrack < nTracks; jTrack++ ){
				if ( iTrack == jTrack ) continue;
				CandidateTrack* bTrack = (CandidateTrack*)tracks->At( jTrack );
				if ( !keepTrack( bTrack ) ) continue;

				TLorentzVector lv1, lv2, lv;
				lv1.SetXYZM( aTrack->mPMomentum_mX1, aTrack->mPMomentum_mX2, aTrack->mPMomentum_mX3, m1 );
				lv2.SetXYZM( bTrack->mPMomentum_mX1, bTrack->mPMomentum_mX2, bTrack->mPMomentum_mX3, m2 );

				lv = lv1 + lv2;

				if ( !keepPair( lv1, lv2 ) ) continue;
				analyzePair( aTrack, bTrack );
				
				nPairs++;

			}
		}

		// post loop hook
		postPairLoop( nPairs );
		// if ( nPairs > 0 ){
		// 	book->get( "nPairs", "pairQA" )->Fill( nPairs );
		// 	mSameEventTree->Fill();
		// }
	} // analyzeEvent


	// virtual void preMake(){

	// 	book->cd();
	// 	CutCollectionTreeMaker::makeCutTree( trackCuts, "trackCuts" );
	// 	CutCollectionTreeMaker::makeCutTree( pairCuts, "pairCuts" );

	// }

	// virtual void postMake(){
	// 	CandidateSkimmer::postMake();
	// }

	virtual void analyzePair( CandidateTrack * _aTrack, CandidateTrack * _bTrack ){
		
	}

	virtual void postPairLoop( int _nPairs ){
		DEBUG( classname(), "" );
		if ( book->exists( "nPairs" ) )
			book->get( "nPairs", "pairQA" )->Fill( _nPairs );
	}

	virtual void prePairLoop(){
		DEBUG( classname(), "" );
	}


	// virtual void fillCandidatePair( CandidateTrack * aTrack, CandidateTrack * bTrack ){

	// 	CandidatePair * aPair = new ((*wPairs)[nCandPairs]) CandidatePair( );
		
	// 	TLorentzVector lv1, lv2, lv;
	// 	lv1.SetXYZM( aTrack->mPMomentum_mX1, aTrack->mPMomentum_mX2, aTrack->mPMomentum_mX3, m1 );
	// 	lv2.SetXYZM( bTrack->mPMomentum_mX1, bTrack->mPMomentum_mX2, bTrack->mPMomentum_mX3, m2 );

	// 	lv = lv1 + lv2;

	// 	aPair->set( lv.Px(), lv.Py(), lv.Pz(), lv.M(), aTrack->charge() + bTrack->charge() );
	// 	nCandPairs++;
	// }

	
};

#endif