#ifndef EVENT_PLANE_CORR_H
#define EVENT_PLANE_CORR_H

//RooBarb
#include "Utils.h"
#include "IObject.h"

#include "XmlPoint.h"
#include "XmlFunction.h"
using namespace jdb;


class EventPlaneCorr : public IObject
{
public:
	virtual const char * classname() const { return "EventPlaneCorr"; }
	EventPlaneCorr() {}
	
	// load in from Xml
	EventPlaneCorr( XmlConfig &config, string nodePath ){
		load( config, nodePath );
	}

	~EventPlaneCorr(){}

	void load( XmlConfig &cfg, string nodePath ){
		centeringPoint.set( cfg, nodePath + ".CenteringOffset" );
		flatteningFunction.set( cfg, nodePath + ".FlatteningFunction" );


		DEBUG( classname(), "Loaded Params from config file" );
		INFO( classname(), "########################### PARAMETERS #################################" );
		INFO( classname(), "Centering (Qx, Qy) = " << centeringPoint.toString() );
		INFO( classname(), "Flattening Function = " << flatteningFunction.toString() );
	}

	void setMeans( double _mean_qx, double _mean_qy ){
		centeringPoint.set( _mean_qx, _mean_qy );
	}

	double center_qx( double qx ){
		return qx - centeringPoint.x;
	}
	double center_qy( double qy ){
		return qy - centeringPoint.y;
	}

	double flatten( double psi ){
		return 1.0;
	}


	// void load(  );
	string toXml( ){
		string line = XmlConfig::declarationV1 + "\n";
		line += "<config>\n";
		line += "\t<EventPlaneCorr>\n";
		line += "\t\t" + centeringPoint.toXml( "CenteringOffset" ) + "\n";
		line += "\t</EventPlaneCorr>\n";
		line += "</config>\n";
		return line;
	}

	string toString(){
		return "CenterintOffset=" + centeringPoint.toString();
	}

protected:

	// double mean_qx, mean_qy;
	XmlPoint centeringPoint;
	XmlFunction flatteningFunction;

};



#endif