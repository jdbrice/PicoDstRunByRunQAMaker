#ifndef ICANDIDATE_PAIR_TREE_MAKER_H
#define ICANDIDATE_PAIR_TREE_MAKER_H

#include "CandidatePair.h"


#include "TTree.h"
#include "TClonesArray.h"
#include "TLorentzVector.h"


class ISameEventPairTreeMaker
{

protected:

	TTree               * mSameEventTree = nullptr;
	CandidateEvent      * wEvent         = nullptr;
	TClonesArray        * wPairs         = nullptr;
	TClonesArray        * wTracks        = nullptr;
	TClonesArray        * wMtdPidTraits  = nullptr;
	Long64_t              wEventHash     = -1;
	string treeDescription               = "GenericPairs";

	Int_t nCandPairs;

public:
	ISameEventPairTreeMaker() {}
	~ISameEventPairTreeMaker() {}


	void createSameEventPairTree( string treeDescription ){

		if ( nullptr == mSameEventTree )
			mSameEventTree = new TTree("FemtoDst", (treeDescription + " Candidates").c_str(), 99);

		if ( nullptr == wPairs )
			wPairs = new TClonesArray( "CandidatePair" );
		mSameEventTree->Branch( "Event", &wEvent, 256000, 99 );
		mSameEventTree->Branch( "Pairs", &wPairs, 256000, 99 );
		mSameEventTree->Branch( "mEventHash", &wEventHash, "mEventHash/L" );
	}

	virtual void resetPairs(){
		nCandPairs    = 0;
		wPairs->Clear();
	}

	virtual void fillCandidatePair( CandidateTrack* aTrack, CandidateTrack* bTrack ) = 0;
};


#endif