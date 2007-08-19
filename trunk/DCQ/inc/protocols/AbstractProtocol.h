#ifndef ABSTRACTPROTOCOL_H_
#define ABSTRACTPROTOCOL_H_

#include <e32base.h>

namespace Protocol
{

   class MAbstractProtocol : public CBase
   {
      public:                    
      	virtual ~MAbstractProtocol(){}
         
         virtual TUint GetProtocolId() const = 0;
         
         virtual const TPtrC GetProtocolDescription() const = 0;

         virtual bool Login() = 0;

         virtual bool Logout() = 0;
                           
      protected:      
         MAbstractProtocol()
         : CBase(){}
   
   };

} // end namespace Protocol

#endif /*ABSTRACTPROTOCOL_H_*/
