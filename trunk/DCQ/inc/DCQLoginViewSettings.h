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
#include <aknsettingitemlist.h>
#include "DCQ.hrh"

// CLASS DECLARATION

/**
 *  CDCQLoginViewSettings
 * 
 */
class CDCQLoginViewSettings : public CAknSettingItemList
{
   public:
      // Constructors and destructor

      void ConstructL();

      CAknSettingItem* CreateSettingItemL( TInt aIdentifier);

      /**
       * ~CDCQLoginView.
       * Virtual Destructor.
       */
      virtual ~CDCQLoginViewSettings();

   private:
      // Data
      TBuf <KMaxICQNumberLength>    iICQNumber;
      TBuf <KMaxICQPasswordLength>  iICQPassword;
      TBool iFlag;

};

#endif // CDCQLOGINVIEWSETTINGS_H

