#ifndef MTD_TREE_MAKER_H
#define MTD_TREE_MAKER_H

#include "CandidateSkimmer.h"
#include "TriggerPatchMapper.h"

#include "TLorentzVector.h"


class MtdTreeMaker : public CandidateSkimmer
{
public:
	MtdTreeMaker() {}
	~MtdTreeMaker() {}

	virtual void initialize(){
		CandidateSkimmer::initialize();

		book->cd();
		trackTuple = new TNtuple( "MtdTrackTree", "MTD Tree", "runIndex:pt:eta:phi:charge:chan:bl:es:tp:mod:dy:dz" );
		eventTuple = new TNtuple( "MtdEventTree", "MTD Tree", "runIndex:nTracks:nTP:tpA:tpB:tpC" );
	}

protected:

	virtual void analyzeEvent(){

		int nTracks = tracks->GetEntries();
		int nTP = 0;
		int tpA = -1, tpB = -1, tpC = -1;
		map<int, bool> tps;
		for ( int iTrack = 0; iTrack < nTracks; iTrack++ ){
			CandidateTrack* aTrack = (CandidateTrack*)tracks->At( iTrack );
			CandidateTrackMtdPidTraits *mtdPid = (CandidateTrackMtdPidTraits *)mtdPidTraits->At( aTrack->mMtdPidTraitsIndex );
			TLorentzVector lv;
			lv.SetXYZM( aTrack->mPMomentum_mX1, aTrack->mPMomentum_mX2, aTrack->mPMomentum_mX3, 0 );

			Float_t chan = mtdPid->mMtdHitChan;
			Float_t bl   = TriggerPatchMapper::backleg( chan );
			Float_t es   = TriggerPatchMapper::etaStrip( chan );
			Float_t tp   = TriggerPatchMapper::findTriggerPatch( chan );
			Float_t mod  = TriggerPatchMapper::module( chan );

			trackTuple->Fill( event->mRunIndex, lv.Pt(), lv.Eta(), lv.Phi(), aTrack->charge(), chan, bl, es, tp, mod, mtdPid->mDeltaY, mtdPid->mDeltaZ );

			if ( 0 == tps.count( tp ) ){
				nTP++;
			}
			if ( 1 == nTP  ) tpA = tp;
			if ( 2 == nTP  ) tpB = tp;
			if ( 3 == nTP  ) tpC = tp;

			tps[ tp ] = true;
		}

		if ( tpB > tpA ){
			int t = tpA;
			tpA = tpB;
			tpB = tpA;
		}
		eventTuple->Fill( event->mRunIndex, nTracks, nTP, tpA, tpB, tpC );


	}

	TNtuple *trackTuple = nullptr;
	TNtuple *eventTuple = nullptr;

	
};


#endif