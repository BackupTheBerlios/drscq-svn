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
#include "connection/CSocketReceiver.h"
#include "connection/CSocketTransmitter.h"


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

