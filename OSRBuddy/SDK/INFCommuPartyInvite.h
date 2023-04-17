#pragma once

#define		MAX_INVITE_USER			5

class CINFImageBtn;
class CINFEditBox;
class CINFImageRadioBtn;
class CINFImage;
class CD3DHanFont;

#include "INFBase.h"
#include "AtumProtocol.h"

class CINFCommuPartyInvite : public CINFBase
{
public:
	virtual ~CINFCommuPartyInvite();

	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual void	Tick();

public:
	CINFImage* m_pFormat;

	BOOL		m_bMove;
	BOOL		m_bShow;

	POINT		m_ptCommOpBk;
	POINT		m_ptCommOpMouse;

	CINFImageBtn* m_pInviteBtn;			// 초대

	CINFImageBtn* m_pRefreshBtn;			// 새로고침
	CINFImageBtn* m_pSelInviteBtn;			// 초대
	CINFImageBtn* m_pCloseBtn;			// 닫기

	CINFEditBox* m_pEditUser;		// 받는 유저
	CD3DHanFont* m_pFontText;

	vector<SRECOMMENDATION_MEMBER_INFO>	m_vecPartyInviteInfo;

	CINFImageRadioBtn* m_pPartyJoint[MAX_INVITE_USER];

};