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
#include <aknstaticnotedialog.h> 

#include "DCQ.hrh"
#include "FileIO.h"
#include "DCQLoginView.h"
#include "DCQLoginViewSettings.h"
#include "DCQdocument.h"

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
   // Try to find the given command in list of valid commands
   switch( aCommand )
   {
      case EDCQLoginViewDoLogin :
      {            
         break;
      }
      case EDCQLoginViewNewAccount :
      {
         break;
      }
      case EDCQLoginViewSettings :
      {
         break;
      }
      case EDCQCommonAbout :
      { 
         // retrieve document...
         CDCQDocument * iDoc = static_cast < CDCQDocument * > ( AppUi()->Document() );                 
         
         // ...check, if document is not NULL
         if ( iDoc != NULL )
         {
            // ... if not, query currrently available protocols
            CDesCArrayFlat * protocols = new ( ELeave ) CDesCArrayFlat( 10 );
            CleanupStack::PushL( protocols );
            
            if ( iDoc->EnumeratePossibleProtocolsL( *protocols ) )
            {
               CAknStaticNoteDialog* dlg = new ( ELeave ) CAknStaticNoteDialog;
               dlg->PrepareLC( R_DCQ_INFO_STATIC_NOTIFICATION );
               dlg->SetNumberOfBorders( 4 );
               dlg->SetTextNumberL( protocols->Count() );
               dlg->RunLD();
            }
            
            CleanupStack::Pop( protocols );
         }
         else
         {            
            ASSERT( 0 );
         }
         
         
         break;
      }
      case EAknSoftkeyExit :
      {
         // Exit will be handled by AppUi
         AppUi()->HandleCommandL( aCommand );
         break;         
      }
      default:
      {
         // If nothing found, we do nothing
         break;
      }
   }
  
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
