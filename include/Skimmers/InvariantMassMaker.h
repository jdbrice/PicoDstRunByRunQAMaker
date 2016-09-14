#ifndef CANDIDATE_INVARIANT_MASS_H
#define CANDIDATE_INVARIANT_MASS_H

//RooBarb
#include "TreeAnalyzer.h"
#include "CutCollection.h"

//ROOT
#include "TLorentzVector.h"

// Project
#include "CandidateSkimmer.h"
#include "CandidateFilter.h"
#include "EventHasher.h"
#include "RunMapFactory.h"
#include "ICandidatePairTreeMaker.h"

#include "TNtuple.h"

class InvariantMassMaker : public CandidateSkimmer, public ICandidatePairTreeMaker
{
public:
	virtual const char * classname() const { return "InvariantMassMaker"; }
	InvariantMassMaker(){}
	~InvariantMassMaker(){}

	virtual void initialize(){
		CandidateSkimmer::initialize();

		m1 = config.getDouble( nodePath + ".Particles:mass1", 0.0511 );
		m2 = config.getDouble( nodePath + ".Particles:mass2", 0.0511 );

		INFO( classname(), "mass1 = " << m1 );
		INFO( classname(), "mass2 = " << m2 );

		if ( config.exists( nodePath + ".MuonCandidateCuts" ) ){
			trackCuts.init( config, nodePath + ".MuonCandidateCuts" );

			INFO( classname(), "" );
			INFO( classname(), "############### Muon Cuts ###################"  );
			trackCuts.report();
			INFO( classname(), "" );
		}

		if ( config.exists( nodePath + ".SameEventPairCuts" ) ){
			pairCuts.init( config, nodePath + ".SameEventPairCuts" );

			INFO( classname(), "" );
			INFO( classname(), "############### Pair Cuts ###################"  );
			pairCuts.report();
			INFO( classname(), "" );
		}

		eventHash = config.getInt( nodePath + ".EventHash", -1 );
		eht.load( config, nodePath + ".MixedEventBins" );

		INFO( classname(), "EventHash = " << eventHash );

		rmf = shared_ptr<RunMapFactory>( new RunMapFactory( "Run15PP200", false ) );
		INFO( classname(), "BAD == " << rmf->isRunBad( 16055005 ) );

		createPairTree( "Muon Pairs" );

	}


protected:

	double m1, m2;
	CutCollection trackCuts;
	CutCollection pairCuts;
	EventHasher eht;
	int eventHash = -1;
	shared_ptr<RunMapFactory> rmf;


	bool keepTrack( CandidateTrack *aTrack ){
		CandidateTrackMtdPidTraits *mtdPid = (CandidateTrackMtdPidTraits *)mtdPidTraits->At( aTrack->mMtdPidTraitsIndex );
		return CandidateFilter::isMuon( aTrack, mtdPid, trackCuts,  makeTrackCutQA ? book : nullptr );
	}

	virtual bool keepEvent(){

		if ( rmf->isRunBad( event->mRunId ) ){
			return false;
		}

		wEvent->copy( event );
		return true;

	}

	virtual void analyzeEvent(){
		// INFO( classname(), tracks->GetEntries() );
		// INFO( classname(), event->eventId );

		resetPairs();
		book->cd("");
		TAxis * axis = book->get( "unlike_sign" )->GetXaxis();

		int aEventHash = eht.hash( event );
		TRACE( classname(), "current Event = " << aEventHash );
		if ( 0 <= eventHash && eventHash != aEventHash ) return;


		int nTracks = tracks->GetEntries();
		for ( int iTrack = 0; iTrack < nTracks; iTrack++ ){
			CandidateTrack* aTrack = (CandidateTrack*)tracks->At( iTrack );
			if ( !keepTrack( aTrack ) ) continue;

			for ( int jTrack = iTrack; jTrack < nTracks; jTrack++ ){
				if ( iTrack == jTrack ) continue;
				CandidateTrack* bTrack = (CandidateTrack*)tracks->At( jTrack );
				if ( !keepTrack( bTrack ) ) continue;

				

				TLorentzVector lv1, lv2, lv;
				lv1.SetXYZM( aTrack->mPMomentum_mX1, aTrack->mPMomentum_mX2, aTrack->mPMomentum_mX3, m1 );
				lv2.SetXYZM( bTrack->mPMomentum_mX1, bTrack->mPMomentum_mX2, bTrack->mPMomentum_mX3, m2 );

				lv = lv1 + lv2;

				if ( !PairFilter::keepSameEventPair( pairCuts, lv1, lv2 ) ) continue;
				fillCandidatePair( aTrack, bTrack );


				double dR = lv1.DeltaR( lv2 );
				double dPhi = lv1.DeltaPhi( lv2 );

				book->cd("");
				int iBin = book->get( "like_sign" )->GetXaxis()->FindBin( lv.M() );
				double bw = book->get( "like_sign" )->GetBinWidth( iBin );

				// like sign
				if ( aTrack->charge() * bTrack->charge() == 1 ){
					book->fill( "like_sign", lv.M(), 1.0 / bw );
					book->fill( "like_sign_dR", lv.M(), dR, 1.0 / bw );
					book->fill( "like_sign_dPhi", lv.M(), dPhi, 1.0 / bw );
					book->fill( "like_sign_pT", lv.M(), lv.Pt() );
					if ( 1 == aTrack->charge()  ){
						book->fill( "like_sign_Pos", lv.M(), 1.0 / bw );
						book->fill( "like_sign_Pos_pT", lv.M(), lv.Pt(), 1.0/ bw );
					} else if ( -1 == aTrack->charge()  ){
						book->fill( "like_sign_Neg", lv.M(), 1.0 / bw );
						book->fill( "like_sign_Neg_pT", lv.M(), lv.Pt(), 1.0/ bw );
					}
				} else {
					book->fill( "unlike_sign", lv.M(), 1.0/bw );
					book->fill( "unlike_sign_dR", lv.M(), dR, 1.0 / bw );
					book->fill( "unlike_sign_dPhi", lv.M(), dPhi, 1.0 / bw );
					book->fill( "unlike_sign_pT", lv.M(), lv.Pt(), 1.0/bw );
				}
			}
		}
		mPairTree->Fill();
	} // analyzeEvent

	void makeCutTree( CutCollection &ccol, string name ){
		INFO( classname(), "Making Cuts Ntuple named " << name );

		book->cd();
		string vars = "";
		vector<float> data;
		string sep = "";
		for ( auto kv : ccol.ranges ){
			vars += sep + kv.first + "_min";
			sep=":";
			vars += sep + kv.first + "_max";

			data.push_back( kv.second->min );
			data.push_back( kv.second->max );
		}
		INFO( classname(), "NTUPLE vars = " << vars );
		INFO( classname(), "data : " << data.size() );

		TNtuple *ntuple = new TNtuple(name.c_str(),name.c_str(), vars.c_str() );
		ntuple->Fill( data.data() );
	}
	virtual void preMake(){

		makeCutTree( trackCuts, "trackCuts" );
		makeCutTree( pairCuts, "pairCuts" );

	}

	virtual void postMake(){
		CandidateSkimmer::postMake();

	}


	virtual void fillCandidatePair( CandidateTrack * aTrack, CandidateTrack * bTrack ){

		CandidatePair * aPair = new ((*wPairs)[nCandPairs]) CandidatePair( );
		aPair->d1.copy( aTrack );
		aPair->d2.copy( bTrack );

		CandidateTrackMtdPidTraits *aMtdPid = (CandidateTrackMtdPidTraits *)mtdPidTraits->At( aTrack->mMtdPidTraitsIndex );
		CandidateTrackMtdPidTraits *bMtdPid = (CandidateTrackMtdPidTraits *)mtdPidTraits->At( bTrack->mMtdPidTraitsIndex );

		aPair->mtd1.copy( aMtdPid );
		aPair->mtd2.copy( bMtdPid );
		
		TLorentzVector lv1, lv2, lv;
		lv1.SetXYZM( aTrack->mPMomentum_mX1, aTrack->mPMomentum_mX2, aTrack->mPMomentum_mX3, m1 );
		lv2.SetXYZM( bTrack->mPMomentum_mX1, bTrack->mPMomentum_mX2, bTrack->mPMomentum_mX3, m2 );

		lv = lv1 + lv2;

		aPair->set( lv.Px(), lv.Py(), lv.Pz(), lv.M(), aTrack->charge() * bTrack->charge() );
		nCandPairs++;
	}

	
};

#endif