#ifndef PID_PDF_MAKER_H
#define PID_PDF_MAKER_H

#include "HistoAnalyzer.h"
#include "RooPlotLib.h"
using namespace jdb;

class PidPdfMaker : public HistoAnalyzer
{
public:
	PidPdfMaker() {}
	~PidPdfMaker() {}

	virtual void initialize(){
		HistoAnalyzer::initialize();

	}
protected:

	virtual void make(){

		book->cd( );

		RooPlotLib rpl;


		for ( string name : config.getStringVector( nodePath + ".CutNames" ) ){
			INFO( classname(), "CutName : " << name );
			string cat = "Unlike_Sign_ROI_";
			TH1D * hSignalBg = (TH1D*)get1D( "trackQA/" + cat + name );
			TH1D * hBg = (TH1D*)get1D( "trackQA/Like_Sign_ROI_" + name );

			INFO( classname(), "Got Signal+Bg = " << hSignalBg );
			INFO( classname(), "Got Bg = " << hBg );

			if ( nullptr == hBg || nullptr == hSignalBg ){
				ERROR( classname(), "Null Histo" );
				continue;
			}

			TH1D * hBgPdf = (TH1D*)get1D( ("trackQA/Like_Sign_" + name).c_str() )->Clone( ("background_" + name).c_str() );
			hBgPdf->Scale( 1.0 / hBgPdf->Integral() );


			rpl.style( hBgPdf ).set( "linecolor", "red" );
			TH1D * hSignal = (TH1D*)hSignalBg->Clone( ("signal_" + name).c_str() );
			
			// book->clone( cat + "_" + name, "signal_" + name );
			// TH1D * hSignal = (TH1D*)book->get( "signal_" + name );
			// TH1D * hBg = (TH1D*)book->get( string("Like_Sign_ROI_") + name );

			if ( hSignal && hBg ){
				string bnp = config.q( nodePath + ".Bins.HistoBins{name==" + name + "}" );
				INFO(classname(), "Looking for new bins @ " << bnp );
				if ( config.exists( bnp ) ){
					HistoBins hb( config, bnp );
					INFO( classname(), "Bins : " << hb.toString() );
					hSignal = (TH1D*)hSignal->Rebin( hb.nBins(), ("rebin_signal_" + name).c_str(), hb.bins.data() );
					hBgPdf = (TH1D*)hBgPdf->Rebin( hb.nBins(), ("rebin_background_" + name).c_str(), hb.bins.data() );
				}
				
				hSignal->Add( hBg, -1 );
				hSignal->Scale( 1.0 / hSignal->Integral() );
				TH1D * hPdf = (TH1D*)hSignal->Clone( ("pdf_ratio_" + name).c_str() );
				hPdf->Divide( hBgPdf );
			}

			

			
		}
	}
	
};

#endif