// MonsterData.h: interface for the CMonsterData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MONSTERDATA_H__F06CA2D1_F4C9_4EF2_B607_B83D503B400C__INCLUDED_)
#define AFX_MONSTERDATA_H__F06CA2D1_F4C9_4EF2_B607_B83D503B400C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UnitData.h"

/*
typedef struct
{
	ClientIndex_t	MonsterIndex;
	INT				CurrentHP;
	INT				MonsterUnitKind;
	SHORT			MonsterForm;
	AVECTOR3		PositionVector;
	AVECTOR3		TargetVector;
	BodyCond_t		BodyCondition;
	INT				MaxHP;
} MSG_FC_CHARACTER_GET_MONSTER_INFO_OK;
*/

class CCinema;
class CMonRender;
class CAppEffectData;
class CSkinnedMesh;
class CMonsterData : public CUnitData
{
public:
	virtual ~CMonsterData();
	virtual void Tick();
	virtual void Render();
	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
												
	// 2007-05-17 by bhsohn ������Ʈ �ڿ� �������� �� ���� ó �˻� ó��
	virtual BOOL	IsCheckObjectShow();
	virtual BOOL	IsCheckObjectColl();	   

public:	   	
	CAtumData* m_pTarget;
	FLOAT				m_fTargetCheckTime;

	D3DXVECTOR3			m_vNextVel;
	D3DXVECTOR3			m_vOldPos;

	// ������ ��ų ���� ���� 2004.06.26 jschoi
	D3DXVECTOR3			m_vOldSkillEndPos;
	D3DXVECTOR3			m_vOldSkillEndVel;
	D3DXVECTOR3			m_vOldSkillEndUp;

	D3DXVECTOR3			m_vExpectPos;

	D3DXVECTOR3			m_vMovepos;
	D3DXVECTOR3			m_vMoveup;

	D3DXVECTOR3			m_vAttackVel;

	FLOAT				m_fLeanRate;				// �¿� ������ ����

//	BYTE				m_nMonsterTypePrimary;		// Ÿ�� ������ ���
//	BYTE				m_nMonsterTypeSecondary;	// Ÿ�� ������ ���
	BOOL				m_bRenderState;				// ������ ����(�������)
//	INT					m_nRenderType;
	FLOAT				m_fLifeTime;
	BOOL				m_bCheckColl;
	BOOL				m_bAlphaBlending;
	//	BOOL				m_bIsRender;				// ȭ�� ������ ����� ������ ���� �ʴ���
		///////////////// �߶� Time /////////////////////
	FLOAT				m_fFallingTime;				// �߶��� Check Time
	D3DMATERIAL9		m_material;
	FLOAT				m_fMaterialCheckTime;


	FLOAT				m_fMaxHP;
	BOOL				m_bRenderHP;
	D3DXMATRIX			m_mScale;
	POINT				m_ptCurRegion;					// ���� �� ������
	POINT				m_ptOldRegion;					// ���� ���� �� ������

	INT					m_nUpDir;						// �ʺ� ����Ʈ �̼��� ���� ���� ����
	INT					m_nSideDir;						// �ʺ� ����Ʈ �̼��� ���� ���� ����

	CMonRender* m_pRenderer;

	CAppEffectData* m_pEffectTarget;

	MSG_FC_CHARACTER_GET_MONSTER_INFO_OK	m_info;
	MEX_MONSTER_INFO* m_pMonsterInfo;
	MONSTERINFO			m_ResInfo;

	// ���� ��ų ���� 2004.06.25 jschoi
	int					m_nMonsterSkillState;			// ���Ͱ� ��ų�� ����
	BOOL				m_bSkillEnd;					// ��ų�� ���Ḧ ���� ������ �����ؾ��Ѵ°�?
	CCinema* m_pMonsterMovePattern;
	CSkinnedMesh* m_pMonMesh;

	ClientIndex_t		m_nTargetIndex;					// ������ Ÿ�� �ε���
	// 2010. 03. 18 by ckPark ���Ǵ�Ƽ �ʵ� 2��(���� ��ų �߰�)
	std::map<INT, ITEM*>	m_mapMonsterBuffSkill;	   	   
	// end 2010. 03. 18 by ckPark ���Ǵ�Ƽ �ʵ� 2��(���� ��ų �߰�)

	// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
	vector<MULTI_TARGET_DATA*>	m_vecvmultiData;
	vectorMonsterMultiTarget	m_vecMonMultiInfo;
	int							m_nindexSize;
	int							m_nMultiIndex;
	int							m_nSiegeIndex;
	BOOL						m_bSiegeMode;
	// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
};

#endif // !defined(AFX_MONSTERDATA_H__F06CA2D1_F4C9_4EF2_B607_B83D503B400C__INCLUDED_)
