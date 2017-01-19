#ifndef COCKTAIL_SINGLE_COMPONENT_FITTER_H
#define COCKTAIL_SINGLE_COMPONENT_FITTER_H

// RooBarb
#include "TreeAnalyzer.h"
#include "HistoBins.h"
#include "Extra/format.h"
using namespace jdb;

// STL
#include <map>

// ROOT
#include "TH1D.h"


class CocktailSingleComponentFitter : public TreeAnalyzer
{
public:
	virtual const char* classname() const { return "CocktailSingleComponentFitter"; }
	CocktailSingleComponentFitter() {}
	~CocktailSingleComponentFitter() {}

	virtual void initialize(){
		TreeAnalyzer::initialize();

		massByName["eta"]      = 0.547853;
		massByName["omega"]    = 0.78265;
		massByName["phi"]      = 1.019455;
		massByName["etaprime"] = 0.95778;

		book->cd();
	}

	static double fProxy( double *x, double *par ){

		if ( nullptr == hPDF )
			return 0;

		Double_t xx = x[0];
		Int_t bin = hPDF->GetXaxis()->FindBin(xx);
		Double_t br = par[0]*hPDF->GetBinContent(bin);
		// br = br / hPDF->GetBinWidth( bin );

		return br;
	}

protected:

	map<string, double> massByName;
	static TH1D *hPDF;

	virtual void make(){
		TreeAnalyzer::preEventLoop();

		// load in the measured signal
		TFile * f = new TFile( config.getXString( nodePath + ".input.TFile:url" ).c_str(), "READ" );
		TH1D * hSignal = (TH1D*)f->Get( "gm_signal" );
		if ( nullptr == hSignal ){
			ERROR( classname(), "Signal from data is NULL" );
			return;
		}

		book->cd();

		string parent = config.getXString( nodePath + ".Component:parent" );
		string decay  = config.getXString( nodePath + ".Component:decay" );

		// hPDF = new TH1D( "dNdM", "component name; M_{#mu#mu} [GeV/c^{2}]; dN/dM", 200, 0, 2.0 );

		string hCommand = "Mll >> dNdM";
		string cut = buildCutString( config.getDouble( nodePath + ".Cuts:minPt", 0.1 ), config.getDouble( nodePath + ".Cuts:minDeltaPhi", 0.05 ) ) + buildComponentString( parent, decay );
		INFO( classname(), "chain->Draw(" << quote(hCommand) << ", " << quote( cut ) );
		chain->Draw( hCommand.c_str(), cut.c_str() );

		hPDF = (TH1D*)book->get( "dNdM" );
		INFO( classname(), "I = " << hPDF->Integral() );

		int cB1 = hPDF->FindFirstBinAbove( 1 );
		int cB2 = hPDF->FindLastBinAbove( 1 );

		
		INFO( classname(), "cB1=" << cB1 );
		INFO( classname(), "cB2=" << cB2 );
		double sigI = hSignal->Integral( cB1, cB2 );
		double comI = hPDF->Integral( cB1, cB2 );
		INFO( classname(), "sigI=" << sigI << ", comI=" << comI << ", sigI/comI=" << sigI/comI );


		double x1 = hSignal->GetBinLowEdge( cB1 );
		double x2 = hSignal->GetBinLowEdge( cB2+2 );
		
		TF1 * fC = new TF1( "fCocktail", fProxy, x1, x2, 1 );
		fC->SetParameter( 0, sigI/comI );
		fC->SetNpx( 50000 );
		hSignal->Fit( fC, "R", "", x1, x2 );
		hSignal->Fit( fC, "R", "", x1, x2 );
		// hSignal->Fit( fC, "RL", "", x1, x2 );

		fC->Write();
		hSignal->SetDirectory( gDirectory );

	}

	string buildCutString( double _minPt, double _minDeltaPhi ){
		return fmt::format( "l1PtRc>{0} && l2PtRc > {0} && fabs( l1Phi - l2Phi ) > {1}", _minPt, _minDeltaPhi );
	}
	string buildComponentString( string _parent, string _decay ){
		if ( "dalitz" == _decay )
			return (" && pPdgM >= " + dts( massByName[_parent] - 0.001) + " && pPdgM <= " + dts( massByName[_parent] + 0.001 ) + " && (nPhi != 0 && nEta != 0 && nPtMc != 0 )");
		
		return " && pPdgM >= " + dts( massByName[_parent] - 0.001) + " && pPdgM <= " + dts( massByName[_parent] + 0.001 ) + " && nPhi == 0 && nEta == 0 && nPtMc == 0 && nM == 0";
	}


	
};



#endif