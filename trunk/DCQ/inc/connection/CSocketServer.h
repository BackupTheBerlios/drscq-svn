/*
 ============================================================================
 Name		: CSocketServer.h
 Author	  : Ronny Röhricht
 Version	 :
 Copyright   : (C) Ronny Röhricht 2007
 Description : CSocketServer declaration
 ============================================================================
 */

#ifndef CSOCKETSERVER_H
#define CSOCKETSERVER_H

#include <e32cons.h>
#include <in_sock.h>
#include <nifman.h>

#include "connection/CTimeOutTimer.h"
#include "observer/MTimeOutObserver.h"

class CSocketTransmitter;
class CSocketReceiver;
class MSocketObserver;
class MErrorObserver;

class CSocketServer : public CActive, public MTimeOutObserver
{
   public:
      enum TSocketServerState
      {
         EIdle,
         EComplete, EConnecting, EConnected,
         ELookingUp, ELookUpFailed, EConnectFailed,
         ETimedOut
      };
      
   public:
      // Cancel and destroy
      ~CSocketServer();

      // Two-phased constructor.
      static CSocketServer* NewL();

      // Two-phased constructor.
      static CSocketServer* NewLC();

   public:
      // New functions

      void OpenL();

      void TransmitL( const TPtrC&      aTransmittedData, 
                      MSocketObserver*  aObserver = NULL,
                      TUint             aTimeout = 0 );

      void ReceiveL( MSocketObserver&   aObserver,
                     TUint              aBlockUntil = 0,
                     TUint              aTimeout = 0 );
      
      void ConnectL( TUint32           aAddr,
                     TUint16           aPort,
                     TUint             aTimeout = 0,
                     MErrorObserver*   aObserver = NULL );
      
      void ConnectL( const TDesC&      aServerName,
                     TUint16           aPort,
                     TUint             aTimeout = 0,
                     MErrorObserver*   aObserver = NULL );

      void Close();

   private:
      // C++ constructor
      CSocketServer();

      // Second-phase constructor
      void ConstructL();

   private:
      // From CActive
      // Handle completion
      void RunL();

      // How to cancel me
      void DoCancel();
      
      void TimerExpired();

   private:
      
      TSocketServerState   iServerStatus;
      CSocketTransmitter*  iTransmitter;
      CSocketReceiver*     iReceiver;
      MSocketObserver*     iObserver;
      MErrorObserver*      iConnectionObserver;
      TUint                iTimeout;
      RSocket              iSocket;
      RSocketServ          iSocketServ;
      RHostResolver        iResolver; 
      TNameEntry           iNameEntry;
      TNameRecord          iNameRecord;
      CTimeOutTimer*       iTimer;
      TInetAddr            iAddress;
      TUint16              iPort;
};

#endif // CSOCKETSERVER_H

