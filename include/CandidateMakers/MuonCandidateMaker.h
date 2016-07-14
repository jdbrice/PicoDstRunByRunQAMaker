#ifndef MUON_CANDIDATE_MAKER_H
#define MUON_CANDIDATE_MAKER_H

// project
#include "CandidateMaker.h"


//RooBarb
#include "CutCollection.h"

#include "TClonesArray.h"
#include "TVector3.h"

class MuonCandidateMaker : public CandidateMaker
{
public:
	virtual const char *classname() const { return "MuonCandidateMaker"; }
	MuonCandidateMaker();
	~MuonCandidateMaker();

	virtual void initialize();

protected:
	CutCollection muonCuts;

	virtual void analyzeEvent();
	virtual bool keepTrack( int iTrack );
	virtual void analyzeCandidateTrack( CandidateTrack * aTrack, int iTrack, int iCandTrack );


};


#endif