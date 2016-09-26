#ifndef IMIXED_EVENT_TREE_MAKER_H
#define IMIXED_EVENT_TREE_MAKER_H

#include "CandidatePair.h"


#include "TTree.h"
#include "TClonesArray.h"
#include "TLorentzVector.h"


class IMixedEventPairTreeMaker
{

protected:

	TTree               * mMixedEventTree = nullptr;
	CandidatePair       * wPairs          = nullptr;
	CandidateEvent      * wEvent1         = nullptr; // event 1 -> daugther 1
	CandidateEvent      * wEvent2         = nullptr; // event 2 -> daughter 2
	Long64_t              wEventHash      = -1;

	string treeDescription = "GenericPairs";

public:
	IMixedEventPairTreeMaker() {}
	~IMixedEventPairTreeMaker() {}


	void createMixedEventPairTree( string treeDescription ){

		if ( nullptr == mMixedEventTree )
			mMixedEventTree = new TTree("FemtoDst", (treeDescription + " Candidates").c_str(), 99);

		
		wPairs = new CandidatePair( );
		
		// mMixedEventTree->Branch( "Event1", &wEvent1, 256000 );
		// mMixedEventTree->Branch( "Event2", &wEvent2, 256000 );
		mMixedEventTree->Branch( "Pairs", &wPairs, 256000 );
		mMixedEventTree->Branch( "mEventHash", &wEventHash, "mEventHash/L" );
	}

	virtual void fillCandidatePair( shared_ptr<Candidate> _cand1, shared_ptr<Candidate> _cand2 ) = 0;
};


#endif