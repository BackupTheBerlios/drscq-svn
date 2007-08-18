/*
* ==============================================================================
*  Name        : DCQview2.h
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


#ifndef __DCQ_VIEW2_H__
#define __DCQ_VIEW2_H__


// INCLUDES
#include <aknview.h>



// FORWARD DECLARATIONS
class CDCQContainer2;

// CLASS DECLARATION

/**
* CDCQView2 view class.
* An instance of the Application View object for the DCQ
* example application
*/
class CDCQView2: public CAknView
    {
    public:    // Constructors and destructor

        /**
        * NewL.
        * Two-phased constructor.
        * Construct a CDCQView2 for the AVKON application aApp.
        * Using two phase construction,and return a pointer to the created object.
        * @return a pointer to the created instance of CDCQView2
        */
        static CDCQView2* NewL();

        /**
        * NewLC.
        * Two-phased constructor.
        * Construct a CDCQView2 for the AVKON application aApp.
        * Using two phase construction,and return a pointer to the created object.
        * @return a pointer to the created instance of CDCQView2
        */
        static CDCQView2* NewLC();

        /**
        * ~CDCQView2.
        * Virtual Destructor.
        */
        virtual ~CDCQView2();


    public:// Functions from base classes from CAknView

        /**
        * Id
        * From CAknView, return Uid.
        * @return Uid Uid value
        */
        TUid Id() const;

        /**
        * HandleCommandL
        * From CAknView, takes care of command handling.
        * @param aCommand Command to be handled
        */
        void HandleCommandL( TInt aCommand );

        /**
        * DoActivateL
        * From CAknExView, activate an AknView.
        * @param aPrevViewId The id of the previous view
        * @param aCustomMessageId message identifier
        * @param aCustomMessage custom message provided when the view is changed
        */
        void DoActivateL( const TVwsViewId& aPrevViewId,
                          TUid aCustomMessageId,
                          const TDesC8& aCustomMessage );

        /**
        * DoDeactivate
        * From AknView, deactivate an AknView
        * Remove the container class instance from the App UI's stack and
        * deletes the instance
        */
        void DoDeactivate();
        
        /**
        * HandleSizeChange
        * Called by HandleResourceChangeL() from CDCQAppUi when layout 
        * is changed.
        * @param aType Type of resources that have changed
        */
        void HandleSizeChange( TInt aType );

    private:    // Constructors and destructor

        /**
        * CDCQView2.
        * C++ default constructor.
        */
        CDCQView2();

        /**
        * ConstructL.
        * 2nd phase constructor.
        */
        void ConstructL();

    private:    // Data

        /**
        * iContainer,container for this view
        * owned by CDCQView2 object.
        */
        CDCQContainer2* iContainer;

        /** View Identifier **/
        TUid       iIdentifier;
       };


#endif // __DCQ_VIEW2_H__


// End of File
