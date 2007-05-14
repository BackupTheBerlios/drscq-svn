/*
* ==============================================================================
*  Name        : DCQdocument.h
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


#ifndef __DCQ_DOCUMENT_H__
#define __DCQ_DOCUMENT_H__



// INCLUDES
#include <akndoc.h>


// FORWARD DECLARATIONS
class CDCQAppUi;
class CEikApplication;



// CLASS DECLARATION

/**
* CDCQDocument application class.
* An instance of class CDCQDocument is the Document part of the AVKON
* application framework for the CDCQApplication example application.
*/
class CDCQDocument : public CAknDocument
    {
    public:  // Constructors and destructor

        /**
        * NewL.
        * Two-phased constructor.
        * Construct a CDCQDocument for the AVKON application aApp.
        * Using two phase construction, and return a pointer to the created object.
        * @param aApp Application creating this document.
        * @return A pointer to the created instance of CDCQDocument.
        */
        static CDCQDocument* NewL( CEikApplication& aApp );

        /**
        * NewLC.
        * Two-phased constructor.
        * Construct a CDCQDocument for the AVKON application aApp.
        * Using two phase construction, and return a pointer to the created object.
        * @param aApp Application creating this document.
        * @return A pointer to the created instance of CDCQDocument.
        */
        static CDCQDocument* NewLC( CEikApplication& aApp );

        /**
        * ~CDCQDocument
        * Virtual Destructor.
        */
        virtual ~CDCQDocument();

    public: // from CAknDocument

        /**
        * CreateAppUiL
        * From CEikDocument, CreateAppUiL.
        * Create a CDCQAppUi object and return a pointer to it.
        * The object returned is owned by the Uikon framework.
        * @return Pointer to created instance of AppUi.
        */
        CEikAppUi* CreateAppUiL();

    private:  // Constructors

        /**
        * ConstructL
        * 2nd phase constructor.
        */
        void ConstructL();

        /**
        * CDCQDocument.
        * C++ default constructor.
        * @param aApp Reference to Application class object
        */
        CDCQDocument( CEikApplication& aApp );

    };


#endif // __DCQ_DOCUMENT_H__


// End of File
    