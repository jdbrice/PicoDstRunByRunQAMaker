#ifndef SAME_EVENT_PAIR_QA_H
#define SAME_EVENT_PAIR_QA_H


#include "MuonCandidateQA.h"

class SameEventPairQA : public CandidateSkimmer
{
public:
	virtual const char* classname() const { return "SameEventPairQA"; }
	SameEventPairQA() {}
	~SameEventPairQA() {}

	virtual void initialize(){
		CandidateSkimmer::initialize();

		book->cd( "trackQA" );

		if ( config.exists( nodePath + ".TrackCuts" ) ){
			trackCuts.init( config, nodePath + ".TrackCuts" );

			// trackCuts.setDefault( "rigidity", -1000, 1000 );

			INFO( classname(), "" );
			INFO( classname(), "############### Track Cuts ###################"  );
			trackCuts.report();
			INFO( classname(), "" );
		}

		
		qaMaker.setHistoBook( book );
		qaMaker.setConfig( config );

		initVariables( qaMaker );

		qaMaker.makeHistograms( "TrackQABins" );
	}



	virtual void analyzeEvent(){

		book->cd( "trackQA" );

		int nPos = 0, nNeg = 0;
		int nTracks = tracks->GetEntries();
		for ( int iTrack = 0; iTrack < nTracks; iTrack++ ){
			CandidateTrack* aTrack = (CandidateTrack*)tracks->At( iTrack );
			CandidateTrackMtdPidTraits *mtdPid = (CandidateTrackMtdPidTraits *)mtdPidTraits->At( aTrack->mMtdPidTraitsIndex );
			
			TVector3 mom = aTrack->pMomentum();
			float rdg        = mom.Pt() * aTrack->charge();

			if ( false == trackCuts[ "rigidity" ]->inInclusiveRange( rdg ) ) continue;

			fillCandidateTrackQA( qaMaker, aTrack, mtdPid );
			

			if ( aTrack->charge() > 0 )
				nPos++;
			if ( aTrack->charge() < 0 )
				nNeg++;

		} // iTrack loop

		// book->fill( "mup_vs_mum", nNeg, nPos );
	}


	CutCollection trackCuts;
	TTreeQA qaMaker;
	
};


#endif