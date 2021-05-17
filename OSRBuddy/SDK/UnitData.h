// UnitData.h: interface for the CUnitData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNITDATA_H__2D386C99_DEB3_45E7_A7B5_A88B6CB2666D__INCLUDED_)
#define AFX_UNITDATA_H__2D386C99_DEB3_45E7_A7B5_A88B6CB2666D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AtumData.h"




// 2007-04-02 by bhsohn Move��Ŷ���� ���� ���� üũ
#define	UNIT_STATE_INVISIBLE	0
#define	UNIT_STATE_CHARINGSHOT	1
#define	UNIT_STATE_HYPERSHOT	2
#define	UNIT_STATE_MAX			3

#define	BGEAR_STATE_CHARINGSHOT		7800060		// ��¡�� 
#define	AGEAR_STATE_HYPERSHOT		7823060		// �����ۼ� 

// 2007-05-17 by bhsohn ������Ʈ �ڿ� �������� �� ���� ó �˻� ó��
#define	CHECK_OBJECT_TIME		1.0f

///////////////////////////////////////////////////////////////////////////////
/// \class		CUnitData
///
/// \brief		CShuttleChild, CEnemyData, CMonsterData�� �θ�μ�, ����κ� ó��
/// \author		dhkwon
/// \version	
/// \date		2004-03-20 ~ 2004-03-20
/// \warning	
///////////////////////////////////////////////////////////////////////////////
class CSkillEffect;
class CItemData;
class CPetManager;		// 2010-06-15 by shcho&hslee ��ý��� - Ŭ���� �߰�
class CUnitData : public CAtumData
{
	friend class CAtumApplication;	// ���Ŀ� ���� ��.
	friend class CUnitRender;		// m_pVBShadow �� ����
	friend class CCharacterRender;	// 2005-07-13 by ispark
	friend class CMonsterRender;	// m_pVBShadow �� ����
public:
	CUnitData();
	virtual ~CUnitData();
public:

	// ����
	virtual void CreateSecondaryShieldDamage(D3DXVECTOR3 vCollPos) {};	 		

	// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
	//virtual void CheckAttack(ATTACK_DATA &attackData, BOOL bReset, ITEM* pWeaponITEM);
	virtual void CheckAttack(ATTACK_DATA& attackData, BOOL bReset, ITEM* pWeaponITEM = NULL, ITEM* pEffectItem = NULL);
	// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
	

	// 2007-05-17 by bhsohn ������Ʈ �ڿ� �������� �� ���� ó �˻� ó��
	virtual BOOL	IsCheckObjectShow();
	virtual BOOL	IsCheckObjectColl();
	// 2010. 03. 18 by jskim ���ͺ��� ī��  

protected:		 	
	// ����
	virtual USHORT GetShiftWeaponBodyconditionByUnitKind();

	// end 2009. 07. 07 by ckPark �κ���� ��û����(�Ѹ�, ����ȭ��, ����, A�������)

public:
	CParamFactor			m_paramFactor;			// ParamFactor( Enemy�� ��� 1���� ����,������Ÿ�Ӹ� ����)
	LPDIRECT3DVERTEXBUFFER9 m_pVBShadow;			// �׸��� ����
	char		m_pad1[16];
	char		m_pad2[16];
#ifndef _DEBUG
	char m_padVector[4];
#endif // !_DEBUG


	//////////////////////////////////////////////////////////////////////////
	// ��ų
	vector<CItemData*>		m_pChaffData;			// 2006-12-04 by ispark
	CSkillEffect* m_pSkillEffect;
	int						m_nAlphaValue;			// ���İ�
	BYTE					m_bySkillStateFlag;		// ��ų ���� (����, �κ�����...)
	ClientIndex_t			m_nTargetIndex;					// Enemy�� Ÿ�� �ε���

	// 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����
	int						m_LoadingPriority;
	//end 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����
							  	
	

protected:
	int						m_nUnitNum;				// ex> 12030100 ( 12 : degree, 03 : amor, 01 : unitKind )
	int						m_nPilotNum;			// 2005-07-13 by ispark	���Ϸ�Ʈ �ѹ�
	BOOL					m_bCharacter;			// 2005-07-13 by ispark (Unit : FALSE, Character : TRUE)
	DWORD					m_dwPkState;
	BOOL					m_bPkAttack;			// 2005-11-03 by ispark PK ���� �����Ѱ�, m_dwPkState�� Normal�̾ �̰��� TRUE�̸� ���� �� ����

	// 2007-04-02 by bhsohn Move��Ŷ���� ���� ���� üũ
	BYTE					m_byUnitState;
	FLOAT					m_fUnitStateChgCap[UNIT_STATE_MAX];		// ���� ���°� ����Ǿ��־��� �ð� 

	// 2007-05-17 by bhsohn ������Ʈ �ڿ� �������� �� ���� ó �˻� ó��
	BOOL					m_bCheckObjectEnemyShow;		// ������Ʈ �ڿ� �������� �� ���� ó �˻� ó��
	BOOL					m_bCheckObject;					// ������Ʈ üũ
	float					n_fCheckObjectTime;
	// 2010. 03. 18 by jskim ���ͺ��� ī��
	int						m_MonsterTransformer;
	D3DXVECTOR3				m_MonsterTransPrimarySidePos;
	D3DXVECTOR3				m_MonsterTransSecondarySidePos;
	float					m_MonsterTransScale;
	//end 2010. 03. 18 by jskim ���ͺ��� ī��
							   	
	CPetManager* m_pPetManager;
};

#endif // !defined(AFX_UNITDATA_H__2D386C99_DEB3_45E7_A7B5_A88B6CB2666D__INCLUDED_)
