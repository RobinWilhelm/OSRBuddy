#pragma once
#include <windows.h>
#include "AtumParam.h"
#include "AtumProtocol.h"




typedef UINT32	UID32_t;

/*

typedef struct PK_TARGET
{
	int			nTargetIndex;
} PK_TARGET;


struct MEX_TIMER_EVENT
{
	TimerEventType		Type;
	UID32_t				TimerUID;				// Ÿ�̸� ���̵�
	TimeUnit_t			StartTimeStamp;			// milli-seconds
	TimeUnit_t			ExpireTime;				// milli-seconds
	TimeUnit_t			TimeInterval;			// milli-seconds, (ExpireTime - StartTimeStamp)
	UID32_t				CharacterUniqueNumber;	// event�� ������ charac�� ������ �ٸ� charac�� socket�� ����ϴ� ��츦 ���� ����, IsUsing()�� CharacterUniqueNumber�� ���ƾ� ��!
	ClientIndex_t		ClientIndex;			// event�� ������ charac�� ������ �ٸ� charac�� socket�� ����ϴ� ��츦 ���� ����, IsUsing()�� ClientIndex�� ���ƾ� ��!
	UINT				nGeneralParam1;			// end_skill: ITEM_SKILL* ,	mine: CMapBlock*,	delete_item��: ITEM_GENERAL*, GRADUAL_SHIELD_UP: HI(ItemUID), GRADUAL_XXX_UP: ITEM*, DELETE_DUMMY: FIELD_DUMMY*
	UINT				nGeneralParam2;			// end_skill: ,				mine: DROPMINE*,	delete_item��:              , GRADUAL_SHIELD_UP: LO(ItemUID)
	UINT				nGeneralParam3;			// end_skill: ,				mine: CFieldIOCP*,	delete_item��:              , GRADUAL_SHIELD_UP: ItemNum
	BOOL				bRepeatable;			// repeat�ؾ� �ϴ��� ����
	INT					nRemainedRepeatCount;	// ���� Ƚ��, ~0(0xFFFFFFFF): ���� �ݺ�, 0����: ����, 1�̻�: ȸ����ŭ �ݺ�
};


typedef struct
{
	UID32_t			FromCharacterUniqueNumber;		// From Possess, Ȥ�� FromCharacterUniqueNumber
	BYTE			ItemInsertionType;				// ������ ���� Ÿ��, IUT_XXX
	ITEM_GENERAL	ItemGeneral;
} MSG_FC_STORE_INSERT_ITEM;

typedef struct
{
	UID64_t			ItemUniqueNumber;	// ���� ������
	BYTE			ItemDeletionType;	// ������ ���� Ÿ��, IUT_XXX
} MSG_FC_STORE_DELETE_ITEM;

typedef struct
{
	UID64_t			ItemUniqueNumber;	// Update�� ������
	INT				NewCount;			// Count�� �� ��
	BYTE			ItemUpdateType;		// ������ ���� Ÿ��, IUT_XXX
} MSG_FC_STORE_UPDATE_ITEM_COUNT;

typedef MSG_FC_STORE_INSERT_ITEM		MSG_FC_TRADE_INSERT_ITEM;
typedef MSG_FC_STORE_UPDATE_ITEM_COUNT	MSG_FC_TRADE_UPDATE_ITEM_COUNT;

struct MSG_FC_ARENA_POSSIBLE_GAMESTART
{// 2008-01-08 by dhjin, �Ʒ��� �ɸ��� ������ �����Ѵ�.
	BitFlag16_t		MapWeather;
	CHARACTER		AFSCharacter;
	char			ServerGroupName0[SIZE_MAX_SERVER_NAME];
	char			MainORTestServerName[SIZE_MAX_SERVER_NAME];
	char			GamePublisher[SIZE_MAX_GAME_PUBLISHER_NAME];
	BOOL			IsPCBangUser;			// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - 
};

struct SARENA_GM_COMMAND_INFO
{
	BYTE 	ArenaMode;							// �Ʒ��� ��� 1 : DeathMatch, 2 : Round
	BYTE	Level;								// �� ����
	BYTE	MemberCount;						// �� �ο���
	INT		TeamCount;							// �� ��
};
typedef SARENA_GM_COMMAND_INFO			MSG_FC_ARENA_GM_COMMAND_INFO;

struct MSG_FC_CHARACTER_CASH_PREMIUM_CARD_INFO
{
	INT				nCardItemNum1;
	ATUM_DATE_TIME	atumTimeUpdatedTime1;	// ������ �ð�
	ATUM_DATE_TIME	atumTimeExpireTime1;	// ���� �ð�
	float			fExpRate1;
	float			fDropRate1;
	float			fDropRareRate1;
	float			fExpRepairRate1;
};



struct MEX_TARGET_INFO
{
	AVECTOR3		TargetPosition;			// ���� Ŭ���̾�Ʈ�� ȭ�鿡���� Ÿ�� ������
	ClientIndex_t	TargetIndex;			// ���� ��� ClientIndex or MonterIndex, 0�̸� ItemFieldIndex�� ��ȿ
	UINT			TargetItemFieldIndex;	// ���� ��� ������ �������̸� TargetIndex ��ȿ, �ƴϸ� TargetIndex�� 0
	USHORT			MultiTargetIndex;		// 2011-03-21 by hskim, ���Ǵ�Ƽ 3�� - ���� ��Ƽ Ÿ���� ��� �߰�

public:
	void SetNullTarget()
	{
		TargetIndex = 0;
		TargetItemFieldIndex = 0;
		MultiTargetIndex = 0;				// 2011-03-21 by hskim, ���Ǵ�Ƽ 3�� - ���� ��Ƽ Ÿ���� ��� �߰�
	}
};

typedef struct
{
	ClientIndex_t	AttackIndex;
	MEX_TARGET_INFO	TargetInfo;
	AVECTOR3		FirePosition;		// ������ �߻� ��ġ
	BYTE			AttackType;			// ���� Ÿ��, ATT_TYPE_XXX
	UID16_t			WeaponIndex;		// Ŭ���̾�Ʈ���� �߻�� �Ѿ��� �ε���, �������� ����, CUID16Generator ���
	UINT			ItemNum;			// ������ ItemNum
	USHORT			RemainedBulletFuel;	// ���� �Ѿ�(Ȥ�� Fuel)�� ��
	UINT			SkillNum;			// ��ų ��� �� ���
	ClientIndex_t	DelegateClientIdx;	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� �� 2�� ���� ���� ó�� �� ���� Ŭ���̾�Ʈ
} MSG_FC_BATTLE_ATTACK_OK;
  */

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

/*
struct MEX_MONSTER_INFO
{
	INT				MonsterUnitKind;					// ���� ������ȣ
	char			MonsterName[SIZE_MAX_MONSTER_NAME];	// ���� �̸�
	BYTE			Level;								// ������ Level
	INT				HP;									// ����
	BYTE			Size;								// �ʵ� ������ SizeForClient�� loading,  NPC ������ SizeForServer�� loading
	BYTE			Belligerence;						// ȣ����, // 2005-12-28 by cmkwon �߰���
	BYTE			AlphaBlending;						// alpha blending ����, TRUE(1), FALSE(0), client�� ����� ���� �߰�, 20030616
	USHORT			RenderIndex;
	float			ScaleValue;
	BYTE			TextureIndex;
	UINT			SourceIndex;
	BitFlag64_t		MPOption;			// 2010-01-11 by cmkwon, ���� MPOption 64bit�� ���� - ����(BYTE)
	BYTE			ClickEvent;							// 2007-09-05 by dhjin, ���� Ŭ�� �̺�Ʈ �߰�
	char			PortraitFileName[SIZE_MAX_FILE_NAME];	// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) - ���� �ʻ�ȭ ����
};

struct MEX_OTHER_GUILD_INFO
{
	char	GuildName[SIZE_MAX_GUILD_NAME];
	UID32_t	GuildUniqueNumber;
	UINT	GuildMarkVersion;

#ifdef _ATUM_IM_SERVER
	// operator overloading
	MEX_OTHER_GUILD_INFO& operator=(const CGuild& rhs);
#endif // _ATUM_IM_SERVER
};


struct MEX_QUEST_INFO						// Character�� ����Ʈ ����
{
	INT				QuestIndex;				// ����Ʈ ��ȣ
	BYTE			QuestState;				// �Ϸ�, ������
	LONGLONG		QuestPlayTimeStamp;		// ����Ʈ ���� ���� TotalPlayTime
	char			szCityWarServerGroupName[SIZE_MAX_SERVER_NAME];
};
 

struct WARP_TARGET_MAP_INFO_4_EXCHANGE
{
	MapIndex_t	MapIndex;
	INT			TargetIndex;	// EVENTINFO�� �����ϴ� TargetIndex
	char		TargetName[SIZE_MAX_WARP_TARGET_NAME];	// Ÿ���� �̸�(ex: ���û��, �����ϴ�)
	INT			Fee;			// ���� ���
};

struct MEX_CHANNEL_INFO {
	ChannelIndex_t	ChannelIndex;
	INT				Crowdedness;		// ȥ�⵵, 0% ~ 100%??, check: ��Ȯ�� ��� �����ؾ� ��
};
*/