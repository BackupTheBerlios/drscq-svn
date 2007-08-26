/*
 ============================================================================
 Name        : MProgressObserver.h
 Author      : Ronny Röhricht
 Version     :
 Copyright   : (C) Ronny Röhricht 2007
 Description : MProgressObserver declaration
 ============================================================================
 */

#ifndef MPROGRESSOBSERVER_H
#define MPROGRESSOBSERVER_H

// INCLUDES
#include <e32cmn.h>
#include "DCQ.rls"

struct TProgressInfoTypes
{
   enum TTypes
   {
      EOpeningConnection = 0,
      EConnecting,
      EResolvingServerName,
      ECancelingProgress
   };
   
   static void ToString( TTypes aInfoCode, TDes& aString )
   {
      switch ( aInfoCode )
      {
         case EOpeningConnection :
         {
            aString = STRING_r_mult_ProgressObserver_OpenConnection;
            break;
         }
         case EConnecting :
         {
            aString = STRING_r_mult_ProgressObserver_Connecting;
            break;
         }
         case EResolvingServerName :
         {
            aString = STRING_r_mult_ProgressObserver_DNS_Resolving;
            break;
         }
         case ECancelingProgress :
         {
            aString = STRING_r_mult_ProgressObserver_Canceling_Progress;
            break;
         }
         default : break;            
      }
   }
   
};

typedef TProgressInfoTypes::TTypes TProgressInfoType;

// CLASS DECLARATION

/**
 *  MProgressObserver
 * 
 */
class MProgressObserver
{
   public:
    
      /**
       * Destructor.
       */
      virtual ~MProgressObserver(){}
      
      virtual void NotifyProgress( TProgressInfoType aProgressInfo, TUint8 aPercentage = 0 ) = 0;     
};


#endif /*MPROGRESSOBSERVER_H*/
