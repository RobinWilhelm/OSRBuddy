// INFGameMain.h: interface for the CInterfaceGameMain class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFGAMEMAIN_H__0FB2504C_BB3C_4763_9ADD_64687E4275A3__INCLUDED_)
#define AFX_INFGAMEMAIN_H__0FB2504C_BB3C_4763_9ADD_64687E4275A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AtumNode.h"
//#include "AtumApplication.h"
//#include "INFMission.h"
// 2007-07-04 by bhsohn ���۷����� �߰�
//#include "INFImageBtn.h"

// 2007-08-07 by bhsohn ����Ŀ ������ �߰�
//#include "INFSpeakeMsg.h"

// 2008-02-27 by bhsohn �Ʒ��� �̵��� ä������ ����
//#include "ChatTab_t.h"



// 2008. 12. 23 by ckPark ��ų ��� ���� ��� ����
//#include "SkillInfo.h"
// end 2008. 12. 23 by ckPark ��ų ��� ���� ��� ����





//#include "INFQuickSlot.h"
//#include "INFParty.h"
//#include "INFMiniMap.h"
//#include "INFQuest.h"

#define LEFT_WINDOW_WEAPON	0			//��� ���ʿ� �Ѿ� ������ ���ö�..
#define LEFT_WINDOW_INVEN	1			//�κ�Ű (I key)�� �������� �κ�â�� �ߴ� ����.
#define LEFT_WINDOW_TRANS	2			//
#define LEFT_WINDOW_PARTY	3			//��Ƽâ..
#define LEFT_WINDOW_SHOP	4			//����.

#define RIGHT_WINDOW_WEAPON 0
#define RIGHT_WINDOW_INFO	1
#define RIGHT_WINDOW_OPTION 2

#define INF_WINDOW_MOVING_VEL	3000

#define UNITKIND_LEVEL_1_MASK		(USHORT)0x1111	// ���Ϸ�
#define UNITKIND_LEVEL_2_MASK		(USHORT)0x2222	// ����
#define UNITKIND_LEVEL_3_MASK		(USHORT)0x4444	// ���̽�
#define UNITKIND_LEVEL_4_MASK		(USHORT)0x8888	// ž��
#define IS_UNITKIND_LEVEL_1(x)		((x&UNITKIND_LEVEL_1_MASK) != 0)
#define IS_UNITKIND_LEVEL_2(x)		((x&UNITKIND_LEVEL_2_MASK) != 0)
#define IS_UNITKIND_LEVEL_3(x)		((x&UNITKIND_LEVEL_3_MASK) != 0)
#define IS_UNITKIND_LEVEL_4(x)		((x&UNITKIND_LEVEL_4_MASK) != 0)


#define GAMEMAIN_BUTTON_INVEN		0
#define GAMEMAIN_BUTTON_INFO		1
#define GAMEMAIN_BUTTON_COMMUNITY	2
#define GAMEMAIN_BUTTON_TRADE		3
#define GAMEMAIN_BUTTON_SYSTEM		4

#define GAMEMAIN_BUTTON_NUMBER		5

#define HELP_NUM					2
#define	GAMEMAIN_TIMESET_ZERO		0
#define	GAMEMAIN_TIME_VIEW_TOP		27


#define HELP_START_X				(g_pD3dApp->GetBackBufferDesc().Width/2)-220
#define HELP_START_Y				130
#define HELP_TEXT_CHECK_TIME		20

// 2007-03-02 by bhsohn ���� ���� �߰� ����
#define MAX_MULTI_SEL				3

// ������ ���� �ð� 
// 2007-09-19 by bhsohn ������ �ð� 1�ð����� ����
//#define	WAR_MONSTER_LIVETIME_HOUR					2
#define	WAR_MONSTER_LIVETIME_HOUR					1
// �� ����ִ� �ð� 
#define	MOTHERSHIP_LIVETIME_HOUR					2
#define	MOTHERSHIP_LIVETIME_SECOND					MOTHERSHIP_LIVETIME_HOUR*3600

// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
// ���� �ý��� ���� ����
#define		SECURITY_MODE_LOCK					0		// Lock
#define		SECURITY_MODE_SETUP_PASSWORD		1		// SETUP_PASSWORD
#define		SECURITY_MODE_SETUP_CHANGE_PASS		2		// 
#define		SECURITY_MODE_PASS_WND				3		// 
#define		MAX_SECURITY_MODE_WND				4		// SETUP_PASSWORD

// 2007-09-27 by bhsohn 2�� �н����� �߰� ��ȹ��
// Lock, UnLock, SecondeModeCanel
#define		SECURITY_MODE_PASS_LOCK					0		// Lock
#define		SECURITY_MODE_PASS_UNLOCK				1		// UnLock
#define		SECURITY_MODE_PASS_SENCOND_CANCEL		2		// Cacncel

// 2006-07-26 by ispark, ���� ������
typedef struct
{
	BYTE					bySelectType;
	INVEN_DISPLAY_INFO* pSelectItem;
	CINFImage* pSelectIcon;
	POINT					ptIcon;
} stSelectItem;

// 2008-06-17 by dgwoo VoIP ���� ä�� ���� ����ü.
struct stVOIPData
{
	BYTE					byVoiceType;					// ���� �������� ����ä��.(VOICE_NONE, VOICE_ONE, VOICE_PARTY, VOICE_GUILD)
	BYTE					byVoiceInput;					// ���� �Է� ���.
	DWORD					nVolum;							// ����.
	stVOIPData()
	{
		byVoiceType = 0;
		byVoiceInput = 0;
		nVolum = 100;
	};
};



// 2008. 12. 16 by ckPark ������ ��� ����
///////////////////////////////////////////////////////////////////////////////
// \class 	: ITEM_DELAY
// \brief	: ������ ���� ���� �ð���, ������ ������ ���� ����Ʈ�� ��Ƶ� ����ü
//			  ���� �ð��� nItemDelayTime + nItemUseTime���� Ŭ ��� ������ ������ �ȴ�
// \author	: ckPark
// \version : 
// \date	: 16:12:2008   14:32
// \warning	: nItemUniqueNumber�� ITEM_BASE�� UniqueNumber ���
//			  nItemUseTime�� ��������� �ð��� ���
//			  nItemDelayTime�� ITEM�� AttackTime ���
struct ITEM_DELAY
{
	UINT64	nItemUniqueNumber;		// ������ ���� �ѹ�
	DWORD	nItemUseTime;			// ������ ����� �ð� (1/1000�� ����)
	USHORT	nItemDelayTime;			// ������ ������ Ÿ��
};
// end 2008. 12. 16 by ckPark ������ ��� ����




// 2008. 12. 23 by ckPark ��ų ��� ���� ��� ����
///////////////////////////////////////////////////////////////////////////////
// \class 	: SKILL_DELAY
// \brief	: ��ų ���� ���� �ð���, ������ ������ ���� ����Ʈ�� ��Ƶ� ����ü
//			  ���� �ð��� nSkillUseTime + nSkillDelayTime���� Ŭ ��� ������ ������ �ȴ�
// \author	: ckPark
// \version : 
// \date	: 26:12:2008   12:58
// \warning	: nTargetUniqueNumber Ÿ�� ����ũ �ѹ�
//			  nSkillUseTime�� ��ų ���� �ð�
//			  nSkillDelayTime�� ITEM�� AttackTime ���
///////////////////////////////////////////////////////////////////////////////
struct SKILL_DELAY
{
	void* pSkillInfo;
	UID32_t		nTargetUniqueNumber;
	DWORD		nSkillUseTime;
	USHORT		nSkillDelayTime;
};
// end 2008. 12. 23 by ckPark ��ų ��� ���� ��� ����


// 2010. 02. 11 by ckPark �ߵ��� ����������
struct INVOKEITEM_COOLTIME
{
	UID64_t		nItemUID;			// ������ UID
	DWORD		nPrevTickTime;		// �� ������ ��Ÿ�� ��� �ð�
	BOOL		bSendEndCoolTime;	// ������ ��Ÿ�� ���Ḧ ���´°�?

	INVOKEITEM_COOLTIME() : nItemUID(0), nPrevTickTime(0), bSendEndCoolTime(FALSE)
	{

	}
};
// end 2010. 02. 11 by ckPark �ߵ��� ����������


class CGameData;
class CINFAttackDirection;
class CINFUnitState;
class CINFGameMainQSlot;
class CINFGameMainUnitInfoBar;
class CINFGameMainMiniMap;
class CINFGameMainOutPost;
class CINFCommunity;
class CINFWindow;
class CINFWeaponInfo;
class CINFTrade;

// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
//class CINFInven;
class CINFInvenExtend;

// 2008-03-19 by bhsohn Ep3�ɼ�â
//class CINFSystem;
class CINFOptionSystem;
// end 2008-03-19 by bhsohn Ep3�ɼ�â

// 2008-09-22 by bhsohn EP3 ĳ���� â
//class CINFCharacterInfo;
class CINFCharacterInfoExtend;

class CINFGameMainChat;
class CINFIcon;
class CINFShop;
class CINFItemInfo;
//class CINFNotice;
class CINFUnitNameInfo;
class CINFImage;
class CD3DHanFont;
class DataHeader;
class CINFGameHelpDesk;
class CINFQuest;
class CINFSkill;
class CINFGameCountDown;
class CINFDamageView;
class CINFOtherCharInfo;
class CINFGameMainFAQ;
class CINFMenuList;
class CINFMp3Player;
class CINFMissionInfo;
// 2007-06-12 by bhsohn �̼� �������̽� ������
class CINFMissionMain;

class CINFCommunityVOIP;
class CINFCityBoard;

// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
class CINFSecuMain;
class CINFChangeCharactor;					// 2007-11-21 by dgwoo ĳ���� ���� ī��
class CINFCouponWindow;						// 2008-01-15 by dgwoo ���� �ý��� �߰�.
class CINFMotherShipManager;				// 2008-04-04 by bhsohn ���� ���� Ŭ���� �߰�
class CINFGameMainSysMsg;					// 2008-11-3 by bhsohn ���� �ð� ���� ��ư �߰�
class CINFOpJoystick;						// 2008-11-13 by bhsohn ���̽�ƽ �۾�
class CINFWorldRankWnd;						// 2009-02-13 by bhsohn ���� ��ŷ �ý���

class CINFGameMain : public CAtumNode
{
public:

	CINFGameMain(CAtumNode* pParent);
	virtual ~CINFGameMain();

	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual void Tick();

public:
	void* m_unknown1;
	void* m_unknown2;
	//��, �� ������ ��ġ ����� �����
	int		m_nLeftWindowY;
	int		m_nRightWindowY;

	//////////////////////////////////////////////////////////////////////////	
	// �������� ������ ���� ���� ����
	CItemInfo* m_pItemInfoWear[SIZE_MAX_POS];					// �����غ��� ������ ����
	ITEM_GENERAL* m_pITEMG[SIZE_MAX_POS];							// �����غ��� ������ ����
	int							m_nItemSourceNum[SIZE_MAX_POS];					// ������ �����ϰ� �ִ� ������ ����
	BOOL						m_bUseShopItem;
	int							m_nArmorColor;									// ������ �Ƹ� Į��
	int							m_nLeaveBuildingIndex;							// ��������� ����
	//
	//////////////////////////////////////////////////////////////////////////	

public:
	

	CGameData* m_pGameData;

	CINFAttackDirection* m_pAttackDirection;
	CINFUnitState* m_pUnitState;
	CINFGameMainQSlot* m_pQuickSlot;
	CINFGameMainUnitInfoBar* m_pUnitInfoBar;
	CINFGameMainMiniMap* m_pMiniMap;
	CINFCommunity* m_pCommunity;
	CINFWindow* m_pInfWindow;
	CINFWeaponInfo* m_pWeaponInfo;
	CINFTrade* m_pTrade;

	// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
	//CINFInven				*	m_pInven ;
	CINFInvenExtend* m_pInven;

	// 2008-03-19 by bhsohn Ep3�ɼ�â
	//CINFSystem				*	m_pSystem ;
	CINFOptionSystem* m_pSystem;

	// 2008-09-22 by bhsohn EP3 ĳ���� â
	//CINFCharacterInfo		*	m_pCharacterInfo ;
	CINFCharacterInfoExtend* m_pCharacterInfo;

	CINFGameMainChat* m_pChat;
	CINFIcon* m_pIcon;
	void* m_pMission;
	// 2009-02-03 by bhsohn ���� ������ �� ����
	//CINFItemInfo			*	m_pItemInfo;	
	// end 2009-02-03 by bhsohn ���� ������ �� ����
	CINFUnitNameInfo* m_pUnitNameInfo;
	CINFSkill* m_pInfSkill;
	CINFGameCountDown* m_pGameCountDown;
	CINFDamageView* m_pDamageView;
	CINFOtherCharInfo* m_pOtherCharInfo;
	CINFGameMainFAQ* m_pInfGameMainFaq;
	CINFMenuList* m_pMenuList;
	CINFCouponWindow* m_pCouponWindow;
	CINFImage* m_pImgButton[GAMEMAIN_BUTTON_NUMBER][BUTTON_STATE_NUMBER];
	CINFImage* m_pImgMission;
	CINFImage* m_pHelp[HELP_NUM];
	CINFImage* m_pSelectIcon;
	CINFImage* m_pImgTextPopUp[3];
	CINFImage* m_pImgTextBg;
	CINFGameHelpDesk* m_pHelpDesk;
	CINFQuest* m_pQuest;
	CINFMp3Player* m_pMp3Player;
	// 2007-08-28 by dgwoo ���������� class�߰�.
	CINFGameMainOutPost* m_pOutPost;

	// 2007-06-12 by bhsohn �̼� �������̽� ������
	//CINFMissionInfo			*	m_pMissionInfo;
	CINFMissionMain* m_pMissionMain;
	CINFChangeCharactor* m_pChangeCharactor;				// 2007-11-21 by dgwoo ĳ���� ���� ī��

	CINFCommunityVOIP* m_pCommunityVOIP;
	CINFCityBoard* m_pCityBoard;
	CINFImage* m_pImgStack;

	int		m_nIconPosX;
	int		m_nIconPosY;
	int		m_nButtonState[GAMEMAIN_BUTTON_NUMBER];
	int		m_nLeftWindowState;
	int		m_nLeftWindowInfo;
	int		m_nLeftWeaponInfoPosX;
	int		m_nLeftWindowPosY;
	int		m_nLeftWindowScaleSize;
	int		m_nRightWindowState;
	int		m_nRightWindowInfo;
	int		m_nRightWeaponInfoPosX;
	int		m_nRightWindowPosY;
	int		m_nRightWindowScaleSize;

	BOOL	m_bHelpDeskFlag;
	BOOL	m_bLeftWindowModeChage;				//����â�� ��ȭ���ִ� ������ ����. ��
	BOOL	m_bRightWindowModeChage;
	BOOL	m_bMp3PlayFlag;

	CD3DHanFont* m_pFontToolTip;
	CD3DHanFont* m_pFontTimeLimit;
	CD3DHanFont* m_pFontDrawMent;
	char m_pad01[16];

	// 2010. 04. 28 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����.
	char				m_szSave_ToolTip[1024];

	vector < string >	m_vecToolTip;

	INT					m_iToolTipMaxWid;
	BOOL				m_bRenderToolTipEx;
	POINT				m_ptToolTipEx;
	RECT				m_rcToolTipEx;

	DWORD				m_dwFrameToolTip[2];
	// End. 2010. 04. 28 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����.

	

	char				m_strToolTip[128];
	POINT				m_ptToolTip;
	BOOL				m_bShowHelp;
	BOOL				m_bRestored;
	BOOL				m_bQuestView;


	BOOL				m_bQuestLimitTimeView;
	// 2008-04-07 by bhsohn ����Ʈ �ð� �����Ǵ� ���� ó��
//	float				m_fTimeElapse;	
//	int					m_nTimeSecond;
//	char				m_strNPCName[32];

	// ������ �̼ǹ�ư �����̱�
//	BOOL				m_bMissionON;
//	BOOL				m_bMissionTwinkle;
// 	float				m_fTimeElapseMission;

	// FAQ ����
	BOOL				m_bFAQProsFlag;
	// �޴� ����Ʈ
	BOOL				m_bMenuListFlag;
	BOOL				m_bMenuLock;
	BOOL				m_bEnterBuilingCashShop;
	BOOL				m_bSendCashItemBuy;

	BOOL				m_bBuyMessage;

	// 2005-03-03 by jschoi - RequestEnable
	CINFImage* m_pRequestEnableBack;
	CINFImage* m_pRequestEnableTriangle;

	// �� ������ ����
	CINFImage* m_pAltiMeterGage;
	CINFImage* m_pAltiMeterPin;
	POINT			m_ptGageBack;
	POINT			m_ptGagePin;

	// �ŷ� 1:1���� ���콺 ����Ʈ ����
	BOOL			m_bChangeMousePoint;
	// ���� ������
	BOOL			m_bQSlotIconFlag;
	int				m_nQSlotPosX;
	int				m_nQSlotPosY;

	// �̼� ����
	int				m_nTimeLimitMissionOldTime;
	// VOIP
	BOOL			m_bVOIPFlag;

	// 2006-08-23 by ispark, ��ư �����̴� �ҽ� ����
	BOOL			m_bKnowON[HELP_SPECIAL_COUNT];
	BOOL			m_bKnowTwinkle;
	float			m_fTimeElapseButtonCheck;

	stSelectItem	m_stSelectItem;			// 2006-07-26 by ispark, ���� ������

	// 2007-03-02 by bhsohn ���� ���� �߰� ����
	stSelectItem	m_stMultiSelectItem[MAX_MULTI_SEL];
	int				m_nMultiSelCnt;
	// 2008-01-15 by dgwoo ���� �ý��� �߰�.
	void* m_pCouponBtn;
	// 2009. 10. 14 by jskim ������ī ����	
	void* m_pTut_SelBtn;
	//end 2009. 10. 14 by jskim ������ī ����	

private:
	// 2007-07-04 by bhsohn ���۷����� �߰�
	void* m_pFaqBtn;

	// 2007-07-27 by bhsohn ���� �߰� �� ���� ���۷����Ϳ� ����
	BOOL					m_bShowStatOpWnd;

	// 2007-08-07 by bhsohn ����Ŀ ������ �߰�
	void* m_pINFSpeakeMsg;
	// end 2007-08-07 by bhsohn ����Ŀ ������ �߰�

	// 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����
	CINFSecuMain* m_pINFSecuMain;
	// end 2007-09-12 by bhsohn 2�� ��ȣ �ý��� ����

	// 2008-04-04 by bhsohn ���� ���� Ŭ���� �߰�
	CINFMotherShipManager* m_pMotherShipC;

	// 2008-04-07 by bhsohn ����Ʈ �ð� �����Ǵ� ���� ó��
	float						m_fQuestTimeElapse;

	// 2008-06-17 by dgwoo ���� ä��.
	stVOIPData					m_stVOIP;

	// 2008-10-14 by bhsohn VOIP����
	BOOL						m_bVOIPSpeaking;

	// 2008-11-3 by bhsohn ���� �ð� ���� ��ư �߰�
	CINFGameMainSysMsg* m_pINFGameMainSysMsg;

	// 2008-11-13 by bhsohn ���̽�ƽ �۾�
	CINFOpJoystick* m_pINFOpJoystick;

	// 2009-02-03 by bhsohn ���� ������ �� ����
	CINFItemInfo* m_pItemInfo;		// ������ ����
	CINFItemInfo* m_pEquipItemInfo;	// ���� ������ ������ ����	
	BOOL						m_bShowMyEqTooltip;
	// end 2009-02-03 by bhsohn ���� ������ �� ����

	// 2009-02-13 by bhsohn ���� ��ŷ �ý���
	CINFWorldRankWnd* m_pINFWorldRankWnd;
	// end 2009-02-13 by bhsohn ���� ��ŷ �ý���

	// 2008. 12. 16 by ckPark ������ ��� ����
	// ���� ó���� �������� �־�� ����Ʈ
	std::list<ITEM_DELAY>	m_listItemDelay;


protected:
	std::list<SKILL_DELAY>	m_listSkillDelay;



	// 2009. 08. 21 by ckPark ĳ�������� �����ϱ⿡ ������ üũ
protected:
	char	m_szCashGiftSendCharacterName[256];


	// end 2009. 08. 21 by ckPark ĳ�������� �����ϱ⿡ ������ üũ


	// 2010. 02. 11 by ckPark �ߵ��� ����������
protected:
	// ��Ÿ�� ����Ʈ
	std::list<INVOKEITEM_COOLTIME>	m_listInvokeItemCoolTime;


	// end 2010. 02. 11 by ckPark �ߵ��� ����������
};

#define POS_LEFT_WINDOW_Y	(((CINFGameMain*)m_pParent)->m_nLeftWindowPosY - ((CINFGameMain*)m_pParent)->m_nLeftWindowScaleSize/2)
#define POS_RIGHT_WINDOW_Y	(((CINFGameMain*)m_pParent)->m_nRightWindowPosY - ((CINFGameMain*)m_pParent)->m_nRightWindowScaleSize/2)
#define POS_RIGHT_WINDOW_X		(g_pD3dApp->GetBackBufferDesc().Width - SIZE_NORMAL_WINDOW_X)


#endif // !defined(AFX_INFGameMain_H__0FB2504C_BB3C_4763_9ADD_64687E4275A3__INCLUDED_)
