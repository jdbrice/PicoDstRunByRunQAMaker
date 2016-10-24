#ifndef PAIR_FILTER_H
#define PAIR_FILTER_H

// RooBarb
#include "CutCollection.h"

// Project
#include "CandidateTrack.h"
#include "CandidateTrackMtdPidTraits.h"


// ROOT
#include "TVector3.h"
#include "TLorentzVector.h"

// STL
#include <limits>


class PairFilter
{
public:
	PairFilter();
	~PairFilter();

	static bool keepMixedPair( 	shared_ptr<CandidateTrack> &aTrack, 
								shared_ptr<CandidateTrackMtdPidTraits> &aMtdPid,
								shared_ptr<CandidateTrack> &bTrack, 
								shared_ptr<CandidateTrackMtdPidTraits> &bMtdPid ){

		if ( aMtdPid->mMtdHitChan == bMtdPid->mMtdHitChan ) return false;
		return true;
	}


	static void setDefaultPairCuts( CutCollection &ccol ){
		ccol.setDefault( "leadingPt", 0, numeric_limits<double>::max() );
	}

	static bool keepSameEventPair( 	CutCollection &ccol, 
									TLorentzVector &lv1, TLorentzVector &lv2 ){
		if ( ccol[ "leadingPt" ]->below( lv1.Pt() ) && ccol[ "leadingPt" ]->below( lv2.Pt() ) ) 
			return false;
		return true;
	}
	
};



#endif