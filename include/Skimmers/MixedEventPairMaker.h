#ifndef MIXED_EVENT_PAIR_MAKER_H
#define MIXED_EVENT_PAIR_MAKER_H

#include "Candidate.h"
#include "MixedEventCandidateSkimmer.h"
#include "TriggerPatchMapper.h"

class MixedEventPairMaker : public MixedEventCandidateSkimmer, public IMixedEventPairTreeMaker
{
public:
	MixedEventPairMaker() {}
	~MixedEventPairMaker() {}

	virtual void initialize(){
		MixedEventCandidateSkimmer::initialize();

		book->cd();
		createMixedEventPairTree( "Mixed Muon Pairs" );
	}

protected:

	virtual bool keepMixedTracks( shared_ptr<Candidate> _cand1, shared_ptr<Candidate> _cand2 ){
		// reject mixed event pairs from SAME event
		if ( _cand1->event->mRunId == _cand2->event->mRunId && _cand1->event->mEventId == _cand2->event->mEventId )
			return false;
		
		// reject dimoun events that are from the same cell, since this is forbidden in a same-event scenario (TODO: Deal with matchFlag > 1 cases?)
		if ( _cand1->mtdPidTraits->mMtdHitChan == _cand2->mtdPidTraits->mMtdHitChan ){
			return false;
		}

		int tpA = TriggerPatchMapper::findTriggerPatch( _cand1->mtdPidTraits->mMtdHitChan );
		int tpB = TriggerPatchMapper::findTriggerPatch( _cand2->mtdPidTraits->mMtdHitChan );

		if ( tpA == tpB ) 
			return false;


		return true;
	}

	virtual void mixTrack( shared_ptr<Candidate> _cand ){
		// we want to mix this event/track with ones from the same event class 
		
		vector<shared_ptr<Candidate> > &buff = buffer[ cEventHash ];

		int nMixed = 0;
		for ( shared_ptr<Candidate> bufCand : buff ){
			
			// Test tracks
			if( !keepMixedTracks( _cand, bufCand ) ) continue;
			
			// Test as a pair
			TLorentzVector lv1, lv2, lv;
			lv1.SetXYZM( _cand->track->mPMomentum_mX1, _cand->track->mPMomentum_mX2, _cand->track->mPMomentum_mX3, m1 );
			lv2.SetXYZM( bufCand->track->mPMomentum_mX1, bufCand->track->mPMomentum_mX2, bufCand->track->mPMomentum_mX3, m2 );
			if ( !PairFilter::keepSameEventPair( pairCuts, lv1, lv2 ) ) continue;
			if ( !PairFilter::keepMixedEventPair( pairCuts, lv1, lv2 ) ) continue;
			
			nMixed++;
			analyzePair( _cand, bufCand );
			if ( nMixed >= nPerEventHash ) break;
		}
		// if ( nMixed < nPerEventHash ){
		// 	WARN( classname(), "EventHash = " << cEventHash <<  "only mixed with " << nMixed << " " );
		// }

		if ( !bufferContains( buff, _cand ) ){
			addToBuffer( _cand );
		}
	}

	virtual void analyzePair( shared_ptr<Candidate> _cand1, shared_ptr<Candidate> _cand2 ){
		fillCandidatePair( _cand1, _cand2 );
		mMixedEventTree->Fill();
	}

	virtual void fillCandidatePair( shared_ptr<Candidate> _cand1, shared_ptr<Candidate> _cand2 ){
		
		wEventHash = cEventHash;

		wEvent1 = _cand1->event.get();
		wEvent2 = _cand2->event.get();
		
		TLorentzVector lv1, lv2, lv;
		lv1.SetXYZM( _cand1->track->mPMomentum_mX1, _cand1->track->mPMomentum_mX2, _cand1->track->mPMomentum_mX3, m1 );
		lv2.SetXYZM( _cand2->track->mPMomentum_mX1, _cand2->track->mPMomentum_mX2, _cand2->track->mPMomentum_mX3, m2 );

		lv = lv1 + lv2;

		float leadingPt = lv1.Pt();
		if ( lv2.Pt() > lv1.Pt() )
			leadingPt = lv2.Pt();

		wPairs->set( lv.Px(), lv.Py(), lv.Pz(), lv.M(), _cand1->track->charge() + _cand2->track->charge(), leadingPt );


		wPairs->d1_mtdBackleg      = TriggerPatchMapper::backleg( _cand1->mtdPidTraits->mMtdHitChan );
		wPairs->d1_mtdTriggerPatch = TriggerPatchMapper::findTriggerPatch( _cand1->mtdPidTraits->mMtdHitChan );
		wPairs->d1_mtdEtaStrip     = TriggerPatchMapper::etaStrip( _cand1->mtdPidTraits->mMtdHitChan );

		wPairs->d2_mtdBackleg      = TriggerPatchMapper::backleg( _cand2->mtdPidTraits->mMtdHitChan );
		wPairs->d2_mtdTriggerPatch = TriggerPatchMapper::findTriggerPatch( _cand2->mtdPidTraits->mMtdHitChan );
		wPairs->d2_mtdEtaStrip     = TriggerPatchMapper::etaStrip( _cand2->mtdPidTraits->mMtdHitChan );


	}
	
};



#endif