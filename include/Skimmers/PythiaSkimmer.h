#ifndef PYTHIA_SKIMMER_H
#define PYTHIA_SKIMMER_H

#include <memory>

#include "TreeAnalyzer.h"
#include "PythiaTrackReader.h"

#include "PhysicalConstants.h"

class PythiaSkimmer : public TreeAnalyzer
{
public:
	virtual const char* classname() const { return "PythiaSkimmer"; }
	PythiaSkimmer() {}
	~PythiaSkimmer() {}

	virtual void initialize(){
		TreeAnalyzer::initialize();

		ptr = shared_ptr<PythiaTrackReader>( new PythiaTrackReader( chain ) );


		kfcodes[ "mu+" ]   = -13;
		kfcodes[ "mu-" ]   = 13;
		kfcodes[ "rho0" ]  = 113;
		kfcodes[ "pi+" ]   = 211;
		kfcodes[ "k+" ]    = 321;
		kfcodes[ "omega" ] = 223;
		kfcodes[ "phi" ]   = 333;
		kfcodes[ "jpsi" ]  = 443;
		kfcodes[ "eta" ]  = 221;
		kfcodes[ "etaprime" ]  = 331;

	}

	virtual bool starAccepts( TLorentzVector &lv1, TLorentzVector &lv2 ){

		if ( lv1.Pt() < 0.2 || lv2.Pt() < 0.2 )
			return false;
		return true;
	}

	virtual void analyzeEvent(){

		// INFO( classname(), "Event" );
		// INFO( classname(), "# Tracks = " << ptr->getNTracks() );

		mup.clear();
		mum.clear();

		int n_tracks = ptr->getNTracks();
		for ( int iTrack = 0; iTrack < n_tracks; iTrack++ ){
			PythiaTrack * pyTr = ptr->getTrack( iTrack );
			PythiaTrack * pyTrPar = ptr->getTrackParent( pyTr );
			book->fill( "KF", pyTr->mKF );
			book->fill( "KS", pyTr->mKS );

			int parentKF = 0;
			if ( pyTrPar )
				parentKF = pyTrPar->mKF;
			if ( kfcodes[ "mu-" ] == pyTr->mKF ){
				book->fill( "mumParents", parentKF );
				mum.push_back( pyTr );
			}
			if ( kfcodes["mu+"] == pyTr->mKF ){
				book->fill( "mupParents", parentKF );
				mup.push_back( pyTr );
			}
		}

		if ( mum.size() == 0 || mup.size() == 0 ) return;


		int nPos = mup.size();
		int nNeg = mum.size();

		// Make all true pairs invariant mass plot
		for ( int iPos = 0; iPos < nPos; iPos++ ){
			PythiaTrack* posplc = mup[ iPos ];
			for ( int iNeg = 0; iNeg < nNeg; iNeg++ ){
				PythiaTrack* negplc = mum[ iNeg ];
				if ( posplc->mParent != negplc->mParent ) continue;

				PythiaTrack * parent = ptr->getTrackParent( posplc );
				if ( parent ){
					
					
					TLorentzVector lv1, lv2, lv, lvp;
					lv1.SetXYZM( negplc->mPx, negplc->mPy, negplc->mPz, negplc->mMass );
					lv2.SetXYZM( posplc->mPx, posplc->mPy, posplc->mPz, posplc->mMass );
					lvp.SetPxPyPzE( parent->mPx, parent->mPy, parent->mPz, parent->mEnergy );
					lv = lv1 + lv2;

					// cout << "=======NEG=========" << endl;
					// negplc->print();
					// cout << "=======POS=========" << endl;
					// posplc->print();

					// INFO( classname(), "rho M from daughters = " << lv.M()  );
					// INFO( classname(), "rho M from self lv = " << lvp.M()  );
					// INFO( classname(), "rho M from pythia track = " << parent->mMass  );

					book->fill( "true_all", lv.M() );

					if ( kfcodes[ "rho0" ] == parent->mKF ){
						book->fill( "true_rho0", lv.M() );
						book->fill( "truep_rho0", lvp.M() );
						
					}
					if ( kfcodes[ "omega" ] == parent->mKF )
						book->fill( "true_omega", lv.M() );
					if ( kfcodes[ "phi" ] == parent->mKF )
						book->fill( "true_phi", lv.M() );
					if ( kfcodes[ "jpsi" ] == parent->mKF )
						book->fill( "true_jpsi", lv.M() );
					if ( kfcodes[ "eta" ] == parent->mKF )
						book->fill( "true_eta", lv.M() );
					if ( kfcodes[ "etaprime" ] == parent->mKF )
						book->fill( "true_etaprime", lv.M() );

				}

			}	
		}

		// true ls pairs
		for ( int iPos = 0; iPos < nPos; iPos++ ){
			PythiaTrack* posplc1 = mup[ iPos ];
			for ( int iPos2 = iPos; iPos2 < nPos; iPos2++ ){
				if ( iPos == iPos2 ) continue;
				PythiaTrack* posplc2 = mup[ iPos2 ];

				if ( posplc1->mParent != posplc2->mParent ) continue;

				PythiaTrack * parent = ptr->getTrackParent( posplc1 );
				if ( parent ){
					TLorentzVector lv;
					lv.SetPxPyPzE( parent->mPx, parent->mPy, parent->mPz, parent->mEnergy );
					book->fill( "true_ls", lv.M() );
				}
			} // loop iPos2
		} // iPos


		// foreground uls pairs
		for ( int iPos = 0; iPos < nPos; iPos++ ){
			PythiaTrack* posplc = mup[ iPos ];
			for ( int iNeg = 0; iNeg < nNeg; iNeg++ ){
				PythiaTrack* negplc = mum[ iNeg ];

				TLorentzVector lv1, lv2, lv;
				lv1.SetPxPyPzE( negplc->mPx, negplc->mPy, negplc->mPz, negplc->mEnergy );
				lv2.SetPxPyPzE( posplc->mPx, posplc->mPy, posplc->mPz, posplc->mEnergy );
				lv = lv1 + lv2;
				book->fill( "fg_uls_all", lv.M() );
				book->fill( "fg_uls_all_2d", lv.M(), lv.Pt() );

				if ( starAccepts( lv1, lv2 ) ){
					book->fill( "star_fg_uls_all", lv.M() );					
				}

			} // iNeg
		} // iPos




	}

protected:

	shared_ptr<PythiaTrackReader> ptr;
	vector<PythiaTrack*> mup;
	vector<PythiaTrack*> mum;

	map<string, int> kfcodes;
};
#endif