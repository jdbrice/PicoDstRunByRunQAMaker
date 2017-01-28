#ifndef MTD_SIGMA_MAKER_H
#define MTD_SIGMA_MAKER_H

#include "HistoAnalyzer.h"
#include "XmlFunction.h"
using namespace jdb;

#include <fstream>
#include <map>


#include "TF1.h"
#include "TMath.h"

class MtdSigmaMaker : public HistoAnalyzer
{
public:
	virtual const char* classname() const { return "MtdSigmaMaker"; }
	MtdSigmaMaker() {}
	~MtdSigmaMaker() {}

	virtual void initialize(){

	}

	TF1 * fDeltaZ = nullptr, *fDeltaY = nullptr, *fDeltaTOF = nullptr;

	virtual void make(){




		string params_file = config.getXString( nodePath + ".output.File:url" );
		ofstream out( params_file.c_str() );

		HistoBins bpt, bmtd, bTOF;
		bpt.load( config, "bins.pt" );
		bmtd.load( config, "bins.mtdDz" );
		bTOF.load( config, "bins.dTOF" );

		INFOC( bpt.toString() );
		INFOC( bmtd.toString() );

		setCurrentFile( "data" );
		book->cd();
		TH2 * uls_roi_dz = HistoBins::rebin2D( "signalDeltaZ", get<TH2>( "trackQA/Unlike_Sign_ROI_mtdDeltaZ_vs_rigidity" ), bpt, bmtd );
		TH2 * ls_roi_dz  = HistoBins::rebin2D( "RoiBgDeltaZ", get<TH2>( "trackQA/Like_Sign_ROI_mtdDeltaZ_vs_rigidity" ), bpt, bmtd );
		TH2 * ls_dz      = HistoBins::rebin2D( "BgDeltaZ", get<TH2>( "trackQA/Like_Sign_mtdDeltaZ_vs_rigidity" ), bpt, bmtd );



		INFOC( "" );
		// normalize to the ROI
		ls_dz->Scale( ls_roi_dz->Integral() / ls_dz->Integral() );

		INFOC( "Scaled Like sign" );
		// subtract like sign from unlike sign
		uls_roi_dz->Add( ls_dz, -1 );
		TH2 * sig_dz = (TH2*)book->addClone( "signal_dz", uls_roi_dz );

		INFOC( "Made PDF : " << sig_dz );
		sig_dz->FitSlicesY( );
		
		book->cd();
		TH1D *sigmas_dz = (TH1D*)gDirectory->Get("signal_dz_2");
		fDeltaZ = new TF1( "fdz", config.getXString( "Params.fDeltaZ" ).c_str() , -10, 10 );
		sigmas_dz->Fit( fDeltaZ, "R", "", config.getDouble( "Params.fDeltaZ:min" ), config.getDouble( "Params.fDeltaZ:max", 0 ));

		sigmas_dz->SetTitle( ";q*pT [GeV/c]; #sigma mtdDeltaZ [cm]" );

		out << XmlConfig::declarationV1;
		out << endl << "<config>" << endl;

		map<string, string> opts;
		opts[ "name" ] = "SigmaMtdDeltaZ";
		opts[ "min" ] = dts(fDeltaZ->GetXaxis()->GetXmin());
		opts[ "max" ] = dts(fDeltaZ->GetXaxis()->GetXmax());
		out << "\t" << XmlFunction::toXml( fDeltaZ, opts ) << endl;



		// ------------------- DeltaY ---------------------
		book->cd();
		TH2 * uls_roi_dy = HistoBins::rebin2D( "signalDeltaY", get<TH2>( "trackQA/Unlike_Sign_ROI_mtdDeltaY_vs_rigidity" ), bpt, bmtd );
		TH2 * ls_roi_dy  = HistoBins::rebin2D( "RoiBgDeltaY", get<TH2>( "trackQA/Like_Sign_ROI_mtdDeltaY_vs_rigidity" ), bpt, bmtd );
		TH2 * ls_dy      = HistoBins::rebin2D( "BgDeltaY", get<TH2>( "trackQA/Like_Sign_mtdDeltaY_vs_rigidity" ), bpt, bmtd );



		INFOC( "" );
		// normalize to the ROI
		ls_dy->Scale( ls_roi_dy->Integral() / ls_dy->Integral() );

		INFOC( "Scaled Like sign" );
		// subtract like sign from unlike sign
		uls_roi_dy->Add( ls_dy, -1 );
		TH2 * sig_dy = (TH2*)book->addClone( "signal_dy", uls_roi_dy );

		INFOC( "Made PDF : " << sig_dy );
		sig_dy->FitSlicesY( );
		
		book->cd();
		TH1D *sigmas_dy = (TH1D*)gDirectory->Get("signal_dy_2");
		fDeltaY = new TF1( "fdz", config.getXString( "Params.fDeltaY" ).c_str() , -10, 10 );
		sigmas_dy->Fit( fDeltaY, "R", "", config.getDouble( "Params.fDeltaY:min" ), config.getDouble( "Params.fDeltaY:max", 0 ));

		sigmas_dy->SetTitle( ";q*pT [GeV/c]; #sigma mtdDeltaY [cm]" );

		map<string, string> opts2;
		opts2[ "name" ] = "SigmaMtdDeltaY";
		opts2[ "min" ] = dts(fDeltaY->GetXaxis()->GetXmin());
		opts2[ "max" ] = dts(fDeltaY->GetXaxis()->GetXmax());
		out << "\t" << XmlFunction::toXml( fDeltaY, opts2 ) << endl;




		// ------------------- DeltaTOF ---------------------
		book->cd();
		TH2 * uls_roi_dtof = HistoBins::rebin2D( "signalDeltaTOF", get<TH2>( "trackQA/Unlike_Sign_ROI_mtdDeltaTOF_vs_rigidity" ), bpt, bTOF );
		TH2 * ls_roi_dtof  = HistoBins::rebin2D( "RoiBgDeltaTOF", get<TH2>( "trackQA/Like_Sign_ROI_mtdDeltaTOF_vs_rigidity" ), bpt, bTOF );
		TH2 * ls_dtof      = HistoBins::rebin2D( "BgDeltaTOF", get<TH2>( "trackQA/Like_Sign_mtdDeltaTOF_vs_rigidity" ), bpt, bTOF );



		INFOC( "" );
		// normalize to the ROI
		ls_dtof->Scale( ls_roi_dtof->Integral() / ls_dtof->Integral() );

		INFOC( "Scaled Like sign" );
		// subtract like sign from unlike sign
		
		uls_roi_dtof->Add( ls_dtof, -1 );
		TH2 * sig_dtof = (TH2*)book->addClone( "signal_dtof", uls_roi_dtof );

		INFOC( "Made PDF : " << sig_dtof );
		sig_dtof->FitSlicesY( );
		
		book->cd();
		TH1D *sigmas_dtof = (TH1D*)gDirectory->Get("signal_dtof_2");
		fDeltaTOF = new TF1( "fdz", config.getXString( "Params.fDeltaTOF" ).c_str() , -10, 10 );
		sigmas_dtof->Fit( fDeltaTOF, "R", "", config.getDouble( "Params.fDeltaTOF:min" ), config.getDouble( "Params.fDeltaTOF:max", 0 ));

		sigmas_dtof->SetTitle( ";q*pT [GeV/c]; #sigma mtdDeltaTOF [ns]" );

		map<string, string> opts3;
		opts3[ "name" ] = "SigmaMtdDeltaTOF";
		opts3[ "min" ] = dts(fDeltaTOF->GetXaxis()->GetXmin());
		opts3[ "max" ] = dts(fDeltaTOF->GetXaxis()->GetXmax());
		out << "\t" << XmlFunction::toXml( fDeltaTOF, opts3 ) << endl;


		// ------------------- nSigmaPion ---------------------
		
		HistoBins bNSigPi;
		bNSigPi.load( config, "bins.nSigPi" );
		TH2 * uls_roi_nSigPi = HistoBins::rebin2D( "signalnSigmaPion", get<TH2>( "trackQA/Unlike_Sign_ROI_nSigmaPion_vs_rigidity" ), bpt, bNSigPi );
		TH2 * ls_roi_nSigPi  = HistoBins::rebin2D( "RoiBgnSigmaPion", get<TH2>( "trackQA/Like_Sign_ROI_nSigmaPion_vs_rigidity" ), bpt, bNSigPi );
		TH2 * ls_nSigPi      = HistoBins::rebin2D( "BgnSigmaPion", get<TH2>( "trackQA/Like_Sign_nSigmaPion_vs_rigidity" ), bpt, bNSigPi );


		TH2 * sig_nSigPi = (TH2*)book->addClone( "signal_nSigPi", uls_roi_nSigPi );
		INFOC( "" );
		// normalize to the ROI
		ls_dtof->Scale( ls_roi_nSigPi->Integral() / ls_nSigPi->Integral() );

		INFOC( "Scaled Like sign" );
		// subtract like sign from unlike sign
		
		sig_nSigPi->Add( ls_roi_nSigPi, -1 );
		




		out << "</config>" << endl;

		INFOC( "DAN" );
	}
protected:
	
};


#endif