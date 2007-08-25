/*
 ============================================================================
 Name		    : MTimeOutObserver.h
 Author	    : Ronny Röhricht
 Version	    :
 Copyright   : (C) Ronny Röhricht 2007
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
