#ifndef ACCEPTANCE_FIXER_H
#define ACCEPTANCE_FIXER_H

// RooBarb
#include "HistoAnalyzer.h"
using namespace jdb;



class AcceptanceFixer : public HistoAnalyzer
{
public:
	AcceptanceFixer() {}
	~AcceptanceFixer() {}

	virtual void initialize(){
		HistoAnalyzer::initialize();
	}

	virtual void makeGeometricMean( TH1*gm, TH1* lsp, TH1* lsn ){
		if ( nullptr == gm || nullptr == lsp || nullptr == lsn ) return;

		int nBins = lsn->GetNbinsX();
		for ( int iBin = 1; iBin <= nBins; iBin++ ){
			
			double Npp = lsp->GetBinContent( iBin );
			double Nmm = lsn->GetBinContent( iBin );

			if ( 0 == Npp || 0 == Nmm ){
				gm->SetBinContent( iBin, 0 );
				gm->SetBinError( iBin, 0 );
				continue;
			}

			double Epp = lsp->GetBinError( iBin ) / Npp;
			double Emm = lsn->GetBinError( iBin ) / Nmm;

			double N = 2 * sqrt( Npp * Nmm ); // includes the factor of 2!!!
			// Q = x^n  
			// ->
			// dQ/Q = n * dx/x
			double E = (Epp+Emm) * 0.5 * N;
			DEBUGC( "B++ = " << Npp << " +/- " << Epp );
			DEBUGC( "B-- = " << Nmm << " +/- " << Emm );

			DEBUGC( "gm = " << N << " +/- " << E );
			gm->SetBinContent( iBin, N );
			gm->SetBinError( iBin, E );
		}
	}

	virtual void makeGeometricMean( TH2*gm, TH2* lsp, TH2* lsn ){
		if ( nullptr == gm || nullptr == lsp || nullptr == lsn ) return;
		INFOC( "2D Geometric Mean" );

		int nBinsX = lsn->GetNbinsX()  ;
		int nBinsY = lsn->GetNbinsY()  ;

		
		for ( int iBinX = 1; iBinX <= nBinsX; iBinX++ ){
			for ( int iBinY = 1; iBinY <= nBinsY; iBinY++ ){
			
				int iBin = lsp->GetBin( iBinX, iBinY ) ;

				double Npp = lsp->GetBinContent( iBin );
				double Nmm = lsn->GetBinContent( iBin );

				if ( 0 == Npp || 0 == Nmm ){
					gm->SetBinContent( iBin, 0 );
					gm->SetBinError( iBin, 0 );
					continue;
				}

				double Epp = lsp->GetBinError( iBin ) / Npp;
				double Emm = lsn->GetBinError( iBin ) / Nmm;

				double N = 2 * sqrt( Npp * Nmm ); // includes factor of 2!!!
				// Q = x^n  
				// ->
				// dQ/Q = n * dx/x
				double E = (Epp+Emm) * 0.5 * N;
				DEBUGC( "B++ = " << Npp << " +/- " << Epp );
				DEBUGC( "B-- = " << Nmm << " +/- " << Emm );

				DEBUGC( "gm = " << N << " +/- " << E );
				gm->SetBinContent( iBin, N );
				gm->SetBinError( iBin, E );
			}
		}
	}

	virtual void multiplyBinByBin( TH1 * A, TH1 * B ){
		
		int nBinsX = A->GetNbinsX()  ;
		int nBinsY = A->GetNbinsY()  ;

		for ( int iBinX = 1; iBinX <= nBinsX; iBinX++ ){
			for ( int iBinY = 1; iBinY <= nBinsY; iBinY++ ){
			
				int iBin = A->GetBin( iBinX, iBinY ) ;

				double NA = A->GetBinContent( iBin );
				double EA = A->GetBinContent( iBin ) / NA;
				double NB = B->GetBinContent( iBin );
				double EB = 0;//B->GetBinContent( iBin ) / NB;

				if ( 0 >= NA ) EA = 0;
				if ( 0 >= NB ) EB = 0;

				double N = NA * NB;
				double E = sqrt( N );//(EA + EB) * N;



				A->SetBinContent( iBin,N );
				A->SetBinError( iBin,E );
			}
		}
	}


	virtual void make(){

		// B = 2 sqrt{ N++ * N-- } * (Accept Corr)
		// TH1D *


		//  Making Mixed event part 1D
		TH1D * hBpm   = get<TH1D>( "unlike_sign"   , "ME" );
		TH1D * hBpp   = get<TH1D>( "like_sign_Pos" , "ME" );
		TH1D * hBmm   = get<TH1D>( "like_sign_Neg" , "ME" );
		TH1D * hBppmm = get<TH1D>( "like_sign"     , "ME" );
		
		book->cd();
		book->addClone( "am_acorr", hBpm );
		TH1D * h = (TH1D*) book->get( "am_acorr" );
		h->Divide( hBppmm );	// (B++)+(B--)

		// make the geometric mean 
		book->addClone( "gmBg", hBpm );
		book->get( "gmBg" )->Reset();	// clear it out
		TH1D * hGm = (TH1D*) book->get( "gmBg" );
		makeGeometricMean( hGm, hBpp, hBmm );

		book->addClone( "acorr", hBpm );
		h = (TH1D*) book->get( "acorr" );
		h->Divide( hGm );

		TH2D * h2Bpm   = get<TH2D>( "unlike_sign_pT"   , "ME" );
		TH2D * h2Bpp   = get<TH2D>( "like_sign_Pos_pT" , "ME" );
		TH2D * h2Bmm   = get<TH2D>( "like_sign_Neg_pT" , "ME" );
		TH2D * h2Bppmm = get<TH2D>( "like_sign_pT"     , "ME" );

		
		book->addClone( "me_gmBg_pT_vs_m", h2Bpm );
		TH2D * h2Gm = (TH2D*) book->get( "me_gmBg_pT_vs_m" );
		h2Gm->Reset();
		makeGeometricMean( h2Gm, h2Bpp, h2Bmm );


		book->addClone( "acorr_pT_vs_m", h2Bpm );
		TH2D * h2Acorr = (TH2D*) book->get( "acorr_pT_vs_m" );
		h2Acorr->Divide( h2Gm );

		book->addClone( "am_acorr_pT_vs_m", h2Bpm );
		TH2D* h2Am = (TH2D*) book->get( "am_acorr_pT_vs_m" );
		h2Am->Divide( h2Bppmm );


		// Same Event Geometric Mean Background
		book->addClone( "se_gmBg_pT_vs_m", h2Bpm );
		TH2D *h2ls = (TH2D*)book->get( "se_gmBg_pT_vs_m" );
		h2ls->Reset();
		
		TH2D * h2sig = get<TH2D>( "unlike_sign_pT", "SE" );

		TH2D * h2lsp = get<TH2D>( "like_sign_Pos_pT", "SE" );
		TH2D * h2lsn = get<TH2D>( "like_sign_Neg_pT", "SE" );
		makeGeometricMean( h2ls, h2lsp, h2lsn );


		book->addClone( "corr_bg", h2ls );
		TH2D * h2corrBg = (TH2D*)book->get( "corr_bg" );
		// h2corrBg->Multiply( h2Gm );
		// multiplyBinByBin( h2corrBg, h2Acorr );


		book->addClone( "acsignal", h2sig );
		h2sig = (TH2D*)book->get( "acsignal" );

		// h2sig->Add( h2corrBg, -1 );

		// Apply trigger patch correction!
		TH2D * tpcorr= get<TH2D>( "uls_tp_pT_vs_m", "Trigger" );
		TH2D * tpcorrden= get<TH2D>( "uls_all_pT_vs_m", "Trigger" );
		tpcorr->Divide( tpcorrden );
		h2sig->Divide( tpcorr );
		h2corrBg->Divide( tpcorr );

		TH1D * hSig = h2sig->ProjectionX( "s1D" );
		TH1D * hBg  = h2corrBg->ProjectionX( "acBg_vs_m" );

		hSig->Add( hBg, -1 );

		// hSig->Add(  ); 
		book->add( "s1D", hSig );




		// Trigger Correction (Kinematic Acceptance)
		




	}
	protected:


};


#endif