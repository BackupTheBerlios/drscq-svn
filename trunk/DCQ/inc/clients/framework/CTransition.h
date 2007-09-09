/*
============================================================================
 Name		: CTransition.h
 Author	  : Ronny Röhricht
 Version	 :
 Copyright   : (C) Ronny Röhricht 2007
 Description : CTransition declaration
============================================================================
*/

#ifndef CTRANSITION_H
#define CTRANSITION_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

// CLASS DECLARATION

/**
*  CCTransition
* 
*/

class CState;

class CTransition : public CBase
{
   public: // Constructors and destructor
   
   	/**
   		* Destructor.
   		*/
   	~CTransition();
   
   		/**
   		* Two-phased constructor.
   		*/
   	static CTransition* NewL();
   
   		/**
   		* Two-phased constructor.
   		*/
   	static CTransition* NewLC();
      
      
      TBool AddStateL( CState& aState, TInt aSignal );
      
      CState* GetNextState( TInt aSignal ) const;
   
   private:
   
   	/**
   		* Constructor for performing 1st stage construction
   		*/
   	CTransition();
   
   	/**
   		* EPOC default constructor for performing 2nd stage construction
   		*/
   	void ConstructL();
      
   private:            
      
      struct TSignalStatePair
      {
         TSignalStatePair( TInt    aSignal, 
                           CState& aState ) 
         : iSignal( aSignal ), 
           iState( aState )
         {}
         
         const TInt iSignal;
         CState&    iState;
      };
      
      typedef CArrayFixSeg < TSignalStatePair > TransitionTable;
            
      mutable TransitionTable* iTransitionTable;
};

#endif // CTRANSITION_H

