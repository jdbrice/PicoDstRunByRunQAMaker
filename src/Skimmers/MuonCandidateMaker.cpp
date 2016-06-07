#include "MuonCandidateMaker.h"


MuonCandidateMaker::MuonCandidateMaker(){

}

MuonCandidateMaker::~MuonCandidateMaker(){

}

void MuonCandidateMaker::initialize(){
	PicoDstSkimmer::initialize();
	
	INFO( classname(), "" );
	event = new CandidateEvent();
	tracks = new TClonesArray( "CandidateTrack" );
	
	createTree();

}