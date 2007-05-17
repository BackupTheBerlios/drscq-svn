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

#include "DCQ.hrh"
#include "FileIO.h"
#include "DCQLoginView.h"
#include "DCQLoginViewSettings.h"

// ========================= MEMBER FUNCTIONS ==================================

_LIT(KLoginViewSettingsFile, "LoginSet.dat");

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
   BaseConstructL( R_DCQ_LOGIN_VIEW);
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
   if (iLoginSettings == NULL)
   {
      iLoginSettings = new (ELeave) CDCQLoginViewSettings;
      TFileIO::LoadSettingsFromFileL(*iEikonEnv,
                                     TFileName(KLoginViewSettingsFile),
                                     *iLoginSettings);
      iLoginSettings->SetMopParent( this);
      iLoginSettings->ConstructL();
      AppUi()->AddToStackL(iLoginSettings);
      iLoginSettings->MakeVisible(ETrue);
      iLoginSettings->SetRect(ClientRect());
      iLoginSettings->ActivateL();
      iLoginSettings->LoadSettingsL();
   }
}

void CDCQLoginView::DoDeactivate()
{
   if (iLoginSettings != NULL)
   {
      TFileIO::SaveSettingsToFileL(*iEikonEnv,
                                   TFileName(KLoginViewSettingsFile),
                                   *iLoginSettings);
      AppUi()->RemoveFromStack( iLoginSettings);
      delete iLoginSettings;
      iLoginSettings = NULL;
   }
}

void CDCQLoginView::HandleCommandL( TInt aCommand)
{
   AppUi()->HandleCommandL( aCommand);
}

void CDCQLoginView::HandleSizeChange( TInt aType)
{  
   if (iLoginSettings)
   {
      if (aType==KEikDynamicLayoutVariantSwitch)
      {
         TRect rect;
         AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EMainPane, rect);
         iLoginSettings->SetRect(rect);
      }
   }
}

// End of File
