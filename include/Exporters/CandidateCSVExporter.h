#ifndef CANDIDATE_CSV_EXPORTER_H
#define CANDIDATE_CSV_EXPORTER_H

#include "CandidateSkimmer.h"

#include <fstream>
#include "CandidateCSVFormatter.h"

class CandidateCSVExporter : public CandidateSkimmer
{
public:
	virtual const char* classname() const { return "CandidateCSVExporter"; }
	CandidateCSVExporter() {}
	~CandidateCSVExporter() {}

	virtual void initialize(){
		CandidateSkimmer::initialize();

		csvFile.open( "cands.csv" );
	}


	virtual void analyzeEvent(){
		string eventStr = CandidateCSVFormatter::eventToCSV( event );

		int nTracks = tracks->GetEntries();
		for ( int iTrack = 0; iTrack < nTracks; iTrack++ ){
			CandidateTrack* aTrack = (CandidateTrack*)tracks->At( iTrack );
			string trackStr = CandidateCSVFormatter::trackToCSV( aTrack );

			CandidateTrackMtdPidTraits *mtdPid = (CandidateTrackMtdPidTraits *)mtdPidTraits->At( aTrack->mMtdPidTraitsIndex );

			string mtdPidStr = CandidateCSVFormatter::mtdPidTraitsToCSV( mtdPid );
			csvFile << eventStr << ", " << trackStr << ", " << mtdPidStr << "\n";
		}
	}

	virtual void postMake(){
		csvFile.close();
	}

protected:
	ofstream csvFile;
};

#endif