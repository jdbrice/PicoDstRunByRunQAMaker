#ifndef MIXED_EVENT_TREE_MAKER_H
#define MIXED_EVENT_TREE_MAKER_H

//RooBarb
#include "TreeAnalyzer.h"
#include "CandidateSkimmer.h"
#include "ICandidateTreeMaker.h"

class MixedEventTreeMaker : public TreeAnalyzer, ICandidateTreeMaker
{
public:
	virtual const char* classname() const { return "MixedEventTreeMaker"; }
	MixedEventTreeMaker(){}
	~MixedEventTreeMaker(){}

	virtual void initialize(){
		TreeAnalyzer::initialize();

		chain->SetBranchStatus( "*", 1 );

		rTracks = new TClonesArray( "CandidateTrack" );
		rBtofPidTraits = new TClonesArray( "CandidateTrackBTofPidTraits" );
		rMtdPidTraits = new TClonesArray( "CandidateTrackMtdPidTraits" );

		chain->GetBranch( "Tracks" )->SetAutoDelete( kFALSE );
		chain->GetBranch( "BTofPidTraits" )->SetAutoDelete( kFALSE );
		chain->GetBranch( "MtdPidTraits" )->SetAutoDelete( kFALSE );
		
		chain->SetBranchAddress( "Tracks", &rTracks );
		chain->SetBranchAddress( "BTofPidTraits", &rBtofPidTraits );
		chain->SetBranchAddress( "MtdPidTraits", &rMtdPidTraits );
		chain->SetBranchAddress( "Event", &rEvent );
		chain->SetBranchAddress( "EventPlane", &rEventPlane );


		// setup the output tree
		createTree();
	}


protected:

	// READ
	CandidateEvent *rEvent;
	CandidateEventPlane *rEventPlane;
	TClonesArray *rTracks;
	TClonesArray *rBtofPidTraits;
	TClonesArray *rMtdPidTraits;


	virtual void preEventLoop(){
		TreeAnalyzer::preEventLoop();

		reset();
	}

	virtual void postEventLoop(){
		INFO( classname(), "Filling Tree" );
		TreeAnalyzer::postEventLoop();

		mTree->Fill();
	}

	virtual void analyzeEvent(){

		fillCandidateEvent();
		fillCandidateEventPlane();

		trackLoop();
	}

	CandidateTrack              * currentTrack;
	CandidateTrackBTofPidTraits * currentBTofPidTraits;
	CandidateTrackMtdPidTraits  * currentMtdPidTraits;


	virtual void trackLoop(){
		int nTracks = rTracks->GetEntries();
		for ( int iTrack = 0; iTrack < nTracks; iTrack++ ){
			currentTrack = (CandidateTrack*)rTracks->At( iTrack );
			CandidateTrack * aTrack =  new ((*tracks)[nCandTracks]) CandidateTrack( );

			fillCandidateTrack( aTrack, nCandTracks );
			fillCandidateBTofPidTraits( aTrack, nCandTracks );
			fillCandidateMtdPidTraits( aTrack, nCandTracks );

			nCandTracks++;
		}
	}

	virtual void fillCandidateEvent(){
		event->copy( rEvent );
	}
	virtual void fillCandidateEventPlane(){
		eventPlane->copy( rEventPlane );
	}
	virtual void fillCandidateTrack( CandidateTrack * aTrack, int iTrack ){
		aTrack->copy( currentTrack );
	}
	virtual void fillCandidateBTofPidTraits( CandidateTrack * aTrack, int iTrack ) {
		// BTofPidTraits
		int iBTof = currentTrack->mBTofPidTraitsIndex;//pico->Tracks_mBTofPidTraitsIndex[ iTrack ];
		if ( iBTof >= 0 ){
			CandidateTrackBTofPidTraits *rbtpid = (CandidateTrackBTofPidTraits*)rBtofPidTraits->At( ( iBTof ) );
			aTrack->mBTofPidTraitsIndex = nBTofPidTraits;

			CandidateTrackBTofPidTraits * btpid = new ((*btofPidTraits)[nBTofPidTraits]) CandidateTrackBTofPidTraits( );
			btpid->copy( rbtpid );
			nBTofPidTraits++;
		}
		else {
			aTrack->mBTofPidTraitsIndex = -1;
		}
	}
	virtual void fillCandidateMtdPidTraits( CandidateTrack * aTrack, int iTrack ) {
		// BTofPidTraits
		int iMtd = currentTrack->mMtdPidTraitsIndex;//pico->Tracks_mBTofPidTraitsIndex[ iTrack ];
		if ( iMtd >= 0 ){
			CandidateTrackMtdPidTraits *rmtdpid = (CandidateTrackMtdPidTraits*)rMtdPidTraits->At( ( iMtd ) );
			aTrack->mMtdPidTraitsIndex = nMtdPidTraits;

			CandidateTrackMtdPidTraits * mtdpid = new ((*mtdPidTraits)[nMtdPidTraits]) CandidateTrackMtdPidTraits( );
			mtdpid->copy( rmtdpid );
			nMtdPidTraits++;
		}
		else {
			aTrack->mMtdPidTraitsIndex = -1;
		}
	}

};

#endif