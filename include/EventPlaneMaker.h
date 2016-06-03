#ifndef EVENT_PLANE_MAKER_H
#define EVENT_PLANE_MAKER_H

// RooBarb
#include "XmlPoint.h"
#include "XmlFunction.h"


#include "PicoDstSkimmer.h"
#include "EventPlaneCorr.h"

class EventPlaneMaker : public PicoDstSkimmer
{
public:
	virtual const char* classname() const { return "EventPlaneMaker"; }
	EventPlaneMaker(){}
	~EventPlaneMaker(){}

	TH1D * hPsi2, *hPsi2Centered, *hPsi2Flattened;
	TH2D * hQxQy, *hQxQyCentered;

	virtual void initialize();

protected:
	EventPlaneCorr epc;
	string v1, v2;

	XmlPoint centeringPoint;
	XmlFunction fWeight;

	virtual void analyzeEvent();
	virtual void postEventLoop();

	void task_rawEventPlane();
	void task_centeredEventPlane();
	void task_centerFlattenEventPlane();

	void fitQxQy();
	void fitPsi();


	virtual void overrideConfig(){

		string name = "EventPlane_" +  config.getString( nodePath + ".EventPlane:v1" );
		string v2 = config.getString( nodePath + ".EventPlane:v2", "" );
		if ( "" != v2 )
			name += "_" + v2 + ".root";
		else 
			name += ".root";

		config.set( nodePath + ".output.data", name );

	}

	// gets the desired raw value from the pico
	double getQ( string value, string var1, string var2="" );
	int getNtrk( string mod1, string mod2="" );



};

#endif