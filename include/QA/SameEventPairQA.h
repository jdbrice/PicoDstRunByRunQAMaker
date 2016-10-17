#ifndef SAME_EVENT_PAIR_QA_H
#define SAME_EVENT_PAIR_QA_H

#include "MuonCandidateQA.h"
#include "SameEventPairMaker.h"

class SameEventPairQA : public SameEventPairMaker
{
public:
	virtual const char* classname() const { return "SameEventPairQA"; }
	SameEventPairQA() {}
	~SameEventPairQA() {}

	virtual void initialize(){
		SameEventPairMaker::initialize();

		book->cd( "trackQA" );

		trackQA.setHistoBook( book );
		trackQA.setConfig( config );

		trackQA.addCategory( "Like_Sign" );
		trackQA.addCategory( "Unlike_Sign" );
		trackQA.makeDefaultCategory( false );
		MuonCandidateQA::initTrackVariables( trackQA );

		trackQA.makeHistograms( "TrackQABins" );
		dimuonBins.load( config, "dimuonBins.invMass" );

		book->cd();
	}


	HistoBins dimuonBins;

	virtual void analyzePair( CandidateTrack * _aTrack, CandidateTrack * _bTrack ){
		book->cd( "trackQA" );

		CandidateTrackMtdPidTraits *aMtdPid = (CandidateTrackMtdPidTraits *)mtdPidTraits->At( _aTrack->mMtdPidTraitsIndex );
		CandidateTrackMtdPidTraits *bMtdPid = (CandidateTrackMtdPidTraits *)mtdPidTraits->At( _bTrack->mMtdPidTraitsIndex );

		TLorentzVector lv1, lv2, lv;
		lv1.SetXYZM( _aTrack->mPMomentum_mX1, _aTrack->mPMomentum_mX2, _aTrack->mPMomentum_mX3, m1 );
		lv2.SetXYZM( _bTrack->mPMomentum_mX1, _bTrack->mPMomentum_mX2, _bTrack->mPMomentum_mX3, m2 );

		lv = lv1 + lv2;

		int iBin = dimuonBins.findBin( lv.M() );
		if ( iBin < 0 ) return;

		double bw = dimuonBins.binWidth( iBin );

		// decide what stuff to keep
		if ( 3.0 < lv.M() && lv.M() < 3.2 ){
			if ( abs(_aTrack->charge() + _bTrack->charge()) > 0 ){
				// INFO( classname(), "Same Sign Pair with M = " << lv.M() );
				MuonCandidateQA::fillCandidateTrackQA( trackQA, _aTrack, aMtdPid, "Like_Sign" );
				MuonCandidateQA::fillCandidateTrackQA( trackQA, _bTrack, bMtdPid, "Like_Sign" );
				book->cd();
				book->fill( "like_sign_jPsi", lv.M(), 1.0/ bw );
			} else {
				// INFO( classname(), "Opposite Sign Pair with M = " << lv.M() );
				MuonCandidateQA::fillCandidateTrackQA( trackQA, _aTrack, aMtdPid, "Unlike_Sign" );
				MuonCandidateQA::fillCandidateTrackQA( trackQA, _bTrack, bMtdPid, "Unlike_Sign" );
				book->cd();
				book->fill( "unlike_sign_jPsi", lv.M(), 1.0/ bw );
			}
		}

		if ( abs(_aTrack->charge() + _bTrack->charge()) > 0 ){
			book->cd();
			book->fill( "like_sign", lv.M(), 1.0/ bw );
		} else {
			book->cd();
			book->fill( "unlike_sign", lv.M(), 1.0/ bw );
		}




	}



protected:
	TTreeQA trackQA;
	
};


#endif