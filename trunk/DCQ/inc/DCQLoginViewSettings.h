/*
 ============================================================================
 Name		: DCQLoginViewSettings.h
 Author	  : Ronny Röhricht
 Version	 :
 Copyright   : (C) Ronny Röhricht 2007
 Description : CCDCQLoginViewSettings declaration
 ============================================================================
 */

#ifndef CDCQLOGINVIEWSETTINGS_H
#define CDCQLOGINVIEWSETTINGS_H

// INCLUDES
#include "DCQSaveableSettingItemList.h"
#include "DCQ.hrh"

// CLASS DECLARATION

/**
 *  CDCQLoginViewSettings
 * 
 */
class CDCQLoginViewSettings : public CDCQSaveableSettingItemList
{
   public:
      // Constructors and destructor      
      
      CDCQLoginViewSettings();
      
      /**
       * ~CDCQLoginView.
       * Virtual Destructor.
       */
      virtual ~CDCQLoginViewSettings();

      void ConstructL();      
      
      void InternalizeSettingsDataL( RReadStream& aStream );
      
      void ExternalizeSettingsDataL( RWriteStream& aStream ) const;   
      
      /**
       * Function:   EditCurrentItemL
       *
       * Discussion: Starts the setting page for the currently selected item 
       *          in the list.
       */
      void EditCurrentItemL();     

   private:
      
      CAknSettingItem* CreateSettingItemL( TInt aIdentifier);
      
      void HandleListBoxEventL(CEikListBox * /*aListBox*/,
                                       TListBoxEvent aEventType);
      
      
      // Data
      TBuf <KMaxICQNumberLength>    iICQNumber;
      TBuf <KMaxICQPasswordLength>  iICQPassword;
      TBool                         iRememberPasswordFlag;

};

#endif // CDCQLOGINVIEWSETTINGS_H

