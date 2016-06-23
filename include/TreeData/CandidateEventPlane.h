#ifndef CANDIDATE_EVENT_PLANE_H
#define CANDIDATE_EVENT_PLANE_H

#include "TObject.h"

class CandidateEventPlane : public TObject
{
public:
	CandidateEventPlane() {}
	~CandidateEventPlane() {}

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