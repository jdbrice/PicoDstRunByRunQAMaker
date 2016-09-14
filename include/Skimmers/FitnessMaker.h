#ifndef FITNESS_MAKER_H
#define FITNESS_MAKER_H

#include "HistoAnalyzer.h"
#include "TNtuple.h"

class FitnessMaker : public HistoAnalyzer {
public:
	virtual const char* classname() const {return "FitnessMaker"; }
	FitnessMaker() {}
	~FitnessMaker() {}

	virtual void initialize(){
		HistoAnalyzer::initialize();

		if ( config.exists( nodePath + ".MuonCandidateCuts" ) ){
			trackCuts.init( config, nodePath + ".MuonCandidateCuts" );

			INFO( classname(), "" );
			INFO( classname(), "############### Muon Cuts ###################"  );
			trackCuts.report();
			INFO( classname(), "" );
		}
	}

protected:
	CutCollection trackCuts;

	virtual void make(){

		TH1 *signal = get1D( "unlike_sign", "data" );
		TH1 *bg 	= get1D( "like_sign", "data" );

		if ( nullptr == signal || nullptr == bg ) return;

		int b1 = signal->FindBin( 3.0 );
		int b2 = signal->FindBin( 3.2 );

		int lmrb1 = signal->FindBin( 0.2 );
		int lmrb2 = signal->FindBin( 1.2 );

		double signalI = signal->Integral( b1, b2 );
		double bgI 	   = bg->Integral( b1, b2 );

		double ratio = signalI / bgI;
		double sig 	 = signalI / sqrt( signalI + 2 * bgI );
		double psignalI = signalI - bgI;
		float score_jpsi2 = psignalI / sqrt( psignalI + 2 * bgI );
		float score_purity = (psignalI) / signalI;

		cout << "RATIO : " << ratio << endl;
		cout << "S / sqrt( S + 2B ) : " << sig << endl;

		float score_jpsi = sig;
		float score_stats = signal->Integral() + bg->Integral();
		float score_lmr = signal->Integral( lmrb1, lmrb2 ) / bg->Integral( lmrb1, lmrb2 );

		book->cd();
		// copy the track cuts from the input file
		TTree* nTrackCuts = ((TTree*)rootFiles[ "data" ]->Get( "trackCuts" ))->CloneTree();

		TNtuple *ntuple = new TNtuple("fitness","Fitness","score_purity:score_stats:score_jpsi:score_jpsi2:score_lmr:index");
		
		float iFitness = config.getFloat( "iFitness" );

		float data[] = {
			score_purity,
			score_stats,
			score_jpsi,
			score_jpsi2,
			score_lmr,
			iFitness
		};
		ntuple->Fill( data );

		// INFO( classname(), "Filling TNtuple " );
		// for ( int i = 0; i < 19; i++ ){
		// 	INFO( classname(), "data[ " << i << " ] = " << data[i] );
		// }
		
	}
	
};

#endif