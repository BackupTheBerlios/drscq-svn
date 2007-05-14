/*
* ==============================================================================
*  Name        : DCQappview.h
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


#ifndef __DCQ_APPVIEW_H__
#define __DCQ_APPVIEW_H__


// INCLUDES
#include <coecntrl.h>



// CLASS DECLARATION

/**
* CDCQAppView container control class.
* An instance of the Application View object for the
* example application DCQ
*/
class CDCQAppView : public CCoeControl
    {
public:     // Constructors and destructor

        /**
        * NewL.
        * Two-phased constructor.
        * Create a CDCQAppView object, which will draw itself to aRect-
        * @param aRect the rectangle this view will be drawn to.
        * @result a pointer to the created instance of CDCQAppView
        */
        static CDCQAppView* NewL( const TRect& aRect );

        /**
        * NewLC.
        * Two-phased constructor.
        * Create a CDCQAppView object, which will draw itself to aRect-
        * @param aRect the rectangle this view will be drawn to.
        * @result a pointer to the created instance of CDCQAppView
        */
        static CDCQAppView* NewLC( const TRect& aRect );

        /**
        * ~CDCQAppView
        * Virtual Destructor.
        */
        virtual ~CDCQAppView();

public:  // from CCoeControl

        /**
        * Draw
        * Draw this CDCQAppView to the screen.
        * @param aRect the rectangle of this view that needs updating
        */
        void Draw( const TRect& aRect ) const;

private: // Constructors and destructor

        /**
        * ConstructL
        * 2nd phase constructor.
        * @param aRect the rectangle this view will be drawn to.
        */
        void ConstructL( const TRect& aRect );

        /**
        * CDCQAppView.
        * C++ default constructor.
        */
        CDCQAppView();
    };

#endif // __DCQ_APPVIEW_H__
