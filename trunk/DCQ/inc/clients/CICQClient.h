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
#include <e32base.h>
#include <CommDbConnPref.h>
#include <es_enum.h>

class MProgressObserver;
class MErrorObserver;
namespace Protocol { class COSCARProtocol; }
class TCommDbConnPref;


// CONSTANTS
static const TUint32 KUndefinedIAPid = 0x00;

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
      
      MProgressObserver*           iProgressObserver;
      MErrorObserver*              iErrorObserver;
      mutable RConnection          iConnection;
      Protocol::COSCARProtocol*    iProtocol;
      mutable TCommDbConnPref      iConnectionPrefs;
};

#endif // CICQCLIENT_H

