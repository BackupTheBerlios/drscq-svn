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

#include "DCQ1.rls"

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
     ECanceled,      
     EConnecting,
     EConnectionFailed,
     EDNSFailure,           
  };
  
  static void ToString( TInfoTypes aInfoCode, TDes& aString )
  {
     switch( aInfoCode )
     {         
        case ESuccessful :
        {
          aString = STRING_r_mult_SocketObserver_Successful;
           break;
        }
        case ETimeOut :
        {
           aString = STRING_r_mult_SocketObserver_Timeout;
           break;           
        }
        case EErrorGeneric :
        {
           aString = STRING_r_mult_SocketObserver_Generic;
           break;
        }
        case ECanceled :
        {
           aString = STRING_r_mult_SocketObserver_Canceled;
           break;
        }
        case EConnecting :
        {
           aString = STRING_r_mult_SocketObserver_Connecting;
           break;
        }
        case EConnectionFailed :
        {
           aString = STRING_r_mult_SocketObserver_Connection_Failed;
           break;
        }
        case EDNSFailure :
        {
           aString = STRING_r_mult_SocketObserver_DNS_Failure;
           break;
        }
        default :
        {
           aString = STRING_r_mult_SocketObserver_Unknown;
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
      
      virtual void NotifyError( TErrorObserverErrorType aErrorType, TErrorObserverInfoType aInfoType ) = 0;     
};

#endif /*MERROROBSERVER_H_*/
