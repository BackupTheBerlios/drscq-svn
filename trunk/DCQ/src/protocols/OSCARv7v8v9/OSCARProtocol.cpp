/********************************************************************
 created:	2007/08/15
 created:	15:8:2007   13:08
 file base:	OSCARProtocol
 file ext:	cpp
 author:		DrSoran
 
 purpose:	
 *********************************************************************/

#include "protocols/OSCARv7v8v9/OSCARProtocol.h"

namespace Protocol {
   
   _LIT(KProtocolDesc, "OSCAR(ICQ) v7,v8,v9");   
   
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
   
   const TPtrC COSCARProtocol::GetProtocolDescription() const
   {
      return KProtocolDesc;
   }
   
   bool COSCARProtocol::Login() const
   {
      return false;
   }
   
   bool COSCARProtocol::Logout() const
   {
      return false;
   }
   
} // end namespace Protocol