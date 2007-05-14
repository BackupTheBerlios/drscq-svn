/*
* ==============================================================================
*  Name        : DCQapplication.h
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


#ifndef __DCQ_APPLICATION_H__
#define __DCQ_APPLICATION_H__


// INCLUDES
#include <aknapp.h>


// CONSTANTS
// Uid for the application, should match the one in the mmp file
const TUid KUidDCQApp = { 0xA00001FA };


// CLASS DECLARATION

/**
* An instance of CDCQApplication is the application part of the AVKON
* application framework for the DCQ example application
*/
class CDCQApplication : public CAknApplication
    {

    public:  // from CAknApplication

        /**
        * AppDllUid
        * @return returns application's UID (KUidAknExMenu).
        */
        TUid AppDllUid() const;


    protected: // from CAknApplication


        /**
        * CreateDocumentL
        * Creates CDCQDocument document object.
        * The returned pointer in not owned by the CDCQApplication object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();
    };

#endif // __DCQ_APPLICATION_H__

// End of File
