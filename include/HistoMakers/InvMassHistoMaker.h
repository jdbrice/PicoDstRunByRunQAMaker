#ifndef INV_MASS_HISTO_MAKER_H
#define INV_MASS_HISTO_MAKER_H

#include "TreeAnalyzer.h"

#include "CandidatePairTreeReader.h"
#include "CandidateEventReader.h"

#include <memory>

#include "TH1D.h"
#include "TH2D.h"

class InvMassHistoMaker : public TreeAnalyzer
{
public:
	virtual const char * classname() const { return "InvMassHistoMaker"; }
	InvMassHistoMaker() {}
	~InvMassHistoMaker() {}

	CandidateEvent * wEvent;
	virtual void initialize(){
		TreeAnalyzer::initialize();

		pairReader = shared_ptr<CandidatePairTreeReader>( new CandidatePairTreeReader( chain ) );
		eventReader = shared_ptr<CandidateEventReader>( new CandidateEventReader( chain ) );

		book->cd("");

		dimuonBins.load( config, "dimuonBins.invMass" );

		INFO( classname(), "Invariant mass Bins : " << dimuonBins.toString() );
	}

	HistoBins dimuonBins;
	TH1D * h_like_sign, *h_unlike_sign;
	TH2D * h_like_sign_vs_pt, *h_unlike_sign_vs_pt;

	virtual bool keepEvent(){
		return true;
	}

	virtual void preEventLoop(){
		TreeAnalyzer::preEventLoop();
		INFO( classname(), "Aliasing Histograms" );

		book->cd( "" );
		h_like_sign = (TH1D*)book->get( "like_sign" );
		h_like_sign_vs_pt = (TH2D*)book->get2D( "like_sign_pT" );

		h_unlike_sign = (TH1D*)book->get( "unlike_sign" );
		h_unlike_sign_vs_pt = (TH2D*)book->get2D( "unlike_sign_pT" );

		INFO( classname(), "Histogram aliasing complete" );
	}

	virtual void analyzeEvent(){

		CandidatePair * pair;
		int nPairs = pairReader->getNPairs();
		for ( int iPair = 0; iPair < nPairs; iPair++ ){
			pair = pairReader->getPair( iPair );
			if ( nullptr == pair ){
				ERROR( classname(), "nullptr pair? How is it possible" );
				continue;
			}
			analyzePair( pair );
		}
	}

	void analyzePair( CandidatePair * pair ){
		TLorentzVector lv;
		lv.SetXYZM( pair->mMomentum_mX1, pair->mMomentum_mX2, pair->mMomentum_mX3, pair->mMass );

		double mass = lv.M();
		double pt = lv.Pt();
		int iBin = dimuonBins.findBin( mass );
		if ( iBin < 0 ) return;

		double bw = dimuonBins.binWidth( iBin );
		double weight = 1.0 / bw;

		int bin16 = 16;
		CandidateEvent* evt = eventReader->getEvent();
		if ( evt != nullptr )
			bin16 = evt->mBin16;

		if ( abs(pair->mChargeSum) == 2 ){
			h_like_sign->Fill( mass, weight );
			h_like_sign_vs_pt->Fill( mass, pt, weight );
			// book->fill( "like_sign_bin16", mass, bin16 );
			// book->fill( "like_sign_gRefMult", mass, evt->mGRefMult );

			if ( 2 == pair->mChargeSum  ){
				book->fill( "like_sign_Pos", lv.M(), 1.0 / bw );
				book->fill( "like_sign_Pos_pT", lv.M(), lv.Pt(), 1.0/ bw );
			} else if ( -2 == pair->mChargeSum  ){
				book->fill( "like_sign_Neg", lv.M(), 1.0 / bw );
				book->fill( "like_sign_Neg_pT", lv.M(), lv.Pt(), 1.0/ bw );
			}
		} else {
			h_unlike_sign->Fill( mass, weight );
			h_unlike_sign_vs_pt->Fill( mass, pt, weight );
			// book->fill( "unlike_sign_bin16", mass, bin16 );
			// book->fill( "unlike_sign_gRefMult", mass, evt->mGRefMult );
		}
	}

protected:
	shared_ptr<CandidatePairTreeReader> pairReader;
	shared_ptr<CandidateEventReader> eventReader;
};

#endif
