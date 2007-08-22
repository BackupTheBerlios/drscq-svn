/*
============================================================================
 Name		: CSocketTransmitter.cpp
 Author	  : Ronny Röhricht
 Version	 :
 Copyright   : (C) Ronny Röhricht 2007
 Description : CSocketTransmitter implementation
============================================================================
*/
#include <in_sock.h>

#include "connection/CSocketTransmitter.h"
#include "connection/SocketObserver.h"

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
   bool busy = ( ( iByteBuffer != NULL ) || ( iTransmitStatus != EWaiting ) || IsActive() );
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
               // Cancel TimeOut timer
               if ( iTimer != NULL )
               {
                  iTimer->Cancel(); 
               }             
               break;
            }
         // Request timed out
         case ETimedOut:
            {
               if ( iObserver != NULL )
               {
                  iObserver->NotifyError( TSocketObserverErrorCodes::ETimeOut );
               }
               break;
            }
         default: break;
      };
   }
   else if ( iStatus == KErrEof )
   {
      // connection lost during write
      // shut down writer
      Cancel();
      
      // notify observer
      if ( iObserver != NULL )
      {
         iObserver->NotifyError( TSocketObserverErrorCodes::EConnectionLost );
      }
   }
   else 
   {
      // stop timeout timer
      if ( iTimer != NULL )
      {
         iTimer->Cancel();
      }
      
      // Error: pass it up to the observer
      if ( iObserver != NULL )
      {
         iObserver->NotifyError( TSocketObserverErrorCodes::EErrorGeneric );
      }
   }
   
   // task has been completed, regardless of any error code
   // free byte buffer
   delete iByteBuffer;
   iByteBuffer = NULL;
   
   iTransmitStatus = EWaiting;
}

void CSocketTransmitter::DoCancel()
{
   // cancel writing to socket
   if ( iSocket != NULL )
   {
      iSocket->CancelWrite();
   }
   
   // stop timer
   if ( iTimer != NULL )
   {
      iTimer->Cancel();
   }
   
   // free byte buffer
   delete iByteBuffer;
   iByteBuffer = NULL;
   
   iTransmitStatus = EWaiting;
   
   // give cancel info to observer   
   if ( IsActive() && iObserver != NULL )
   {
      iObserver->NotifyError( TSocketObserverErrorCodes::ECanceled );
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