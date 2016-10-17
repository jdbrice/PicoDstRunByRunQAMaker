#ifndef CANDIDATE_CSV_FORMATTER_H
#define CANDIDATE_CSV_FORMATTER_H

#include "IObject.h"
using namespace jdb;

#include "Extra/format.h"

#include "CandidateEvent.h"

#include <string>
using namespace std;

class CandidateCSVFormatter : public IObject
{
public:
	CandidateCSVFormatter() {}
	~CandidateCSVFormatter() {}

	static string eventToCSV( CandidateEvent * _event ){
		string eventStr = fmt::format( "{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}",
			_event->mPrimaryVertex_mX1,
			_event->mPrimaryVertex_mX2,
			_event->mPrimaryVertex_mX3,
			_event->mWeight,
			_event->mRunId,
			_event->mEventId,
			_event->mPsi2,
			_event->mTriggerWord,
			_event->mTriggerWordMtd,
			_event->mGRefMult,
			_event->mBin16,
			_event->mRunIndex );
		return eventStr;
	}

	static string trackToCSV( CandidateTrack * _track ){
		string trackStr = fmt::format( "{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}",
			      _track->mPMomentum_mX1,
			      _track->mPMomentum_mX2,
			      _track->mPMomentum_mX3,
			      _track->mId,
			(int) _track->mDedx,
			(int) _track->mNHitsFit,
			(int) _track->mNHitsMax,
			      _track->mNHitsDedx,
			      _track->mNSigmaPion,
			      _track->mNSigmaKaon,
			      _track->mNSigmaProton,
			      _track->mNSigmaElectron,
			      _track->mDCA );
		return trackStr;
	}

	static string mtdPidTraitsToCSV( CandidateTrackMtdPidTraits * _mtdPid ){
		string mtdPidStr = fmt::format("{}, {}, {}, {}, {}",
				      _mtdPid-> mDeltaY,
				      _mtdPid-> mDeltaZ,
				      _mtdPid-> mDeltaTimeOfFlight,
				(int) _mtdPid-> mMatchFlag,
				      _mtdPid-> mMtdHitChan );
		return mtdPidStr;
	}
	
};



#endif