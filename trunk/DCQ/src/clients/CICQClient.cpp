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
#include "connection/CSocketServer.h"
#include "protocols/OSCARv7v8v9/OSCARProtocol.h"

static const TUint TIMEOUT_CONNECT_MS = 10000000; // 10 sec

CICQClient::CICQClient()
: iProgressObserver( NULL ),
  iErrorObserver( NULL ),
  iSocketServer( NULL ),
  iProtocol( NULL )
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
   
   iSocketServer = CSocketServer::NewL();
   CleanupStack::PushL( iSocketServer );
   iSocketServer->OpenL();
   
   CleanupStack::Pop( iSocketServer );
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

void CICQClient::ConnectL( TUint32 aAddr, TUint16 aPort )
{
   iSocketServer->ConnectL( aAddr, aPort, TIMEOUT_CONNECT_MS, iErrorObserver );
}

void CICQClient::ConnectL( const TDesC& aServerName, TUint16 aPort )
{
   iSocketServer->ConnectL( aServerName, aPort, TIMEOUT_CONNECT_MS, iErrorObserver );
}

bool CICQClient::IsConnected() const
{
   return iSocketServer->IsConnected();
}

void CICQClient::Cancel()
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

void CICQClient::Shutdown()
{
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
}






