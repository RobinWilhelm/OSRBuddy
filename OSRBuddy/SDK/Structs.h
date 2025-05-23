#pragma once
#include <windows.h>
#include "AtumParam.h"
#include "AtumProtocol.h"

typedef UINT32	UID32_t;

struct BitS_CParamFactor
{
	UINT	pfb_SKILL_ROLLING_TIME : 1;		// 2009-08-03 by cmkwon, EP3-4 편대 대형 스킬 구현 - 기존 BOOL 변수를 비트구조체로 변경, 
	UINT	pfb_SKILL_Barrier : 1;		// 2009-08-03 by cmkwon, EP3-4 편대 대형 스킬 구현 - 기존 BOOL 변수를 비트구조체로 변경, 
	UINT	pfb_SKILL_SHIELD_PARALYZE : 1;		// 2009-09-09 ~ 2010-02-18 by dhjin, 인피니티 - Debuff 체크도 추가 // 2009-09-09 ~ 2010 by dhjin, 인피니티 - Debuff 체크로 변경	// 2009-08-03 by cmkwon, EP3-4 편대 대형 스킬 구현 - 기존 BOOL 변수를 비트구조체로 변경, 
	UINT	pfb_SKILL_Invincible : 1;		// 2009-08-03 by cmkwon, EP3-4 편대 대형 스킬 구현 - 기존 BOOL 변수를 비트구조체로 변경, 
	UINT	pfb_SKILL_DamageDistribution : 1;		// 2009-08-03 by cmkwon, EP3-4 편대 대형 스킬 구현 - 기존 BOOL 변수를 비트구조체로 변경, 추가함
	UINT	pfb_ITEM_IgnoreDefence : 1;		// 203, // 2009-09-09 ~ 2010 by dhjin, 인피니티 - 방어력 무시 아이템 사용 체크
	UINT	pfb_ITEM_IgnoreAvoid : 1;		// 204, // 2009-09-09 ~ 2010 by dhjin, 인피니티 - 회피력 무시 아이템 사용 체크
};

///////////////////////////////////////////////////////////////////////////////
/// \class		CParamFactor
///
/// \brief		캐릭터의 각종 파라미터에 적용될 factors, DES_XXX에 대응됨
///				pfp:Plus 해주는 Param, Param을 더해준는 처리
///				pfp:Multiple 해주는 Param, Param을 곱해주는 처리
/// \author		kelovon
/// \version
/// \date		2004-04-10 ~ 2004-04-10
/// \warning	캐릭터의 ParamFactor는 ITEM에 적용시에 장전된 무기에만 해당된다.
///////////////////////////////////////////////////////////////////////////////
class CParamFactor
{
public:
	CParamFactor() { Reset(); }
	~CParamFactor() {}

	void Reset();

	CParamFactor operator+(const CParamFactor& rhs) const;
	CParamFactor& operator+=(const CParamFactor& rhs);
	CParamFactor operator-(const CParamFactor& rhs) const;
	CParamFactor& operator-=(const CParamFactor& rhs);

	void Print(BOOL i_bDbgOutOrMsg, void* i_pSocket = NULL, BOOL i_bOnlyValidParam = TRUE);

public:
	float		pfp_ATTACK_PART;			// 1, 공격 파트
	float		pfp_DEFENSE_PART;			// 2, 방어 파트
	float		pfp_FUEL_PART;				// 3, 연료 파트
	float		pfp_SOUL_PART;				// 4, 감응 파트
	float		pfp_SHIELD_PART;			// 5, 쉴드 파트
	float		pfp_DODGE_PART;				// 6, 회피 파트
	float		pfp_BODYCONDITION;			// 7, 몸상태
	float		pfp_ENDURANCE_01;			// 8, 내구도 01
	float		pfp_ENDURANCE_02;			// 9, 내구도 02
	float		pfp_CHARGING_01;			// 10, 장탄수 01
	float		pfp_CHARGING_02;			// 11, 장탄수 02
	INT			pfp_PROPENSITY;				// 12, 성향
	float		pfp_HP;						// 13, 히트포인트
	float		pfp_SP;						// 14, 소울포인트, 일정 시간 후에 SP를 증가시키기만 하면 됨
	float		pfp_DP;						// 89, 쉴드(DEFENSE)포인트
	float		pfp_EP;						// 15, 엔진포인트
	float		pfp_SPRECOVERY;				// 16, 소울포인트회복력
	float		pfp_HPRECOVERY;				// 17, 에너지포인트회복력
	float		pfm_MINATTACK_01;			// 18, (*) 최소 공격력 01
	float		pfm_MAXATTACK_01;			// 71, (*) 최대 공격력 02
	float		pfm_MINATTACK_02;			// 19, (*) 최소 공격력 01
	float		pfm_MAXATTACK_02;			// 72, (*) 최대 공격력 02
	float		pfp_ATTACKPROBABILITY_01;	// 20, // 2010-07-19 by dhjin, 확률 수식 변경 공격확률 01, 0 ~ 255	
	float		pfp_ATTACKPROBABILITY_02;	// 21, // 2010-07-19 by dhjin, 확률 수식 변경공격확률 02, 0 ~ 255
	float		pfp_DEFENSE_01;				// 22, // 2010-07-19 by dhjin, 확률 수식 변경방어력 01, 0 ~ 255
	float		pfp_DEFENSE_02;				// 23, // 2010-07-19 by dhjin, 확률 수식 변경방어력 02, 0 ~ 255
	float		pfp_DEFENSEPROBABILITY_01;	// 24, // 2010-07-19 by dhjin, 확률 수식 변경방어확률 01, 0 ~ 255
	float		pfp_DEFENSEPROBABILITY_02;	// 25, // 2010-07-19 by dhjin, 확률 수식 변경방어확률 02, 0 ~ 255
	Prob256_t	pfp_SKILLPROBABILITY;		// 26, 스킬공격확률, 0 ~ 255
	Prob256_t	pfp_FACTIONRESISTANCE;		// 27, 속성저항력, 0 ~ 255
	float		pfm_SPEED;					// 28, (*) 이동속도
	float		pfp_TRANSPORT;				// 29, 운반력
	float		pfp_MATERIAL;				// 30, 재질
	float		pfm_REATTACKTIME_01;		// 31, (*) 리어택타임 01
	float		pfm_REATTACKTIME_02;		// 32, (*) 리어택타임 02
	Prob256_t	pfp_ABRASIONRATE_01;		// 33, 마모율 01, 0 ~ 255
	Prob256_t	pfp_ABRASIONRATE_02;		// 34, 마모율 02, 0 ~ 255
	float		pfm_RANGE_01;				// 35, (*) 유효거리 01
	float		pfm_RANGE_02;				// 36, (*) 유효거리 02
	float		pfp_RANGEANGLE_01;			// 37, 유효각도 01, 서버에선 불필요
	float		pfp_RANGEANGLE_02;			// 38, 유효각도 02, 서버에선 불필요
	int			pfp_MULTITAGET;				// 39, 멀티타겟, 서버에선 불필요
	float		pfp_EXPLOSIONRANGE_01;		// 40, 폭발반경 01
	float		pfp_EXPLOSIONRANGE_02;		// 67, 폭발반경 02
	float		pfp_UNIT;					// 41, 유닛의 종류 (28 ~ 29이 같이 쓰여 유닛마다의 보정값으로 사용됨)
	float		pfp_REVISION;				// 42, 유닛의 보정값 (28 ~ 29이 같이 쓰여 유닛마다의 보정값으로 사용됨)
	Prob256_t	pfp_FACTIONPROBABILITY;		// 43, 속성에 대한 방어확률, 0 ~ 255
	int			pfp_SHOTNUM_01;				// 44, 일점사 당 발사 수 01
	int			pfp_SHOTNUM_02;				// 69, 일점사 당 발사 수 02
	int			pfp_MULTINUM_01;			// 45, 동시 발사 수 01
	int			pfp_MULTINUM_02;			// 70, 동시 발사 수 02
	float		pfp_ATTACKTIME_01;			// 46, 처음 공격 시의 타임 01
	float		pfp_ATTACKTIME_02;			// 47, 처음 공격 시의 타임 02
	float		pfm_TIME_01;				// 48, (*) 지속 시간 01
	float		pfm_TIME_02;				// 49, (*) 지속 시간 02
	float		pfm_WEIGHT_01;				// 75, (*) 무게 01
	float		pfm_WEIGHT_02;				// 76, (*) 무게 02
	USHORT		pfp_REACTION_RANGE;			// 91, ITEM의 ReactionRange 변경
	int			pfp_REQ_MIN_LEVEL;			// 96, (서버미사용)아이템장착 요구 MinLevel을 낮춘다
	int			pfp_REQ_MAX_LEVEL;			// 97, (서버미사용)아이템장착 요구 MaxLevel을 낮춘다
	float		pfm_SKILL_REDUCE_SHIELD_DAMAGE;		// 121, 2005-11-21 by cmkwon - 쉴드에 가는 데미지를 줄여준다.(*)
	float		pfm_ATTACK_RANGE_01;				// 129, 2005-11-21 by cmkwon - 레이다의 기본 무기 조준 거리를 증가시킨다.(*)
	float		pfm_ATTACK_RANGE_02;				// 130, 2005-11-21 by cmkwon - 레이다의 고급 무기 조준 거리를 증가시킨다.(*)
// 2005-12-02 by cmkwon	float		pfm_SKILL_HYPERMOVING;				// 132, 2005-11-28 by cmkwon - 유닛의 전체 이동속도가 좋아지고, 부스터 사용이 되지 않는다.(*)
	float		pfm_SKILL_COLLISIONDAMAGE_DOWN;		// 140, 2005-11-21 by cmkwon - 배경 오브젝트,바닥 충돌시 데미지를 감소시킨다.(*)
	float		pfm_SKILL_SMARTSP;					// 148, 2005-11-21 by cmkwon - 자신이 사용하는 모든 스킬의 사용량을 줄여준다.(*)	
	float		pfm_SKILL_REACTIONSPEED;			// 154, 2005-12-02 by cmkwon - 하이퍼 무빙(반응속도)
	float		pfm_SKILL_ENGINEANGLE;				// 155, 2005-12-02 by cmkwon - 하이퍼 무빙(선회각)
	float		pfm_SKILL_ENGINEBOOSTERANGLE;		// 156, 2005-12-02 by cmkwon - 하이퍼 무빙(부스터 선회각)

	float		pfm_DROP_EXP;						// 157, 2006-03-30 by cmkwon - 경험치, 프리미엄과 중첩 불가
	float		pfm_DROP_SPI;						// 158, 2006-03-30 by cmkwon - SPI, 프리미엄과 중첩 불가
	float		pfm_DROP_ITEM;						// 159, 2006-03-30 by cmkwon - 아이템 드랍율, 프리미엄과 중첩 불가
	float		pfm_DROP_RAREITEM;					// 238, 2010-11-30 by shcho, 레어아이템 드랍 확률 증가 아이템 구현
	float		pfm_HP_REPAIR_RATE_FLIGHTING;		// 160, 2006-03-30 by cmkwon - 비행시 HP 회복율
	float		pfm_DP_REPAIR_RATE;					// 161, 2006-03-30 by cmkwon - DP 회복율
	float		pfm_SP_REPAIR_RATE;					// 162, 2006-03-30 by cmkwon - SP 회복율
// 2009-08-03 by cmkwon, EP3-4 편대 대형 스킬 구현 - 기존 BOOL 변수를 비트구조체로 변경, 아래와 같이 비트구조체로 변경
// 	BOOL		pfb_SKILL_ROLLING_TIME;				// 170, 2006-11-17 by dhjin - 30초간 롤링 재사용 시간을 없애준다 
// 	BOOL		pfb_SKILL_Barrier;					// 173, 2006-11-24 by dhjin - A기어의 고급무기에 대한 무적스킬
// 	BOOL		pfb_SKILL_SHIELD_PARALYZE;			// 175,	2006-11-24 by dhjin - A기어의 쉴드마비 스킬, 상대기어의 쉴드 회복율을 0으로 만든다
// 	BOOL		pfb_SKILL_Invincible;				// 122, 2006-11-27 by dhjin - M기어의 무적 스킬
	///////////////////////////////////////////////////////////////////////////////
	// 2009-08-03 by cmkwon, EP3-4 편대 대형 스킬 구현 - 기존 BOOL 변수를 비트구조체로 변경, 
	BitS_CParamFactor	pfb_BitFlag;

	float		pf_SKILL_Big_Boom_damage;			// 174, 2006-11-29 by dhjin - A기어의 기본무기 차징샷, 스플래쉬 데미지는 Range

	float		pfm_WARHEAD_SPEED;					// 176, 2007-06-11 by cmkwon, 탄두의 속도

	// 2008-09-22 by dhjin, 신규 인첸트
	float		pfn_ENGINE_BOOSTER_TIME_UP;			// 178		// 2008-09-22 by dhjin, 부스터 시간 증가
	float		pfn_ENGINE_MAX_SPEED_UP;			// 179,	// 2008-09-22 by dhjin, 엔진 일반속도(최대) 증가
	float		pfn_ENGINE_MIN_SPEED_UP;			// 180,	// 2008-09-22 by dhjin, 엔진 일반속도(최소) 증가
	float		pfn_ENGINE_BOOSTER_SPEED_UP;		// 181,	// 2008-09-22 by dhjin, 엔진 부스터속도 증가
	float		pfn_ENGINE_GROUND_SPEED_UP;			// 182,	// 2008-09-22 by dhjin, 엔진 지상속도 증가
	int			pfn_RADAR_OBJECT_DETECT_RANGE;		// 183, // 2008-09-22 by dhjin, 레이더 물체 감지 반경
	float		pfm_PIERCE_UP_01;					// 184, // 2008-09-22 by dhjin, 기본무기 피어스율 증가 카드
	float		pfm_PIERCE_UP_02;					// 185, // 2008-09-22 by dhjin, 고급무기 피어스율 증가 카드
	float		pfm_ENGINE_ANGLE_UP;				// 186,	// 2008-09-30 by dhjin, 엔진 회전각 증가 카드
	float		pfm_ENGINE_BOOSTERANGLE_UP;			// 187,	// 2008-09-30 by dhjin, 엔진 부스터 회전각 증가 카드	
	ParamValue_t	pf_ITEM_Resistance;				// 201, // 2009-09-09 ~ 2010 by dhjin, 인피니티 - 저항 아이템 사용 체크 
	ParamValue_t	pf_ITEM_AddAttack;				// 202, // 2009-09-09 ~ 2010 by dhjin, 인피니티 - 절대값 타격치 아이템 사용 체크 
	ParamValue_t	pf_ITEM_ReduceDamage;			// 205, // 2009-09-09 ~ 2010 by dhjin, 인피니티 - 데미지 절대값 감소 아이템 사용 체크
	ParamValue_t	pf_ITEM_AddAttack_Sec;			// 206, // 2009-09-09 ~ 2010 by dhjin, 인피니티 - 절대값 타격치 아이템 고급무기용(기무와 분류)
	ParamValue_t	pf_ITEM_OnceResistance;			// 207, // 2009-09-09 ~ 2010-01-19 by dhjin, 인피니티 - 한 번만 저항하고 없어지는 저항 아이템 추가
	float			pfm_PLUS_WARPOINT_RATE;			// 234, // 2010-05-18 by cmkwon, WarPoint 증가 아이템 구현(일본요청) - 
	ParamValue_t	pf_ITEMS_MOVE_SPEED_RATE;		// 239, // 2010-12-21 by jskim, 마을 이동 속도 증가 아이템 구현
};

