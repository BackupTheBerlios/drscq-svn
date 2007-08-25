/*
============================================================================
 Name		: CICQClient.h
 Author	  : Ronny Röhricht
 Version	 :
 Copyright   : (C) Ronny Röhricht 2007
 Description : CICQClient declaration
============================================================================
*/

#ifndef CICQCLIENT_H
#define CICQCLIENT_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

class MProgressObserver;
class MErrorObserver;
class CSocketServer;
namespace Protocol { class COSCARProtocol; }

// CLASS DECLARATION

/**
*  CICQClient
* 
*/
class CICQClient : public CBase
{
   public: // Constructors and destructor
   
   	/**
   		* Destructor.
   		*/
   	~CICQClient();
   
   		/**
   		* Two-phased constructor.
   		*/
   	static CICQClient* NewL();
   
   		/**
   		* Two-phased constructor.
   		*/
   	static CICQClient* NewLC();
      
      
      void RegisterProgressObserver( MProgressObserver* aProgressObserver );
           
      void RegisterErrorObsrerver( MErrorObserver* aErrorObserer );
      
      void ConnectL( TUint32 aAddr, TUint16 aPort );
      
      void ConnectL( const TDesC& aServerName, TUint16 aPort );     
      
      void Cancel();
      
      void Shutdown();
      
      bool IsConnected() const;
   
   private:
   
   	/**
   		* Constructor for performing 1st stage construction
   		*/
   	CICQClient();
   
   	/**
   		* EPOC default constructor for performing 2nd stage construction
   		*/
   	void ConstructL();
      
   private:
      
      MProgressObserver*        iProgressObserver;
      MErrorObserver*           iErrorObserver;
      CSocketServer*            iSocketServer;
      Protocol::COSCARProtocol* iProtocol;      
};

#endif // CICQCLIENT_H

