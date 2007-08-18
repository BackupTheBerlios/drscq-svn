#ifndef OSCARCONSTANTS_H_
#define OSCARCONSTANTS_H_

namespace Protocol
{
	typedef unsigned char T_IQL_BYTE; 
	
	/* FLAP ********************************************************************/
	typedef T_IQL_BYTE 		T_FLAP_CHAN;
	typedef unsigned short 	T_FLAP_SEQ_NUM;
	typedef unsigned short 	T_FLAP_DATA_SIZE;
	
	static const T_IQL_BYTE 	K_FLAP_ID = 0x2A;
	static const T_FLAP_CHAN 	K_FLAP_CHAN_NewConnectionNegotation = 0x01;
	static const T_FLAP_CHAN 	K_FLAP_CHAN_SNACData = 0x02;
	static const T_FLAP_CHAN 	K_FLAP_CHAN_FLAPLevelError = 0x03;
	static const T_FLAP_CHAN 	K_FLAP_CHAN_CloseConnectionNegotation = 0x04;
	static const T_FLAP_CHAN 	K_FLAP_CHAN_KeepAlive = 0x05;
	
	
	
	/* SNAC ********************************************************************/
	typedef unsigned short	T_SNAC_FAM_ID;
	typedef unsigned short  T_SNAC_SUB_ID;
	typedef unsigned short	T_SNAC_FLAGS;
	typedef unsigned int	T_SNAC_REQ_ID;
	typedef unsigned short	T_SNAC_FAM_SUB_PAIR;
	typedef unsigned short	T_SNAC_ERROR;
	
	// Errors
	static const T_SNAC_ERROR			K_SNAC_ERROR_INVALID_SNAC_HEADER		= 0x0001;
	static const T_SNAC_ERROR			K_SNAC_ERROR_SRV_RATE_LIMIT				= 0x0002;
	static const T_SNAC_ERROR			K_SNAC_ERROR_CLI_RATE_LIMIT				= 0x0003;
	static const T_SNAC_ERROR			K_SNAC_ERROR_REC_NOT_LOGGED_IN			= 0x0004;
	static const T_SNAC_ERROR			K_SNAC_ERROR_REQ_SERV_UNAVAIL			= 0x0005;
	static const T_SNAC_ERROR			K_SNAC_ERROR_SRV_UNDEF					= 0x0006;
	static const T_SNAC_ERROR			K_SNAC_ERROR_OBSOLETE_SNAC				= 0x0007;
	static const T_SNAC_ERROR			K_SNAC_ERROR_SRV_NOT_SUPPORTED			= 0x0008;
	static const T_SNAC_ERROR			K_SNAC_ERROR_CLI_NOT_SUPPORTED			= 0x0009;
	static const T_SNAC_ERROR			K_SNAC_ERROR_CLI_REFUSED				= 0x000A;
	static const T_SNAC_ERROR			K_SNAC_ERROR_TOO_BIG					= 0x000B;
	static const T_SNAC_ERROR			K_SNAC_ERROR_RESP_LOST					= 0x000C;
	static const T_SNAC_ERROR			K_SNAC_ERROR_REQ_DENIED					= 0x000D;
	static const T_SNAC_ERROR			K_SNAC_ERROR_INCORRECT_SNAC				= 0x000E;
	static const T_SNAC_ERROR			K_SNAC_ERROR_INSUFF_RIGHTS				= 0x000F;
	static const T_SNAC_ERROR			K_SNAC_ERROR_REC_BLOCKED				= 0x0010;
	static const T_SNAC_ERROR			K_SNAC_ERROR_SENDER_TOO_EVIL			= 0x0011;
	static const T_SNAC_ERROR			K_SNAC_ERROR_REC_TOO_EVIL				= 0x0012;
	static const T_SNAC_ERROR			K_SNAC_ERROR_TEMP_UNAVAIL				= 0x0013;
	static const T_SNAC_ERROR			K_SNAC_ERROR_NO_MATCH					= 0x0014;
	static const T_SNAC_ERROR			K_SNAC_ERROR_LIST_OVERFLOW				= 0x0015;
	static const T_SNAC_ERROR			K_SNAC_ERROR_REQ_AMBIGIOUS				= 0x0016;
	static const T_SNAC_ERROR			K_SNAC_ERROR_SRV_QUEUE_FULL				= 0x0017;
	static const T_SNAC_ERROR			K_SNAC_ERROR_NOT_IN_AOL					= 0x0018;
	
	
	// Family 0x01 Generic service
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_SRV_GEN_ERROR 			= 0x0101;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_CLI_READY 				= 0x0102;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_SRV_FAMILIES		    	= 0x0103;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_CLI_SERVICExREQ 			= 0x0104;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_SRV_REDIRECTxSERVICE 	= 0x0105;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_CLI_RATES_REQUEST 		= 0x0106;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_SRV_RATE_LIMIT_INFO 		= 0x0107;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_CLI_RATES_ACK 			= 0x0108;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_CLI_RATES_DEL 			= 0x0109;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_SRV_RATE_LIMIT_WARN 		= 0x010A;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_SRV_PAUSE 				= 0x010B;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_CLI_PAUSE_ACK 			= 0x010C;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_SRV_RESUME 				= 0x010D;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_CLI_REQ_SELFINFO 		= 0x010E;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_SRV_ONLINExINFO 			= 0x010F;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_SRV_EVIL_NOTICE 			= 0x0110;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_CLI_SETxIDLExTIME 		= 0x0111;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_SRV_MIGRATION 			= 0x0112;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_SRV_MOTD 				= 0x0113;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_CLI_SET_PRIVACY 			= 0x0114;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_SRV_WELL_KNOWN_URLS 		= 0x0115;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_CLI_KEEPALIVE 			= 0x0116;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_CLI_FAMILIES_VERSIONS 	= 0x0117;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_SRV_FAMILIES_VERSIONS 	= 0x0118;	
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_CLI_SETxSTATUS 			= 0x011E;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_SRV_CLI_VERIFICATION 	= 0x011F;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_CLI_VERIFICATION_REPLY 	= 0x0120;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_SRV_EXT_STATUS 			= 0x0121;
	
	// Family 0x03 Buddy list management
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_SRV_BLM_ERROR				= 0x0301;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_CLI_BUDDYLIST_RIGHTS_REQ		= 0x0302;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_SRV_BUDDYLIST_RIGHTS_REPLY	= 0x0303;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_CLI_BUDDYLIST_ADD			= 0x0304;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_CLI_BUDDYLIST_REMOVE			= 0x0305;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_CLI_WATCHERS_REQUEST			= 0x0306;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_SRV_WATCHERS_LIST			= 0x0307;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_CLI_WATCHERxSUBxREQUEST		= 0x0308;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_SRV_WATCHERxNOTIFICATION		= 0x0309;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_SRV_NOTIFICATION_REJECTED	= 0x030A;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_SRV_USER_ONLINE				= 0x030B;
	static const T_SNAC_FAM_SUB_PAIR 	K_SNAC_SRV_USER_OFFLINE				= 0x030C;
	
	
	/* TLV *******************************************************/
	typedef unsigned short	T_TLV_TYPE;
	typedef unsigned short  T_TLV_LENGTH;
	
	static const T_TLV_TYPE				K_TLV_SCREEN_NAME					= 0x0001;
	static const T_TLV_TYPE				K_TLV_NEW_PASSWD					= 0x0002;
	static const T_TLV_TYPE				K_TLV_CLI_ID_STRING					= 0x0003;
	static const T_TLV_TYPE				K_TLV_ERR_DESC_URL					= 0x0004;
	static const T_TLV_TYPE				K_TLV_RECONNECT_HERE				= 0x0005;
	static const T_TLV_TYPE				K_TLV_AUTH_COOKIE					= 0x0006;
	static const T_TLV_TYPE				K_TLV_SNAC_VERSION					= 0x0007;
	static const T_TLV_TYPE				K_TLV_ERROR_SUB_CODE				= 0x0008;
	static const T_TLV_TYPE				K_TLV_DISCONN_REASON				= 0x0009;
	static const T_TLV_TYPE				K_TLV_RECONN_HOSTNAME				= 0x000A;
	static const T_TLV_TYPE				K_TLV_URL							= 0x000B;
	static const T_TLV_TYPE				K_TLV_DEBUG_DATA					= 0x000C;
	static const T_TLV_TYPE				K_TLV_FAMILY_ID						= 0x000D;
	static const T_TLV_TYPE				K_TLV_CLI_COUNTRY					= 0x000E;
	static const T_TLV_TYPE				K_TLV_CLI_LANG						= 0x000F;
	static const T_TLV_TYPE				K_TLV_SCRIPT						= 0x0010;
	static const T_TLV_TYPE				K_TLV_USER_EMAIL					= 0x0011;
	static const T_TLV_TYPE				K_TLV_OLD_PASSWD					= 0x0012;
	static const T_TLV_TYPE				K_TLV_REG_STATUS					= 0x0013;
	static const T_TLV_TYPE				K_TLV_DIST_NUMBER					= 0x0014;
	static const T_TLV_TYPE				K_TLV_PERSONAL_TEXT					= 0x0015;
	static const T_TLV_TYPE				K_TLV_CLI_ID						= 0x0016;
	static const T_TLV_TYPE				K_TLV_CLI_MAJ_VER					= 0x0017;
	static const T_TLV_TYPE				K_TLV_CLI_MIN_VER					= 0x0018;
	static const T_TLV_TYPE				K_TLV_CLI_LESS_VER					= 0x0019;
	static const T_TLV_TYPE				K_TLV_CLI_BUILD_NUM					= 0x001A;
	static const T_TLV_TYPE				K_TLV_PASSWD_HASH_MD5				= 0x0025;
	static const T_TLV_TYPE				K_TLV_LATES_BETA_BUILD_NUM			= 0x0040;
	static const T_TLV_TYPE				K_TLV_LATES_BETA_INSTALL_URL		= 0x0041;
	static const T_TLV_TYPE				K_TLV_LATES_BETA_INFO_URL			= 0x0042;
	static const T_TLV_TYPE				K_TLV_LATES_BETA_VER				= 0x0043;
	static const T_TLV_TYPE				K_TLV_LATES_REL_BUILD_NUM			= 0x0044;
	static const T_TLV_TYPE				K_TLV_LATES_REL_INSTALL_URL			= 0x0045;
	static const T_TLV_TYPE				K_TLV_LATES_REL_INFO_URL			= 0x0046;
	static const T_TLV_TYPE				K_TLV_LATES_REL_VER					= 0x0047;
	static const T_TLV_TYPE				K_TLV_BETA_DIGEST_SIG_MD5			= 0x0048;
	static const T_TLV_TYPE				K_TLV_REL_DIGEST_SIG_MD5			= 0x0049;
	static const T_TLV_TYPE				K_TLV_CHANGE_PASSWD_URL				= 0x0054;
	
	/* Message Types + Flags *****************************************************************/
	typedef T_IQL_BYTE T_MTYPE;
	typedef T_IQL_BYTE T_MFLAG;
	
	static const T_MTYPE 				K_MTYPE_PLAIN 			= 0x01;  //Plain text (simple) message 
	static const T_MTYPE				K_MTYPE_CHAT 			= 0x02;	 //Chat request message 
	static const T_MTYPE				K_MTYPE_FILEREQ 		= 0x03;  //File request / file ok message 
	static const T_MTYPE				K_MTYPE_URL 			= 0x04;  //URL message (0xFE formatted) 
	static const T_MTYPE				K_MTYPE_AUTHREQ 		= 0x06;  //Authorization request message (0xFE formatted) 
	static const T_MTYPE				K_MTYPE_AUTHDENY  		= 0x07;  //Authorization denied message (0xFE formatted) 
	static const T_MTYPE				K_MTYPE_AUTHOK  		= 0x08;  //Authorization given message (empty) 
	static const T_MTYPE				K_MTYPE_SERVER  		= 0x09;  //Message from OSCAR server (0xFE formatted) 
	static const T_MTYPE				K_MTYPE_ADDED  			= 0x0C;  //"You-were-added" message (0xFE formatted) 
	static const T_MTYPE				K_MTYPE_WWP   			= 0x0D;  //Web pager message (0xFE formatted) 
	static const T_MTYPE				K_MTYPE_EEXPRESS 		= 0x0E;  //Email express message (0xFE formatted) 
	static const T_MTYPE				K_MTYPE_CONTACTS 		= 0x13;  //Contact list message 
	static const T_MTYPE				K_MTYPE_PLUGIN   		= 0x1A;  //Plugin message described by text string 
	static const T_MTYPE				K_MTYPE_AUTOAWAY 		= 0xE8;  //Auto away message  
	static const T_MTYPE				K_MTYPE_AUTOBUSY 		= 0xE9;  //Auto occupied message  
	static const T_MTYPE				K_MTYPE_AUTONA   		= 0xEA;  //Auto not available message  
	static const T_MTYPE				K_MTYPE_AUTODND  		= 0xEB;  //Auto do not disturb message  
	static const T_MTYPE				K_MTYPE_AUTOFFC  		= 0xEC;  //Auto free for chat message  
	
	static const T_MFLAG				K_MFLAG_NORMAL			= 0x01;
	static const T_MFLAG				K_MFLAG_AUTO			= 0x03;
	static const T_MFLAG				K_MFLAG_MULTI			= 0x80;
	
	
	/* User ************************************************************************************/
	typedef unsigned short T_USER_CLASS;
	typedef unsigned short T_USER_STATUS;
	
	static const T_USER_CLASS			K_USER_CLASS_UNCONFIRMED	= 0x0001;
	static const T_USER_CLASS			K_USER_CLASS_ADMIN			= 0x0002;
	static const T_USER_CLASS			K_USER_CLASS_AOL			= 0x0004;
	static const T_USER_CLASS			K_USER_CLASS_COMMERCIAL		= 0x0008;
	static const T_USER_CLASS			K_USER_CLASS_FREE			= 0x0010;
	static const T_USER_CLASS			K_USER_CLASS_AWAY			= 0x0020;
	static const T_USER_CLASS			K_USER_CLASS_ICQ			= 0x0040;
	static const T_USER_CLASS			K_USER_CLASS_WIRELESS		= 0x0080;
	static const T_USER_CLASS			K_USER_CLASS_UNKNOWN100		= 0x0100;
	static const T_USER_CLASS			K_USER_CLASS_UNKNOWN200		= 0x0200;
	static const T_USER_CLASS			K_USER_CLASS_UNKNOWN400		= 0x0400;
	static const T_USER_CLASS			K_USER_CLASS_UNKNOWN800		= 0x0800;
		
	static const T_USER_STATUS			K_USER_STATUS_WEBAWARE		= 0x0001;
	static const T_USER_STATUS			K_USER_STATUS_SHOW_IP		= 0x0002;
	static const T_USER_STATUS			K_USER_STATUS_BIRTHDAY		= 0x0008;
	static const T_USER_STATUS			K_USER_STATUS_WEBFRONT		= 0x0020;
	static const T_USER_STATUS			K_USER_STATUS_DCDISABLED	= 0x0100;
	static const T_USER_STATUS			K_USER_STATUS_DCAUTH		= 0x1000;
	static const T_USER_STATUS			K_USER_STATUS_DCCONT		= 0x2000;
	
	static const T_USER_STATUS			K_USER_STATUS_ONLINE		= 0x0000;
	static const T_USER_STATUS			K_USER_STATUS_AWAY			= 0x0001;
	static const T_USER_STATUS			K_USER_STATUS_DND			= 0x0002;
	static const T_USER_STATUS			K_USER_STATUS_NA			= 0x0004;
	static const T_USER_STATUS			K_USER_STATUS_BUSY			= 0x0010;
	static const T_USER_STATUS			K_USER_STATUS_FREE4CHAT		= 0x0020;
	static const T_USER_STATUS			K_USER_STATUS_INVISIBLE		= 0x0100;

} // end namespace Protocol

#endif /*OSCARCONSTANTS_H_*/
