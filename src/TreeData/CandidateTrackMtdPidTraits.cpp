#include "CandidateTrackMtdPidTraits.h"

#include <string>
#include "Utils.h"

using namespace std;
string CandidateTrackMtdPidTraits::print(){
	string msg = "";

	msg += "mDeltaY = "            + ts(mDeltaY)            + "\n";
	msg += "mDeltaZ = "            + ts(mDeltaZ)            + "\n";
	msg += "mDeltaTimeOfFlight = " + ts(mDeltaTimeOfFlight) + "\n";
	msg += "mMatchFlag = "         + ts(mMatchFlag)         + "\n";
	msg += "mMtdHitChan = "        + ts(mMtdHitChan)        + "\n";
	msg += "mTriggerFlag = "       + ts(mTriggerFlag)       + "\n";

	return msg;
}