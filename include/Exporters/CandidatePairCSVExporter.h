#ifndef CANDIDATE_PAIR_CSV_EXPORTER_H
#define CANDIDATE_PAIR_CSV_EXPORTER_H

#include "SameEventPairMaker.h"

class CandidatePairCSVExporter : public SameEventPairMaker
{
public:
	virtual const char* classname() const { return "CandidatePairCSVExporter"; }
	CandidatePairCSVExporter() {}
	~CandidatePairCSVExporter() {}

	virtual void initialize(){
		SameEventPairMaker::initialize();

		string fname = config.getXString( nodePath + ".output.File:url", "pair_cands.csv" );
		INFO( classname(), "Exporting to : " << fname );
		csvFile.open( fname );
		keepAll = config.getBool( nodePath + ".keepAll", false );

	}

	// virtual void overriceConfig(){
	// 	vector<string> requiredPaths = {
	// 		nodePath,
	// 		nodePath + ".input",
	// 		nodePath + ".input.File",
	// 		nodePath + ".input.File:url",

	// 	}
	// 	// set some defaults
	// 	if ( !config.exists(nodePath) ){
	// 		config.set( nodePath, "" );
	// 	}
	// 	if ( !config.exists( nodePath + ".input" ) ){
	// 		config.set(  )
	// 	}
	// }


	virtual void analyzePair( CandidateTrack * _aTrack, CandidateTrack * _bTrack ){

		CandidateTrackMtdPidTraits *aMtdPid = (CandidateTrackMtdPidTraits *)mtdPidTraits->At( _aTrack->mMtdPidTraitsIndex );
		CandidateTrackMtdPidTraits *bMtdPid = (CandidateTrackMtdPidTraits *)mtdPidTraits->At( _bTrack->mMtdPidTraitsIndex );

		TLorentzVector lv1, lv2, lv;
		lv1.SetXYZM( _aTrack->mPMomentum_mX1, _aTrack->mPMomentum_mX2, _aTrack->mPMomentum_mX3, m1 );
		lv2.SetXYZM( _bTrack->mPMomentum_mX1, _bTrack->mPMomentum_mX2, _bTrack->mPMomentum_mX3, m2 );

		lv = lv1 + lv2;

		bool keep = false;
		bool signal = false;
		// decide what stuff to keep
		if ( 3.0 < lv.M() && lv.M() < 3.2 ){
			if ( abs(_aTrack->charge() + _bTrack->charge()) == 0 ){
			// signal
				signal = true;
				keep = true;
			} 
		}

		if ( abs(_aTrack->charge() + _bTrack->charge()) > 0 ){
			// background
			signal = false;
			keep = true;
		}

		if ( keep || keepAll == true ){
			string trackStrA = CandidateCSVFormatter::trackToCSV( _aTrack );
			string trackStrB = CandidateCSVFormatter::trackToCSV( _bTrack );
			
			string mtdPidStrA = CandidateCSVFormatter::mtdPidTraitsToCSV( aMtdPid );
			string mtdPidStrB = CandidateCSVFormatter::mtdPidTraitsToCSV( bMtdPid );
			int cat = 0;
			if ( signal )
				cat = 1;

			// csvFile << mtdPidStrA <<", " << mtdPidStrB << ", " << cat << "\n";
			csvFile << trackStrA << ", " << mtdPidStrA << ", " << trackStrB << ", " << mtdPidStrB ;
			if ( keepAll ){
				csvFile << "\n";
			} else {
				csvFile << ", " << cat << "\n";
			}
		}
		
	}

	virtual void postMake(){
		csvFile.close();
	}

protected:
	ofstream csvFile;
	bool keepAll = false;
};


#endif