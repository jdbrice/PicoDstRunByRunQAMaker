#ifndef PID_PLOT_MAKER_H
#define PID_PLOT_MAKER_H

#include "MuonCandidateQA.h"
#include "SameEventPairMaker.h"
#include "SameEventPairQA.h"

#include "TRandom3.h"

class PidPlotMaker : public SameEventPairQA
{
public:
	virtual const char* classname() const { return "PidPlotMaker"; }
	PidPlotMaker() {}
	~PidPlotMaker() {}

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

			trackQA.addCategory( "Like_Sign_ROI" );
			trackQA.addCategory( "Like_Sign" );
			trackQA.addCategory( "Unlike_Sign_ROI" );
			trackQA.addCategory( "Unlike_Sign" );
			trackQA.makeDefaultCategory( false );
			MuonCandidateQA::initTrackVariables( trackQA );

			trackQA.makeHistograms( "TrackQABins" );
		}
		
		// if ( config.getBool( nodePath + ".MakeQA:Pair", true ) ){
		// 	pairQA.setHistoBook( book );
		// 	pairQA.setConfig( config );
		// 	pairQA.addCategory( "Like_Sign" );
		// 	pairQA.addCategory( "Like_Sign_Pos" );
		// 	pairQA.addCategory( "Like_Sign_Neg" );
		// 	pairQA.addCategory( "Unlike_Sign" );
		// 	pairQA.makeDefaultCategory( false );
		// 	SameEventPairQA::initPairVariables( pairQA );
		// 	book->cd( "pairQA" );
		// 	pairQA.makeHistograms( "PairQABins" );
		// }

		book->cd();

		// setup the TIGHT PID cuts for N-1 application
		
		pidCuts.init( config, nodePath + ".PidCuts" );
		for ( auto kv : pidCuts.ranges ){
			INFO( classname(), "Adding PidCut : " << quote( kv.first ) );
			cutNames.push_back( kv.first );
		}
		CandidateFilter::setDefaultMuonCuts( pidCuts );
		book->cd();
	}


	virtual void preEventLoop(){
		CandidateSkimmer::preEventLoop();

		book->cd();
		for ( string excludeCut : cutNames ){
			book->clone( "unlike_sign", "unlike_sign_" + excludeCut );
			book->clone( "like_sign", "like_sign_" + excludeCut );

			book->add( "nPass_" + excludeCut, (TH1D*) new TH1D( ("nPass_" + excludeCut).c_str(), "", 10, 0, 10  ) );
		}

		book->clone( "unlike_sign", "unlike_sign_loose"  );
		book->clone( "like_sign", "like_sign_loose"  );

		book->clone( "unlike_sign", "unlike_sign_roi"  );
		book->clone( "like_sign", "like_sign_roi"  );

	}

	void fillOnlyOneVar( TTreeQA &_qaMaker, CandidateTrack* _track, CandidateTrackMtdPidTraits* _mtdPid, string _cat = "", string _var = "" ){

		TVector3 mom = _track->pMomentum();

		float rdg        = mom.Pt() * _track->charge();
		float dEdx       = _track->mDedx/1000.0;
		float nSigmaPion = _track->mNSigmaPion / 100.0;

		if ( _var == "phi" )
			_qaMaker.s( "phi"          , mom.Phi() );
		if ( _var == "eta" )
			_qaMaker.s( "eta"          , mom.Eta() );
		
			_qaMaker.s( "rigidity"     , rdg );
		if ( _var == "mtdHitChan" )
			_qaMaker.s( "mtdHitChan"   , _mtdPid->mMtdHitChan );
		if ( _var == "mtdCell" )
			_qaMaker.s( "mtdCell"      , _mtdPid->cell() );
		if ( _var == "mtdDeltaY"  )
			_qaMaker.s( "mtdDeltaY"   , _mtdPid->mDeltaY * _track->charge() );
		if ( _var == "mtdDeltaZ" )
			_qaMaker.s( "mtdDeltaZ"    , _mtdPid->mDeltaZ );
		if ( _var == "mtdDeltaTOF" )
			_qaMaker.s( "mtdDeltaTOF"  , _mtdPid->mDeltaTimeOfFlight );
		if ( _var == "nSigmaPion" )
			_qaMaker.s( "nSigmaPion"   , nSigmaPion );

		if ( _var == "dca" || _var == "gDCA")
			_qaMaker.s( "dca"         , _track->gDCA() );



		_qaMaker.fill( _cat );
	}


	virtual void analyzePair( CandidateTrack * _aTrack, CandidateTrack * _bTrack ){
		CandidateTrackMtdPidTraits *aMtdPid = (CandidateTrackMtdPidTraits *)mtdPidTraits->At( _aTrack->mMtdPidTraitsIndex );
		CandidateTrackMtdPidTraits *bMtdPid = (CandidateTrackMtdPidTraits *)mtdPidTraits->At( _bTrack->mMtdPidTraitsIndex );

		

		TLorentzVector lv1, lv2, lv;
		lv1.SetXYZM( _aTrack->mPMomentum_mX1, _aTrack->mPMomentum_mX2, _aTrack->mPMomentum_mX3, m1 );
		lv2.SetXYZM( _bTrack->mPMomentum_mX1, _bTrack->mPMomentum_mX2, _bTrack->mPMomentum_mX3, m2 );

		lv = lv1 + lv2;
		
		if ( !PairFilter::keepSameEventPair( pairCuts, lv1, lv2 ) ) return;

		int iBin = dimuonBins.findBin( lv.M() );
		if ( iBin < 0 ) return;

		double bw = dimuonBins.binWidth( iBin );

		if ( abs(_aTrack->charge() + _bTrack->charge()) > 0 ){
			book->cd();
			book->fill( "like_sign_loose", lv.M(), 1.0/ bw );
			book->cd( "trackQA" );
			// MuonCandidateQA::fillCandidateTrackQA( trackQA, _aTrack, aMtdPid, "Like_Sign_Loose" );
			// MuonCandidateQA::fillCandidateTrackQA( trackQA, _bTrack, bMtdPid, "Like_Sign_Loose" );
		} else {
			book->cd();
			book->fill( "unlike_sign_loose", lv.M(), 1.0/ bw );
			book->cd( "trackQA" );
			// MuonCandidateQA::fillCandidateTrackQA( trackQA, _aTrack, aMtdPid, "Unlike_Sign_Loose" );
			// MuonCandidateQA::fillCandidateTrackQA( trackQA, _bTrack, bMtdPid, "Unlike_Sign_Loose" );
		}

		for ( string excludeCut : cutNames ){

				if ( 	!CandidateFilter::isMuon( _aTrack, aMtdPid, pidCuts, nullptr, excludeCut ) ||
						!CandidateFilter::isMuon( _bTrack, bMtdPid, pidCuts, nullptr, excludeCut ) ) continue;
					

				if ( abs(_aTrack->charge() + _bTrack->charge()) > 0 ){
					book->cd();
					book->fill( "like_sign_" + excludeCut, lv.M(), 1.0/ bw );
				} else {
					book->cd();
					book->fill( "unlike_sign_" + excludeCut, lv.M(), 1.0/ bw );
				}

			// decide what stuff to keep
			
				
			book->cd();
			book->fill( "nPass_" + excludeCut, 1 );
			book->fill( "nPass_" + excludeCut, 1 );

			if ( abs(_aTrack->charge() + _bTrack->charge()) > 0 ){
				book->cd( "trackQA" );
				
				if (  qaCuts["InvMass"]->inInclusiveRange( lv.M() ) ){
					fillOnlyOneVar( trackQA, _aTrack, aMtdPid, "Like_Sign_ROI", excludeCut );
					fillOnlyOneVar( trackQA, _bTrack, bMtdPid, "Like_Sign_ROI", excludeCut );
				}
				fillOnlyOneVar( trackQA, _aTrack, aMtdPid, "Like_Sign", excludeCut );
				fillOnlyOneVar( trackQA, _bTrack, bMtdPid, "Like_Sign", excludeCut );
			} else {
				book->cd( "trackQA" );
				if (  qaCuts["InvMass"]->inInclusiveRange( lv.M() ) ){
					fillOnlyOneVar( trackQA, _aTrack, aMtdPid, "Unlike_Sign_ROI", excludeCut );
					fillOnlyOneVar( trackQA, _bTrack, bMtdPid, "Unlike_Sign_ROI", excludeCut );
				}
				fillOnlyOneVar( trackQA, _aTrack, aMtdPid, "Unlike_Sign", excludeCut );
				fillOnlyOneVar( trackQA, _bTrack, bMtdPid, "Unlike_Sign", excludeCut );
			} // charge
			



		} // loop excludeCut


		if ( 	CandidateFilter::isMuon( _aTrack, aMtdPid, pidCuts, nullptr ) &&
						CandidateFilter::isMuon( _bTrack, bMtdPid, pidCuts, nullptr ) ){
			
			if ( abs(_aTrack->charge() + _bTrack->charge()) > 0 ){
				book->cd();
				book->fill( "like_sign", lv.M(), 1.0/ bw );
				if (  qaCuts["InvMass"]->inInclusiveRange( lv.M() ) )
					book->fill( "like_sign_roi", lv.M(), 1.0/ bw );

			} else {
				book->cd();
				book->fill( "unlike_sign", lv.M(), 1.0/ bw );
				if (  qaCuts["InvMass"]->inInclusiveRange( lv.M() ) )
					book->fill( "unlike_sign_roi", lv.M(), 1.0/ bw );
			}
		}	
	} // analyze pair


	virtual void postMake() {


		book->cd( "trackQA" );


		for ( string name : cutNames ){
			
			string cat = "Unlike_Sign_ROI";
			book->clone( cat + "_" + name, "signal_" + name );
			TH1D * hSignal = (TH1D*)book->get( "signal_" + name );
			TH1D * hBg = (TH1D*)book->get( string("Like_Sign_ROI_") + name );

			if ( hSignal && hBg ){
				hSignal->Add( hBg, -1 );
			}
			
		}

	}



protected:
	CutCollection pidCuts;
	vector<string> cutNames;
	
	
};


#endif