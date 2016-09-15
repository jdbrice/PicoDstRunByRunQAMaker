#ifndef ICANDIDATE_PAIR_TREE_MAKER_H
#define ICANDIDATE_PAIR_TREE_MAKER_H

#include "CandidatePair.h"


#include "TTree.h"
#include "TClonesArray.h"
#include "TLorentzVector.h"


class ICandidatePairTreeMaker
{

protected:

	TTree               * mPairTree          = nullptr;
	TClonesArray        * wPairs             = nullptr;
	CandidateEvent      * wEvent         = nullptr;

	string treeDescription = "GenericPairs";

	Int_t nCandPairs;

public:
	ICandidatePairTreeMaker() {}
	~ICandidatePairTreeMaker() {}


	void createPairTree( string treeDescription ){

		if ( nullptr == mPairTree )
			mPairTree = new TTree("FemtoDst", (treeDescription + " Candidates").c_str(), 99);

		if ( nullptr == wPairs )
			wPairs = new TClonesArray( "CandidatePair" );
		mPairTree->Branch( "Event", &wEvent, 256000, 99 );
		mPairTree->Branch( "Pairs", &wPairs, 256000, 99 );
	}

	virtual void resetPairs(){
		nCandPairs    = 0;
		wPairs->Clear();
	}

	virtual void fillCandidatePair( CandidateTrack* aTrack, CandidateTrack* bTrack ) = 0;
};


#endif