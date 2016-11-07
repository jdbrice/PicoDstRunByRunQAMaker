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

	static bool keepMixedEventPair( 	CutCollection &ccol, 
										TLorentzVector &lv1, TLorentzVector &lv2 ){
		bool kse = keepSameEventPair( ccol, lv1, lv2 );
		if ( kse == false ) return true;

		TLorentzVector lv = lv1 + lv2;
		if ( lv1.DeltaPhi( lv2 ) < 0.5 / ( lv.Pt() ) ) return false;
		return true;
	}


	static void setDefaultPairCuts( CutCollection &ccol ){
		ccol.setDefault( "leadingPt", 0, numeric_limits<double>::max() );
	}

	static bool keepSameEventPair( 	CutCollection &ccol, 
									TLorentzVector &lv1, TLorentzVector &lv2 ){
		if ( ccol[ "leadingPt" ]->below( lv1.Pt() ) && ccol[ "leadingPt" ]->below( lv2.Pt() ) ) 
			return false;

		if ( !ccol["deltaEta"]->inInclusiveRange( fabs( lv1.Eta() - lv2.Eta() ) ) ){
			// INFO( "PairFilter", "deltaEta" );
			return false;
		}

		if ( !ccol["deltaPhi"]->inInclusiveRange( fabs( lv1.DeltaPhi( lv2 ) ) ) ){
			// INFO( "PairFilter", "deltaPhi" );
			return false;
		}
		

		return true;
	}
	
};



#endif