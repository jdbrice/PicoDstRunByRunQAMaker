#ifndef EVENT_PLANE_CORR_H
#define EVENT_PLANE_CORR_H

//RooBarb
#include "Utils.h"
using namespace jdb;


class EventPlaneCorr
{
public:
	EventPlaneCorr() : mean_qx(0), mean_qy(0) {}
	~EventPlaneCorr(){}

	void setMeans( double _mean_qx, double _mean_qy ){
		mean_qx = _mean_qx;
		mean_qy = _mean_qy;
	}

	double center_qx( double qx ){
		return qx - mean_qx;
	}
	double center_qy( double qy ){
		return qy - mean_qy;
	}


	void load(  );
	string toXml( ){

		string line = "<EventPlaneCorr ";
		line += "mean_qx=\"";
		line += dts( mean_qx );
		line += "\"";
		line += "mean_qy=\"";
		line += dts( mean_qy );
		line += "\"";

		line += " >";
		line += "\n </EventPlaneCorr>";
		return line;
	}

protected:

	double mean_qx, mean_qy;


	
};



#endif