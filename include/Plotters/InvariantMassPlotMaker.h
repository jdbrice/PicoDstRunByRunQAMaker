#ifndef INVARIANT_MASS_PLOT_MAKER_H
#define INVARIANT_MASS_PLOT_MAKER_H

#include "TLatex.h"

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


	double significance( TH1 * hus, TH1 * hls, double min, double max ){
		int b1 = hus->GetXaxis()->FindBin( min );
		int b2 = hus->GetXaxis()->FindBin( max );

		double rs = hus->Integral( b1, b2 );
		double bg = hls->Integral( b1, b2 );

		double s = ( rs - bg );
		double sig = s / sqrt( s + 2 * bg );
		return sig;
	}

	virtual void make(){
		

		setCurrentFile( "data" );
		INFO( classname(), "inFile : " << inFile );
		string cwd = config.getString( "CWD:out" );
		RooPlotLib rpl;

		TH1D * unlike_sign = (TH1D*)get1D( "raw_signal" );
		TH1D * like_sign = (TH1D*)inFile->Get( "geom_mean_bg" );
		TH1D * signal_minus_bg = (TH1D*)get1D( "signal_minus_geom_mean" );

		// unlike_sign->RebinX( 3 );
		// like_sign->RebinX( 3 );

		// gPad->SetLeftMargin( 0.1 );
		gPad->SetLeftMargin( 0.11 );
		gPad->SetRightMargin( 0.025 );

		TLatex latex;
		latex.SetTextAlign(12);  //centered
		latex.SetTextSize(0.025);

		rpl.style( unlike_sign )
			// .set( "lw", 2 )
			// .set( "color", kBlack )
			// .set( "markerstyle", 1 )
			// .set( "markersize", 1 )
			.set( "xr", 0, 4.2 )
			// .set( "yr", 1e2, 2e5 )
			// .set( "optstat", 0 )
			// .set( "yto", 1.0 )
			// .set( "logy", 1 )
			.set( "title", "Run15 pp #sqrt{s}=200 GeV ; M_{#mu#mu} [GeV/c^{2}]; dN/dM_{#mu#mu} [c^{2}/GeV]" )
			// .set( "draw", "E1" )
			.draw()
			.set( config, "Style.unlike_sign" )
			.draw();

		rpl.style( like_sign )
			.set( "lw", 2 )
			.set( "color", kBlue )
			.set( "markerstyle", 1 )
			.set( "markersize", 1 )
			.set( "draw", "sameE1" )
			.draw();
		rpl.style( signal_minus_bg )
			.set( "lw", 2 )
			.set( "color", kRed )
			.set( "markerstyle", 1 )
			.set( "markersize", 1 )
			.set( "draw", "sameE1" )
			.draw();

		// TLegend leg( 0.16, 0.2, 0.45, 0.34 );
		TLegend leg( 0.26, 0.6, 0.55, 0.84 );
		leg.AddEntry( unlike_sign, "#mu^{+}#mu^{-}", "lpe" );
		leg.AddEntry( like_sign, "(#mu^{+}#mu^{+}) + (#mu^{-}#mu^{-})", "lpe" );
		leg.AddEntry( signal_minus_bg, "signal", "lpe" );
		leg.Draw("same");

		// latex.DrawLatexNDC(.2,.84,( string("[2.9, 3.2] : S/#sqrt{S+2B} = ") + dts( significance( unlike_sign, like_sign, 2.9, 3.2 ) ) ).c_str() );
		// latex.DrawLatexNDC(.2,.86,( string("[0.772, 0.792] : S/#sqrt{S+2B} = ") + dts( significance( unlike_sign, like_sign, 0.75, 0.79 ) ) ).c_str() );

		// gPad->Clear();

		reporter->saveImage( cwd + "invariant_mass.pdf" );
		reporter->saveImage( cwd + "invariant_mass.eps" );

		rpl.style( unlike_sign )
			.set( "color", kBlack )
			.set( "markerstyle", 1 )
			.set( "markersize", 1 )
			.set( "xr", 0.2, 1.8 )
			.set( "optstat", 0 )
			.set( "yto", 1.0 )
			.set( "logy", 1 )
			.set( "title", "; M_{#mu#mu} [GeV/c^{2}]; dN/dM_{#mu#mu}" )
			.draw();
		rpl.style( like_sign )
			.set( "color", kBlue )
			.set( "markerstyle", 1 )
			.set( "markersize", 1 )
			.set( "draw", "same" )
			.draw();
		rpl.style( signal_minus_bg )
			.set( "lw", 2 )
			.set( "color", kRed )
			.set( "markerstyle", 1 )
			.set( "markersize", 1 )
			.set( "draw", "sameE1" )
			.draw();

		leg.Draw("same");
		reporter->saveImage( cwd + "invariant_mass_lmr.pdf" );

		rpl.style( unlike_sign )
			.set( "color", kBlack )
			.set( "markerstyle", 1 )
			.set( "markersize", 1 )
			.set( "xr", 1.0, 3.05 )
			.set( "optstat", 0 )
			.set( "yto", 1.0 )
			.set( "logy", 1 )
			.set( "title", "; M_{#mu#mu} [GeV/c^{2}]; dN/dM_{#mu#mu}" )
			.draw();
		rpl.style( like_sign )
			.set( "color", kRed )
			.set( "markerstyle", 1 )
			.set( "markersize", 1 )
			.set( "draw", "same" )
			.draw();

		reporter->saveImage( cwd + "invariant_mass_imr.pdf" );

		rpl.style( unlike_sign )
			.set( "color", kBlack )
			.set( "markerstyle", 1 )
			.set( "markersize", 1 )
			.set( "xr", 2.8, 8.0 )
			.set( "optstat", 0 )
			.set( "yto", 1.0 )
			.set( "logy", 1 )
			.set( "title", "; M_{#mu#mu} [GeV/c^{2}]; dN/dM_{#mu#mu}" )
			.draw();
		rpl.style( like_sign )
			.set( "color", kRed )
			.set( "markerstyle", 1 )
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

		// TH2D * unlike_sign_pT = (TH2D*)inFile->Get( "unlike_sign_pT" );
		// TH2D * like_sign_pT = (TH2D*)inFile->Get( "like_sign_pT" );

		// // unlike_sign_pT->RebinX( 8 );
		// // like_sign_pT->RebinX( 8 );
		// // unlike_sign_pT->RebinY( 8 );
		// // like_sign_pT->RebinY( 8 );

		// rpl.style( unlike_sign_pT )
		// 	.set( "draw", "colz" )
		// 	.set( "logz", 1 )
		// 	.set( "logy", 0 )
		// 	.set( "xr", 0, 8 )
		// 	.set( "yr", 0, 8 )
		// 	.draw();

		// reporter->saveImage( cwd + "unlike_sign_vs_pT.png" );

		// rpl.style( like_sign_pT )
		// 	.set( "draw", "colz" )
		// 	.set( "logz", 1 )
		// 	.set( "logy", 0 )
		// 	.set( "xr", 0, 8 )
		// 	.set( "yr", 0, 8 )
		// 	.draw();

		// reporter->saveImage( cwd + "like_sign_vs_pT.png" );

	}

protected:
	
};


#endif