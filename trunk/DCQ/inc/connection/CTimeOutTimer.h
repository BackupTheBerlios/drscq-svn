/*
============================================================================
 Name		: TimeOutTimer.h
 Author	  : Ronny Röhricht
 Version	 :
 Copyright   : (C) Ronny Röhricht 2007
 Description : TimeOutTimer declaration
============================================================================
*/

#ifndef CTIMEOUTTIMER_H
#define CTIMEOUTTIMER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include "observer/MTimeOutObserver.h"

// CLASS DECLARATION

class CTimeOutTimer : public CTimer
{
   public:
      static CTimeOutTimer* NewL( const TInt aPriority, 
                                  MTimeOutObserver& aTimeOutNotify );
      ~CTimeOutTimer();

   protected:
      CTimeOutTimer( const TInt aPriority );
      
      void ConstructL( MTimeOutObserver& aTimeOutNotify );
      
      virtual void RunL();

   private:
      MTimeOutObserver* iNotify;
};

#endif // CTIMEOUTTIMER_H

