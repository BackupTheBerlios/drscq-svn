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
#include "connection/CSocketReceiver.h"
#include "connection/CSocketTransmitter.h"

#include "observer/MSocketObserver.h"
#include "observer/MErrorObserver.h"


CSocketServer::CSocketServer() 
:  CActive( EPriorityStandard ), // Standard priority
   iServerStatus ( EIdle ),
   iTransmitter ( NULL ),
   iReceiver( NULL ),
   iObserver( NULL ),
   iConnectionObserver( NULL ),
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
   CleanupStack::PushL( self );
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
   iTimer = CTimeOutTimer::NewL( EPriorityHigh, *this );
   
   CActiveScheduler::Add( this); // Add to scheduler
}

CSocketServer::~CSocketServer()
{
   if ( iTransmitter != NULL )
   {
      iTransmitter->Cancel();
   }
   if ( iReceiver != NULL )
   {
      iReceiver->Cancel();
   }
   if ( iTimer != NULL )
   {
      iTimer->Cancel();
   }
   
   delete iReceiver;
   delete iTransmitter;
   delete iTimer;
   iSocket.Close();
   iSocketServ.Close();
}

void CSocketServer::OpenL()
{
   // Open channel to Socket Server
   User::LeaveIfError( iSocketServ.Connect() );
   
   // Open a TCP socket
   User::LeaveIfError( iSocket.Open( iSocketServ, KAfInet, KSockStream, KProtocolInetTcp ) );
   
   iReceiver    = CSocketReceiver::NewL( &iSocket );
   iTransmitter = CSocketTransmitter::NewL( &iSocket );
}

void CSocketServer::TransmitL( const TPtrC&      aTransmittedData, 
                               MSocketObserver*  aObserver /* = NULL */,
                               TUint             aTimeout /* = 0 */ )
{
   
}

void CSocketServer::ReceiveL( MSocketObserver&   aObserver,
                              TUint              aBlockUntil /* = 0 */,
                              TUint              aTimeout /* = 0 */ )
{
   
}

void CSocketServer::ConnectL( TUint32           aAddr,
                              TUint16           aPort,
                              TUint             aTimeout, /* = 0 */
                              MErrorObserver*   aObserver /* = NULL */ )
{
   // port number for test purposes - may need to be changed
   iPort = aPort;
   iAddress.SetPort( aPort );
   iAddress.SetAddress( aAddr );
   iConnectionObserver = aObserver;
   iSocket.Connect( iAddress, iStatus );
   iServerStatus = EConnecting;
   
   if ( iConnectionObserver != NULL )
   {
      iConnectionObserver->NotifyError( TErrorObserverErrorTypes::EErrorInfo,
                                        TErrorObserverInfoTypes::EConnecting );                                                  
   }  
   
   SetActive();
   
   if ( aTimeout > 0 )
   {
      iTimer->After( aTimeout ); 
   }
}

void CSocketServer::ConnectL( const TDesC&      aServerName,
                              TUint16           aPort,
                              TUint             aTimeout, /* = 0 */
                              MErrorObserver*   aObserver /* = NULL */ )
{
   iPort = aPort;
   iConnectionObserver = aObserver;
   // Initiate DNS
   User::LeaveIfError( iResolver.Open( iSocketServ, KAfInet, KProtocolInetUdp ) );
   // DNS request for name resolution
   iResolver.GetByName( aServerName, iNameEntry, iStatus );
   
   iServerStatus = ELookingUp;
   
   // Request time out
   if ( aTimeout > 0 )
   {
      iTimer->After( aTimeout );
   }
   SetActive();
}

void CSocketServer::Close()
{
   
}

void CSocketServer::RunL()
{
   // Cancel TimeOut timer before completion
   iTimer->Cancel(); 
   TBuf < 15 > ipAddr;

   switch( iServerStatus )
   {
      case EConnecting:
      {
          // IP connection request
          if ( iStatus == KErrNone )
          // Connection completed sucessfully
          {                    
             if ( iConnectionObserver != NULL )
             {
                iConnectionObserver->NotifyError( TErrorObserverErrorTypes::EErrorInfo,
                                                  TErrorObserverInfoTypes::ESuccessful );                                                  
             }  
             iServerStatus = EConnected;
          }
          else
          {
             iServerStatus = EConnectFailed;

             if ( iConnectionObserver != NULL )
             {
                iConnectionObserver->NotifyError( TErrorObserverErrorTypes::EErrorCritical,
                                                  TErrorObserverInfoTypes::EConnectionFailed );
             }      
          }
          break;
      }
      case ETimedOut:
      {
          // Timeout request
         if ( iConnectionObserver != NULL )
         {
            iConnectionObserver->NotifyError( TErrorObserverErrorTypes::EErrorCritical,
                                              TErrorObserverInfoTypes::ETimeOut );
         }  
         break;
      }
      case ELookingUp:
      {
          iResolver.Close();
          if ( iStatus == KErrNone )
          // DNS look up successful
          {
             iNameRecord = iNameEntry();
             
             // Extract domain name and IP address from name record
             TInetAddr::Cast( iNameRecord.iAddr ).Output( ipAddr );
             // And connect to the IP address
             ConnectL( TInetAddr::Cast( iNameRecord.iAddr ).Address(), iPort );
           }
          else
          {   
             iStatus = ELookUpFailed;
             if ( iConnectionObserver != NULL )
             {
                iConnectionObserver->NotifyError( TErrorObserverErrorTypes::EErrorCritical,
                                                  TErrorObserverInfoTypes::EDNSFailure );
             }  
          }
          break;
      }
      default:;
   };
}

void CSocketServer::DoCancel()
{
   iTimer->Cancel();

   // Cancel appropriate request to socket
   switch ( iServerStatus )
   {
      case EConnecting:
      {
         iSocket.CancelConnect();
         break;
      }         
      case ELookingUp:
      {
         // Cancel look up attempt
         iResolver.Cancel();
         iResolver.Close();
         break;
      }         
      default:
      {
         break;
      }
   }
}


void CSocketServer::TimerExpired()
{
   Cancel();
   iServerStatus = ETimedOut;
   TRequestStatus* p = &iStatus;     
   SetActive();
   User::RequestComplete( p, ETimedOut );
}
