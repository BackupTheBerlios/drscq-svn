#include <S32FILE.H>
#include <f32file.h>


#include "FileIO.h"
#include "DCQ.hrh"
#include "DCQSaveableSettingItemList.h"

TFileIO::~TFileIO()
{
}

TFileIO::TFileIO()
{
}

void TFileIO::LoadSettingsFromFileL(const CEikonEnv& aEikonEnv,
                                    const TFileName& aFilename,
                                    CDCQSaveableSettingItemList& aTarget)
{
   TFileName aCompleteName = CreateCompleteFileNameL(aEikonEnv, aFilename);
   
   RFs& fs=  aEikonEnv.FsSession();
   RFileReadStream readStream;
   TInt error = readStream.Open(fs, aCompleteName, EFileRead);
   TInt internalizationError = KErrNone;
   // if file existed, try to read settings.
   if (error == KErrNone)
   {
      TRAP(internalizationError, aTarget.InternalizeSettingsDataL(readStream);)
   }
   readStream.Release();
   
   // reading failed, settings file might be corrupted.    
   if (internalizationError != KErrNone)
   {
      User::LeaveIfError(fs.Delete(aCompleteName));
   }
}

void TFileIO::SaveSettingsToFileL(const CEikonEnv& aEikonEnv,
                                  const TFileName& aFilename,
                                  const CDCQSaveableSettingItemList& aSource)
{
   TFileName aCompleteName = CreateCompleteFileNameL(aEikonEnv, aFilename);
   
   RFs& fs=  aEikonEnv.FsSession();
   RFileWriteStream writeStream;
   TInt error = writeStream.Open(fs, aCompleteName, EFileWrite);
   // setting file did not exist, create one.
   if (error != KErrNone)
   {
      User::LeaveIfError(writeStream.Create(fs, aCompleteName, EFileWrite));
   }
   aSource.ExternalizeSettingsDataL(writeStream);
   writeStream.CommitL();
   writeStream.Release();
   
}

TFileName TFileIO::CreateCompleteFileNameL(const CEikonEnv& aEikonEnv,
                                           const TFileName& aRawFileName)
{
   TFileName aCompleteName;
   
   RFs& fsSession=  aEikonEnv.FsSession();
   
#ifdef __SERIES60_3X__
   User::LeaveIfError(fsSession.CreatePrivatePath( EDriveC ) );
   User::LeaveIfError(fsSession.PrivatePath(aCompleteName));
   aCompleteName += aRawFileName;
#else
   TFileName appFullName = Application()->AppFullName();
   TParsePtr appPath(appFullName);
#ifdef __WINS__
   aCompleteName = _L("c:");
   iSettingsFile.Append(appPath.Path());
   fsSession.MkDir(aCompleteName);
#else
   aCompleteName = appPath.DriveAndPath();
#endif // __WINS__

   aCompleteName.Append(aRawFileName);
#endif // __SERIES60_3x__   

   return aCompleteName;
}

