#ifndef ACCEPTANCE_FIXER_H
#define ACCEPTANCE_FIXER_H

// RooBarb
#include "HistoAnalyzer.h"
using namespace jdb;



class AcceptanceFixer : public HistoAnalyzer
{
public:
	AcceptanceFixer() {}
	~AcceptanceFixer() {}

	virtual void initialize(){
		HistoAnalyzer::initialize();
	}

	virtual void makeGeometricMean( TH1*gm, TH1* lsp, TH1* lsn );

	virtual void makeGeometricMean( TH2*gm, TH2* lsp, TH2* lsn );

	virtual void multiplyBinByBin( TH1 * A, TH1 * B );

	virtual void applyTriggerPatchCorr( TH1* _sig, TH1* _tpcorr );
	virtual void applyTriggerPatchCorr( TH2* _sig, TH2* _tpcorr );

	virtual void makeEmbeddingEfficiencyCurve();

	void make2D();
	void makeMass1D();
	virtual void make();
	protected:


};


#endif