//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHUTTLECHILD_H__D04D8E18_A72E_48CF_A9EE_5FF7DC242111__INCLUDED_)
#define AFX_SHUTTLECHILD_H__D04D8E18_A72E_48CF_A9EE_5FF7DC242111__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ItemInfo.h"
#include "EnemyData.h"
#include "Skill.h"
#include "ClientParty.h"
#include "AtumProtocol.h"



#define WEAR_ITEM_NUMBER			9
#define A_GEAR_GUN_LIMIT_ANGLE_UP		25
#define A_GEAR_GUN_LIMIT_ANGLE_DOWN		110
#define OBSERVE_MAX_QUICK				10

// 2011-06-30 by jhahn  ÀÎÇÇ3Â÷ ½Ã³×¸¶ ÀÓ½ÃÀ§Ä¡
#define INFINITY_THIRD_X_POS		5000
#define INFINITY_THIRD_Z_POS		2500
#define INFINITY_THIRD_Y_POS		1200
// 2011-06-30 by jhahn  ÀÎÇÇ3Â÷ ½Ã³×¸¶ ÀÓ½ÃÀ§Ä¡

// ÀåÂøµÈ ¾ÆÀÌÅÛÀÇ ÆÄ¶÷ÆÑÅÍ °ü¸®
struct WEAR_ITEM_PARAM_FACTOR
{
	// 2009-04-21 by bhsohn ¾ÆÀÌÅÛ DesParamÃß°¡
// 	BYTE		DestParameter1;	
// 	float		ParameterValue1;
// 	BYTE		DestParameter2;	
// 	float		ParameterValue2;
// 	BYTE		DestParameter3;	
// 	float		ParameterValue3;
// 	BYTE		DestParameter4;	
// 	float		ParameterValue4;
	BYTE		ArrDestParameter[SIZE_MAX_DESPARAM_COUNT_IN_ITEM]; // ITEM¿¡ DesParam ÇÊµå °³¼ö 8°³·Î ´Ã¸®±â - 
	float		ArrParameterValue[SIZE_MAX_DESPARAM_COUNT_IN_ITEM]; // ITEM¿¡ DesParam ÇÊµå °³¼ö 8°³·Î ´Ã¸®±â - 
	// end 2009-04-21 by bhsohn ¾ÆÀÌÅÛ DesParamÃß°¡
};

typedef struct _USED_ITEM
{
	LONGLONG	UniqueNumber;
	float		fOverHeatTime;
	float		fOverHeatCheckTime;
	BOOL		bIsOverHeat;
} USED_ITEM;

enum ITEMTYPE {
	ITEM_PRIMARY_WEAPON,
	ITEM_SECONDARY_WEAPON,
	ITEM_CONTROL_SKILL
};

// ¿¬Ãâ½Ã »ç¿ë
enum EVENT_TYPE {
	EVENT_WARP_IN,
	EVENT_WARP_OUT,
	EVENT_CITY_OUTDOOR,
	EVENT_CITY_OUT_MOVE,
	EVENT_GAME_START,
	EVENT_GAME_END
};

typedef struct
{
	MEX_TIMER_EVENT mexTimerEvent;
	float		fTimeflow;
	BOOL		bPause;
} ClientTimer_t;


class CTickTimeProcess
{

public:
	CTickTimeProcess();
	virtual ~CTickTimeProcess();
	virtual void Tick(float fElapsedTime);

public:
	// 2004-10-01 Å¬¶óÀÌ¾ðÆ® Å¸ÀÌ¸Ó °è»ê
	vector<ClientTimer_t>	m_vecClientTimer;				// Å¬¶óÀÌ¾ðÆ® Å¸ÀÌ¸Ó °è»ê
	float					m_fFlowTotalTime;
};

//class CClientParty;
class CCinema;
class CStoreData;
//class CQuestData;
class CShuttleRender;
class CWeaponItemInfo;
class CUnitRender;
class CPkNormalTimer;
class CSkinnedMesh;
class CPetChild;		// 2010-06-15 by shcho&hslee Æê½Ã½ºÅÛ - Æê °ø°Ý Ã³¸®

// 2006-04-04 by ispark
struct INVEN_WEAPON_MESH
{
	CSkinnedMesh* pInvenWeaponMesh;
	int				nMatIndex;
};
typedef vector<INVEN_WEAPON_MESH>		vectINVEN_WEAPON_MESH;

/*
typedef struct
{
	MAP_CHANNEL_INDEX	MapChannel;		// ¿©´ÜÀüÀÌ ÀÏ¾î³ª´Â ¸Ê
	UID32_t				PeerGuildUID;	// »ó´ë ±æµåÀÇ ±æµå ¹øÈ£
} MSG_FC_GUILD_GET_WAR_INFO_OK;


struct MSG_FC_CHARACTER_OBSERVER_INFO
{// 2007-03-27 by dhjin, ¿ÉÀú¹ö¿¡°Ô Á¦°øµÇ´Â Á¤º¸
	ClientIndex_t		ClientIndex;
	SHORT				HP;
	SHORT				DP;
	SHORT				SP;
	SHORT				EP;
	float				CurrentHP;
	float				CurrentDP;
	SHORT				CurrentSP;
	float				CurrentEP;
};
*/

// 2007-03-20 by dgwoo ÀÓ½Ã ¿ÉÀú¹ö ¸ðµå.
struct stOBSERVE
{
	ClientIndex_t	ClientIndex;
	// 2007-03-19 by dgwoo
	CEnemyData* pEnemyData;			// ¿ÉÀú¹ö ¸ðµå½Ã µû¶ó°¡¾ßÇÒ EnemyÀÇ ÁÖ¼Ò.
	D3DXVECTOR3		vObserveUp;
	D3DXVECTOR3		vObserveSide;
	D3DXVECTOR3		vObserveLook;
	D3DXVECTOR3		vObservePos;
	D3DXVECTOR3		vObserveNextPos;
	MSG_FC_CHARACTER_OBSERVER_INFO		ClientInfo;
	stOBSERVE()
	{
		ClientIndex = NULL;
		pEnemyData = NULL;
	}
};
typedef stOBSERVE stOPERATION;

class CGameData;
class CObjectChild;
class PK_TARGET;

class CShuttleChild : public CUnitData
{
public:
	CShuttleChild();
	virtual ~CShuttleChild();
	virtual void Tick(float fElapsedTime);
	virtual void Render();
	virtual HRESULT InitDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();

	// 2009. 08. 27 by ckPark ±×·¡ÇÈ ¸®¼Ò½º º¯°æ ½Ã½ºÅÛ ±¸Çö
	//virtual void CheckAttack(ATTACK_DATA &attackData, BOOL bReset, ITEM* pWeaponITEM=NULL);
	virtual void CheckAttack(ATTACK_DATA& attackData, BOOL bReset, ITEM* pWeaponITEM = NULL, ITEM* pEffectItem = NULL);
	// end 2009. 08. 27 by ckPark ±×·¡ÇÈ ¸®¼Ò½º º¯°æ ½Ã½ºÅÛ ±¸Çö

	virtual USHORT GetShiftWeaponBodyconditionByUnitKind();
	virtual void CreateSecondaryShieldDamage(D3DXVECTOR3 vCollPos);

public:

	char m_pad1[8];
	char m_pad2[8];
	CGameData* m_pGameData;
	CStoreData* m_pStoreData;
	CUnitRender* m_pRender;							// ShuttleÀÇ Rendering Ã³¸®
														// 2007-03-20 by dgwoo ÀÓ½Ã ¿ÉÀú¹ö ¸ðµå.
	stOBSERVE			m_stObserve;						// ¿ÉÀú¹öÇÒ À¯ÀúÀÇ Á¤º¸.and °üÀü.
	BOOL				m_bObserve;							// ¿ÉÀú¹ö ¸ðµåÀÎ°¡?
	ClientIndex_t		m_ObserveQuick[OBSERVE_MAX_QUICK];	// ¿ÉÀú¹ö ´ÜÃàÅ° 1~0 ¹ø±îÁö ÀÌ¸ç °¢ ÀÎµ¦½º ¹øÈ£¸¦ °¡Áö°íÀÖ´Â´Ù.
	//char		m_pad3[6];
	
	D3DXVECTOR3			m_vTargetPosition;
	D3DXVECTOR3			m_vGroundTargetPos;					// Áö»ó Æø°Ý½Ã Å¸°Ù Æ÷Áö¼Ç
	D3DXVECTOR3			m_vBasisUp;							// Basis Up Vector
	FLOAT				m_fSideRate;						// ÁÂ¿ì È¸Àü ¼Óµµ Á¶Àý ¹× ±â¿ïÀÓ
	FLOAT				m_fSideCheckRate;					// ÁÂ¿ì È¸Àü ¼Óµµ ¹× ±â¿ïÀÓ Á¶Àýº¯¼ö(Âø·ú½Ã ¼öÆòÀ» ¸¶Ãß±â À§ÇØ)
	FLOAT				m_fHeightRate;						// °íµµ Á¶Àý º¯¼ö
	FLOAT				m_fLRVelRate;						// ÁÂ¿ì °¡¼Óµµ¿¡ ¿µÇâÀ» ÁÙ º¯¼ö
	FLOAT				m_fOldUpRate;						// ÀÌÀü ¾÷º¤ÅÍ¸¦ ±â·ÏÇÏ¿© ºÎµå·´°Ô ±â¿ïÀÎ´Ù(ÁÂ¿ì ÀÌµ¿ ±â¿ïÀÓ°ú È¸Àü ±â¿ïÀÓ Á¶Àý)

	FLOAT				m_fShuttleSpeed;					// ¼ÅÆ²¼Óµµ º¯¼ö (¿£Áø¿¡ ÁÂ¿ìµÈ´Ù)		
	FLOAT				m_fShuttleSpeedMax;					// ¼ÅÆ²¼Óµµ ÃÖ´ë (¿£Áø¿¡ ÁÂ¿ìµÈ´Ù)		
	FLOAT				m_fShuttleSpeedMin;					// ¼ÅÆ²¼Óµµ ÃÖ¼Ò (¿£Áø¿¡ ÁÂ¿ìµÈ´Ù)		
	FLOAT				m_fShuttleSpeedBoosterOn;			// ¼ÅÆ²¼Óµµ ºÎ½ºÅÍ »ç¿ë (¿£Áø¿¡ ÁÂ¿ìµÈ´Ù)
	FLOAT				m_fShuttleGroundSpeed;				// ¼ÅÆ²¼Óµµ ¶¥ ¼Ó·Â (¿£Áø¿¡ ÁÂ¿ìµÈ´Ù)
	FLOAT				m_fShuttleGroundSpeedMax;			// ¼ÅÆ²¼Óµµ ¶¥ ¼Ó·Â ÃÖ´ë (¿£Áø¿¡ ÁÂ¿ìµÈ´Ù) // 2005-11-26 by ispark
	BYTE				m_bySpeedPenalty;					// ¿£Áø¼±È¸°¡¼Ó·Â	// 2005-08-16 by ispark

	FLOAT				m_fRealShuttleSpeedMax;				// ½ÇÁ¦ ¼ÅÆ² ÃÖ´ë ¼Ó·Â
	FLOAT				m_fRealShuttleSpeedMin;				// ½ÇÁ¦ ¼ÅÆ² ÃÖ¼Ò ¼Ó·Â
	FLOAT				m_fRealShuttleSpeedBoosterOn;		// ½ÇÁ¦ ¼ÅÆ² ºÎ½ºÅÍ ¼Ó·Â

	FLOAT				m_fBoosterCheckTime;				// ºÎ½ºÅÍ »ç¿ë Ã¼Å© Å¸ÀÓ
	FLOAT				m_fChangeBodyForBoosterCheckTime;	// ºÎ½ºÅÍ °ü·Ã Àü¼Û Ã¼Å© Å¸ÀÓ
	INT					m_nShuttleBoosterState;				// ºÎ½ºÅÍ¸¦ Å°±â À§ÇÑ ´õºíÅ¬¸¯Ã¼Å© »óÅÂ
	INT					m_nShuttleStopState;				// °øÁßºÎ¾çÀ» À§ÇÑ ´õºíÅ¬¸¯Ã¼Å© »óÅÂ

	INT					m_nFBDir;							// ¾ÕµÚ ¹æÇâ
	INT					m_nLRDir;							// ÁÂ¿ì ¹æÇâ
	INT					m_nSideRotateDir;					// ÁÂ¿ì ¹æÇâ

	CHARACTER			m_myShuttleInfo;					// Shuttle ÀÇ Á¤º¸
	FLOAT				m_fDefenseTotal;					// Shuttle ÀÇ Total ¹æ¾î·Â
	FLOAT				m_fDefenseForItem;					// Shuttle ÀÇ Item ¹æ¾î·Â
	FLOAT				m_fDefenseForSkill;					// Shuttle ÀÇ Skill ¹æ¾î·Â
	FLOAT				m_fDefenseForShuttle;				// Shuttle ÀÇ ±âÃ¼ ¹æ¾î·Â
	FLOAT				m_fTransportTotal;					// Shuttle ÀÇ Total Áß·®
	FLOAT				m_fTransportCurrent;				// Shuttle ÀÇ Current Áß·®

	BYTE				m_bCollObjectCheck;					// Ãæµ¹ Ã¼Å©ÇØ¾ß ÇÏ´Â°¡?(¿ÀºêÁ§Æ®, ¸ó½ºÅÍ, Å¸ Ä³¸¯ÅÍ)
	BYTE				m_bCollMonsterCheck;				// Ãæµ¹ Ã¼Å©ÇØ¾ß ÇÏ´Â°¡?(¿ÀºêÁ§Æ®, ¸ó½ºÅÍ, Å¸ Ä³¸¯ÅÍ)
	BYTE				m_bCollShuttleCheck;				// Ãæµ¹ Ã¼Å©ÇØ¾ß ÇÏ´Â°¡?(¿ÀºêÁ§Æ®, ¸ó½ºÅÍ, Å¸ Ä³¸¯ÅÍ)
	BYTE				m_bCollAttackCheck;					// Attack ½Ã Ãæµ¹ Ã¼Å©ÇØ¾ß ÇÏ´Â°¡?(¿ÀºêÁ§Æ®, ¸ó½ºÅÍ, Å¸ Ä³¸¯ÅÍ)

	FLOAT				m_fExpPer;							// °æÇèÄ¡ ÆÛ¼¾Æ¼Áö 
	/////////////// »ó´ë Á¤º¸ ¿äÃ»À» À§ÇÑ ÇÃ·¡±×¿Í ÀÎµ¦½º º¯¼ö ////////
	BOOL				m_bGetOtherInfo;
	FLOAT				m_fGetOtherInfoCheckTime;
	INT					m_nGetOtherIndex;
	///////////////// Ä³¸¯°£ Ãæµ¹ Ã³¸® À§ÇÑ º¯¼ö //////////////////////
	BOOL				m_bColl;							// ¸ó½ºÅÍ ¹× Å¸ Ä³¸¯ÅÍ¿ÍÀÇ Ãæµ¹
	D3DXVECTOR3			m_vCollPos;							// Ãæµ¹ Æ÷Áö¼Ç
	FLOAT				m_fCheckCollTime;
	INT					m_nBooster;							// Booster State
	INT					m_nHyperBooster;					// 2006-10-11 by ispark, ÇÏÀÌÆÛ ºÎ½ºÅÍ
	BOOL				m_bOnObject;						// ¼ÅÆ² ¾Æ·¡,À§¿¡ ¿ÀºêÁ§Æ®°¡ ÀÖ´ÂÁö
	FLOAT				m_fAxisRate;						// ¼ÅÆ²ÀÇ ±â¿ïÀÓ Á¤µµ 
	INT					m_nUDState;							// °íÀú Á¶Àý »óÅÂ 
	///////////////// ÀÚµ¿ °íµµ ¼ÂÆÃ  /////////////////////
	D3DXVECTOR3			m_vOldPos;

	///////////////// Party  /////////////////////
	CClientParty* m_pClientParty;						// ÆÄÆ¼ °ü·Ã


	BYTE				m_bCheckMove;						// ÀÌµ¿ Å¸ÀÔ °áÁ¤	
															// 0:¸ø°¡´Â Áö¿ª, 1:2Â÷°¨¼Ó, 2:1Â÷°¨¼Ó, 3:°¡´ÂÁö¿ª, 4:ÀÏ¹ÝºñÇàÁö¿ª
															// 0~3Àº Ãæµ¹½Ã¿¡ Ã¼Å©µÇ°í 4´Â Ãæµ¹ÀÌ ¹ß»ýÇÏÁö ¾ÊÀ½À» ¶æÇÑ´Ù
	BOOL				m_bIsWater;							// ÇöÀç ºñÇàÁßÀÎ°÷ÀÌ ¹°ÀÎ°¡

	BOOL				m_bCollMap;							// ¸Ê°úÀÇ Ãæµ¹ ÆÇ´Ü º¯¼ö
	FLOAT				m_fCollMapCheckTime;				// ¸Ê°úÀÇ Ãæµ¹½Ã Æ¨°ÜÁ® ¿Ã¶ó°¡´Â ½Ã°£À» ÃøÁ¤ÇÒ º¯¼ö

	D3DXVECTOR3			m_vNormal;							// ÇöÀç ¸ÊÀÇ ³ë¸»º¤ÅÍ

	// Primary, Second, Skill ÀÇ ÇÑ¹ø¿¡ ¹ß»çµÇ´Â ¾ç(Amount), ÇÑ¹ø¿¡ ¹ß»çµÇ°í ´ÙÀ½ ÅÏ±îÁöÀÇ µô·¹ÀÌ(RATime), µô·¹ÀÌ°¡ Àû¿ëµÇ¸é¼­ ¹ß»çµÇ´Â ÃÖ´ë È½¼ö(Cont)

	////////////////////////////////////////////////////////////////////////////////////
	//							1Çü 2Çü Weapon °ü·Ã º¯¼öµé							  //
	////////////////////////////////////////////////////////////////////////////////////
	BYTE				m_bAttackMode;						// °ø°Ý ¸ðµå-0:ÀÏ¹Ý 1:Æø°Ý 2:½ÃÁî
	BOOL				m_bAttack;							// °ø°ÝÀÌ °¡´ÉÇÑ°¡. TRUE : °ø°Ý°¡´É FALSE : °ø°ÝºÒ°¡´É.

	//////////////////////////  Skill Test Key Input (¸ÅÅ©·Î) //////////////////////////
	FLOAT				m_fSkillMoveTime;					// ÀÌµ¿ ¸¶ÀÎµå ÄÁÆ®·Ñ½Ã Å¸ÀÓ Ã¼Å©
	BOOL				m_bSkillMoveIsUse;					// ÀÌµ¿¿¡ °ü·ÃµÈ ¸¶ÀÎµå ÄÁÆ®·Ñ »ç¿ë À¯¹«
	BOOL				m_bIsCameraPattern;					// Ä«¸Þ¶ó ÆÐÅÏÀ» »ç¿ëÇØ ÀÌµ¿ÁßÀÎ°¡? 2004.06.28 jschoi
	BOOL				m_bSkillMoveType;					// ¸¶ÀÎµå ÄÁÆ®·Ñ¹ßµ¿½Ã Move Type Å×½ºÆ®(µµ´Â¸ð¾ç Á¤ÀÇ)
	D3DXVECTOR3			m_vSkillMoveVel;					// È¸Àü ¸¶ÀÎµå ÄÁÆ®·Ñ ¹ßµ¿½Ã ¹æÇâÀÌ ¼ÂÆÃµÇ¾îÁú º¯¼ö(ÀÌÀü ¹æÇâÀ» ±â¾ïÇÔ)

	BOOL				m_bTurnCamera;
	CAtumData* m_pTarget;							// ÇöÀç °ø°ÝÇÏ°í ÀÖ´Â Å¸°Ù Æ÷ÀÎÅÍ
	CAtumData* m_pOrderTarget;						// Å¸°Ù Áö½Ã½Ã Ç¥½Ã·Î °¡¸£Å°°Ô µÇ´Â Æ÷ÀÎÅÍ
	UINT				m_nCurrentPatternNumber;			// ÇöÀç »ç¿ëÁßÀÎ ÆÐÅÏ ¹øÈ£
	BYTE				m_bMoveGroundType;					// ÁöÇü¿¡ ¼ÂÆÃµÈ ÀÌµ¿ Å¸ÀÔ
	////////////////////////////////////////////////////////////////////////////////////
	BYTE				m_bEffectGround;					// 0:°øÁß  1:¶¥À§³·°Ô 2:¹°À§³·°Ô

	///////////////// DT ÇüÀ» À§ÇÑ °øÁß¿¡ ¶° ÀÖ´Â »óÅÂÀÎÁö /////////////////////
	BOOL				m_bIsAir;
	FLOAT				m_fDTEventCheckTime;				// DT Çü ÀÌº¥Æ® Ã¼Å© Å¸ÀÓ
	////////////////////////////////////////////////////////////////////////////////////
	FLOAT				m_fNumpad0keyTime;
	FLOAT				m_fCancelSkillCheckTime;
	BYTE				m_bMoveInputType;					// ÀÌµ¿ Å°Á¶ÀÛ ¹æ¹ý	0:Auto 1:Normal
	FLOAT				m_fMouseLRMoveRate;					// ¸¶¿ì½º ÁÂ, ¿ì È¸Àü ºñÀ²
	FLOAT				m_fMouseUDMoveRate;					// ¸¶¿ì½º »ó, ÇÏ È¸Àü ºñÀ²

	char				m_strChatPToP[MAX_CHAT_PTOP_CONT][SIZE_MAX_CHARACTER_NAME];
	BYTE				m_bCurPToPPos;
	BYTE				m_bOldPToPPos;

	BOOL				m_bRButtonState;					// ¸¶¿ì½º ¿ìÃø ¹öÆ° »óÅÂ
	BOOL				m_bLButtonState;					// ¸¶¿ì½º ÁÂÃø ¹öÆ° »óÅÂ
	BOOL				m_bMButtonState;					// ¸¶¿ì½º ÈÙ¹öÆ° »óÅÂ
	BOOL				m_bUpButtonState;					// Å°º¸µå UP ¹öÆ° »óÅÂ
	BOOL				m_bDownButtonState;					// Å°º¸µå DOWN ¹öÆ° »óÅÂ
	BOOL				m_bLeftButtonState;					// Å°º¸µå LEFT ¹öÆ° »óÅÂ
	BOOL				m_bRightButtonState;				// Å°º¸µå RIGHT ¹öÆ° »óÅÂ
	BOOL				m_bSkillGoMove;						// ¿òÁ÷ÀÏ¼ö ÀÖ´Â »óÅÂÀÎ°¡? T:¿òÁ÷ÀÓ, F:¸ø¿òÁ÷ÀÓ.

	POINT				m_pOldMousePoint;

	BOOL				m_bUseBooster;						// ºÎ½ºÅÍ »ç¿ëÈÄ MaxSpeed·Î µ¹¾Æ¿Ã¶§±îÁö ºÎ½ºÅÍ »ç¿ë±ÝÁö
	BOOL				m_bReChargeBURN;
	FLOAT				m_fBURN;
	FLOAT				m_fCurrentBURN;

	POINT				m_ptOldPoint;

	BOOL				m_bFirstStart;						// ÃÖÃÊ ½ÃÀÛ½Ã Âø·ú»óÅÂÀÏ¶§ÀÇ ¼ÂÆÃÀ» À§ÇÑ º¯¼ö(ÇÑ¹ø TickÀ» ¼öÇàÇÏÁö ¾Ê±â À§ÇÔ)

	BOOL				m_bAutoLockon;						// ÀÚµ¿ °­Á¦ ¶ô¿Â 
	BOOL				m_bAutoHeightControl;				// °­Á¦ ¶ô¿Â µÈ ¸ó½ºÅÍ¿¡ ÀÚµ¿ °íµµ Á¶Àý
//	BOOL				m_bEventReady;						// ÀÌº¥Æ®±â´Ù¸®´ÂÁß,  »èÁ¦ÇØµµ µÉµí.
	FLOAT				m_fWeaponMaxDistance;				// 1 ~ 2 Çü ¹«±âÁß »çÁ¤°Å¸®¸¦ Ã¼Å© - °¡Àå ±ä °Å¸®ÀÇ °ª
	INT					m_nMonsterCount;					// ÃÊº¸ ¼ö·Ã¸ðµå¿¡¼­ÀÇ ¸ó½ºÅÍ ¼ö¸¦ Ç¥½ÃÇÏ±â À§ÇÑ º¯¼ö
//	FLOAT				m_fEventCheckTime;					// ÀÌº¥Æ® Ã¼Å© Å¸ÀÓ

	FLOAT				m_fNextHP;							// ¼­¼­È÷ HP°¡ È¸º¹ÇÏ´Â°ÍÀ» º¸¿©ÁÖ±â À§ÇÑ º¯¼ö(´ÙÀ½ HP)
	FLOAT				m_fNextSP;							// ¼­¼­È÷ SP°¡ È¸º¹ÇÏ´Â°ÍÀ» º¸¿©ÁÖ±â À§ÇÑ º¯¼ö(´ÙÀ½ SP)
	FLOAT				m_fNextEP;							// ¼­¼­È÷ EP°¡ È¸º¹ÇÏ´Â°ÍÀ» º¸¿©ÁÖ±â À§ÇÑ º¯¼ö(´ÙÀ½ EP)
	FLOAT				m_fNextDP;							// ¼­¼­È÷ EP°¡ È¸º¹ÇÏ´Â°ÍÀ» º¸¿©ÁÖ±â À§ÇÑ º¯¼ö(´ÙÀ½ EP)
	FLOAT				m_fNextHPRate;						// ¼­¼­È÷ HP°¡ È¸º¹ÇÏ´Â°ÍÀ» º¸¿©ÁÖ±â À§ÇÑ º¯¼ö(È¸º¹ ¼Óµµ)
	FLOAT				m_fNextSPRate;						// ¼­¼­È÷ SP°¡ È¸º¹ÇÏ´Â°ÍÀ» º¸¿©ÁÖ±â À§ÇÑ º¯¼ö(È¸º¹ ¼Óµµ)
	FLOAT				m_fNextEPRate;						// ¼­¼­È÷ EP°¡ È¸º¹ÇÏ´Â°ÍÀ» º¸¿©ÁÖ±â À§ÇÑ º¯¼ö(È¸º¹ ¼Óµµ)
	FLOAT				m_fNextDPRate;						// ¼­¼­È÷ EP°¡ È¸º¹ÇÏ´Â°ÍÀ» º¸¿©ÁÖ±â À§ÇÑ º¯¼ö(È¸º¹ ¼Óµµ)

	BOOL				m_bIsSetFlighting;					// ºñÇà ÆòÇüÀ» ¸¶Ãß°í ÀÖ´Â ÁßÀÎ°¡?
	FLOAT				m_fCollSendDamageCheckTime;			// ÁöÇüÃæµ¹½Ã µ¥¹ÌÁö Àü¼ÛÀ» À§ÇÑ Å¸ÀÓ Á¶Àý

	D3DXVECTOR3			m_vMouseDir;						// ¸¶¿ì½º ¹æÇâ º¤ÅÍ
	D3DXVECTOR3			m_vMousePos;						// 2010-06-15 by shcho&hslee Æê½Ã½ºÅÛ - ¸¶¿ì½º À§Ä¡
	FLOAT				m_fMouseRate;						// ¸¶¿ì½º °¨µµ Á¶Àýº¯¼ö(È¸Àü¼Óµµ ¿µÇâ)
	POINT				m_pt;								// ¸¶¿ì½º ÁÂÇ¥
	POINT				m_ptDir;							// ¸¶¿ì½º ¹æÇâ ÁÂÇ¥
	POINT				m_ptDirOld;							// ¸¶¿ì½º ¹æÇâ ÁÂÇ¥ ¿Ãµå
	POINT				m_ptMove;							// ¸¶¿ì½º ÀÌµ¿ ÁÂÇ¥

	vector<USED_ITEM*>				m_vecUsedItem;			// »ç¿ëÇÏ´Ù°¡ ³»¸° ¾Æ´ÏÅÛ (1Çü,2Çü,½ºÅ³)

	D3DXVECTOR3			m_vCollCenter;						// Ãæµ¹ÀÌ ¹ß»ýÇÑ ¿ÀºêÁ§Æ®ÀÇ Áß½ÉÁÂÇ¥
	BYTE				m_bBeginnerQuestDegree;				// ÃÊº¸ Äù½ºÆ® ÁøÇà ´Ü°è º¯¼ö

	BOOL				m_bMouseLock;						// ¸¶¿ì½º ¶ô ¸ðµå ÀüÈ¯

	BOOL				m_bOrderMove;						// Ä«¸Þ¶ó ÄÁÆ®·Ñµî°ú °°Àº °­Á¦ ÀÌµ¿ ¸ðµå½Ã ÀÔ·Â Àû¿ë ÇÏÁö ¾ÊÀ½
	BYTE				m_bOrderMoveType;					// °­Á¦ ÀÌµ¿ Å¸ÀÔ
	D3DXVECTOR3			m_vTargetPos;						// Å¸°ÙÀ¸·Î ÀÌµ¿ÇÏ±â À§ÇÑ ÁÂÇ¥(ÀÚµ¿ÀÌµ¿¿¡ ¾²ÀÎ´Ù)
	D3DXVECTOR3			m_vTargetVel;						// Å¸°ÙÀ¸·Î ÀÌµ¿ÇÏ¿© ¹Ù¶óº¼ ¹æÇâ(ÀÚµ¿ÀÌµ¿¿¡ ¾²ÀÎ´Ù)
	FLOAT				m_fLandingCheckTime;				// ·£µù °­Á¦ ÀÌµ¿½Ã Àû¿ëÇÒ Âø·ú ¼Óµµ
	FLOAT				m_fLandingDist;						// ·£µù °­Á¦ ÀÌµ¿½Ã Àû¿ëÇÒ Âø·úÀå±îÁöÀÇ °Å¸®
	FLOAT				m_fRasingCheckTime;					// Take_Off ½Ã ÀÏÁ¤½Ã°£ »ó½ÂÀ» À§ÇÑ º¯¼ö

	// 2010-06-15 by shcho&hslee Æê½Ã½ºÅÛ - ÀåÂøÇ° ÃÖ´ë °³¼ö°ª º¯°æ.
	WEAR_ITEM_PARAM_FACTOR	m_wearItemParamFactor[MAX_EQUIP_POS];
	// 2010. 04. 21 by jskim ½Å±Ô ·°Å° ¸Ó½Å ±¸Çö
	WEAR_ITEM_PARAM_FACTOR	m_wearPreRareItemParamFactor[MAX_EQUIP_POS];
	WEAR_ITEM_PARAM_FACTOR	m_wearSufRareItemParamFactor[MAX_EQUIP_POS];
	//end 2010. 04. 21 by jskim ½Å±Ô ·°Å° ¸Ó½Å ±¸Çö

	/*
	WEAR_ITEM_PARAM_FACTOR	m_wearItemParamFactor[WEAR_ITEM_NUMBER];
	// 2010. 04. 21 by jskim ½Å±Ô ·°Å° ¸Ó½Å ±¸Çö
	WEAR_ITEM_PARAM_FACTOR	m_wearPreRareItemParamFactor[WEAR_ITEM_NUMBER];
	WEAR_ITEM_PARAM_FACTOR	m_wearSufRareItemParamFactor[WEAR_ITEM_NUMBER];
	//end 2010. 04. 21 by jskim ½Å±Ô ·°Å° ¸Ó½Å ±¸Çö
	*/
	// End 2010-06-15 by shcho&hslee Æê½Ã½ºÅÛ - ÀåÂøÇ° ÃÖ´ë °³¼ö°ª º¯°æ.

	CSkill* m_pSkill;

	// 2004-06-03, ydkim, Âø·úÀå Å¸ÀÏ´ÜÀ§ ÀÌµ¿ °ü·Ã  
	BOOL                m_bAniKeyBlock;						// ¾Ö´Ï¸ÞÀÌ¼ÇÁß Å°ºí·Ï 
	BOOL                m_bAgearPortflag;					// A±â¾î °ü·Ã ÀÌº¥Æ®Áö¿ª »óÅÂÈ®ÀÎ 
	BOOL				m_bLandingOldCamtypeFPS;			// ·£µùÀü Ä·Å¸ÀÔÀÌ 1ÀÎÄªÀÌ¿´³ª 

	DWORD				m_dwLastAttackTick;

	float               m_fAniFlag;							// ¾Ö´Ï¸ÞÀÌ¼Ç »óÅÂÈ®ÀÎ 		
	float				m_fKeyboardInputTimer;				// Å°º¸µå ÀÔ·Â Å¸ÀÌ¸Ó
	float               m_fMoveFrameTimer;                  // ÃÊ´ç ¿òÁ÷ÀÌ´Â ÇÁ·¹ÀÓ¼ö
	float               m_fFrameLerp;                       // ÇÁ·¹ÀÓ ·¯ÇÁ°ª 
	float				m_fAnimationMoveTimer;				// ¾Ö´Ï¸Þ¿¡¼Ç Áß ÇÁ·¹ÀÓ Å¸ÀÓ 
	float				m_fSinMove;							// Âø·ú½Ã ºÎµå·´°Ô

//	POINT				m_pAutoTargetOldMousePos;			// ½ÃÁîÇü¸ðµå¿¡¼­ »ç¿ëµÉ ÀÚµ¿Á¶ÁØ ¸ðµå½Ã ¸¶¿ì½ºÆ÷ÀÎÆ® ÀÌµ¿ Æ÷Áö¼Ç 


	D3DXVECTOR3         m_vMyOldPos;						// ¹æÇâÅ°¸¦ ´©¸£±âÀü ³ªÀÇ À§Ä¡ 
	D3DXVECTOR3			m_vAniFrame;						// ÇÁ·¹ÀÓ ¸ñÇ¥°ª 
	BOOL				m_bReflexionKeyBlock;				// º®À» ¸¸³µÀ»¶§ Å°ºí·° 

	CCinema* m_pCinemaUnitPattern;				// À¯´Ö(½ºÅ³,¿¬Ãâ) ÆÐÅÏ
	CCinema* m_pCinemaCamera;					// Ä«¸Þ¶ó ÆÐÅÏ

	EVENT_TYPE			m_nEventType;

	float				m_fWarpOutDistance;					// ¿öÇÁ ÀÌº¥Æ® ¿ÀºêÁ§Æ® »çÀÌ °Å¸®(¿öÇÁ ¾Æ¿ô½Ã)
	D3DXVECTOR3			m_vWarpOutPosition;					// ¿öÇÁ ¾Æ¿ô½Ã ÃÖÃÊ À§Ä¡ 

	CObjectChild* m_pCurrentObjEvent;					// m_nEventType == EVENT_WARP_IN ½Ã¿¡ »ç¿ë
	CObjectChild* m_pCurrentObjEventOld;
	CWeaponItemInfo* m_pPrimaryWeapon;
	CWeaponItemInfo* m_pSecondaryWeapon;

	MSG_FC_GUILD_GET_WAR_INFO_OK* m_pGuildWarInfo;		// ¿©´ÜÀü½Ã¿¡ ÀÌ Á¤º¸°¡ ¼¼ÆÃµÈ´Ù.
	USHORT				m_nOldMapIndex;

	// Å¬¶óÀÌ¾ðÆ® Tick Time °è»ê
	CTickTimeProcess    m_timeProcess;

	//#ifdef _DEBUG
	//	int					m_nDebugWarpMove;
	//	int					m_nDebugSendPacketMove;
	//	float				m_fDebugWarpCheckTime;
	//	float				m_fDebugSendCheckTime;
	//#endif
	//	float				m_fMissileFireTime;

		// 2005-02-15 by jschoi  -  PK Delay Timer
	CPkNormalTimer* m_pPkNormalTimer;
	BOOL				m_bCtrlKey;		// CtrlKey »óÅÂ º¯¼ö TRUE : Ctrl Down »óÅÂ, FALSE : Ctrl Up »óÅÂ

	BYTE				m_byCityWarTeamType;	// µµ½ÃÁ¡·ÉÀü »óÅÂ º¯¼ö
	float				m_fTempGravity;			// Áß·Â °ª 
	float				m_fRollTime;			// ·Ñ¸µ ½Ã½ºÅÛ ½ÃÀÛ ½Ã°£			// 2005-07-11 by ispark
	BOOL				m_bRollUsed;			// 2005-07-14 by ispark ·Ñ¸µ »ç¿ëÁßÀÎ°¡

	// // 2005-07-21 by ydkim 
	int					m_nEventTypeAirPort;	// Âø·úÀå Âø·ú ÆÐÅÏÅ¸ÀÔ
	int					m_nEventIndex;
	BOOL				m_bKeyBlock;
	BOOL				m_bWarpLink;			// Âø·úÀå ¿öÇÁ ¿¬°á ÆÐÅÏ
	BOOL				m_bUnitStop;
	BOOL				m_bPenaltyUnitStop;		// 2005-08-09 by ispark À¯´ÖÁ¤Áö Æä³ÎÆ¼ - Ãâ¹ß½Ã Àû¿ë
	BOOL				m_bMouseMoveLock;		// ¸¶¿ì½º ÀÌµ¿ ¸·À½ // 2005-08-09 by ispark

	CItemInfo* m_pRadarItemInfo;		// 2005-08-16 by ispark ·¹ÀÌ´õ ¾ÆÀÌÅÛ Á¤º¸

	// 2005-10-10 by ispark - PK Å¸°Ù
	vector<PK_TARGET*>	m_vecPKTarget;
	int					m_bPKState;				// TRUE : ¶ô¿Â, FALSE : ¾ð¶ô¿Â

	BOOL				m_bLandedMove;			// LandedÈÄ Å°·Î ±â¾î¸¦ ¿òÁ÷ÀÏ ¼ö ÀÖ´Â »óÅÂ
	BOOL				m_bSkipPattern;			// ÆÐÅÏ ½ºÅµ

	// 2008-08-22 by bhsohn EP3 ÀÎº¥Åä¸® Ã³¸®
//	BOOL				m_bInvenRender;
//	D3DXMATRIX			m_pMatInven;
//	D3DXMATRIX			m_pMatInvenWeaponSetPosition[4];
//	D3DXMATRIX			m_pMatInvenWeaponOrgPosition[4];// 2006-01-03 by ispark, ¹«±â Æ÷Áö¼Ç ¸ÞÆ®¸¯½º

	float				m_fAdvanceTime;			// ¸Þ¸ð¸® ÇÙ Ã¼Å© Advance

	// 2009-03-16 by bhsohn A±â¾î Æ÷´ë ¹æÇâ ÇÁ·ÎÅäÄÝ ÃÖ¼ÒÈ­
	DWORD				m_dwCheckTimeSendMoveVel;
	// end 2009-03-16 by bhsohn A±â¾î Æ÷´ë ¹æÇâ ÇÁ·ÎÅäÄÝ ÃÖ¼ÒÈ­

private:
	BOOL				m_bOperation;						// °üÀü ¸ðµåÀÎ°¡?

	BOOL				m_bWarpGateZone;
	BOOL				m_bTargetChange;
	BOOL				m_bRenderInven;

	float				m_fCurrentAngle;		// YÃà ¼±È¸ °¢µµ   // 2005.6.13 by dhkwon - ¼±È¸ °¢µµ °¡¼Ó·Â
	float				m_fCurrentSideRate;		// XÃà ¼±È¸ °¢µµ

	// 2005-07-05 by ispark
	// ·Ñ¸µ ½Ã½ºÅÛ Å° Ã³¸®
	BOOL				m_bKeyDownA;			// A ÁÂÃø ·Ñ¸µ
	BOOL				m_bKeyDownD;			// D ¿ìÃø ·Ñ¸µ
	BOOL				m_bKeyDownACheck;		// A ÁÂÃø ·Ñ¸µ »ç¿ëÇã°¡ Ã¼Å©
	BOOL				m_bKeyDownDCheck;		// D ¿ìÃø ·Ñ¸µ »ç¿ëÇã°¡ Ã¼Å©
	// 2005-09-26 by ispark
	// ·Ñ¸µ º¯Çü(A, DÅ¬¸¯½Ã ÁÂ¿ì ÀÌµ¿ ºÎÈ°, ´õºíÅ¬¸¯½Ã ·Ñ¸µ)
	BOOL				m_bKeyDownADouble;		// A ´õºíÅ¬¸¯
	BOOL				m_bKeyDownDDouble;		// D ´õºíÅ¬¸¯
	float				m_fADoubleKeyTime;
	float				m_fDDoubleKeyTime;

	float				m_fRollMessageTime;		// ·Ñ¸µ ¸Þ¼¼Áö º¸³»´Â ½Ã°£ Ã¼Å©
	float				m_fRollAngle;			// ·Ñ¸µ È¸Àü °¢µµ
	float				m_fRollLength;			// ·Ñ¸µ ÁÂ¿ì ÀÌµ¿ °Å¸® Ã¼Å©
	float				m_fRollDownSpeed;		// ·Ñ¸µ ´Ù¿î ½ºÇÇµå
	D3DXVECTOR3			m_vRollStart;			// ·Ñ¸µ ½ÃÀÛÇÑ ÁÂÇ¥
	D3DXVECTOR3			m_vRollOldPos;			// ·Ñ¸µ ÁÂÇ¥ ÀÌµ¿½Ã Àü ÁÂÇ¥

	BOOL				m_bMissileWarning;		// Àû 2Çü¹«±â °ø°ÝÁß
	BOOL				m_bSkillMissileWarning;	// ½ºÅ³·Î ÀÎÇÑ ¹Ì»çÀÏ °æ°í À¯¹«
	int					m_nMissileCount;		// Àû 2Çü¹«±â °¹¼ö

	BOOL				m_bLandingField;		// Âø·úÀåÀÎ°¡ (A±â¾î°¡ Âø·úÁß¿¡´Â ¾Æ¹« Ã³¸® ¾ÈÇÏ±â À§ÇØ¼­)

	// ÀÎº¥Åä¸®
//	LPDIRECT3DVERTEXBUFFER9 m_pMirrorVB;
	LPDIRECT3DTEXTURE9      m_pTexturesBackInven;

	float				m_fRotationX;
	float				m_fRotationY;
	float				m_fRotationZ;
	float				m_fRotationA;

	BOOL				m_bSkillAirMove;		// ½ºÅ³ ¿¡¾î ¹«ºê ÆÐÅÏÀÌ´Ù.

	float				m_fCheckWearItemTime;	// Ã¼Å© ÀåÂø ¾ÆÀÌÅÛ
	int					m_nCheckDamage;			// Ã¼Å© µ¥¹ÌÁö

	float				m_fCheckDead;			// Á×¾ú´ÂÁö Ã¼Å©

	int					m_nArmorColorIndex;		// 2006-02-17 by ispark, Ä®¶ó ÀÎµ¦½º
	int					m_nInvenArmorColorIndex;// 2006-02-17 by ispark,ÀÎº¥ Ä®¶ó ÀÎµ¦½º

	//INVEN_WEAPON_MESH	m_stInvenWeaponMesh[6];	// 2006-04-04 by ispark
	vectINVEN_WEAPON_MESH	m_vectInvenWeaponMesh;	// 2006-04-04 by ispark

	BYTE				m_byFormationFlightType;

	// 2007-04-17 by bhsohn °¡±î¿î °Å¸®¿¡¼­ÀÇ ½ÃÁî¸ðµå½Ã µ¥ÀÌÁö ¾Èµé¾î°¡´Â Çö»ó Ã³¸®
	BOOL				m_bAGearFollowEnemy;		// A±â¾î Æ÷´ë ÇöÀç ÀûÀ» µû¶ó°¡°íÀÖ³Ä?

	// 2007-05-15 by bhsohn ±â¾î ½ºÅÈ °ü·Ã Ã³¸®
	GEAR_STAT			m_myShuttleFullStatInfo;	// ÀüÃ¼ ½ºÅÈÁ¤º¸ 

	float				m_fUnitX;
	float				m_fUnitY;
	float				m_fUnitZ;
	float				m_fScaling;

	BOOL				m_bNowMousePosWindowArea;
	BOOL				m_bOldMousePosWindowArea;

	FLOAT				m_fAmorHeight;				// ÇöÀç ¾Æ¸ÓÀÇ ³ôÀÌ.

	// 2008-11-13 by bhsohn Á¶ÀÌ½ºÆ½ ÀÛ¾÷
	BOOL				m_bSetCursorPos;
	int					m_nJoyStickRolling;

	// 2009-03-30 by bhsohn Â÷Â¡¼¦ ÀÌÆåÆ® ¹ö±× ¼öÁ¤
	float				m_fDelCapChagingSkill;

	// 2010. 03. 25 by ckPark »ç¸Á½Ã 5ÃÊÀÌ»ó Ãß¶ôÇÏ¸é ºÎÈ°¸Þ¼¼Áö Ãß°¡
	BOOL				m_bDeadMessageEnable;

	DWORD				m_dwDeadTime;
	// end 2010. 03. 25 by ckPark »ç¸Á½Ã 5ÃÊÀÌ»ó Ãß¶ôÇÏ¸é ºÎÈ°¸Þ¼¼Áö Ãß°¡

	// 2010. 05. 27 by jskim ½Ã³×¸¶ Àû¿ë Ä«¸Þ¶ó ±¸Çö
	//BOOL				m_ShowInterface;
	BOOL				m_bShowCinema;
	//end 2010. 05. 27 by jskim ½Ã³×¸¶ Àû¿ë Ä«¸Þ¶ó ±¸Çö


	//2011-06-30 by jhahn  ÀÎÇÇ3Â÷ ½Ã³×¸¶ ½ºÅµ±ÝÁö
	BOOL					m_InfiState;
	//end 2011-06-30 by jhahn  ÀÎÇÇ3Â÷ ½Ã³×¸¶ ½ºÅµ±ÝÁö

};

#endif // !defined(AFX_SHUTTLECHILD_H__D04D8E18_A72E_48CF_A9EE_5FF7DC242111__INCLUDED_)
