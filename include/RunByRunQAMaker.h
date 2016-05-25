#include "TreeAnalyzer.h"

#include "DataSource.h"

#include "PicoDst.h"
#include "CentralityMaker.h"

#include <map>

class RunByRunQAMaker : public TreeAnalyzer
{

protected:
	std::map< int, unsigned int > runIndices;
	unsigned int runIndex;
	unsigned int nextRunIndex;

	static vector<int> runNumbers;

	bool makeTrackQA, makeEventQA;

	PicoDst * pico;

	StRefMultCorr * rmc;

public:
	virtual const char* classname() const { return "RunByRunQAMaker"; }
	RunByRunQAMaker(){}
	~RunByRunQAMaker(){}


	virtual void initialize();
	virtual bool keepEvent();
	virtual void analyzeEvent();
	
};