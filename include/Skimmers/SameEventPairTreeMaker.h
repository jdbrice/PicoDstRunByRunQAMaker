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

		float leadingPt = lv1.Pt();
		if ( lv2.Pt() > lv1.Pt() )
			leadingPt = lv2.Pt();

		aPair->set( lv.Px(), lv.Py(), lv.Pz(), lv.M(), aTrack->charge() + bTrack->charge(), leadingPt );

		CandidateTrackMtdPidTraits * d1MtdPid = (CandidateTrackMtdPidTraits*)mtdPidTraits->At( aTrack->mMtdPidTraitsIndex );
		CandidateTrackMtdPidTraits * d2MtdPid = (CandidateTrackMtdPidTraits*)mtdPidTraits->At( bTrack->mMtdPidTraitsIndex );

		aPair->d1_mMomentum_mX1   = lv1.Px();
		aPair->d1_mMomentum_mX2   = lv1.Py();
		aPair->d1_mMomentum_mX3   = lv1.Pz();
		aPair->d1_mMass           = m1;
		aPair->d1_mtdBackleg      = TriggerPatchMapper::backleg( d1MtdPid->mMtdHitChan );
		aPair->d1_mtdTriggerPatch = TriggerPatchMapper::findTriggerPatch( d1MtdPid->mMtdHitChan );
		aPair->d1_mtdEtaStrip     = TriggerPatchMapper::etaStrip( d1MtdPid->mMtdHitChan );

		aPair->d2_mMomentum_mX1   = lv2.Px();
		aPair->d2_mMomentum_mX2   = lv2.Py();
		aPair->d2_mMomentum_mX3   = lv2.Pz();
		aPair->d2_mMass           = m2;
		aPair->d2_mtdBackleg      = TriggerPatchMapper::backleg( d2MtdPid->mMtdHitChan );
		aPair->d2_mtdTriggerPatch = TriggerPatchMapper::findTriggerPatch( d2MtdPid->mMtdHitChan );
		aPair->d2_mtdEtaStrip     = TriggerPatchMapper::etaStrip( d2MtdPid->mMtdHitChan );

		nCandPairs++;
	}

	virtual void postPairLoop( int _nPairs ){

		book->cd();
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