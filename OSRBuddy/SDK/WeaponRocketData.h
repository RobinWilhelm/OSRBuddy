#pragma once

#include "WSlowData.h"

class CItemData;
class CCinema;
class CAtumData;
struct ITEM;
struct ATTACK_DATA;
class CPkNormalTimer;

class CWeaponRocketData : public CWSlowData
{
public:
	virtual ~CWeaponRocketData();
	virtual void Tick();
	virtual void NormalTick();
	virtual void SkillTick();

public:
	INT					m_nTargetIndex;
	INT					m_nTargetItemFieldIndex;

	FLOAT				m_fTurnCheckTime;			// 테스트 : 일정 시간 마다의 유도성을 주기 위한 테스트 변수
	BOOL				m_bSendData;				// Change Target 에 대한 요청을 서버에 했는지
	BYTE				m_bTraceColorRed;			// 궤적 색상(R)
	BYTE				m_bTraceColorGreen;			// 궤적 색상(G)
	BYTE				m_bTraceColorBlue;			// 궤적 색상(B)
	CCinema* m_pCinema;
	INT					m_nTargetMe;

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