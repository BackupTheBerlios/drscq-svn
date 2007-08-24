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

// ========================= MEMBER FUNCTIONS ==================================

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
   AddViewL( iLoginView );
   SetDefaultViewL( *iLoginView );
   
   iSocketServer = CSocketServer::NewL( iLoginView );   
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
         iSocketServer->OpenL();
         iSocketServer->ConnectL( _L("www.google.de"), 80 );
         break;
      }
      case EEikCmdExit:
      case EAknSoftkeyExit:
      {
         iSocketServer->Close();
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


void CDCQAppUi::Notify( const TDesC8& /* aReadData */ )
{

}

void CDCQAppUi::NotifyError( TSocketObserverErrorCode aErrCode )
{
   CAknStaticNoteDialog* dlg = new ( ELeave ) CAknStaticNoteDialog;
   
   // ...and prepare infos...
   CleanupStack::PushL( dlg );
   dlg->PrepareLC( R_DCQ_SERVEROBSERVER_STATIC_NOTIFICATION );
   dlg->SetNumberOfBorders( 4 );   
   TBuf < 255 > buffer;
   TSocketObserverErrorCodes::ToString( aErrCode, static_cast < TDes& > ( buffer ) );
   dlg->SetTextL( buffer );
   CleanupStack::Pop( dlg );
   
   // ...and run dialog...
   // dialog will delete itself after closing
   dlg->RunLD();
}
// End of File
