
#include "rbrPlot.C"

string names[] = {
	"mRefMult",
	"mVzVpd",
	"mRanking",
	"mPrimaryVertex_mX1",
	"mPrimaryVertex_mX2",
	"mPrimaryVertex_mX3",
	"mBBCx",
	"mZDCx",
	"mBackgroundRate",
	"mQx_eta_pos",
	"mQx_eta_neg",
	"mRefMultPos",
	"mQy_eta_pos",
	"mQy_eta_neg",
	"mQx_chg_pos",
	"mQx_chg_neg",
	"mQy_chg_pos",
	"mQy_chg_neg",
	"mNtrk_eta_pos",
	"mNtrk_eta_neg",
	"mNtrk_chg_pos_eta_pos",
	"mNtrk_chg_pos_eta_neg",
	"mRefMultNeg",
	"mNtrk_chg_neg_eta_pos",
	"mNtrk_chg_neg_eta_neg",
	"mNtrk_ran_1_eta_pos",
	"mNtrk_ran_1_eta_neg",
	"mNtrk_ran_2_eta_pos",
	"mNtrk_ran_2_eta_neg",
	"mWeight_eta_pos",
	"mWeight_eta_neg",
	"mWeight_chg_pos",
	"mWeight_chg_neg",
	"mGRefMult",
	"mWeight_ran_1",
	"mWeight_ran_2",
	"mNumberOfGlobalTracks",
	"mNBTOFMatch",
	"mNBEMCMatch",
	"mbTofTrayMultiplicity",
	"delta_mVzVpd_mPrimaryVertex_mX3"
};

void plotAll(){

	XmlConfig config( "config.xml" );


	for ( string name : names ){
		cout << name << endl;
		cout << "nSigma = " << config.getDouble( "nSigma." + name ) << endl;
		rbrPlot( name, config.getDouble( "nSigma." + name ) );
	}




}