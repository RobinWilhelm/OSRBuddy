#pragma once
#include <windows.h>
#include "AtumParam.h"
#include "AtumProtocol.h"

typedef UINT32	UID32_t;

struct BitS_CParamFactor
{
	UINT	pfb_SKILL_ROLLING_TIME : 1;		// 2009-08-03 by cmkwon, EP3-4 ��� ���� ��ų ���� - ���� BOOL ������ ��Ʈ����ü�� ����, 
	UINT	pfb_SKILL_Barrier : 1;		// 2009-08-03 by cmkwon, EP3-4 ��� ���� ��ų ���� - ���� BOOL ������ ��Ʈ����ü�� ����, 
	UINT	pfb_SKILL_SHIELD_PARALYZE : 1;		// 2009-09-09 ~ 2010-02-18 by dhjin, ���Ǵ�Ƽ - Debuff üũ�� �߰� // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - Debuff üũ�� ����	// 2009-08-03 by cmkwon, EP3-4 ��� ���� ��ų ���� - ���� BOOL ������ ��Ʈ����ü�� ����, 
	UINT	pfb_SKILL_Invincible : 1;		// 2009-08-03 by cmkwon, EP3-4 ��� ���� ��ų ���� - ���� BOOL ������ ��Ʈ����ü�� ����, 
	UINT	pfb_SKILL_DamageDistribution : 1;		// 2009-08-03 by cmkwon, EP3-4 ��� ���� ��ų ���� - ���� BOOL ������ ��Ʈ����ü�� ����, �߰���
	UINT	pfb_ITEM_IgnoreDefence : 1;		// 203, // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���� ������ ��� üũ
	UINT	pfb_ITEM_IgnoreAvoid : 1;		// 204, // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ȸ�Ƿ� ���� ������ ��� üũ
};

///////////////////////////////////////////////////////////////////////////////
/// \class		CParamFactor
///
/// \brief		ĳ������ ���� �Ķ���Ϳ� ����� factors, DES_XXX�� ������
///				pfp:Plus ���ִ� Param, Param�� �����ش� ó��
///				pfp:Multiple ���ִ� Param, Param�� �����ִ� ó��
/// \author		kelovon
/// \version
/// \date		2004-04-10 ~ 2004-04-10
/// \warning	ĳ������ ParamFactor�� ITEM�� ����ÿ� ������ ���⿡�� �ش�ȴ�.
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
	float		pfp_ATTACK_PART;			// 1, ���� ��Ʈ
	float		pfp_DEFENSE_PART;			// 2, ��� ��Ʈ
	float		pfp_FUEL_PART;				// 3, ���� ��Ʈ
	float		pfp_SOUL_PART;				// 4, ���� ��Ʈ
	float		pfp_SHIELD_PART;			// 5, ���� ��Ʈ
	float		pfp_DODGE_PART;				// 6, ȸ�� ��Ʈ
	float		pfp_BODYCONDITION;			// 7, ������
	float		pfp_ENDURANCE_01;			// 8, ������ 01
	float		pfp_ENDURANCE_02;			// 9, ������ 02
	float		pfp_CHARGING_01;			// 10, ��ź�� 01
	float		pfp_CHARGING_02;			// 11, ��ź�� 02
	INT			pfp_PROPENSITY;				// 12, ����
	float		pfp_HP;						// 13, ��Ʈ����Ʈ
	float		pfp_SP;						// 14, �ҿ�����Ʈ, ���� �ð� �Ŀ� SP�� ������Ű�⸸ �ϸ� ��
	float		pfp_DP;						// 89, ����(DEFENSE)����Ʈ
	float		pfp_EP;						// 15, ��������Ʈ
	float		pfp_SPRECOVERY;				// 16, �ҿ�����Ʈȸ����
	float		pfp_HPRECOVERY;				// 17, ����������Ʈȸ����
	float		pfm_MINATTACK_01;			// 18, (*) �ּ� ���ݷ� 01
	float		pfm_MAXATTACK_01;			// 71, (*) �ִ� ���ݷ� 02
	float		pfm_MINATTACK_02;			// 19, (*) �ּ� ���ݷ� 01
	float		pfm_MAXATTACK_02;			// 72, (*) �ִ� ���ݷ� 02
	float		pfp_ATTACKPROBABILITY_01;	// 20, // 2010-07-19 by dhjin, Ȯ�� ���� ���� ����Ȯ�� 01, 0 ~ 255	
	float		pfp_ATTACKPROBABILITY_02;	// 21, // 2010-07-19 by dhjin, Ȯ�� ���� �������Ȯ�� 02, 0 ~ 255
	float		pfp_DEFENSE_01;				// 22, // 2010-07-19 by dhjin, Ȯ�� ���� ������� 01, 0 ~ 255
	float		pfp_DEFENSE_02;				// 23, // 2010-07-19 by dhjin, Ȯ�� ���� ������� 02, 0 ~ 255
	float		pfp_DEFENSEPROBABILITY_01;	// 24, // 2010-07-19 by dhjin, Ȯ�� ���� ������Ȯ�� 01, 0 ~ 255
	float		pfp_DEFENSEPROBABILITY_02;	// 25, // 2010-07-19 by dhjin, Ȯ�� ���� ������Ȯ�� 02, 0 ~ 255
	Prob256_t	pfp_SKILLPROBABILITY;		// 26, ��ų����Ȯ��, 0 ~ 255
	Prob256_t	pfp_FACTIONRESISTANCE;		// 27, �Ӽ����׷�, 0 ~ 255
	float		pfm_SPEED;					// 28, (*) �̵��ӵ�
	float		pfp_TRANSPORT;				// 29, ��ݷ�
	float		pfp_MATERIAL;				// 30, ����
	float		pfm_REATTACKTIME_01;		// 31, (*) ������Ÿ�� 01
	float		pfm_REATTACKTIME_02;		// 32, (*) ������Ÿ�� 02
	Prob256_t	pfp_ABRASIONRATE_01;		// 33, ������ 01, 0 ~ 255
	Prob256_t	pfp_ABRASIONRATE_02;		// 34, ������ 02, 0 ~ 255
	float		pfm_RANGE_01;				// 35, (*) ��ȿ�Ÿ� 01
	float		pfm_RANGE_02;				// 36, (*) ��ȿ�Ÿ� 02
	float		pfp_RANGEANGLE_01;			// 37, ��ȿ���� 01, �������� ���ʿ�
	float		pfp_RANGEANGLE_02;			// 38, ��ȿ���� 02, �������� ���ʿ�
	int			pfp_MULTITAGET;				// 39, ��ƼŸ��, �������� ���ʿ�
	float		pfp_EXPLOSIONRANGE_01;		// 40, ���߹ݰ� 01
	float		pfp_EXPLOSIONRANGE_02;		// 67, ���߹ݰ� 02
	float		pfp_UNIT;					// 41, ������ ���� (28 ~ 29�� ���� ���� ���ָ����� ���������� ����)
	float		pfp_REVISION;				// 42, ������ ������ (28 ~ 29�� ���� ���� ���ָ����� ���������� ����)
	Prob256_t	pfp_FACTIONPROBABILITY;		// 43, �Ӽ��� ���� ���Ȯ��, 0 ~ 255
	int			pfp_SHOTNUM_01;				// 44, ������ �� �߻� �� 01
	int			pfp_SHOTNUM_02;				// 69, ������ �� �߻� �� 02
	int			pfp_MULTINUM_01;			// 45, ���� �߻� �� 01
	int			pfp_MULTINUM_02;			// 70, ���� �߻� �� 02
	float		pfp_ATTACKTIME_01;			// 46, ó�� ���� ���� Ÿ�� 01
	float		pfp_ATTACKTIME_02;			// 47, ó�� ���� ���� Ÿ�� 02
	float		pfm_TIME_01;				// 48, (*) ���� �ð� 01
	float		pfm_TIME_02;				// 49, (*) ���� �ð� 02
	float		pfm_WEIGHT_01;				// 75, (*) ���� 01
	float		pfm_WEIGHT_02;				// 76, (*) ���� 02
	USHORT		pfp_REACTION_RANGE;			// 91, ITEM�� ReactionRange ����
	int			pfp_REQ_MIN_LEVEL;			// 96, (�����̻��)���������� �䱸 MinLevel�� �����
	int			pfp_REQ_MAX_LEVEL;			// 97, (�����̻��)���������� �䱸 MaxLevel�� �����
	float		pfm_SKILL_REDUCE_SHIELD_DAMAGE;		// 121, 2005-11-21 by cmkwon - ���忡 ���� �������� �ٿ��ش�.(*)
	float		pfm_ATTACK_RANGE_01;				// 129, 2005-11-21 by cmkwon - ���̴��� �⺻ ���� ���� �Ÿ��� ������Ų��.(*)
	float		pfm_ATTACK_RANGE_02;				// 130, 2005-11-21 by cmkwon - ���̴��� ��� ���� ���� �Ÿ��� ������Ų��.(*)
// 2005-12-02 by cmkwon	float		pfm_SKILL_HYPERMOVING;				// 132, 2005-11-28 by cmkwon - ������ ��ü �̵��ӵ��� ��������, �ν��� ����� ���� �ʴ´�.(*)
	float		pfm_SKILL_COLLISIONDAMAGE_DOWN;		// 140, 2005-11-21 by cmkwon - ��� ������Ʈ,�ٴ� �浹�� �������� ���ҽ�Ų��.(*)
	float		pfm_SKILL_SMARTSP;					// 148, 2005-11-21 by cmkwon - �ڽ��� ����ϴ� ��� ��ų�� ��뷮�� �ٿ��ش�.(*)	
	float		pfm_SKILL_REACTIONSPEED;			// 154, 2005-12-02 by cmkwon - ������ ����(�����ӵ�)
	float		pfm_SKILL_ENGINEANGLE;				// 155, 2005-12-02 by cmkwon - ������ ����(��ȸ��)
	float		pfm_SKILL_ENGINEBOOSTERANGLE;		// 156, 2005-12-02 by cmkwon - ������ ����(�ν��� ��ȸ��)

	float		pfm_DROP_EXP;						// 157, 2006-03-30 by cmkwon - ����ġ, �����̾��� ��ø �Ұ�
	float		pfm_DROP_SPI;						// 158, 2006-03-30 by cmkwon - SPI, �����̾��� ��ø �Ұ�
	float		pfm_DROP_ITEM;						// 159, 2006-03-30 by cmkwon - ������ �����, �����̾��� ��ø �Ұ�
	float		pfm_DROP_RAREITEM;					// 238, 2010-11-30 by shcho, ��������� ��� Ȯ�� ���� ������ ����
	float		pfm_HP_REPAIR_RATE_FLIGHTING;		// 160, 2006-03-30 by cmkwon - ����� HP ȸ����
	float		pfm_DP_REPAIR_RATE;					// 161, 2006-03-30 by cmkwon - DP ȸ����
	float		pfm_SP_REPAIR_RATE;					// 162, 2006-03-30 by cmkwon - SP ȸ����
// 2009-08-03 by cmkwon, EP3-4 ��� ���� ��ų ���� - ���� BOOL ������ ��Ʈ����ü�� ����, �Ʒ��� ���� ��Ʈ����ü�� ����
// 	BOOL		pfb_SKILL_ROLLING_TIME;				// 170, 2006-11-17 by dhjin - 30�ʰ� �Ѹ� ���� �ð��� �����ش� 
// 	BOOL		pfb_SKILL_Barrier;					// 173, 2006-11-24 by dhjin - A����� ��޹��⿡ ���� ������ų
// 	BOOL		pfb_SKILL_SHIELD_PARALYZE;			// 175,	2006-11-24 by dhjin - A����� ���帶�� ��ų, ������� ���� ȸ������ 0���� �����
// 	BOOL		pfb_SKILL_Invincible;				// 122, 2006-11-27 by dhjin - M����� ���� ��ų
	///////////////////////////////////////////////////////////////////////////////
	// 2009-08-03 by cmkwon, EP3-4 ��� ���� ��ų ���� - ���� BOOL ������ ��Ʈ����ü�� ����, 
	BitS_CParamFactor	pfb_BitFlag;

	float		pf_SKILL_Big_Boom_damage;			// 174, 2006-11-29 by dhjin - A����� �⺻���� ��¡��, ���÷��� �������� Range

	float		pfm_WARHEAD_SPEED;					// 176, 2007-06-11 by cmkwon, ź���� �ӵ�

	// 2008-09-22 by dhjin, �ű� ��þƮ
	float		pfn_ENGINE_BOOSTER_TIME_UP;			// 178		// 2008-09-22 by dhjin, �ν��� �ð� ����
	float		pfn_ENGINE_MAX_SPEED_UP;			// 179,	// 2008-09-22 by dhjin, ���� �Ϲݼӵ�(�ִ�) ����
	float		pfn_ENGINE_MIN_SPEED_UP;			// 180,	// 2008-09-22 by dhjin, ���� �Ϲݼӵ�(�ּ�) ����
	float		pfn_ENGINE_BOOSTER_SPEED_UP;		// 181,	// 2008-09-22 by dhjin, ���� �ν��ͼӵ� ����
	float		pfn_ENGINE_GROUND_SPEED_UP;			// 182,	// 2008-09-22 by dhjin, ���� ����ӵ� ����
	int			pfn_RADAR_OBJECT_DETECT_RANGE;		// 183, // 2008-09-22 by dhjin, ���̴� ��ü ���� �ݰ�
	float		pfm_PIERCE_UP_01;					// 184, // 2008-09-22 by dhjin, �⺻���� �Ǿ�� ���� ī��
	float		pfm_PIERCE_UP_02;					// 185, // 2008-09-22 by dhjin, ��޹��� �Ǿ�� ���� ī��
	float		pfm_ENGINE_ANGLE_UP;				// 186,	// 2008-09-30 by dhjin, ���� ȸ���� ���� ī��
	float		pfm_ENGINE_BOOSTERANGLE_UP;			// 187,	// 2008-09-30 by dhjin, ���� �ν��� ȸ���� ���� ī��	
	ParamValue_t	pf_ITEM_Resistance;				// 201, // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ������ ��� üũ 
	ParamValue_t	pf_ITEM_AddAttack;				// 202, // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���밪 Ÿ��ġ ������ ��� üũ 
	ParamValue_t	pf_ITEM_ReduceDamage;			// 205, // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ������ ���밪 ���� ������ ��� üũ
	ParamValue_t	pf_ITEM_AddAttack_Sec;			// 206, // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���밪 Ÿ��ġ ������ ��޹����(�⹫�� �з�)
	ParamValue_t	pf_ITEM_OnceResistance;			// 207, // 2009-09-09 ~ 2010-01-19 by dhjin, ���Ǵ�Ƽ - �� ���� �����ϰ� �������� ���� ������ �߰�
	float			pfm_PLUS_WARPOINT_RATE;			// 234, // 2010-05-18 by cmkwon, WarPoint ���� ������ ����(�Ϻ���û) - 
	ParamValue_t	pf_ITEMS_MOVE_SPEED_RATE;		// 239, // 2010-12-21 by jskim, ���� �̵� �ӵ� ���� ������ ����
};

