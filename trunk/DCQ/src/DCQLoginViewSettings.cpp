/*
 ============================================================================
 Name		: DCQLoginViewSettings.cpp
 Author	  : Ronny Röhricht
 Version	 :
 Copyright   : (C) Ronny Röhricht 2007
 Description : CCDCQLoginViewSettings implementation
 ============================================================================
 */

#include "DCQLoginViewSettings.h"
#include "DCQ.rsg"

// ========================= MEMBER FUNCTIONS ==================================

void CDCQLoginViewSettings::ConstructL()
{
   CAknSettingItemList::ConstructFromResourceL( R_DCQ_LOGIN_VIEW_SETTINGS);
}

CAknSettingItem* CDCQLoginViewSettings::CreateSettingItemL( TInt aIdentifier)
{
   CAknSettingItem* settingItem=  NULL;
   
   switch (aIdentifier)
   {
      case EDCQLoginViewSettingICQNumber:
      {
         settingItem =new (ELeave) CAknTextSettingItem(aIdentifier, iICQNumber);
         break;
      }
      case EDCQLoginViewSettingICQPassword:
      {
         settingItem =new (ELeave) CAknPasswordSettingItem(aIdentifier, 
                                                           CAknPasswordSettingItem::EAlpha,
                                                           iICQPassword);        
         break;
      }
      case EDCQLoginViewSettingRememberPass:
      {
         settingItem =new (ELeave) CAknBinaryPopupSettingItem(aIdentifier, iFlag);
         break;
      }
      default: return NULL;     
   }
   
   return settingItem;
}

CDCQLoginViewSettings::~CDCQLoginViewSettings()
{
   // No implementation required
}

// End of File
