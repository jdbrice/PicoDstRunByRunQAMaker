#ifndef CANDIDATE_INVARIANT_MASS_H
#define CANDIDATE_INVARIANT_MASS_H

//RooBarb
#include "TreeAnalyzer.h"

//ROOT
#include "TClonesArray.h"

#include "TLorentzVector.h"

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

	}


protected:

	double m1, m2;

	virtual void analyzeEvent(){
		// INFO( classname(), tracks->GetEntries() );
		// INFO( classname(), event->eventId );
		int nTracks = tracks->GetEntries();
		for ( int iTrack = 0; iTrack < nTracks; iTrack++ ){
			CandidateTrack* aTrack = (CandidateTrack*)tracks->At( iTrack );
			for ( int jTrack = iTrack; jTrack < nTracks; jTrack++ ){
				if ( iTrack == jTrack ) continue;
				CandidateTrack* bTrack = (CandidateTrack*)tracks->At( jTrack );

				TLorentzVector lv1, lv2, lv;
				lv1.SetXYZM( aTrack->pX, aTrack->pY, aTrack->pZ, m1 );
				lv2.SetXYZM( bTrack->pX, bTrack->pY, bTrack->pZ, m2 );

				lv = lv1 + lv2;

				if ( lv1.P() < 3.5 && lv2.P() < 3.5   ) continue;

				// like sign
				// if ( aTrack->charge * bTrack->charge == 1 ){
				// 	book->fill( "like_sign", lv.M() );
				// } else {
				// 	book->fill( "unlike_sign", lv.M() );
				// }
			}
		}

	}

	
};

#endif