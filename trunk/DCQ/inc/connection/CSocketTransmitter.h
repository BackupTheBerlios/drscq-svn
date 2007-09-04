/*
============================================================================
 Name		: CSocketTransmitter.h
 Author	  : Ronny Röhricht
 Version	 :
 Copyright   : (C) Ronny Röhricht 2007
 Description : CCSocketTransmitter declaration
============================================================================
*/

#ifndef CSOCKETTRANSMITTER_H
#define CSOCKETTRANSMITTER_H

#include <e32base.h>	   // For CActive, link against: euser.lib

#include "connection/CTimeOutTimer.h"
#include "observer/MTimeOutObserver.h"

class MSocketObserver;
class RSocket;

class CSocketTransmitter : public CActive, public MTimeOutObserver
{
   public:
      
      enum TTransmitState 
      {
         ESending, EWaiting ,ETimedOut
      };
      
   public:
      // CancelCurrentAction and destroy
      ~CSocketTransmitter();

      // Two-phased constructor.
      static CSocketTransmitter* NewL( RSocket* aSocket );

      // Two-phased constructor.
      static CSocketTransmitter* NewLC( RSocket* aSocket );

   public:
      // New functions

      bool TransmitL( const TPtrC8&    aTransmittedData,
                      MSocketObserver* aObserver = NULL, 
                      TUint            aTimeout = 0 );

   private:
      // C++ constructor
      CSocketTransmitter();

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
      
      TDesC8 *         iByteBuffer;
      RSocket*         iSocket;
      CTimeOutTimer*   iTimer;
      TTransmitState   iTransmitStatus;
      MSocketObserver* iObserver;
};

#endif // CSOCKETTRANSMITTER_H
