/*
 ============================================================================
 Name		: CSocketServer.cpp
 Author	  : Ronny Röhricht
 Version	 :
 Copyright   : (C) Ronny Röhricht 2007
 Description : CSocketServer implementation
 ============================================================================
 */

#include "connection/CSocketServer.h"
#include "connection/SocketObserver.h"

/*
 CTimeOutTimer: timer for comms time-outs
 */
CTimeOutTimer::CTimeOutTimer( const TInt aPriority ) :
   CTimer( aPriority )
{
}

CTimeOutTimer::~CTimeOutTimer()
{
   Cancel();
}

CTimeOutTimer* CTimeOutTimer::NewL(const TInt aPriority,
                                   MTimeOutNotify& aTimeOutNotify)
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
void CTimeOutTimer::ConstructL( MTimeOutNotify &aTimeOutNotify )
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


////////////////////////////////////////////////////////////////////////////////

CSocketTransmitter::CSocketTransmitter() 
: CActive( EPriorityNormal),
  iByteBuffer( NULL ),
  iTimer( NULL ),
  iTransmitStatus( EWaiting ),
  iObserver( NULL )
{
}

CSocketTransmitter* CSocketTransmitter::NewLC( RSocket* aSocket )
{
   CSocketTransmitter* self = new ( ELeave ) CSocketTransmitter();
   CleanupStack::PushL( self);
   self->ConstructL( aSocket );
   return self;
}

CSocketTransmitter* CSocketTransmitter::NewL( RSocket* aSocket )
{
   CSocketTransmitter* self = CSocketTransmitter::NewLC( aSocket );
   CleanupStack::Pop(); // self;
   return self;
}

void CSocketTransmitter::ConstructL( RSocket* aSocket )
{
   iSocket = aSocket;
   ASSERT( iSocket != NULL );
  
   CActiveScheduler::Add( this ); // Add to scheduler
   iTimer = CTimeOutTimer::NewL( EPriorityMore, (*this ) );
   iTransmitStatus = EWaiting;
}

CSocketTransmitter::~CSocketTransmitter()
{
   Cancel(); // Cancel any request, if outstanding
   
   delete iByteBuffer;
   iByteBuffer = NULL;  
   delete iTimer;
   iTimer = NULL;
   
   if ( iSocket != NULL )
   {
      iSocket->Close();
   }
   iSocket = NULL;
   
   iTransmitStatus = EWaiting;
   iObserver = NULL;
}

bool CSocketTransmitter::TransmitL( const TPtrC8& aTransmittedData,
                                    MSocketObserver* aObserver /* = NULL */, 
                                    TUint aTimeout /* = 0 */ )
{
   bool busy = ( ( iByteBuffer != NULL ) || ( iTransmitStatus == ESending ) );
   bool ok = ( ( iSocket != NULL ) && !busy );
   
   if ( ok )
   {               
      // copy data that should transmitted to buffer on heap
      ASSERT( iTransmitStatus != ESending );
      ASSERT( iByteBuffer == NULL );
      
      iByteBuffer = static_cast < TDesC8* > ( aTransmittedData.AllocL() );   
      
      // register observer
      iObserver = aObserver;
      
      // write buffered data to socket
      ASSERT( iByteBuffer != NULL );
      iSocket->Write( *iByteBuffer , iStatus );
      
      // start timeout timer, if requested
      if ( aTimeout > 0 )
      {
         iTimer->After( aTimeout );
      }
      
      SetActive();
      iTransmitStatus = ESending;
   }
  
   return ok;
}

void CSocketTransmitter::RunL()
{
   if ( iStatus == KErrNone )
   {     
      switch( iTransmitStatus )
      {
         // Character has been written to socket
         case ESending:
            {
               // Delete content to transferred
               delete iByteBuffer;
               iByteBuffer = NULL;
               
               // Cancel TimeOut timer
               if ( iTimer != NULL )
               {
                  iTimer->Cancel(); 
               }
               iTransmitStatus = EWaiting;
               break;
            }
         // Request timed out
         case ETimedOut:
            {
               // Delete content to transferred
               delete iByteBuffer;
               iByteBuffer = NULL;
               
               if ( iObserver != NULL )
               {
                  iObserver->NotifyError( TSocketObserverErrorCodes::ETimeOut );
               }
               break;
            }
         default: break;
      };
   }
   else 
   {
      // Error: pass it up to the observer
      if ( iObserver != NULL )
      {
         iObserver->NotifyError( TSocketObserverErrorCodes::EErrorGeneric );
      }
   }
}

void CSocketTransmitter::DoCancel()
{
   if ( iSocket != NULL )
   {
      iSocket->CancelWrite();
   }
}

void CSocketTransmitter::TimerExpired()
{
   Cancel();
   iTransmitStatus = ETimedOut;
   TRequestStatus* p = &iStatus;
   SetActive();
   User::RequestComplete( p, ETimedOut );   
}

////////////////////////////////////////////////////////////////////////////////

CSocketReceiver::CSocketReceiver() 
: CActive( EPriorityNormal),
  iByteBuffer( NULL ),
  iSocket( NULL )
  iTimer( NULL ),
  iTimeOut( 0 ),
  iReceiveState( EWaiting ),
  iObserver( NULL )
{
}

CSocketReceiver* CSocketReceiver::NewLC( RSocket* aSocket )
{
   CSocketReceiver* self = new ( ELeave ) CSocketReceiver();
   CleanupStack::PushL( self);
   self->ConstructL( aSocket );
   return self;
}

CSocketReceiver* CSocketReceiver::NewL( RSocket* aSocket )
{
   CSocketReceiver* self = CSocketReceiver::NewLC( aSocket );
   CleanupStack::Pop(); // self;
   return self;
}

void CSocketReceiver::ConstructL( RSocket* aSocket )
{
   iSocket = aSocket;  
   ASSERT( iSocket != NULL );
   CActiveScheduler::Add( this); // Add to scheduler
}

CSocketReceiver::~CSocketReceiver()
{
   Cancel(); // Cancel any request, if outstanding
   
   if ( iTimer != NULL )
   {
      delete iTimer;
      iTimer = NULL;
   }   
}

bool CSocketReceiver::Receive( MSocketObserver& aObserver,
                               TUint            aBlockUntil /* = 0 */,
                               TUint            aTimeout /* = 0 */)
{
   bool ok
   if ( !IsActive() )
   {
      iSocket->Recv();
      iSocket->Recv( iByteBuffer, 0, iStatus, aBlockUntil );
      SetActive();
   }
}

void CSocketReceiver::RunL()
{
   if ( iStatus == KErrNone )        
   { 
      // Character has been read from socket
      TBuf16<1> Buffer;
      Buffer.Copy(iBuffer);
      iConsole->PrintNotify(Buffer);
     
//      TInetAddr &ipAddr = GetHostby;
//      IssueRecvFrom(ipAddr);
   }
   else
   {    // Error: pass it up to user interface   
      _LIT(KCEchoReadError,"\nCEchoRead error");
      iConsole->ErrorNotify(KCEchoReadError, iStatus.Int());
   }   
}

void CSocketReceiver::DoCancel()
{
   if ( iSocket != NULL )
   {
      iSocket->CancelRead();
   }      
}

////////////////////////////////////////////////////////////////////////////////////

CSocketServer::CSocketServer() 
:  CActive( EPriorityStandard), // Standard priority
   iServerStatus ( EIdle ),
   iTransmitter ( NULL ),
   iReceiver( NULL ),
   iTimeout( 0 ),
   iSocket(),
   iSocketServ(),
   iResolver(),
   iNameEntry(),
   iNameRecord(),
   iTimer( NULL ),
   iAddress( 0 )
{
}

CSocketServer* CSocketServer::NewLC()
{
   CSocketServer* self = new ( ELeave ) CSocketServer();
   CleanupStack::PushL( self);
   self->ConstructL();
   return self;
}

CSocketServer* CSocketServer::NewL()
{
   CSocketServer* self = CSocketServer::NewLC();
   CleanupStack::Pop(); // self;
   return self;
}

void CSocketServer::ConstructL()
{
   CActiveScheduler::Add( this); // Add to scheduler
}

CSocketServer::~CSocketServer()
{
   Cancel(); // Cancel any request, if outstanding
   // Delete instance variables if any
}

void CSocketServer::OpenL( MSocketObserver* aObserver /* = NULL */ )
{
   
}

void CSocketServer::Transmit( const TPtrC&      aTransmittedData, 
                              MSocketObserver*  aObserver /* = NULL */,
                              TUint             aTimeout /* = 0 */ )
{
   
}

void CSocketServer::Receive( MSocketObserver&   aObserver,
                             TUint              aBlockUntil /* = 0 */,
                             TUint              aTimeout /* = 0 */ )
{
   
}

void CSocketServer::ConnectL( TUint32           aAddr, 
                              MSocketObserver*  aObserver /* = NULL */,
                              TUint             aTimeout /* = 0 */)
{
   
}

void CSocketServer::ConnectL( const TDesC&      aServerName,
                              MSocketObserver*  aObserver /* = NULL */,
                              TUint             aTimeout /* = 0 */)
{
   
}

void CSocketServer::Close()
{
   
}

void CSocketServer::RunL()
{
   SetActive(); // Tell scheduler a request is active
}

void CSocketServer::DoCancel()
{
   
}

