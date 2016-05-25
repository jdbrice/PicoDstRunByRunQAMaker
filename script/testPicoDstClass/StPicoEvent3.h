#ifndef StPicoEvent_hh
#define StPicoEvent_hh

#include "StThreeVectorF.h"

class StPicoEvent : public TObject {
public:

	Int_t          mRunId;           // run number
  Int_t          mEventId;         // event number
  UShort_t       mFillId;          // fill number
  Float_t        mBField;          // B field in kilogauss
  StThreeVectorF mPrimaryVertex;   // primary Vertex (1st)
  StThreeVectorF mSecondVertex;    // second Vertex position (for study)
  StThreeVectorF mPrimaryVertexError; // vertex error
  UInt_t         mTriggerWord;     // self-defined trigger word - see code for details
  UInt_t         mTriggerWordMtd;  // Added in Run14, st_mtd trigger
  UShort_t       mRefMultFtpcEast; // FTPC refMult east
  UShort_t       mRefMultFtpcWest; // FTPC refMult west
  UShort_t       mRefMultNeg;      // TPC refMult neg
  UShort_t       mRefMultPos;      // TPC refMult pos
  UShort_t       mRefMult2NegEast; // TPC refMult2 neg (-1<eta<-0.5)
  UShort_t       mRefMult2PosEast; // TPC refMult2 pos (-1<eta<-0.5)
  UShort_t       mRefMult2NegWest; // TPC refMult2 neg (0.5<eta<1.0)
  UShort_t       mRefMult2PosWest; // TPC refMult2 pos (0.5<eta<1.0)
  UShort_t       mRefMultHalfNegEast ;// TPC refMultHalf neg (eta<0)
  UShort_t       mRefMultHalfPosEast ;// TPC refMultHalf pos (eta<0)
  UShort_t       mRefMultHalfNegWest ;// TPC refMultHalf neg (eta>0)
  UShort_t       mRefMultHalfPosWest ;// TPC refMultHalf pos (eta>0)
  UShort_t       mGRefMult;
  UShort_t       mNHitsHFT[4];
  
  UChar_t        mNVpdHitsEast;    // Vpd Hits east;
  UChar_t        mNVpdHitsWest;    // vpd hits west;
  UShort_t       mNT0;             // number of T0 particles in BTOF self calibration
  Short_t        mVzVpd;           // VzVpd*100.

  UInt_t        mZDCx;           // zdcX
  UInt_t        mBBCx;
  Float_t mBackgroundRate;
  Float_t mBbcBlueBackgroundRate;
  Float_t mBbcYellowBackgroundRate;
  Float_t mBbcEastRate;
  Float_t mBbcWestRate;
  Float_t mZdcEastRate;
  Float_t mZdcWestRate;
  //Nov.10, 2008, Na
  UShort_t mVpd[64];
  UShort_t mZdcSumAdcEast;
  UShort_t mZdcSumAdcWest;
  UShort_t mZdcSmdEastHorizontal[8];
  UShort_t mZdcSmdEastVertical[8];
  UShort_t mZdcSmdWestHorizontal[8];
  UShort_t mZdcSmdWestVertical[8];
  Float_t mSpaceCharge;

  UShort_t mbTofTrayMultiplicity ; // BTOF tray multiplicity
  UShort_t mNumberOfGlobalTracks ; // # of global tracks

  // From StMuPrimaryVertex
  Float_t mRanking ;
  UShort_t mNBEMCMatch ;
  UShort_t mNBTOFMatch ;

  // BBC ADC for q-vectors (Hiroshi)
  UShort_t mBbcAdcEast[24] ; /// BBC East ADC: 0-23
  UShort_t mBbcAdcWest[24] ; /// BBC West ADC: 24-47

  // Online HT/JP thresholds
  UChar_t mHT_Th[4];
  UChar_t mJP_Th[4];
    
  ClassDef(StPicoEvent,1)
};

#endif