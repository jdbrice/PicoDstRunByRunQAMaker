#ifndef MIXED_EVENT_PAIR_MAKER_H
#define MIXED_EVENT_PAIR_MAKER_H


class MixedEventPairMaker : public MixedEventCandidateSkimmer
{
public:
	MixedEventPairMaker() {}
	~MixedEventPairMaker() {}

	virtual void initialize(){
		MixedEventCandidateSkimmer::initialize();
	}

protected:

	virtual bool keepMixedTracks( shared_ptr<Candidate> _cand1, shared_ptr<Candidate> _cand2 ){
		// reject mixed event pairs from SAME event
		if ( _cand1->event->mRunId == _cand2->event->mRunId ) //&& _cand1->event->mEventId == _cand2->event->mEventId )
			return false;
		// reject dimoun events that are from the same cell, since this is forbidden in a same-event scenario (TODO: Deal with matchFlag > 1 cases?)
		if ( _cand1->mtdPidTraits->mMatchFlag >= 1 && _cand2->mtdPidTraits->mMatchFlag >= 1 && _cand1->mtdPidTraits->mMtdHitChan == _cand2->mtdPidTraits->mMtdHitChan ){
			return false;
		}

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


			nMixed++;

			fillCandidatePair( _cand, bufCand );
			mMixedEventTree->Fill();

			
			if ( nMixed >= nPerEventHash ) break;
		}
		if ( nMixed < nPerEventHash ){
			WARN( classname(), "Only mixed with " << nMixed << " " );
		}

		if ( !bufferContains( buff, _cand ) ){
			addToBuffer( _cand );
		}
	}
	
};



#endif