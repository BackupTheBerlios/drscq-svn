/*
 ============================================================================
 Name		: DCQLoginViewSettings.cpp
 Author	  : Ronny Röhricht
 Version	 :
 Copyright   : (C) Ronny Röhricht 2007
 Description : CCDCQLoginViewSettings implementation
 ============================================================================
 */

#include <S32STRM.H> // Streams

#include "DCQLoginViewSettings.h"
#include "DCQ.rsg"

// ========================= MEMBER FUNCTIONS ==================================

CDCQLoginViewSettings::CDCQLoginViewSettings() :
   CDCQSaveableSettingItemList(), iICQNumber( _L("")), iICQPassword( _L("")),
         iRememberPasswordFlag(EFalse)
{
}

CDCQLoginViewSettings::~CDCQLoginViewSettings()
{
   // No implementation required
}

void CDCQLoginViewSettings::ConstructL()
{
   CAknSettingItemList::ConstructFromResourceL( R_DCQ_LOGIN_VIEW_SETTINGS);
}

void CDCQLoginViewSettings::HandleListBoxEventL(CEikListBox* /*aListBox*/,
                                                TListBoxEvent aEventType)
{
   if (aEventType == EEventEnterKeyPressed)
   {
      EditCurrentItemL();
   }
}

void CDCQLoginViewSettings::EditCurrentItemL()
{
   TInt aCurrItemIdx = ListBox()->CurrentItemIndex();
   
   // invoke EditItemL on the current item
   EditItemL(aCurrItemIdx, // the item index
             EFalse); // not invoked from menu

   //Updating CAknPasswordSettingItem.
   if (aCurrItemIdx == EDCQLoginViewSettingICQPasswordOrder)
   {
      (*(SettingItemArray()))[aCurrItemIdx]->UpdateListBoxTextL();
   }
   
   StoreSettingsL();
}

CAknSettingItem* CDCQLoginViewSettings::CreateSettingItemL( TInt aIdentifier)
{
   CAknSettingItem* settingItem= NULL;
   
   switch (aIdentifier)
   {
      case EDCQLoginViewSettingICQNumberId:
      {
         settingItem =new (ELeave) CAknTextSettingItem(aIdentifier, iICQNumber);
         break;
      }
      case EDCQLoginViewSettingICQPasswordId:
      {
         settingItem =new (ELeave) CAknPasswordSettingItem(aIdentifier,
               CAknPasswordSettingItem::EAlpha,
               iICQPassword);
         break;
      }
      case EDCQLoginViewSettingRememberPassId:
      {
         settingItem =new (ELeave) CAknBinaryPopupSettingItem(aIdentifier, iRememberPasswordFlag);
         break;
      }
      default:
         return NULL;
   }
   
   return settingItem;
}

void CDCQLoginViewSettings::InternalizeSettingsDataL( RReadStream& aStream)
{
   aStream >> iICQNumber;
   aStream >> iICQPassword;
   iRememberPasswordFlag = aStream.ReadInt16L();
}

void CDCQLoginViewSettings::ExternalizeSettingsDataL( RWriteStream& aStream) const
{
   aStream << iICQNumber;
   
   if (iRememberPasswordFlag)
   {
      aStream << iICQPassword;
   } else
   {
      aStream << _L("");
   }
   
   aStream.WriteInt16L(iRememberPasswordFlag);
}

// End of File
