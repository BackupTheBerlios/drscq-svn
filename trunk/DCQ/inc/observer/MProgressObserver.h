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

struct TProgressTypes
{
   enum TTypes
   {
      EProgressGauge = 0,
      EProgressWait,
   };  
};

typedef TProgressTypes::TTypes TProgressType;

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
      
      virtual void NotifyProgress( TProgressType aProgressType, TUint8 aPercentage = 0 ) = 0;     
};


#endif /*MPROGRESSOBSERVER_H*/
