/*
 * ==============================================================================
 *  Name        : DCQappui.cpp
 *  Part of     : DCQ
 *  Interface   :
 *  Description :
 *  Version     :
 *
 Copyright (c) 2004 - 2006 Nokia Corporation.
 *  This material, including documentation and any related
 *  computer programs, is protected by copyright controlled by
 *  Nokia Corporation.
 * ==============================================================================
 */

// INCLUDE FILES
#include <e32std.h>
#include <DCQ.rsg>
#include <aknstaticnotedialog.h> 

#include "DCQ.hrh"
#include "DCQ.pan"
#include "DCQAppUi.h"
#include "DCQLoginView.h"

#include "connection/CSocketServer.h"
#include "clients/CICQClient.h"

// ========================= MEMBER FUNCTIONS ==================================
CDCQAppUi::CDCQAppUi()
: iLoginView( NULL ),
  iICQClient( NULL ),
  iWaitNoteWrapper( NULL ),
  iIdle( true )
{ 
}

CDCQAppUi::~CDCQAppUi()
{  
  if ( iICQClient != NULL )
  {
     iICQClient->Shutdown();
  }
  delete iICQClient;
  iICQClient = NULL;
  
  delete iWaitNoteWrapper;
  iWaitNoteWrapper = NULL;
}

// -----------------------------------------------------------------------------
// CDCQAppUi::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CDCQAppUi::ConstructL()
{
   // Initialise app UI
   BaseConstructL( EAknEnableSkin );
   
   iLoginView = CDCQLoginView::NewL();
   CleanupStack::PushL( iLoginView );
   
   AddViewL( iLoginView );
   SetDefaultViewL( *iLoginView );
   
   iICQClient = CICQClient::NewL();
   iICQClient->RegisterErrorObsrerver( this );
   
   CleanupStack::Pop( iLoginView );   
}

// -----------------------------------------------------------------------------
// CDCQAppUi::HandleCommandL()
// Takes care of command handling.
// -----------------------------------------------------------------------------
//
void CDCQAppUi::HandleCommandL( TInt aCommand )
{
   switch ( aCommand )
   {
      case EDCQLoginViewDoLogin :
      {   
         if ( iICQClient != NULL )
         {
            iICQClient->ConnectL( _L("www.google.de"), 80 );
            
            ASSERT( iWaitNoteWrapper == NULL );
            iWaitNoteWrapper = CAknWaitNoteWrapper::NewL();
            iWaitNoteWrapper->ExecuteL( R_DCQ_WAIT_NOTE_CONNECTING, *this );
         }
         break;
      }
      case EEikCmdExit:
      case EAknSoftkeyExit:
      {
         Exit();
         break;
      }         
      default:
      {
         break;
      }
         
   }
}

// -----------------------------------------------------------------------------
// CDCQAppUi::HandleResourceChangeL()
// Called by framework when layout is changed.
// -----------------------------------------------------------------------------
//
void CDCQAppUi::HandleResourceChangeL( TInt aType )
{
   CAknAppUi::HandleResourceChangeL( aType );
   
   if ( aType == KEikDynamicLayoutVariantSwitch )
   {
      iLoginView->HandleSizeChange( aType );
   }
}


void CDCQAppUi::DialogDismissedL( TInt /* aButton */ )
{
   if ( iICQClient != NULL )
   {
      iICQClient->Cancel();
   }
}


TBool CDCQAppUi::IsProcessDone() const
{
   return iIdle;
}

void CDCQAppUi::ProcessFinished()
{
   delete iWaitNoteWrapper;
   iWaitNoteWrapper = NULL;
   iIdle = true;
}

void CDCQAppUi::StepL(){}


void CDCQAppUi::NotifyProgress( TProgressType aProgressType, TUint8 /* aPercentage */ )
{
   ASSERT( iIdle );
   switch ( aProgressType )
   {
      case TProgressTypes::EProgressGauge :
      {
         break;
      }
      case TProgressTypes::EProgressWait :
      {
         break;
      }
      default : break;
   }
}

void CDCQAppUi::NotifyError( TErrorObserverErrorType aErrorType, TErrorObserverInfoType aInfoType )
{
   ASSERT( iIdle );
   
   bool aMustNotify = ( aInfoType != TErrorObserverInfoTypes::ESuccessful );
   
   if ( aMustNotify )
   {
      TBuf < 255 > buffer;
      TErrorObserverInfoTypes::ToString( aInfoType, static_cast < TDes& > ( buffer ) );
      
      switch ( aErrorType )
      {
         case TErrorObserverErrorTypes::EErrorCritical :
         {
            break;
         }
         case TErrorObserverErrorTypes::EErrorWarning :
         {
            break;
         }
         case TErrorObserverErrorTypes::EErrorInfo :
         {
            break;
         }
         case TErrorObserverErrorTypes::EErrorDebug :
         {
            break;
         }
         default : break;
      }
   }
   
   iIdle = true;   
}
// End of File
