#ifndef ELECTRON_CANDIDATE_MAKER_H
#define ELECTRON_CANDIDATE_MAKER_H

// project
#include "CandidateMaker.h"


//RooBarb
#include "CutCollection.h"

#include "TClonesArray.h"
#include "TVector3.h"

class ElectronCandidateMaker : public CandidateMaker
{
public:
	virtual const char *classname() const { return "ElectronCandidateMaker"; }
	ElectronCandidateMaker();
	~ElectronCandidateMaker();

	virtual void initialize();

protected:
	CutCollection muonCuts;
	CutCollection electronCuts;
	int nElectrons;
	int nMuons;


	virtual void analyzeEvent();
	virtual bool keepTrack( int iTrack );
	virtual void analyzeCandidateTrack( CandidateTrack * aTrack, int iTrack, int iCandTrack );


};


#endif