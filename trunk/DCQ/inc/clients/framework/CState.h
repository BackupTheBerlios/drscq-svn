/*
============================================================================
 Name		: CState.h
 Author	  : Ronny R�hricht
 Version	 :
 Copyright   : (C) Ronny R�hricht 2007
 Description : CState declaration
============================================================================
*/

#ifndef CSTATE_H
#define CSTATE_H

#include <e32base.h>
#include "observer/MSocketObserver.h"


class CState : public CActive,
               public MSocketObserver
{
   public:
   	// Cancel and destroy
   	virtual ~CState();
      
      virtual void EnterL() = 0;
      
      virtual void LeaveL() = 0;
   
   protected:
      
      // C++ constructor
      CState();
            
};

#endif // CSTATE_H
