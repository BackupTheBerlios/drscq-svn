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

#include "observer/MProgressObserver.h"
#include "observer/MErrorObserver.h"

#include "protocols/OSCARv7v8v9/OSCARProtocol.h"


CICQClient::CICQClient()
: iProgressObserver( NULL ),
  iErrorObserver( NULL ),
  iConnection(),
  iProtocol( NULL ),
  iConnectionPrefs()
{
}



CICQClient::~CICQClient()
{
   iProgressObserver = NULL;
   iErrorObserver = NULL;
   
   CancelCurrentAction();
   Shutdown();
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
   iProtocol = Protocol::COSCARProtocol::NewL();
   CleanupStack::PushL( iProtocol );
   iProtocol->OpenL();
   CleanupStack::Pop( iProtocol );
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
   if ( iProtocol != NULL )
   {
      iProtocol->Cancel();
   }
}



void CICQClient::Shutdown()
{
   if ( IsConnected() )
   {
      iConnection.Close();
   }
   
   iConnectionPrefs = TCommDbConnPref();
   
   if ( iProtocol != NULL )
   {
      iProtocol->Close();
      delete iProtocol;
      iProtocol = NULL;   
   }
}
