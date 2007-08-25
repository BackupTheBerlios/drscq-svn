/*
============================================================================
 Name		: TimeOutTimer.cpp
 Author	  : Ronny Röhricht
 Version	 :
 Copyright   : (C) Ronny Röhricht 2007
 Description : TimeOutTimer implementation
============================================================================
*/

#include "connection/CTimeOutTimer.h"

CTimeOutTimer::CTimeOutTimer( const TInt aPriority ) 
: CTimer( aPriority )
{
}

CTimeOutTimer::~CTimeOutTimer()
{
   Cancel();
}

CTimeOutTimer* CTimeOutTimer::NewL(const TInt aPriority,
                                   MTimeOutObserver& aTimeOutNotify)
{
   CTimeOutTimer *p = new (ELeave) CTimeOutTimer(aPriority);
   CleanupStack::PushL( p );
   p->ConstructL( aTimeOutNotify );
   CleanupStack::Pop();
   return p;
}

/**
 * ConstructL function is used to add the active object to the scheduler 
 */
void CTimeOutTimer::ConstructL( MTimeOutObserver &aTimeOutNotify )
{
   iNotify = &aTimeOutNotify;
   CTimer::ConstructL();
   CActiveScheduler::Add(this);
}

/**
 Timer request has completed, so notify the timer's owner
 */
void CTimeOutTimer::RunL()

{
   iNotify->TimerExpired();
}
