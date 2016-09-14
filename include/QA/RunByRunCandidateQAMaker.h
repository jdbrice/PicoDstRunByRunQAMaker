#ifndef RUN_BY_RUNCADIDATE_QA_MAKER_H
#define RUN_BY_RUNCADIDATE_QA_MAKER_H

#include "CandidateSkimmer.h"

class RunByRunCandidateQAMaker : public CandidateSkimmer
{
public:
	virtual const char* classname() const { return "RunByRunCandidateQAMaker"; }
	RunByRunCandidateQAMaker() {}
	~RunByRunCandidateQAMaker() {}

	virtual void initialize(){
		CandidateSkimmer::initialize();



	}

	virtual void analyzeEvent(){

		book->fill( "runIndex", event->mRunIndex );
		book->fill( "vertexX", event->mRunIndex, event->mPrimaryVertex_mX1 );
		book->fill( "vertexY", event->mRunIndex, event->mPrimaryVertex_mX2 );
		book->fill( "vertexZ", event->mRunIndex, event->mPrimaryVertex_mX3 );
		book->fill( "gRefMult", event->mRunIndex, event->mGRefMult );


		int nTracks = tracks->GetEntries();
		for ( int iTrack = 0; iTrack < nTracks; iTrack++ ){
			analyzeTrack( iTrack );
		}


	}

	virtual void analyzeTrack( int iTrack ){
		CandidateTrack* aTrack = (CandidateTrack*)tracks->At( iTrack );
		CandidateTrackMtdPidTraits *mtdPid = (CandidateTrackMtdPidTraits *)mtdPidTraits->At( aTrack->mMtdPidTraitsIndex );

		book->fill( "nTracks",        event->mRunIndex, tracks->GetEntries() );
		book->fill( "momentum",       event->mRunIndex, aTrack->pMomentum().Mag() );
		book->fill( "pt",             event->mRunIndex, aTrack->pMomentum().Pt() );
		book->fill( "dedx",           event->mRunIndex, aTrack->dEdx() );
		book->fill( "nHitsFit",       event->mRunIndex, aTrack->mNHitsFit );
		book->fill( "nHitsMax",       event->mRunIndex, aTrack->mNHitsMax );
		book->fill( "nHitsDedx",      event->mRunIndex, aTrack->mNHitsDedx );
		book->fill( "nSigmaPion",     event->mRunIndex, aTrack->nSigmaPion() );
		book->fill( "nSigmaKaon",     event->mRunIndex, aTrack->nSigmaKaon() );
		book->fill( "nSigmaProton",   event->mRunIndex, aTrack->nSigmaProton() );
		book->fill( "nSigmaElectron", event->mRunIndex, aTrack->nSigmaElectron() );
		book->fill( "gDCA",           event->mRunIndex, aTrack->gDCA() );
		book->fill( "mtdDeltaY",      event->mRunIndex, mtdPid->mDeltaY );
		book->fill( "mtdDeltaZ",      event->mRunIndex, mtdPid->mDeltaZ );
		book->fill( "mtdDeltaTof",    event->mRunIndex, mtdPid->mDeltaTimeOfFlight );
		book->fill( "mtdMatchFlag",   event->mRunIndex, mtdPid->mMatchFlag );
		book->fill( "mtdHitChan",     event->mRunIndex, mtdPid->mMtdHitChan );

	}

protected:

	
};

#endif