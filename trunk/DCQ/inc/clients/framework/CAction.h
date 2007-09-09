/*
============================================================================
 Name		: CAction.h
 Author	  : Ronny R�hricht
 Version	 :
 Copyright   : (C) Ronny R�hricht 2007
 Description : CAction declaration
============================================================================
*/

#ifndef CACTION_H
#define CACTION_H

#include <e32base.h>

class MErrorObserver;
class MProgressObserver;
class CSocketReceiver;

class CTransition;
class CState;


class CAction : public CActive
{
   public:
   	// Cancel and destroy
   	virtual ~CAction() {}
         
      virtual void PerformL( MErrorObserver* aErrorObserver = NULL,
                             MProgressObserver* aProgressObserver = NULL ) = 0;
   
   protected:
   	// C++ constructor
   	CAction() 
         : CActive( EPriorityStandard ),
           iErrorObserver( NULL ),
           iProgressObserver( NULL ),
           iTransitions( NULL ),
           iInitialState( NULL )
      {}   
   
   protected:
      
      MErrorObserver*    iErrorObserver;
      MProgressObserver* iProgressObserver;
      
      CArrayFix < CTransition* >* iTransitions;
      CState*                     iInitialState;

};

#endif // CACTION_H
