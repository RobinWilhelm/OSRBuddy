// Skill.h: interface for the CSkill class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKILL_H__5A26A431_9BF7_4616_8ADB_BBBEF7A4D820__INCLUDED_)
#define AFX_SKILL_H__5A26A431_9BF7_4616_8ADB_BBBEF7A4D820__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SkillInfo.h"
#define SCAN_SKILL						0
#define SCAN_ITEM						1
#define MAX_SCAN						2

/*
struct MSG_FC_SKILL_CONFIRM_USE			// 2005-12-02 by cmkwon
{
	char				szAttackCharacterName[SIZE_MAX_CHARACTER_NAME];	// 스킬 사용자의 CharacterName;
	UID32_t				AttackCharacterUID;		// 스킬 사용자 CharacterUID
	UID32_t				TargetCharacterUID;		// 스킬 타겟 CharacterUID
	int					UsingSkillItemNum;		// 사용 스킬 ItemNum
	MAP_CHANNEL_INDEX	MapChannelIndex;		// 스킬 사용자의 MapChannelIndex
	int					SkillConfirmUseUID;		// 2009-04-06 by cmkwon, 콜오브 히어로 스킬 시스템 변경 - 해당 요청의 UID
};
*/

class CAppEffectData;
class CUnitData;
class CSkill
{
	friend class CINFSkill;
public:
	CSkill();
	virtual ~CSkill();

public:

	map<int, CSkillInfo*>	m_mapEnemySkillInfo;		// 다른 사람이 사용한 스킬(key:ItemNum, value:skill info)
	map<int, CSkillInfo*>	m_mapSkill;					// 사용 가능한 모든 스킬 (key:ItemNum, value:skill info)

	char _pad01[8];
	vector<CSkillInfo*>		m_vecUsingSkill;			// 나 자신에게 사용한 스킬.
	vector<CSkillInfo*>		m_vecEnemyUsingSkillForMe;	// 다른 유저가 나한테 쓴 스킬.
	// 2007-04-19 by bhsohn 서치아이 아이템 추가
	//D3DXVECTOR3				m_vScanPosition;			// 스캔한 중심 좌표.

	BOOL					m_bSmartSpeed;				// SmartSpeed 스킬을 사용중인가?
	// 2009. 09. 21 by ckPark 인피니티 필드 몬스터 스킬 구현
	BOOL					m_bMonsterHold;
	// end 2009. 09. 21 by ckPark 인피니티 필드 몬스터 스킬 구현
	int						m_nSkillPatternType;		// 현재 사용중인 패턴 타입
	int						m_nChargingShotState;		// 차징샷의 상태
	BOOL					m_bScan;					// 현재 스캔버프스킬을 받고 있는 상태인가?
	//float					m_fScanRange;
	CSkillInfo* m_pPriSkillInfo;			// 현재 사용중인 1형무기 Skill 을 저장하기위한 임시변수
	CSkillInfo* m_pSecSkillInfo;			// 현재 사용중인 2형무기 Skill 을 저장하기위한 임시변수
	BOOL					m_bSkillTargetState;		// 현재 마우스 포인터 타켓 클릭 상태
	ClientIndex_t			m_nTargetIndex;				// 타켓이 있는 스킬인 경우 TargetIndex;
	UID32_t					m_nCharacterUID;			// 클라이언트 인덱스가 유효하지 않을 때 유니크넘버를 입력
	MSG_FC_SKILL_CONFIRM_USE m_stSkillConfirm;

	// 2007-04-05 by bhsohn 빅붐 버그 처리
	INT						m_nPreSkillItemNum;			// 사용을 시도중인 기술

	// 2007-04-19 by bhsohn 서치아이 아이템 추가
	INT						m_nScanState;
	D3DXVECTOR3				m_vScanPosition[MAX_SCAN];			// 스캔한 중심 좌표.
	float					m_fScanRange[MAX_SCAN];				// 스캔 범위 

	// 2009. 04. 06 by ckPark 콜오브히어로시 다른 타겟팅 스킬 못쓰는 문제
};

#endif // !defined(AFX_SKILL_H__5A26A431_9BF7_4616_8ADB_BBBEF7A4D820__INCLUDED_)
