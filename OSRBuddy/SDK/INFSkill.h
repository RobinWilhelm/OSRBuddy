// INFSkill.h: interface for the CINFSkill class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFSKILL_H__86964810_B32C_47B6_B7C0_5C6A8B1CB8B7__INCLUDED_)
#define AFX_INFSKILL_H__86964810_B32C_47B6_B7C0_5C6A8B1CB8B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INFBase.h"
#include "INFImage.h"
// 2010. 03. 31 by jskim 사용류 아이템 보여주는 아이콘 팁 변경
//#include "INFItemInfo.h"
//end 2010. 03. 31 by jskim 사용류 아이템 보여주는 아이콘 팁 변경
class CSkillInfo;
class CD3DHanFont;

// 2010. 03. 31 by jskim 사용류 아이템 보여주는 아이콘 팁 변경
#define BOX_MARGIN		 6
#define LINE_INTERVAL	 1
//end 2010. 03. 31 by jskim 사용류 아이템 보여주는 아이콘 팁 변경

typedef struct {
	CSkillInfo* pItemSkill;
	CD3DHanFont* pSkillFont;
	// 2010. 03. 31 by jskim 사용류 아이템 보여주는 아이콘 팁 변경
	vector<string>	m_strSkillInfo;
	// 2010. 03. 31 by jskim 사용류 아이템 보여주는 아이콘 팁 변경
} SkillFontInfo;

typedef struct {
	ITEM* pItemInfo;
	UID64_t			ItemUID;
	CD3DHanFont* pItemFont;
	float			fRemainedTime;
	BOOL			bUseItemFinish;
	// 2008-03-05 by bhsohn 느린 시스템에서 시간제 아이템 시간 계산이 잘못 되는 부분 수정
	BOOL			bFirstTimeCheck;	// 처음 시간 계산함
	// 2010. 03. 31 by jskim 사용류 아이템 보여주는 아이콘 팁 변경
	vector<string>	m_strItemInfo;
	// 2010. 03. 31 by jskim 사용류 아이템 보여주는 아이콘 팁 변경
} ItemFontInfo;


class CINFSkill : public CINFBase
{
	friend class CSkill;
public:
	CINFSkill();
	virtual ~CINFSkill();
	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();

	vector<SkillFontInfo*>		m_vecSkillFontInfo;
	vector<ItemFontInfo*>		m_vecItemFontInfo;

	// 2010. 02. 11 by ckPark 발동류 장착아이템
	// 발동류 아이템 버프
	vector<ItemFontInfo*>		m_vecItemBuffInfo;
	// end 2010. 02. 11 by ckPark 발동류 장착아이템

	CINFImage* m_pGroundTarget;
	LPDIRECT3DVERTEXBUFFER9		m_pVBGroundTarget;
	D3DXMATRIX					m_mGroundTargetMatrix;

	CD3DHanFont* m_pToolTipFont;

	// 2010-09-29 by jskim, SpriteDevice Lost 되었을 때 구조 변경
	//LPD3DXSPRITE				m_pToolTipSprite;
	// end 2010-09-29 by jskim, SpriteDevice Lost 되었을 때 구조 변경
	LPDIRECT3DTEXTURE9			m_pToolTipTexture;

	POINT						m_ptMouse;
	// 2010. 03. 31 by jskim 사용류 아이템 보여주는 아이콘 팁 변경
	CINFImage* m_pInfoBoxSide[9];
	//end 2010. 03. 31 by jskim 사용류 아이템 보여주는 아이콘 팁 변경
};

#endif // !defined(AFX_INFSKILL_H__86964810_B32C_47B6_B7C0_5C6A8B1CB8B7__INCLUDED_)
