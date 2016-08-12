#ifndef MIXED_EVENT_MASS_PLOTTER_H
#define MIXED_EVENT_MASS_PLOTTER_H

//RooBarb
#include "TreeAnalyzer.h"
#include "CutCollection.h"

//ROOT
#include "TLorentzVector.h"

// Project
#include "MixedCandidateSkimmer.h"
#include "CandidateFilter.h"
#include "EventHasher.h"




class MixedEventMassPlotter : public MixedCandidateSkimmer
{
public:
	virtual const char * classname() const { return "MixedEventMassPlotter"; }
	MixedEventMassPlotter(){}
	~MixedEventMassPlotter(){}

	virtual void initialize(){
		MixedCandidateSkimmer::initialize();

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

		eventA = shared_ptr<CandidateEvent>( new CandidateEvent() );
		eventB = shared_ptr<CandidateEvent>( new CandidateEvent() );

		trackA = shared_ptr<CandidateTrack>( new CandidateTrack() );
		trackB = shared_ptr<CandidateTrack>( new CandidateTrack() );

		meb.load( config, nodePath + ".MixedEventBins" );

		maxToMix = config.getInt( nodePath + ":maxToMix", 10 );
		INFO( classname(), "Max # to mix = " << maxToMix );

		// build the buffers
		initializeBuffers();

	}


protected:

	// class CandidateClone {
	// 	shared_ptr< CandidateEvent > event;
	// 	shared_ptr< CandidateTrack > track;
	// };
	double m1, m2;
	CutCollection trackCuts;
	bool makeTrackCutQA = false;

	int maxToMix = 10;
	vector<shared_ptr<CandidateEvent>> eventBuffer;
	vector<shared_ptr<CandidateTrack>> trackBuffer;
	vector<shared_ptr<CandidateTrackMtdPidTraits>> mtdPidTraitsBuffer;
	EventHasher meb;


	shared_ptr<CandidateEvent> eventA, eventB;
	shared_ptr<CandidateTrack> trackA, trackB;
	shared_ptr<CandidateTrackMtdPidTraits> mtdPidA, mtdPidB;

	void initializeBuffers(){
		for ( int i = 0; i < maxToMix; i++ ){

			eventBuffer.push_back( shared_ptr<CandidateEvent>( new CandidateEvent() ) );
			trackBuffer.push_back( shared_ptr<CandidateTrack>( new CandidateTrack() ) );
			mtdPidTraitsBuffer.push_back( shared_ptr<CandidateTrackMtdPidTraits>( new CandidateTrackMtdPidTraits() ) );

		}
	}


	Long64_t fillBuffer( Long64_t eventStart = 0 ){

		int nFound = 0;

		Long64_t iEvent = eventStart;

		while( true ) {
			Long64_t read = chain->GetEntry(iEvent);
			DEBUG( classname(),"Inner Event " << iEvent );

			if ( read <= 0 ){ // break if we read past end or hit limit
				// TODO: maybe wrap to ensure fully filled buffers
				break;
			}

			eventBuffer[ nFound ]->copy( event );
			trackBuffer[ nFound ]->copy( tracks );
			mtdPidTraitsBuffer[ nFound ]->copy( mtdPidTraits );
			nFound++;

			DEBUG( classname(), "Filling buffer with iEvent =" << iEvent);


			iEvent ++;

			if ( nFound >= maxToMix ){
				break;
			}
			
		}

		// return the next event index to read
		// break happens after ++ so this event has not been read yet
		return iEvent;

	}

	virtual void eventLoop( ){
		DEBUG( classname(), "EventLoop" );

		TaskTimer t;
		t.start();

		TaskProgress tp( "Event Loop", nEventsToProcess );
		
		// loop over all events 
		Long64_t iEvent = 0;
		
		while (true){ // what could go wrong 
			Long64_t read = chain->GetEntry(iEvent);
			
			if ( read <= 0 || (nEventsToProcess >= 0 && iEvent >= nEventsToProcess) ){ // break if we read past end or hit limit
				INFO( classname(), "Ending event loop on iEvent = " << iEvent );
				break;
			}

			if ( showProgress )
				tp.showProgress( iEvent );

			// analyzeEventBeforeCuts();

			if ( !keepEvent() ){
				// analyzeRejectedEvent();
				iEvent++;
				continue;
			}

			// innerLoop( iEvent );
				// analyzeEvent();
			iEvent = fillBuffer( iEvent );
			INFO( classname(), "iEvent = " << iEvent );
			makePairs();
			// iEvent++;
		} // Event Loop
		
		if ( false == showProgress ){
			INFO( classname(), "Event Loop Completed in " << t.elapsed() );
		}
	}


	bool keepTrack( CandidateTrack *aTrack, CandidateTrackMtdPidTraits * aMtdPid ){
		return CandidateFilter::isMuon( aTrack, aMtdPid, trackCuts,  makeTrackCutQA ? book : nullptr );
		// return true;
	}


	virtual void makePairs(){

		for ( int a = 0; a < maxToMix; a++ ){
			eventA = eventBuffer[ a ];
			trackA = trackBuffer[ a ];
			mtdPidA = mtdPidTraitsBuffer[ a ];
			for ( int b = a; b < maxToMix; b++ ){ // don't double count
				if ( a == b ) continue; // skip self-same pair
				eventB = eventBuffer[ b ];
				trackB = trackBuffer[ b ];
				mtdPidB = mtdPidTraitsBuffer[ b ];

				// analyse this pair
				analyzePair();
			}
		}

	}

	virtual void analyzePair(){

		// reject pairs from same event
		if ( eventA->mRunId == eventB->mRunId && eventA->mEventId == eventB->mEventId ) return;

		if ( !keepTrack( trackA.get(), mtdPidA.get() ) ) return;
		if ( !keepTrack( trackB.get(), mtdPidB.get() ) ) return;


		TLorentzVector lv1, lv2, lv;
		lv1.SetXYZM( trackA->mPMomentum_mX1, trackA->mPMomentum_mX2, trackA->mPMomentum_mX3, m1 );
		lv2.SetXYZM( trackB->mPMomentum_mX1, trackB->mPMomentum_mX2, trackB->mPMomentum_mX3, m2 );

		lv = lv1 + lv2;

		// if ( lv1.Pt() < 1.5 && lv2.Pt() < 1.5   ) continue;

		book->cd("");
		int iBin = book->get( "like_sign" )->GetXaxis()->FindBin( lv.M() );
		double bw = book->get( "like_sign" )->GetBinWidth( iBin );

		// like sign
		if ( trackA->charge() * trackB->charge() == 1 ){
			book->fill( "like_sign", lv.M(), 1.0 / bw );
			book->fill( "like_sign_pT", lv.M(), lv.Pt() );
			if ( 1 == trackA->charge()  ){
				book->fill( "like_sign_Pos", lv.M(), 1.0 / bw );
				book->fill( "like_sign_Pos_pT", lv.M(), lv.Pt(), 1.0/ bw );
			} else if ( -1 == trackA->charge()  ){
				book->fill( "like_sign_Neg", lv.M(), 1.0 / bw );
				book->fill( "like_sign_Neg_pT", lv.M(), lv.Pt(), 1.0/ bw );
			}
		} else {
			book->fill( "unlike_sign", lv.M(), 1.0/bw );
			book->fill( "unlike_sign_pT", lv.M(), lv.Pt(), 1.0/bw );
		}

	}

};

#endif