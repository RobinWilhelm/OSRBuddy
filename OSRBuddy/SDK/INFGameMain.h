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
// 2007-07-04 by bhsohn 오퍼레이터 추가
//#include "INFImageBtn.h"

// 2007-08-07 by bhsohn 스피커 아이템 추가
//#include "INFSpeakeMsg.h"

// 2008-02-27 by bhsohn 아레나 이동시 채팅정보 뺵업
//#include "ChatTab_t.h"



// 2008. 12. 23 by ckPark 스킬 사용 지연 사용 지연
//#include "SkillInfo.h"
// end 2008. 12. 23 by ckPark 스킬 사용 지연 사용 지연





//#include "INFQuickSlot.h"
//#include "INFParty.h"
//#include "INFMiniMap.h"
//#include "INFQuest.h"

#define LEFT_WINDOW_WEAPON	0			//평소 왼쪽에 총알 정보가 나올때..
#define LEFT_WINDOW_INVEN	1			//인벤키 (I key)를 눌렀을때 인벤창이 뜨는 상태.
#define LEFT_WINDOW_TRANS	2			//
#define LEFT_WINDOW_PARTY	3			//파티창..
#define LEFT_WINDOW_SHOP	4			//상점.

#define RIGHT_WINDOW_WEAPON 0
#define RIGHT_WINDOW_INFO	1
#define RIGHT_WINDOW_OPTION 2

#define INF_WINDOW_MOVING_VEL	3000

#define UNITKIND_LEVEL_1_MASK		(USHORT)0x1111	// 파일럿
#define UNITKIND_LEVEL_2_MASK		(USHORT)0x2222	// 윙맨
#define UNITKIND_LEVEL_3_MASK		(USHORT)0x4444	// 에이스
#define UNITKIND_LEVEL_4_MASK		(USHORT)0x8888	// 탑건
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

// 2007-03-02 by bhsohn 다중 선택 추가 보안
#define MAX_MULTI_SEL				3

// 거점전 생성 시간 
// 2007-09-19 by bhsohn 거점전 시간 1시간으로 변경
//#define	WAR_MONSTER_LIVETIME_HOUR					2
#define	WAR_MONSTER_LIVETIME_HOUR					1
// 모선 살아있는 시간 
#define	MOTHERSHIP_LIVETIME_HOUR					2
#define	MOTHERSHIP_LIVETIME_SECOND					MOTHERSHIP_LIVETIME_HOUR*3600

// 2007-09-12 by bhsohn 2차 암호 시스템 구현
// 보안 시스템 관련 변수
#define		SECURITY_MODE_LOCK					0		// Lock
#define		SECURITY_MODE_SETUP_PASSWORD		1		// SETUP_PASSWORD
#define		SECURITY_MODE_SETUP_CHANGE_PASS		2		// 
#define		SECURITY_MODE_PASS_WND				3		// 
#define		MAX_SECURITY_MODE_WND				4		// SETUP_PASSWORD

// 2007-09-27 by bhsohn 2차 패스워드 추가 기획안
// Lock, UnLock, SecondeModeCanel
#define		SECURITY_MODE_PASS_LOCK					0		// Lock
#define		SECURITY_MODE_PASS_UNLOCK				1		// UnLock
#define		SECURITY_MODE_PASS_SENCOND_CANCEL		2		// Cacncel

// 2006-07-26 by ispark, 선택 아이템
typedef struct
{
	BYTE					bySelectType;
	INVEN_DISPLAY_INFO* pSelectItem;
	CINFImage* pSelectIcon;
	POINT					ptIcon;
} stSelectItem;

// 2008-06-17 by dgwoo VoIP 음성 채팅 관리 구조체.
struct stVOIPData
{
	BYTE					byVoiceType;					// 현재 진행중인 음성채팅.(VOICE_NONE, VOICE_ONE, VOICE_PARTY, VOICE_GUILD)
	BYTE					byVoiceInput;					// 음성 입력 방식.
	DWORD					nVolum;							// 볼륨.
	stVOIPData()
	{
		byVoiceType = 0;
		byVoiceInput = 0;
		nVolum = 100;
	};
};



// 2008. 12. 16 by ckPark 아이템 사용 지연
///////////////////////////////////////////////////////////////////////////////
// \class 	: ITEM_DELAY
// \brief	: 아이템 사용시 일정 시간뒤, 서버로 보내기 위해 리스트에 담아둘 구조체
//			  현재 시간이 nItemDelayTime + nItemUseTime보다 클 경우 서버로 보내면 된다
// \author	: ckPark
// \version : 
// \date	: 16:12:2008   14:32
// \warning	: nItemUniqueNumber는 ITEM_BASE의 UniqueNumber 사용
//			  nItemUseTime는 사용했을시 시간을 기록
//			  nItemDelayTime는 ITEM의 AttackTime 사용
struct ITEM_DELAY
{
	UINT64	nItemUniqueNumber;		// 아이템 고유 넘버
	DWORD	nItemUseTime;			// 아이템 사용한 시간 (1/1000초 단위)
	USHORT	nItemDelayTime;			// 아이템 딜레이 타임
};
// end 2008. 12. 16 by ckPark 아이템 사용 지연




// 2008. 12. 23 by ckPark 스킬 사용 지연 사용 지연
///////////////////////////////////////////////////////////////////////////////
// \class 	: SKILL_DELAY
// \brief	: 스킬 사용시 일정 시간뒤, 서버로 보내기 위해 리스트에 담아둘 구조체
//			  현재 시간이 nSkillUseTime + nSkillDelayTime보다 클 경우 서버로 보내면 된다
// \author	: ckPark
// \version : 
// \date	: 26:12:2008   12:58
// \warning	: nTargetUniqueNumber 타겟 유니크 넘버
//			  nSkillUseTime는 스킬 사용시 시간
//			  nSkillDelayTime는 ITEM의 AttackTime 사용
///////////////////////////////////////////////////////////////////////////////
struct SKILL_DELAY
{
	void* pSkillInfo;
	UID32_t		nTargetUniqueNumber;
	DWORD		nSkillUseTime;
	USHORT		nSkillDelayTime;
};
// end 2008. 12. 23 by ckPark 스킬 사용 지연 사용 지연


// 2010. 02. 11 by ckPark 발동류 장착아이템
struct INVOKEITEM_COOLTIME
{
	UID64_t		nItemUID;			// 아이템 UID
	DWORD		nPrevTickTime;		// 맨 마지막 쿨타임 계산 시간
	BOOL		bSendEndCoolTime;	// 서버로 쿨타임 종료를 보냈는가?

	INVOKEITEM_COOLTIME() : nItemUID(0), nPrevTickTime(0), bSendEndCoolTime(FALSE)
	{

	}
};
// end 2010. 02. 11 by ckPark 발동류 장착아이템


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

// 2008-08-22 by bhsohn EP3 인벤토리 처리
//class CINFInven;
class CINFInvenExtend;

// 2008-03-19 by bhsohn Ep3옵션창
//class CINFSystem;
class CINFOptionSystem;
// end 2008-03-19 by bhsohn Ep3옵션창

// 2008-09-22 by bhsohn EP3 캐릭터 창
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
// 2007-06-12 by bhsohn 미션 인터페이스 수정안
class CINFMissionMain;

class CINFCommunityVOIP;
class CINFCityBoard;

// 2007-09-12 by bhsohn 2차 암호 시스템 구현
class CINFSecuMain;
class CINFChangeCharactor;					// 2007-11-21 by dgwoo 캐릭터 변경 카드
class CINFCouponWindow;						// 2008-01-15 by dgwoo 쿠폰 시스템 추가.
class CINFMotherShipManager;				// 2008-04-04 by bhsohn 모선전 관리 클래스 추가
class CINFGameMainSysMsg;					// 2008-11-3 by bhsohn 서버 시간 보기 버튼 추가
class CINFOpJoystick;						// 2008-11-13 by bhsohn 조이스틱 작업
class CINFWorldRankWnd;						// 2009-02-13 by bhsohn 월드 랭킹 시스템

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
	//좌, 우 윈도우 위치 계산한 결과값
	int		m_nLeftWindowY;
	int		m_nRightWindowY;

	//////////////////////////////////////////////////////////////////////////	
	// 아이템을 착용해 보기 위한 정보
	CItemInfo* m_pItemInfoWear[SIZE_MAX_POS];					// 착용해보기 아이템 정보
	ITEM_GENERAL* m_pITEMG[SIZE_MAX_POS];							// 착용해보기 아이템 정보
	int							m_nItemSourceNum[SIZE_MAX_POS];					// 그전에 착용하고 있던 아이템 정보
	BOOL						m_bUseShopItem;
	int							m_nArmorColor;									// 전착용 아머 칼라
	int							m_nLeaveBuildingIndex;							// 착용아이템 상점
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

	// 2008-08-22 by bhsohn EP3 인벤토리 처리
	//CINFInven				*	m_pInven ;
	CINFInvenExtend* m_pInven;

	// 2008-03-19 by bhsohn Ep3옵션창
	//CINFSystem				*	m_pSystem ;
	CINFOptionSystem* m_pSystem;

	// 2008-09-22 by bhsohn EP3 캐릭터 창
	//CINFCharacterInfo		*	m_pCharacterInfo ;
	CINFCharacterInfoExtend* m_pCharacterInfo;

	CINFGameMainChat* m_pChat;
	CINFIcon* m_pIcon;
	void* m_pMission;
	// 2009-02-03 by bhsohn 장착 아이템 비교 툴팁
	//CINFItemInfo			*	m_pItemInfo;	
	// end 2009-02-03 by bhsohn 장착 아이템 비교 툴팁
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
	// 2007-08-28 by dgwoo 전진기지전 class추가.
	CINFGameMainOutPost* m_pOutPost;

	// 2007-06-12 by bhsohn 미션 인터페이스 수정안
	//CINFMissionInfo			*	m_pMissionInfo;
	CINFMissionMain* m_pMissionMain;
	CINFChangeCharactor* m_pChangeCharactor;				// 2007-11-21 by dgwoo 캐릭터 변경 카드

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
	BOOL	m_bLeftWindowModeChage;				//왼쪽창에 변화가있는 동안의 상태. 참
	BOOL	m_bRightWindowModeChage;
	BOOL	m_bMp3PlayFlag;

	CD3DHanFont* m_pFontToolTip;
	CD3DHanFont* m_pFontTimeLimit;
	CD3DHanFont* m_pFontDrawMent;
	char m_pad01[16];

	// 2010. 04. 28 by hsLee 인피니티 필드 2차 난이도 조절.
	char				m_szSave_ToolTip[1024];

	vector < string >	m_vecToolTip;

	INT					m_iToolTipMaxWid;
	BOOL				m_bRenderToolTipEx;
	POINT				m_ptToolTipEx;
	RECT				m_rcToolTipEx;

	DWORD				m_dwFrameToolTip[2];
	// End. 2010. 04. 28 by hsLee 인피니티 필드 2차 난이도 조절.

	

	char				m_strToolTip[128];
	POINT				m_ptToolTip;
	BOOL				m_bShowHelp;
	BOOL				m_bRestored;
	BOOL				m_bQuestView;


	BOOL				m_bQuestLimitTimeView;
	// 2008-04-07 by bhsohn 퀘스트 시간 지연되는 문제 처리
//	float				m_fTimeElapse;	
//	int					m_nTimeSecond;
//	char				m_strNPCName[32];

	// 랩업시 미션버튼 깜박이기
//	BOOL				m_bMissionON;
//	BOOL				m_bMissionTwinkle;
// 	float				m_fTimeElapseMission;

	// FAQ 관련
	BOOL				m_bFAQProsFlag;
	// 메뉴 리스트
	BOOL				m_bMenuListFlag;
	BOOL				m_bMenuLock;
	BOOL				m_bEnterBuilingCashShop;
	BOOL				m_bSendCashItemBuy;

	BOOL				m_bBuyMessage;

	// 2005-03-03 by jschoi - RequestEnable
	CINFImage* m_pRequestEnableBack;
	CINFImage* m_pRequestEnableTriangle;

	// 고도 게이지 설정
	CINFImage* m_pAltiMeterGage;
	CINFImage* m_pAltiMeterPin;
	POINT			m_ptGageBack;
	POINT			m_ptGagePin;

	// 거래 1:1대결시 마우스 포인트 변경
	BOOL			m_bChangeMousePoint;
	// 단축 아이콘
	BOOL			m_bQSlotIconFlag;
	int				m_nQSlotPosX;
	int				m_nQSlotPosY;

	// 미션 인포
	int				m_nTimeLimitMissionOldTime;
	// VOIP
	BOOL			m_bVOIPFlag;

	// 2006-08-23 by ispark, 버튼 깜박이는 소스 수정
	BOOL			m_bKnowON[HELP_SPECIAL_COUNT];
	BOOL			m_bKnowTwinkle;
	float			m_fTimeElapseButtonCheck;

	stSelectItem	m_stSelectItem;			// 2006-07-26 by ispark, 선택 아이템

	// 2007-03-02 by bhsohn 다중 선택 추가 보안
	stSelectItem	m_stMultiSelectItem[MAX_MULTI_SEL];
	int				m_nMultiSelCnt;
	// 2008-01-15 by dgwoo 쿠폰 시스템 추가.
	void* m_pCouponBtn;
	// 2009. 10. 14 by jskim 프리스카 제거	
	void* m_pTut_SelBtn;
	//end 2009. 10. 14 by jskim 프리스카 제거	

private:
	// 2007-07-04 by bhsohn 오퍼레이터 추가
	void* m_pFaqBtn;

	// 2007-07-27 by bhsohn 스탯 추가 된 도움말 오퍼레이터에 통합
	BOOL					m_bShowStatOpWnd;

	// 2007-08-07 by bhsohn 스피커 아이템 추가
	void* m_pINFSpeakeMsg;
	// end 2007-08-07 by bhsohn 스피커 아이템 추가

	// 2007-09-12 by bhsohn 2차 암호 시스템 구현
	CINFSecuMain* m_pINFSecuMain;
	// end 2007-09-12 by bhsohn 2차 암호 시스템 구현

	// 2008-04-04 by bhsohn 모선전 관리 클래스 추가
	CINFMotherShipManager* m_pMotherShipC;

	// 2008-04-07 by bhsohn 퀘스트 시간 지연되는 문제 처리
	float						m_fQuestTimeElapse;

	// 2008-06-17 by dgwoo 음성 채팅.
	stVOIPData					m_stVOIP;

	// 2008-10-14 by bhsohn VOIP개선
	BOOL						m_bVOIPSpeaking;

	// 2008-11-3 by bhsohn 서버 시간 보기 버튼 추가
	CINFGameMainSysMsg* m_pINFGameMainSysMsg;

	// 2008-11-13 by bhsohn 조이스틱 작업
	CINFOpJoystick* m_pINFOpJoystick;

	// 2009-02-03 by bhsohn 장착 아이템 비교 툴팁
	CINFItemInfo* m_pItemInfo;		// 아이템 툴팁
	CINFItemInfo* m_pEquipItemInfo;	// 현재 장착한 아이템 툴팁	
	BOOL						m_bShowMyEqTooltip;
	// end 2009-02-03 by bhsohn 장착 아이템 비교 툴팁

	// 2009-02-13 by bhsohn 월드 랭킹 시스템
	CINFWorldRankWnd* m_pINFWorldRankWnd;
	// end 2009-02-13 by bhsohn 월드 랭킹 시스템

	// 2008. 12. 16 by ckPark 아이템 사용 지연
	// 지연 처리할 아이템을 넣어둘 리스트
	std::list<ITEM_DELAY>	m_listItemDelay;


protected:
	std::list<SKILL_DELAY>	m_listSkillDelay;



	// 2009. 08. 21 by ckPark 캐쉬아이템 선물하기에 블럭계정 체크
protected:
	char	m_szCashGiftSendCharacterName[256];


	// end 2009. 08. 21 by ckPark 캐쉬아이템 선물하기에 블럭계정 체크


	// 2010. 02. 11 by ckPark 발동류 장착아이템
protected:
	// 쿨타임 리스트
	std::list<INVOKEITEM_COOLTIME>	m_listInvokeItemCoolTime;


	// end 2010. 02. 11 by ckPark 발동류 장착아이템
};

#define POS_LEFT_WINDOW_Y	(((CINFGameMain*)m_pParent)->m_nLeftWindowPosY - ((CINFGameMain*)m_pParent)->m_nLeftWindowScaleSize/2)
#define POS_RIGHT_WINDOW_Y	(((CINFGameMain*)m_pParent)->m_nRightWindowPosY - ((CINFGameMain*)m_pParent)->m_nRightWindowScaleSize/2)
#define POS_RIGHT_WINDOW_X		(g_pD3dApp->GetBackBufferDesc().Width - SIZE_NORMAL_WINDOW_X)


#endif // !defined(AFX_INFGameMain_H__0FB2504C_BB3C_4763_9ADD_64687E4275A3__INCLUDED_)
