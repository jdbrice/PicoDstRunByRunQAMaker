#ifndef TREE_QA_MAKER_H
#define TREE_QA_MAKER_H

#include "IObject.h"
#include "HistoBook.h"
#include <map>

#include "TChain.h"

class TTreeQA : public IObject, public IConfig
{
public:
	virtual const char* classname() const { return "TTreeQA"; }
	TTreeQA(){

	}
	TTreeQA( shared_ptr<HistoBook> _book, XmlConfig &_config ) {
		setHistoBook( _book );
		setConfig( _config );
	}
	~TTreeQA(){

	}

	void setHistoBook( shared_ptr<HistoBook> _book ) {
		this->book = _book;
	}
	void setConfig( XmlConfig &_config ){
		this->config = _config;
	}

	void setVariable( string _name, double _value ){
		data[ _name ] = _value;
	}

	void s( string _name, double _value ){
		setVariable( _name, _value );
	}

	void initVariable( string _name, string _title="", string _units="", string _bins="", string _axis="" ){
		data[ _name ] = 0;
		units[ _name ] = _units; 
		title[ _name ] = _title;
		if ( "" != _bins )
			bins[ _name ] = _bins;
		axis[ _name ] = _axis;
	}

	void i( string _name, string _title="", string _units="", string _bins="", string _axis="" ){
		initVariable( _name, _title, _units, _bins, _axis );
	}

	void makeHistograms( string _binBasePath ){
		if ( histosMade ) return;

		binBasePath = config.basePath( _binBasePath );
		// create 1D histos for each variable
		for ( auto &elem : data ){
			const string &x = elem.first;
			string hName = x;
			INFO( classname(), "Checking for " << hName );
			if ( book->exists( hName ) ) continue;
			
			string bx = binsFor( x );
			if ( config.exists( _binBasePath + "." + bx ) ){
				HistoBins hbx( config, binBasePath + "." + bx );
				TH1 * h = book->make( "D", hName, histoTitleFor( x ), hbx );
				book->add( hName, h );
			} else {
				ERROR( classname(), "Cannot make histogram for " << hName );
				ERROR( classname(), "Could not find bins at " << _binBasePath + "." + x );
			}
		}

		for ( auto &elem1 : data ){
			const string &x = elem1.first;
			
			for ( auto &elem2 : data ){
				const string &y = elem2.first;
				if ( skipPair( x, y ) ) continue;

				string hName = nameFor( x, y );

				INFO( classname(), "Checking for " << hName );
				if ( book->exists( hName ) ) continue;
				
				INFO( classname(), "Making Histogram for " << hName );

				string bx = binsFor( x ); 
				string by = binsFor( y );
				if ( config.exists( _binBasePath + "." + bx ) && config.exists( _binBasePath + "." + by ) ){
					
					HistoBins hbx( config, binBasePath + "." + bx );
					HistoBins hby( config, binBasePath + "." + by );

					TH1 * h = book->make( "D", hName, histoTitleFor( x, y ), hbx, hby );
					book->add( hName, h );
				} else {
					ERROR( classname(), "Cannot make histogram for " << hName );
					if ( !config.exists( _binBasePath + "." + x ) ){
						ERROR( classname(), "Could not find bins at " << _binBasePath + "." + x );
					}
					if ( !config.exists( _binBasePath + "." + y ) ){
						ERROR( classname(), "Could not find bins at " << _binBasePath + "." + y );
					}
				}
				// make it
			}
		}
		histosMade = true;
	}

	void fill(){
		for ( auto &elem1 : data ){
			const string &x = elem1.first;

			string hName1d = x;
			// fill 1D histos
			if ( book->exists( hName1d ) ){
				book->fill( hName1d, data[ x ] );
			}


			for ( auto &elem2 : data ){
				const string &y = elem2.first;
				// fill 2d
				if ( skipPair( x, y ) ) continue;

				string hName = nameFor( x, y );
				book->fill( hName, data[ x ], data[ y ] );
			}
		}


	}

	bool skipPair( string _x, string _y ){
		
		if ( _x == _y ) return true;
		if ( _x > _y && "" == axisFor( _x ) ) return true;
		if ( "x" == axisFor( _y ) ) return true;
		return false;
	}
	
	string axisFor( string _name ){
		// TODO: doesnt work yet
		if ( axis.count( _name ) >= 1 ){
			return axis[ _name ];
		}
		return "";
	}

	string nameFor( string _x, string _y ){
		return _y + "_vs_" + _x;
	}

	string titleFor( string _x ){
		if ( title.count( _x ) >= 1 && "" != title[ _x ] ){
			return title[ _x ];
		}
		return _x;
	}
	string histoTitleFor( string _x ){
		return ";" + titleFor( _x ) + " " + units[ _x ] + "; dN/d" + titleFor(_x);
	}
	string histoTitleFor( string _x, string _y ){

		string _xt = titleFor( _x );
		string _yt = titleFor( _y );
		return ";" + _xt + " " + units[ _x ] + ";" + _yt + " " + units[ _y ];
	}

	string binsFor( string _name ){
		if ( bins.count(_name ) >= 1 && bins[ _name ] != "" )
			return bins[ _name ];
		return _name;
	}

	
	map<string, double> data;
	map<string, string> units;
	map<string, string> title;
	map<string, string> bins;
	map<string, string> axis;
protected:

	shared_ptr<HistoBook> book;
	bool histosMade = false;

	// the path in config to the histogram bins
	string binBasePath;

	
};

#endif