/*
 ============================================================================
 Name		: CSocketServer.cpp
 Author	  : Ronny R�hricht
 Version	 :
 Copyright   : (C) Ronny R�hricht 2007
 Description : CSocketServer implementation
 ============================================================================
 */

#include "connection/CSocketServer.h"
#include "connection/CSocketReceiver.h"
#include "connection/CSocketTransmitter.h"

#include "observer/MSocketObserver.h"
#include "observer/MErrorObserver.h"
#include "observer/MProgressObserver.h"

#define NOTIFY_ERROR(a,b)    if(iErrorObserver!=NULL)iErrorObserver->NotifyError(a,b)
#define NOTIFY_PROGRESS(a)   if(iProgressObserver!=NULL)iProgressObserver->NotifyProgress(a)

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
   Close();
   
   iErrorObserver = NULL;
   iProgressObserver = NULL;
}



void CSocketServer::InitL()
{
   // Open a TCP socket
   User::LeaveIfError( iSocket.Open( iSocketServ, KAfInet, KSockStream, KProtocolInetTcp ) );      
}



void CSocketServer::ConnectL( TUint32            aAddr,
                              TUint16            aPort,
                              TUint              aTimeout, /* = 0 */
                              MErrorObserver*    aErrorObserver, /* = NULL */
                              MProgressObserver* aProgressObserver /* = NULL */ )
{
   iPort             = aPort;  
   iErrorObserver    = aErrorObserver;
   iProgressObserver = aProgressObserver;
   iServerStatus     = EConnecting;
   
   iAddress.SetPort( aPort );
   iAddress.SetAddress( aAddr );   
   iSocket.Connect( iAddress, iStatus );
   
   NOTIFY_PROGRESS( TProgressInfoTypes::EConnecting );
   
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
   
   NOTIFY_PROGRESS( TProgressInfoTypes::EConnecting );
   
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
   
   NOTIFY_PROGRESS( TProgressInfoTypes::EResolvingServerName );
   
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
      delete iTransmitter;
      iTransmitter = NULL;
   }
   if ( iReceiver != NULL )
   {
      iReceiver->Cancel();
      delete iReceiver;
      iReceiver = NULL;
   }
   if ( iTimer != NULL )
   {
      iTimer->Cancel();
      delete iTimer;
      iTimer = NULL;
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
             NOTIFY_ERROR( TErrorObserverErrorTypes::EErrorInfo,
                           TErrorObserverInfoTypes::ESuccessful );
                          
             // CancelCurrentAction TimeOut timer before completion
             iTimer->Cancel(); 
             
             // create new receiver/transmitter for the new connection
             iReceiver     = CSocketReceiver::NewL( &iSocket );
             iTransmitter  = CSocketTransmitter::NewL( &iSocket );
             iServerStatus = EConnected;
          }
          else
          {  
             NOTIFY_ERROR( TErrorObserverErrorTypes::EErrorCritical,
                           TErrorObserverInfoTypes::EConnectionFailed );
            
             // CancelCurrentAction TimeOut timer before completion
             iTimer->Cancel();              
             iServerStatus = EIdle;
          }
          break;
      }
      case ETimedOut:
      {
         // Timeout request
         NOTIFY_ERROR( TErrorObserverErrorTypes::EErrorCritical,
                       TErrorObserverInfoTypes::ETimeOut );
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
             NOTIFY_ERROR( TErrorObserverErrorTypes::EErrorCritical,
                           TErrorObserverInfoTypes::EDNSFailure );
             
             // CancelCurrentAction TimeOut timer before completion
             iTimer->Cancel(); 
             
             iStatus = EIdle;
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
   
   NOTIFY_ERROR( TErrorObserverErrorTypes::EErrorWarning,
                 TErrorObserverInfoTypes::ECanceled );   
}



void CSocketServer::TimerExpired()
{
   Cancel();
   iServerStatus = ETimedOut;
   TRequestStatus* p = &iStatus;     
   SetActive();
   User::RequestComplete( p, ETimedOut );
}

