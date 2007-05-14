/*
* ==============================================================================
*  Name        : DCQ.pan
*  Part of     : DCQ
*  Interface   :
*  Description :
*  Version     :
*
*  Copyright (c) 2004-2006 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation.
* ==============================================================================
*/

#ifndef __DCQ_PAN__
#define __DCQ_PAN__


// DCQ application panic codes
enum TDCQPanics
    {
    EDCQBasicUi = 1
    // add further panics here
    };

inline void Panic( TDCQPanics aReason )
    {
    _LIT( applicationName,"DCQ" );
    User::Panic( applicationName, aReason );
    }

#endif // __DCQ_PAN__

// End of File
