/*
============================================================================
 Name		: CSocketReceiver.cpp
 Author	  : Ronny Röhricht
 Version	 :
 Copyright   : (C) Ronny Röhricht 2007
 Description : CCSocketReceiver implementation
============================================================================
*/
#include <in_sock.h>

#include "connection/CSocketReceiver.h"
#include "observer/MSocketObserver.h"

CSocketReceiver::CSocketReceiver() 
: CActive( EPriorityNormal ),
  iMultiByteBuffer( NULL ),
  iSingleByteBuffer(),
  iSocket( NULL ),
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
   CActiveScheduler::Add( this ); // Add to scheduler
}

CSocketReceiver::~CSocketReceiver()
{
   Cancel(); // Cancel any request, if outstanding
   
   delete iMultiByteBuffer;
   iMultiByteBuffer = NULL;
   
   delete iTimer;
   iTimer = NULL;
   
   if ( iSocket != NULL )
   {
      iSocket->Close();
   }
   iSocket = NULL;
   
   iReceiveState = EWaiting;
   iObserver = NULL;
}

bool CSocketReceiver::ReceiveL( MSocketObserver& aObserver,
                                TUint            aBlockUntil /* = 0 */,
                                TUint            aTimeout /* = 0 */)
{
   bool busy = ( IsActive() || ( iMultiByteBuffer != NULL ) || ( iReceiveState != EWaiting ) );
   
   bool ok = ( !busy && ( iSocket != NULL ) );
   
   if ( ok )
   {
      // register observer
      iObserver = &aObserver;
      
      // check if we should block until a special amount
      // of data has been received      
      if ( aBlockUntil > 0 )
      {
         // if so, resize byte buffer to the size of desired number
         // of bytes to read. To set the size of the heap buffer to
         // maximal aBlockUntil bytes, indicates the socket read function
         // it should not return until these amount have been read.
         ASSERT( iMultiByteBuffer == NULL );
         
         iMultiByteBuffer = HBufC8::NewMaxL( aBlockUntil ); 
         TPtr8 aMultiByteBufferDes = iMultiByteBuffer->Des();
         
         iSocket->Recv( static_cast < TDes8& > ( aMultiByteBufferDes ), 0, iStatus );               
      }
      else
      {
         // if not so, only read one byte
         iSocket->Recv( static_cast < TDes8& > ( iSingleByteBuffer ), 0, iStatus );
      }

      // start timeout timer, if requested
      if ( aTimeout > 0 )
      {
         iTimer->After( aTimeout );
      }
      
      SetActive();
      iReceiveState = EReceiving;
   }
   
   return ok;
}

void CSocketReceiver::RunL()
{
   ASSERT( iObserver != NULL );
   
   // determine the cause why this method has been called
   if ( iStatus == KErrNone )
   {
      // no error occured
      // handle successful scheduler run
      switch( iReceiveState )
      {
         // all required characters has been read from socket
         case EReceiving:
            {
               // notify observer with the read data
               if ( iObserver != NULL )
               {
                  // check which buffer has been filled
                  if ( iMultiByteBuffer != NULL )
                  {
                     //iObserver->Notify( static_cast < const TDesC8& > ( *iMultiByteBuffer ) );
                  }
                  else
                  {
                     //iObserver->Notify( static_cast < const TDesC8& > ( iSingleByteBuffer ) );
                  }
               }
               
               // Cancel TimeOut timer
               if ( iTimer != NULL )
               {
                  iTimer->Cancel(); 
               }             
               break;
            }            
         // Read attempt timed out
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
      // connection lost during read      
      // shut down reader
      Cancel();
      
      // notify observer
      if ( iObserver != NULL )
      {
         iObserver->NotifyError( TSocketObserverErrorCodes::EConnectionLost );
      }
   }
   else
   {
      // unknown cause
      // Error: pass it up to the observer
      
      // stop timeout timer
      if ( iTimer != NULL )
      {
         iTimer->Cancel();
      }
      
      if ( iObserver != NULL )
      {
         iObserver->NotifyError( TSocketObserverErrorCodes::EErrorGeneric );
      }
   }            
   
   // task has been completed, regardless of any error code
   // free byte buffer
   delete iMultiByteBuffer;
   iMultiByteBuffer = NULL;
   
   iReceiveState = EWaiting;  
}

void CSocketReceiver::DoCancel()
{
   // cancel writing to socket
   if ( iSocket != NULL )
   {
      iSocket->CancelRecv();
   }
   
   // stop timer
   if ( iTimer != NULL )
   {
      iTimer->Cancel();
   }
   
   // free byte buffer
   delete iMultiByteBuffer;
   iMultiByteBuffer = NULL;
   
   iReceiveState = EWaiting;
   
   // give cancel info to observer   
   if ( IsActive() && iObserver != NULL )
   {
      iObserver->NotifyError( TSocketObserverErrorCodes::ECanceled );
   }
}

void CSocketReceiver::TimerExpired()
{
   Cancel();
   iReceiveState = ETimedOut;
   TRequestStatus* p = &iStatus;
   SetActive();
   User::RequestComplete( p, ETimedOut );   
}
