/*
* ==============================================================================
*  Name        : DCQappview.cpp
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
#include "DCQAppView.h"


// ========================= MEMBER FUNCTIONS ==================================

// -----------------------------------------------------------------------------
// CDCQAppView::CDCQAppView()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CDCQAppView::CDCQAppView()
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// CDCQAppView::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CDCQAppView* CDCQAppView::NewL( const TRect& aRect )
    {
    CDCQAppView* self = CDCQAppView::NewLC( aRect );
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CDCQAppView::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CDCQAppView* CDCQAppView::NewLC( const TRect& aRect )
    {
    CDCQAppView* self = new ( ELeave ) CDCQAppView;
    CleanupStack::PushL( self );
    self->ConstructL( aRect );
    return self;
    }

// -----------------------------------------------------------------------------
// CDCQAppUi::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CDCQAppView::ConstructL( const TRect& aRect )
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect( aRect );

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

// -----------------------------------------------------------------------------
// CDCQAppView::~CDCQAppView()
// Destructor.
// -----------------------------------------------------------------------------
//
CDCQAppView::~CDCQAppView()
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// CDCQAppView::Draw() const
// Draws the display
// -----------------------------------------------------------------------------
//
void CDCQAppView::Draw( const TRect& /*aRect*/ ) const
    {
    // Clear the screen
    CWindowGc& gc = SystemGc();
    gc.Clear( Rect() );
    }

// End of File
