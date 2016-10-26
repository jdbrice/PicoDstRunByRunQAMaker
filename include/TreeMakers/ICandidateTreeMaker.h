#ifndef ICANDIDATE_TREE_MAKER_H
#define ICANDIDATE_TREE_MAKER_H

#include "CandidateEvent.h"
#include "CandidateEventPlane.h"
#include "CandidateTrack.h"
#include "CandidateTrackBTofPidTraits.h"
#include "CandidateTrackMtdPidTraits.h"
#include "CandidateTrackEmcPidTraits.h"
#include "CandidateTrackHelix.h"

#include "TTree.h"
#include "TClonesArray.h"


class ICandidateTreeMaker
{

protected:

	TTree               * mTree          = nullptr;
	CandidateEvent      * wEvent         = nullptr;
	CandidateEventPlane * wEventPlane    = nullptr;
	TClonesArray        * wTracks        = nullptr;
	TClonesArray        * wBTofPidTraits = nullptr;
	TClonesArray        * wMtdPidTraits  = nullptr;
	TClonesArray        * wTrackHelices  = nullptr;

	bool makeEventPlane    = false;
	bool makeTracks        = false;
	bool makeBTofPidTraits = false;
	bool makeMtdPidTraits  = false;
	bool makeEmcPidTraits  = false;
	bool makeHelices       = false;

	string treeDescription = "Generic";

	Int_t nCandTracks;
	Int_t nBTofPidTraits;
	Int_t nMtdPidTraits;
	Int_t nHelices;
	bool keepCandidateEvent;

	// bool isElectron;
	// bool isMuon;

public:
	ICandidateTreeMaker() {}
	~ICandidateTreeMaker() {}


	void createTree( 
						bool _makeEventPlane = false, 
						bool _makeTracks = false, 
						bool _makeBTofPidTraits = false, 
						bool _makeMtdPidTraits = false, 
						bool _makeEmcPidTraits = false,
						bool _makeHelices = false ){

		// once it has been set to true you can't unset it
		// ie remove the branch after it is made is not possible
		
		makeEventPlane    |= _makeEventPlane;
		makeTracks        |= _makeTracks;
		makeBTofPidTraits |= _makeBTofPidTraits;
		makeMtdPidTraits  |= _makeMtdPidTraits;
		makeEmcPidTraits  |= _makeEmcPidTraits;
		makeHelices       |= _makeHelices;

		// makes it safe to call multiple times
		if ( nullptr == wEvent )
			wEvent = new CandidateEvent();

		if ( nullptr == wEventPlane )
			wEventPlane = new CandidateEventPlane();

		if ( nullptr == wTracks )
			wTracks = new TClonesArray( "CandidateTrack" );
		if ( nullptr == wBTofPidTraits )
			wBTofPidTraits = new TClonesArray( "CandidateTrackBTofPidTraits" );
		
		if ( nullptr == wMtdPidTraits )
			wMtdPidTraits = new TClonesArray( "CandidateTrackMtdPidTraits" );

		if ( nullptr == wTrackHelices )
			wTrackHelices = new TClonesArray( "CandidateTrackHelix" );

		if ( nullptr == mTree )
			mTree = new TTree("FemtoDst", (treeDescription + " Candidates").c_str(), 99);
		
		mTree->Branch( "Event", &wEvent, 256000, 99 );

		if ( makeEventPlane )
			mTree->Branch( "EventPlane", &wEventPlane, 256000, 99 );
		
		if ( makeTracks )
			mTree->Branch( "Tracks", &wTracks, 256000, 99 );
		if ( makeBTofPidTraits )
			mTree->Branch( "BTofPidTraits", &wBTofPidTraits, 256000, 99 );
		if ( makeMtdPidTraits )
			mTree->Branch( "MtdPidTraits", &wMtdPidTraits, 256000, 99 );
		// if ( makeEmcPidTraits )
		// 	mTree->Branch( "EmcPidTraits", &wEmcPidTraits, 256000, 99 );
		if ( makeHelices )
			mTree->Branch( "TrackHelices", &wTrackHelices, 256000, 99 );


	}

	virtual void resetTracks(){
		nCandTracks    = 0;
		nBTofPidTraits = 0;
		nMtdPidTraits  = 0;
		nHelices       = 0;

		wTracks->Clear();
		wBTofPidTraits->Clear();
		wMtdPidTraits->Clear();
		wTrackHelices->Clear();
	}

	virtual void fillCandidateEvent(int runIndex, int bin16, float weight, float psi) = 0;
	virtual void fillCandidateEventPlane() = 0;
	virtual void fillCandidateTrack( CandidateTrack * aTrack, int iTrack ) = 0;
	virtual void fillCandidateBTofPidTraits( CandidateTrack * aTrack, int iTrack ) = 0;
	virtual void fillCandidateMtdPidTraits( CandidateTrack * aTrack, int iTrack ) = 0;
	virtual void fillCandidateEmcPidTraits( CandidateTrack * aTrack, int iTrack ) = 0;
	virtual void fillCandidateTrackHelix( CandidateTrack * aTrack, int iTrack ) = 0;
	
};


#endif