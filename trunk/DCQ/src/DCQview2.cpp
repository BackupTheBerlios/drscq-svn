/*
 * ==============================================================================
 *  Name        : DCQview2.cpp
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
#include <aknviewappui.h>
#include <aknconsts.h>
#include <aknnotewrappers.h>
#include <DCQ.rsg>
#include <stringloader.h>

#include "DCQView2.h"
#include "DCQContainer2.h"
#include "DCQ.hrh"

// ========================= MEMBER FUNCTIONS ==================================

// -----------------------------------------------------------------------------
// CDCQView2::CDCQView2()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CDCQView2::CDCQView2()
{
   // No implementation required
}

// -----------------------------------------------------------------------------
// CDCQView2::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CDCQView2* CDCQView2::NewL()
{
   CDCQView2* self = CDCQView2::NewLC();
   CleanupStack::Pop( self);
   return self;
}

// -----------------------------------------------------------------------------
// CDCQView2::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CDCQView2* CDCQView2::NewLC()
{
   CDCQView2* self = new ( ELeave ) CDCQView2();
   CleanupStack::PushL( self);
   self->ConstructL();
   return self;
}

// -----------------------------------------------------------------------------
// CDCQView2::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CDCQView2::ConstructL()
{
   BaseConstructL( R_DCQ_VIEW2);
}

// -----------------------------------------------------------------------------
// CDCQView2::~CDCQView2()
// Destructor.
// -----------------------------------------------------------------------------
//
CDCQView2::~CDCQView2()
{
   // No implementation required
}

// -----------------------------------------------------------------------------
// CDCQView2::Id()
// Returns View's ID.
// -----------------------------------------------------------------------------
//
TUid CDCQView2::Id() const
{
   return TUid::Uid( EDCQView2Id);
}

// -----------------------------------------------------------------------------
// CDCQView2::DoActivateL()
// Activate an MultiView2
// -----------------------------------------------------------------------------
//
void CDCQView2::DoActivateL( const TVwsViewId& /*aPrevViewId*/,
                            TUid /*aCustomMessageId*/, const TDesC8& /*aCustomMessage*/)
{
   iContainer = CDCQContainer2::NewL( ClientRect());
}

// -----------------------------------------------------------------------------
// CDCQView2::DoDeactivate()
// DeActivate an MultiView2
// -----------------------------------------------------------------------------
//
void CDCQView2::DoDeactivate()
{
   if ( iContainer)
   {
      AppUi()->RemoveFromStack( iContainer);
      delete iContainer;
      iContainer = NULL;
   }
}

// -----------------------------------------------------------------------------
// CDCQView2::HandleCommandL()
// Takes care of Command handling.
// -----------------------------------------------------------------------------
//
void CDCQView2::HandleCommandL( TInt aCommand)
{
   //    if ( aCommand == EDCQCommand1 )
   //        {
   //         // Load a string from the resource file.
   //        HBufC* textResource = StringLoader::LoadLC(  R_MULT_COMMAND1_TEXT  );
   //        CAknInformationNote* informationNote = new ( ELeave ) CAknInformationNote;
   //        informationNote->ExecuteLD( *textResource );
   //
   //        // Pop HBuf from CleanUpStack and Destroy it.
   //        CleanupStack::PopAndDestroy(  textResource  );
   //
   //        }
   //    else if ( aCommand == EDCQSwitchToView1 )
   //        {
   //        AppUi()->ActivateLocalViewL( TUid::Uid( EDCQView1Id ) );
   //        }
   //    else
   //        {
   //        AppUi()->HandleCommandL( aCommand );
   //        }
   
   AppUi()->HandleCommandL( aCommand );
}

// -----------------------------------------------------------------------------
// CDCQView2::HandleSizeChange()
// Called by HandleResourceChangeL() from CDCQAppUi when layout is 
// changed.
// -----------------------------------------------------------------------------
//
void CDCQView2::HandleSizeChange( TInt aType)
{
   if ( iContainer)
   {
      iContainer->HandleResourceChange( aType);
      
      if ( aType==KEikDynamicLayoutVariantSwitch)
      {
         TRect rect;
         AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EMainPane, rect);
         iContainer->SetRect(rect);
      }
   }
}

// End of File
