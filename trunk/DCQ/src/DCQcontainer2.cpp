/*
* ==============================================================================
*  Name        : DCQcontainer2.cpp
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
#include "DCQContainer2.h"


// ========================= MEMBER FUNCTIONS ==================================

// -----------------------------------------------------------------------------
// CDCQContainer2::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CDCQContainer2* CDCQContainer2::NewL( const TRect& aRect )
    {
    CDCQContainer2* self = CDCQContainer2::NewLC( aRect );
    CleanupStack::Pop( self );
    return self;
    }


// -----------------------------------------------------------------------------
// CDCQContainer2::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CDCQContainer2* CDCQContainer2::NewLC( const TRect& aRect )
    {
    CDCQContainer2* self = new ( ELeave ) CDCQContainer2;
    CleanupStack::PushL( self );
    self->ConstructL( aRect );
    return self;
    }

// -----------------------------------------------------------------------------
// CDCQContainer2::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CDCQContainer2::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }


// -----------------------------------------------------------------------------
// CDCQContainer2::CountComponentControls() const
// returns number of controls inside this container.
// -----------------------------------------------------------------------------
//
TInt CDCQContainer2::CountComponentControls() const
    {
    return 0;
    }

// -----------------------------------------------------------------------------
// CDCQContainer2::ComponentControl() const
// returns pointer of controls inside this container
// -----------------------------------------------------------------------------
//
CCoeControl* CDCQContainer2::ComponentControl( TInt /*aIndex*/ ) const
    {
    return NULL;
    }

// -----------------------------------------------------------------------------
// CDCQContainer2::Draw() const
// Draws the display
// -----------------------------------------------------------------------------
//
void CDCQContainer2::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbRed );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// End of File
