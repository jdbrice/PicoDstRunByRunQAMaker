
// #include "StPicoEvent3.h"


void test(){
	
	TChain * c = new TChain( "PicoDst" );
	c->Add( "~/bnl/local/data/muonPico/st_mtd_15095014_raw_1000002.picoDst.root" );


	c->SetBranchStatus( "*", 0 );
	c->SetBranchStatus( "Event.*", 1 );

	// StPicoEvent * event = new StPicoEvent();

	// c->SetBranchAddress( "Event", &event );

	for ( int i = 0; i < 100; i++ ){
		cout << "[" << c->GetEntry(i) << "]";
		// cout << 
		// cout << event->mRunId << endl;
		// cout << event->numberOfGlobalTracks() << endl;	
		// cout << event->runId() << endl;
	}

	


}