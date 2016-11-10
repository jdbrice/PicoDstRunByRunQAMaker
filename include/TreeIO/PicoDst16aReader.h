#ifndef PICO_DST_16A_READER_H
#define PICO_DST_16A_READER_H

#include "IObject.h"

#include "StPicoBTOWHit.h"
#include "StPicoBTofHit.h"
#include "StPicoBTofPidTraits.h"
#include "StPicoEmcPidTraits.h"
#include "StPicoEmcTrigger.h"
#include "StPicoEvent.h"
#include "StPicoMtdHit.h"
#include "StPicoMtdPidTraits.h"
#include "StPicoMtdTrigger.h"
#include "StPicoTrack.h"

class PicoDst16aReader : public IObject
{
public:
	virtual const char* classname() const { return "PicoDst16aReader"; }
	PicoDst16aReader() {}
	
	PicoDst16aReader( TChain * _tree ) {
		create( _tree );
	}
	~PicoDst16aReader() {}

	StPicoEvent * event(  ) { return (StPicoEvent*)events->At(0); }
	Int_t nTracks() { return tracks->GetEntries(); }
	StPicoTrack * track( int i ) { return (StPicoTrack*)tracks->At(i); }

	Int_t nMtdPidTraits() { return mtdPidTraits->GetEntries(); }
	StPicoMtdPidTraits * mtdPidTrait( int i ) { return (StPicoMtdPidTraits*)mtdPidTraits->At(i); }
	StPicoMtdPidTraits * mtdPidTraitFor( int i ) { 
		StPicoTrack * _track = track( i );
		if (_track->mtdPidTraitsIndex() < 0 )
			return nullptr;
		DEBUG( classname(), "Mtd index = " << _track->mtdPidTraitsIndex() );
		return (StPicoMtdPidTraits*)mtdPidTraits->At( _track->mtdPidTraitsIndex() ); 
	}

	Int_t nBTofPidTraits() { return btofPidTraits->GetEntries(); }
	StPicoBTofPidTraits * btofPidTrait( int i ) { return (StPicoBTofPidTraits*)btofPidTraits->At(i); }
	StPicoBTofPidTraits * btofPidTraitFor( int i ) { 
		StPicoTrack * _track = track( i );
		if (_track->bTofPidTraitsIndex() < 0 )
			return nullptr;
		return (StPicoBTofPidTraits*)btofPidTraits->At( _track->bTofPidTraitsIndex() ); 
	}

	void create( TChain * _tree ){
		if ( nullptr == _tree ){
			ERROR( classname(), "Invalid TChain" );
			return;
		}


		/***************** Event branch ******************/
		b_events = _tree->GetBranch( "Event" );
		if ( !b_events ){
			ERROR( classname(), "Event Branch DNE" );
			return;
		}

		events = new TClonesArray( "StPicoEvent" );
		_tree->SetBranchAddress( "Event", &events );
		b_events->SetAutoDelete( kFALSE );


		/***************** Tracks branch ******************/
		b_tracks = _tree->GetBranch( "Tracks" );
		if ( !b_tracks ){
			ERROR( classname(), "Tracks Branch DNE" );
			return;
		}

		tracks = new TClonesArray( "StPicoTrack" );
		_tree->SetBranchAddress( "Tracks", &tracks );
		b_tracks->SetAutoDelete( kFALSE );

		/***************** MtdPidTraits branch ******************/
		b_mtdPidTraits = _tree->GetBranch( "MtdPidTraits" );
		if ( !b_mtdPidTraits ){
			ERROR( classname(), "MtdPidTraits Branch DNE" );
			return;
		}

		mtdPidTraits = new TClonesArray( "StPicoTrack" );
		_tree->SetBranchAddress( "MtdPidTraits", &mtdPidTraits );
		b_mtdPidTraits->SetAutoDelete( kFALSE );

		/***************** BTofPidTraits branch ******************/
		b_btofPidTraits = _tree->GetBranch( "BTofPidTraits" );
		if ( !b_btofPidTraits ){
			ERROR( classname(), "BTofPidTraits Branch DNE" );
			return;
		}

		btofPidTraits = new TClonesArray( "StPicoTrack" );
		_tree->SetBranchAddress( "BTofPidTraits", &btofPidTraits );
		b_btofPidTraits->SetAutoDelete( kFALSE );

	}
protected:


	TBranch * b_events;
	TClonesArray * events = nullptr;

	TBranch * b_tracks;
	TClonesArray * tracks = nullptr;

	TBranch * b_mtdPidTraits;
	TClonesArray * mtdPidTraits = nullptr;

	TBranch * b_btofPidTraits;
	TClonesArray * btofPidTraits = nullptr;

};

#endif