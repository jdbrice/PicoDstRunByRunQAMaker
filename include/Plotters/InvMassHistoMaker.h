#ifndef INV_MASS_HISTO_MAKER_H
#define INV_MASS_HISTO_MAKER_H

#include "TreeAnalyzer.h"

#include "CandidatePairTreeReader.h"

#include <memory>

#include "TH1D.h"
#include "TH2D.h"

class InvMassHistoMaker : public TreeAnalyzer
{
public:
	virtual const char * classname() const { return "InvMassHistoMaker"; }
	InvMassHistoMaker() {}
	~InvMassHistoMaker() {}

	virtual void initialize(){
		TreeAnalyzer::initialize();

		treeReader = shared_ptr<CandidatePairTreeReader>( new CandidatePairTreeReader( chain ) );
		book->cd("");

		dimuonBins.load( config, "dimuonBins.mass" );

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


	}

	virtual void analyzeEvent(){


		// INFO( classname(), "N Pairs = " << treeReader->getNPairs() )
		CandidatePair * pair = treeReader->getPair();
		if ( nullptr == pair ){
			ERROR( classname(), "nullptr pair? How is it possible" );
			return;
		}

		TLorentzVector lv1, lv2, lv;
	// 	// lv1.SetXYZM( pair->d1.mPMomentum_mX1, pair->d1.mPMomentum_mX2, pair->d1.mPMomentum_mX3, 0 );	// mass not needed, only for deltaR and delta Phi
	// 	// lv2.SetXYZM( pair->d2.mPMomentum_mX1, pair->d2.mPMomentum_mX2, pair->d2.mPMomentum_mX3, 0 );

		lv.SetXYZM( pair->mMomentum_mX1, pair->mMomentum_mX2, pair->mMomentum_mX3, pair->mMass );

	// 	double dR = 0;//lv1.DeltaR( lv2 );
	// 	double dPhi = 0;//lv1.DeltaPhi( lv2 );



		// int iBin = book->get( "like_sign" )->GetXaxis()->FindBin( lv.M() );
		// double bw = book->get( "like_sign" )->GetBinWidth( iBin );
		double mass = lv.M();
		double pt = lv.Pt();
		int iBin = dimuonBins.findBin( mass );
		if ( iBin < 0 ) return;

		double bw = dimuonBins.binWidth( iBin );
		double weight = 1.0 / bw;

	// 	// like sign
		if ( pair->mChargeProduct == 1 ){
			h_like_sign->Fill( mass, weight );
			h_like_sign_vs_pt->Fill( mass, pt, weight );

			// book->fill( "like_sign_dR", lv.M(), dR, 1.0 / bw );
			// book->fill( "like_sign_dPhi", lv.M(), dPhi, 1.0 / bw );
			// book->fill( "like_sign_pT", lv.M(), lv.Pt() );
			// if ( 1 == pair->d1.charge()  ){
			// 	book->fill( "like_sign_Pos", lv.M(), 1.0 / bw );
			// 	book->fill( "like_sign_Pos_pT", lv.M(), lv.Pt(), 1.0/ bw );
			// } else if ( -1 == pair->d1.charge()  ){
			// 	book->fill( "like_sign_Neg", lv.M(), 1.0 / bw );
			// 	book->fill( "like_sign_Neg_pT", lv.M(), lv.Pt(), 1.0/ bw );
			// }
		} else {
			h_unlike_sign->Fill( mass, weight );
			h_unlike_sign_vs_pt->Fill( mass, pt, weight );
		}
	}

protected:
	shared_ptr<CandidatePairTreeReader> treeReader;
};

#endif
