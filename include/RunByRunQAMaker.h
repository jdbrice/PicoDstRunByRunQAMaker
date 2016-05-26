
// RooBarb
#include "TreeAnalyzer.h"

// Project
#include "PicoDst.h"
#include "CentralityMaker.h"
#include "RunMapFactory.h"
#include "ProductionFinder.h"


// STL
#include <memory>


class RunByRunQAMaker : public TreeAnalyzer
{

protected:
	std::map< int, unsigned int > runIndices;
	unsigned int runIndex;
	unsigned int nextRunIndex;

	static vector<int> runNumbers;

	bool makeTrackQA, makeEventQA;

	shared_ptr<PicoDst> pico;
	StRefMultCorr * rmc;
	shared_ptr<RunMapFactory> rmf;

public:
	virtual const char* classname() const { return "RunByRunQAMaker"; }
	RunByRunQAMaker(){}
	~RunByRunQAMaker(){}

	virtual void overrideConfig();
	virtual void initialize();
	virtual bool keepEvent();
	virtual void analyzeEvent();
	
};