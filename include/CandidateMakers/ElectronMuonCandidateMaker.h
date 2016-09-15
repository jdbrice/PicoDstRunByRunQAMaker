#ifndef ELECTRON_MUON_CANDIDATE_MAKER_H
#define ELECTRON_MUON_CANDIDATE_MAKER_H

// project
#include "CandidateMaker.h"
#include "CandidateTreeMaker.h"


//RooBarb
#include "CutCollection.h"

#include "TClonesArray.h"
#include "TVector3.h"

class ElectronMuonCandidateMaker : public CandidateMaker, public CandidateTreeMaker
{
public:
	virtual const char *classname() const { return "ElectronMuonCandidateMaker"; }
	ElectronMuonCandidateMaker();
	~ElectronMuonCandidateMaker();

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