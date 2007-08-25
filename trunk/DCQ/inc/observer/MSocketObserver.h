/*
 ============================================================================
 Name		    : MSocketObserver.h
 Author	    : Ronny Röhricht
 Version	    :
 Copyright   : (C) Ronny Röhricht 2007
 Description : MSocketObserver declaration
 ============================================================================
 */

#ifndef MSOCKETOBSERVER_H
#define MSOCKETOBSERVER_H

// INCLUDES
#include <e32cmn.h>

struct TSocketObserverErrorCodes
{
   enum TErrorCode
   {
      EErrorNone = 0,
      ETimeOut,
      EErrorGeneric,
      ECanceled,      
      EConnectionLost,                
   };
};

typedef TSocketObserverErrorCodes::TErrorCode TSocketObserverErrorCode;
// CLASS DECLARATION

/**
 *  MSocketObserver
 * 
 */
class MSocketObserver
{
   public:
      // Constructors and destructor

      /**
       * Destructor.
       */
      virtual ~MSocketObserver(){}
      
      virtual void NotifySuccess() = 0;
      
      virtual void NotifyError( TSocketObserverErrorCode aErrCode ) = 0;
};

#endif // MSOCKETOBSERVER_H

