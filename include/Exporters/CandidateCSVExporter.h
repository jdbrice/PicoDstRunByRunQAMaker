#ifndef CANDIDATE_CSV_EXPORTER_H
#define CANDIDATE_CSV_EXPORTER_H

#include "CandidateSkimmer.h"

#include <fstream>
#include "Extra/format.h"

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

		// string eventStr = fmt::format(
		// 	"{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}",
		// 	event->mPrimaryVertex_mX1,
		// 	event->mPrimaryVertex_mX2,
		// 	event->mPrimaryVertex_mX3,
		// 	event->mWeight,
		// 	event->mRunId,
		// 	event->mEventId,
		// 	event->mPsi2,
		// 	event->mTriggerWord,
		// 	event->mTriggerWordMtd,
		// 	event->mGRefMult,
		// 	event->mBin16,
		// 	event->mRunIndex );

		string eventStr = fmt::format( "{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}",
			event->mPrimaryVertex_mX1,
			event->mPrimaryVertex_mX2,
			event->mPrimaryVertex_mX3,
			event->mWeight,
			event->mRunId,
			event->mEventId,
			event->mPsi2,
			event->mTriggerWord,
			event->mTriggerWordMtd,
			event->mGRefMult,
			event->mBin16,
			event->mRunIndex );

		// INFO( classname(), eventStr );
		

		int nTracks = tracks->GetEntries();
		for ( int iTrack = 0; iTrack < nTracks; iTrack++ ){
			CandidateTrack* aTrack = (CandidateTrack*)tracks->At( iTrack );
			string trackStr = fmt::format( "{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}",
			aTrack->mPMomentum_mX1,
			aTrack->mPMomentum_mX2,
			aTrack->mPMomentum_mX3,
			aTrack->mId,
			(int)aTrack->mDedx,
			(int)aTrack->mNHitsFit,
			(int)aTrack->mNHitsMax,
			aTrack->mNHitsDedx,
			aTrack->mNSigmaPion,
			aTrack->mNSigmaKaon,
			aTrack->mNSigmaProton,
			aTrack->mNSigmaElectron,
			aTrack->mDCA );


			CandidateTrackMtdPidTraits *mtdPid = (CandidateTrackMtdPidTraits *)mtdPidTraits->At( aTrack->mMtdPidTraitsIndex );

			string mtdPidStr = fmt::format("{}, {}, {}, {}, {}",
				mtdPid->mDeltaY,
				mtdPid->mDeltaZ,
				mtdPid->mDeltaTimeOfFlight,
				(int)mtdPid->mMatchFlag,
				mtdPid->mMtdHitChan );

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