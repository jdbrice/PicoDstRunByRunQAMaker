#ifndef SAME_EVENT_PAIR_QA_H
#define SAME_EVENT_PAIR_QA_H

#include "MuonCandidateQA.h"
#include "SameEventPairMaker.h"

#include "TRandom3.h"

class SameEventPairQA : public SameEventPairMaker
{
public:
	virtual const char* classname() const { return "SameEventPairQA"; }
	SameEventPairQA() {}
	~SameEventPairQA() {}

	static TRandom3 rnd;

	virtual void initialize(){
		SameEventPairMaker::initialize();


		qaCuts.setDefault( "InvMass", 0, 15 );
		if ( config.exists( nodePath + ".QACuts" ) ){
			qaCuts.init( config, nodePath + ".QACuts" );

			INFO( classname(), "" );
			INFO( classname(), "############### QA Cuts ###################"  );
			qaCuts.report();
			INFO( classname(), "" );
		}

		dimuonBins.load( config, "dimuonBins.invMass" );


		if ( config.getBool( nodePath + ".MakeQA:SingleTrack", true ) ){
			book->cd( "trackQA" );

			trackQA.setHistoBook( book );
			trackQA.setConfig( config );

			trackQA.addCategory( "Like_Sign" );
			trackQA.addCategory( "Unlike_Sign" );
			trackQA.makeDefaultCategory( false );
			MuonCandidateQA::initTrackVariables( trackQA );

			trackQA.makeHistograms( "TrackQABins" );
		}
		
		if ( config.getBool( nodePath + ".MakeQA:Pair", true ) ){
			pairQA.setHistoBook( book );
			pairQA.setConfig( config );
			pairQA.addCategory( "Like_Sign" );
			pairQA.addCategory( "Like_Sign_Pos" );
			pairQA.addCategory( "Like_Sign_Neg" );
			pairQA.addCategory( "Unlike_Sign" );
			pairQA.makeDefaultCategory( false );
			SameEventPairQA::initPairVariables( pairQA );
			book->cd( "pairQA" );
			pairQA.makeHistograms( "PairQABins" );
		}

		rnd.SetSeed(0);

		book->cd();
	}


	HistoBins dimuonBins;

	virtual void analyzePair( CandidateTrack * _aTrack, CandidateTrack * _bTrack ){
		

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
		if (  qaCuts["InvMass"]->inInclusiveRange( lv.M() ) ){
			if ( abs(_aTrack->charge() + _bTrack->charge()) > 0 ){
				// INFO( classname(), "Same Sign Pair with M = " << lv.M() );
				if ( config.getBool( nodePath + ".MakeQA:SingleTrack", true ) ){
					book->cd( "trackQA" );
					MuonCandidateQA::fillCandidateTrackQA( trackQA, _aTrack, aMtdPid, "Like_Sign" );
					MuonCandidateQA::fillCandidateTrackQA( trackQA, _bTrack, bMtdPid, "Like_Sign" );
				}
				
				// book->cd();
				// book->fill( "like_sign_selected", lv.M(), 1.0/ bw );
			} else {
				// INFO( classname(), "Opposite Sign Pair with M = " << lv.M() );
				if ( config.getBool( nodePath + ".MakeQA:SingleTrack", true ) ){
					book->cd( "trackQA" );
					MuonCandidateQA::fillCandidateTrackQA( trackQA, _aTrack, aMtdPid, "Unlike_Sign" );
					MuonCandidateQA::fillCandidateTrackQA( trackQA, _bTrack, bMtdPid, "Unlike_Sign" );
				}
				// book->cd();
				// book->fill( "unlike_sign_selected", lv.M(), 1.0/ bw );
			}
		}

		if ( abs(_aTrack->charge() + _bTrack->charge()) > 0 ){
			book->cd();
			book->fill( "like_sign", lv.M(), 1.0/ bw );
		} else {
			book->cd();
			book->fill( "unlike_sign", lv.M(), 1.0/ bw );
		}

		if ( config.getBool( nodePath + ".MakeQA:Pair", true ) ){
			book->cd( "pairQA" );
			// SameEventPairQA::fillPairVariables( pairQA, _aTrack, _bTrack, m1, m2 );
			if ( abs(_aTrack->charge() + _bTrack->charge()) > 0 ){
				SameEventPairQA::fillPairVariables( pairQA, _aTrack, _bTrack, m1, m2, "Like_Sign" );
				if (_aTrack->charge() + _bTrack->charge() == 2 )
					SameEventPairQA::fillPairVariables( pairQA, _aTrack, _bTrack, m1, m2, "Like_Sign_Pos" );
				else if (_aTrack->charge() + _bTrack->charge() == -2 )
					SameEventPairQA::fillPairVariables( pairQA, _aTrack, _bTrack, m1, m2, "Like_Sign_Neg" );
			} else {
				SameEventPairQA::fillPairVariables( pairQA, _aTrack, _bTrack, m1, m2, "Unlike_Sign");
			}

		}

	}


	static void initPairVariables( TTreeQA &_qaMaker ){
		_qaMaker.i( "phi_d1"   , "d1 #phi"      , "[rad]"       , "phi"    , "x" );
		_qaMaker.i( "phi_d2"   , "d2 #phi"      , "[rad]"       , "phi" );
		_qaMaker.i( "eta_d1"   , "d1 #eta"      , ""            , "eta"    , "x" );
		_qaMaker.i( "eta_d2"   , "d2 #eta"      , ""            , "eta" );
		_qaMaker.i( "deltaPhi" , "#Delta Phi"   , "[rad]" );
		_qaMaker.i( "deltaEta" , "#Delta #eta"  , "" );
		_qaMaker.i( "deltaR"   , "#Delta R"     , "" );
		_qaMaker.i( "parentPt" , "Parent p_{T}" , "[GeV/c]"     , ""       , "x" );
		_qaMaker.i( "parentM"  , "M"            , "[GeV/c^{2}]" , ""       , "x" );
		// _qaMaker.i( "deltaR", "dPhi", "[rad]" );
	}

	static void fillPairVariables( 
			TTreeQA &_qaMaker, 
			CandidateTrack * _aTrack, 
			CandidateTrack * _bTrack, 
			double _m1, double _m2,
			string _cat = "" ){

		TLorentzVector lv1, lv2, lv;
		lv1.SetXYZM( _aTrack->mPMomentum_mX1, _aTrack->mPMomentum_mX2, _aTrack->mPMomentum_mX3, _m1 );
		lv2.SetXYZM( _bTrack->mPMomentum_mX1, _bTrack->mPMomentum_mX2, _bTrack->mPMomentum_mX3, _m2 );
		lv = lv1 + lv2;


		_qaMaker.s( "phi_d1", lv1.Phi() );
		_qaMaker.s( "phi_d2", lv2.Phi() );
		_qaMaker.s( "eta_d1", lv1.Eta() );
		_qaMaker.s( "eta_d2", lv2.Eta() );

		float dPhi = -10;
		float dEta = -100;
		float dR = -100;
		if ( rnd.Uniform(  ) <= 0.5 ){
			dPhi = lv1.DeltaPhi( lv2 );
			dEta = lv1.Eta() - lv2.Eta();
			dR = lv1.DeltaR( lv2 );
		} else {
			dPhi = lv2.DeltaPhi( lv1 );
			dEta = lv2.Eta() - lv1.Eta();
			dR = lv2.DeltaR( lv1 );
		}
		

		_qaMaker.s( "deltaPhi", dPhi );
		_qaMaker.s( "deltaEta", dEta );
		_qaMaker.s( "deltaR", dR );


		_qaMaker.s( "parentPt", lv.Pt() );
		_qaMaker.s( "parentM", lv.M() );

		_qaMaker.fill( _cat );
	}



protected:
	TTreeQA trackQA;
	CutCollection qaCuts;
	TTreeQA pairQA;
	
};


#endif