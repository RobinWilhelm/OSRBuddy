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
// 2010. 03. 31 by jskim ���� ������ �����ִ� ������ �� ����
//#include "INFItemInfo.h"
//end 2010. 03. 31 by jskim ���� ������ �����ִ� ������ �� ����
class CSkillInfo;
class CD3DHanFont;

// 2010. 03. 31 by jskim ���� ������ �����ִ� ������ �� ����
#define BOX_MARGIN		 6
#define LINE_INTERVAL	 1
//end 2010. 03. 31 by jskim ���� ������ �����ִ� ������ �� ����

typedef struct {
	CSkillInfo* pItemSkill;
	CD3DHanFont* pSkillFont;
	// 2010. 03. 31 by jskim ���� ������ �����ִ� ������ �� ����
	vector<string>	m_strSkillInfo;
	// 2010. 03. 31 by jskim ���� ������ �����ִ� ������ �� ����
} SkillFontInfo;

typedef struct {
	ITEM* pItemInfo;
	UID64_t			ItemUID;
	CD3DHanFont* pItemFont;
	float			fRemainedTime;
	BOOL			bUseItemFinish;
	// 2008-03-05 by bhsohn ���� �ý��ۿ��� �ð��� ������ �ð� ����� �߸� �Ǵ� �κ� ����
	BOOL			bFirstTimeCheck;	// ó�� �ð� �����
	// 2010. 03. 31 by jskim ���� ������ �����ִ� ������ �� ����
	vector<string>	m_strItemInfo;
	// 2010. 03. 31 by jskim ���� ������ �����ִ� ������ �� ����
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

	// 2010. 02. 11 by ckPark �ߵ��� ����������
	// �ߵ��� ������ ����
	vector<ItemFontInfo*>		m_vecItemBuffInfo;
	// end 2010. 02. 11 by ckPark �ߵ��� ����������

	CINFImage* m_pGroundTarget;
	LPDIRECT3DVERTEXBUFFER9		m_pVBGroundTarget;
	D3DXMATRIX					m_mGroundTargetMatrix;

	CD3DHanFont* m_pToolTipFont;

	// 2010-09-29 by jskim, SpriteDevice Lost �Ǿ��� �� ���� ����
	//LPD3DXSPRITE				m_pToolTipSprite;
	// end 2010-09-29 by jskim, SpriteDevice Lost �Ǿ��� �� ���� ����
	LPDIRECT3DTEXTURE9			m_pToolTipTexture;

	POINT						m_ptMouse;
	// 2010. 03. 31 by jskim ���� ������ �����ִ� ������ �� ����
	CINFImage* m_pInfoBoxSide[9];
	//end 2010. 03. 31 by jskim ���� ������ �����ִ� ������ �� ����
};

#endif // !defined(AFX_INFSKILL_H__86964810_B32C_47B6_B7C0_5C6A8B1CB8B7__INCLUDED_)
