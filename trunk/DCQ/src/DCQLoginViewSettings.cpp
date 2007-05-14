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
#include "DCQ.hrh"
#include "DCQ.rsg"

// ========================= MEMBER FUNCTIONS ==================================

void CDCQLoginViewSettings::ConstructL()
{
   CAknSettingItemList::ConstructFromResourceL( R_DCQ_LOGIN_VIEW_SETTINGS );
}

CAknSettingItem* CDCQLoginViewSettings::CreateSettingItemL( TInt aIdentifier )
{
   CAknSettingItem* settingItem = NULL;

   switch (aIdentifier)
       {
       case EDCQLoginViewSettingRememberPass:
           settingItem = 
               new (ELeave) CAknBinaryPopupSettingItem(aIdentifier, iFlag);
           break;
       }

   return settingItem;
}


CDCQLoginViewSettings::~CDCQLoginViewSettings()
{
   // No implementation required
}


// End of File
