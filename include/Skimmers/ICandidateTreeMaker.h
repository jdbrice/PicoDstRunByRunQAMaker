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

	TTree               * mTree         = nullptr;
	CandidateEvent      * event         = nullptr;
	CandidateEventPlane * eventPlane    = nullptr;
	TClonesArray        * tracks        = nullptr;
	TClonesArray        * btofPidTraits = nullptr;
	TClonesArray        * mtdPidTraits  = nullptr;

	bool makeEventPlane    = false;
	bool makeTracks        = false;
	bool makeBTofPidTraits = false;
	bool makeMtdPidTraits  = false;
	bool makeEmcPidTraits  = false;

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


	void createTree( bool _makeEventPlane = false, bool _makeTracks = false, bool _makeBTofPidTraits = false, bool _makeMtdPidTraits = false, bool _makeEmcPidTraits = false){

		// once it has been set to true you can't unset it
		// ie remove the branch after it is made is not possible
		
		makeEventPlane    |= _makeEventPlane;
		makeTracks        |= _makeTracks;
		makeBTofPidTraits |= _makeBTofPidTraits;
		makeMtdPidTraits  |= _makeMtdPidTraits;
		makeEmcPidTraits  |= _makeEmcPidTraits;

		// makes it safe to call multiple times
		if ( nullptr == event )
			event = new CandidateEvent();

		if ( nullptr == eventPlane )
		eventPlane = new CandidateEventPlane();

		if ( nullptr == tracks )
			tracks = new TClonesArray( "CandidateTrack" );
		if ( nullptr == btofPidTraits )
			btofPidTraits = new TClonesArray( "CandidateTrackBTofPidTraits" );
		
		if ( nullptr == mtdPidTraits )
			mtdPidTraits = new TClonesArray( "CandidateTrackMtdPidTraits" );

		if ( nullptr == mTree )
			mTree = new TTree("FemtoDst", (treeDescription + " Candidates").c_str(), 99);
		
		mTree->Branch( "Event", &event, 256000, 99 );

		if ( makeEventPlane )
			mTree->Branch( "EventPlane", &eventPlane, 256000, 99 );
		
		if ( makeTracks )
			mTree->Branch( "Tracks", &tracks, 256000, 99 );
		if ( makeBTofPidTraits )
			mTree->Branch( "BTofPidTraits", &btofPidTraits, 256000, 99 );
		if ( makeMtdPidTraits )
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