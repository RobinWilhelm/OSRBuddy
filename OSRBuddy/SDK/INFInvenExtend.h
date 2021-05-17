// INFInvenExtend.h: interface for the CINFInvenExtend class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFINVENEXTEND_H__72C927DE_F4B8_40AF_8E52_F525B1E5541E__INCLUDED_)
#define AFX_INFINVENEXTEND_H__72C927DE_F4B8_40AF_8E52_F525B1E5541E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INFBase.h"
#include "atumparam.h"
//#include "RangeTime.h"



#define INVEN_X_NUMBER	10
#define INVEN_Y_NUMBER	6
#define INVEN_NUMBER	(INVEN_X_NUMBER*INVEN_Y_NUMBER)	// 총 인벤수
#define WEAR_ITEM_NUMBER 9

#define INVEN_ROTATION_NUM		5	// 로테이션 이미지 
#define INVEN_ROTATION_STATE	2	// 로테이션 이미지 

#define INVEN_SLOT_SIZE			30
#define INVEN_SLOT_INTERVAL		32
#define INVEN_ITEM_SLOT_START_X 309
#define INVEN_ITEM_SLOT_START_Y 30

// 인벤창 순서
#define INVEN_ITEM_WND			0	// 아이템 창
#define INVEN_EQ_WND			1	// 장비창


class CGameData;
class CINFImage;
class CD3DHanFont;
class CItemInfo;

class CINFInvenEquip;
class CINFInvenItem;

typedef struct
{
	INT			CurrentCount;
	UID64_t		UniqueNumber;					// 아이템 고유번호
} structDelItemInfo;

class CINFInvenExtend : public CINFBase
{
public:
	CINFInvenExtend(CAtumNode* pParent);
	virtual ~CINFInvenExtend();

	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects(); 
	virtual void	Tick();

	virtual int		WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL bShowInven = FALSE);

public:
	//CGameData *		m_pGameData;
	BOOL			m_bRestored;
	BOOL			m_bInvalidated;

	CINFImage* m_pItemSl;

	CD3DHanFont* m_pFontSpi;
	CD3DHanFont* m_pFontWeight[3];
	CD3DHanFont* m_pFontItemNum[INVEN_Y_NUMBER];
	int				m_nItemSpi;
	LONGLONG		m_hyItemSpiUniqueNumber;

	// [0][1] ... [5]
	// [6] ...
	// [12] ...
	INVEN_DISPLAY_INFO* m_pInvenDisplayInfo[INVEN_NUMBER];
	//	[2]	[0]	[4]	
	//	[1]	[5]	[3]
	//	[8]	[6]	[7]

	// 2010-06-15 by shcho&hslee 펫시스템 - 장착품 최대 개수 변경.
	//INVEN_DISPLAY_INFO *m_pWearDisplayInfo[WEAR_ITEM_NUMBER];
	INVEN_DISPLAY_INFO* m_pWearDisplayInfo[MAX_EQUIP_POS];

	//int					m_nInvenCurrentScroll;
	//int					m_nInvenCurrentScrollPosition;

	POINT				m_ptMouse;

	CINFImage* m_pSelectIcon;// 마우스 클릭에 의해 선택된 아이콘 이미지(reference)
	CItemInfo* m_pSelectItem;// 아이템 포인터(reference)

	// 아이템 삭제시, 메모리 버그 수정
	//CItemInfo*			m_pDeleteItem;// 지울 아이템 포인터
	structDelItemInfo		m_struDeleteItem;

	//	int					m_nSelectItemWindowPosition;// 클릭된 아이템의 Window에서의 위치 // 2006-06-21 by ispark, m_SelectItem->ItemWindowIndex 이 변수를 쓰기로 함

	BOOL				m_bEnchantState;
	CItemInfo* m_pEnchantItem;

	int					m_nRenderMoveIconIntervalHeight;
	int					m_nRenderMoveIconIntervalWidth;

	INVEN_DISPLAY_INFO* m_pCurrentItemInfo;// 현재 보여지고 있는 아이템 정보

	BOOL				m_bSelectWearItem;
	BOOL				m_bMouseDownState;

	//////////////////////////////////////////////////////////////////////////	
	// 수정 인벤토리 이미지 (기존이미지는 상점및 교환창 변경후 완전 삭제 요망
	// ydkim 2005.11.04
	// 완전 수정후 함수정리 필요	

	// 2011-07-22 by hsson 샾 중복 접속으로 인챈트 되던 버그 수정
	enum { SHOP_CONCURRENT_DELAY = 200, };
	DWORD				m_bShopConcurrent;
	// end 2011-07-22 by hsson 샾 중복 접속으로 인챈트 되던 버그 수정

public:

	// 2008-08-22 by bhsohn EP3 인벤토리 처리
	// 인벤토리
	CINFInvenEquip* m_pINFInvenEquip;	// 장착창
	CINFInvenItem* m_pINFInvenItem;	// 아이템 창
	deque<int>			m_vecWndOrder;

	POINT				m_pEqIvenNormalPos;
	BOOL				m_bEqSetPos;		// 위치를 지정했냐?

	POINT				m_pEqIvenShopPos;
	BOOL				m_bEqShopSetPos;		// 위치를 지정했냐?

	POINT				m_pItemIvenPos;
	BOOL				m_bItemSetPos;		// 위치를 지정했냐?


	BOOL				m_bShowEqWnd;		// 일반 장비창
	BOOL				m_bShowEqShopWnd;	// 상점 장비창

};

#endif // !defined(AFX_INFINVENEXTEND_H__72C927DE_F4B8_40AF_8E52_F525B1E5541E__INCLUDED_)
