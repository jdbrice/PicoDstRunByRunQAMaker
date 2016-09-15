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

	void createFile( string _filename ){
		outputFilename = _filename;
		INFO( classname(), "[output] " << _filename  );
		output = new TFile( outputFilename.c_str(), "RECREATE" );
		output->cd();
		isFileOpen = true;
	}

	void setPicoDst( shared_ptr<IPicoDst> _pico ){
		mPico = _pico;
	}

	void close(){
		if ( nullptr == output )  return;
		output->cd();
		mTree->Write();
		output->close();
		output = nullptr;
		isFileOpen = false;
	}

	void reopen( ) {
		if ( isFileOpen && output != nullptr ) return;
		output = new TFile( outputFilename.c_str(), "UPDATE" );
		output->cd();
		isFileOpen = true;
	}

	virtual void fillCandidateEvent( int runIndex, int bin16, float weight, float psi ){
		CandidateTreeMaker::fillCandidateEvent( mPico, wEvent, runIndex, bin16, weight, psi) ;
	}

	static void fillCandidateEvent( shared_ptr<IPicoDst> _pico, CandidateEvent *event, int runIndex, int bin16, float weight, float psi ) {
		if ( nullptr == _pico ) return;
		event->mRunId 				= _pico->Event_mRunId[0];
		event->mEventId 			= _pico->Event_mEventId[0];
		event->mGRefMult 			= _pico->Event_mGRefMult[0];
		event->mTriggerWord 		= _pico->Event_mTriggerWord[0];
		event->mTriggerWordMtd 		= _pico->Event_mTriggerWordMtd[0];
		event->mPrimaryVertex_mX1 	= _pico->vx();
		event->mPrimaryVertex_mX2 	= _pico->vy();
		event->mPrimaryVertex_mX3 	= _pico->vz();
		event->mRunIndex			= runIndex;
		event->mBin16 				= bin16;
		event->mWeight 				= weight;
		event->mPsi2 				= (psi * 10000) ;
		
	}

	virtual void fillCandidateEventPlane(){
		if ( nullptr == mPico ) return;
		wEventPlane->mQx_eta_pos           = mPico->EventPlane_mQx_eta_pos[0];
		wEventPlane->mQy_eta_pos           = mPico->EventPlane_mQy_eta_pos[0];
		wEventPlane->mQx_eta_neg           = mPico->EventPlane_mQx_eta_neg[0];
		wEventPlane->mQy_eta_neg           = mPico->EventPlane_mQy_eta_neg[0];
		wEventPlane->mNtrk_eta_pos         = mPico->EventPlane_mNtrk_eta_pos[0];
		wEventPlane->mNtrk_eta_neg         = mPico->EventPlane_mNtrk_eta_neg[0];
		wEventPlane->mWeight_eta_pos       = mPico->EventPlane_mWeight_eta_pos[0];
		wEventPlane->mWeight_eta_neg       = mPico->EventPlane_mWeight_eta_neg[0];
		wEventPlane->mQx_chg_pos           = mPico->EventPlane_mQx_chg_pos[0];
		wEventPlane->mQy_chg_pos           = mPico->EventPlane_mQy_chg_pos[0];
		wEventPlane->mQx_chg_neg           = mPico->EventPlane_mQx_chg_neg[0];
		wEventPlane->mQy_chg_neg           = mPico->EventPlane_mQy_chg_neg[0];
		wEventPlane->mNtrk_chg_pos_eta_pos = mPico->EventPlane_mNtrk_chg_pos_eta_pos[0];
		wEventPlane->mNtrk_chg_pos_eta_neg = mPico->EventPlane_mNtrk_chg_pos_eta_neg[0];
		wEventPlane->mNtrk_chg_neg_eta_pos = mPico->EventPlane_mNtrk_chg_neg_eta_pos[0];
		wEventPlane->mNtrk_chg_neg_eta_neg = mPico->EventPlane_mNtrk_chg_neg_eta_neg[0];
		wEventPlane->mWeight_chg_pos       = mPico->EventPlane_mWeight_chg_pos[0];
		wEventPlane->mWeight_chg_neg       = mPico->EventPlane_mWeight_chg_neg[0];
		wEventPlane->mQx_ran_1             = mPico->EventPlane_mQx_ran_1[0];
		wEventPlane->mQy_ran_1             = mPico->EventPlane_mQy_ran_1[0];
		wEventPlane->mQx_ran_2             = mPico->EventPlane_mQx_ran_2[0];
		wEventPlane->mQy_ran_2             = mPico->EventPlane_mQy_ran_2[0];
		wEventPlane->mNtrk_ran_1_eta_pos   = mPico->EventPlane_mNtrk_ran_1_eta_pos[0];
		wEventPlane->mNtrk_ran_1_eta_neg   = mPico->EventPlane_mNtrk_ran_1_eta_neg[0];
		wEventPlane->mNtrk_ran_2_eta_pos   = mPico->EventPlane_mNtrk_ran_2_eta_pos[0];
		wEventPlane->mNtrk_ran_2_eta_neg   = mPico->EventPlane_mNtrk_ran_2_eta_neg[0];
		wEventPlane->mWeight_ran_1         = mPico->EventPlane_mWeight_ran_1[0];
		wEventPlane->mWeight_ran_2         = mPico->EventPlane_mWeight_ran_2[0];
	}

	CandidateTrack* makeCandidateTrack(){
		CandidateTrack * aTrack =  new ((*wTracks)[nCandTracks]) CandidateTrack( );
		nCandTracks ++;
		return aTrack;
	}

	virtual void fillCandidateTrack( CandidateTrack * aTrack, int iTrack ){
		

		aTrack->mId                 = mPico->Tracks_mId[iTrack];
		aTrack->mPMomentum_mX1      = mPico->Tracks_mPMomentum_mX1[iTrack];
		aTrack->mPMomentum_mX2      = mPico->Tracks_mPMomentum_mX2[iTrack];
		aTrack->mPMomentum_mX3      = mPico->Tracks_mPMomentum_mX3[iTrack];

		aTrack->mDedx               = mPico->Tracks_mDedx[ iTrack ];
		aTrack->mNHitsFit           = mPico->Tracks_mNHitsFit[iTrack];
		aTrack->mNHitsMax           = mPico->Tracks_mNHitsMax[iTrack];
		aTrack->mNHitsDedx          = mPico->Tracks_mNHitsDedx[iTrack];

		aTrack->mNSigmaPion         = mPico->Tracks_mNSigmaPion[ iTrack ];
		aTrack->mNSigmaKaon         = mPico->Tracks_mNSigmaKaon[ iTrack ];
		aTrack->mNSigmaProton       = mPico->Tracks_mNSigmaProton[ iTrack ];
		aTrack->mNSigmaElectron     = mPico->Tracks_mNSigmaElectron[ iTrack ];

		aTrack->mDCA                = mPico->mGDCA( iTrack );

		// default out the PidTraits
		aTrack->mBTofPidTraitsIndex = -1;
		aTrack->mMtdPidTraitsIndex  = -1;

		fillCandidateBTofPidTraits( aTrack, iTrack );
		fillCandidateMtdPidTraits( aTrack, iTrack );
		

		// aTrack->species = speciesMask();
	}

	virtual void fillCandidateBTofPidTraits( CandidateTrack * aTrack, int iTrack ){
		// BTofPidTraits
		int iBTof = mPico->Tracks_mBTofPidTraitsIndex[ iTrack ];
		if ( iBTof >= 0 ){
			aTrack->mBTofPidTraitsIndex = nBTofPidTraits;

			CandidateTrackBTofPidTraits * btpid = new ((*wBTofPidTraits)[nBTofPidTraits]) CandidateTrackBTofPidTraits( );
			btpid->mBTofBeta 		= mPico->BTofPidTraits_mBTofBeta[ iBTof ];
			btpid->mBTofYLocal 		= mPico->BTofPidTraits_mBTofYLocal[ iBTof ];
			btpid->mBTofZLocal 		= mPico->BTofPidTraits_mBTofZLocal[ iBTof ];
			btpid->mBTofMatchFlag 	= mPico->BTofPidTraits_mBTofMatchFlag[ iBTof ];

			nBTofPidTraits++;
		}
		else {
		}
	}

	virtual void fillCandidateMtdPidTraits( CandidateTrack * aTrack, int iTrack ){
		// MtdPidTraits
		int iMtd = mPico->Tracks_mMtdPidTraitsIndex[ iTrack ];
		if ( iMtd >= 0 ){
			aTrack->mMtdPidTraitsIndex = nMtdPidTraits;
			CandidateTrackMtdPidTraits * mtdpid = new ((*wMtdPidTraits)[nMtdPidTraits]) CandidateTrackMtdPidTraits( );

			mtdpid->mMatchFlag 			= mPico->MtdPidTraits_mMatchFlag[ iMtd ];
			mtdpid->mDeltaY 			= mPico->MtdPidTraits_mDeltaY[ iMtd ];
			mtdpid->mDeltaZ 			= mPico->MtdPidTraits_mDeltaZ[ iMtd ];
			mtdpid->mDeltaTimeOfFlight 	= mPico->MtdPidTraits_mDeltaTimeOfFlight[ iMtd ];
			mtdpid->mMtdHitChan 		= mPico->MtdPidTraits_mMtdHitChan[ iMtd ];

			nMtdPidTraits ++;
		} else {

		}
	}

	virtual void fillTree(){
		if ( output ){
			if ( keepCandidateEvent ){
				output->cd();
				mTree->Fill();
			}
		} else {
			ERROR( classname(), "NO Output" );
		}
	}


	void keepEvent( bool kce ){
		keepCandidateEvent = kce;
	}

	int numberOfTracks(){
		return nCandTracks;
	}

	protected:
		string outputFilename;
		TFile * output = nullptr;
		shared_ptr<IPicoDst> mPico;
		bool isFileOpen = false;
};


#endif