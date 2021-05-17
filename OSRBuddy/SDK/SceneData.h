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
/// \brief		렌더링할 배경화면 데이타, 맵데이타, 몬스터, object, enemy,날씨,시간 등
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



// 오브젝트와 충돌을 위한 영역 구하기 위한 함수
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
	CAtumNode* m_pItemData;					// 아이템 데이타(필드내의)
	vector<CItemData*>			m_vecScanData;
	CWeapon* m_pWeaponData;				// 무기 데이타, 이거 다른 구조로 바꿔야 함
	CBackground* m_pGround;					// 맵
	CObjRender* m_pObjectRender;			// 맵상의 오브젝트(지물들)
	CMonRender* m_pMonsterRender;			// 몬스터 렌더러
	CETCRender* m_pETCRender;				// 기타 각종 렌더러
	CWater* m_pWater;					// 물렌더링
	CMapMonsterList				m_mapMonsterList;				// 몬스터 리스트
	//CMapMonsterList				m_mapMonsterRenderList;			// 몬스터 렌더링 리스트
	CVecMonsterList				m_vecMonsterRenderList;			// 몬스터 렌더링 리스트			
	//CVecMonsterList				m_vecMonsterShadowRenderList;	// 몬스터 그림자 렌더링 리스트	
	CMapEnemyList				m_mapEnemyList;					// 타캐릭터 리스트(인덱스가 0인 경우 60000번대로 임시로 넣는다)
	//CMapEnemyList				m_mapEnemyRenderList;			// 타캐릭터 렌더링 리스트
	CVecEnemyList				m_vecEnemyRenderList;			// 타캐릭터 렌더링 리스트
	//CVecEnemyList				m_vecEnemyShadowRenderList;		// 타캐릭터 그림자 렌더링 리스트
	vector<CUnitData*>			m_vecUnitRenderList;
	///////// 안개 효과 변수들 /////////////
	DWORD						m_dwFogColor;					// 안개색
	FLOAT						m_fOrgFogStartValue;				// 안개 시작지점-거리(실제값)
	FLOAT						m_fOrgFogEndValue;					// 안개 끝지점-거리(질제값)
	FLOAT						m_fFogStartValue;				// 안개 시작지점-거리(현재값)
	FLOAT						m_fFogEndValue;					// 안개 끝지점-거리(현재값)
	FLOAT						m_fBeforeFogStartValue;			// 방금전의 안개 시작지점-거리
	FLOAT						m_fBeforeFogEndValue;			// 반금전의 안개 끝지점-거리
	BOOL						m_bFog;							// 렌더링을 On Off 시키는 변수, 사용안함
	BOOL						m_bFogStay;						// 안개가 완전히 걷히기 전까지 대기 시키는 변수, 사용안함
	D3DLIGHT9					m_light0;						// 전체를 비출 라이트
	D3DLIGHT9					m_light1;						// 헤드라이트
	D3DLIGHT9					m_light2;						// 이펙트 보조 라이트
	D3DLIGHT9					m_light3;						// 셔틀을 비출 라이트
	BOOL						m_bNight;

	CSunRender* m_pSunRender;					// 태양 렌더러
	CSunData* m_pSunData;						// 태양 데이타

	///////////// Tile Texture Buffer /////////////
	CGameData* m_pData;						// 데이타파일 (맵타일파일)
	LPDIRECT3DTEXTURE9			m_pCreateTexture[TEXTILE_NUM];

	BOOL						m_bIsRestore;					// Restore-Res 참조

	FLOAT						m_fSkyRedColor;
	FLOAT						m_fSkyGreenColor;
	FLOAT						m_fSkyBlueColor;
	CRainRender* m_pRainRender;				// 날씨 비 렌더러
	CAtumNode* m_pRainList;				// 날씨 비 리스트
	BYTE						m_byWeatherType;				// 날씨 타입(0:없음, 1:눈, 2:비)
	DWORD						m_dwStartTime;				// 시간을 계산하기 위한 클라이언트의 시작시간
	INT							m_nBaseTime;				// 서버로 전송받은 기준 시간
	BYTE						m_byMapType;					// 맵 타입(도시, 필드 등..)

	CVecEnemyList* m_vecEnemyBlockList;
	CVecMonsterList* m_vecMonsterList;
	vectorCObjectChildPtr		m_vectorRangeObjectPtrList;		//맵상의 시야주위의 영역 오브젝트 리스트
	vectorCObjectChildPtr		m_vectorCulledObjectPtrList;	//맵상의 렌더링할 오브젝트 리스트
	vectorCObjectChildPtr		m_vectorCollisionObjectPtrList; //맵상의 충돌검사를 할 오브젝트 리스트

	int							m_nMaxAtitudeHeight;			// 맵상 이동 가능한 최대 높이 // 2005-07-11 by ispark

	int							m_nBlockSizeX;
	int							m_nBlockSizeY;
	BOOL						m_bChangeWeather;			// 날씨 교체시에 실행

	// 2004-10-20 by jschoi
	float						m_fChangeWeatherCheckTime;		// 날씨 변화 진행 시간

	// 2005-01-20 by jschoi
	float						m_fAlphaSky;		// 스카이 박스 낮,밤 혼합비율

//	float						m_fFogDestStartValue;			// 디버깅 용
//	float						m_fFogDestEndValue;			// 디버깅 용

	// 2006-11-16 by ispark, 알파 렌더링
	vector<ALPHA_CHARACTERINFO>	m_vecAlphaEffectRender;
	vector<CUnitData*>			m_vecAlphaUnitRender;

	// 2010. 10. 05 by jskim 맵로딩 구조 변경
	PROJECTINFO					m_prProject;
	// end 2010. 10. 05 by jskim 맵로딩 구조 변경

protected:
	CGameData* m_pCinemaData;
	BOOL						m_bWaterShaderRenderFlag;

	float						m_fGetItemAllDelay;
	float						m_fGetItemMessage;				// 채팅창에 인벤이 다 찼다는 경고 시간체크.

// 2008. 12. 11 by ckPark 물렌더링

	LPDIRECT3DTEXTURE9			m_pWaterBumpTexture;			// 물 범프 텍스쳐(게임 시작시 한번만 생성한다)
// end 2008. 12. 11 by ckPark 물렌더링
};

#endif // !defined(AFX_SCENEDATA_H__5325A197_B598_4A01_9E34_946C65760A16__INCLUDED_)
