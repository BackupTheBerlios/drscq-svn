/*
* ==============================================================================
*  Name        : DCQapplication.cpp
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
#include "DCQDocument.h"
#include "DCQApplication.h"


// ========================= MEMBER FUNCTIONS ==================================

// -----------------------------------------------------------------------------
// CDCQApplication::CreateDocumentL()
// Create an DCQ document, and return a pointer to it
// -----------------------------------------------------------------------------
//
CApaDocument* CDCQApplication::CreateDocumentL()
    {
    return( static_cast< CApaDocument* >( CDCQDocument::NewL( *this ) ) );
    }

// -----------------------------------------------------------------------------
// CDCQApplication::AppDllUid()
// Returns application UID
// -----------------------------------------------------------------------------
//
TUid CDCQApplication::AppDllUid() const
    {
    return KUidDCQApp;
    }

// End of File
