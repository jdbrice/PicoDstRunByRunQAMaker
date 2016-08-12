#ifndef CANDIDATE_EVENT_H
#define CANDIDATE_EVENT_H

#include "TObject.h"

class CandidateEvent : public TObject
{
public:
	CandidateEvent() {}
	~CandidateEvent() {}
	void copy( CandidateEvent * that ){
		this->mPrimaryVertex_mX1 = that->mPrimaryVertex_mX1;
		this->mPrimaryVertex_mX2 = that->mPrimaryVertex_mX2;
		this->mPrimaryVertex_mX3 = that->mPrimaryVertex_mX3;
		this->mWeight            = that->mWeight;
		this->mRunId             = that->mRunId;
		this->mEventId           = that->mEventId;
		this->mPsi2              = that->mPsi2;
		this->mTriggerWord       = that->mTriggerWord;
		this->mTriggerWordMtd    = that->mTriggerWordMtd;
		this->mGRefMult          = that->mGRefMult;
		this->mBin16             = that->mBin16;
	}

	float psi() { return mPsi2 / 10000.0; }

	Float_t 	mPrimaryVertex_mX1;		// Event VertexX
	Float_t 	mPrimaryVertex_mX2;		// Event VertexY
	Float_t 	mPrimaryVertex_mX3;		// Event VertexZ
	Float_t 	mWeight;				// Event weight from StRefMultCorr
	Int_t 		mRunId;					// Run ID
	Int_t 		mEventId;				// Event Id
	UInt_t 		mTriggerWord;			// Trigger word
	UInt_t 		mTriggerWordMtd;		// MTD trigger word
	UShort_t 	mGRefMult;				// global RefMult
	Short_t 	mPsi2;					// event plane angle * 10000
	UChar_t 	mBin16;					// centrality bin 16



	ClassDef( CandidateEvent, 2 )
};


#endif