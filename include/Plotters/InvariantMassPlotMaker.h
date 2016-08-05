#ifndef INVARIANT_MASS_PLOT_MAKER_H
#define INVARIANT_MASS_PLOT_MAKER_H

#include "HistoAnalyzer.h"


#include "RooPlotLib.h"

class InvariantMassPlotMaker : public HistoAnalyzer
{
public:
	InvariantMassPlotMaker() {}
	~InvariantMassPlotMaker() {}

	virtual void initialize(){
		HistoAnalyzer::initialize();

	}

	virtual void make(){
		
		string cwd = config.getString( "CWD:out" );
		RooPlotLib rpl;

		TH1D * unlike_sign = (TH1D*)inFile->Get( "unlike_sign" );
		TH1D * like_sign = (TH1D*)inFile->Get( "like_sign" );

		// unlike_sign->RebinX( 3 );
		// like_sign->RebinX( 3 );

		rpl.style( unlike_sign )
			.set( "lw", 2 )
			.set( "color", kBlack )
			.set( "markerstyle", 8 )
			.set( "markersize", 1 )
			.set( "xr", 0, 8 )
			.set( "optstat", 0 )
			.set( "yto", 1.0 )
			.set( "logy", 1 )
			.set( "title", "; M_{#mu#mu} [GeV/c^{2}]; dN/dM_{#mu#mu}" )
			.draw();
		rpl.style( like_sign )
			.set( "lw", 2 )
			.set( "color", kRed )
			.set( "markerstyle", 8 )
			.set( "markersize", 1 )
			.set( "draw", "same" )
			.draw();

		TLegend leg( 0.7, 0.8, 0.9, 0.9 );
		leg.AddEntry( unlike_sign, "unlike sign", "lp" );
		leg.AddEntry( like_sign, "like sign", "lp" );
		leg.Draw("same");

		reporter->saveImage( cwd + "invariant_mass.pdf" );

		rpl.style( unlike_sign )
			.set( "color", kBlack )
			.set( "markerstyle", 8 )
			.set( "markersize", 1 )
			.set( "xr", 0.2, 1.1 )
			.set( "optstat", 0 )
			.set( "yto", 1.0 )
			.set( "logy", 1 )
			.set( "title", "; M_{#mu#mu} [GeV/c^{2}]; dN/dM_{#mu#mu}" )
			.draw();
		rpl.style( like_sign )
			.set( "color", kRed )
			.set( "markerstyle", 8 )
			.set( "markersize", 1 )
			.set( "draw", "same" )
			.draw();

		reporter->saveImage( cwd + "invariant_mass_lmr.pdf" );

		rpl.style( unlike_sign )
			.set( "color", kBlack )
			.set( "markerstyle", 8 )
			.set( "markersize", 1 )
			.set( "xr", 1.0, 3.05 )
			.set( "optstat", 0 )
			.set( "yto", 1.0 )
			.set( "logy", 1 )
			.set( "title", "; M_{#mu#mu} [GeV/c^{2}]; dN/dM_{#mu#mu}" )
			.draw();
		rpl.style( like_sign )
			.set( "color", kRed )
			.set( "markerstyle", 8 )
			.set( "markersize", 1 )
			.set( "draw", "same" )
			.draw();

		reporter->saveImage( cwd + "invariant_mass_imr.pdf" );

		rpl.style( unlike_sign )
			.set( "color", kBlack )
			.set( "markerstyle", 8 )
			.set( "markersize", 1 )
			.set( "xr", 2.8, 8.0 )
			.set( "optstat", 0 )
			.set( "yto", 1.0 )
			.set( "logy", 1 )
			.set( "title", "; M_{#mu#mu} [GeV/c^{2}]; dN/dM_{#mu#mu}" )
			.draw();
		rpl.style( like_sign )
			.set( "color", kRed )
			.set( "markerstyle", 8 )
			.set( "markersize", 1 )
			.set( "draw", "same" )
			.draw();

		reporter->saveImage( cwd + "invariant_mass_hmr.pdf" );



		rpl.style( unlike_sign )
			.set( "xr", 2.8, 3.5 )
			.draw();
		rpl.style( like_sign )
			.set( "draw", "same" )
			.draw();

		reporter->saveImage( cwd + "invariant_mass_jpsi.pdf" );

		TH2D * unlike_sign_pT = (TH2D*)inFile->Get( "unlike_sign_pT" );
		TH2D * like_sign_pT = (TH2D*)inFile->Get( "like_sign_pT" );

		// unlike_sign_pT->RebinX( 8 );
		// like_sign_pT->RebinX( 8 );
		// unlike_sign_pT->RebinY( 8 );
		// like_sign_pT->RebinY( 8 );

		rpl.style( unlike_sign_pT )
			.set( "draw", "colz" )
			.set( "logz", 1 )
			.set( "logy", 0 )
			.set( "xr", 0, 8 )
			.set( "yr", 0, 8 )
			.draw();

		reporter->saveImage( cwd + "unlike_sign_vs_pT.png" );

		rpl.style( like_sign_pT )
			.set( "draw", "colz" )
			.set( "logz", 1 )
			.set( "logy", 0 )
			.set( "xr", 0, 8 )
			.set( "yr", 0, 8 )
			.draw();

		reporter->saveImage( cwd + "like_sign_vs_pT.png" );

	}

protected:
	
};


#endif