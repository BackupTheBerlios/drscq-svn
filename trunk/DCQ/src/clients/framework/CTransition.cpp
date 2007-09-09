/*
============================================================================
 Name		: CTransition.cpp
 Author	  : Ronny Röhricht
 Version	 :
 Copyright   : (C) Ronny Röhricht 2007
 Description : CCTransition implementation
============================================================================
*/

#include "clients/framework/CTransition.h"

CTransition::CTransition()
: iTransitionTable( NULL )
{
	// No implementation required
}


CTransition::~CTransition()
{
}

CTransition* CTransition::NewLC()
{
	CTransition* self = new ( ELeave ) CTransition();
	CleanupStack::PushL( self );
	self->ConstructL();
	return self;
}

CTransition* CTransition::NewL()
{
	CTransition* self = CTransition::NewLC();
	CleanupStack::Pop(); // self;
	return self;
}

void CTransition::ConstructL()
{
   iTransitionTable = new ( ELeave ) CArrayFixSeg < TSignalStatePair >( 2 );
}

TBool CTransition::AddStateL( CState& aState, TInt aSignal )
{
   TBool aOk = false;
   
   // first check if not another state already exists for this signal
   CState* aTempState = GetNextState( aSignal );
   
   if ( aTempState == NULL )
   {
      const TSignalStatePair aSignalStatePair( aSignal, aState );
      iTransitionTable->AppendL( aSignalStatePair );
      aOk = true;
   }
   
   return aOk;
}

CState* CTransition::GetNextState( TInt aSignal ) const
{
   CState* aFoundState = NULL;
     
   for ( TUint i = 0; ( aFoundState == NULL && i < iTransitionTable->Count() ); ++i  )
   {
      const TSignalStatePair& aSignalStatePair = iTransitionTable->At( i );
      
      if ( aSignalStatePair.iSignal == aSignal )
      {
         aFoundState = &aSignalStatePair.iState;
      }
   }
   
   return aFoundState;
}

