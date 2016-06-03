#ifndef RUNBYRUN_REPORT_MAKER_H
#define RUNBYRUN_REPORT_MAKER_H

//RooBarb
#include "HistoAnalyzer.h"
#include "RooPlotLib.h"
#include "XmlRange.h"

// ROOT
#include "TMath.h"
#include "TProfile.h"
#include "TH1D.h"

// Project
#include "RunMapFactory.h"

class RunByRunReportMaker : public HistoAnalyzer
{
public:
	virtual const char* classname() const { return "RunByRunReportMaker"; }
	RunByRunReportMaker(){}
	~RunByRunReportMaker(){}

protected:

	RunMapFactory rmf;
	vector<bool> badRunMask;
	XmlRange *region;
	vector<string> badRunHistos;
	vector<string> histoNames;

	virtual void make();

	void profile(string name, bool draw=true );
	double meanForPeriod( TProfile * h, XmlRange *r=nullptr );
	double rmsForPeriod( TProfile * h, string name, XmlRange *r=nullptr );

	double maxFor( TProfile * h );
	double minFor( TProfile * h );
	void drawBands( TProfile * h, string name, double nSig = 3.0, XmlRange *r=nullptr );
	void findBadRuns( TProfile * h, double nSig = 3.0, XmlRange *r=nullptr );
	TH1 * makeBadRunPlot( TProfile * h, string name, XmlRange *r=nullptr );


	
};


#endif