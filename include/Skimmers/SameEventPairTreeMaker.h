#ifndef SAME_EVENT_PAIR_TREE_MAKER_H
#define SAME_EVENT_PAIR_TREE_MAKER_H

#include "SameEventPairMaker.h"
#include "ISameEventPairTreeMaker.h"

class SameEventPairTreeMaker : public SameEventPairMaker, public ISameEventPairTreeMaker
{
public:
	virtual const char* classname() const { return "SameEventPairTreeMaker"; }
	SameEventPairTreeMaker(){}
	~SameEventPairTreeMaker(){}

	virtual void initialize(){
		SameEventPairMaker::initialize();
		createSameEventPairTree( "Same Event Muon Pairs" );
	}

	virtual void preMake(){
		book->cd();
		CutCollectionTreeMaker::makeCutTree( trackCuts, "trackCuts" );
		CutCollectionTreeMaker::makeCutTree( pairCuts, "pairCuts" );
	}

	virtual void analyzePair( CandidateTrack * _aTrack, CandidateTrack * _bTrack ){
		fillCandidatePair( _aTrack, _bTrack );
	}

	virtual void prePairLoop(){
		resetPairs();
	}

	virtual void fillCandidatePair( CandidateTrack * aTrack, CandidateTrack * bTrack ){

		CandidatePair * aPair = new ((*wPairs)[nCandPairs]) CandidatePair( );
		
		TLorentzVector lv1, lv2, lv;
		lv1.SetXYZM( aTrack->mPMomentum_mX1, aTrack->mPMomentum_mX2, aTrack->mPMomentum_mX3, m1 );
		lv2.SetXYZM( bTrack->mPMomentum_mX1, bTrack->mPMomentum_mX2, bTrack->mPMomentum_mX3, m2 );

		lv = lv1 + lv2;

		aPair->set( lv.Px(), lv.Py(), lv.Pz(), lv.M(), aTrack->charge() + bTrack->charge() );
		nCandPairs++;
	}

	virtual void postPairLoop( int _nPairs ){

		wEventHash = currentEventHash;
		wBin16 = event->mBin16;
		wEvent->copy( event );

		if ( _nPairs > 0 ){
			// book->get( "nPairs", "pairQA" )->Fill( nPairs );
			mSameEventTree->Fill();
		}
	}

protected:

};



#endif