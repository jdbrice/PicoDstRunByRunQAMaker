#ifndef PID_PDF_MAKER_H
#define PID_PDF_MAKER_H

#include "HistoAnalyzer.h"
#include "RooPlotLib.h"
#include "XmlRange.h"
#include "XmlFunction.h"
using namespace jdb;


#include <fstream>

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

		// NOTE
		// 
		// signal_i = UL - LS in ROI
		// bg_i = LS in full range
		// 
		string params_file = config.getXString( nodePath + ".output.XmlFile:url" );
		ofstream out( params_file.c_str() );

		out << XmlConfig::declarationV1;
		out << endl << "<config>" << endl;

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

			TH1D * hBgPdf = (TH1D*)get1D( ("trackQA/Like_Sign_" + name).c_str() )->Clone( ("bg_" + name).c_str() );
			hBgPdf->Sumw2();
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
					hBgPdf = (TH1D*)hBgPdf->Rebin( hb.nBins(), ("rebin_bg_" + name).c_str(), hb.bins.data() );
				}
				
				hSignal->Add( hBg, -1 );
				hSignal->Sumw2();
				hSignal->Scale( 1.0 / hSignal->Integral() );
				
				TH1D * hPdf = (TH1D*)hBgPdf->Clone( ("pdf_ratio_" + name).c_str() );
				hPdf->Divide( hSignal );


				// now lets fit each PDF!
				string p = config.q( nodePath + ".FitFunctions{name==" + name + "}" );
				if ( config.exists( p ) ){
					string f1name = "f1_" + name;
					string form = config.getString( p + ":formula" );
					INFOC( "Fitting " << quote( name ) << " to " << quote( form ) );
					TF1 * f1 = new TF1( f1name.c_str(), form.c_str() );
					if ( config.exists( p + ":min" ) && config.exists( p + ":max" ) ){
						double min = config.getDouble( p + ":min" );
						double max = config.getDouble( p + ":max" );
						hPdf->Fit( f1, "R", "", min, max );
					} else {
						hPdf->Fit( f1 );
					}
					
					f1->Write();


					map<string, string> opts;
					opts[ "name" ] = name;
					opts[ "min" ] = dts(hPdf->GetXaxis()->GetXmin());
					opts[ "max" ] = dts(hPdf->GetXaxis()->GetXmax());
					out << "\t" << XmlFunction::toXml( f1, opts ) << endl;

					delete f1;
				}
			}
		} // loop name
		out << "</config>" << endl;
	}
	
};

#endif