// SceneData.h: interface for the CSceneData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCENEDATA_H__5325A197_B598_4A01_9E34_946C65760A16__INCLUDED_)
#define AFX_SCENEDATA_H__5325A197_B598_4A01_9E34_946C65760A16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AtumNode.h"
#include "ObjRender.h"
#include "ObjectChild.h"
#include "Background.h"

///////////////////////////////////////////////////////////////////////////////
/// \class		CSceneData
///
/// \brief		�������� ���ȭ�� ����Ÿ, �ʵ���Ÿ, ����, object, enemy,����,�ð� ��
/// \author		dhkwon
/// \version	
/// \date		2004-03-19 ~ 2004-03-19
/// \warning	
///////////////////////////////////////////////////////////////////////////////

class CCinema;
class CFrustum;
class CMonRender;
class CSunRender;
class CSunData;
class CRainRender;
class CRainData;
class CETCRender;
class CWeapon;
class CItemData;
class CGameData;
class CUnitData;
class CAtumData;
class CItemData;
class CAppEffectData;
class CWater;
struct ALPHA_CHARACTERINFO;

class CSceneData : CAtumNode
{
public:
	CSceneData();
	virtual ~CSceneData();

	void SetFogLevel(DWORD dwFogColor, float fFogStart, float fFogEnd);

	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual void Render();
	virtual void Tick();



// ������Ʈ�� �浹�� ���� ���� ���ϱ� ���� �Լ�
	enum MoveType
	{
		NOMOVE,
		TOPLEFT,
		TOPRIGHT,
		BOTTOMLEFT,
		BOTTOMRIGHT
	};


public:
	CFrustum* m_pFrustum;
	CAtumNode* m_pItemData;					// ������ ����Ÿ(�ʵ峻��)
	vector<CItemData*>			m_vecScanData;
	CWeapon* m_pWeaponData;				// ���� ����Ÿ, �̰� �ٸ� ������ �ٲ�� ��
	CBackground* m_pGround;					// ��
	CObjRender* m_pObjectRender;			// �ʻ��� ������Ʈ(������)
	CMonRender* m_pMonsterRender;			// ���� ������
	CETCRender* m_pETCRender;				// ��Ÿ ���� ������
	CWater* m_pWater;					// ��������
	CMapMonsterList				m_mapMonsterList;				// ���� ����Ʈ
	//CMapMonsterList				m_mapMonsterRenderList;			// ���� ������ ����Ʈ
	CVecMonsterList				m_vecMonsterRenderList;			// ���� ������ ����Ʈ			
	//CVecMonsterList				m_vecMonsterShadowRenderList;	// ���� �׸��� ������ ����Ʈ	
	CMapEnemyList				m_mapEnemyList;					// Ÿĳ���� ����Ʈ(�ε����� 0�� ��� 60000����� �ӽ÷� �ִ´�)
	//CMapEnemyList				m_mapEnemyRenderList;			// Ÿĳ���� ������ ����Ʈ
	CVecEnemyList				m_vecEnemyRenderList;			// Ÿĳ���� ������ ����Ʈ
	//CVecEnemyList				m_vecEnemyShadowRenderList;		// Ÿĳ���� �׸��� ������ ����Ʈ
	vector<CUnitData*>			m_vecUnitRenderList;
	///////// �Ȱ� ȿ�� ������ /////////////
	DWORD						m_dwFogColor;					// �Ȱ���
	FLOAT						m_fOrgFogStartValue;				// �Ȱ� ��������-�Ÿ�(������)
	FLOAT						m_fOrgFogEndValue;					// �Ȱ� ������-�Ÿ�(������)
	FLOAT						m_fFogStartValue;				// �Ȱ� ��������-�Ÿ�(���簪)
	FLOAT						m_fFogEndValue;					// �Ȱ� ������-�Ÿ�(���簪)
	FLOAT						m_fBeforeFogStartValue;			// ������� �Ȱ� ��������-�Ÿ�
	FLOAT						m_fBeforeFogEndValue;			// �ݱ����� �Ȱ� ������-�Ÿ�
	BOOL						m_bFog;							// �������� On Off ��Ű�� ����, ������
	BOOL						m_bFogStay;						// �Ȱ��� ������ ������ ������ ��� ��Ű�� ����, ������
	D3DLIGHT9					m_light0;						// ��ü�� ���� ����Ʈ
	D3DLIGHT9					m_light1;						// ������Ʈ
	D3DLIGHT9					m_light2;						// ����Ʈ ���� ����Ʈ
	D3DLIGHT9					m_light3;						// ��Ʋ�� ���� ����Ʈ
	BOOL						m_bNight;

	CSunRender* m_pSunRender;					// �¾� ������
	CSunData* m_pSunData;						// �¾� ����Ÿ

	///////////// Tile Texture Buffer /////////////
	CGameData* m_pData;						// ����Ÿ���� (��Ÿ������)
	LPDIRECT3DTEXTURE9			m_pCreateTexture[TEXTILE_NUM];

	BOOL						m_bIsRestore;					// Restore-Res ����

	FLOAT						m_fSkyRedColor;
	FLOAT						m_fSkyGreenColor;
	FLOAT						m_fSkyBlueColor;
	CRainRender* m_pRainRender;				// ���� �� ������
	CAtumNode* m_pRainList;				// ���� �� ����Ʈ
	BYTE						m_byWeatherType;				// ���� Ÿ��(0:����, 1:��, 2:��)
	DWORD						m_dwStartTime;				// �ð��� ����ϱ� ���� Ŭ���̾�Ʈ�� ���۽ð�
	INT							m_nBaseTime;				// ������ ���۹��� ���� �ð�
	BYTE						m_byMapType;					// �� Ÿ��(����, �ʵ� ��..)

	CVecEnemyList* m_vecEnemyBlockList;
	CVecMonsterList* m_vecMonsterList;
	vectorCObjectChildPtr		m_vectorRangeObjectPtrList;		//�ʻ��� �þ������� ���� ������Ʈ ����Ʈ
	vectorCObjectChildPtr		m_vectorCulledObjectPtrList;	//�ʻ��� �������� ������Ʈ ����Ʈ
	vectorCObjectChildPtr		m_vectorCollisionObjectPtrList; //�ʻ��� �浹�˻縦 �� ������Ʈ ����Ʈ

	int							m_nMaxAtitudeHeight;			// �ʻ� �̵� ������ �ִ� ���� // 2005-07-11 by ispark

	int							m_nBlockSizeX;
	int							m_nBlockSizeY;
	BOOL						m_bChangeWeather;			// ���� ��ü�ÿ� ����

	// 2004-10-20 by jschoi
	float						m_fChangeWeatherCheckTime;		// ���� ��ȭ ���� �ð�

	// 2005-01-20 by jschoi
	float						m_fAlphaSky;		// ��ī�� �ڽ� ��,�� ȥ�պ���

//	float						m_fFogDestStartValue;			// ����� ��
//	float						m_fFogDestEndValue;			// ����� ��

	// 2006-11-16 by ispark, ���� ������
	vector<ALPHA_CHARACTERINFO>	m_vecAlphaEffectRender;
	vector<CUnitData*>			m_vecAlphaUnitRender;

	// 2010. 10. 05 by jskim �ʷε� ���� ����
	PROJECTINFO					m_prProject;
	// end 2010. 10. 05 by jskim �ʷε� ���� ����

protected:
	CGameData* m_pCinemaData;
	BOOL						m_bWaterShaderRenderFlag;

	float						m_fGetItemAllDelay;
	float						m_fGetItemMessage;				// ä��â�� �κ��� �� á�ٴ� ��� �ð�üũ.

// 2008. 12. 11 by ckPark ��������

	LPDIRECT3DTEXTURE9			m_pWaterBumpTexture;			// �� ���� �ؽ���(���� ���۽� �ѹ��� �����Ѵ�)
// end 2008. 12. 11 by ckPark ��������
};

#endif // !defined(AFX_SCENEDATA_H__5325A197_B598_4A01_9E34_946C65760A16__INCLUDED_)
