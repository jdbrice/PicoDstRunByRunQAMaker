#ifndef SIGNAL_COCKTAIL_PLOTTER_H
#define SIGNAL_COCKTAIL_PLOTTER_H

#include "HistoAnalyzer.h"
using namespace jdb;



class SignalCocktailPlotter : public HistoAnalyzer
{
public:
	virtual const char* classname() const { return "SignalCocktailPlotter"; }
	SignalCocktailPlotter() {}
	~SignalCocktailPlotter() {}

	virtual void initialize(){
		HistoAnalyzer::initialize();
	}

	virtual void make(){

		book->cd();

		TH1 * hSignal = book->addClone( "hSignal", get<TH1>( "normsig", "signal" ) );
		TH1 * hRho    = book->addClone( "rho", get<TH1>( "dNdM_rho_mumu", "rho" ) );
		TH1 * hOmega  = book->addClone( "omega", get<TH1>( "dNdM_omega_mumu", "omega" ) );
		TH1 * hPhi    = book->addClone( "phi", get<TH1>( "dNdM_phi_mumu", "phi" ) );
		TH1 * hEta    = book->addClone( "eta", get<TH1>( "dNdM_eta_mumu", "eta" ) );
		TH1 * hJPsi   = book->addClone( "jpsi", get<TH1>( "dNdM_jpsi_mumu", "jpsi" ) );

		TH1 * hEtaD   = book->addClone( "eta_dalitz", get<TH1>( "dNdM_eta_gammamumu", "eta_dalitz" ) );
		TH1 * hEtaPD  = book->addClone( "etaprime_dalitz", get<TH1>( "dNdM_etaprime_gammamumu_dalitz", "etaprime_dalitz" ) );
		TH1 * hOmegaD = book->addClone( "omega_dalitz", get<TH1>( "dNdM_omega_pi0mumu", "omega_dalitz" ) );

		TH1 * hSum    = book->addClone( "sum", get<TH1>( "dNdM_rho_mumu", "rho" ) );
		hSum->Reset();


		// hSignal->Scale(4e1);
		hRho->Scale(1e2, "width");
		hOmega->Scale(1e2, "width");
		hPhi->Scale(1e2, "width");

		hEta->Scale(1e2, "width");
		hJPsi->Scale(1e2, "width");
		hEtaD->Scale(1e2, "width");
		hEtaPD->Scale(1e2, "width");
		hOmegaD->Scale(1e2, "width");


		hSum->Add( hRho );
		hSum->Add( hOmega );
		hSum->Add( hPhi );
		hSum->Add( hEta );
		hSum->Add( hJPsi );
		hSum->Add( hEtaD );
		hSum->Add( hEtaPD );
		hSum->Add( hOmegaD );
		// hSum->Add(  );

	}

protected:
};



#endif