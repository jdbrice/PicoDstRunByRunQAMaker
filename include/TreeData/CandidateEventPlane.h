#ifndef CANDIDATE_EVENT_PLANE_H
#define CANDIDATE_EVENT_PLANE_H

#include "TObject.h"

class CandidateEventPlane : public TObject
{
public:
	CandidateEventPlane() {}
	~CandidateEventPlane() {}

	void copy( CandidateEventPlane * that ){
		this->mQx_eta_pos           = that->mQx_eta_pos;
		this->mQy_eta_pos           = that->mQy_eta_pos;
		this->mQx_eta_neg           = that->mQx_eta_neg;
		this->mQy_eta_neg           = that->mQy_eta_neg;
		this->mNtrk_eta_pos         = that->mNtrk_eta_pos;
		this->mNtrk_eta_neg         = that->mNtrk_eta_neg;
		this->mWeight_eta_pos       = that->mWeight_eta_pos;
		this->mWeight_eta_neg       = that->mWeight_eta_neg;
		this->mQx_chg_pos           = that->mQx_chg_pos;
		this->mQy_chg_pos           = that->mQy_chg_pos;
		this->mQx_chg_neg           = that->mQx_chg_neg;
		this->mQy_chg_neg           = that->mQy_chg_neg;
		this->mNtrk_chg_pos_eta_pos = that->mNtrk_chg_pos_eta_pos;
		this->mNtrk_chg_pos_eta_neg = that->mNtrk_chg_pos_eta_neg;
		this->mNtrk_chg_neg_eta_pos = that->mNtrk_chg_neg_eta_pos;
		this->mNtrk_chg_neg_eta_neg = that->mNtrk_chg_neg_eta_neg;
		this->mWeight_chg_pos       = that->mWeight_chg_pos;
		this->mWeight_chg_neg       = that->mWeight_chg_neg;
		this->mQx_ran_1             = that->mQx_ran_1;
		this->mQy_ran_1             = that->mQy_ran_1;
		this->mQx_ran_2             = that->mQx_ran_2;
		this->mQy_ran_2             = that->mQy_ran_2;
		this->mNtrk_ran_1_eta_pos   = that->mNtrk_ran_1_eta_pos;
		this->mNtrk_ran_1_eta_neg   = that->mNtrk_ran_1_eta_neg;
		this->mNtrk_ran_2_eta_pos   = that->mNtrk_ran_2_eta_pos;
		this->mNtrk_ran_2_eta_neg   = that->mNtrk_ran_2_eta_neg;
		this->mWeight_ran_1         = that->mWeight_ran_1;
		this->mWeight_ran_2         = that->mWeight_ran_2;
	}

	Float_t mQx_eta_pos;
	Float_t mQy_eta_pos;
	Float_t mQx_eta_neg;
	Float_t mQy_eta_neg;
	Short_t mNtrk_eta_pos;
	Short_t mNtrk_eta_neg;
	Float_t mWeight_eta_pos;
	Float_t mWeight_eta_neg;

	Float_t mQx_chg_pos;
	Float_t mQy_chg_pos;
	Float_t mQx_chg_neg;
	Float_t mQy_chg_neg;
	Short_t mNtrk_chg_pos_eta_pos;
	Short_t mNtrk_chg_pos_eta_neg;
	Short_t mNtrk_chg_neg_eta_pos;
	Short_t mNtrk_chg_neg_eta_neg;
	Float_t mWeight_chg_pos;
	Float_t mWeight_chg_neg;

	Float_t mQx_ran_1;
	Float_t mQy_ran_1;
	Float_t mQx_ran_2;
	Float_t mQy_ran_2;
	Short_t mNtrk_ran_1_eta_pos; 
	Short_t mNtrk_ran_1_eta_neg; 
	Short_t mNtrk_ran_2_eta_pos; 
	Short_t mNtrk_ran_2_eta_neg; 
	Float_t mWeight_ran_1;
	Float_t mWeight_ran_2;

	ClassDef( CandidateEventPlane, 1 )
};


#endif