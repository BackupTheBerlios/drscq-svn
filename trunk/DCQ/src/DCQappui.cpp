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

#include "DCQ.pan"
#include "DCQAppUi.h"
#include "DCQLoginView.h"
#include "DCQView2.h"

// ========================= MEMBER FUNCTIONS ==================================

// -----------------------------------------------------------------------------
// CDCQAppUi::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CDCQAppUi::ConstructL()
{
   // Initialise app UI
   BaseConstructL(EAknEnableSkin);
   
   iLoginView = CDCQLoginView::NewL();
   iAppView2 = CDCQView2::NewL();
   AddViewL(iLoginView);
   AddViewL(iAppView2);
   SetDefaultViewL( *iLoginView );
   
}

// -----------------------------------------------------------------------------
// CDCQAppUi::HandleCommandL()
// Takes care of command handling.
// -----------------------------------------------------------------------------
//
void CDCQAppUi::HandleCommandL( TInt aCommand)
{
   switch ( aCommand)
   {
      case EEikCmdExit:
      case EAknSoftkeyExit:
         Exit();
         break;
      default:
         Panic( EDCQBasicUi);
         break;
   }
}

// -----------------------------------------------------------------------------
// CDCQAppUi::HandleResourceChangeL()
// Called by framework when layout is changed.
// -----------------------------------------------------------------------------
//
void CDCQAppUi::HandleResourceChangeL( TInt aType)
{
   CAknAppUi::HandleResourceChangeL( aType);
   
   if ( aType == KEikDynamicLayoutVariantSwitch)
   {
      iLoginView->HandleSizeChange(aType);
      //        iAppView2->HandleSizeChange(aType);
   }
}

// End of File
