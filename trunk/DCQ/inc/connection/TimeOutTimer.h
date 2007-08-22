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


// MTimeOutNotify: used in conjunction with CTimeOutTimer class
class MTimeOutNotify
{
   public:
      virtual void TimerExpired() = 0;
};

// CLASS DECLARATION

class CTimeOutTimer : public CTimer
{
   public:
      static CTimeOutTimer* NewL( const TInt aPriority, 
                                  MTimeOutNotify& aTimeOutNotify );
      ~CTimeOutTimer();

   protected:
      CTimeOutTimer( const TInt aPriority );
      
      void ConstructL( MTimeOutNotify& aTimeOutNotify );
      
      virtual void RunL();

   private:
      MTimeOutNotify* iNotify;
};

#endif // CTIMEOUTTIMER_H

