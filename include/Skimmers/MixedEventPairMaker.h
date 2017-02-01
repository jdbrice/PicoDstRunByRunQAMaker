#ifndef MIXED_EVENT_PAIR_MAKER_H
#define MIXED_EVENT_PAIR_MAKER_H

#include "Candidate.h"
#include "MixedEventCandidateSkimmer.h"
#include "TriggerPatchMapper.h"

#include "PidLR.h"

class MixedEventPairMaker : public MixedEventCandidateSkimmer, public IMixedEventPairTreeMaker
{
protected:

	bool rejectSameChannel      = true;
	bool rejectSameTriggerPatch = true;
	double trackMergedEta       = 0.02;
	double trackMergedPhi       = 1.00;

	PidLR pidLR;
	bool LRPid = false;
	double minLR = -1.0;

public:
	MixedEventPairMaker() {}
	~MixedEventPairMaker() {}

	virtual void initialize(){
		MixedEventCandidateSkimmer::initialize();

		book->cd();
		createMixedEventPairTree( "Mixed Muon Pairs" );

		rejectSameChannel      = config.getBool( nodePath + ".Control:rejectSameChannel", true );
		rejectSameTriggerPatch = config.getBool( nodePath + ".Control:rejectSameTriggerPatch", true );

		INFOC( "reject SameChannel = " << bts(rejectSameChannel) );
		INFOC( "reject SameTriggerPatch = " << bts(rejectSameTriggerPatch) );

		trackMergedEta = config.getDouble( nodePath + ".Params:trackMergedEta", 0.02 );
		trackMergedPhi = config.getDouble( nodePath + ".Params:trackMergedPhi", 1.00 );

		INFOC( "Track Merge Params:" );
		INFOC( "deltaEta = " << trackMergedEta );
		INFOC( "deltaPhi = " << trackMergedPhi );


		vector<string> lrfs = config.childrenOf( nodePath + ".LikelihoodPid", "XmlFunction" );
		INFOC( "Found " << lrfs.size() << plural( lrfs.size(), " PDF", " PDFs" ) );
		for ( string p : lrfs ){
			pidLR.addPDF( config, p );
			INFOC( "ADDING LR: " << config.getString( p+":name" ) );
		}

		LRPid = config.getBool( nodePath + ".Params.LRPid", false );
		minLR = config.getDouble( nodePath + ".Params.minLR", -1.0 );

		INFOC( "==================== LRPID ==================" );
		INFOC( "= " << LRPid << ", min = " << minLR );
		INFOC( "==================== LRPID ==================" );

	}

protected:

	virtual TLorentzVector pairLV( shared_ptr<Candidate> _cand1, shared_ptr<Candidate> _cand2 ){
		TLorentzVector lv1, lv2, lv;
		lv1.SetXYZM( _cand1->track->mPMomentum_mX1, _cand1->track->mPMomentum_mX2, _cand1->track->mPMomentum_mX3, m1 );
		lv2.SetXYZM( _cand2->track->mPMomentum_mX1, _cand2->track->mPMomentum_mX2, _cand2->track->mPMomentum_mX3, m2 );
		lv = lv1+lv2;
		return lv;
	}

	void fillState( string _s, TLorentzVector &_lv, TLorentzVector &_lv1, TLorentzVector &_lv2 ){	
		book->fill( _s + "pT_vs_m", _lv.M(), _lv.Pt() );
		book->fill( _s + "dPhi_vs_dEta",fabs( _lv1.Eta() - _lv2.Eta() ), _lv1.DeltaPhi( _lv2 ) );
	}

	int nTriggerPatch;
	virtual bool keepEvent(){
		nTriggerPatch = 0;
		map<int, bool> tps;
		int nTracks = tracks->GetEntries();
		for ( int iTrack = 0; iTrack < nTracks; iTrack++ ){
			CandidateTrack* aTrack = (CandidateTrack*)tracks->At( iTrack );
			CandidateTrackMtdPidTraits * d1MtdPid = (CandidateTrackMtdPidTraits*)mtdPidTraits->At( aTrack->mMtdPidTraitsIndex );
			int tp = TriggerPatchMapper::findTriggerPatch( d1MtdPid->mMtdHitChan );
			if ( 0 == tps.count( tp ) ) nTriggerPatch++;
			tps[ tp ] = true;
		}

		// if ( nTriggerPatch != 2 ) return false;

		return true;
	}

	virtual void preEventLoop(){
		CandidateSkimmer::preEventLoop();
		
		if ( iEventLoop > 0 ) return;
		book->cd();

		for ( string c : { "uls_", "lsp_", "lsn_" } ){
			for ( string s : { "all_", "chan_", "tp_", "merge_" } ){
				for ( string n : { "pT_vs_m", "dPhi_vs_dEta" } ){

					book->clone( n, c + s + n );
					
					// for ( int iHash = minEventHash; iHash < maxEventHash; iHash++ ){

					// } // iHash
				} // n
			} // s
		} // c
	}

	virtual bool keepMixedTracks( shared_ptr<Candidate> _cand1, shared_ptr<Candidate> _cand2 ){
		// reject mixed event pairs from SAME event
		book->fill( "mixedPairCuts", 0 );

		double lr1 = pidLR.eval( _cand1->track.get(), _cand1->mtdPidTraits.get() );
		double lr2 = pidLR.eval( _cand2->track.get(), _cand2->mtdPidTraits.get() );
		if ( LRPid && (lr1 < minLR || lr2 < minLR) ) return false;

		if ( _cand1->event->mRunId == _cand2->event->mRunId && _cand1->event->mEventId == _cand2->event->mEventId )
			return false;

		TLorentzVector lv = pairLV( _cand1, _cand2 );
		TLorentzVector lv1 = _cand1->track->lvM( m1 );
		TLorentzVector lv2 = _cand2->track->lvM( m2 );

		string c = "uls_";
		if (  2 == _cand1->track->charge() + _cand2->track->charge() ) c = "lsp_";
		if ( -2 == _cand1->track->charge() + _cand2->track->charge() ) c = "lsn_";


		book->fill( "mixedPairCuts", 1 );

		fillState( c + "all_", lv, lv1, lv2 );

		// reject dimoun events that are from the same cell, since this is forbidden in a same-event scenario (TODO: Deal with matchFlag > 1 cases?)
		if ( rejectSameChannel && _cand1->mtdPidTraits->mMtdHitChan == _cand2->mtdPidTraits->mMtdHitChan ){
			return false;
		}
		book->fill( "mixedPairCuts", 2 );
		fillState( c + "chan_", lv, lv1, lv2 );
	

		if ( fabs( lv1.Eta() - lv2.Eta() ) > trackMergedEta || fabs(lv1.DeltaPhi( lv2 )) > trackMergedPhi ){
			book->fill( "mixedPairCuts", 3 );
			fillState( c + "merge_", lv, lv1, lv2 );
		}

		int tpA = TriggerPatchMapper::findTriggerPatch( _cand1->mtdPidTraits->mMtdHitChan );
		int tpB = TriggerPatchMapper::findTriggerPatch( _cand2->mtdPidTraits->mMtdHitChan );

		if ( rejectSameTriggerPatch && tpA == tpB ){
			// return false;
		} else {
			book->fill( "mixedPairCuts", 4 );
			fillState( c + "tp_", lv, lv1, lv2 );
		}
		

		return true;
	}

	virtual void mixTrack( shared_ptr<Candidate> _cand ){
		// we want to mix this event/track with ones from the same event class 
		
		vector<shared_ptr<Candidate> > &buff = buffer[ cEventHash ];

		int nMixed = 0;
		for ( shared_ptr<Candidate> bufCand : buff ){
			
			// Test tracks
			
			
			// Test as a pair
			TLorentzVector lv1, lv2, lv;
			lv1.SetXYZM( _cand->track->mPMomentum_mX1, _cand->track->mPMomentum_mX2, _cand->track->mPMomentum_mX3, m1 );
			lv2.SetXYZM( bufCand->track->mPMomentum_mX1, bufCand->track->mPMomentum_mX2, bufCand->track->mPMomentum_mX3, m2 );
			lv = lv1 + lv2;
			if ( !PairFilter::keepSameEventPair( pairCuts, lv, lv1, lv2 ) ) continue;
			// Apply leading pT cut (keepSameEventPair) before maing trigger correction plots
			if( !keepMixedTracks( _cand, bufCand ) ) continue;
			
			
			nMixed++;
			analyzePair( _cand, bufCand );
			if ( nMixed >= nPerEventHash ) break;
		}
		

		if ( nMixed < nPerEventHash ){
			WARN( classname(), "EventHash = " << cEventHash <<  "only mixed with " << nMixed << " " );
		}

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

		double lr1 = pidLR.eval( _cand1->track.get(), _cand1->mtdPidTraits.get() );
		double lr2 = pidLR.eval( _cand2->track.get(), _cand2->mtdPidTraits.get() );

		wPairs->set( lv, _cand1->track->charge() + _cand2->track->charge() );
		wPairs->setDaughters(    lv1, _cand1->mtdPidTraits->mMtdHitChan, lr1,
								 lv2, _cand2->mtdPidTraits->mMtdHitChan, lr2 );

	}
	
};



#endif