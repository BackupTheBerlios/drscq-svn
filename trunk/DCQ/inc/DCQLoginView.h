/*
 * ==============================================================================
 *  Name        : DCQLoginview.h
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

#ifndef __DCQ_LOGINVIEW_H__
#define __DCQ_LOGINVIEW_H__

// INCLUDES
#include <aknview.h>

// FORWARD DECLARATIONS
class CDCQLoginViewContainer;
class CDCQLoginViewSettings;

// CLASS DECLARATION

/**
 * CDCQLoginView view class.
 * An instance of the Application View object for the DCQ
 * example application
 */
class CDCQLoginView : public CAknView
{
   public:
      // Constructors and destructor

      static CDCQLoginView * NewL();
      
      static CDCQLoginView * NewLC();

      /**
       * ~CDCQLoginView.
       * Virtual Destructor.
       */
      virtual ~CDCQLoginView();

   public:
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

   private:
      
      CDCQLoginView();
      
      /**
       * ConstructL.
       * 2nd phase constructor.
       */
       void ConstructL();

   private:
      // Data
      CDCQLoginViewContainer * iContainer;
      
      CDCQLoginViewSettings * iSettings;

      /** View Identifier **/
      TUid iIdentifier;      
};

#endif // __DCQ_LOGINVIEW_H__


// End of File
