/*
 ============================================================================
 Name        : SocketObserver.cpp
 Author      : Ronny R�hricht
 Version     :
 Copyright   : (C) Ronny R�hricht 2007
 Description : MSocketObserver declaration
 ============================================================================
 */

#include "connection/SocketObserver.h"
#include "DCQ.rls"

void TSocketObserverErrorCodes::ToString( TErrorCode aErrorCode, TDes& aString ) const
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
      default :
      {
         aString = STRING_r_mult_SocketObserver_Unknown;
         break;
      }
   }
}