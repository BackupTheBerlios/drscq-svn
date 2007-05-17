#ifndef DCQSAVEABLESETTINGITEMLIST_H_
#define DCQSAVEABLESETTINGITEMLIST_H_

#include <aknsettingitemlist.h>

class RReadStream;
class RWriteStream;

class CDCQSaveableSettingItemList : public CAknSettingItemList
{
   public:
      
      virtual ~CDCQSaveableSettingItemList()
      {
      }
      
      virtual void ConstructL() = 0;

      virtual void InternalizeSettingsDataL( RReadStream& aStream) = 0;

      virtual void ExternalizeSettingsDataL( RWriteStream& aStream) const = 0;

      /**
       * Function:    SizeChanged
       *
       * Discussion:  Inherited from CCoeControl. Calculates size based on
       *           contained control required sizes.
       *
       */
      virtual void SizeChanged()
      {
         // if size changes, make sure component takes whole available space
         CEikFormattedCellListBox *listbox = ListBox();
         
         if (listbox)
         {
            listbox->SetRect(Rect());
         }
      }
      
      /**
       * Function:   EditCurrentItemL
       *
       * Discussion: Starts the setting page for the currently selected item 
       *          in the list.
       */
      virtual void EditCurrentItemL() = 0;

   protected:
      
      CDCQSaveableSettingItemList()
      {
      }
      
      /**
       * Function:    CreateSettingItemL
       *
       * Discussion:  Factory function for creating CAknSettingItem derived
       *           SettingItem classes used t display current values
       *
       * Params:      aSettingId - the id of the control which should be created
       *
       */
      virtual CAknSettingItem* CreateSettingItemL(TInt aSettingId) = 0;

      virtual void HandleListBoxEventL(CEikListBox * /*aListBox*/,
                                       TListBoxEvent aEventType) = 0;
};

#endif /*DCQSAVEABLESETTINGITEMLIST_H_*/
