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

#include <e32base.h>


namespace Protocol {

   class COSCARProtocol : public CBase
   {
   public:
           
      static COSCARProtocol * NewL();
      
      static COSCARProtocol * NewLC();
      
      ~COSCARProtocol();

      const TPtrC GetProtocolDescription() const;

      bool Login() const;

      bool Logout() const;

   private:
      
      COSCARProtocol();
      
      void ConstructL();
      
   private:
      
     static const TPtrC KProtocolDesc;
      
   };

} // end namespace DCQLib

#endif // COSCARPROTOCOL_H