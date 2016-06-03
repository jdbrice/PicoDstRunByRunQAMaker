#ifndef EVENT_PLANE_MAKER_H
#define EVENT_PLANE_MAKER_H

#include "PicoDstSkimmer.h"
#include "EventPlaneCorr.h"

class EventPlaneMaker : public PicoDstSkimmer
{
public:
	virtual const char* classname() const { return "EventPlaneMaker"; }
	EventPlaneMaker(){}
	~EventPlaneMaker(){}

	TH1D * hPsi2, *hPsi2Centered;
	TH2D * hQxQy, *hQxQyCentered;

	virtual void initialize(){
		PicoDstSkimmer::initialize();

		// override any default in PicoDstSkimmer::initialize()
		nEventLoops = 2;

		hPsi2 = new TH1D("Psi2","",640,-3.2,3.2);
		hQxQy = new TH2D("QxQy","",1000,-1,1,1000,-1,1);
		hPsi2Centered = new TH1D("Psi2Centered","",640,-3.2,3.2);
		hQxQyCentered = new TH2D("QxQyCentered","",1000,-1,1,1000,-1,1);


		v1 = config.getString( nodePath + ".EventPlane:v1", "eta_pos" );
		v2 = config.getString( nodePath + ".EventPlane:v2", "eta_neg" );

	}

protected:
	EventPlaneCorr epc;
	string v1, v2;

	virtual void analyzeEvent();
	virtual void postEventLoop();


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
	double getQ( string value, string var1, string var2="" ){

		if ( "mQx" != value && "mQy" != value ){
			ERROR( classname(), "value must be either \"mQx\" or \"mQy\" " );
			return 0;
		}

		string v1 = "EventPlane." + value + "_" + var1;
		string v2 = "EventPlane." + value + "_" + var2;
		
		TRACE( classname(), "v1 = " << v1 );
		TRACE( classname(), "v2 = " << v2 );

		double dv1 = 0, dv2 = 0;

		dv1 = pico->get<Float_t>( v1 );
		dv2 = pico->get<Float_t>( v2 );
		
		if ( "" != var2 )
			return dv1 + dv2;
		else 
			return dv1;
	}

	int getNtrk( string mod1, string mod2="" ){

		string v1 = "EventPlane.mNtrk_" + mod1;
		string v2 = "EventPlane.mNtrk_" + mod2;

		int dv1 = 0, dv2 = 0;

		if ( 	("eta_neg" == mod1 && "eta_pos" == mod2) || 
				("eta_neg" == mod2 && "eta_pos" == mod1) ){
			dv1 = pico->get<Short_t>( v1 );
			dv2 = pico->get<Short_t>( v2 );	
			
		} else {

			dv1 = pico->get<Short_t>( v1 + "_eta_pos" ) + pico->get<Short_t>( v1 + "_eta_neg" );
			dv2 = pico->get<Short_t>( v2 + "_eta_pos" ) + pico->get<Short_t>( v2 + "_eta_neg" );

		}

		if ( "" != mod2 )
			return dv1 + dv2;	
		else 
			return dv1;

	}



};

#endif