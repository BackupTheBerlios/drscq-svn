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
  iWaitDialog( NULL ),
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
  
  iWaitDialog = NULL;
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
            ASSERT( iWaitDialog == NULL );
            iWaitDialog = new (ELeave) CAknWaitDialog ( REINTERPRET_CAST ( CEikDialog**, &iWaitDialog ), ETrue );
            iWaitDialog->SetCallback( this );            
            iWaitDialog->ExecuteLD ( R_DCQ_WAIT_NOTE_CONNECTING );
            
            iICQClient->ConnectL( _L("www.google.de"), 80 );                       
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
   
   if ( iWaitDialog != NULL )
   {
      iWaitDialog->SetCallback( NULL );
      iWaitDialog->ProcessFinishedL();
      iWaitDialog = NULL;
   }
}


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
   
   if ( iWaitDialog != NULL )
   {
      iWaitDialog->SetCallback( NULL );
      TRAP_IGNORE( iWaitDialog->ProcessFinishedL() );
      iWaitDialog = NULL;
   }
   
   bool aMustNotify = ( aInfoType != TErrorObserverInfoTypes::ESuccessful );
   
   if ( aMustNotify )
   {
      TBuf < 255 > buffer;
      TErrorObserverInfoTypes::ToString( aInfoType, static_cast < TDes& > ( buffer ) );
      
      switch ( aErrorType )
      {
         case TErrorObserverErrorTypes::EErrorCritical :
         {
            CAknStaticNoteDialog* dlg = new ( ELeave ) CAknStaticNoteDialog;
            
            // ...and prepare infos...
            CleanupStack::PushL( dlg );
            dlg->PrepareLC( R_DCQ_NOTE_ERROR_CRITICAL );
            dlg->SetNumberOfBorders( 4 );
            dlg->SetTextL( buffer );
            CleanupStack::Pop( dlg );
            
            // ...and run dialog...
            // dialog will delete itself after closing
            dlg->RunLD();
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
