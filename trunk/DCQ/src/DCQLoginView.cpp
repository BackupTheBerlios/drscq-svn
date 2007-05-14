/*
 * ==============================================================================
 *  Name        : DCQLoginView.cpp
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

#include "DCQLoginView.h"
#include "DCQLoginViewContainer.h"
#include "DCQLoginViewSettings.h"
#include "DCQ.hrh"

// ========================= MEMBER FUNCTIONS ==================================

CDCQLoginView::CDCQLoginView()
{  
}


CDCQLoginView* CDCQLoginView::NewL()
{
   CDCQLoginView* self = CDCQLoginView::NewLC();
   CleanupStack::Pop( self);
   return self;
}


CDCQLoginView* CDCQLoginView::NewLC()
{
   CDCQLoginView* self = new ( ELeave ) CDCQLoginView();
   CleanupStack::PushL( self);
   self->ConstructL();
   return self;
}



void CDCQLoginView::ConstructL()
{
   BaseConstructL( R_DCQ_LOGIN_VIEW );
}


// -----------------------------------------------------------------------------
// CDCQLoginView::~CDCQLoginView()
// Destructor.
// -----------------------------------------------------------------------------
//
CDCQLoginView::~CDCQLoginView()
{
   // No implementation required  
}


// -----------------------------------------------------------------------------
// CDCQLoginView::Id()
// Returns View's ID.
// -----------------------------------------------------------------------------
//
TUid CDCQLoginView::Id() const
{
   return TUid::Uid( EDCQLoginViewId);
}



void CDCQLoginView::DoActivateL( const TVwsViewId& /*aPrevViewId*/,
                             TUid /*aCustomMessageId*/, const TDesC8& /*aCustomMessage*/)
 {
    if (iContainer == NULL)
    {
       iContainer = CDCQLoginViewContainer::NewL( ClientRect());
    }
    
    if (iSettings == NULL)
    {
       iSettings = new (ELeave) CDCQLoginViewSettings;
       iSettings->SetMopParent( this );
       iSettings->ConstructL();
       AppUi()->AddToStackL(iSettings);
       iSettings->MakeVisible(ETrue);
       iSettings->SetRect(ClientRect());
       iSettings->ActivateL();
    }
 }



void CDCQLoginView::DoDeactivate()
{
   if ( iContainer)
   {
      AppUi()->RemoveFromStack( iContainer);
      delete iContainer;
      iContainer = NULL;
   }
   
   if(iSettings)
   {
      AppUi()->RemoveFromStack( iSettings);
      delete iSettings;
      iSettings = NULL;
   }
}


void CDCQLoginView::HandleCommandL( TInt aCommand)
{  
   AppUi()->HandleCommandL( aCommand );
}



void CDCQLoginView::HandleSizeChange( TInt aType)
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
