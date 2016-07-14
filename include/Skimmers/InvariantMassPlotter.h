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

class InvariantMassPlotter : public CandidateSkimmer
{
public:
	virtual const char * classname() const { return "InvariantMassPlotter"; }
	InvariantMassPlotter(){}
	~InvariantMassPlotter(){}

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

	}


protected:

	double m1, m2;
	CutCollection trackCuts;
	bool makeTrackCutQA = false;


	bool keepTrack( CandidateTrack *aTrack ){
		CandidateTrackMtdPidTraits *mtdPid = (CandidateTrackMtdPidTraits *)mtdPidTraits->At( aTrack->mMtdPidTraitsIndex );
		return CandidateFilter::isMuon( aTrack, mtdPid, trackCuts,  makeTrackCutQA ? book : nullptr );
	}

	virtual void analyzeEvent(){
		// INFO( classname(), tracks->GetEntries() );
		// INFO( classname(), event->eventId );
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

				// if ( lv1.Pt() < 1.5 && lv2.Pt() < 1.5   ) continue;

				book->cd("");
				int iBin = book->get( "like_sign" )->GetXaxis()->FindBin( lv.M() );
				double bw = book->get( "like_sign" )->GetBinWidth( iBin );

				// like sign
				if ( aTrack->charge() * bTrack->charge() == 1 ){
					book->fill( "like_sign", lv.M() );
					book->fill( "like_sign_pT", lv.M(), lv.Pt() );
				} else {
					book->fill( "unlike_sign", lv.M() );
					book->fill( "unlike_sign_pT", lv.M(), lv.Pt() );
				}
			}
		}

	}

	
};

#endif