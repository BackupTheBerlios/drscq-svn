/*
============================================================================
 Name		: CICQClient.cpp
 Author	  : Ronny Röhricht
 Version	 :
 Copyright   : (C) Ronny Röhricht 2007
 Description : CICQClient implementation
============================================================================
*/
#include "clients/CICQClient.h"
#include "clients/OSCARConstants.h"

#include "connection/CSocketServer.h"

#include "observer/MProgressObserver.h"
#include "observer/MErrorObserver.h"


CICQClient::CICQClient()
: CActive( EPriorityNormal ),
  iClientStatus( EIdle ),
  iProgressObserver( NULL ),
  iErrorObserver( NULL ),
  iConnection(),
  iConnectionPrefs(),
  iSocketServer( NULL )
{
   SetConnectionPreferences( ECommDbBearerUnknown, ETrue );
}



CICQClient::~CICQClient()
{   
   CancelCurrentAction();
   Shutdown();
   
   iProgressObserver = NULL;
   iErrorObserver = NULL;
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
   // creates a new CSocketServer instance and connects to
   // the RSocketServ during construction.
   iSocketServer = CSocketServer::NewL();
}


TUint CICQClient::GetProtocolId()
{
   return static_cast < TUint > ( K_PROTOCOL_ID );
}

const TPtrC CICQClient::GetProtocolDescription()
{
   return TPtrC( K_PROTOCOL_DESC );
}


void CICQClient::RegisterProgressObserver( MProgressObserver* aProgressObserver )
{
   iProgressObserver = aProgressObserver;
}



void CICQClient::RegisterErrorObsrerver( MErrorObserver* aErrorObserer )
{
   iErrorObserver = aErrorObserer;
}



void CICQClient::SetConnectionPreferences( TUint   aBearer, 
                                           TBool   aShowDialog, 
                                           TUint32 aIapId /* = KUndefinedIAPid */ )
{
   iConnectionPrefs.SetDirection( ECommDbConnectionDirectionOutgoing );
   
   if ( aShowDialog )
   {
      iConnectionPrefs.SetDialogPreference( ECommDbDialogPrefPrompt );
   }
   else
   {
      iConnectionPrefs.SetDialogPreference( ECommDbDialogPrefDoNotPrompt );
   }
   
   iConnectionPrefs.SetIapId( aIapId );
   iConnectionPrefs.SetBearerSet( aBearer );
   iConnectionPrefs.SetDirection( ECommDbConnectionDirectionOutgoing );
}



TBool CICQClient::IsConnected() const
{
   // Check if there is an active connection
   TBool connected = EFalse;

   if ( iConnectionPrefs.IapId() != KUndefinedIAPid )
   {
      TUint connectionCount;
      //Enumerate currently active connections across all socket servers
      if ( iConnection.EnumerateConnections( connectionCount ) == KErrNone )
      {
         if ( connectionCount > 0 )
         {
            TPckgBuf < TConnectionInfoV2 > connectionInfo;
            
            for ( TUint i = 1; !connected && ( i <= connectionCount ); ++i )
            {
               iConnection.GetConnectionInfo( i, connectionInfo );
              
               if ( connectionInfo().iIapId == iConnectionPrefs.IapId() )
               {   
                  connected = ETrue;
               }
            }
         }
      }  
   }
   
   return connected;
}



RConnection& CICQClient::GetConnection()
{
   return iConnection;
}



const RConnection& CICQClient::GetConnection() const
{
   return iConnection;
}



TCommDbConnPref& CICQClient::GetConnectionPreferences()
{
   return iConnectionPrefs;
}



const TCommDbConnPref& CICQClient::GetConnectionPreferences() const
{
   return iConnectionPrefs;
}



void CICQClient::CancelCurrentAction()
{    
 
}



void CICQClient::Shutdown()
{
   iClientStatus = EShuttingDown;
   
   if ( IsConnected() )
   {
      iConnection.Close();
   }
   
   if ( iSocketServer != NULL )
   {
      iSocketServer->Close();
      delete iSocketServer;
      iSocketServer = NULL;
   }
   
   iConnectionPrefs = TCommDbConnPref();   
   
   iClientStatus = EIdle;
}



void CICQClient::RunL()
{
   switch( iClientStatus )
   {
      default : break;
   }
}



void CICQClient::DoCancel()
{
   
}
