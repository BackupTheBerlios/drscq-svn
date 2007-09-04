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
: iIAPPreferences(),
  iLoginView( NULL ),
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
   iICQClient->RegisterProgressObserver( this );
   
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



void CDCQAppUi::SelectIAP()
{
   iIAPPreferences.SetDirection( ECommDbConnectionDirectionOutgoing );
   iIAPPreferences.SetDialogPreference( ECommDbDialogPrefPrompt );
   iIAPPreferences.SetIapId( 0 );
   iIAPPreferences.SetBearerSet( 0 );
}



void CDCQAppUi::DialogDismissedL( TInt /* aButton */ )
{
   if ( iICQClient != NULL )
   {
      iICQClient->CancelCurrentAction();
   }
   
   if ( iWaitDialog != NULL )
   {
      iWaitDialog->SetCallback( NULL );
      iWaitDialog->ProcessFinishedL();
      iWaitDialog = NULL;
   }
}


void CDCQAppUi::NotifyProgress( TProgressInfoType aProgressType, TUint8 /* aPercentage */ )
{
   ASSERT( !iIdle );
   
   TBuf < 255 > buffer;
   TProgressInfoTypes::ToString( aProgressType, static_cast < TDes& > ( buffer ) );
   
   switch ( aProgressType )
   {
      case TProgressInfoTypes::EOpeningConnection :
      {
         ASSERT( iWaitDialog == NULL );
         iWaitDialog = new ( ELeave ) CAknWaitDialog ( REINTERPRET_CAST ( CEikDialog**, &iWaitDialog ), ETrue );
         iWaitDialog->SetCallback( this );
         TRAP_IGNORE( iWaitDialog->SetTextL( buffer ) );
         
         TInt trapCode;
         TRAP( trapCode, iWaitDialog->ExecuteLD ( R_DCQ_COMMON_WAIT_NOTE ) );
         
         if ( trapCode != KErrNone )
         {
            delete iWaitDialog;
            iWaitDialog = NULL;
         }
         
         break;
      }
      default:
      {
         if ( iWaitDialog != NULL )
         {
            iWaitDialog->SetTextL( buffer );
         }         
         break;
      }   
   }   
}


void CDCQAppUi::NotifyError( TErrorObserverErrorType aErrorType, 
                             TErrorObserverInfoType  aInfoType,
                             TInt                    aErrorCode )
{
   ASSERT( !iIdle );
   
   if ( iWaitDialog != NULL )
   {
      iWaitDialog->SetCallback( NULL );
      TRAP_IGNORE( iWaitDialog->ProcessFinishedL() );
      iWaitDialog = NULL;
   }
   
   bool aMustNotifyUser = ( aInfoType != TErrorObserverInfoTypes::ESuccessful );
   
   if ( aMustNotifyUser )
   {
      TBuf < 255 > buffer;
      TErrorObserverInfoTypes::ToString( aInfoType, static_cast < TDes& > ( buffer ) );
            
      if ( aErrorCode != 0 )
      {
         buffer.Append( _L(" (") );
         buffer.AppendNum( aErrorCode );
         buffer.Append( _L(")") );
      }

      
      CAknStaticNoteDialog* dlg = new ( ELeave ) CAknStaticNoteDialog;
      CleanupStack::PushL( dlg );
      
      switch ( aErrorType )
      {
         case TErrorObserverErrorTypes::EErrorCritical :
         {                               
            dlg->PrepareLC( R_DCQ_NOTE_ERROR_CRITICAL );
            break;
         }
         case TErrorObserverErrorTypes::EErrorWarning :
         {
            dlg->PrepareLC( R_DCQ_NOTE_ERROR_CRITICAL );
            break;
         }
         case TErrorObserverErrorTypes::EErrorInfo :
         {
            dlg->PrepareLC( R_DCQ_NOTE_ERROR_CRITICAL );
            break;
         }
         case TErrorObserverErrorTypes::EErrorDebug :
         {
            dlg->PrepareLC( R_DCQ_NOTE_ERROR_CRITICAL );
            break;
         }
         default : break;
      }
      
      dlg->SetNumberOfBorders( 4 );
      dlg->SetTextL( buffer );
      CleanupStack::Pop( dlg );
      
      // ...and run dialog...
      // dialog will delete itself after closing
      dlg->RunLD();
   }
   
   iIdle = true;   
}
// End of File
