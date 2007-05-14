/*
* ==============================================================================
*  Name        : DCQcontainer2.h
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



#ifndef __DCQ_CONTAINER2_H__
#define __DCQ_CONTAINER2_H__


// INCLUDES
#include <aknview.h>



// CLASS DECLARATION

/**
* CDCQContainer2 container control class.
* An instance of CDCQContainer2 contains the view drawn to the screen
* for CDCQView2
*/
class CDCQContainer2 : public CCoeControl
    {
    public:  // Constructors and destructor

        /**
        * NewL.
        * Two-phased constructor.
        * Create a CDCQContainer2 object, which will draw itself to aRect.
        * @param aRect The rectangle this view will be drawn to.
        * @return a pointer to the created instance of CDCQLoginViewContainer.
        */
        static CDCQContainer2* NewL( const TRect& aRect );

        /**
        * NewLC.
        * Two-phased constructor.
        * Create a CDCQContainer2 object, which will draw itself to aRect.
        * @param aRect The rectangle this view will be drawn to.
        * @return a pointer to the created instance of CDCQContainer2.
        */
        static CDCQContainer2* NewLC( const TRect& aRect );

        /**
        * ConstructL
        * 2nd phase constructor.
        * @param aRect Frame rectangle for container.
        */
        void ConstructL( const TRect& aRect );

    public: // from CoeControl

        /**
        * CountComponentControls
        * @return number of controls inside this container.
        */
        TInt CountComponentControls() const;

        /**
        * ComponentControl
        * @param Index number of the control.
        * @return Pointer of controls inside this container.
        */
        CCoeControl* ComponentControl( TInt aIndex ) const;

        /**
        * Draw
        * Draw this CDCQLoginViewContainer to the screen.
        * @param aRect the rectangle of this view that needs updating
        */
        void Draw( const TRect& aRect ) const;

    };

#endif // __DCQ_CONTAINER2_H__

// End of File
    