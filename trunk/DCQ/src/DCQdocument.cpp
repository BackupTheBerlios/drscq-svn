/*
* ==============================================================================
*  Name        : DCQdocument.cpp
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
#include "DCQAppUi.h"
#include "DCQDocument.h"


// ========================= MEMBER FUNCTIONS ==================================


// -----------------------------------------------------------------------------
// CDCQDocument::CDCQDocument()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CDCQDocument::CDCQDocument( CEikApplication& aApp ) 
   : CAknDocument( aApp )
    {
       // No implementation required
    }

// -----------------------------------------------------------------------------
// CDCQDocument::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CDCQDocument* CDCQDocument::NewL( CEikApplication& aApp )
    {
    CDCQDocument* self = NewLC( aApp );
    CleanupStack::Pop( self );
    return self;
    }


// -----------------------------------------------------------------------------
// CDCQDocument::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CDCQDocument* CDCQDocument::NewLC( CEikApplication& aApp )
    {
    CDCQDocument* self = new ( ELeave ) CDCQDocument( aApp );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// -----------------------------------------------------------------------------
// CDCQDocument::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CDCQDocument::ConstructL()
    {
      
    }

// -----------------------------------------------------------------------------
// CDCQDocument::~CDCQDocument()
// Destructor.
// -----------------------------------------------------------------------------
//
CDCQDocument::~CDCQDocument()
    {
     
    }

// -----------------------------------------------------------------------------
// CDCQDocument::CreateAppUiL()
// Create the application user interface, and return a pointer to it
// -----------------------------------------------------------------------------
//
CEikAppUi* CDCQDocument::CreateAppUiL()
    {
    return( static_cast<CEikAppUi*>( new ( ELeave ) CDCQAppUi ) );
    }

// End of File
