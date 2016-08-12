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


	}


protected:

	double m1, m2;
	CutCollection trackCuts;
	bool makeTrackCutQA = false;

	int nToMix = 10;
	EventHasher meb;


	shared_ptr<CandidateEvent> eventA, eventB;
	shared_ptr<CandidateTrack> trackA, trackB;


	void innerLoop( Long64_t iEventA ){


		// save eventA first
		eventA->copy( event );
		trackA->copy( tracks );
		// INFO( classname(), "EventA Bin = " << meb.eventBin( eventA.get() ) );

		int eventABin = meb.hash( eventA.get() );
		int nFound = 0;
		// for ( Long64_t iEventB = iEventA + 1; iEventB <= iEventA + 1000; iEventB++ ){
		
		INFO( classname(),"============================ Inner Loop =================================== " );
		Long64_t iEventB = iEventA + 1;
		while( true ) {
			Long64_t read = chain->GetEntry(iEventB);
			INFO( classname(),"Inner Event " << iEventB );

			if ( read <= 0 ){ // break if we read past end or hit limit
				break;
			}

			// skip same event pairs
			if ( eventA->mRunId == event->mRunId && eventA->mEventId == event->mEventId ) { 
				iEventB++;
				continue;
			}


			if ( meb.hash( event ) == eventABin ){
				eventB->copy( event );
				trackB->copy( tracks );

				analyzeEvent();	
				nFound ++;
			}

			iEventB ++;

			// if ( nFound >= nToMix ){
			// 	break;
			// }
			
		}


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

			analyzeEventBeforeCuts();

			if ( !keepEvent() ){
				analyzeRejectedEvent();
				iEvent++;
				continue;
			}

			innerLoop( iEvent );
				// analyzeEvent();

			iEvent++;
		} // Event Loop
		
		if ( false == showProgress ){
			INFO( classname(), "Event Loop Completed in " << t.elapsed() );
		}
	}


	bool keepTrack( CandidateTrack *aTrack ){
		// CandidateTrackMtdPidTraits *mtdPid = (CandidateTrackMtdPidTraits *)mtdPidTraits->At( aTrack->mMtdPidTraitsIndex );
		// return CandidateFilter::isMuon( aTrack, mtdPid, trackCuts,  makeTrackCutQA ? book : nullptr );
		return true;
	}


	virtual void analyzeEvent(){
		// INFO( classname(), "" );

		// INFO( classname(), "EventA " << eventA->mEventId );
		// INFO( classname(), "EventB " << eventB->mEventId );

		if ( !keepTrack( trackA.get() ) ) return;
		if ( !keepTrack( trackB.get() ) ) return;


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


		// INFO( classname(), event->eventId );

		// book->cd("");
		// TAxis * axis = book->get( "unlike_sign" )->GetXaxis();


		// int nTracks = tracks->GetEntries();
		// for ( int iTrack = 0; iTrack < nTracks; iTrack++ ){
		// 	CandidateTrack* trackA = (CandidateTrack*)tracks->At( iTrack );
		// 	if ( !keepTrack( trackA ) ) continue;

		// 	for ( int jTrack = iTrack; jTrack < nTracks; jTrack++ ){
		// 		if ( iTrack == jTrack ) continue;
		// 		CandidateTrack* trackB = (CandidateTrack*)tracks->At( jTrack );
		// 		if ( !keepTrack( trackB ) ) continue;

		// 		TLorentzVector lv1, lv2, lv;
		// 		lv1.SetXYZM( aTrack->mPMomentum_mX1, aTrack->mPMomentum_mX2, aTrack->mPMomentum_mX3, m1 );
		// 		lv2.SetXYZM( trackB->mPMomentum_mX1, trackB->mPMomentum_mX2, trackB->mPMomentum_mX3, m2 );

		// 		lv = lv1 + lv2;

		// 		// if ( lv1.Pt() < 1.5 && lv2.Pt() < 1.5   ) continue;

		// 		book->cd("");
		// 		int iBin = book->get( "like_sign" )->GetXaxis()->FindBin( lv.M() );
		// 		double bw = book->get( "like_sign" )->GetBinWidth( iBin );

		// 		// like sign
		// 		if ( aTrack->charge() * trackB->charge() == 1 ){
		// 			book->fill( "like_sign", lv.M(), 1.0 / bw );
		// 			book->fill( "like_sign_pT", lv.M(), lv.Pt() );
		// 			if ( 1 == aTrack->charge()  ){
		// 				book->fill( "like_sign_Pos", lv.M(), 1.0 / bw );
		// 				book->fill( "like_sign_Pos_pT", lv.M(), lv.Pt(), 1.0/ bw );
		// 			} else if ( -1 == aTrack->charge()  ){
		// 				book->fill( "like_sign_Neg", lv.M(), 1.0 / bw );
		// 				book->fill( "like_sign_Neg_pT", lv.M(), lv.Pt(), 1.0/ bw );
		// 			}
		// 		} else {
		// 			book->fill( "unlike_sign", lv.M(), 1.0/bw );
		// 			book->fill( "unlike_sign_pT", lv.M(), lv.Pt(), 1.0/bw );
		// 		}
		// 	}
		// }

	}

	
};

#endif