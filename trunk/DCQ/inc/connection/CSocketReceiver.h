/*
============================================================================
 Name		: CSocketReceiver.h
 Author	  : Ronny Röhricht
 Version	 :
 Copyright   : (C) Ronny Röhricht 2007
 Description : CSocketReceiver declaration
============================================================================
*/

#ifndef CSOCKETRECEIVER_H
#define CSOCKETRECEIVER_H

#include <e32base.h>	   // For CActive, link against: euser.lib

#include "connection/TimeOutTimer.h"

class MSocketObserver;
class RSocket;

class CSocketReceiver : public CActive, public MTimeOutNotify
{
   public:
      enum TReceiveState 
      {
         EReceiving, EWaiting ,ETimedOut
      };
   
   public:
      // Cancel and destroy
      ~CSocketReceiver();

      // Two-phased constructor.
      static CSocketReceiver* NewL( RSocket* aSocket );

      // Two-phased constructor.
      static CSocketReceiver* NewLC( RSocket* aSocket );

   public:
      // New functions

      bool ReceiveL( MSocketObserver& aObserver,
                     TUint            aBlockUntil = 0,
                     TUint            aTimeout = 0);     

   private:
      // C++ constructor
      CSocketReceiver();

      // Second-phase constructor
      void ConstructL( RSocket* aSocket );

   private:
      // From CActive
      // Handle completion
      void RunL();

      // How to cancel me
      void DoCancel();
      
      void TimerExpired();
      
   private:
      
      HBufC8*          iMultiByteBuffer;
      TBuf8 < 1 >      iSingleByteBuffer;
      RSocket*         iSocket;
      CTimeOutTimer*   iTimer;
      TInt             iTimeOut;
      TReceiveState    iReceiveState;
      MSocketObserver* iObserver;
};
#endif // CSOCKETRECEIVER_H
