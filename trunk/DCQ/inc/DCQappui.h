/*
* ==============================================================================
*  Name        : DCQappui.h
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


#ifndef __DCQ_APPUI_H__
#define __DCQ_APPUI_H__


// INCLUDES
#include <aknViewAppUi.h>


// FORWARD DECLARATIONS
class CDCQLoginView;
class CDCQView2;


// CLASS DECLARATION

/**
* CDCQAppUi application UI class.
* An instance of class CDCQAppUi is the UserInterface part of the AVKON
* application framework for the DCQ example application
*/
class CDCQAppUi : public CAknViewAppUi
    {

    public: // Constructors and destructor

        /**
        * ConstructL.
        * 2nd phase constructor.
        */
        void ConstructL();

    public: // New functions from CEikAppUi

        /**
        * HandleCommandL
        * Takes care of command handling.
        * @param aCommand Command to be handled.
        */
        void HandleCommandL( TInt aCommand );
        
        /**
        * HandleResourceChangeL()
        * Called by framework when layout is changed.
        * @param aType The type of resources that have changed.
        */
        virtual void HandleResourceChangeL( TInt aType );
        
    private: // Data

        /**
        * iLoginView, The application login view
        * Not owned by CDCQAppUi object.
        */
        CDCQLoginView* iLoginView;
    };


#endif // __DCQ_APPUI_H__

// End of File
