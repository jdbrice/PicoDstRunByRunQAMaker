#ifndef PYTHIA_TRACK_H
#define PYTHIA_TRACK_H

#include "TObject.h"
#include <iostream>

class PythiaTrack : public TObject {
	
public:
	PythiaTrack() {}
	virtual ~PythiaTrack() {}

	virtual void print(){
		std::cout << "mId" << mId << std::endl;
		std::cout << "mEnergy" << mEnergy << std::endl;
		std::cout << "mKF" << mKF << std::endl;
		std::cout << "mKS" << mKS << std::endl;
		std::cout << "mLifetime" << mLifetime << std::endl;
		std::cout << "mMass" << mMass << std::endl;
		std::cout << "mParent" << mParent << std::endl;
		std::cout << "mPx" << mPx << std::endl;
		std::cout << "mPy" << mPy << std::endl;
		std::cout << "mPz" << mPz << std::endl;
		std::cout << "mTime" << mTime << std::endl;
		std::cout << "mVx" << mVx << std::endl;
		std::cout << "mVy" << mVy << std::endl;
		std::cout << "mVz" << mVz << std::endl;
	}

	Int_t mId;
	Float_t mEnergy;
	Int_t mKF;
	Int_t mKS;
	Float_t mLifetime;
	Float_t mMass;
	Int_t mParent;
	Float_t mPx;
	Float_t mPy;
	Float_t mPz;
	Float_t mTime;
	Float_t mVx;
	Float_t mVy;
	Float_t mVz;

	ClassDef( PythiaTrack, 2 )
};

#endif