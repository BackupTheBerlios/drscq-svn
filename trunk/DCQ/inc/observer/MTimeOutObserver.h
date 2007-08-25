/*
 ============================================================================
 Name		    : MTimeOutObserver.h
 Author	    : Ronny R�hricht
 Version	    :
 Copyright   : (C) Ronny R�hricht 2007
 Description : MTimeOutObserver declaration
 ============================================================================
 */


#ifndef MTIMEOUTOBSERVER_H
#define MTIMEOUTOBSERVER_H

// MTimeOutObserver: used in conjunction with CTimeOutTimer class
class MTimeOutObserver
{
   public:
      virtual void TimerExpired() = 0;
};

#endif /*MTIMEOUTOBSERVER_H*/
