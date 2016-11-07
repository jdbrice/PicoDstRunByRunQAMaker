#ifndef MIXED_EVENT_PAIR_QA_MAKER_H
#define MIXED_EVENT_PAIR_QA_MAKER_H

#include "MuonCandidateQA.h"
#include "MixedEventPairMaker.h"

class MixedEventPairQAMaker : public MixedEventPairMaker
{
public:
	virtual const char* classname() const { return "MixedEventPairQAMaker"; }
	MixedEventPairQAMaker() {}
	~MixedEventPairQAMaker() {}

	virtual void initialize(){
		MixedEventCandidateSkimmer::initialize();


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

		book->cd();
	}


	HistoBins dimuonBins;

	virtual void analyzePair( shared_ptr<Candidate> _candA, shared_ptr<Candidate> _candB ){
		DEBUG( classname(), "analyzePair" );

		TLorentzVector lv1, lv2, lv;
		lv1.SetXYZM( _candA->track->mPMomentum_mX1, _candA->track->mPMomentum_mX2, _candA->track->mPMomentum_mX3, m1 );
		lv2.SetXYZM( _candB->track->mPMomentum_mX1, _candB->track->mPMomentum_mX2, _candB->track->mPMomentum_mX3, m2 );

		lv = lv1 + lv2;

		int iBin = dimuonBins.findBin( lv.M() );
		if ( iBin < 0 ) return;

		double bw = dimuonBins.binWidth( iBin );

		// decide what stuff to keep
		if (  qaCuts["InvMass"]->inInclusiveRange( lv.M() ) ){
			if ( abs(_candA->track->charge() + _candB->track->charge()) > 0 ){
				// INFO( classname(), "Same Sign Pair with M = " << lv.M() );
				if ( config.getBool( nodePath + ".MakeQA:SingleTrack", true ) ){
					book->cd( "trackQA" );
					MuonCandidateQA::fillCandidateTrackQA( trackQA, _candA->track.get(), _candA->mtdPidTraits.get(), "Like_Sign" );
					MuonCandidateQA::fillCandidateTrackQA( trackQA, _candB->track.get(), _candB->mtdPidTraits.get(), "Like_Sign" );
				}
				
				// book->cd();
				// book->fill( "like_sign_selected", lv.M(), 1.0/ bw );
			} else {
				// INFO( classname(), "Opposite Sign Pair with M = " << lv.M() );
				if ( config.getBool( nodePath + ".MakeQA:SingleTrack", true ) ){
					book->cd( "trackQA" );
					MuonCandidateQA::fillCandidateTrackQA( trackQA, _candA->track.get(), _candA->mtdPidTraits.get(), "Unlike_Sign" );
					MuonCandidateQA::fillCandidateTrackQA( trackQA, _candB->track.get(), _candB->mtdPidTraits.get(), "Unlike_Sign" );
				}
				// book->cd();
				// book->fill( "unlike_sign_selected", lv.M(), 1.0/ bw );
			}
		}

		if ( abs(_candA->track->charge() + _candB->track->charge()) > 0 ){
			book->cd();
			book->fill( "like_sign", lv.M(), 1.0/ bw );
		} else {
			book->cd();
			book->fill( "unlike_sign", lv.M(), 1.0/ bw );
		}

		if ( config.getBool( nodePath + ".MakeQA:Pair", true ) ){
			book->cd( "pairQA" );
			// MixedEventPairQAMaker::fillPairVariables( pairQA, _candA->track, _candB->track, m1, m2 );
			if ( abs(_candA->track->charge() + _candB->track->charge()) > 0 ){
				SameEventPairQA::fillPairVariables( pairQA, _candA->track.get(), _candB->track.get(), _candA->mtdPidTraits.get(), _candB->mtdPidTraits.get(), m1, m2, "Like_Sign" );
				if ( _candA->track->charge() + _candB->track->charge() == 2 )
					SameEventPairQA::fillPairVariables( pairQA, _candA->track.get(), _candB->track.get(), _candA->mtdPidTraits.get(), _candB->mtdPidTraits.get(), m1, m2, "Like_Sign_Pos" );
				else if ( _candA->track->charge() + _candB->track->charge() == -2 )
					SameEventPairQA::fillPairVariables( pairQA, _candA->track.get(), _candB->track.get(), _candA->mtdPidTraits.get(), _candB->mtdPidTraits.get(), m1, m2, "Like_Sign_Neg" );
			} else {
				SameEventPairQA::fillPairVariables( pairQA, _candA->track.get(), _candB->track.get(), _candA->mtdPidTraits.get(), _candB->mtdPidTraits.get(), m1, m2, "Unlike_Sign");
			}

		}

	}


protected:
	TTreeQA trackQA;
	CutCollection qaCuts;
	TTreeQA pairQA;
	
};


#endif