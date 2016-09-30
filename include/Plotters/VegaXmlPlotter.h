#ifndef VEGA_XML_PLOTTER_H
#define VEGA_XML_PLOTTER_H

#include "TaskRunner.h"
#include "RooPlotLib.h"

#include <map>
#include <algorithm>
#include <vector>

#include "TFile.h"
#include "TCanvas.h"
#include "TH1.h"

class VegaXmlPlotter : public TaskRunner
{
public:
	virtual const char* classname() const { return "VegaXmlPlotter"; }
	VegaXmlPlotter() {}
	~VegaXmlPlotter() {}

	virtual void initialize(){
		
	}

	virtual void make() {

		loadDataFiles();

		Logger::setGlobalLogLevel( "debug" );
		makePlots();
		

	}

	map<string, TFile*> dataFiles;
	virtual void loadDataFiles(){

		vector<string> data_nodes = config.childrenOf( nodePath, "Data" );

		for ( string path : data_nodes ){
			if ( config.exists( path + ":name" ) ){
				string name= config.getXString( path+":name" );
				string url= config.getXString( path+":url" );
				INFO( classname(), "Data name=" << name << " @ " << url );
				TFile * f = new TFile( url.c_str() );
				dataFiles[ name ] = f;
			}
		}
	} // loadDataFiles


	virtual void makePlots(){
		vector<string> plot_paths = config.childrenOf( nodePath, "Plot" );
		INFO( classname(), "Found " << plot_paths.size() << plural( plot_paths.size(), " Plot", " Plots" ) );
		for ( string path : plot_paths ){

			if ( config.exists( path + ".Palette" ) ){
				gStyle->SetPalette( config.getInt( path + ".Palette" ) );
			}

			makeHistograms( path );

		}
	}

	virtual void makeMargins( string _path ){
		if ( config.exists( _path + ".Margins:top" ) )
			gPad->SetTopMargin( config.getDouble( _path + ".Margins:top" ) );
		if ( config.exists( _path + ".Margins:right" ) )
			gPad->SetRightMargin( config.getDouble( _path + ".Margins:right" ) );
		if ( config.exists( _path + ".Margins:bottom" ) )
			gPad->SetBottomMargin( config.getDouble( _path + ".Margins:bottom" ) );
		if ( config.exists( _path + ".Margins:left" ) )
			gPad->SetLeftMargin( config.getDouble( _path + ".Margins:left" ) );
		
	}
	virtual void makeHistograms( string _path ){
		Logger::setGlobalLogLevel( "debug" );

		TCanvas * c = new TCanvas( "c" );
		c->cd();
		makeMargins( _path );
		RooPlotLib rpl;

		map<string, TH1*> histos;

		vector<string> hist_paths = config.childrenOf( _path, "Histo" );
		sort( hist_paths.begin(), hist_paths.end() );
		bool init = false;
		int iHist = 0;
		for ( string hpath : hist_paths ){
			string name= config[ hpath + ":name" ];
			INFO( classname(), "Found Histo [" << name << "]" );

			string data = config.getXString( hpath + ":data" );
			if ( dataFiles.count( data ) <= 0 || !dataFiles[ data ] ) continue;
			
			TH1 * h = (TH1*)dataFiles[ data ]->Get( name.c_str() )->Clone( ("hist_" + ts(iHist)).c_str() );
			INFO( classname(), "Got " << h );
			if ( nullptr == h ) continue;
			histos[ name ] = h;

			// transforms
			if ( config.exists( hpath + ".Scale" ) && config.getDouble( hpath + ".Scale" ) ){
				h->Scale( config.getDouble( hpath + ".Scale" ) );
			}


			// offCan->cd();
			// // rpl.style( h ).draw();
			
			if ( !init ){
				init = true;
				h->Draw();
				// INFO( classname(), config.getXString( hpath + ".style:title" ) );
				// h->SetTitle( config.getXString( hpath + ".style:title" ).c_str() );
			} else {
				h->Draw( "same" );
			}
			

			
			rpl.style( h ).set( config, hpath + ".style" ).draw();

			INFO( classname(), "Drawing " << name );
			iHist++;
		}

		if ( config.exists( _path + ".Legend" ) ){
			INFO( classname(), "Legend" );

			TLegend * leg = new TLegend( 
				config.getDouble( _path + ".Legend.Position:x1", 0.1 ),
				config.getDouble( _path + ".Legend.Position:y1", 0.7 ),
				config.getDouble( _path + ".Legend.Position:x2", 0.5 ),
				config.getDouble( _path + ".Legend.Position:y2", 0.9 ) );

			for ( auto kv : histos ){
				INFO( classname(), "Legend Entry for : " << kv.first );
				string t = config.getString(  _path + ".Legend." + kv.first+ ":title", kv.first) ;
				string opt = config.getString(  _path + ".Legend." + kv.first+ ":opt", "l") ;

				leg->AddEntry( kv.second, t.c_str(), opt.c_str() );
			}
			leg->Draw( );

		}



		vector<string> exp_paths = config.childrenOf( _path, "Export" );
		for ( string epath : exp_paths ){
			if ( !config.exists( epath + ":url" ) ) continue;

			string url = config.getXString( epath + ":url" );
			gPad->Print( url.c_str() );
			INFO( classname(), "Exporting gPad to " << url );
		}






	}
	
};



#endif