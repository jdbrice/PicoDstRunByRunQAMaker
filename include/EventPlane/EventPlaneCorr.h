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
		centeringPoint.set( cfg, nodePath + ".CenteringPoint" );
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
	// string toXml( ){

	// 	string line = "<EventPlaneCorr ";
	// 	line += "mean_qx=\"";
	// 	line += dts( mean_qx );
	// 	line += "\"";
	// 	line += "mean_qy=\"";
	// 	line += dts( mean_qy );
	// 	line += "\"";

	// 	line += " >";
	// 	line += "\n </EventPlaneCorr>";
	// 	return line;
	// }

protected:

	// double mean_qx, mean_qy;
	XmlPoint centeringPoint;
	XmlFunction flatteningFunction;


	
};



#endif