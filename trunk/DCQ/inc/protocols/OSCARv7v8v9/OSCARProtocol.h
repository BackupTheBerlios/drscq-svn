/********************************************************************
	created:	2007/08/15
	created:	15:8:2007   13:05
	file base:	OSCARProtocol
	file ext:	h
	author:		DrSoran
	
	purpose:	
*********************************************************************/

#ifndef COSCARPROTOCOL_H
#define COSCARPROTOCOL_H

#include "protocols/AbstractProtocol.h"

namespace Protocol {

   class COSCARProtocol : public CAbstractProtocol
   {
   public:
           
      static COSCARProtocol * NewL();
      
      static COSCARProtocol * NewLC();
      
      ~COSCARProtocol();
      
      TUint GetProtocolId() const;

      const TPtrC GetProtocolDescription() const;

      bool Login();

      bool Logout();

   private:
      
      COSCARProtocol();
      
      void ConstructL();
      
   };

} // end namespace DCQLib

#endif // COSCARPROTOCOL_H

