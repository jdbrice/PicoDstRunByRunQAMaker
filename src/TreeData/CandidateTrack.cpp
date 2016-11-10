#include "CandidateTrack.h"
#include "Utils.h"

std::string CandidateTrack::print(){
	std::string msg = "";
	msg += "mPMomentum_mX1 = "      + ts(mPMomentum_mX1)      + "\n";
	msg += "mPMomentum_mX2 = "      + ts(mPMomentum_mX2)      + "\n";
	msg += "mPMomentum_mX3 = "      + ts(mPMomentum_mX3)      + "\n";
	msg += "mId = "                 + ts(mId)                 + "\n";
	msg += "mDedx = "               + ts(mDedx)               + "\n";
	msg += "mNHitsFit = "           + ts(mNHitsFit)           + "\n";
	msg += "mNHitsMax = "           + ts(mNHitsMax)           + "\n";
	msg += "mNHitsDedx = "          + ts(mNHitsDedx)          + "\n";
	msg += "mNSigmaPion = "         + ts(mNSigmaPion)         + "\n";
	msg += "mNSigmaKaon = "         + ts(mNSigmaKaon)         + "\n";
	msg += "mNSigmaProton = "       + ts(mNSigmaProton)       + "\n";
	msg += "mNSigmaElectron = "     + ts(mNSigmaElectron)     + "\n";
	msg += "mDCA = "                + ts(mDCA)                + "\n";
	msg += "mBTofPidTraitsIndex = " + ts(mBTofPidTraitsIndex) + "\n";
	msg += "mMtdPidTraitsIndex = "  + ts(mMtdPidTraitsIndex)  + "\n";
	msg += "mEmcPidTraitsIndex = "  + ts(mEmcPidTraitsIndex)  + "\n";
	msg += "mHelixIndex = "         + ts(mHelixIndex)         + "\n";
	return msg;
}