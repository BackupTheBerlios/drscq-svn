/*
* ==============================================================================
*  Name        : DCQ.cpp
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
#include <eikstart.h>
 
#include "DCQApplication.h"


// ========================== OTHER EXPORTED FUNCTIONS =========================

// -----------------------------------------------------------------------------
// NewApplication()
// Constructs CAknExMenuApp.
// Create an application, and return a pointer to it
// -----------------------------------------------------------------------------
EXPORT_C CApaApplication* NewApplication()
    {
      CApaApplication * pNewApp = static_cast<CApaApplication*> ( new CDCQApplication );
      return pNewApp;
    }

// -----------------------------------------------------------------------------
// E32Main()
// Entry point function for Symbian Apps.
// -----------------------------------------------------------------------------
//  
GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication( NewApplication );
    }
    
// End of File
