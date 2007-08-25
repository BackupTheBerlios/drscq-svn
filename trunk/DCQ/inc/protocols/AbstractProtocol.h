#ifndef ABSTRACTPROTOCOL_H_
#define ABSTRACTPROTOCOL_H_

#include <e32base.h>

#include "observer/MSocketObserver.h"

namespace Protocol
{

   class MAbstractProtocol : public CBase, 
                             public MSocketObserver
   {
      public:                    
      	virtual ~MAbstractProtocol(){}
         
         virtual TUint GetProtocolId() const = 0;
         
         virtual const TPtrC GetProtocolDescription() const = 0;
         
         virtual void OpenL() = 0;

         virtual void LoginL() = 0;

         virtual void LogoutL() = 0;
         
         virtual void Cancel() = 0;
         
         virtual void Close() = 0;
                           
      protected:      
         MAbstractProtocol()
         : CBase(){}
   
   };

} // end namespace Protocol

#endif /*ABSTRACTPROTOCOL_H_*/
