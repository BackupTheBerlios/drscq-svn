/*
============================================================================
 Name		: CState.cpp
 Author	  : Ronny Röhricht
 Version	 :
 Copyright   : (C) Ronny Röhricht 2007
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