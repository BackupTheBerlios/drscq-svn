#ifndef FILEIO_H_
#define FILEIO_H_

class CEikonEnv;
class CDCQSaveableSettingItemList;

class TFileIO
{
   public:
      ~TFileIO();

      static void LoadSettingsFromFileL(const CEikonEnv& aEikonEnv,
                                        const TFileName& aFilename,
                                        CDCQSaveableSettingItemList& aTarget);

      static void
            SaveSettingsToFileL(const CEikonEnv& aEikonEnv,
                                const TFileName& aFilename,
                                const CDCQSaveableSettingItemList& aSource);

   private:
      TFileIO();

      static TFileName CreateCompleteFileNameL(const CEikonEnv& aEikonEnv, const TFileName& aRawFileName);
};

#endif /*FILEIO_H_*/
