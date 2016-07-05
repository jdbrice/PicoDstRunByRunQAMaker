#ifndef ICANDIDATE_TREE_MAKER_H
#define ICANDIDATE_TREE_MAKER_H

#include "CandidateEvent.h"
#include "CandidateEventPlane.h"
#include "CandidateTrack.h"
#include "CandidateTrackBTofPidTraits.h"
#include "CandidateTrackMtdPidTraits.h"

#include "TTree.h"
#include "TClonesArray.h"


class ICandidateTreeMaker
{

protected:

	TTree * mTree;
	CandidateEvent * event;
	CandidateEventPlane * eventPlane;
	TClonesArray * tracks;
	TClonesArray * btofPidTraits;
	TClonesArray * mtdPidTraits;

	string treeDescription = "Generic";

	Int_t nCandTracks;
	Int_t nBTofPidTraits;
	Int_t nMtdPidTraits;
	bool keepCandidateEvent;

	bool isElectron;
	bool isMuon;

public:
	ICandidateTreeMaker() {}
	~ICandidateTreeMaker() {}


	void createTree( bool _eventPlane = true, bool _btofPidTraits = true, bool _mtdPidTraits = true, bool _emcPidTraits = true ){

		event = new CandidateEvent();
		eventPlane = new CandidateEventPlane();
		tracks = new TClonesArray( "CandidateTrack" );
		btofPidTraits = new TClonesArray( "CandidateTrackBTofPidTraits" );
		mtdPidTraits = new TClonesArray( "CandidateTrackMtdPidTraits" );

		mTree = new TTree("FemtoDst", (treeDescription + " Candidates").c_str(), 99);
		mTree->Branch( "Event", &event, 256000, 99 );
		if ( _eventPlane )
			mTree->Branch( "EventPlane", &eventPlane, 256000, 99 );
		mTree->Branch( "Tracks", &tracks, 256000, 99 );

		if ( _btofPidTraits )
			mTree->Branch( "BTofPidTraits", &btofPidTraits, 256000, 99 );
		if ( _mtdPidTraits )
			mTree->Branch( "MtdPidTraits", &mtdPidTraits, 256000, 99 );
	}

	virtual void reset(){
		nCandTracks    = 0;
		nBTofPidTraits = 0;
		nMtdPidTraits  = 0;

		tracks->Clear();
		btofPidTraits->Clear();
		mtdPidTraits->Clear();


	}

	virtual void fillCandidateEvent() = 0;
	virtual void fillCandidateEventPlane() = 0;
	virtual void fillCandidateTrack( CandidateTrack * aTrack, int iTrack ) = 0;
	virtual void fillCandidateBTofPidTraits( CandidateTrack * aTrack, int iTrack ) = 0;
	virtual void fillCandidateMtdPidTraits( CandidateTrack * aTrack, int iTrack ) = 0;
	
};


#endif