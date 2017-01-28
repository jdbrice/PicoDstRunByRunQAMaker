#ifndef PAIR_FILTER_H
#define PAIR_FILTER_H

// RooBarb
#include "CutCollection.h"

// Project
#include "CandidateTrack.h"
#include "CandidateTrackMtdPidTraits.h"
#include "TriggerPatchMapper.h"


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
		// bool kse = keepSameEventPair( ccol, lv1, lv2 );
		// if ( kse == false ) return true;

		// TLorentzVector lv = lv1 + lv2;
		// if ( lv1.DeltaPhi( lv2 ) < 0.5 / ( lv.Pt() ) ) return false;
		
		
		return true;
	}


	static void setDefaultPairCuts( CutCollection &ccol ){
		ccol.setDefault( "leadingPt", 0, numeric_limits<double>::max() );
	}

	static bool keepSameEventPair( 	CutCollection &ccol, 
									TLorentzVector &_lv, TLorentzVector &_lv1, TLorentzVector &_lv2 ){
		
		if ( ccol[ "leadingPt" ]->below( _lv1.Pt() ) && ccol[ "leadingPt" ]->below( _lv2.Pt() ) ) 
			return false;


		if ( !ccol[ "y" ]->inInclusiveRange( _lv.Rapidity() ) )
			return false;
		if ( !ccol[ "eta" ]->inInclusiveRange( _lv1.Eta() ) || !ccol[ "eta" ]->inInclusiveRange( _lv2.Eta() ) )
			return false;

		return true;
	}

	static bool keepSameEventPair( CutCollection &ccol, CandidateTrack *_aTrack, CandidateTrackMtdPidTraits * _aMtdPidTraits,
														CandidateTrack *_bTrack, CandidateTrackMtdPidTraits * _bMtdPidTraits ){

		if ( ccol[ "mtdBackLegA" ] != nullptr &&  ccol[ "mtdBackLegB" ] != nullptr ){

			int blA = TriggerPatchMapper::backleg( _aMtdPidTraits->mMtdHitChan );
			int blB = TriggerPatchMapper::backleg( _bMtdPidTraits->mMtdHitChan );

			if( !ccol["mtdBackLegA"]->inInclusiveRange( blA ) && !ccol["mtdBackLegB"]->inInclusiveRange( blA ) )
				return false;
			if( !ccol["mtdBackLegA"]->inInclusiveRange( blB ) && !ccol["mtdBackLegB"]->inInclusiveRange( blB ) )
				return false;

			
		}

		return true;
	}
	
};



#endif