#pragma once

#include "Weapon.h"

// 2010. 03. 18 by ckPark 인피니티 필드 2차(몬스터 스킬 추가)
#define BLIND_INTERVAL	100
// end 2010. 03. 18 by ckPark 인피니티 필드 2차(몬스터 스킬 추가)

class CWSlowData : public CWeapon
{
public:
	virtual ~CWSlowData();

public:
	INT					m_nClientIndex;
	INT					m_nItemIndex;
	USHORT				m_nRemainedBulletFuel;		// 남은 총알 수
	USHORT				m_nWeaponIndex;				// 서버에서 보내준 총알의 고유 번호

	BOOL				m_bEvasion;					// 회피
	float				m_fWarheadSpeed;			// 2007-06-15 by dgwoo 속도 추가.

	// 2010. 03. 18 by ckPark 인피니티 필드 2차(몬스터 스킬 추가)
	DWORD				m_nBlindSpeedDownTime;

	int					m_nBlindCumulate;
	// end 2010. 03. 18 by ckPark 인피니티 필드 2차(몬스터 스킬 추가)
};