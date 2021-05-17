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
#define INVEN_NUMBER	(INVEN_X_NUMBER*INVEN_Y_NUMBER)	// �� �κ���
#define WEAR_ITEM_NUMBER 9

#define INVEN_ROTATION_NUM		5	// �����̼� �̹��� 
#define INVEN_ROTATION_STATE	2	// �����̼� �̹��� 

#define INVEN_SLOT_SIZE			30
#define INVEN_SLOT_INTERVAL		32
#define INVEN_ITEM_SLOT_START_X 309
#define INVEN_ITEM_SLOT_START_Y 30

// �κ�â ����
#define INVEN_ITEM_WND			0	// ������ â
#define INVEN_EQ_WND			1	// ���â


class CGameData;
class CINFImage;
class CD3DHanFont;
class CItemInfo;

class CINFInvenEquip;
class CINFInvenItem;

typedef struct
{
	INT			CurrentCount;
	UID64_t		UniqueNumber;					// ������ ������ȣ
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

	// 2010-06-15 by shcho&hslee ��ý��� - ����ǰ �ִ� ���� ����.
	//INVEN_DISPLAY_INFO *m_pWearDisplayInfo[WEAR_ITEM_NUMBER];
	INVEN_DISPLAY_INFO* m_pWearDisplayInfo[MAX_EQUIP_POS];

	//int					m_nInvenCurrentScroll;
	//int					m_nInvenCurrentScrollPosition;

	POINT				m_ptMouse;

	CINFImage* m_pSelectIcon;// ���콺 Ŭ���� ���� ���õ� ������ �̹���(reference)
	CItemInfo* m_pSelectItem;// ������ ������(reference)

	// ������ ������, �޸� ���� ����
	//CItemInfo*			m_pDeleteItem;// ���� ������ ������
	structDelItemInfo		m_struDeleteItem;

	//	int					m_nSelectItemWindowPosition;// Ŭ���� �������� Window������ ��ġ // 2006-06-21 by ispark, m_SelectItem->ItemWindowIndex �� ������ ����� ��

	BOOL				m_bEnchantState;
	CItemInfo* m_pEnchantItem;

	int					m_nRenderMoveIconIntervalHeight;
	int					m_nRenderMoveIconIntervalWidth;

	INVEN_DISPLAY_INFO* m_pCurrentItemInfo;// ���� �������� �ִ� ������ ����

	BOOL				m_bSelectWearItem;
	BOOL				m_bMouseDownState;

	//////////////////////////////////////////////////////////////////////////	
	// ���� �κ��丮 �̹��� (�����̹����� ������ ��ȯâ ������ ���� ���� ���
	// ydkim 2005.11.04
	// ���� ������ �Լ����� �ʿ�	

	// 2011-07-22 by hsson �� �ߺ� �������� ��æƮ �Ǵ� ���� ����
	enum { SHOP_CONCURRENT_DELAY = 200, };
	DWORD				m_bShopConcurrent;
	// end 2011-07-22 by hsson �� �ߺ� �������� ��æƮ �Ǵ� ���� ����

public:

	// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
	// �κ��丮
	CINFInvenEquip* m_pINFInvenEquip;	// ����â
	CINFInvenItem* m_pINFInvenItem;	// ������ â
	deque<int>			m_vecWndOrder;

	POINT				m_pEqIvenNormalPos;
	BOOL				m_bEqSetPos;		// ��ġ�� �����߳�?

	POINT				m_pEqIvenShopPos;
	BOOL				m_bEqShopSetPos;		// ��ġ�� �����߳�?

	POINT				m_pItemIvenPos;
	BOOL				m_bItemSetPos;		// ��ġ�� �����߳�?


	BOOL				m_bShowEqWnd;		// �Ϲ� ���â
	BOOL				m_bShowEqShopWnd;	// ���� ���â

};

#endif // !defined(AFX_INFINVENEXTEND_H__72C927DE_F4B8_40AF_8E52_F525B1E5541E__INCLUDED_)
