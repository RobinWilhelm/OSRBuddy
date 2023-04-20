#pragma once

#include "WSlowData.h"

class CItemData;
class CAtumData;
class CCinema;
struct ITEM;
struct ATTACK_DATA;

class CWeaponMissileData : public CWSlowData
{
public:
	virtual ~CWeaponMissileData();
	virtual void Tick();
	virtual void SkillTick();

public:
	INT					m_nTargetIndex;
	INT					m_nTargetItemFieldIndex;
	// 2005-07-19 by ispark
	INT					m_nTargetMe;
	CCinema* m_pCinema;
	float				m_fFireTime;
	// 2007-06-12 by dgwoo 폭발 반경(공폭시 : 미사일이 폭반에 의해 미리 터진다.
	//								 지폭시 : 땅에 터질경우 폭반안에 있으면 데미지를 입는다.)
	float				m_fExplosionRange;

	// 2009. 08. 27 by ckPark 그래픽 리소스 변경 시스템 구현
	ITEM* m_pEffectItem;
	// end 2009. 08. 27 by ckPark 그래픽 리소스 변경 시스템 구현
	// 2009. 11. 23 by jskim 리소스 로딩 구조 변경
	int					m_LoadingPriority;
	//end 2009. 11. 23 by jskim 리소스 로딩 구조 변경
	// 2011. 03. 08 by jskim 인피3차 구현 - 넌 타겟 시스템
	int m_nMultiTargetIndex;
	// end 2011. 03. 08 by jskim 인피3차 구현 - 넌 타겟 시스템	 
};