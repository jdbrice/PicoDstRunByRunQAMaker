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

		CandidateTrackMtdPidTraits * d1MtdPid = (CandidateTrackMtdPidTraits*)mtdPidTraits->At( aTrack->mMtdPidTraitsIndex );
		CandidateTrackMtdPidTraits * d2MtdPid = (CandidateTrackMtdPidTraits*)mtdPidTraits->At( bTrack->mMtdPidTraitsIndex );

		// calculate pid LRs
		double lr1 = pidLR.eval( aTrack, d1MtdPid );
		double lr2 = pidLR.eval( bTrack, d2MtdPid );

		aPair->set( lv, aTrack->charge() + bTrack->charge() );
		aPair->setDaughters(    lv1, d1MtdPid->mMtdHitChan, lr1,
								lv2, d2MtdPid->mMtdHitChan, lr2 );




		// aPair->set( lv.Px(), lv.Py(), lv.Pz(), lv.M(), aTrack->charge() + bTrack->charge(), leadingPt );

		

		// aPair->d1_mMomentum_mX1   = lv1.Px();
		// aPair->d1_mMomentum_mX2   = lv1.Py();
		// aPair->d1_mMomentum_mX3   = lv1.Pz();
		// aPair->d1_mMass           = m1;
		// aPair->d1_mMtdBackleg      = TriggerPatchMapper::backleg( d1MtdPid->mMtdHitChan );
		// aPair->d1_mMtdTriggerPatch = TriggerPatchMapper::findTriggerPatch( d1MtdPid->mMtdHitChan );
		// aPair->d1_mMtdEtaStrip     = TriggerPatchMapper::etaStrip( d1MtdPid->mMtdHitChan );

		// aPair->d2_mMomentum_mX1   = lv2.Px();
		// aPair->d2_mMomentum_mX2   = lv2.Py();
		// aPair->d2_mMomentum_mX3   = lv2.Pz();
		// aPair->d2_mMass           = m2;
		// aPair->d2_mMtdBackleg      = TriggerPatchMapper::backleg( d2MtdPid->mMtdHitChan );
		// aPair->d2_mMtdTriggerPatch = TriggerPatchMapper::findTriggerPatch( d2MtdPid->mMtdHitChan );
		// aPair->d2_mMtdEtaStrip     = TriggerPatchMapper::etaStrip( d2MtdPid->mMtdHitChan );

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