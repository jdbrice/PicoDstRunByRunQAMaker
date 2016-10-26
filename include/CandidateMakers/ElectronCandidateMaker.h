#ifndef ELECTRON_CANDIDATE_MAKER_H
#define ELECTRON_CANDIDATE_MAKER_H

// project
#include "CandidateMaker.h"
#include "CandidateTreeMaker.h"

//RooBarb
#include "CutCollection.h"

#include "TClonesArray.h"
#include "TVector3.h"

class ElectronCandidateMaker : public CandidateMaker, public CandidateTreeMaker
{
public:
	virtual const char *classname() const { return "ElectronCandidateMaker"; }
	ElectronCandidateMaker();
	~ElectronCandidateMaker();

	virtual void initialize();

protected:
	CutCollection electronCuts;
	int nElectrons = 0;
	
	virtual void makeTree( shared_ptr<CandidateTreeMaker> _tree ){
		_tree->createTree( 
				false, // EventPlane branch
				true,  // Tracks
				true, // bTof
				false,  // MTD
				false, // EMC
				true
				 );
	}
	virtual void analyzeEvent();
	virtual bool keepTrack( int iTrack );
	virtual void analyzeCandidateTrack( CandidateTrack * aTrack, int iTrack );

};


#endif