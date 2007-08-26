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
#include <e32cons.h>
#include <es_sock.h>
#include <nifman.h>

class MProgressObserver;
class MErrorObserver;
class CSocketServer;
namespace Protocol { class COSCARProtocol; }
class TCommDbConnPref;

// CLASS DECLARATION

/**
*  CICQClient
* 
*/
class CICQClient : public CActive
{
   public:
      
      enum TICQClientStates
      {
         EIdle,
         EOpening,
         EOpen
      };
      
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
           
      void ConnectL( TUint32 aAddr, TUint16 aPort, TCommDbConnPref& aConPrefs );
      
      void ConnectL( const TDesC& aServerName, TUint16 aPort, TCommDbConnPref& aConPrefs );     
      
      TBool IsConnected() const;
      
      void Cancel();
      
      void Shutdown();     
   
   private:
   
   	/**
   		* Constructor for performing 1st stage construction
   		*/
   	CICQClient();
   
   	/**
   		* EPOC default constructor for performing 2nd stage construction
   		*/
   	void ConstructL();
      
      void OpenL( TCommDbConnPref& aConPrefs );      
      
       // From CActive
      // Handle completion
      void RunL();

      // How to cancel me
      void DoCancel();
      
   private:
      
      TICQClientStates          iClientStatus;
      MProgressObserver*        iProgressObserver;
      MErrorObserver*           iErrorObserver;
      RConnection               iConnection;
      CSocketServer*            iSocketServer;
      Protocol::COSCARProtocol* iProtocol;
      
      TUint32                   iAddr;
      TUint16                   iPort;    
      TBuf < KMaxSockAddrSize > iName;
      
};

#endif // CICQCLIENT_H

