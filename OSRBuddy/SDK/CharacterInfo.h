// CharacterInfo.h: interface for the CCharacterInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHARACTERINFO_H__902387E2_AA6D_4345_8FCB_B8CC5C2D7A70__INCLUDED_)
#define AFX_CHARACTERINFO_H__902387E2_AA6D_4345_8FCB_B8CC5C2D7A70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "effect.h"

struct CharacterData
{
	char	m_strCharacterFileName[20];
	int		m_nBodyConditionNumber;

};

struct BodyConditionData
{
	BodyCond_t	m_nBodyCondition;
	char	m_strBodyConditionName[20];
	BOOL	m_bCharacterAlphaBlending;
	int		m_nCharacterTextureRenderState;
	int		m_nCharacterDestBlend;
	int		m_nCharacterSrcBlend;
	int		m_nEffectNumber;
	float	m_fStartAnimationTime;
	float	m_fEndAnimationTime;
	BOOL	m_bCharacterRendering;
	//add
	BOOL	m_bNotAnimationLooping;
	float	m_fAnimationVel;
	char	m_strSoundFileName[20];
};

struct EffectData
{
	int		m_nEffectType;
	char	m_strEffectName[20];
	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3	m_vTarget;
	D3DXVECTOR3	m_vUp;
	float	m_fStartTime;
	BOOL	m_bUseBillboard;
	float	m_fBillboardAngle;
	float	m_fBillboardRotateAngle;
	float	m_fBillboardRotatePerSec;
	float	m_fRandomUpLargeAngle;
	float	m_fRandomUpSmallAngle;
	BOOL	m_bUseCharacterMatrix;
	BOOL	m_bGroundBillboard;
};

class CBodyConditionInfo;
class CCharacterInfo;
class CEffectInfo : public EffectData
{
public:
	CEffectInfo();
	~CEffectInfo();

	void* operator new(size_t size);
	void operator delete(void* p);


	void InitData();
	BOOL Tick(float fElapsedTime);
	void Render();
	HRESULT InitDeviceObjects();
	HRESULT RestoreDeviceObjects();
	HRESULT InvalidateDeviceObjects();
	HRESULT DeleteDeviceObjects();
	void ParticleStop();
	void SetTexture(char* strTexture);// by dhkwon, 030917
	void SetObjectAniStartTime(float fStartObjectAniTime);
	void SetTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }
	void SetInven(int nInvenWeaponIndex) { m_nInvenWeaponIndex = nInvenWeaponIndex; }

public:
	// 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����
	int m_LoadingPriority;
	//end 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����
	char* m_pEffect;
	BOOL m_bRestored;
	float m_fCurrentTime;
	CBodyConditionInfo* m_pParent;
	LPDIRECT3DTEXTURE9	m_pTexture;	// �ܺ� ���� Texture, �� ������ �����̱� ������ ����� ������ �ʴ´�.
	int m_nInvenWeaponIndex;
	int	m_nAlphaValue;				// 2006-12-06 by ispark, ���İ�
};

class CBodyConditionInfo : public BodyConditionData
{
public:

	CBodyConditionInfo();
	~CBodyConditionInfo();

	void* operator new(size_t size);
	void operator delete(void* p);

	CEffectInfo* GetEffectInfo(char* szEffectName);
	void InitData();
	BOOL Tick(float fElapsedTime);
	void Render();
	HRESULT InitDeviceObjects();
	HRESULT RestoreDeviceObjects();
	HRESULT InvalidateDeviceObjects();
	HRESULT DeleteDeviceObjects();

	BOOL IsUsing();
	BOOL EffectStop();
	BOOL IsUsingParticle() { return m_bUsingParticle; }
	void SetObjectAniStartTime(float fStartObjectAniTime);
	void SetInven(int nInvenWeaponIndex);

	// 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����
	int				m_LoadingPriority;
	//end 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����
	vector<CEffectInfo*> m_vecEffect;
	CCharacterInfo* m_pParent;
	float			m_fCurrentAnimationTime;
	D3DXMATRIX		m_mMatrix;
	BOOL			m_bUsingParticle;
	// ��ƼŬ�� ���� ��� ������=TRUE, �ٵ������ Change�ÿ� �ٵ�����ǿ� ��ƼŬ�� �����ִ� ��츦 ���� ���
// 2010. 03. 18 by jskim ���ͺ��� ī��
	int				m_MonsterTransformer;
	float			m_MonsterTransScale;
	//end 2010. 03. 18 by jskim ���ͺ��� ī��

public:	// inline process.

	inline float	GetFrameSpeed(void) { return m_fFrameSpeed; }
	inline void		SetFrameSpeed(const float a_fFrameSpeed) { m_fFrameSpeed = a_fFrameSpeed; m_fFrameSpeed = max(m_fFrameSpeed, .0f); }

private:

	float			m_fFrameSpeed;

};

class CCharacterInfo : public CharacterData
{
public:
	CCharacterInfo();
	~CCharacterInfo();

	D3DXVECTOR3 GetEffectPos(BodyCond_t hyBody, char* szEffectName);
	D3DXMATRIX GetEffectMatrix(BodyCond_t hyBody, char* szEffectName);
	void InitData();
	void ChangeBodyCondition(BodyCond_t hyBody);
	void SetBodyCondition(BodyCond_t hyBody);
	void ResetBodyCondition(BodyCond_t hyBody);
	void TurnOnSingleBodyCondition(BodyCond_t hySingleBodyCondition);
	void TurnOffSingleBodyCondition(BodyCond_t hySingleBodyCondition);
	BOOL IsUpkeepBodyCondition(BodyCond_t hyBody);
	BOOL Tick(float fElapsedTime);
	void Render();
	HRESULT InitDeviceObjects();
	HRESULT RestoreDeviceObjects();
	HRESULT InvalidateDeviceObjects();
	HRESULT DeleteDeviceObjects();
	//	void Save(char* strName);
		// 2010. 03. 18 by jskim ���ͺ��� ī��
		//BOOL Load(char* strName);
	BOOL Load(char* strName, int nMonsterTransformer = 0, float nMonsterTransScale = 0.0f);
	//end 2010. 03. 18 by jskim ���ͺ��� ī��

	BOOL IsUsing(BodyCond_t hyBody);// single body condition
	BOOL IsUsing();
	void SetShuttleChildEffect(BOOL bSet);
	void SetSingleBodyConditionMatrix(BodyCond_t hyBody, D3DXMATRIX m);
	void SetAllBodyConditionMatrix(D3DXMATRIX m);
	void SetObjectAniStartTime(float fStartObjectAniTime);// Object animation�� ���۵Ǵ� �ð� ����(ex, DT���� 45���ΰ�� �ð��� 45/3�� �����ϸ� �ȴ�.( 3 : �ʴ� 30Frame���� ))
	void SetInven(int nInvenWeaponIndex);

	inline void SetCharacterAnimationBodyConditionMask(BodyCond_t hyBody);
	inline float GetCurrentCharacterAnimationTime();
	inline float GetCurrentBodyConditionEndAnimationTime();

	// 2010. 02. 04 by ckPark ���� �غ� ���߿� ���� ���� �ִϸ��̼� ���� ����
	void	ForceTurnOffBodyCondition(BodyCond_t nBodyCon);
	// end 2010. 02. 04 by ckPark ���� �غ� ���߿� ���� ���� �ִϸ��̼� ���� ����

protected:
	inline void SetCharacterAnimationBodyCondition(CBodyConditionInfo* pBody);
public:
	CBodyConditionInfo* FindBodyConditionInfo(BodyCond_t hyBody);
	BOOL			m_bShuttleChildEffect;	// ShuttleChild �� ��츸 ������ �ϴ� ����Ʈ�� ��� FALSE(���� �÷��� ����)
	map<BodyCond_t, CBodyConditionInfo*> m_mapBodyCondition;
	BodyCond_t		m_nCurrentBodyCondition;
	D3DXMATRIX		m_mMatrix;
	D3DXVECTOR3		m_vPos;
	set<BodyCond_t> m_vecCurrentBodyCondition;
	CBodyConditionInfo* m_pCharacterAnimationBodyCondition;
	BodyCond_t		m_hyCharacterAnimationBodyConditionFlag;// ĳ������ �ִϸ��̼��� ����ִ� �ٵ� �����(�� �ٵ�������� �ߺ��� �� ����.)

	// 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����
	int				m_LoadingPriority;
	//end 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����

	// 2010. 03. 18 by jskim ���ͺ��� ī��
	int m_MonsterTransformer;
	float m_MonsterTransScale;
	//end 2010. 03. 18 by jskim ���ͺ��� ī��
};

struct ALPHA_CHARACTERINFO
{
	CCharacterInfo* pCharInfo;
	int				nAlphaValue;

	ALPHA_CHARACTERINFO()
	{
		pCharInfo = NULL;
		nAlphaValue = 255;
	}

	~ALPHA_CHARACTERINFO()
	{
		pCharInfo = NULL;
		nAlphaValue = 255;
	}
};
///////////////////////////////////////////////////////////////////////////////
/// \fn			void CCharacterInfo::SetCharacterAnimationBodyConditionMask(BodyCond_t hyBody)
/// \brief		ĳ������ �ִϸ��̼ǵ���Ÿ�� ������ �ٵ������ ����Ʈ�� �����Ѵ�.
/// \author		dhkwon
/// \date		2004-03-26 ~ 2004-03-26
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// \fn			float CCharacterInfo::GetCurrentCharacterAnimationTime()
/// \brief		ĳ���� �ִϸ��̼� Ÿ���� �����´�.
/// \author		dhkwon
/// \date		2004-03-26 ~ 2004-03-26
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
float CCharacterInfo::GetCurrentCharacterAnimationTime()
{
	return m_pCharacterAnimationBodyCondition ? m_pCharacterAnimationBodyCondition->m_fCurrentAnimationTime : 0;
}
float CCharacterInfo::GetCurrentBodyConditionEndAnimationTime()
{
	return m_pCharacterAnimationBodyCondition ? m_pCharacterAnimationBodyCondition->m_fEndAnimationTime : 0;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void SetCharacterAnimationBodyCondition(CBodyConditionInfo* pBody) 
/// \brief		ĳ������ �ִϸ��̼��� ����� �ٵ�������� �����Ѵ�.
/// \author		dhkwon
/// \date		2004-03-26 ~ 2004-03-26
/// \warning	SetCharacterAnimationBodyConditionMask�Լ��� ���� ����ũ�� �����θ�
///				ChangeBodycondition�� �ϸ鼭 �ڵ����� ���õǴ� �Լ��̴�.(protected func)
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CCharacterInfo::SetCharacterAnimationBodyCondition(CBodyConditionInfo* pBody)
{
	m_pCharacterAnimationBodyCondition = pBody;
}
#endif // !defined(AFX_CHARACTERINFO_H__902387E2_AA6D_4345_8FCB_B8CC5C2D7A70__INCLUDED_)
