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
#include "observer/MProgressObserver.h"


CSocketServer::CSocketServer() 
:  CActive( EPriorityStandard ), // Standard priority
   iServerStatus ( EIdle ),
   iTransmitter ( NULL ),
   iReceiver( NULL ),
   iErrorObserver( NULL ),
   iProgressObserver( NULL ),
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
   
   // Open channel to Socket Server
   User::LeaveIfError( iSocketServ.Connect() );
  
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

   iErrorObserver = NULL;
   iProgressObserver = NULL;
}



void CSocketServer::InitL()
{
   // Open a TCP socket
   User::LeaveIfError( iSocket.Open( iSocketServ, KAfInet, KSockStream, KProtocolInetTcp ) );
   
   iReceiver    = CSocketReceiver::NewL( &iSocket );
   iTransmitter = CSocketTransmitter::NewL( &iSocket );
}



void CSocketServer::ConnectL( TUint32            aAddr,
                              TUint16            aPort,
                              TUint              aTimeout, /* = 0 */
                              MErrorObserver*    aErrorObserver, /* = NULL */
                              MProgressObserver* aProgressObserver /* = NULL */ )
{
   iPort = aPort;
   iAddress.SetPort( aPort );
   iAddress.SetAddress( aAddr );
   iErrorObserver = aErrorObserver;
   iProgressObserver = aProgressObserver;
   iSocket.Connect( iAddress, iStatus );
   iServerStatus = EConnecting;
   
   if ( iProgressObserver != NULL )
   {
      iProgressObserver->NotifyProgress( TProgressInfoTypes::EConnecting );                                                  
   }  
   
   SetActive();
   
   if ( aTimeout > 0 && !iTimer->IsActive() )
   {
      iTimer->After( aTimeout ); 
   }
}



void CSocketServer::ConnectResolvedL( TUint32 aAddr, TUint16 aPort )
{
   iPort = aPort;
   iAddress.SetPort( aPort );
   iAddress.SetAddress( aAddr );
   iSocket.Connect( iAddress, iStatus );
   iServerStatus = EConnecting;
   
   if ( iProgressObserver != NULL )
   {
      iProgressObserver->NotifyProgress( TProgressInfoTypes::EConnecting );
   }  
   
   SetActive();
}



void CSocketServer::ConnectL( const TDesC&       aServerName,
                              TUint16            aPort,
                              TUint              aTimeout, /* = 0 */
                              MErrorObserver*    aErrorObserver, /* = NULL */
                              MProgressObserver* aProgressObserver /* = NULL */)
{
   iPort = aPort;
   iErrorObserver = aErrorObserver;
   iProgressObserver = aProgressObserver;
   // Initiate DNS
   User::LeaveIfError( iResolver.Open( iSocketServ, KAfInet, KProtocolInetUdp ) );
   // DNS request for name resolution
   iResolver.GetByName( aServerName, iNameEntry, iStatus );
   
   iServerStatus = ELookingUp;
   
   if ( iProgressObserver != NULL )
   {
      iProgressObserver->NotifyProgress( TProgressInfoTypes::EResolvingServerName );
   }  
   
   // Request time out
   if ( aTimeout > 0 && !iTimer->IsActive() )
   {
      iTimer->After( aTimeout );
   }
   SetActive();
}



TBool CSocketServer::IsConnected() const
{
   return ( iServerStatus == EConnected );
}



CSocketReceiver* CSocketServer::GetSocketReceiver()
{
   return iReceiver;
}



const CSocketReceiver* CSocketServer::GetSocketReceiver() const
{
   return iReceiver;
}



CSocketTransmitter* CSocketServer::GetSocketTransmitter()
{
   return iTransmitter;
}



const CSocketTransmitter* CSocketServer::GetSocketTransmitter() const
{
   return iTransmitter;
}



RSocketServ& CSocketServer::GetSocketServInstance()
{
   return iSocketServ;
}



const RSocketServ& CSocketServer::GetSocketServInstance() const
{
   return iSocketServ;
}



void CSocketServer::Close()
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
   
   iSocket.Close();
   iSocketServ.Close();
   iServerStatus = EIdle;
}



void CSocketServer::RunL()
{
   TBuf < 15 > ipAddr;

   switch( iServerStatus )
   {
      case EConnecting:
      {
          // IP connection request
          if ( iStatus == KErrNone )
          // Connection completed sucessfully
          {                    
             if ( iErrorObserver != NULL )
             {
                iErrorObserver->NotifyError( TErrorObserverErrorTypes::EErrorInfo,
                                             TErrorObserverInfoTypes::ESuccessful );                                                  
             }  
             iServerStatus = EConnected;
             // CancelCurrentAction TimeOut timer before completion
             iTimer->Cancel(); 
          }
          else
          {
             iServerStatus = EConnectFailed;

             if ( iErrorObserver != NULL )
             {
                iErrorObserver->NotifyError( TErrorObserverErrorTypes::EErrorCritical,
                                             TErrorObserverInfoTypes::EConnectionFailed );
             }
             // CancelCurrentAction TimeOut timer before completion
             iTimer->Cancel(); 
          }
          break;
      }
      case ETimedOut:
      {
          // Timeout request
         if ( iErrorObserver != NULL )
         {
            iErrorObserver->NotifyError( TErrorObserverErrorTypes::EErrorCritical,
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
             
             // And connect to the IP address
             ConnectResolvedL( TInetAddr::Cast( iNameRecord.iAddr ).Address(), iPort );
           }
          else
          {   
             iStatus = ELookUpFailed;
             if ( iErrorObserver != NULL )
             {
                iErrorObserver->NotifyError( TErrorObserverErrorTypes::EErrorCritical,
                                             TErrorObserverInfoTypes::EDNSFailure );
             }
             // CancelCurrentAction TimeOut timer before completion
             iTimer->Cancel(); 
          }
          break;
      }
      default:;
   };
}



void CSocketServer::DoCancel()
{
   iTimer->Cancel();

   // CancelCurrentAction appropriate request to socket
   switch ( iServerStatus )
   {
      case EConnecting:
      {
         iSocket.CancelConnect();
         break;
      }         
      case ELookingUp:
      {
         // CancelCurrentAction look up attempt
         iResolver.Cancel();
         iResolver.Close();
         break;
      }         
      default:
      {
         break;
      }
   }
   
   iServerStatus = EIdle;
   
   if ( iErrorObserver != NULL )
   {
      iErrorObserver->NotifyError( TErrorObserverErrorTypes::EErrorWarning,
                                   TErrorObserverInfoTypes::ECanceled );
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

