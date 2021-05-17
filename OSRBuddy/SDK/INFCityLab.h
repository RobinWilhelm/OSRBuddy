// INFCityStore.h: interface for the CINFCityLab class.
// 2004.07.15 ydKim
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFCITYLAB_H__AD058082_959A_4B02_BEDD_AAE54DE7B3E0__INCLUDED_)
#define AFX_INFCITYLAB_H__AD058082_959A_4B02_BEDD_AAE54DE7B3E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INFBase.h"

// 2008-03-14 by bhsohn 조합식 개선안
//#include "INFNumEditBox.h"
class CINFNumEditBox;

#define LAB_BUTTON_NUMBER			3

class CINFImage;
class CD3DHanFont;

class CINFCityLab : public CINFBase
{
public:
	CINFCityLab(CAtumNode* pParent, BUILDINGNPC* pBuilding);
	virtual ~CINFCityLab();

	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual void Render();
	virtual void Tick();
	virtual int WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	char m_pad01[16];

	CItemInfo* m_pSelectItem;
	BOOL				m_bIsEnchantCheck; 

	BOOL				m_bRestored;

	CINFImage* m_pImgButton[LAB_BUTTON_NUMBER][4];	// 0 : 제조(SEND), 1 : cancel, 2 : ok
	int					m_nButtonState[2];

	CINFImage* m_pImgBack;
	CINFImage* m_pImgBackFactory;	// 연구소배경 // 2008-03-14 by bhsohn 조합식 개선안

	CINFImage* m_pImgTitle;
	CINFImage* m_pImgPrice;
	// 2008-03-14 by bhsohn 조합식 개선안
	CINFNumEditBox* m_pNumEditBox;

	CD3DHanFont* m_pFontPrice;
	char				m_szPrice[64];
	vector<CItemInfo*>  m_vecSource;
	vector<CItemInfo*>  m_vecTarget;
	BOOL				m_bShowTarget;
	BUILDINGNPC* m_pBuildingInfo;

	BOOL				m_bSelectDown;

};

#endif // !defined(AFX_INFCITYSTORE_H__AD058082_959A_4B02_BEDD_AAE54DE7B3E0__INCLUDED_)
