// INFCityBase.h: interface for the CINFCityBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFCITYBASE_H__79E1DB05_7EE1_486A_8C14_5A021065FC0D__INCLUDED_)
#define AFX_INFCITYBASE_H__79E1DB05_7EE1_486A_8C14_5A021065FC0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INFBase.h"

// 2007-07-04 by bhsohn 오퍼레이터 추가
//#include "INFImageBtn.h"
class CINFImageBtn;

#define CITY_BUTTON_NUMBER	4

#define BUTTON_STATE_UP			0
#define BUTTON_STATE_DOWN		1
#define BUTTON_STATE_DISABLE	2
#define BUTTON_STATE_NORMAL		3


#define BUILDINGNPC_RENDER_TALKBOX			0
#define BUILDINGNPC_RENDER_SHOP				1
#define BUILDINGNPC_RENDER_MISSION			2
#define BUILDINGNPC_RENDER_OCCUPY			3
#define BUILDINGNPC_RENDER_CASH_SHOP		4
#define BUILDINGNPC_RENDER_ARENA			5
#define BUILDINGNPC_RENDER_WARPOINT			6
#define BUILDINGNPC_RENDER_MSGBOX			7
#define BUILDINGNPC_RENDER_INFLUENCE		8
#define BUILDINGNPC_RENDER_LUCKYMACHINE		9

// 2009. 11. 02 by ckPark 인피니티 필드 인스턴스 던젼 시스템
#define BUILDINGNPC_RENDER_INFINITYFIELD	10
#define BUILDINGNPC_RENDER_INFINITYSHOP		11
// end 2009. 11. 02 by ckPark 인피니티 필드 인스턴스 던젼 시스템

// 2010. 04. 21 by jskim 신규 럭키 머신 구현
#define BUILDINGNPC_RENDER_OPTIONMACHINE	12
// 2010. 04. 21 by jskim 신규 럭키 머신 구현

// 2010-08-31 by shcho&&jskim, 용해 시스템 구현
#define BUILDINGKIND_RENDER_DISSOLUTION		13
// end 2010-08-31 by shcho&&jskim, 용해 시스템 구현

#define CITY_NPCTALK_LINE_FONT_NUMBER		4
//#define CITY_NPCTALK_LINE_STRING_NUMBER		10

#define CITY_FOG_COLOR			D3DCOLOR_ARGB(0,55,65,70)
#define CITY_FOG_START			50.0f
#define CITY_FOG_END			620.0f

#define CITY_NPC_BUTTON_MAIN	0
#define CITY_NPC_BUTTON_MISSION	1
#define CITY_NPC_BUTTON_CLOSE	2
#define CITY_NPC_BUTTON_CREATE	3
#define CITY_NPC_BUTTON_APP		4
#define CITY_NPC_BUTTON_CANCEL	5
#define CITY_NPC_BUTTON_QUICK	6


// 좌표
#define CITY_BASE_BUTTON_SIZE_X				65
#define CITY_BASE_BUTTON_SIZE_Y				19

#define CITY_BASE_UP_BOX_HEIGHT				30
//#define CITY_BASE_DOWN_BOX_HEIGHT			84
#define CITY_BASE_DOWN_BOX_HEIGHT			62
#define CITY_BASE_DOWN_BOX_START_Y			(Pointer_CD3DApplication->GetBackBufferDesc().Height-CITY_BASE_DOWN_BOX_HEIGHT)

#define CITY_BASE_DOWN_NPC_INTERVAL			14//34
#define CITY_BASE_NPC_BOX_SIZE_X			720
#define CITY_BASE_NPC_BOX_SIZE_Y			104//84
#define CITY_BASE_NPC_BOX_START_X			((Pointer_CD3DApplication->GetBackBufferDesc().Width - CITY_BASE_NPC_BOX_SIZE_X ) /2 )
#define CITY_BASE_NPC_BOX_START_Y			(Pointer_CD3DApplication->GetBackBufferDesc().Height - \
										(CITY_BASE_NPC_BOX_SIZE_Y+CITY_BASE_DOWN_NPC_INTERVAL+CITY_BASE_DOWN_BOX_HEIGHT) )
#define CITY_BASE_NPC_BUTTON_START_X		(CITY_BASE_NPC_BOX_START_X+18)
#define CITY_BASE_NPC_BUTTON_START_Y		(CITY_BASE_NPC_BOX_START_Y+77) // 57
#define CITY_BASE_NPC_BUTTON_POS_X_INTERVAL	67	// 다음 버튼의 X위치
#define CITY_BASE_NPC_CLOSE_BUTTON_START_X	(CITY_BASE_NPC_BOX_START_X+CITY_BASE_NPC_BOX_SIZE_X-80)
#define CITY_BASE_NPC_CLOSE_BUTTON_START_Y	(CITY_BASE_NPC_BOX_START_Y+77) // 57
#define CITY_BASE_NPC_CREATE_BUTTON_X		(CITY_BASE_NPC_BOX_START_X + CITY_BASE_NPC_BOX_SIZE_X-148)
#define CITY_BASE_NPC_CREATE_BUTTON_Y		(CITY_BASE_NPC_BOX_START_Y+77)
#define CITY_BASE_NPC_APP_BUTTON_X			(CITY_BASE_NPC_CREATE_BUTTON_X)
#define CITY_BASE_NPC_APP_BUTTON_Y			(CITY_BASE_NPC_CREATE_BUTTON_Y - 23)
// 빠른신청.
#define CITY_BASE_NPC_QUICKAPP_BUTTON_X		(CITY_BASE_NPC_CREATE_BUTTON_X)
#define CITY_BASE_NPC_QUICKAPP_BUTTON_Y		(CITY_BASE_NPC_CREATE_BUTTON_Y - 51)
#define CITY_BASE_NPC_QUICKAPP_BUTTON_W		134
#define CITY_BASE_NPC_QUICKAPP_BUTTON_H		26
#define CITY_BASE_NPC_CANCEL_BUTTON_X		(CITY_BASE_NPC_CLOSE_BUTTON_START_X)
#define CITY_BASE_NPC_CANCEL_BUTTON_Y		(CITY_BASE_NPC_APP_BUTTON_Y)
#define CITY_BASE_NPC_TEXT_START_X			(CITY_BASE_NPC_BOX_START_X+22) // 21
#define CITY_BASE_NPC_TEXT_START_Y			(CITY_BASE_NPC_BOX_START_Y+15) // 21
#define CITY_BASE_NPC_TEXT_LINE_INTERVAL	15
#define CITY_BASE_NPC_IMG_SIZE_X			(368-20)// 20 : 여백
#define CITY_BASE_NPC_IMG_SIZE_Y			434//350//316
#define CITY_BASE_NPC_IMG_START_X			(CITY_BASE_NPC_BOX_START_X+CITY_BASE_NPC_BOX_SIZE_X-CITY_BASE_NPC_IMG_SIZE_X)
#define CITY_BASE_NPC_IMG_START_Y			(CITY_BASE_NPC_BOX_START_Y+CITY_BASE_NPC_BOX_SIZE_Y-CITY_BASE_NPC_IMG_SIZE_Y)

#define CITY_BASE_NPC_MISSION_SIZE_X		468
#define CITY_BASE_NPC_MISSION_SIZE_Y		308

#define CITY_BASE_WARP_SIZE_X				233
#define CITY_BASE_WARP_SIZE_Y				201

#define NPC_BUTTON_ITEM_SHOP				0
#define NPC_BUTTON_STORE_SHOP				1
#define NPC_BUTTON_WARP						2
#define NPC_BUTTON_MISSION					3
#define NPC_BUTTON_RACING_SHOP				4
#define NPC_BUTTON_ACTIONHOUSE				5
#define NPC_BUTTON_CLOSE					6
#define NPC_BUTTON_LABORATORY				7
#define NPC_BUTTON_FACTORY					8
#define NPC_BUTTON_OCCUPY_INFO				9
#define NPC_BUTTON_CASH_SHOP				10
#define NPC_BUTTON_NUMBER					11

// x : 버튼의 개수
#define CITY_BASE_DOWN_BUTTON_START_X(x)	(Pointer_CD3DApplication->GetBackBufferDesc().Width/2 - \
											((x/2*CITY_BASE_NPC_BUTTON_POS_X_INTERVAL-1) + \
											 ((x%2)*(CITY_BASE_BUTTON_SIZE_X+1)/2)))
#define CITY_BASE_DOWN_BUTTON_START_Y		(CITY_BASE_DOWN_BOX_START_Y + 8)
#define CITY_BASE_DOWN_OUTDOOR_BUTTON_START_X	(Pointer_CD3DApplication->GetBackBufferDesc().Width - 81)

#define SKILL_SHOP_SPI_START_X				(CITY_BASE_NPC_BOX_START_X+301)
#define SKILL_SHOP_SPI_START_Y				(CITY_BASE_NPC_BOX_START_Y - SIZE_NORMAL_WINDOW_Y + 235)

// 2008-08-22 by bhsohn EP3 인벤토리 처리
// 아이템 인벤 위치
#define INVEN_ITEM_START_X			0
#define INVEN_ITEM_START_Y			241
// 장비 인벤 위치
#define INVEN_EQ_START_X			429
#define INVEN_EQ_START_Y			241

// 상점에서의 인벤위취
#define INVEN_ITEM_SHOP_START_X			(CITY_BASE_NPC_BOX_START_X)
#define INVEN_ITEM_SHOP_START_Y			(CITY_BASE_NPC_BOX_START_Y-SIZE_NORMAL_WINDOW_Y)
#define INVEN_EQ_SHOP_START_X			(CITY_BASE_NPC_BOX_START_X+426)
#define INVEN_EQ_SHOP_START_Y			(CITY_BASE_NPC_BOX_START_Y-2*SIZE_NORMAL_WINDOW_Y)
// end 2008-08-22 by bhsohn EP3 인벤토리 처리

// 2006-03-07 by ispark, 언어에 따라 위치 수정
#if defined(LANGUAGE_ENGLISH) || defined(LANGUAGE_VIETNAM)|| defined(LANGUAGE_THAI)// 2008-04-30 by bhsohn 태국 버전 추가
#define CITY_NPCTALK_SIZE					120//75
#else
#define CITY_NPCTALK_SIZE					75
#endif

class CINFImage;
class CINFCityWarp;
class CD3DHanFont;
class CINFCityMission;
class CINFScrollBar;
class DataHeader;
typedef struct
{
	CINFImage* m_pButton[CITY_BUTTON_NUMBER];
	BUILDINGNPC buildingInfo;
} GUI_BUILDINGNPC;

typedef map<int, GUI_BUILDINGNPC*>				CMapCityGroupList;				// 도시 상점 정보
typedef map<int, GUI_BUILDINGNPC*>::iterator	CMapCityGroupIterator;
typedef map<int, int>							CMapButtonState;
typedef map<int, int>::iterator					CMapButtonStateIterator;
typedef map<int, CINFBase*>						CMapCityShopList;
typedef map<int, CINFBase*>::iterator			CMapCityShopIterator;

class CINFCityBase : public CINFBase
{
public:
	CINFCityBase(CAtumNode* pParent);
	virtual ~CINFCityBase();

	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	
	virtual void Tick();
	virtual int WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual int WebWndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	

public:
	CMapCityShopList	m_mapCityShop;	// map[buildlingKind] = CINFBase;
	CINFCityMission* m_pMission;
	char				m_strGuildMasterGr[512];


	BOOL				m_bRestored;

	CINFImage* m_pNPCBoxImage[9];
	CINFImage* m_pDownBoxImage[2];
	CINFImage* m_pUpBoxImage[2];
	CINFImage* m_pNPCButtonImage[NPC_BUTTON_NUMBER][CITY_BUTTON_NUMBER];

	CINFImage* m_pImgCreateB[CITY_BUTTON_NUMBER];					// 아레나 생성버튼.
	CINFImage* m_pImgAppB[CITY_BUTTON_NUMBER];					// 아레나 신청버튼.
	CINFImage* m_pImgQuickAppB[CITY_BUTTON_NUMBER];				// 아레나 빠른 신청 버튼.
	CINFImage* m_pImgCancelB[CITY_BUTTON_NUMBER];					// 취소 버튼.

	int					m_nNPCButtonState[3];
	CINFImage* m_pOutDoorButtonImage[CITY_BUTTON_NUMBER];

	int					m_nOutDoorButtonState;

	UINT				m_nCreateB;											// 아레나 생성 버튼.
	UINT				m_nAppB;											// 아레나 신청 버튼.
	UINT				m_nQuickAppB;										// 빠른 신청 버튼상태.
	UINT				m_nCancelB;											// 취소 버튼.

//	CMapCityGroupList	m_mapButtonGroup;// map[buidlingIndex] = GUI_BUILDINGNPC
	vector<GUI_BUILDINGNPC*>	m_vecButtonGroup;// map[buidlingIndex] = GUI_BUILDINGNPC
	CMapButtonState		m_mapButtonState;// map[rendering order] = button state;
	GUI_BUILDINGNPC*	m_pCurrentBuildingNPC; // 현재 화면에 렌더링할 NPC화면
	int					m_nCurrentEnterBuildingIndex;
	int					m_nCurrentBuildingNPCState;// 화면에 보여지는 NPC화면의 렌더링 상태( BUILDINGNPC_RENDER_TALKBOX, SHOP, MISSION )
	//char				m_strNPCTalk[CITY_NPCTALK_LINE_STRING_NUMBER][CITY_NPCTALK_SIZE];
	vector<string>		m_vecNPCTalk;
	CD3DHanFont* m_pFontNPCTalk[CITY_NPCTALK_LINE_FONT_NUMBER];
	int					m_nNextEnterBuilding;
	CINFScrollBar* m_pNPCScroll;

	DataHeader* m_pDataHeader;
	CINFImage* m_pNPCImage;
	float				m_fCurrentShowTimeTime;

	CINFImage* m_pWebTitleBarImage;
	CINFImage* m_pRenewShopImage;

	// 2008-03-27 by bhsohn 미션성공창이 떠있는 상태에서는 상점이 안열리게 변경
	BOOL				m_bForceClose;	// 윈도우창 강제 종료
};

#endif // !defined(AFX_INFCITYBASE_H__79E1DB05_7EE1_486A_8C14_5A021065FC0D__INCLUDED_)
