// AppEffectData.h: interface for the CAppEffectData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_APPEFFECTDATA_H__015F7554_AAB5_4E73_A7CF_80BFEB534741__INCLUDED_)
#define AFX_APPEFFECTDATA_H__015F7554_AAB5_4E73_A7CF_80BFEB534741__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AtumNode.h"
#include "CharacterInfo.h"
// 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����
#include "AtumDefine.h"
//end 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����

class CCamera;
class CCharacterInfo;
class CAppEffectData : public CAtumNode
{
public:
	// 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����
	//CAppEffectData(CAtumNode * pParent,int nType,D3DXVECTOR3 vPos, int nWeaponPositionIndex = 0);
	//CAppEffectData(CCamera * pParent,int nType,float fDist = 0, float fSide = 0,float fUp = 0);
	//CAppEffectData(int nType,D3DXVECTOR3 vPos, float fVelRate,D3DXVECTOR3 vVel);
	//CAppEffectData(int nType,D3DXVECTOR3 vPos);
	//CAppEffectData(GUIUnitRenderInfo * pParent,int nType);
	//ysw 9_22
	//CAppEffectData(CAtumNode * pParent2, CCamera * pParent, int nType, D3DXVECTOR3 vPos,float fDist = 0, float fSide = 0,float fUp = 0);
//
	CAppEffectData(CAtumNode* pParent, int nType, D3DXVECTOR3 vPos, int nWeaponPositionIndex = 0, int LoadingPriority = _NOTHING_STEP);
	CAppEffectData(CCamera* pParent, int nType, float fDist = 0, float fSide = 0, float fUp = 0, int LoadingPriority = _NOTHING_STEP);
	CAppEffectData(int nType, D3DXVECTOR3 vPos, float fVelRate, D3DXVECTOR3 vVel, int LoadingPriority = _NOTHING_STEP);
	CAppEffectData(int nType, D3DXVECTOR3 vPos, int LoadingPriority = _NOTHING_STEP);
	CAppEffectData(GUIUnitRenderInfo* pParent, int nType);
	// 	//ysw 9_22
	CAppEffectData(CAtumNode* pParent2, CCamera* pParent, int nType, D3DXVECTOR3 vPos, float fDist = 0, float fSide = 0, float fUp = 0, int LoadingPriority = _NOTHING_STEP);
	//end 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����

	virtual ~CAppEffectData();
	virtual void Tick();
	void SetHeight();
	void SetEffectTick(float fTick);
	BOOL CheckItemPoint();
	void ChangeBodyCondition(BodyCond_t hyBody);
	void ResetBodyCondition(BodyCond_t hyBody);
	void LoadCharacterEffect(char* strFileName);

	// 2010-06-15 by shcho&hslee ��ý��� - �� ���� ����
	// 2010-06-15 by shcho&hslee ��ý��� - ���� �̵� ó��
	void SetPetPos(D3DXVECTOR3 CharPos, D3DXVECTOR3 PetPos, float fElapsedTime);
	// end 2010-06-15 by shcho&hslee ��ý��� - ���� �̵� ó��
	// end 2010-06-15 by shcho&hslee ��ý��� - �� ���� ����

	// 2008-12-29 by bhsohn ��Ű �ӽ� ���� ����Ʈ �߰�
	void SetAffDataMaxtrix(D3DXVECTOR3	i_vPos, D3DXVECTOR3	i_vVel, D3DXVECTOR3	i_vUp);

	DWORD				m_dwState;
	CCamera* m_pCamera;
	BodyCond_t			m_bodyCondition;
	CCharacterInfo* m_pCharacterInfo;
	D3DXVECTOR3			m_vPos;						// Position
	D3DXVECTOR3			m_vVel;						// ����
	D3DXVECTOR3			m_vUp;						// Position
	D3DXVECTOR3			m_vTargetPos;						// Position
	D3DXMATRIX			m_mMatrix;
	INT					m_nType;
	FLOAT				m_fDistance;
	FLOAT				m_fSideDistance;
	FLOAT				m_fUpDistance;
	FLOAT				m_fVelRate;

	GUIUnitRenderInfo* m_pGUIInfo;

	// 2009. 07. 07 by ckPark �κ���� ��û����(�Ѹ�, ����ȭ��, ����, A�������)
	BOOL				m_bRender;

	enum	RobotWeapon1_1_FirePos { NONE, LEFT, RIGHT };

	RobotWeapon1_1_FirePos	m_nFirePos;
	// end 2009. 07. 07 by ckPark �κ���� ��û����(�Ѹ�, ����ȭ��, ����, A�������)


	// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

	BOOL				m_bRepeat;			// �ݺ� ��Ű�� ����Ʈ�ΰ�?
	float				m_fPlayTime;		// �� ��� �ð�
	EffectPlayCount_t	m_nPlayCount;		// �� �ݺ���� Ƚ��

	// �ݺ� ��� ���� ����
	void	SetRepeat(BOOL bRepeat, float	fPlayTime = 0, EffectPlayCount_t nPlayCount = 0)
	{
		m_bRepeat = bRepeat;

		// �ݺ� ����� �ƴ϶�� ���� �ʱ�ȭ
		if (!bRepeat)
		{
			m_fPlayTime = 0.0f;
			m_nPlayCount = 0;
		}
		else
		{
			m_fPlayTime = fPlayTime;
			m_nPlayCount = nPlayCount;
		}
	}

	// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

	// 2010-06-15 by shcho&hslee ��ý��� - ���� �̵� ó��
	D3DXMATRIX m_mPetMatrix;
	float		m_fPetSpeed;
	float		m_fOldDistance;
	float		m_fPetAddSpeed;
	// end 2010-06-15 by shcho&hslee ��ý��� - ���� �̵� ó��
};

#endif // !defined(AFX_APPEFFECTDATA_H__015F7554_AAB5_4E73_A7CF_80BFEB534741__INCLUDED_)
