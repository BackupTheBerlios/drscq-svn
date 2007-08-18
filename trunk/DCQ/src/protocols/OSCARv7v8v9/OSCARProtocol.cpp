/********************************************************************
 created:	2007/08/15
 created:	15:8:2007   13:08
 file base:	OSCARProtocol
 file ext:	cpp
 author:		DrSoran
 
 purpose:	
 *********************************************************************/

#include "protocols/OSCARv7v8v9/OSCARProtocol.h"
#include "protocols/OSCARv7v8v9/OSCARConstants.h"

namespace Protocol {
   
      
   
   COSCARProtocol * COSCARProtocol::NewL()
   {
      COSCARProtocol * self = new (ELeave) COSCARProtocol();
      CleanupStack::PushL(self);
      self->ConstructL();
      CleanupStack::Pop();
      return self;
   }
   
   COSCARProtocol * COSCARProtocol::NewLC()
   {
      COSCARProtocol * self = new (ELeave) COSCARProtocol();
      CleanupStack::PushL(self);
      self->ConstructL();
      return self;
   }
   
   COSCARProtocol::COSCARProtocol()
   {
      
   }
   
   COSCARProtocol::~COSCARProtocol()
   {
      
   }
   
   void COSCARProtocol::ConstructL()
   {
      
   }
   
   TUint COSCARProtocol::GetProtocolId() const
   {
      return static_cast < TUint > ( K_PROTOCOL_ID );
   }
   
   const TPtrC COSCARProtocol::GetProtocolDescription() const
   {
      return TPtrC( K_PROTOCOL_DESC );
   }
   
   bool COSCARProtocol::Login()
   {
      return false;
   }
   
   bool COSCARProtocol::Logout()
   {
      return false;
   }
   
} // end namespace Protocol
