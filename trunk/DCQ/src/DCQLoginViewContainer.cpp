/*
* ==============================================================================
*  Name        : DCQLoginViewContainer.cpp
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
#include "DCQLoginViewContainer.h"


// ========================= MEMBER FUNCTIONS ==================================


// -----------------------------------------------------------------------------
// CDCQLoginViewContainer::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CDCQLoginViewContainer* CDCQLoginViewContainer::NewL( const TRect& aRect )
    {
    CDCQLoginViewContainer* self = CDCQLoginViewContainer::NewLC( aRect );
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CDCQLoginViewContainer::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CDCQLoginViewContainer* CDCQLoginViewContainer::NewLC( const TRect& aRect )
    {
    CDCQLoginViewContainer* self = new ( ELeave ) CDCQLoginViewContainer;
    CleanupStack::PushL( self );
    self->ConstructL( aRect );
    return self;
    }

// -----------------------------------------------------------------------------
// CDCQLoginViewContainer::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CDCQLoginViewContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }

// -----------------------------------------------------------------------------
// CDCQLoginViewContainer::CountComponentControls() const
// returns number of controls inside this container.
// -----------------------------------------------------------------------------
//
TInt CDCQLoginViewContainer::CountComponentControls() const
    {
    return 0;
    }


// -----------------------------------------------------------------------------
// CDCQLoginViewContainer::ComponentControl() const
// returns pointer of controls inside this container
// -----------------------------------------------------------------------------
//
CCoeControl* CDCQLoginViewContainer::ComponentControl( TInt /*aIndex*/ ) const
    {
    return NULL;
    }

// -----------------------------------------------------------------------------
// CDCQLoginViewContainer::Draw() const
// Draws the display
// -----------------------------------------------------------------------------
//
void CDCQLoginViewContainer::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbBlue );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }
    

// End of File

