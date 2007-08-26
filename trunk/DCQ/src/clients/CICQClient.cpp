/*
============================================================================
 Name		: CICQClient.cpp
 Author	  : Ronny Röhricht
 Version	 :
 Copyright   : (C) Ronny Röhricht 2007
 Description : CICQClient implementation
============================================================================
*/

#include <CommDbConnPref.h>

#include "clients/CICQClient.h"

#include "observer/MProgressObserver.h"
#include "observer/MErrorObserver.h"

#include "connection/CSocketServer.h"

#include "protocols/OSCARv7v8v9/OSCARProtocol.h"

static const TUint32 INVALID_ADDRESS       = 0;
static const TUint16 INVALID_PORT          = 0;
static const TUint   TIMEOUT_CONNECT_MS    = 10000000; // 10 sec

CICQClient::CICQClient()
: CActive( EPriorityStandard ),
  iClientStatus( EIdle ),
  iProgressObserver( NULL ),
  iErrorObserver( NULL ),
  iConnection(),
  iSocketServer( NULL ),
  iProtocol( NULL ),
  iAddr( INVALID_ADDRESS ),
  iPort( INVALID_PORT ),
  iName()
{
}


CICQClient::~CICQClient()
{
   iProgressObserver = NULL;
   iErrorObserver = NULL;
   
   if ( iSocketServer != NULL )
   {
      iSocketServer->Close();
   }
   delete iSocketServer;
   iSocketServer = NULL;
   
   if ( iProtocol != NULL )
   {
      iProtocol->Close();
   }
   delete iProtocol;
   iProtocol = NULL;
   
   iConnection.Close();
   iClientStatus = EIdle;
}

CICQClient* CICQClient::NewLC()
{
	CICQClient* self = new ( ELeave ) CICQClient();
	CleanupStack::PushL( self );
	self->ConstructL();
	return self;
}

CICQClient* CICQClient::NewL()
{
	CICQClient* self = CICQClient::NewLC();
	CleanupStack::Pop(); // self;
	return self;
}

void CICQClient::ConstructL()
{
   CActiveScheduler::Add( this );
}

void CICQClient::RegisterProgressObserver( MProgressObserver* aProgressObserver )
{
   iProgressObserver = aProgressObserver;
}



void CICQClient::RegisterErrorObsrerver( MErrorObserver* aErrorObserer )
{
   iErrorObserver = aErrorObserer;
}



void CICQClient::OpenL( TCommDbConnPref& aConPrefs )
{
   if ( iClientStatus == EIdle )
   {
      iClientStatus = EOpening;
      
      iProgressObserver->NotifyProgress( TProgressInfoTypes::EOpeningConnection );
      
      iProtocol = Protocol::COSCARProtocol::NewL();
      CleanupStack::PushL( iProtocol );
      iProtocol->OpenL();
      
      iSocketServer = CSocketServer::NewL();
      CleanupStack::PushL( iSocketServer );
      iSocketServer->OpenL();
      
      iConnection.Open( iSocketServer->GetSocketServInstance() );
      iConnection.Start( aConPrefs, iStatus );
      
      CleanupStack::Pop( iSocketServer );
      CleanupStack::Pop( iProtocol );      
   }   
}


void CICQClient::ConnectL( TUint32 aAddr, TUint16 aPort, TCommDbConnPref& aConPrefs )
{
   if ( ( iClientStatus == EIdle ) && ( aAddr != INVALID_ADDRESS ) && ( aPort != INVALID_PORT ) )
   {
      iAddr = aAddr;
      iPort = aPort;
      OpenL( aConPrefs );
      SetActive();
   }
   else if ( iErrorObserver != NULL )
   {
      iErrorObserver->NotifyError( TErrorObserverErrorTypes::EErrorWarning,
                                   TErrorObserverInfoTypes::EConnectionAlreadyExists );
   }
}



void CICQClient::ConnectL( const TDesC& aServerName, TUint16 aPort, TCommDbConnPref& aConPrefs )
{   
   if ( ( iClientStatus == EIdle ) && ( aServerName.Length() > 0 ) && ( aPort != INVALID_PORT ) )
   {
      iName.Copy( aServerName );
      iPort = aPort;
      OpenL( aConPrefs );     
      SetActive();
   }
   else if ( iErrorObserver != NULL )
   {
      iErrorObserver->NotifyError( TErrorObserverErrorTypes::EErrorWarning,
                                   TErrorObserverInfoTypes::EConnectionAlreadyExists );
   }
}



TBool CICQClient::IsConnected() const
{
   TBool aConnected = false;
   
   if ( iSocketServer != NULL )
   {
      aConnected = iSocketServer->IsConnected();
   }
   
   return aConnected;
}



void CICQClient::Cancel()
{    
   if ( iProgressObserver != NULL )
   {
      iProgressObserver->NotifyProgress( TProgressInfoTypes::ECancelingProgress );
   }
   
   if ( iClientStatus == EOpening )
   {
      iConnection.Close();
      iClientStatus = EIdle;
   }
   else
   {
      if ( iProtocol != NULL )
      {
         iProtocol->Cancel();
      }
      if ( iSocketServer != NULL )
      {
         iSocketServer->Cancel();
      }     
   }
}



void CICQClient::Shutdown()
{
   if ( IsConnected() )
   {
      iConnection.Close();
   }
   
   if ( iSocketServer != NULL )
   {
      iSocketServer->Close();
   }
   
   if ( iProtocol != NULL )
   {
      iProtocol->Close();
   }
   
   delete iSocketServer;
   iSocketServer = NULL;
   
   delete iProtocol;
   iProtocol = NULL;   
   
   iErrorObserver = NULL;
   iProgressObserver = NULL;
   
   iClientStatus = EIdle;
}



void CICQClient::RunL()
{ 
   TInt statusCode = iStatus.Int();
   
   /** NO ERROR **/
   if ( statusCode == KErrNone )
   {
      // Connection created succesfully
      iClientStatus = EOpen;
      
      if ( iAddr != INVALID_ADDRESS )
      {
         iSocketServer->ConnectL( iAddr, iPort, 
                                  TIMEOUT_CONNECT_MS, 
                                  iErrorObserver,
                                  iProgressObserver );
      }
      else
      {
         iSocketServer->ConnectL( iName, iPort, 
                                  TIMEOUT_CONNECT_MS, 
                                  iErrorObserver,
                                  iProgressObserver );
      }    
   } // end if
   
   /** CONNECTION ALREADY EXISTS **/
   else if ( statusCode == KErrAlreadyExists )
   {
      if ( iErrorObserver != NULL )
      {
         iErrorObserver->NotifyError( TErrorObserverErrorTypes::EErrorWarning,
                                      TErrorObserverInfoTypes::EConnectionAlreadyExists );
      }
      iClientStatus = EOpen;
   }
   
   /** ERROR OCCURED **/
   else
   {
      switch ( statusCode )
      {         
         case KErrNotFound: // Connection failed
         {
            if ( iErrorObserver != NULL )
            {
               iErrorObserver->NotifyError( TErrorObserverErrorTypes::EErrorCritical,
                                            TErrorObserverInfoTypes::EConnectionFailed,
                                            statusCode );
            }
            
            Shutdown();
            
            break;
         }
         case KErrCancel: // Connection attempt cancelled
         {
            if ( iErrorObserver != NULL )
            {
               iErrorObserver->NotifyError( TErrorObserverErrorTypes::EErrorWarning,
                                            TErrorObserverInfoTypes::ECanceled );
            }            
            
            break;
         }
         
         default:
         {
            if ( iErrorObserver != NULL )
            {
               iErrorObserver->NotifyError( TErrorObserverErrorTypes::EErrorCritical,
                                            TErrorObserverInfoTypes::EErrorUnknown,
                                            statusCode );
            }
            
            Shutdown();
            
            break;
         }
         
       } // end switch       
            
    } // end else
}



void CICQClient::DoCancel()
{
   
}


