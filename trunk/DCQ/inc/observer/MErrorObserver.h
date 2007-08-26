/*
 ============================================================================
 Name        : MErrorObserver.h
 Author      : Ronny Röhricht
 Version     :
 Copyright   : (C) Ronny Röhricht 2007
 Description : MErrorObserver declaration
 ============================================================================
 */

#ifndef MERROROBSERVER_H_
#define MERROROBSERVER_H_

// INCLUDES
#include <e32cmn.h>

#include "DCQ.rls"

struct TErrorObserverErrorTypes
{
   enum TErrorTypes
   {
      EErrorCritical = 0,
      EErrorWarning,
      EErrorInfo,
      EErrorDebug
   };
};

typedef TErrorObserverErrorTypes::TErrorTypes TErrorObserverErrorType;

struct TErrorObserverInfoTypes
{
  enum TInfoTypes
  {
     ESuccessful = 0,
     ETimeOut,
     EErrorGeneric,
     EErrorUnknown,
     ECanceled,      
     EConnectionFailed,
     EConnectionAlreadyExists,
     EDNSFailure,           
  };
  
  static void ToString( TInfoTypes aInfoCode, TDes& aString )
  {
     switch( aInfoCode )
     {         
        case ESuccessful :
        {
          aString = STRING_r_mult_ErrorObserver_Successful;
           break;
        }
        case ETimeOut :
        {
           aString = STRING_r_mult_ErrorObserver_Timeout;
           break;           
        }
        case EErrorGeneric :
        {
           aString = STRING_r_mult_ErrorObserver_Generic;
           break;
        }
        case EErrorUnknown :
        {
           aString = STRING_r_mult_ErrorObserver_Unknown;
           break;
        }
        case ECanceled :
        {
           aString = STRING_r_mult_ErrorObserver_Canceled;
           break;
        }
        case EConnectionFailed :
        {
           aString = STRING_r_mult_ErrorObserver_Connection_Failed;
           break;
        }
        case EConnectionAlreadyExists :
        {
           aString = STRING_r_mult_ErrorObserver_Connection_Already_Exists;
           break;
        }
        case EDNSFailure :
        {
           aString = STRING_r_mult_ErrorObserver_DNS_Failure;
           break;
        }
        default :
        {
           aString = STRING_r_mult_ErrorObserver_Unknown;
           break;
        }
     }
  }
  
};

typedef TErrorObserverInfoTypes::TInfoTypes TErrorObserverInfoType;

// CLASS DECLARATION

/**
 *  MProgressObserver
 * 
 */
class MErrorObserver
{
   public:
    
      /**
       * Destructor.
       */
      virtual ~MErrorObserver(){}
      
      virtual void NotifyError( TErrorObserverErrorType aErrorType, 
                                TErrorObserverInfoType  aInfoType,
                                TInt                    aErrorCode = 0 ) = 0;
};

#endif /*MERROROBSERVER_H_*/
