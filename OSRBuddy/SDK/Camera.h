// Camera.h: interface for the CCamera class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAMERA_H__A85A685E_A796_4B9D_B700_FA1F1B8282ED__INCLUDED_)
#define AFX_CAMERA_H__A85A685E_A796_4B9D_B700_FA1F1B8282ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "D3DUtil.h"
/*
#define CAM_NORMAL_SPEED				10
#define OBJECT_SCCREENX_MIN_RATE		0.15
#define OBJECT_SCCREENX_MAX_RATE		0.85
#define OBJECT_SCCREENY_MIN_RATE		0.55
#define OBJECT_SCCREENY_MAX_RATE		0.9
*/
class CEnemyData;
class CCamera : public CD3DCamera
{
public:
	CCamera();
	virtual ~CCamera();	  	

public:
	D3DXVECTOR3	m_vCamNextPos;		// 카메라 다음 위치
	D3DXVECTOR3	m_vNextCamVel;		// 카메라 속도
	D3DXVECTOR3	m_vObjectPos;		// 화면에 무조건 나타나야 하는 object position
	D3DXVECTOR3	m_vNextTargetPos;	// 카메라가 바라보는 맵에서의 위치
	D3DXVECTOR3 m_vDistance;
	D3DXVECTOR3 m_vHeight;
	D3DXVECTOR3 m_vObjOldPos;
	D3DXVECTOR3 m_vCollCamPos;		// 충돌시 타격시 카메라를 흔들기 위한 벡터

	FLOAT		m_fOriDistance;		// 디폴트 카메라의 셔틀로부터 거리
	FLOAT		m_fOriHeight;		// 디폴트 카메라의 셔틀로부터 높이
	FLOAT		m_fAngle;
	FLOAT		m_fSideAngle;
	BOOL		m_bTurning;
	FLOAT		m_fCheckCollTime;	// 카메라 떨림 시간 변수
	BYTE		m_bCamCollType;		// 카메라 떨림 타입

	BYTE		m_bCamType;
public:
	D3DXVECTOR3	m_vCamCurrentPos;	// 카메라 현재 위치
	D3DXVECTOR3	m_vTargetStart;		// 맵의 시작
	D3DXVECTOR3	m_vTargetEnd;		// 맵의 끝
	D3DXVECTOR3 m_vCurrentTargetPos;

	FLOAT		m_fDistance;		// 현재 카메라의 셔틀로부터 거리
	FLOAT		m_fHeight;			// 현재 카메라의 셔틀로부터 높이

	FLOAT		m_fAngleX;			// 2005-08-16 by ispark
	FLOAT		m_fAngleY;

	// 2004.06.23 jschoi
	D3DXVECTOR3 m_vOldCamEyePos;	// 이전 카메라 눈 위치
	FLOAT		m_fOldHeight;		// 이전 Height
	FLOAT		m_fOldDistance;		// 이전 Distance
	FLOAT		m_fOldSideAngle;	// 이전 회전 각

	BOOL		m_bIsCamControl;	// 카메라를 컨트롤 중인가
	FLOAT		m_fCamControlCheckTime;	// 카메라 컨트롤시 타임 체크하여 타겟 방향을 부드럽게한다.
	FLOAT		m_fCheckSpeedRate;		// 카메라의 따라가는 속도

	// 지형 컬링을 위한 변수들
	D3DXPLANE	m_pl[4];				// 지형 컬링을 위한 4개의 평면
	FLOAT		m_fMinX;				// 컬링을 위한 최소 X
	FLOAT		m_fMaxX;				// 컬링을 위한 최대 X
	FLOAT		m_fMinY;				// 컬링을 위한 최소 Y
	FLOAT		m_fMaxY;				// 컬링을 위한 최대 Y
	FLOAT		m_fDetailRateGround;	// 디테일한 정도 (비율에 따라 타일 맵이 적용된다)
	FLOAT		m_fRenderDistance;		// 렌더링 영역 (거리)

	// 시즈모드 락시 시점전환 
	D3DXVECTOR3 m_vCamSlowNextPos;
	FLOAT		m_fFrameLerp;

	// 2004-08-17 jschoi
	D3DXPLANE	m_planeView;			// 카메라 평면
	BOOL		m_bSmoothMove;			// 카메라 방향 천천히 돌아가도록
	float		m_fSmoothTime;			// 부드러운 카메라 최대 지속시간

//	// 2005-07-20 by ispark
//	// 캐릭터 일때 쓰는 변수들
//	D3DXVECTOR3		m_vChaVel;			// 캐릭터를 쳐다 보는 방향. 처음에 한번 저장 후 회전각을 여기에 곱함ㅁ

	// 2005-08-18 by ispark
	float		m_fTotalAngleX;			// 움직인 각도
	float		m_fAngleError;			// 각도 오차 : 처음 카메라 위치 셋팅에 따라 카메라 상,하 제한을 두기 위해서
										//			   각도오차를 변수에 저장한다. 이 변수로 각도 제한 Define에 쓰인다.
	// 2005-08-19 by ispark
	float		m_fCollDistance;		// 충돌시 카메라의 캐릭터로부터 거리


};

#endif // !defined(AFX_CAMERA_H__A85A685E_A796_4B9D_B700_FA1F1B8282ED__INCLUDED_)
