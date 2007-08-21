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

class MSocketObserver;

// MTimeOutNotify: used in conjunction with CTimeOutTimer class
class MTimeOutNotify
{
   public:
      virtual void TimerExpired() = 0;
};

// CTimeOutTimer: timer for comms time-outs
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

///////////////////////////////////////////////////////////////////////////////////////////

class CSocketTransmitter : public CActive, public MTimeOutNotify
{
   public:
      
      enum TTransmitState 
      {
         ESending, EWaiting ,ETimedOut
      };
      
   public:
      // Cancel and destroy
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

///////////////////////////////////////////////////////////////////////////////////////////

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

      bool Receive( MSocketObserver& aObserver,
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
      
      TDesC8*          iByteBuffer;
      RSocket*         iSocket;
      CTimeOutTimer*   iTimer;
      TInt             iTimeOut;
      TReceiveState    iReceiveState;
      MSocketObserver* iObserver;
};


///////////////////////////////////////////////////////////////////////////////////////////

class CSocketServer : public CActive, public MTimeOutNotify
{
   public:
      enum TSocketServerState
      {
         EIdle,
         EComplete, EConnecting, EConnected,
         ELookingUp, ELookUpFailed, EConnectFailed,
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

      void OpenL( MSocketObserver* aObserver = NULL );

      void Transmit( const TPtrC&      aTransmittedData, 
                     MSocketObserver*  aObserver = NULL,
                     TUint             aTimeout = 0 );

      void Receive( MSocketObserver&   aObserver,
                    TUint              aBlockUntil = 0,
                    TUint              aTimeout = 0 );
      
      void ConnectL( TUint32           aAddr, 
                     MSocketObserver*  aObserver = NULL,
                     TUint             aTimeout = 0 );
      
      void ConnectL( const TDesC&      aServerName,
                     MSocketObserver*  aObserver = NULL,
                     TUint             aTimeout = 0 );

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
      TUint                iTimeout;
      RSocket              iSocket;
      RSocketServ          iSocketServ;
      RHostResolver        iResolver; 
      TNameEntry           iNameEntry;
      TNameRecord          iNameRecord;
      CTimeOutTimer*       iTimer;
      TInetAddr            iAddress;
};

#endif // CSOCKETSERVER_H

