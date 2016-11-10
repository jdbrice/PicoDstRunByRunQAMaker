#ifndef CANDIDATE_TRACK_BTOF_PID_TRAITS_H
#define CANDIDATE_TRACK_BTOF_PID_TRAITS_H

#include "TObject.h"

class CandidateTrackBTofPidTraits : public TObject
{
public:
	CandidateTrackBTofPidTraits(){
		reset();
	}
	~CandidateTrackBTofPidTraits(){ }

	void reset(){
		this->mBTofBeta      = 0.0;
		this->mBTofYLocal    = 0.0;
		this->mBTofZLocal    = 0.0;
		this->mBTofMatchFlag = 0.0;
	}

	void copy( CandidateTrackBTofPidTraits * that){
		this->mBTofBeta      = that->mBTofBeta;
		this->mBTofYLocal    = that->mBTofYLocal;
		this->mBTofZLocal    = that->mBTofZLocal;
		this->mBTofMatchFlag = that->mBTofMatchFlag;
	}

	Float_t beta() { return mBTofBeta / 20000.0; }  
	Float_t yLocal() { return mBTofYLocal / 1000.0; }
	Float_t zLocal() { return mBTofZLocal / 1000.0; }

	UShort_t mBTofBeta;			// beta * 20000
	Short_t  mBTofYLocal;		// ylocal * 1000
	Short_t  mBTofZLocal;		// zlocal * 1000
	UChar_t  mBTofMatchFlag;	// 0 - no match, 1 - one-to-one, 2 - one-to-multiple
	
	ClassDef( CandidateTrackBTofPidTraits, 1 )
};

#endif