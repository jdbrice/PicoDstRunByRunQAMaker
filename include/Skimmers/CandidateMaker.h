#ifndef CANDIDATE_MAKER_H
#define CANDIDATE_MAKER_H

//Project
#include "PicoDstSkimmer.h"
#include "CandidateEvent.h"
#include "CandidateEventPlane.h"
#include "CandidateTrack.h"
#include "CandidateTrackBTofPidTraits.h"
#include "CandidateTrackMtdPidTraits.h"

#include "StRefMultCorr.h"
#include "CentralityMaker.h"

//ROOT
#include "TClonesArray.h"
#include "TVector3.h"

class CandidateMaker : public PicoDstSkimmer
{
public:
	virtual const char *classname() const { return "CandidateMaker"; }
	CandidateMaker() {}
	~CandidateMaker() {}

	virtual void initialize(){
		INFO( classname(), "" );
		PicoDstSkimmer::initialize();

		event = new CandidateEvent();
		eventPlane = new CandidateEventPlane();
		tracks = new TClonesArray( "CandidateTrack" );
		btofPidTraits = new TClonesArray( "CandidateTrackBTofPidTraits" );
		mtdPidTraits = new TClonesArray( "CandidateTrackMtdPidTraits" );
		
		createTree();

		if ( config.getBool( nodePath + ":rmc", true ) )
			rmc = CentralityMaker::instance()->getgRefMultCorr();
	}


protected:
	StRefMultCorr * rmc;
	string treeDescription = "Generic";
	TTree * mTree;
	Int_t nCandTracks;
	Int_t nBTofPidTraits;
	Int_t nMtdPidTraits;
	bool keepEvent;

	bool isElectron;
	bool isMuon;
	
	CandidateEvent * event;
	CandidateEventPlane * eventPlane;
	TClonesArray * tracks;
	TClonesArray * btofPidTraits;
	TClonesArray * mtdPidTraits;

	void createTree(){
		mTree = new TTree("FemtoDst", (treeDescription + " Candidates").c_str(), 99);
		mTree->Branch( "Event", &event, 256000, 99 );
		mTree->Branch( "EventPlane", &eventPlane, 256000, 99 );
		mTree->Branch( "Tracks", &tracks, 256000, 99 );

		mTree->Branch( "BTofPidTraits", &btofPidTraits, 256000, 99 );
		mTree->Branch( "MtdPidTraits", &mtdPidTraits, 256000, 99 );
	}

	virtual void analyzeEvent(){

		/*********** Initialize the RefMultCorr *************/
		if ( config.getBool( nodePath + ":rmc", true ) ){
			rmc->init( pico->Event_mRunId[0] );
			rmc->initEvent( 
				pico->Event_mGRefMult[0], 
				pico->Event_mPrimaryVertex_mX3[0], 
				pico->Event_mZDCx[0]
			);
		}

		// set the event level items
		fillEvent();

		fillEventPlane();

		// for instance, use to keep only events with pairs of muons
		// default to keep all accepted events
		keepEvent = true;
		// and default the track level
		isMuon = false;
		isElectron = false;
	}

	virtual void fillEvent() {
		event->mRunId 		= pico->Event_mRunId[0];
		event->mEventId 	= pico->Event_mEventId[0];
		event->mTriggerWord = pico->Event_mTriggerWord[0];
		event->mTriggerWordMtd = pico->Event_mTriggerWordMtd[0];

		// TODO: after EventPlane is settled
		event->mPsi2 		= 0;

		// StRefMultCorr
	}

	virtual void fillEventPlane(){
		eventPlane->mQx_eta_pos = pico->EventPlane_mQx_eta_pos[0];
		eventPlane->mQy_eta_pos = pico->EventPlane_mQy_eta_pos[0];
		eventPlane->mQx_eta_neg = pico->EventPlane_mQx_eta_neg[0];
		eventPlane->mQy_eta_neg = pico->EventPlane_mQy_eta_neg[0];
		eventPlane->mNtrk_eta_pos = pico->EventPlane_mNtrk_eta_pos[0];
		eventPlane->mNtrk_eta_neg = pico->EventPlane_mNtrk_eta_neg[0];
		eventPlane->mWeight_eta_pos = pico->EventPlane_mWeight_eta_pos[0];
		eventPlane->mWeight_eta_neg = pico->EventPlane_mWeight_eta_neg[0];
		eventPlane->mQx_chg_pos = pico->EventPlane_mQx_chg_pos[0];
		eventPlane->mQy_chg_pos = pico->EventPlane_mQy_chg_pos[0];
		eventPlane->mQx_chg_neg = pico->EventPlane_mQx_chg_neg[0];
		eventPlane->mQy_chg_neg = pico->EventPlane_mQy_chg_neg[0];
		eventPlane->mNtrk_chg_pos_eta_pos = pico->EventPlane_mNtrk_chg_pos_eta_pos[0];
		eventPlane->mNtrk_chg_pos_eta_neg = pico->EventPlane_mNtrk_chg_pos_eta_neg[0];
		eventPlane->mNtrk_chg_neg_eta_pos = pico->EventPlane_mNtrk_chg_neg_eta_pos[0];
		eventPlane->mNtrk_chg_neg_eta_neg = pico->EventPlane_mNtrk_chg_neg_eta_neg[0];
		eventPlane->mWeight_chg_pos = pico->EventPlane_mWeight_chg_pos[0];
		eventPlane->mWeight_chg_neg = pico->EventPlane_mWeight_chg_neg[0];
		eventPlane->mQx_ran_1 = pico->EventPlane_mQx_ran_1[0];
		eventPlane->mQy_ran_1 = pico->EventPlane_mQy_ran_1[0];
		eventPlane->mQx_ran_2 = pico->EventPlane_mQx_ran_2[0];
		eventPlane->mQy_ran_2 = pico->EventPlane_mQy_ran_2[0];
		eventPlane->mNtrk_ran_1_eta_pos = pico->EventPlane_mNtrk_ran_1_eta_pos[0];
		eventPlane->mNtrk_ran_1_eta_neg = pico->EventPlane_mNtrk_ran_1_eta_neg[0];
		eventPlane->mNtrk_ran_2_eta_pos = pico->EventPlane_mNtrk_ran_2_eta_pos[0];
		eventPlane->mNtrk_ran_2_eta_neg = pico->EventPlane_mNtrk_ran_2_eta_neg[0];
		eventPlane->mWeight_ran_1 = pico->EventPlane_mWeight_ran_1[0];
		eventPlane->mWeight_ran_2 = pico->EventPlane_mWeight_ran_2[0];
	}

	virtual void trackLoop(){
		// counters
		nCandTracks = 0;
		nBTofPidTraits = 0;
		nMtdPidTraits = 0;

		// Clear TClones Arrays
		tracks->Clear();
		btofPidTraits->Clear();
		mtdPidTraits->Clear();

		for ( int iTrack = 0; iTrack < pico->Tracks_; iTrack++ ){

			if ( !keepTrack( iTrack ) ) continue;

			CandidateTrack * aTrack =  new ((*tracks)[nCandTracks]) CandidateTrack( );
			analyzeCandidateTrack( aTrack, iTrack, nCandTracks );
			nCandTracks ++;
		}

		if ( keepEvent )
			mTree->Fill();
	}

	virtual void fillCandidateTrack( CandidateTrack * aTrack, int iTrack ){
		

		aTrack->pX = pico->Tracks_mPMomentum_mX1[iTrack];
		aTrack->pY = pico->Tracks_mPMomentum_mX2[iTrack];
		aTrack->pZ = pico->Tracks_mPMomentum_mX3[iTrack];

		aTrack->mDedx = pico->Tracks_mDedx[ iTrack ];
		aTrack->mNHitsFit = pico->Tracks_mNHitsFit[iTrack];
		aTrack->mNHitsMax = pico->Tracks_mNHitsMax[iTrack];
		aTrack->mNHitsDedx = pico->Tracks_mNHitsDedx[iTrack];

		aTrack->mNSigmaPion = pico->Tracks_mNSigmaPion[ iTrack ];
		aTrack->mNSigmaKaon = pico->Tracks_mNSigmaKaon[ iTrack ];
		aTrack->mNSigmaProton = pico->Tracks_mNSigmaProton[ iTrack ];
		aTrack->mNSigmaElectron = pico->Tracks_mNSigmaElectron[ iTrack ];

		// default out the PidTraits
		aTrack->mBTofPidTraitsIndex = -1; 
		aTrack->mMtdPidTraitsIndex = -1;

		fillBTofPidTraits( aTrack, iTrack );
		fillMtdPidTraits( aTrack, iTrack );
		

		// aTrack->species = speciesMask();
	}

	virtual void fillBTofPidTraits( CandidateTrack * aTrack, int iTrack ){
		// BTofPidTraits
		int iBTof = pico->Tracks_mBTofPidTraitsIndex[ iTrack ];
		if ( iBTof >= 0 && isElectron){
			aTrack->mBTofPidTraitsIndex = nBTofPidTraits;

			CandidateTrackBTofPidTraits * btpid = new ((*btofPidTraits)[nBTofPidTraits]) CandidateTrackBTofPidTraits( );
			btpid->mBTofBeta 		= pico->BTofPidTraits_mBTofBeta[ iBTof ];
			btpid->mBTofYLocal 		= pico->BTofPidTraits_mBTofYLocal[ iBTof ];
			btpid->mBTofZLocal 		= pico->BTofPidTraits_mBTofZLocal[ iBTof ];
			btpid->mBTofMatchFlag 	= pico->BTofPidTraits_mBTofMatchFlag[ iBTof ];

			nBTofPidTraits++;
		}
		else {
		}
	}

	virtual void fillMtdPidTraits( CandidateTrack * aTrack, int iTrack ){
		// MtdPidTraits
		int iMtd = pico->Tracks_mMtdPidTraitsIndex[ iTrack ];
		if ( iMtd >= 0 ){
			aTrack->mMtdPidTraitsIndex = nMtdPidTraits;
			CandidateTrackMtdPidTraits * mtdpid = new ((*mtdPidTraits)[nMtdPidTraits]) CandidateTrackMtdPidTraits( );

			mtdpid->mMatchFlag 	= pico->MtdPidTraits_mMatchFlag[ iMtd ];
			mtdpid->mDeltaY 	= pico->MtdPidTraits_mDeltaY[ iMtd ];
			mtdpid->mDeltaZ 	= pico->MtdPidTraits_mDeltaZ[ iMtd ];
			mtdpid->mDeltaTimeOfFlight = pico->MtdPidTraits_mDeltaTimeOfFlight[ iMtd ];
			mtdpid->mMtdHitChan = pico->MtdPidTraits_mMtdHitChan[ iMtd ];

			nMtdPidTraits ++;
		} else {

		}
	}


	virtual void analyzeCandidateTrack( CandidateTrack * aTrack, int iTrack, int nCandTracks ){
		fillCandidateTrack( aTrack, iTrack );
	}
	virtual bool keepTrack( int iTrack ){
		return true;
	}

	Char_t speciesMask( ){
		Char_t mask = 0;
		if ( isElectron )
			mask |= 1;
		if ( isMuon )
			mask |= 2;
		return mask;
	}
	
};


#endif