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
#include <CommDbConnPref.h>
#include <es_enum.h>

class MProgressObserver;
class MErrorObserver;
class TCommDbConnPref;
class CSocketServer;


// CONSTANTS
static const TUint32 KUndefinedIAPid = 0x00;

// CLASS DECLARATION

/**
*  CICQClient
* 
*/
class CICQClient : public CActive
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
      
      static TUint GetProtocolId();

      static const TPtrC GetProtocolDescription();
      
      void RegisterProgressObserver( MProgressObserver* aProgressObserver );
           
      void RegisterErrorObsrerver( MErrorObserver* aErrorObserer );
      
      /*
       * SetConnectionPreferences()
       *  
       * Sets connection preferences
       *
       * Params:
       * TUint aBearer    Bearer type
       * TBool aDialog    Show dialog? 
       * TUint32 aIapId   IAP to be connected, default KUndefinedIAPid
       *
       */
      void SetConnectionPreferences( TUint   aBearer, 
                                     TBool   aShowDialog, 
                                     TUint32 aIapId = KUndefinedIAPid );
     
      RConnection& GetConnection();
      
      const RConnection& GetConnection() const;
      
      TCommDbConnPref& GetConnectionPreferences();
      
      const TCommDbConnPref& GetConnectionPreferences() const;
      
      TBool IsConnected() const;           

      void LoginL();

      void LogoutL();
            
      void CancelCurrentAction();
      
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
      
   private:
      
      enum TICQClientStatus
      {
         EIdle = 0,
         EShuttingDown
      };
            
      // CActive implementations
      
      void RunL();
      
      void DoCancel();
      
   private:
      
      TICQClientStatus        iClientStatus;
      MProgressObserver*      iProgressObserver;
      MErrorObserver*         iErrorObserver;
      mutable RConnection     iConnection;
      mutable TCommDbConnPref iConnectionPrefs;
      CSocketServer*          iSocketServer;
};

#endif // CICQCLIENT_H

