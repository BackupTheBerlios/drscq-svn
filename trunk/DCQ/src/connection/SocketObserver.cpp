/*
 ============================================================================
 Name        : SocketObserver.cpp
 Author      : Ronny Röhricht
 Version     :
 Copyright   : (C) Ronny Röhricht 2007
 Description : MSocketObserver declaration
 ============================================================================
 */

#include "connection/SocketObserver.h"
#include "DCQ.rls"

void TSocketObserverErrorCodes::ToString( TErrorCode aErrorCode, TDes& aString )
{
   switch( aErrorCode )
   {         
      case EErrorNone :
      {
         aString = STRING_r_mult_SocketObserver_ErrorNone;            
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
      case EConnectionLost :
      {
         aString = STRING_r_mult_SocketObserver_Connection_Lost;
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