// AtumApplication.h: interface for the CAtumApplication class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ATUMAPPLICATION_H__32E91AE4_C7F3_424D_B983_17488D8A215B__INCLUDED_)
#define AFX_ATUMAPPLICATION_H__32E91AE4_C7F3_424D_B983_17488D8A215B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "AtumProtocol.h"
#include "Structs.h"	
#include "AtumTypedef.h"
#include "AtumDefine.h"	
#include "AtumDatabase.h"
#include "D3DApp.h"
#include "IMEKey.h"		// imm32.lib
//#include "INFGameMainQSlot.h"
// 2008-03-19 by bhsohn Ep3¿É¼ÇÃ¢
//#include "INFSystem.h"
//#include "INFOptionSystem.h"
#include "WeaponItemInfo.h"		 


#include "D3DHanFont.h"
#include "Camera.h"
#include "ShuttleChild.h"
#include "StoreData.h"

#include "INFCityBase.h"
#include "INFCityLab.h"
#include "Interface.h"
#include "FieldWinSocketManager.h"
#include "MonsterData.h"
#include "SceneData.h"



//#include "CInput.h"

// 2009. 06. 09 by ckPark OMI °ÔÀÓ ½ÃÀÛ½Ã Ã¼Å©¼¶ °è»êÇÏµµ·Ï º¯°æ
//#include "sha256.h"
// end 2009. 06. 09 by ckPark OMI °ÔÀÓ ½ÃÀÛ½Ã Ã¼Å©¼¶ °è»êÇÏµµ·Ï º¯°æ

class CFrustum;
//class CD3DHanFont;
class CKeyBoardInput;
//class CCamera;
class CShuttleRender;
//class CShuttleChild;
class CCharacterChild;
class CTraceRender;
class IMEKey;
class CChat;
//class CFieldWinSocket;
class CIMSocket;
// 2007-11-22 by bhsohn ¾Æ·¹³ª ÅëÇÕ¼­¹ö
class CIMSocketManager;
//class CFieldWinSocketManager;
class CArenaManager;

class CMapInitThread;
class CGameData;
class CEffectRender;
class CAtumNode;
//class CInterface;
class CAbuseFilter;
class CAtumSound;
//class CSceneData;
//class CAtumDatabase;
class CINFStageEffect;
class CINFGameMain;
//class CStoreData;
class CQuestData;
class CBackground;
class CINFSelect;
class CINFChannelList;
class CUnitRender;
class CCharacterRender;						// 2005-07-21 by ispark
class CFxSystem;
class CTutorialSystem;
class CInputManager;
class CGlobalImage;
class CUnitData;
class CSinglePlayGame;	// 2008-08-11 by bhsohn ´Üµ¶À¸·Î ½ÇÇà µÇ°Ô²û
// 2008-11-13 by bhsohn Á¶ÀÌ½ºÆ½ ÀÛ¾÷
class CJoyStickInput;
class CJoyStickFreedback;
// end 2008-11-13 by bhsohn Á¶ÀÌ½ºÆ½ ÀÛ¾÷

class CWorldRankManager;		// 2009-02-13 by bhsohn ¿ùµå ·©Å· ½Ã½ºÅÛ

// 2009. 11. 02 by ckPark ÀÎÇÇ´ÏÆ¼ ÇÊµå ÀÎ½ºÅÏ½º ´øÁ¯ ½Ã½ºÅÛ
class CInfinityManager;
// end 2009. 11. 02 by ckPark ÀÎÇÇ´ÏÆ¼ ÇÊµå ÀÎ½ºÅÏ½º ´øÁ¯ ½Ã½ºÅÛ

// 2009. 11. 23 by jskim ¸®¼Ò½º ·Îµù ±¸Á¶ º¯°æ
class CSkinnedMesh;
class CMeshInitThread;
//end 2009. 11. 23 by jskim ¸®¼Ò½º ·Îµù ±¸Á¶ º¯°æ

// 2010-06-15 by shcho&hslee Æê½Ã½ºÅÛ
class CPetManager;
// end 2010-06-15 by shcho&hslee Æê½Ã½ºÅÛ



class CMapLoad;    // 2010. 10. 05 by jskim ¸Ê·Îµù ±¸Á¶ º¯°æ

struct MSG_FC_WAR_INFLUENCE_CONSECUTIVE_VICTORITES
{
	INT PointBCU;
	INT PointANI;
};

typedef struct
{
	INT			ItemNum;						// ¾ÆÀÌÅÛ °íÀ¯¹øÈ£, ÀåÂø ¾ÆÀÌÅÛÀÏ ¶§ (ITEM_BASE*)
	BYTE		byItemKind;				// ¾ÆÀÌÅÛ Á¾·ù(±â°üÆ÷, ºö, ·ÎÄÏ, ½ºÅ³.....)
	UID64_t		nUniqueNumber;			// ¾ÆÀÌÅÛ °íÀ¯¹øÈ£
	INT			nAmount;				// ¾ÆÀÌÅÛ °¹¼ö
	UINT		nBuildingIndex;			// °Ç¹° ÀÎµ¦½º
	char		szIconName[20];			// ¾ÆÀÌÅÛ ID
	char		szName[50];				// ¾ÆÀÌÅÛ ÀÌ¸§
	UINT		uSellingPrice;			// ÆÇ¸Å °¡°Ý 
	INT			SourceIndex;			// ÀÌÆåÆ®, ¾ÆÀÌÄÜ(ºò/½º¸ô) ¸®¼Ò½º µ¥ÀÌÅ¸
	BYTE		bySelectType;
	POINT		ptIcon;
} stMultiSelectItem;

// 2007-11-20 by bhsohn ¸Ê·Îµù ÇÏ´Â ¹æ½Ä º¯°æ
// °ÔÀÓ ½ÃÀÛ ½Ã ±¸Á¶Ã¼
typedef struct
{
	AVECTOR3		vPos;
	BitFlag16_t		MapWeather;
} stGameStartInfo;

// 2007-12-21 by bhsohn ÇÁ·Î±×·¥ ´ÙÁß ¶ô ±¸Á¶ »ý¼º
// ¶ô°ü·Ã ¸ðµå
#define		MULTI_LOCK_ALL_MATCHING		0		//	¸ðµÎ ¸ÅÄª µÇ¾ßÁö¸¸ Ç®¸°´Ù.
#define		MULTI_LOCK_ONE_MATCHING		1		//	ÇÏ³ª¸¸ ¸ÅÄªµÇµµ Ç®¸°´Ù.

// °ÔÀÓ ½ÃÀÛÇÏ±â À§ÇÑ ±âº» Á¤º¸
typedef struct
{
	MessageType_t			nLockMsg;
	vector<MessageType_t>	vecUnLockMsg;
	int						nLockType;
	BOOL					bFiledServer;
} stMultiLockInfo;
// end 2007-12-21 by bhsohn ÇÁ·Î±×·¥ ´ÙÁß ¶ô ±¸Á¶ »ý¼º

// 2007-11-22 by bhsohn ¾Æ·¹³ª ÅëÇÕ¼­¹ö
// °ÔÀÓ ½ºÅ¸Æ® ¿Ï·á½Ã Ã³¸® µÇ´Â ±¸Á¶Ã¼
typedef struct
{
	char			ServerGroupName0[SIZE_MAX_SERVER_NAME];			// 2007-04-09 by cmkwon
	char			MainORTestServerName[SIZE_MAX_SERVER_NAME];		// 2007-04-09 by cmkwon
	char			GamePublisher[SIZE_MAX_GAME_PUBLISHER_NAME];	// 2007-04-09 by cmkwon

	MAP_CHANNEL_INDEX	MapChannelIndex;		// Ä³¸¯ÅÍ°¡ ¼ÓÇÑ ¸Ê ¹× Ã¤³Î
	BYTE				CharacterMode0;				// 

	AVECTOR3			PositionVector;
	BitFlag16_t			MapWeather;
	BOOL				bMemberPCBang;			// °¡¸Í PC¹æ ÇÃ·¡±×
}structGameStartOkInfo;
// end 2007-11-22 by bhsohn ¾Æ·¹³ª ÅëÇÕ¼­¹ö

// 2009. 11. 23 by jskim ¸®¼Ò½º ·Îµù ±¸Á¶ º¯°æ
struct structLoadingGameData
{
	structLoadingGameData()
	{
		LoadingPriority = _NOTHING_PRIORITY;
	}
	CGameData* pGameData;
	int				MeshIndex;
	int				MeshType;
	int				Step;					// ·Îµù ½ºÅÜ(1, 6)
	int				Text_Cnt;				// ÅØ½ºÃÄ ·Îµù ÁøÇà ¼ö
	int				LoadingPriority;
	CSkinnedMesh* pSkinnedMesh;
};
struct structLoadingGameInfo
{
	structLoadingGameInfo()
	{
		LoadingPriority = _NOTHING_PRIORITY;
	}
	char			MeshName[16];
	int				MeshType;
	CSkinnedMesh* pSkinnedMesh;
	int				LoadingPriority;
};

class CItemInfo;

// 2007-07-10 by bhsohn Åë½Å Å¸ÀÔ ¿¡·¯¿¡ ´ëÇÑ Ã³¸®
#define SIZE_MAX_ERROR_CHAT_MESSAGE			512

// 2008-11-13 by bhsohn Á¶ÀÌ½ºÆ½ ÀÛ¾÷
#define MAX_JOYCTL_LIST			10			// MAX_JOY_LIST¿Í µ¿ÀÏÇÑ °ªÀÌ¾î¾ßÇÑ´Ù.

// 2009-01-22 by bhsohn Xign Code »ç¿ëÇÏ´Â ³ª¶ó¸¸ ¸ðµâ Ãß°¡
//////////////////////// °ÔÀÓ °¡µå ¼³Á¤////////////////////////
//
#define		USE_GAMEGUARD_NONE					0		//°ÔÀÓ°¡µå »ç¿ë¾ÈÇÔ
#define		USE_GAMEGUARD_AHNLAB_HACKSHIELD		1		//ÇÙ½¯µå °ÔÀÓ°¡µå
#define		USE_GAMEGUARD_XIGNCODE				2		//Xign °ÔÀÓ°¡µå
#define		USE_GAMEGUARD_NPROTECTOR			3		// 2009-01-28 by bhsohn nProtector °ÔÀÓ °¡µå Ãß°¡				
// 2009. 06. 17 by ckPark Frost System
#define		USE_GAMEGUARD_FROST					4
// end 2009. 06. 17 by ckPark Frost System
	// 2009. 09. 21 by jskim °ÔÀÓ°¡µå XTRAP Àû¿ë(¹èÆ®³²)
#define		USE_GAMEGUARD_XTRAP					5
	//end 2009. 09. 21 by jskim °ÔÀÓ°¡µå XTRAP Àû¿ë(¹èÆ®³²)

// 2009. 11. 03 by ckPark ÅÂ±¹ APEX °ÔÀÓ°¡µå ÀÛ¾÷
#define		USE_GAMEGUARD_APEX					6
// end 2009. 11. 03 by ckPark ÅÂ±¹ APEX °ÔÀÓ°¡µå ÀÛ¾÷


// 2009. 06. 17 by ckPark Frost System

// #if defined(_DEBUG) || defined(INNOVA_RELEASE) || defined(GAMEFORGE_RELEASE)
// 	// °ÔÀÓ°¡µå »ç¿ë¾ÈÇÔ
// 	#define		GAMEGUARD_TYPE 					USE_GAMEGUARD_NONE
// 	#define		NO_GAMEGUARD
// #elif defined(LANGUAGE_CHINA) // 2009-04-15 by bhsohn Áß±¹ XignCode»ç¿ë
// 	#define		DEFINE_USE_GAMEGUARD_XIGNCODE		
// 	// XIGNCode
// 	#define		GAMEGUARD_TYPE					USE_GAMEGUARD_XIGNCODE	
// 
// // 2009-01-28 by bhsohn nProtector °ÔÀÓ °¡µå Ãß°¡
// #elif defined(LANGUAGE_JAPAN)
// 	// nProtector °ÔÀÓ °¡µå Ãß°¡
// 	#define		GAMEGUARD_TYPE 					USE_GAMEGUARD_NPROTECTOR
// 	#define		DEFINE_USE_GAMEGUARD_NPROTECTOR	
// 	#pragma comment(lib, "NPGameLib.lib")
// 	#include "NPGameLib.h"		// 
// // end 2009-01-28 by bhsohn nProtector °ÔÀÓ °¡µå Ãß°¡
// #else
// 	// ÇÙ½¯µå
// 	#define		GAMEGUARD_TYPE					USE_GAMEGUARD_AHNLAB_HACKSHIELD		
// #endif
// // end 2009-01-22 by bhsohn Xign Code »ç¿ëÇÏ´Â ³ª¶ó¸¸ ¸ðµâ Ãß°¡


	// 2009. 07. 13 by jsKim °ÔÀÓÆ÷Áö ÇÙ½Çµå Àû¿ë
// #if defined(_DEBUG) || defined(GAMEFORGE_RELEASE)
// 	// °ÔÀÓ°¡µå »ç¿ë¾ÈÇÔ
// 	#define		GAMEGUARD_TYPE 					USE_GAMEGUARD_NONE
// 	#define		NO_GAMEGUARD

#if defined(_DEBUG)
// °ÔÀÓ°¡µå »ç¿ë¾ÈÇÔ
#define		GAMEGUARD_TYPE 					USE_GAMEGUARD_NONE
#define		NO_GAMEGUARD

	// 2011. 01. 18 by jsKim 140¹ø ÇÙ½Çµå Á¦°Å 
#elif  defined(GAMEGUARD_NOT_EXECUTE_HSSON)
#define		GAMEGUARD_TYPE					USE_GAMEGUARD_NONE
	// end 2011. 01. 18 by jsKim 140¹ø ÇÙ½Çµå Á¦°Å 
#elif  defined(GAMEFORGE_RELEASE)
#define		GAMEGUARD_TYPE					USE_GAMEGUARD_AHNLAB_HACKSHIELD
	// end 2009. 07. 13 by jsKim °ÔÀÓÆ÷Áö ÇÙ½Çµå Àû¿ë


#elif defined(LANGUAGE_CHINA)
	// 2009-04-15 by bhsohn Áß±¹ XignCode»ç¿ë
#define		DEFINE_USE_GAMEGUARD_XIGNCODE		
// XIGNCode
#define		GAMEGUARD_TYPE					USE_GAMEGUARD_XIGNCODE	

#elif defined(LANGUAGE_JAPAN)
	// 2009-01-28 by bhsohn nProtector °ÔÀÓ °¡µå Ãß°¡
	// nProtector °ÔÀÓ °¡µå Ãß°¡
#define		GAMEGUARD_TYPE 					USE_GAMEGUARD_NPROTECTOR
#define		DEFINE_USE_GAMEGUARD_NPROTECTOR	
#pragma comment(lib, "NPGameLib.lib")
#include "NPGameLib.h"		// 
// end 2009-01-28 by bhsohn nProtector °ÔÀÓ °¡µå Ãß°¡

// 2009. 09. 21 by jskim °ÔÀÓ°¡µå XTRAP Àû¿ë(¹èÆ®³²)
#elif defined(LANGUAGE_VIETNAM)
#define		GAMEGUARD_TYPE 					USE_GAMEGUARD_XTRAP
#define		DEFINE_USE_GAMEGUARD_XTRAP

#pragma comment(lib, "XTrap4Client_st")
#pragma comment(lib, "XTrap4Client_ClientPart_st")
#pragma comment(lib, "XTrap4Client_ServerPart_st")
#pragma comment(lib, "XTrap_Unipher_st")
#include "Xtrap_C_Interface.h"
//end 2009. 09. 21 by jskim °ÔÀÓ°¡µå XTRAP Àû¿ë(¹èÆ®³²)

// 2009. 11. 03 by ckPark ÅÂ±¹ APEX °ÔÀÓ°¡µå ÀÛ¾÷
#elif defined(LANGUAGE_THAI)
#define		GAMEGUARD_TYPE					USE_GAMEGUARD_APEX
#define		DEFINE_USE_GAMEGUARD_APEX

#include "ApexClient.h"
#pragma comment( lib, "AHClientInterface.lib" )
// end 2009. 11. 03 by ckPark ÅÂ±¹ APEX °ÔÀÓ°¡µå ÀÛ¾÷

#elif defined(INNOVA_RELEASE)
#define		GAMEGUARD_TYPE					USE_GAMEGUARD_FROST
#define		DEFINE_USE_GAMEGUARD_FROST

// 2010. 01. 13 by ckPark Frost°ÔÀÓ°¡µå 2009.11.10ÀÏÀÚ ¾÷µ¥ÀÌÆ®
#pragma warning (disable : 4786)
// end 2010. 01. 13 by ckPark Frost°ÔÀÓ°¡µå 2009.11.10ÀÏÀÚ ¾÷µ¥ÀÌÆ®

#include "shieldSecurity.h"
#include "shieldSecurityDll.h"
// 2010. 11. 05 by jskim °ÔÀÓ°¡µå Àû¿ë (¾Æ¸£ÇîÆ¼³ª)
#elif defined(LANGUAGE_ARGENTINA)
#define		GAMEGUARD_TYPE					USE_GAMEGUARD_XTRAP
#define		DEFINE_USE_GAMEGUARD_XTRAP
#pragma comment(lib, "XTrap4Client_st")
#pragma comment(lib, "XTrap4Client_ClientPart_st")
#pragma comment(lib, "XTrap4Client_ServerPart_st")
#pragma comment(lib, "XTrap_Unipher_st")
#include "Xtrap_C_Interface.h"
// end 2010. 11. 05 by jskim °ÔÀÓ°¡µå Àû¿ë (¾Æ¸£ÇîÆ¼³ª)
#else
	// ÇÙ½¯µå
#define		GAMEGUARD_TYPE					USE_GAMEGUARD_AHNLAB_HACKSHIELD		
#endif

// end 2009. 06. 17 by ckPark Frost System

class CAtumApplication : public CD3DApplication
{
	friend class CShuttleChild;
public:
	
	CAtumApplication();
	virtual ~CAtumApplication();

public:
	
	// 2004-11-11 by jschoi ½ºÇÇµåÇÙ °ü·Ã º¯¼ö
	int							m_nSendMovePacketCount;	// MovePacketÀ» º¸³½ ¼ö
	int							m_nCheckSpeedHackCount;	// ½ºÇÇµåÇÙ Ã¼Å© Ä«¿îÆ® 1ÃÊ´ç 5°³
	DWORD						m_dwCheckSpeedHackTime;		// ½ºÇÇµåÇÙ Ã¼Å© Å¸ÀÓ timeGetTime()
	DWORD						m_dwSpeedHackTimer;
	DWORD						m_dwHackCheckTime;		// 2005-12-21 by ispark, ÇÙ Ã¼Å© Å¸ÀÓ(1ºÐ´ç)

	void*						m_unknown1;
	DWORD						m_dwInetAnticheatCheckTime;
	DWORD						m_dwInetAnticheatCheckTime2;
	DWORD						m_dwMoveCheckTime;	   		

	CD3DHanFont* m_pFontDebug;				// ÅØ½ºÆ® Ç¥½Ã¿ë ÆùÆ®
	CD3DHanFont* m_pFontCandidate[CHAR_INF_CANDIDATE];				// ÇÑÆùÆ®
	// 2007.04.24 by bhsohn China IME Working
	CD3DHanFont* m_pFontCompositon;
	CD3DHanFont* m_pFontIMEType;

	CKeyBoardInput* m_pKeyBoard;				// KeyBoard Á¦¾î
	CCamera* m_pCamera;					// Camera Á¦¾î

	// 2008-11-13 by bhsohn Á¶ÀÌ½ºÆ½ ÀÛ¾÷
	CJoyStickInput* m_pJoyStick;				// Á¶ÀÌ½ºÆ½ Á¦¾î
	CJoyStickFreedback* m_pJoyStickFreedback;				// Áøµ¿ Á¶ÀÌ½ºÆ½ Á¦¾î	
	// end 2008-11-13 by bhsohn Á¶ÀÌ½ºÆ½ ÀÛ¾÷

	CUnitRender* m_pUnitRender;
	CCharacterRender* m_pCharacterRender;			// 2005-07-13 by ispark Ä³¸¯ÅÍ ·»´õ¸µ
	CShuttleChild* m_pShuttleChild;			// ¼ÅÆ² Data
	CCharacterChild* m_pCharacterChild;			// Ä³¸¯ÅÍ Data// 2005-07-21 by ispark

	DWORD						m_dwStateBlock;				// 
	DWORD						m_dwGameState;
	LPDIRECT3DVERTEXBUFFER9		m_pVBSleep;
	BOOL						m_bBazaar;					// ¹ÙÀÚ¸Ê

	//void* m_unknown2;

	CD3DHanFont* m_pFontInput;
	IMEKey						m_inputkey;
	CChat* m_pChat;
	BOOL						m_bChatMode;
	BOOL						m_bFixUnitDirMode;				// À¯´Ö ÁøÇà¹æÇâ °íÁ¤ ¸ðµå
	BOOL						m_bMessageBox;					// ¸Þ½ÃÁö ¹Ú½º°¡ È­¸é»ó¿¡ Á¸ÀçÇÏ´Â°¡?
	char						m_strChat[SIZE_MAX_CHAT_MESSAGE];

	// 2007-11-22 by bhsohn ¾Æ·¹³ª ÅëÇÕ¼­¹ö
	//CFieldWinSocket *			m_pFieldWinSocket;				// ÇÊµå ¼­¹ö
	CFieldWinSocketManager* m_pFieldWinSocket;				// ÇÊµå ¼­¹ö

	BOOL						m_bReconnectFieldServer;		// ´Ù¸¥ IP ¼­¹ö·ÎÀÇ ÀçÁ¢¼Ó

	// 2007-11-22 by bhsohn ¾Æ·¹³ª ÅëÇÕ¼­¹ö
	//CIMSocket		*			m_pIMSocket;					// Ã¤ÆÃ ¼­¹ö
	CIMSocketManager* m_pIMSocket;			// Ã¤ÆÃ ¼­¹ö

	

	char						m_strUserID[SIZE_MAX_ACCOUNT_NAME];
	char						m_strUserPassword[SIZE_MAX_PASSWORD_MD5_STRING];
	UINT						m_accountUniqueNumber;
	char						m_strFieldIP[SIZE_MAX_IPADDRESS];
	char						m_strFieldIPCurrent[SIZE_MAX_IPADDRESS];
	INT							m_nFieldPort;
	char						m_strChatIP[SIZE_MAX_IPADDRESS];
	INT							m_nChatPort;

	BOOL						m_bOtherFieldWarping;
	USHORT						m_sWarpAreaIndex;

	INT							m_nInvalidClientIndexCont;		// Å¸Ä³¸¯ÅÍ ¸®½ºÆ®Áß ÀÎµ¦½º°¡ 0 ÀÎ ¸®½ºÆ® ¼ö
	///////////// Thread ////////////////
	CMapInitThread* m_pMapInitThread;				// ¸Ê ·Îµù
	CRITICAL_SECTION			m_cs;							// µ¿±âÈ­ °´Ã¼
	///////////// Tile Texture Buffer /////////////
	CGameData* m_pData;						// µ¥ÀÌÅ¸ÆÄÀÏ (¸ÊÅ¸ÀÏÆÄÀÏ)

	D3DXVECTOR3					m_vClientOldPos;				// Move Á¤º¸ º¸³¾½Ã¿¡ ¿òÁ÷ÀÎ °Å¸®¸¦ Ã¼Å©ÇÏ±âÀ§ÇØ ÀÌÀü ¼ÅÆ²ÁÂÇ¥ ÀúÀå
	///////////// Render ÂüÁ¶ /////////////
	INT							m_nCheckRenderPos;				// ·»´õ¸µ °Ë»ç¸¦ ÇØ¾ßÇÒ ºÎºÐÀ» Ã¼Å©ÇÏ´Â º¯¼ö
	FLOAT						m_fRenderDeleteCheckTime;		// »ç¿ëÇÏÁö ¾ÊÀº ¸®¼Ò½º¸¦ Áö¿ï ½Ã°£ Ã¼Å© 
	BYTE						m_nItemStorage;					//¾ÆÀÌÅÛÃ¢, Ã¢°í ±¸ºÐ
	// VoIP	//////////////////////////////////////////////////////////////////
	VOIP_STATE					m_VOIPState;
	/////////////////////////////////////////////////////////////////////////
	// Effect
	CEffectRender* m_pEffectRender;//by dhkwon	2003.5.13
	/////////////////////////////////////////////////////////////////////////
	FLOAT						m_fCheckSocketTime;				// Socket Check Time
	FLOAT						m_fOldTickTime;					// Áö³­ ElapsedTime
	FLOAT						m_fReturnKeyTime;				// Return Key Check Time

	CAtumNode* m_pEffectList;

	/////////////////////////////////////////////////////////////////////////
	BOOL						m_bDebugText;
	/////////////////////////////////////////////////////////////////////////
	BOOL						m_bClientQuit;
	BOOL						m_bResCheck;
	BOOL						m_bReadyBeginScene;

	BOOL						m_bDeleteItemSend;			// Item À» Áö¿ì¶ó°í ¼­¹ö¿¡ Àü¼Û

	CInterface* m_pInterface;
	BOOL						m_IsFullMode;					// Ã¢¸ðµåÀÎÁö
	CAbuseFilter* m_pAbuseFilter;
	CGameData* m_pAbuseFilterData;

	FLOAT						m_fBattleCountCheckTime;	// ÆÄÆ¼ ´ë°á½Ã Ä«¿îÆ® ´Ù¿î µé¾î°¡±â À§ÇÑ º¯¼ö
	INT							m_nBattlePartyCount;
	INT							m_bDegree;					// 0 Àú»ç¾ç, 1 Áß»ç¾ç , 2 °í»ç¾ç, 3 Ãæµ¹Ã³¸®(À¯´Ö)

	char						m_strDebug[512];			// À±¿ø¾¾ µð¹ö±×¿ë ¿¡·¯ ¸Þ¼¼Áö
	// 2010-09-29 by jskim, SpriteDevice Lost µÇ¾úÀ» ¶§ ±¸Á¶ º¯°æ
	//LPD3DXSPRITE				m_pd3dxSprite;
	// end 2010-09-29 by jskim, SpriteDevice Lost µÇ¾úÀ» ¶§ ±¸Á¶ º¯°æ
	FLOAT						m_fUserCheckTime;
	char						m_strSeverUserNum[128];
	char						m_strMapUserNum[128];

	// remodeling, 2004-03-19 by dhkwon
	CAtumSound* m_pSound;
	CSceneData* m_pScene;
	CAtumDatabase* m_pDatabase;

	BOOL						m_bReadyToGetGuildInfo;

	// 2007-01-07 by bhsohn ±æµå Á¤º¸ µ¿±âÈ­ ¹®Á¦ °ü·Ã Ã³¸®
	BOOL						m_bReadyFieldGameStartOk;

	CINFStageEffect* m_pStageEffect;
	CQuestData* m_pQuestData;
	CFxSystem* m_pFxSystem;
	BOOL						m_bWeb;
	BOOL						m_bRequestEnable;		// ¼­¹ö·Î ¿äÃ» ÇÒ ¼ö ÀÖ´Â »óÅÂÀÎ°¡?
	BOOL						m_bInputItemDone;		// 2007-07-16 by dgwoo Ã³À½ ÁøÀÔ½Ã ¸ðµç ¾ÆÀÌÅÛÀ» ¹Þ¾Ò´Â°¡?
	float						m_fRequestEnableTime;	// ¸Þ½ÃÁö ¾Ö´Ï¸ÞÀÌ¼ÇÀ» À§ÇÑ ½Ã°£ º¯¼ö
	DWORD						m_dwTargetting;			// 2005-03-25 by jschoi - Å¸°ÙÆÃ °ü·Ã 
	CTutorialSystem* m_pTutorial;			// Æ©Åä¸®¾ó ½Ã½ºÅÛ
	CInputManager* m_pInputManager;

	// Ä³¸¯ÅÍ
	BOOL						m_bCharacter;			// TRUE : Ä³¸¯ÅÍ¸ðµå, FLASE: ±â¾î¸ðµå

	// 2005-08-10 by ispark
	// ±×¸²ÀÚ ·»´õ¸µ ÀåÄ¡¿¡ °üÇÑ ¼³Á¤ Ã¼Å© (±×·¡ÇÈ Ä«µå¿¡¼­ Áö¿ø¿¡ ÀÇÇÑ ¹®Á¦)
	int							m_nDephbias;

	// ¾Æ¸Ó Ä®·¯¸¦ ·»´õ¸µÇÏ±â À§ÇÑ º¯¼öÁöÁ¤
	int							m_nArmorNum;		// ³ªÀÇ ¼ÅÆ² Ä®¶ó
	int							m_nArmorNumMax;		// ¾Æ¸Ó°¡ °¡Áú¼ö ÀÖ´Â ÃÖ´ë Ä®¶ó¼ö

	D3DXVECTOR3					m_vShuttleOldPos;		// Àü ÁÂÇ¥

	// 2010. 10. 05 by jskim ¸Ê·Îµù ±¸Á¶ º¯°æ
	CMapLoad* m_pMaploading;
	// end 2010. 10. 05 by jskim ¸Ê·Îµù ±¸Á¶ º¯°æ
#ifdef _DEBUG
	// ÀÌº¥Æ® ¿ÀºêÁ§Æ® ·»´õ
	BOOL						m_bEventObjectRender;	// TURE : °¡´É, FALSE : ºÒ°¡´É
#endif

	// IME°ü·Ã ÈÄº¸¸®½ºÆ® ÀúÀå
	vector<string>	m_vecStingCandidate;
	int				m_nGlabalImageCase;
	char			m_strFont[64];

	// µ¥ÀÌÅÍ¸¦ ÀÏÁ¤ ½Ã°£¿¡¸¸ º¸³»±â À§ÇÑ º¯¼ö
	vectorClientIndex			m_vecCharacterOtherInfo;
	vectorClientIndex			m_vecCharacterOtherInfoRequest;
	vectorClientIndex			m_vecCharacterOtherMove;
	vectorClientIndex			m_vecCharacterOtherRenderInfo;
	vectorClientIndex			m_vecCharacterOtherRenderInfoRequest;
	vectorClientIndex			m_vecMoveTarget;

	vector<INT>					m_vecMapObjectInfo;
	vector<INT>					m_vecMonsterInfo;
	vector<INT>					m_vecSimpleItemInfo;
	vector<INT>					m_vecItemInfo;
	// 2006-07-05 by ispark, °­Á¦ Á¾·á½Ã Ã³¸®ÇÏ´Â ºÎºÐ
	BOOL						m_bShutDown;				// °­Á¦ Á¾·á?
	// 2007-07-10 by bhsohn Åë½Å Å¸ÀÔ ¿¡·¯¿¡ ´ëÇÑ Ã³¸®
	//char						m_strMsgLastError[SIZE_MAX_CHAT_MESSAGE];
	char						m_strMsgLastError[SIZE_MAX_ERROR_CHAT_MESSAGE];

	BOOL						m_bGameShutDown;		// 2006-08-04 by ispark, °ÔÀÓ °­Á¦ Á¾·á
	float						m_fGameShutDownTime;	// 2006-08-04 by ispark, °ÔÀÓ °­Á¦ Á¾·á ½Ã°£

	BOOL						m_bCheckQuickSlotSave;

	// 2007-07-27 by dgwoo ¼¼·Â ¼±ÅÃÀ» ÇÑ À¯ÀúÀÎ°¡?
	BOOL						m_bInfregular;

	vector<MSG_FC_TRADE_INSERT_ITEM>			m_vecTutorialInsertItem;
	vector<MSG_FC_TRADE_UPDATE_ITEM_COUNT>     m_vecTutorialUpdateItem;

	// 2009. 11. 02 by ckPark ÀÎÇÇ´ÏÆ¼ ÇÊµå ÀÎ½ºÅÏ½º ´øÁ¯ ½Ã½ºÅÛ
	CInfinityManager* m_pInfinityManager;		// ÀÎÇÇ´ÏÆ¼ UI°ü·Ã Á¤º¸

	typedef enum ARENASOCKET_TYPE { ARENASOCKET_ARENA, ARENASOCKET_INFINITY, ARENASOCKET_NONE };

	ARENASOCKET_TYPE			m_ArenaSocketType;		// ¾Æ·¹³ª ¼ÒÄÏ Å¸ÀÔ

	BOOL						m_bInfinityMapload;		// ÀÎÇÇ´ÏÆ¼ ¸Ê ·Îµù ÁßÀÎ°¡?(ÀÎÇÇ´ÏÆ¼ ¸Ê ·ÎµùÀº ¼­¹öÀÇ ½ÂÀÎÀÌ ¿Ã¶§±îÁö ´ë±âÇÑ´Ù)

	BOOL						m_bEnterInfinityAllowed;// ÀÎÇÇ´ÏÆ¼ ¸Ê¿¡ ÀÔÀå Çã°¡(¸ðµç ÆÄÆ¼¿øµéÀÌ ¸Ê·ÎµùÀÌ ´Ù Á¾·á‰çÀ»¶§ TRUE)

	BOOL						m_bInfinityRestart;		// ÀÎÇÇ´ÏÆ¼ Æ¨°åÀ»¶§ ÀçÀÔÀåÀÎ°¡?
	BOOL						m_bAddInfinityRestartMessageBox;	// ÀÎÇÇ´ÏÆ¼ ÀçÀÔÀå ¸Þ¼¼Áö ¹Ú½º¸¦ ¶ç¿ï°ÍÀÎ°¡?
	// end 2009. 11. 02 by ckPark ÀÎÇÇ´ÏÆ¼ ÇÊµå ÀÎ½ºÅÏ½º ´øÁ¯ ½Ã½ºÅÛ


	// 2010. 03. 03 by ckPark ÀÎÇÇ´ÏÆ¼ ÇÊµå 2Â÷(ÀÔÀå UIº¯°æ)
	BOOL						m_bWaitInfinityMapLoad;	// ÀÎÇÇ´ÏÆ¼ ¸Ê ·ÎµùÀ» ±â´Ù¸®´Â ÁßÀÎ°¡?

	DWORD						m_nInfinityMapLoadTime;	// ÀÎÇÇ´ÏÆ¼ ¸Ê ·ÎµùÀ» ½ÃÀÛÇÒ ½Ã°£

	MSG_FC_ARENA_POSSIBLE_GAMESTART	m_ArenaStartPacket;	// ÀÎÇÇ´ÏÆ¼ ¸Ê ·Îµù¿¡ »ç¿ëÇÒ ÆÐÅ¶ ÀúÀå
	// end 2010. 03. 03 by ckPark ÀÎÇÇ´ÏÆ¼ ÇÊµå 2Â÷(ÀÔÀå UIº¯°æ)


	// 2010. 03. 23 by ckPark ÀÎÇÇ´ÏÆ¼ ÇÊµå 2Â÷(ÀÎÇÇ´ÏÆ¼ ÇÊµå ÀÔÀå Ä³½¬¾ÆÀÌÅÛ)
	BOOL						m_bInfinityMapLoadedSendEnable;
	BOOL						m_bInfinitySkillSetupOKDone;
	// end 2010. 03. 23 by ckPark ÀÎÇÇ´ÏÆ¼ ÇÊµå 2Â÷(ÀÎÇÇ´ÏÆ¼ ÇÊµå ÀÔÀå Ä³½¬¾ÆÀÌÅÛ)


	// 2009. 11. 23 by jskim ¸®¼Ò½º ·Îµù ±¸Á¶ º¯°æ
	DWORD							m_dwTimeCheck;
	vector<structLoadingGameData*>	m_vecLoadingGameData;
	CMeshInitThread* m_pMeshInitThread;
	structLoadingGameData* m_pLoadingGameData;
	//end 2009. 11. 23 by jskim ¸®¼Ò½º ·Îµù ±¸Á¶ º¯°æ


	//	BOOL						m_bCashShopFlag;		// Ä³½¬¼¥ ÇÃ·¹±×
	BOOL						m_bTestServer;			// Å×½ºÆ® ¼­¹ö ÇÃ·¡±×
	BOOL						m_bDeadByP2PPK;			// PK½Ã Àû À¯´Ö¿¡°Ô Á×¾ú³ª? TRUE : Àû À¯´Ö¿¡°Ô Á×¾ú´Ù.

	MSG_FC_CHARACTER_CASH_PREMIUM_CARD_INFO		m_PremiumCardInfo;

	// 2007-02-12 by bhsohn Æ÷Ä¿½º ÀÒ¾î ¸Ô¾úÀ» ‹šÀÇ ¹®Á¦ Ã³¸®	
	FLOAT						m_fCheckElapsedTime;
	DWORD						m_dwCurrentTime;

	// 2007-02-12 by bhsohn Item ´ÙÁß ¼±ÅÃ Ã³¸®
	// ÆÇ¸Å º¤ÅÍ
	deque<stMultiSelectItem>	m_vecSellMultiSelectItem;
	deque<stMultiSelectItem>	m_vecInvenStoreMultiSelectItem;
	deque<stMultiSelectItem>	m_vecCityStoreMultiSelectItem;
	BOOL						m_bCtrlBtnClick;
	BOOL						m_bStartMultiSell;
	BOOL						m_bStartMultiStore;

	// 2007-02-28 by bhsohn ´ÙÁß ÆÇ¸Å½Ã 0 spi¿¡ ´ëÇÑ Ã³¸®
	stMultiSelectItem			m_struLastSelMultiItem;

	// 2007-04-09 by bhsohn °ü¸®ÀÚ °èÁ¤ Ç¥Ãâ Á¤º¸ Ã³¸®
	char						m_strConnectSeverName[1024];

	// 2007.04.24 by bhsohn China IME Working
	char						m_szReadingString[1024];
	char						m_szImeString[1024];

	// 2007-05-21 by bhsohn China IME Working
	FLOAT						m_fIMETypeShowTime;
	vector<MSG_FC_ARENA_GM_COMMAND_INFO> m_vecTeamInfo;			// GM¸í·É¾î /¾Æ·¹³ª.

	// 2007-07-10 by bhsohn Åë½Å Å¸ÀÔ ¿¡·¯¿¡ ´ëÇÑ Ã³¸®
	int							m_nPreComType;
	int							m_nPreIMComType;

	// 2007-07-24 by bhsohn ³ª·¹ÀÌ¼Ç mp3Ãß°¡
	char				m_chNarrationSound[256];
	// 2009. 01. 22 by ckPark °¢ ¼¼·Âº° ¿ÀÆÛ·¹ÀÌÅÍ MP3 ºÐ¸®
	char				m_chErNarrationSound[256];
	// end 2009. 01. 22 by ckPark °¢ ¼¼·Âº° ¿ÀÆÛ·¹ÀÌÅÍ MP3 ºÐ¸®

	// 2007-08-03 by bhsohn Ä³¸¯ÅÍ ¿ÀºêÁ§Æ® Ã¼Å©½æ º¸³¿
	vector<int>					m_vecSendCharacterOmiInfo;

	// 2007-09-12 by bhsohn 2Â÷ ¾ÏÈ£ ½Ã½ºÅÛ ±¸Çö
	BYTE			m_bIsUseSecondaryPasswordSystem;	// ½Ã½ºÅÛÀ» »ç¿ëÇÒÁö ¿©ºÎ
	BYTE			m_bIsSetSecondaryPassword;		// ¾ÏÈ£¸¦ ¼³Á¤Çß´ÂÁö ¿©ºÎ

	// 2007-10-30 by dgwoo ¾ÆÀÌÅÛ ¸ñ·ÏÀÌ ¿Ã°æ¿ì´Â ¸¶Áö¸·¿¡ ÇÑ¹ø¸¸ ¼ÒÆÃÇØÁØ´Ù.
	BOOL			m_bResortingItem;

	// 2007-11-27 by bhsohn Å×½ºÆ® ¼­¹ö µðÆÄÀÎ
	BOOL			m_bTestServerDefine;

	// 2007-11-20 by bhsohn ¸Ê·Îµù ÇÏ´Â ¹æ½Ä º¯°æ
	stGameStartInfo		m_struGameStartInfo;
	BOOL				m_bGameStartInfo;
	// 2007-11-22 by bhsohn ¾Æ·¹³ª ÅëÇÕ¼­¹ö
	CArenaManager* m_pArenaManager;

	// 2007-12-17 by bhsohn ¾ÆÀÌÅÛ Á¤º¸°¡ ´Ù ¾È¿À¸é °ÔÀÓ ´ë±â»óÅÂ·Î


	// 2007-12-21 by bhsohn ÇÁ·Î±×·¥ ´ÙÁß ¶ô ±¸Á¶ »ý¼º	
	stMultiLockInfo		m_vecLockProtocol;

	// 2008-01-11 by bhsohn 1ºÐµ¿¾È °­Á¦·Î Å¬¶óÀÌ¾ðÆ® ¸ØÃß°Ô ÇÏ¸é Å¬¶óÀÌ¾ðÆ® °­Á¦ Á¾·á
	DWORD				m_dwLastestTickTime;		// Tick¿¡ ¸¶Áö¸·À¸·Î 	

	// 2008-02-15 by bhsohn ³×Æ®¿öÅ© ¼Óµµ Ã¼Å©
	structNetCheckInfo	m_stNetCheckInfo;

	// 2008-06-20 by bhsohn EP3 ¿É¼Ç°ü·Ã Ã³¸®
	float				m_fMouseLockTime;
	BOOL				m_bWndMoving;
	int					m_nOnFriendCount;

	// 2008-07-07 by bhsohn 2Â÷ ÆÐ½º¿öµå È°¼ºÈ­½Ã, ÀÎº¥ ¾È¿­¸®°Ô ÇÔ
	BYTE				m_bSecondPassLock;

	// 2008-08-11 by bhsohn ´Üµ¶À¸·Î ½ÇÇà µÇ°Ô²û
	CSinglePlayGame* m_pSinglePlayGame;

	// 2008-08-18 by bhsohn 1ÃÊ °£°Ý ¾ÆÀÌÅÛ ÀÌµ¿ ½Ã½ºÅÛ 	
	DWORD				m_dwSendTermTime;
	BOOL				m_bSendTerm;

	// 2008-11-13 by bhsohn Á¶ÀÌ½ºÆ½ ÀÛ¾÷
	float				m_fJoyStickCheckTime;
	float				m_fJoyStickFeedbackPlayTime;	// Áøµ¿½Ã°£
	int					m_nJoyStickFeedbackType;		// Áøµ¿Å¸ÀÔ	
	int					m_nJoyContorlLen;
	char				m_chJoystickCtrlList[MAX_JOYCTL_LIST][MAX_PATH];
	// end 2008-11-13 by bhsohn Á¶ÀÌ½ºÆ½ ÀÛ¾÷

	// 2009-01-28 by bhsohn nProtector °ÔÀÓ °¡µå Ãß°¡	
#if defined(DEFINE_USE_GAMEGUARD_NPROTECTOR)	
	CNPGameLib* m_pNpgl;
	float				m_fnProtectorHackCheckTime;
#endif
	// end 2009-01-28 by bhsohn nProtector °ÔÀÓ °¡µå Ãß°¡
	// 2009. 09. 21 by jskim °ÔÀÓ°¡µå XTRAP Àû¿ë(¹èÆ®³²)
#if defined(DEFINE_USE_GAMEGUARD_XTRAP)	
	float				m_fXTrapHackCheckTime;
#endif
	//end 2009. 09. 21 by jskim °ÔÀÓ°¡µå XTRAP Àû¿ë(¹èÆ®³²)

	// 2009-02-13 by bhsohn ¿ùµå ·©Å· ½Ã½ºÅÛ
	CWorldRankManager* m_pWorldRankManager;
	// end 2009-02-13 by bhsohn ¿ùµå ·©Å· ½Ã½ºÅÛ

	// 2009-04-08 by bhsohn ´ÙÁß ¼±ÅÃ½Ã, À¯´ÏÅ© ¹× ÀÎÃ¦Æ® µÈ ¾ÆÀÌÅÛ ÆÇ¸Å½Ã °æ°í ¸Þ½ÃÁö Ãâ·Â ±âÈ¹ ¹®¼­(K0000174)
	stMultiSelectItem		m_stMultiWarningSelItem;
	// end 2009-04-08 by bhsohn ´ÙÁß ¼±ÅÃ½Ã, À¯´ÏÅ© ¹× ÀÎÃ¦Æ® µÈ ¾ÆÀÌÅÛ ÆÇ¸Å½Ã °æ°í ¸Þ½ÃÁö Ãâ·Â ±âÈ¹ ¹®¼­(K0000174)

	// 2009. 06. 09 by ckPark OMI °ÔÀÓ ½ÃÀÛ½Ã Ã¼Å©¼¶ °è»êÇÏµµ·Ï º¯°æ
	BYTE					m_nOMICheckSum[32];
	long					m_nOMIFileSize;
	// end 2009. 06. 09 by ckPark OMI °ÔÀÓ ½ÃÀÛ½Ã Ã¼Å©¼¶ °è»êÇÏµµ·Ï º¯°æ


	// 2010. 03. 12 by ckPark Interface.tex Ã¼Å©¼¶ Ãß°¡
	BYTE					m_nInterfaceCheckSum[32];
	long					m_nInterfaceFileSize;
	// end 2010. 03. 12 by ckPark Interface.tex Ã¼Å©¼¶ Ãß°¡


	// 2009. 11. 03 by ckPark ÅÂ±¹ APEX °ÔÀÓ°¡µå ÀÛ¾÷
#if defined( DEFINE_USE_GAMEGUARD_APEX )
	_FUNC_C_REC				m_pApexfp_rec;
#endif
	// end 2009. 11. 03 by ckPark ÅÂ±¹ APEX °ÔÀÓ°¡µå ÀÛ¾÷
	
	// 2004-11-11 by jschoi 스피드핵 관련 변수

};

#endif