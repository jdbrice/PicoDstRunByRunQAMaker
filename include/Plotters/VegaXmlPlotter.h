#ifndef VEGA_XML_PLOTTER_H
#define VEGA_XML_PLOTTER_H

#include "TaskRunner.h"
#include "RooPlotLib.h"
#include "HistoBook.h"

#include <map>
#include <algorithm>
#include <vector>
#include <memory>

#include "TFile.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TPaveStats.h"

class VegaXmlPlotter : public TaskRunner
{
public:
	virtual const char* classname() const { return "VegaXmlPlotter"; }
	VegaXmlPlotter() {}
	~VegaXmlPlotter() {}

	virtual void initialize(){
	}

	virtual void make() {

		loadData();

		Logger::setGlobalLogLevel( "debug" );
		makePlots();
	}

	// shared_ptr<HistoBook> book;
	map<string, TFile*> dataFiles;
	map<string, TChain *> dataChains;
	virtual void loadDataFile( string _path ){
		if ( config.exists( _path + ":name" ) ){
			string name = config.getXString( _path+":name" );
			string url = config.getXString( _path+":url" );
			INFO( classname(), "Data name=" << name << " @ " << url );
			TFile * f = new TFile( url.c_str() );
			dataFiles[ name ] = f;
		}
	} // loadDataFiles

	virtual void loadChain( string _path ){
		string name     = config.getXString( _path + ":name" );
		string treeName = config.getXString( _path + ":treeName" );
		string url      = config.getXString( _path + ":url" );
		int maxFiles    = config.getInt( _path + ":maxFiles", -1 );

		dataChains[ name ] = new TChain( treeName.c_str() );
		ChainLoader::loadList( dataChains[ name ], url, maxFiles );
		INFO( classname(), "Loaded TTree[ name=" << name << "] from url: " << url );
		int nFiles = 0;
		if ( dataChains[name]->GetListOfFiles() )
			nFiles = dataChains[name]->GetListOfFiles()->GetEntries();
		INFO( classname(), "Chain has " << nFiles << plural( nFiles, " file", " files" ) );
	}

	virtual void loadData(){
		vector<string> data_nodes = config.childrenOf( nodePath, "Data" );

		for ( string path : data_nodes ){
			if ( config.exists( path + ":name" ) && !config.exists( path + ":treeName" ) ){
				loadDataFile( path );
			} else if ( config.exists( path + ":name" ) && config.exists( path + ":treeName" )){
				loadChain( path );
			}
		}
	} // loadData


	virtual void makePlots(){
		vector<string> plot_paths = config.childrenOf( nodePath, "Plot" );
		INFO( classname(), "Found " << plot_paths.size() << plural( plot_paths.size(), " Plot", " Plots" ) );
		for ( string path : plot_paths ){

			if ( config.exists( path + ".Palette" ) ){
				gStyle->SetPalette( config.getInt( path + ".Palette" ) );
			}

			makeHistograms( path );
			makeLatex(""); // global first
			makeLatex(path);
			makeExports( path );

		}
	}

	virtual void makeMargins( string _path ){
		
		// Global first
		if ( config.exists( "Margins:top" ) )
			gPad->SetTopMargin( config.getDouble( "Margins:top" ) );
		if ( config.exists( "Margins:right" ) )
			gPad->SetRightMargin( config.getDouble( "Margins:right" ) );
		if ( config.exists( "Margins:bottom" ) )
			gPad->SetBottomMargin( config.getDouble( "Margins:bottom" ) );
		if ( config.exists( "Margins:left" ) )
			gPad->SetLeftMargin( config.getDouble( "Margins:left" ) );

		if ( config.exists( _path + ".Margins:top" ) )
			gPad->SetTopMargin( config.getDouble( _path + ".Margins:top" ) );
		if ( config.exists( _path + ".Margins:right" ) )
			gPad->SetRightMargin( config.getDouble( _path + ".Margins:right" ) );
		if ( config.exists( _path + ".Margins:bottom" ) )
			gPad->SetBottomMargin( config.getDouble( _path + ".Margins:bottom" ) );
		if ( config.exists( _path + ".Margins:left" ) )
			gPad->SetLeftMargin( config.getDouble( _path + ".Margins:left" ) );
	}

	virtual TH1* findHistogram( string _path, int iHist ){

		string data = config.getXString( _path + ":data" );
		string name = config.getXString( _path + ":name" );
		INFO( classname(), "Looking for [" << name << "] in " << data << "=(" << dataFiles[data] <<")" );
		// first check for a normal histogram from a root file
		if ( dataFiles.count( data ) > 0 && dataFiles[ data ] ){
			if ( nullptr == dataFiles[ data ]->Get( name.c_str() ) ) return nullptr;
			TH1 * h = (TH1*)dataFiles[ data ]->Get( name.c_str() )->Clone( ("hist_" + ts(iHist)).c_str() );
			INFO( classname(), "Found Histogram [" << name << "]= " << h << " in data file " << data );
			return h;
		}

		// look for a dataChain with the name
		if ( dataChains.count( data ) > 0 && dataChains[ data ] ){
			TH1 * h = makeHistoFromDataTree( _path, iHist );
			return h;
		}

		return nullptr;
	}

	virtual void makeHistograms( string _path ){
		Logger::setGlobalLogLevel( "debug" );

		TCanvas * c = makeCanvas( _path ); 
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

			// string data = config.getXString( hpath + ":data" );
			// if ( dataFiles.count( data ) <= 0 || !dataFiles[ data ] ) continue;
			
			// TH1 * h = (TH1*)dataFiles[ data ]->Get( name.c_str() )->Clone( ("hist_" + ts(iHist)).c_str() );
			TH1 *h = findHistogram( hpath, iHist );
			INFO( classname(), "Got " << h );
			
			if ( nullptr == h ) continue;
			histos[ name ] = h;

			// transforms
			if ( config.exists( hpath + ".Scale" ) && config.getDouble( hpath + ".Scale" ) ){
				h->Scale( config.getDouble( hpath + ".Scale" ) );
			}
			if ( config.exists( hpath + ".Norm" ) && config.getBool( hpath + ".Norm", true ) ){
				h->Scale( 1.0 / h->Integral() );
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
			

			string styleRef = config.getXString( hpath + ":style" );
			INFO( classname(), "Style Ref : " << styleRef );
			if ( config.exists( styleRef ) ){
				rpl.style( h ).set( config, styleRef );
			}

			rpl.style( h ).set( config, hpath + ".style" ).draw();

			TPaveStats *st = (TPaveStats*)h->FindObject("stats");
			if ( nullptr != st  ){
				INFO( classname(), "Found Stats" );
				positionOptStats( hpath, st );
				// st->SetX1NDC( 0.7 ); st->SetX2NDC( 0.975 );
			}

			INFO( classname(), "Drawing " << name );
			iHist++;
		}

		makeLegend( _path, histos );

	} // makeHistograms

	virtual void makeLegend( string _path, map<string, TH1*> &histos ){
		if ( config.exists( _path + ".Legend" ) ){
			INFO( classname(), "Legend" );

			TLegend * leg = new TLegend( 
				config.getDouble( _path + ".Legend.Position:x1", 0.1 ),
				config.getDouble( _path + ".Legend.Position:y1", 0.7 ),
				config.getDouble( _path + ".Legend.Position:x2", 0.5 ),
				config.getDouble( _path + ".Legend.Position:y2", 0.9 ) );

			// TODO : fix bc histo "names" can include / invalid char
			// change to <Entry name="histo/name" title="bleh" ... />
			for ( auto kv : histos ){
				INFO( classname(), "Legend Entry for : " << kv.first );
				string t = config.getString(  _path + ".Legend." + kv.first+ ":title", kv.first) ;
				string opt = config.getString(  _path + ".Legend." + kv.first+ ":opt", "l") ;

				leg->AddEntry( kv.second, t.c_str(), opt.c_str() );
			}
			leg->Draw( );

		}
	}

	virtual void makeLatex( string _path ){
		
		TLatex latex;
		vector<string> latex_paths = config.childrenOf( _path, "TLatex" );
		for ( string ltpath : latex_paths ){
			if ( !config.exists( ltpath + ":text" ) ) continue;

			string text = config.getXString( ltpath + ":text" );
			
			INFO( classname(), "Latex" );
			latex.SetTextSize( config.getFloat( ltpath + ":size", 0.05 ) );

			latex.DrawLatexNDC( config.getFloat( ltpath + ":x" ), 
								config.getFloat( ltpath + ":y" ), 
								config.getXString( ltpath + ":text" ).c_str() );
			
		}
	}

	virtual void makeExports( string _path ){
		vector<string> exp_paths = config.childrenOf( _path, "Export" );
		for ( string epath : exp_paths ){
			if ( !config.exists( epath + ":url" ) ) continue;

			string url = config.getXString( epath + ":url" );
			gPad->Print( url.c_str() );
			INFO( classname(), "Exporting gPad to " << url );
		}
	}

	virtual TH1* makeHistoFromDataTree( string _path, int iHist ){
		string data = config.getXString( _path + ":data" );
		TChain * chain = dataChains[ data ];
		string title = config.getXString( _path + ":title" );
		string hName = config.getXString( _path + ":name" ) +"_" + ts( iHist );
		string drawCmd = config.getXString( _path + ":draw" ) + " >> " + hName;
		string selectCmd = config.getXString( _path + ":select" );
		
		// if bins are given lets assume we need to make the histo first
		if ( config.exists( _path + ":bins_x" ) ){
			HistoBins bx( config, config.getXString( _path + ":bins_x" ) );
			HistoBins by( config, config.getXString( _path + ":bins_y" ) );
			HistoBins bz( config, config.getXString( _path + ":bins_z" ) );
			HistoBook::make( "D", hName, title, bx, by, bz );
		}


		INFO( classname(), "TTree->Draw( \"" << drawCmd << "\", \"" << selectCmd << "\" )" );
		chain->Draw( drawCmd.c_str(), selectCmd.c_str() );


		TH1 *h = (TH1*)gPad->GetPrimitive( hName.c_str() );
		return h;
	}

	virtual void positionOptStats( string _path, TPaveStats * st ){
		if ( nullptr == st ) return;

		// global first
		if ( config.exists( "OptStats:x1" ) )
			st->SetX1NDC( config.getFloat( "OptStats:x1" ) );
		if ( config.exists( "OptStats:x2" ) )
			st->SetX2NDC( config.getFloat( "OptStats:x2" ) );
		if ( config.exists( "OptStats:y1" ) )
			st->SetY1NDC( config.getFloat( "OptStats:y1" ) );
		if ( config.exists( "OptStats:y2" ) )
			st->SetY2NDC( config.getFloat( "OptStats:y2" ) ); 
		
		// local 
		if ( config.exists( _path + ".OptStats:x1" ) )
			st->SetX1NDC( config.getFloat( _path + ".OptStats:x1" ) );
		if ( config.exists( _path + ".OptStats:x2" ) )
			st->SetX2NDC( config.getFloat( _path + ".OptStats:x2" ) );
		if ( config.exists( _path + ".OptStats:y1" ) )
			st->SetY1NDC( config.getFloat( _path + ".OptStats:y1" ) );
		if ( config.exists( _path + ".OptStats:y2" ) )
			st->SetY2NDC( config.getFloat( _path + ".OptStats:y2" ) ); 
	}

	virtual TCanvas* makeCanvas( string _path ){
		int width = -1, height = -1;
		// global first
		width = config.getInt( "TCanvas:width", -1 );
		height = config.getInt( "TCanvas:height", -1 );

		width = config.getInt( _path + ".TCanvas:width", width );
		height = config.getInt( _path + ".TCanvas:height", height );

		TCanvas * c = nullptr; 
		if ( width != -1 && height > -1 )
			c = new TCanvas( "c", "c", width, height );
		else 
			c = new TCanvas( "c" );

		return c;
	}
	
};



#endif