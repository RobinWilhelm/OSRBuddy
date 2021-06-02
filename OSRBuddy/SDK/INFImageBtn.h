// INFImageBtn.h: interface for the CINFImageBtn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFIMAGEBTN_H__30BBF036_84B2_46BF_A6EF_8ADF9C968B2F__INCLUDED_)
#define AFX_INFIMAGEBTN_H__30BBF036_84B2_46BF_A6EF_8ADF9C968B2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INFBase.h"

#define	BTN_STATUS_UP		0
#define	BTN_STATUS_DOWN		1
#define	BTN_STATUS_SEL		2
#define	BTN_STATUS_DISABLE	3
#define	MAX_BTN_STATUS		4

class CINFImageBtn : public CINFBase
{
public:
	CINFImageBtn();
	virtual ~CINFImageBtn();


	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();

	virtual BOOL IsMouseOverlab(POINT ptPos);			

	CINFImage* m_pImageBtn[MAX_BTN_STATUS];
	int				m_nBtnStatus;

	float			m_fPosX;
	float			m_fPosY;

	float			m_fWidth;
	float			m_fHeight;

	// 2007-06-12 by bhsohn 미션 인터페이스 수정안
	BOOL			m_bShowBtn;

	// 2007-07-04 by bhsohn 오퍼레이터 추가
	BOOL			m_bBlingBtn;
	float			m_fBlingTime;
	float			m_fCapBlingTime;

	BOOL			m_bClick;

	// 2008-05-13 by dgwoo 눌러지는 버튼인가?
	BOOL			m_bPush;

};

#endif // !defined(AFX_INFIMAGEBTN_H__30BBF036_84B2_46BF_A6EF_8ADF9C968B2F__INCLUDED_)
