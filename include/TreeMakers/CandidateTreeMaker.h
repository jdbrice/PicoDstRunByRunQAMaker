#ifndef CANDIDATE_TREE_MAKER_H
#define CANDIDATE_TREE_MAKER_H

#include "ICandidateTreeMaker.h"
#include "IObject.h"

#include "CandidateEvent.h"
#include "CandidateEventPlane.h"
#include "CandidateTrack.h"
#include "CandidateTrackBTofPidTraits.h"
#include "CandidateTrackMtdPidTraits.h"


class CandidateTreeMaker : public ICandidateTreeMaker, public IObject
{
public:
	virtual const char* classname() const { return "CandidateTreeMaker"; }
	CandidateTreeMaker( ) {}
	~CandidateTreeMaker( ) {}

	createFile( string _filename ){
		outputFilename = _filename;
		output = new TFile( outputFilename.c_str(), "RECREATE" );
	}

	void setPicoDst( shared_ptr<IPicoDst> _pico ){
		pico = _pico;
	}

	void close(){
		if ( nullptr == output )  return;
		output->cd();
		mTree->Write();
	}


	virtual void fillCandidateEvent( int runIndex, int bin16, float weight, float psi ) {
		
		wEvent->mRunId 				= pico->Event_mRunId[0];
		wEvent->mEventId 			= pico->Event_mEventId[0];
		wEvent->mGRefMult 			= pico->Event_mGRefMult[0];
		wEvent->mTriggerWord 		= pico->Event_mTriggerWord[0];
		wEvent->mTriggerWordMtd 	= pico->Event_mTriggerWordMtd[0];
		wEvent->mPrimaryVertex_mX1 	= pico->vx();
		wEvent->mPrimaryVertex_mX2 	= pico->vy();
		wEvent->mPrimaryVertex_mX3 	= pico->vz();
		wEvent->mRunIndex			= runIndex;

		if ( rmc ){
			wEvent->mBin16 			= bin16;
			wEvent->mWeight 		= weight;
		} else {
			wEvent->mBin16 			= 0;
			wEvent->mWeight 		= 1.0;
		}

		// TODO: after EventPlane is settled
		if ( calcEventPlane )
			wEvent->mPsi2 		= (psi * 10000) ;
		else 
			wEvent->mPsi2 		= 0.0;
	}

	virtual void fillCandidateEventPlane(){

		wEventPlane->mQx_eta_pos           = pico->EventPlane_mQx_eta_pos[0];
		wEventPlane->mQy_eta_pos           = pico->EventPlane_mQy_eta_pos[0];
		wEventPlane->mQx_eta_neg           = pico->EventPlane_mQx_eta_neg[0];
		wEventPlane->mQy_eta_neg           = pico->EventPlane_mQy_eta_neg[0];
		wEventPlane->mNtrk_eta_pos         = pico->EventPlane_mNtrk_eta_pos[0];
		wEventPlane->mNtrk_eta_neg         = pico->EventPlane_mNtrk_eta_neg[0];
		wEventPlane->mWeight_eta_pos       = pico->EventPlane_mWeight_eta_pos[0];
		wEventPlane->mWeight_eta_neg       = pico->EventPlane_mWeight_eta_neg[0];
		wEventPlane->mQx_chg_pos           = pico->EventPlane_mQx_chg_pos[0];
		wEventPlane->mQy_chg_pos           = pico->EventPlane_mQy_chg_pos[0];
		wEventPlane->mQx_chg_neg           = pico->EventPlane_mQx_chg_neg[0];
		wEventPlane->mQy_chg_neg           = pico->EventPlane_mQy_chg_neg[0];
		wEventPlane->mNtrk_chg_pos_eta_pos = pico->EventPlane_mNtrk_chg_pos_eta_pos[0];
		wEventPlane->mNtrk_chg_pos_eta_neg = pico->EventPlane_mNtrk_chg_pos_eta_neg[0];
		wEventPlane->mNtrk_chg_neg_eta_pos = pico->EventPlane_mNtrk_chg_neg_eta_pos[0];
		wEventPlane->mNtrk_chg_neg_eta_neg = pico->EventPlane_mNtrk_chg_neg_eta_neg[0];
		wEventPlane->mWeight_chg_pos       = pico->EventPlane_mWeight_chg_pos[0];
		wEventPlane->mWeight_chg_neg       = pico->EventPlane_mWeight_chg_neg[0];
		wEventPlane->mQx_ran_1             = pico->EventPlane_mQx_ran_1[0];
		wEventPlane->mQy_ran_1             = pico->EventPlane_mQy_ran_1[0];
		wEventPlane->mQx_ran_2             = pico->EventPlane_mQx_ran_2[0];
		wEventPlane->mQy_ran_2             = pico->EventPlane_mQy_ran_2[0];
		wEventPlane->mNtrk_ran_1_eta_pos   = pico->EventPlane_mNtrk_ran_1_eta_pos[0];
		wEventPlane->mNtrk_ran_1_eta_neg   = pico->EventPlane_mNtrk_ran_1_eta_neg[0];
		wEventPlane->mNtrk_ran_2_eta_pos   = pico->EventPlane_mNtrk_ran_2_eta_pos[0];
		wEventPlane->mNtrk_ran_2_eta_neg   = pico->EventPlane_mNtrk_ran_2_eta_neg[0];
		wEventPlane->mWeight_ran_1         = pico->EventPlane_mWeight_ran_1[0];
		wEventPlane->mWeight_ran_2         = pico->EventPlane_mWeight_ran_2[0];
	}

	virtual void makeCandidateTrack(){
		CandidateTrack * aTrack =  new ((*wTracks)[nCandTracks]) CandidateTrack( );
		nCandTracks ++;
	}

	virtual void fillCandidateTrack( CandidateTrack * aTrack, int iTrack ){
		

		aTrack->mId                 = pico->Tracks_mId[iTrack];
		aTrack->mPMomentum_mX1      = pico->Tracks_mPMomentum_mX1[iTrack];
		aTrack->mPMomentum_mX2      = pico->Tracks_mPMomentum_mX2[iTrack];
		aTrack->mPMomentum_mX3      = pico->Tracks_mPMomentum_mX3[iTrack];

		aTrack->mDedx               = pico->Tracks_mDedx[ iTrack ];
		aTrack->mNHitsFit           = pico->Tracks_mNHitsFit[iTrack];
		aTrack->mNHitsMax           = pico->Tracks_mNHitsMax[iTrack];
		aTrack->mNHitsDedx          = pico->Tracks_mNHitsDedx[iTrack];

		aTrack->mNSigmaPion         = pico->Tracks_mNSigmaPion[ iTrack ];
		aTrack->mNSigmaKaon         = pico->Tracks_mNSigmaKaon[ iTrack ];
		aTrack->mNSigmaProton       = pico->Tracks_mNSigmaProton[ iTrack ];
		aTrack->mNSigmaElectron     = pico->Tracks_mNSigmaElectron[ iTrack ];

		aTrack->mDCA                = pico->mGDCA( iTrack );

		// default out the PidTraits
		aTrack->mBTofPidTraitsIndex = -1;
		aTrack->mMtdPidTraitsIndex  = -1;

		fillCandidateBTofPidTraits( aTrack, iTrack );
		fillCandidateMtdPidTraits( aTrack, iTrack );
		

		// aTrack->species = speciesMask();
	}

	virtual void fillCandidateBTofPidTraits( CandidateTrack * aTrack, int iTrack ){
		// BTofPidTraits
		int iBTof = pico->Tracks_mBTofPidTraitsIndex[ iTrack ];
		if ( iBTof >= 0 && isElectron){
			aTrack->mBTofPidTraitsIndex = nBTofPidTraits;

			CandidateTrackBTofPidTraits * btpid = new ((*wBTofPidTraits)[nBTofPidTraits]) CandidateTrackBTofPidTraits( );
			btpid->mBTofBeta 		= pico->BTofPidTraits_mBTofBeta[ iBTof ];
			btpid->mBTofYLocal 		= pico->BTofPidTraits_mBTofYLocal[ iBTof ];
			btpid->mBTofZLocal 		= pico->BTofPidTraits_mBTofZLocal[ iBTof ];
			btpid->mBTofMatchFlag 	= pico->BTofPidTraits_mBTofMatchFlag[ iBTof ];

			nBTofPidTraits++;
		}
		else {
		}
	}

	virtual void fillCandidateMtdPidTraits( CandidateTrack * aTrack, int iTrack ){
		// MtdPidTraits
		int iMtd = pico->Tracks_mMtdPidTraitsIndex[ iTrack ];
		if ( iMtd >= 0 ){
			aTrack->mMtdPidTraitsIndex = nMtdPidTraits;
			CandidateTrackMtdPidTraits * mtdpid = new ((*wMtdPidTraits)[nMtdPidTraits]) CandidateTrackMtdPidTraits( );

			mtdpid->mMatchFlag 			= pico->MtdPidTraits_mMatchFlag[ iMtd ];
			mtdpid->mDeltaY 			= pico->MtdPidTraits_mDeltaY[ iMtd ];
			mtdpid->mDeltaZ 			= pico->MtdPidTraits_mDeltaZ[ iMtd ];
			mtdpid->mDeltaTimeOfFlight 	= pico->MtdPidTraits_mDeltaTimeOfFlight[ iMtd ];
			mtdpid->mMtdHitChan 		= pico->MtdPidTraits_mMtdHitChan[ iMtd ];

			nMtdPidTraits ++;
		} else {

		}
	}

	protected:
		string outputFilename;
		TFile * output = nullptr;
		shared_ptr<IPicoDst> pico;
};


#endif