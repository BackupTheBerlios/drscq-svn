/*
============================================================================
 Name		: CState.cpp
 Author	  : Ronny R�hricht
 Version	 :
 Copyright   : (C) Ronny R�hricht 2007
 Description : CState implementation
============================================================================
*/

#include "clients/framework/CState.h"

CState::CState() : CActive( EPriorityStandard )	// Standard priority
{
}

CState::~CState()
{
}