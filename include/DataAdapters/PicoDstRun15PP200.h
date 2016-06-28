//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jun 27 17:24:56 2016 by ROOT version 6.06/02
// from TTree PicoDst/StPicoDst
// found on file: /Users/jdb/bnl/local/data/Run15/pp200/046/16046039/st_mtd_16046039_raw_2000004.picoDst.root
//////////////////////////////////////////////////////////

#ifndef PICO_DST_RUN15_PP_200_H
#define PICO_DST_RUN15_PP_200_H

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "TClonesArray.h"
#include "TObject.h"
#include "utility"

#include "IPicoDst.h"

class PicoDstRun15PP200 : public IPicoDst {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   
   UShort_t        Tracks_mChi2Prob[kMaxTracks];   //[Tracks_]
   Float_t         Tracks_mGMomentum_mX1[kMaxTracks];   //[Tracks_]
   Float_t         Tracks_mGMomentum_mX2[kMaxTracks];   //[Tracks_]
   Float_t         Tracks_mGMomentum_mX3[kMaxTracks];   //[Tracks_]
   
   UChar_t         Tracks_mFlowFlag[kMaxTracks];   //[Tracks_]
   Short_t         Tracks_mOriginX[kMaxTracks];   //[Tracks_]
   Short_t         Tracks_mOriginY[kMaxTracks];   //[Tracks_]
   Short_t         Tracks_mOriginZ[kMaxTracks];   //[Tracks_]
   UShort_t        Tracks_mGDca[kMaxTracks];   //[Tracks_]
   
   UChar_t         Tracks_mNHitsMapHFT[kMaxTracks];   //[Tracks_]

   TBranch        *b_Tracks_mChi2Prob;   //!
   TBranch        *b_Tracks_mGMomentum_mX1;   //!
   TBranch        *b_Tracks_mGMomentum_mX2;   //!
   TBranch        *b_Tracks_mGMomentum_mX3;   //!
   TBranch        *b_Tracks_mFlowFlag;   //!
   TBranch        *b_Tracks_mOriginX;   //!
   TBranch        *b_Tracks_mOriginY;   //!
   TBranch        *b_Tracks_mOriginZ;   //!
   TBranch        *b_Tracks_mGDca;   //!
   TBranch        *b_Tracks_mNHitsMapHFT;   //!

   PicoDstRun15PP200(TTree *tree=0);
   virtual ~PicoDstRun15PP200();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif
