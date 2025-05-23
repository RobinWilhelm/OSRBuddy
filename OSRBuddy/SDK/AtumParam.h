///////////////////////////////////////////////////////////////////////////////
//		캐릭터, 몬스터, 아이템 파라미터 정의
///////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ATUMPARAM_H)
#define AFX_ATUMPARAM_H

#include <math.h>
#ifdef _ATUM_CLIENT
#include "d3dx9math.h"
#else
#include <d3dx8math.h>
#include "XOR_Lib.h"		// 2007-10-24 by cmkwon, 서버 정보 암호화 - 추가함
#endif
#include <stdio.h>
//#include "DebugAssert.h"
#include <string>
#include <vector>
#include <SQLTYPES.H>
//#include "DefineGlobal.h"					// 2007-03-14 by cmkwon
//#include "LocalizationDefineCommon.h"		// 2006-09-05 by cmkwon
#include "AtumDateTime.h"
#include "mt_stl.h"							// 2007-01-09 by cmkwon

#if defined(_ATUM_SERVER)
#include "GlobalFunc.h"						// 2008-06-26 by cmkwon, float -> int 형변환 함수 추가 - 
#endif



typedef USHORT MessageType_t;
using namespace std;




// 2008-04-25 by cmkwon, 지원 언어/서비스 추가시 꼭 추가 되어야 하는 사항 - [언어-필수] 추가 언어 정의 추가
#define LANGUAGE_TYPE_UNKNOWN			-1
#define LANGUAGE_TYPE_KOREAN			0
#define LANGUAGE_TYPE_ENGLISH			1
#define LANGUAGE_TYPE_JAPANESE			2
#define LANGUAGE_TYPE_CHINESE			3
#define LANGUAGE_TYPE_VIETNAMESE		4			// 2006-02-27 by cmkwon
#define LANGUAGE_TYPE_GERMAN			5			// 2008-04-25 by cmkwon, 지원 언어에 독일어 추가 - 언어 정의 추가, Gameforge4D_Deu
#define LANGUAGE_TYPE_THAI				6			// 2008-04-11 by cmkwon, 지원 언어 추가 - 태국어(Thai - Tha)
#define LANGUAGE_TYPE_RUSSIAN			7			// 2008-04-11 by cmkwon, 지원 언어 추가 - 러시아어(Russian - Rus)
#define LANGUAGE_TYPE_TAIWANESE			8			// 2008-09-02 by cmkwon, 지원 언어 추가(대만어 Taiwanese - Tpe) - 
#define LANGUAGE_TYPE_TURKISH			9			// 2008-10-20 by cmkwon, 지원 언어 추가(터키아, 불어, 이탈리아어) - 
#define LANGUAGE_TYPE_FRENCH			10			// 2008-10-20 by cmkwon, 지원 언어 추가(터키아, 불어, 이탈리아어) - 
#define LANGUAGE_TYPE_ITALIAN			11			// 2008-10-20 by cmkwon, 지원 언어 추가(터키아, 불어, 이탈리아어) - 
#define LANGUAGE_TYPE_POLISH			12			// 2009-03-17 by cmkwon, 지원 언어 추가(폴란드어, 스페인어) - Gameforge4D_Pol(PL)
#define LANGUAGE_TYPE_SPANISH			13			// 2009-03-17 by cmkwon, 지원 언어 추가(폴란드어, 스페인어) - Gameforge4D_Esp(ES)
#define LANGUAGE_TYPE_ARGENTINA			14			// 2010-11-01 by shcho, Lin 아르헨티나 서비스 시작 준비 - 언어정의 추가
#define LANGUAGE_TYPE_INDONESIA			15			// 2010-01-11 by shcho,	 지원 서비스 추가(WinnerOnline 인도네시아어) -

#define LANGUAGE_TYPE_LAST				LANGUAGE_TYPE_INDONESIA		// 2009-03-17 by cmkwon, 지원 언어 추가(폴란드어, 스페인어) - 
// 2008-04-11 by cmkwon, 지원 언어 추가 - 아래와 같이 수정
//#define IS_VALID_LANGUAGE_TYPE(_lang)	((_lang) >= LANGUAGE_TYPE_KOREAN && (_lang) <= LANGUAGE_TYPE_VIETNAMESE)
#define IS_VALID_LANGUAGE_TYPE(_lang)	((_lang) >= LANGUAGE_TYPE_KOREAN && (_lang) <= LANGUAGE_TYPE_LAST)	// 2008-04-11 by cmkwon, 지원 언어 추가 - 

extern char* GET_LANGUAGE_TYPE_STRING(int i_nLangTy);	// 2008-04-25 by cmkwon, 지원 언어에 독일어 추가 - Gameforge4D_Deu 추가

// 2009-12-28 by cmkwon, 마상회사 IP 변경 - 기존(121.134.114.)
#define MASANG_PREFIX_IP1				"61.39.170."			// 2010-01-18 by cmkwon, 마상 서초 사무실, // 2007-01-03 by cmkwon, MasangSoft 남부터미널로 이전
#define MASANG_PREFIX_IP2				"222.99.72."			// 2010-01-18 by cmkwon, 마상 분당 사무실, // 2009-03-02 by cmkwon, 내부 테섭에서 캐쉬 포인트 관련 수정(디버그 모드시만 동작) - 2로 수정, // 2007-01-03 by cmkwon, MasangSoft 남부터미널로 이전
#define IS_MASANG_IP(ip)				(0 == strncmp((ip),MASANG_PREFIX_IP1,strlen(MASANG_PREFIX_IP1)) || 0 == strncmp((ip),MASANG_PREFIX_IP2,strlen(MASANG_PREFIX_IP2)))


///////////////////////////////////////////////////////////////////////////////
// Atum Type 정의
typedef INT64		TimeUnit_t;				// milli-seconds
typedef SHORT		Stat_t;					// 각 스텟 값
typedef BYTE		TimerEventType;			// 타이머 이벤트 타입, TE_TYPE_XXX
typedef UINT64		PartyID_t;				// 파티 아이디, PartyID(PartyUnqiueNumber + CreationTime)
typedef BYTE		BitFlag8_t;				// 8 bit flag
typedef USHORT		BitFlag16_t;			// 16 bit flag
typedef UINT		BitFlag32_t;			// 32 bit flag
typedef ULONGLONG	BitFlag64_t;			// 64 bit flag
typedef double		Experience_t;			// 경험치
#define COMPARE_BIT_FLAG(VAR, MASK)	(((VAR) & (MASK)) != 0)
#define SET_BIT_FLAG(VAR, MASK)		{(VAR) |= (MASK);}
#define CLEAR_BIT_FLAG(VAR, MASK)	{(VAR) &= ~(MASK);}
typedef short		Prob256_t;				// 확률 [0, 256)
#define PROB256_MAX_VALUE	255
typedef short		Prob100_t;				// 확률 [0, 100]
// 2010-07-19 by dhjin, 확률 수식 변경
// #define PROB100_MAX_VALUE	99	// 2010-07-19 by dhjin, 확률 수식 변경
#define PROB100_MAX_VALUE	100
typedef short		Prob1000_t;				// 확률 [0, 1000)
#define PROB1000_MAX_VALUE	999
typedef short		Prob10K_t;				// 확률 [0, 10000)
#define PROB10K_MAX_VALUE	9999
typedef int			Prob100K_t;				// 확률 [0, 100000)
#define PROB100K_MAX_VALUE	99999
typedef int			Prob1000K_t;			// 확률 [0, 1000000)
#define PROB1000K_MAX_VALUE	999999
typedef USHORT ChannelIndex_t;
typedef USHORT MapIndex_t;
const char* Int2String(int n, std::string& str);	// convert integer to string
#define INT2STRING(x)	Int2String(x, std::string())
typedef USHORT	Err_t;
typedef vector<UINT>		vectUINT;		// 2009-09-17 by cmkwon, B기어 체프 하향 - 

///////////////////////////////////////////////////////////////////////////////
// 2008-04-16 by cmkwon, 몬스터 사망 시 몬스터 소환 이벤트 시스템 구현 - 
#define MILLISECOND_TO_SECOND(ms)			((int)((ms)/1000))		// 2008-04-16 by cmkwon, 몬스터 사망 시 몬스터 소환 이벤트 시스템 구현 - MilliSecond 를 Second 로 변경하는 디파인 추가
#define Prob256_TO_Prob10K(pro)				(((pro)==PROB256_MAX_VALUE) ? PROB10K_MAX_VALUE : (Prob10K_t)((pro)*39.0625f))	// 2008-04-16 by cmkwon, 몬스터 사망 시 몬스터 소환 이벤트 시스템 구현 - 256 확률을 10K 확률로 변경
#define MAX_DELAY_TIME_AT_EVENT_MONSTER		600		// 2008-04-17 by cmkwon, 600 초 = 10 분

typedef enum
{
	MGAME_EVENT_NO_EVENT = 0,
	MGAME_EVENT_OPEN_BETA_ATTENDANCE = 1,			// 오픈베타 출석 이벤트
} MGAME_EVENT_t;

typedef USHORT	UID16_t;	// 2 Bytes Unique IDentifier, 0이거나 INVALID_UID16이면 잘못된 UID임, 기존의 UniqueNumber에 해당, 20040722, kelovon
typedef UINT32	UID32_t;	// 4 Bytes Unique IDentifier, 0이거나 INVALID_UID32이면 잘못된 UID임, 기존의 UniqueNumber에 해당, 20040722, kelovon
typedef UINT64	UID64_t;	// 8 Bytes Unique IDentifier, 0이거나 INVALID_UID64이면 잘못된 UID임, 기존의 UniqueNumber에 해당, 20040722, kelovon
#define INVALID_UID16		((UID16_t)~0)
#define INVALID_UID32		((UID32_t)~0)
#define INVALID_UID64		((UID64_t)~0)
#define INVALID_GUILD_UID	0				// 2005-02-04 by cmkwon

// Atum Defined SQL_C_XXX
#define SQL_C_PROB256		SQL_C_SHORT
#define SQL_C_PROB100		SQL_C_SHORT
#define SQL_C_PROB1000		SQL_C_SHORT
#define SQL_C_PROB10K		SQL_C_SHORT
#define SQL_C_PROB100K		SQL_C_LONG	
#define SQL_C_PROB1000K		SQL_C_LONG	
#define SQL_C_UID16			SQL_C_USHORT
#define SQL_C_UID32			SQL_C_ULONG
#define SQL_C_UID64			SQL_C_UBIGINT


// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 인피니티 관련 Type 정의
typedef INT			MSec_t;				// MilliSecond 단위 표현
typedef INT			HPActionUID_t;		// HPActionUID	Type
typedef INT			HPActionIdx_t;		// HPActionIndex Type
typedef BYTE		HPValueRate_t;		// HPValueRate Type
typedef INT			ItemIdx_t;			// ItemIndex Type
typedef BYTE		HPHitRate_t;		// HPHitRate Type
typedef INT			HPUseCount_t;		// HPUseCount Type	
typedef BYTE		HPTalkCondition_t;	// HPTalkCondition Type
typedef BYTE		HPTalkImportance_t; // HPTalkImportance Type
typedef char		HPTalk_t;			// HPTalk Type
typedef float		MonHP_t;			// MonsterHP Type
typedef	INT			CinemaNum_t;		// CinemaNum Type
typedef	INT			CinemaOrder_t;		// CinemaOrder Type
typedef	INT			RevisionNum_t;		// RevisionNum Type
typedef	USHORT		RevisionHP_t;		// RevisionHP Type
typedef	USHORT		RevisionDP_t;		// RevisionDP Type
typedef	INT			RevisionWeapon1_t;	// RevisionStandardWeapon Type
typedef	INT			RevisionWeapon2_t;	// RevisionAdvancedWeapon Type
typedef INT			EffectIdx_t;		// EffectIndex Type
typedef FLOAT		Position_t;			// Position Type
typedef INT			EffectPlayCount_t;	// EffectPlayCount Type
typedef short		ObjectIdx_t;		// ObjectIndex Type
typedef INT			ObjectNum_t;		// ObjectNumber Type
typedef INT			MonIdx_t;			// MonsterIdx Type
typedef BYTE		InfiMonTargetType_t;	// InfinityMonster Target Type
typedef BYTE		InfiMonTargetCount_t;	// InfinityMonster TargetCount Type
typedef INT			InfiModeUID_t;		// InfinityModeUID Type
typedef BYTE		ResetCycle_t;		// ResetCycle Type
typedef BYTE		EntranceCount_t;	// EntranceCount Type
typedef INT			Minute_t;			// Minute 단위 표현
typedef BYTE		Lv_t;				// Level Type
typedef BYTE		AdmissionCount_t;	// AdmissionCount Type
typedef UID64_t		ImputeUID_t;		// ImputeUID Type
typedef UID64_t		InfinityCreateUID_t;		// InfinityCreateUID Type
typedef BYTE		ChangeTarget_t;		// ChangeTarget Type
typedef UID32_t		KillCnt_t;			// KillCount Type
typedef UID32_t		DeathCnt_t;			// DeathCount Type
typedef UID32_t		TenderUID_t;		// TenderUID Type
typedef INT			ItemNum_t;			// ItemNum Type		// 2010-01-26 by cmkwon, 캐쉬 아이템 한정판매 시스템 구현 - 타입 정의 추가(기존 UID32_t)
typedef BYTE		DiceCnt_t;			// DiceCount Type
typedef char		CinemaTalk_t;		// CinemaTalk Type
typedef	float		ParamValue_t;		// Item ParamValue Type
typedef	UID32_t		InfinityShopUID_t;	// InfinityShopUID Type			// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 인피 상점
typedef UID32_t		InfinityShopItemCnt_t;	// InfinityShopItemCount Type // 2009-09-09 ~ 2010 by dhjin, 인피니티 - 인피 상점
typedef BYTE		DestParam_t;		// DestParam Type	// 2009-09-09 ~ 2010-02-10 by dhjin, 인피니티 - 발동류장착아이템
typedef INT			InvokingDestParamID_t;	// InvokingDestParamID Type	// 2009-09-09 ~ 2010-02-10 by dhjin, 인피니티 - 발동류장착아이템
typedef UID64_t		ItemUID_t;			// ItemUID Type		// 2009-09-09 ~ 2010-02-10 by dhjin, 인피니티 - 발동류장착아이템
typedef char		FileName_t;			// FileName Type		// 2010-03-31 by dhjin, 인피니티(기지방어) -
typedef INT			SummonCnt_t;		// SummonCount Type		// 2010-03-31 by dhjin, 인피니티(기지방어) -
typedef INT			Distance_t;			// Distance Type		// 2010-03-31 by dhjin, 인피니티(기지방어) -
typedef INT			QuestIndex_t;		// QuestIndex Type		// 2011-03-09 by hskim, 인피니티 3차 - 시네마 퀘스트 인덱스 설정 추가
typedef	BYTE		KeyMonster_t;		// KeyMonster Type		// 2011-04-21 by hskim, 인피니티 3차 - 시네마 단계별 기능 구현
typedef INT			CustomIdx_t;		// CustomIdx Type		// 2011-04-28 by hskim, 인피니티 3차 - 시네마 관련 기능 추가
typedef INT			Penalty_t;			// Penalty Type			// 2011-06-14 by hskim, 인피니티 3차 - 패널티 기능 추가 (HP 및 시간 동시 지원을 위해)					

// start 2011-04-28 by hskim, 인피니티 3차 - 시네마 관련 기능 추가
typedef enum
{
	CINEMA_MONSTER_INDEX_CREATE = 0,		// 몬스터 생성
	CINEMA_MONSTER_INDEX_DESTORY = 1,		// 몬스터 파괴
	CINEMA_MONSTER_INDEX_CHANGE = 2,		// 몬스터 교체
	CINEMA_MONSTER_INDEX_REGEN_ON = 3,		// 몬스터 리젠 ON 설정
	CINEMA_MONSTER_INDEX_REGEN_OFF = 4			// 몬스터 리젠 OFF 설정
} eCINEMA_MONSTER_INDEX_TYPE;
// end 2011-04-28 by hskim, 인피니티 3차 - 시네마 관련 기능 추가

// 2010-01-18 by cmkwon, 아이템 사용시 Parameter 중복 체크 시스템 구현 - 아래에 있던것을 여기 위쪽으로 옮김
typedef vector<INT>				vectINT;					// 2008-01-31 by cmkwon, 시간제한 아이템 DB 에 추가 중 체크 - 

///////////////////////////////////////////////////////////////////////////////
// START - Atum VECTOR3 정의
typedef SHORT		CoordUnit_t;			// 좌표의 단위

typedef struct _AVECTOR3
{
	CoordUnit_t	x;
	CoordUnit_t	y;
	CoordUnit_t	z;

	_AVECTOR3() { Reset(); }
	_AVECTOR3(CoordUnit_t i_x, CoordUnit_t i_y, CoordUnit_t i_z)
	{
		x = i_x;
		y = i_y;
		z = i_z;
	}

	inline _AVECTOR3& operator=(const D3DXVECTOR3& rhs)
	{
		this->x = (CoordUnit_t)rhs.x;
		this->y = (CoordUnit_t)rhs.y;
		this->z = (CoordUnit_t)rhs.z;
		return *this;
	}

	inline D3DXVECTOR3& CopyA2DX(D3DXVECTOR3& outVec)
	{
		outVec.x = (float)this->x;
		outVec.y = (float)this->y;
		outVec.z = (float)this->z;
		return outVec;
	}

	inline void Reset()
	{
		x = y = z = 0;
	}
} AVECTOR3;		// Atum Protocol용 Vector

#define A2DX(vec3)		(D3DXVECTOR3(vec3.x, vec3.y, vec3.z))			// Convert AVECTOR3 to D3DXVECTOR3
#define AP2DX(pVec3)	(D3DXVECTOR3(pVec3->x, pVec3->y, pVec3->z))		// Convert AVECTOR3* to D3DXVECTOR3
// END - Atum VECTOR3 정의
///////////////////////////////////////////////////////////////////////////////

struct STRNBUF
{
	STRNBUF(int i_nSize) { szBuf = new char[i_nSize]; memset(szBuf, 0, i_nSize); nSize = i_nSize; }
	~STRNBUF() { if (szBuf != NULL) { delete(szBuf); szBuf = NULL; } nSize = 0; }

	char* GetBuffer() { return szBuf; }
	int GetSize() { return nSize; }

private:
	char* szBuf;
	int		nSize;
};

inline float GGetLength(float x, float z)
{
	return sqrtf(x * x + z * z);
}

extern char CONFIG_ROOT[1024];

#ifndef __NPCID_T__
#define __NPCID_T__
typedef INT	NPCID_t;
typedef INT	NPCScriptID_t;
#endif// end__NPCID_T__

#define MAKEUINT32(low, high) ( (UINT)((USHORT)(low)) | ((UINT)((USHORT)(high)) << 16) )
#define MAKEUINT64(low, high) ( (UINT64)((UINT)(low)) | ((UINT64)((UINT)(high)) << 32) )

#define VALID_ATTACK_DISTANCE					100.0f		// Lock On, Attack 계산시에 필요한 기본 거리값
#define VALID_ATTACK_PINPOINT					0.523f		// 3.14 * 1/6 ==> 30도

#define SIZE_OTHER_SERVER_LIST					20			// 다른 서버들을 위해 IOCPSocket의 Array Server에 할당

#define SIZE_MAX_CLIENT_REPORT					256
#define SIZE_MAX_VERSION						4		// Client Version
#define SIZE_MIN_CHARACTER_NAME					2		// 2006-03-16 by cmkwon, 최소 캐릭터명 Character Name
#define SIZE_MAX_CHARACTER_NAME					20		// Character Name
#define SIZE_MAXUSE_CHARACTER_NAME				15		// 2006-05-19 by cmkwon, 최대는 20bytes 이지만 실제로는 15Bytes까지만 사용 가능
#define SIZE_MAX_NICK_NAME						SIZE_MAX_CHARACTER_NAME		// 2009-02-12 by cmkwon, EP3-3 월드랭킹시스템 구현 - 

// 2008-10-08 by cmkwon, 대만 2단계 계정 시스템 지원 구현(email->uid) - 
#if !defined(SIZE_MAX_ACCOUNT_NAME)
#define SIZE_MAX_ACCOUNT_NAME					20		// 1차 계정 이외에 사용될 2차 계정 사이즈, 대부분이 이것을 사용한다.
#endif
#if !defined(SIZE_MAX_ORIGINAL_ACCOUNT_NAME)
#define SIZE_MAX_ORIGINAL_ACCOUNT_NAME			20		// 2008-10-08 by cmkwon, 대만 2단계 계정 시스템 지원 구현(email->uid) - 인증시에만 사용될 1차 계정 사이즈
#endif

#define SIZE_MAX_CITY_NAME						40
#define SIZE_MAX_PASSWORD						20		// 6 ~ 16, 이 값을 바꾸면 FtpPassword때문에 UpdateFileList를 모두 바꿔야 하므로 주의 요!
#define SIZE_MAX_PASSWORD_MD5					16		//
#define SIZE_MAX_PASSWORD_MD5_STRING			33		// 32 characters
#define SIZE_MAX_GUILD_NAME						30
#define SIZE_MAX_GUILD_MARK_IMAGE				1600	// bytes, 20x20 4Bytes image
#define SIZE_MAX_SERVER_NAME					20		// SIZE_MAX_SERVER_GROUP_NAME
#define SIZE_MAX_MAP_NAME						40
#define SIZE_MAX_MAP_DESCRIPTION				1024		// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 
#define SIZE_MAX_PET_NAME						40		// 2010-06-16 by hslee, 20 --> 40
#define SIZE_MAX_PET_OPERATOR_DESCRIPTION		128		// 2010-12-03 by shcho, 펫 시스템 관련 스트링 로컬리제이션 추가
#define SIZE_MAX_MONSTER_NAME					40		// 2005-12-19 by cmkwon, 20 --> 40
#define SIZE_MAX_BUILDING_NAME					40		// 2008-01-03 by cmkwon, BuildingName 필드 40Bytes 로 수정 - , // = SIZE_MAX_SHOP_NAME
// 2008-01-03 by cmkwon, BuildingName 필드 40Bytes 로 수정 - 사용하지 않음
//#define SIZE_MAX_SHOP_NAME						20		// = SIZE_MAX_BUILDING_NAME
#define SIZE_MAX_NPC_NAME						40
#define SIZE_MAX_NPC_TALK_STRING				2000	// 2005-10-18 by cmkwon, 1000에서 2000으로 변경함, string1024를 string2048로 수정했음
#define SIZE_MAX_BUILDING_NPC_TALK_STRING		1000	// 2005-10-18 by cmkwon, 이전에는 SIZE_MAX_NPC_TALK_STRING를 같이 사용함
#define SIZE_MAX_QUEST_NAME						40
#define SIZE_MAX_RARE_FIX_NAME					30
#define SIZE_MAX_ITEM_NAME						40
#define SIZE_MAX_ITEM_DESCRIPTION				200
#define SIZE_MAX_NUM_CHARACTER					3
#define SIZE_MAX_CHAT_MESSAGE					100			// 2006-05-04 by cmkwon, 60-->100
#define SIZE_MAX_ERROR_STRING					60
#define SIZE_MAX_A_LOG_LINE						1400		// check: SIZE_MAX_PACKET - 92 !!!
#define SIZE_MAX_LOG_ACTION_STRING				1000		// check: SIZE_MAX_A_LOG_LINE - N
#define SIZE_MAX_WORKSPACE_FILE_NAME			40			// Map에서 Workspace File Name Size
#define SIZE_MAX_PROJECT_FILE_NAME				40			// Map에서 Project File Name Size
#define SIZE_MAX_EVENT_PARAM_NAME				40			// Map에서 Event Param Name Size
#define SIZE_MAX_MONSTER_REGION_NAME			40			// Map에서 Event Param Name Size
#define SIZE_MAX_NUM_MEMBER_IN_PARTY			8
#define HEIGHT_FLYING_ALTITUDE					30
#define SIZE_MAX_MAP_PER_A_FIELD_SERVER			100
#define SIZE_MAX_BLOCK_ELEMENT					100
#define MONSTER_CLIENT_INDEX_START_NUM			((ClientIndex_t)10000)		// monster의 client index의 시작 번호
#define MONSTER_CLIENT_INDEX_END_NUM			((ClientIndex_t)15000)		// monster의 client index의 시작 번호
#define SIZE_MAX_WARP_TARGET_NAME				40
#define SIZE_MAX_CITY_BRIEFING_LENGTH			100
#ifndef SIZE_MAX_IPADDRESS
#define SIZE_MAX_IPADDRESS					16		// string IP Address
#endif
#define SIZE_MAX_OBJECT_NAME					40
#define SIZE_MAX_COUPON_NUMBER					30
#define SIZE_MAX_BLOCKED_ACCOUNT_REASON			200
// 2006-09-04 by cmkwon, LocalizationDefineCommon.h 화일에 정의
//#define SIZE_MAX_GUILD_MEMBER_CAPACITY			60		// 최대 가능 길드원 수
//#define SIZE_MAX_INITIAL_GUILD_CAPACITY			40		// 초기 길드 생성 시 가능 길드원 수
#define ROLLING_USE_INTERVAL_TICK				3000	// 롤링 재사용 시간, // 2005-11-18 by cmkwon, 4초->3초
#define ROLLING_USE_CONSUMPTION_SP				3		// 롤링 사용시 소모되는 SP, // 2005-11-18 by cmkwon, 5->3


#define MAX_ITEM_COUNTS							2000000000					// 최대 아이템 카운트(20억)
#define MAX_NOTIFY_ITEM_COUNTS					(MAX_ITEM_COUNTS-100000000)	// 최대 경고 아이템 카운트(19억 = 20억-1억)
#define ITEM_NOT_USING							0							// 사용시간이 있는 아이템일 경우 사용중이 아니다
#define	MAX_ITEM_COUNTS_FOR_BUY					10							// 2008-07-16 by cmkwon, ITEM_GENERAL 관련 버그 체크 - 상점에서 넌카운트블 아이템 구입 가능한 최대 개수, 판매는 상관 없음.

#define SIZE_MAX_SZQUERY						2000			// 2007-01-30 by dhjin, 쿼리 완성을 위한 스트링 크기
#define SIZE_MAX_TABLE_NAME						128				// 2008-08-27 by cmkwon, 날쿼리를 Procedure로 수정 - 

// Client Index 정의
#if defined(_ATUM_FIELD_SERVER) || defined(_ATUM_NPC_SERVER)
#define CLIENT_INDEX_START_NUM					((ClientIndex_t)SIZE_MAX_UDP_CHANNEL_SESSION)	// 2008-08-29 by cmkwon, FieldServ<->NPCServ 가 UDP 통신 할 채널수 - // client index의 시작 번호
#elif defined(_ATUM_IM_SERVER)
#define CLIENT_INDEX_START_NUM					((ClientIndex_t)1)		// client index의 시작 번호
#else
#define CLIENT_INDEX_START_NUM					((ClientIndex_t)0)		// 2008-08-29 by cmkwon, FieldServ<->NPCServ 가 UDP 통신 할 채널수 - // client index의 시작 번호
#endif
#define CLIENT_INDEX_FIELDSERVER_NUM			60001					// 2011-03-28 by hskim, 인피니티 3차 - 몬스터 멀티 타겟팅 기능 추가 - field server index 번호 - 발사된 2형 무기의 필드 서버 처리를 위해 (선택된 유저가 없음)
#define INVALID_CLIENT_INDEX					((ClientIndex_t)~0)
#define IS_CHARACTER_CLIENT_INDEX(x)			((ClientIndex_t)(x) >= CLIENT_INDEX_START_NUM && (ClientIndex_t)(x) < MONSTER_CLIENT_INDEX_START_NUM)	// character인지 확인
#define IS_MONSTER_CLIENT_INDEX(x)				((ClientIndex_t)(x) >= MONSTER_CLIENT_INDEX_START_NUM && (ClientIndex_t)(x) < 20000)					// monster인지 확인, check: 20000이면 충분하다고 생각함, 2003103, kelovon w/ chkwon
#define IS_VALID_CLIENT_INDEX(idx)				(idx >= CLIENT_INDEX_START_NUM && idx < MONSTER_CLIENT_INDEX_START_NUM && idx != INVALID_CLIENT_INDEX && idx != 0)
#define IS_VALID_CHARACTER_AND_MONSTER_INDEX(idx)				(idx >= CLIENT_INDEX_START_NUM && idx < 20000 && idx != INVALID_CLIENT_INDEX && idx != 0)			// 2009-09-09 ~ 2010-01-11 by dhjin, 인피니티 - 몬스터간 타겟 설정을 위해 수정			
#define INVALID_UNIQUE_NUMBER					(UINT)(~0)
#define IS_VALID_UNIQUE_NUMBER(num)				((num) != 0 && (num) != INVALID_UNIQUE_NUMBER)
#define IS_VALID_UID64(num)						((num) != 0 && (num) != INVALID_UID64)				// 2006-10-11 by cmkwon
#define SIZE_MAX_VERSION_STRING					64
// 2006-09-06 by cmkwon, LocalizationDefineCommon.h 화일에 정의
//#define CHARACTER_MAX_LEVEL						100
#define PI										3.1415926535f
#define SIZE_MAX_LONG_PACKET					200000	// 긴 packet을 보낼 때 사용할 buffer의 사이즈, 사용시 크기 비교 필요함
#define DEFAULT_POSITION_X						100
#define DEFAULT_POSITION_Y						HEIGHT_FLYING_ALTITUDE
#define DEFAULT_POSITION_Z						100
#define SPEED_INCREASE_AMOUNT					19
#define REQUERED_TRADE_DISTANCE					500			// check: 정확한 거리 정하기
#define REQUERED_P2P_PK_DISTANCE				1500			// check: 정확한 거리 정하기
#define REQUERED_REQUEST_DISTANCE				1500			// check: 정확한 거리 정하기
// 2005-12-08 by cmkwon, 제거됨
//#define POSSESS_STORE_NUMBER					0			// 창고에 있을 때 possess 수치
#define POSSESS_AUCTION_NUMBER					((UID32_t)0xFFFFFFFF)	// 경매 중일 때 possess 수치, -1 = 0xFFFFFFFF
#define CHARACTER_SIZE							15.0f		// 캐릭터 반지름
#define INVALID_MAP_NAME						""
#define MAP_INDEX_ALL							(USHORT)(~0)
#define ATUM_LOAD_TEST_PREFIX_ACCOUNT_NAME			"*loadtest"
#define ATUM_LOAD_TEST_PREFIX_ACCOUNT_NAME_SIZE		9
#define SIZE_MAX_PARTY_MEMBER					6			// 최대 파티원 수
#define SIZE_MAX_INITIAL_SUM_OF_STAT			24
#define SIZE_MAX_ENCHANT_PER_ITEM				40			// 한 아이템에 붙일 수 있는 최대 인챈트 수
#define SIZE_MAX_ENCHANT_USE_ITEMKIND_PREVENTION_DELETE_ITEM	40	// 파방(파과방지) 사용 가능한 최대 인챈트수, // 2006-08-23 by cmkwon, 8 --> 40
#define SIZE_REMAIN_ENCHANT_COUNT_BY_PREVENTION_DELETE_ITEM		5	// 인챈트시 파방(파과방지) 사용하면 남는 인챈크 카운트
#define IS_VALID_PLANE_COORDINATES(x, z, maxX, maxZ)	((x) >= 0 && (z) >= 0 && (x) < (maxX) && (z) < (maxZ))
#define ACOS(fVal)									(((fVal) > 1.0f) ? acos(1.0f) : acos(fVal))
#define SIZE_MAX_FTP_URL							64
#define DOWNLOAD_BUFFER_SIZE						4096
#define SIZE_MAX_FTP_FILE_PATH						256
#define SIZE_MAX_FRIENDLIST_COUNT					60		// 2006-07-18 by cmkwon, 50 --> 60
#define SIZE_MAX_REJECTLIST_COUNT					60		// 2006-07-18 by cmkwon, 50 --> 60
#define SIZE_CITY_POSITION_RANDOM_XZ_RADIUS			30		// 2005-12-21 by cmkwon, 50 --> 30		

// 2006-09-04 by cmkwon, LocalizationDefineCommon.h 화일에 정의
//#define SIZE_MAX_ITEM_GENERAL						61		// 캐릭터의 인벤토리에 소유할 수 있는 아이템의 최대 개수(1개는 SPI 아이템의 카운트이다, 클라이언트는 60을 사용한다.)
//#define SIZE_MAX_ITEM_GENERAL_IN_STORE				101		// 창고에 소유할 수 있는 아이템의 최대 개수

#define TUTORIAL_MAP_INDEX							8001	// 튜토리얼맵은 하나이므로 define한다
#define VCN_CITY_MAP_INDEX							2001	// 일반군, 정규군 도시맵인덱스
#define ANI_CITY_MAP_INDEX							2002	// 반란군 도시맵인덱스
// 2009-10-12 by cmkwon, 프리스카 제거 방안 적용 - 제거
//#define NORMAL_CITY_MAP_INDEX						2003	// 2007-05-21 by cmkwon, 일반군 도시맵인덱스 - 아카데미맵
#define INFLUENCE_CITY_MAP_INDEX					9999	// 각 세력별 도시맵인덱스
#define INFLUENCE_GARDEN_MAP_INDEX					9998	// 2009-10-12 by cmkwon, 프리스카 제거 방안 적용 - 각 세력별 앞마당(Garden)
#define VCN_CONFERENCEROOM_MAP_INDEX				1001	// 2007-08-30 by cmkwon, 회의룸 시스템 구현 - 정규군 회의룸 맵인덱스
#define ANI_CONFERENCEROOM_MAP_INDEX				1002	// 2007-08-30 by cmkwon, 회의룸 시스템 구현 - 반란군 회의룸 맵인덱스

// 2006-07-03 by cmkwon, 1000번대는 개인상점맵으로 사용 할 것임
//#define IS_CITY_MAP_INDEX(__MAP_INDEX)				(((MapIndex_t)__MAP_INDEX)/1000==1)		// 격납고맵
#define IS_CONFERENCEROOM_MAP_INDEX(__MAP_INDEX)	( (VCN_CONFERENCEROOM_MAP_INDEX==(__MAP_INDEX)) || (ANI_CONFERENCEROOM_MAP_INDEX==(__MAP_INDEX)) )			// 2007-08-30 by cmkwon, 회의룸 시스템 구현 - 맵인덱스 정의 추가함
#define IS_BAZAAR_MAP_INDEX(__MAP_INDEX)			(IS_CONFERENCEROOM_MAP_INDEX(__MAP_INDEX))	// 2007-08-30 by cmkwon, 회의룸 시스템 구현 - 기존  바자맵을 이용함,	// 2006-07-19 by cmkwon, 개인상점맵
#define IS_CITYWAR_MAP_INDEX(__MAP_INDEX)			(((MapIndex_t)__MAP_INDEX)/1000==5)		// 도시점령전이 일어나는 맵
#define IS_SPACE_MAP_INDEX(__MAP_INDEX)				(((MapIndex_t)__MAP_INDEX)/1000==6)		// 우주맵
#define IS_TUTORIAL_MAP_INDEX(__MAP_INDEX)			((__MAP_INDEX)==TUTORIAL_MAP_INDEX)		// 튜토리얼맵
#define IS_RACING_MAP_INDEX(__MAP_INDEX)			(((MapIndex_t)__MAP_INDEX)/1000==9)		// 레이싱맵
#define IS_VCN_CITY_MAP_INDEX(__MAP_INDEX)			((__MAP_INDEX) == VCN_CITY_MAP_INDEX)	// 일반군, 정규군 도시맵인덱스인가?
#define IS_ANI_CITY_MAP_INDEX(__MAP_INDEX)			((__MAP_INDEX) == ANI_CITY_MAP_INDEX)	// 반란군 도시맵인덱스인가?
// 2009-10-12 by cmkwon, 프리스카 제거 방안 적용 - 제거
//#define IS_NORMAL_CITY_MAP_INDEX(__MAP_INDEX)		((__MAP_INDEX) == NORMAL_CITY_MAP_INDEX)	// 2007-05-21 by cmkwon, 일반군 도시맵인덱스인가?
#define IS_OUTPOST_CITY_MAP_INDEX(__MAP_INDEX)		(2004 == (__MAP_INDEX) || 2005 == (__MAP_INDEX) || 2006 == (__MAP_INDEX))		// 2008-09-10 by dhjin, 2006추가 차후 MAP_INFLUENCE_OUTPOST = 6000값으로 변경해야할듯하다.	// 2007-09-10 by dhjin, 전진기지 도시맵 인가? 

// 2008-02-12 by cmkwon, IS_CITY_MAP_INDEX() 매크로를 포괄적인 도시맵인지 여부를 리턴
// 2009-10-12 by cmkwon, 프리스카 제거 방안 적용 - 일반세력 도시맵 제외
//#define IS_CITY_MAP_INDEX(__MAP_INDEX)				(IS_VCN_CITY_MAP_INDEX(__MAP_INDEX) || IS_ANI_CITY_MAP_INDEX(__MAP_INDEX) || IS_NORMAL_CITY_MAP_INDEX(__MAP_INDEX) || IS_CONFERENCEROOM_MAP_INDEX(__MAP_INDEX) || IS_OUTPOST_CITY_MAP_INDEX(__MAP_INDEX))		// 격납고맵 - // 2007-05-21 by cmkwon, IS_NORMAL_CITY_MAP_INDEX() 추가함
#define IS_CITY_MAP_INDEX(__MAP_INDEX)				(IS_VCN_CITY_MAP_INDEX(__MAP_INDEX) || IS_ANI_CITY_MAP_INDEX(__MAP_INDEX) || IS_CONFERENCEROOM_MAP_INDEX(__MAP_INDEX) || IS_OUTPOST_CITY_MAP_INDEX(__MAP_INDEX))		// 2009-10-12 by cmkwon, 프리스카 제거 방안 적용 - ,// 격납고맵 - // 2007-05-21 by cmkwon, IS_NORMAL_CITY_MAP_INDEX() 추가함

// 2009-10-12 by cmkwon, 프리스카 제거 방안 적용 - 일반세력 도시맵 제외
//#define IS_INFLUENCE_CITY_MAP_INDEX(__MAP_INDEX)	(IS_VCN_CITY_MAP_INDEX(__MAP_INDEX) || IS_ANI_CITY_MAP_INDEX(__MAP_INDEX) || IS_NORMAL_CITY_MAP_INDEX(__MAP_INDEX))		// 2008-02-12 by cmkwon, 세력별 도시맵
#define IS_INFLUENCE_CITY_MAP_INDEX(__MAP_INDEX)	(IS_VCN_CITY_MAP_INDEX(__MAP_INDEX) || IS_ANI_CITY_MAP_INDEX(__MAP_INDEX))		// 2009-10-12 by cmkwon, 프리스카 제거 방안 적용 - , // 2008-02-12 by cmkwon, 세력별 도시맵

///////////////////////////////////////////////////////////////////////////////
// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 팅긴 유저 재접속 처리
#define INFINITY_MAP_INDEX				9200
#define	INFINITY_MAP_INDEX_LAST			9299
#define IS_INFINITY_MAP_INDEX(__MAP_INDEX)		( INFINITY_MAP_INDEX <= (__MAP_INDEX) && INFINITY_MAP_INDEX_LAST >= (__MAP_INDEX) )


#define MONEY_ITEM_NUMBER							7000022		// 스피(SPI) 아이템넘버
#define ITEM_NUM_CASH_NORMAL_PREMIUM_CARD			7001120		// 일반 프리미엄 아이템넘버
// 2006-07-05 by cmkwon, MonthlyPay 시스템에는 필요 없는 define
//#define ITEM_NUM_CASH_SUPER_PREMIUM_CARD			7001130		// 슈퍼 프리미엄 아이템넘버
//#define ITEM_NUM_CASH_UPGRADE_PREMIUM_CARD			7001140		// 슈퍼 업그레이드 아이템넘버
#define ITEM_NUM_APLUS_GRADE_HP_KIT					7010430		// A+급수리키트		- 클라이언트에서만 사용
#define ITEM_NUM_APLUS_GRADE_DP_KIT					7010440		// A+급쉴드키트		- 클라이언트에서만 사용
#define ITEM_NUM_S_GRADE_HP_KIT						7010290		// S급수리키트		- 클라이언트에서만 사용
#define ITEM_NUM_S_GRADE_DP_KIT						7010300		// S급쉴드키트		- 클라이언트에서만 사용

#define ITEM_NUM_NEUTRON_RECHARGEABLE_BATTERY_MKIII	7026260		// 2009-09-09 ~ 2010-01-13 by dhjin, 인피니티 - 회복 아이템 추가 // 뉴트론 충전지 MKIII
#define ITEM_NUM_NEUTRON_RECHARGEABLE_BATTERY_MKII	7026280		// 2009-09-09 ~ 2010-01-13 by dhjin, 인피니티 - 회복 아이템 추가 // 뉴트론 충전지 MKII
#define ITEM_NUM_NEUTRON_RECHARGEABLE_BATTERY_MKI	7026290		// 2009-09-09 ~ 2010-01-13 by dhjin, 인피니티 - 회복 아이템 추가 // 뉴트론 충전지 MKI
#define ITEM_NUM_DEUS_EX_MACHINA_MKIII				7026300		// 2009-09-09 ~ 2010-01-13 by dhjin, 인피니티 - 회복 아이템 추가 // 데우스 엑스 마키나 MKIII
#define ITEM_NUM_DEUS_EX_MACHINA_MKII				7026310		// 2009-09-09 ~ 2010-01-13 by dhjin, 인피니티 - 회복 아이템 추가 // 데우스 엑스 마키나 MKII
#define ITEM_NUM_DEUS_EX_MACHINA_MKI				7026320		// 2009-09-09 ~ 2010-01-13 by dhjin, 인피니티 - 회복 아이템 추가 // 데우스 엑스 마키나 MKI


#define ITEM_NUM_BRIGHTNESS_OF_BCU_LEADER			7001320		// 2007-05-02 by dhjin, '지도자의 광휘' 아이템 번호 
#define ITEM_NUM_BRIGHTNESS_OF_ANI_LEADER			7001330		// 2007-05-02 by dhjin, '지도자의 광휘' 아이템 번호 


#define SIZE_MAX_ARMOR_COLOR_COUNT						10			// 2005-12-08 by cmkwon, 아머가 가질수 있는 최대 색상 개수
#define COLORItemNum_TO_ArmorSourceIndex(itemNum)		(((int)((itemNum)/100))*100)		// 색상아이템의 ItemNum을 아머의 SourceIndex로 변환하기
#define ARMORSourceIndex_TO_BaseColorItemNum(itemNum)	(((int)((itemNum)/100))*100 + 1)	// 아머의 SourceIndex로 기본색상아이템의 ItemNum으로 변환하기

#define TERM_ENABLE_CASH_PREMIUM_CARD_BUY_MONTH		1			// 한달더 추가로 구입 가능하다
#define TERM_MONTHLYPAY_MAX_BUY_ENABLE_DAY			180			// MonthlyPay 구입 가능 최대 날짜

#define CASH_SHOP_BUILDING_INDEX					9999		// 유료화 상점 BuindNPCIndex
#define FIELD_STORE_SHOP_BUILDING_INDEX				9998		// 2009-09-23 by cmkwon, 필드창고 캐쉬 아이템 구현 - 필드창고 BuildingIndex

#define DEFAULT_OBJECT_MONSTER_OBJECT				90000000
#define IS_DEFAULT_OBJECT_MONSTER_OBJECT(num)		(  (int)((num)/10000000) == 9  )


#define TIMEGAP_CITYWAR_CHANGEABLE_TERM_HOUR		4		// 여단장이 변경 가능한(디폴트 시간이후부터) 다음 도시점령전 시간
#define CITYWAR_MINIMUM_TEX_PERCENT					2.0f	// 도시점령전 상점 이용 최소 tex
#define CITYWAR_MAXIMUM_TEX_PERCENT					100.0f	// 도시점령전 상점 이용 최대 tex

#define TICKGAP_SEND_INVASION_MSG					300000	// 침략 메시지 전송 텀, 단위:ms, 300000 = 300초 = 5분
#define MAXIMUM_USABLE_FAME_POINT_FOR_ONE_DAY		20		// 2005-12-29 by cmkwon, 하루에 한명에게 받을수 있는 최대 명성치

#define SIZE_MAX_USERLIST_ON_BOSS_MONSTER_DEAD		10		// 2006-01-23 by cmkwon, 보스 몬스터 죽을 때 로그 남길 유저 리스트 숫자

// 2006-09-28 by cmkwon, 변경(1000-->300)
#define SIZE_MIN_SELECTED_INFLUENCE_TYPE_USER_COUNT_FOR_INFLUENCE_DISTRIBUTION		100		// 2009-03-31 by cmkwon, 세력초기화 시스템 구현 - 기존(300), // 2006-02-08 by cmkwon, 세력 분포 처리를 위한 조건인 세력 선택 유저의 총합

#define SIZE_MAX_SIGN_BOARD_STRING					64		// 2006-04-17 by cmkwon, 전광판에 들어갈 스트링 최대 길이
#define INFLWAR_APPLY_TAX_PERIOD_DAY				30		// 2006-05-19 by cmkwon, 세력전 분포 계산에 들어가 캐릭터 검색시 최근 로그인이 현재에서 이날짜 이전보다 이후여야한다.

#define WEIGHT_RATE_HEAVY							0.7f	// 2006-10-13 by cmkwon, 초과시 연료 소모 2배 
#define WEIGHT_RATE_VERY_HEAVY						0.8f	// 2006-10-13 by cmkwon, 초과시 연료 소모 2배, 부스터 사용 안됨

#define TERM_QUEST_REQUEST_WARP_EFFECTIVE_TIME		20000	// 2006-10-16 by cmkwon, 파티 워프 유효시간(단위:ms)

#define TERM_STRATEGYPOINT_OCCUPY_TIME						7200000		// 2006-11-21 by cmkwon, 전략포인트 폭파시 소유 시간(단위:ms, 7200000 = 2시간 = 2*60*60*1000)
#define ADD_CONTRIBUTIONPOINT_STRATEGYPOINT_MONSTER			500			// 2006-11-21 by cmkwon, 전략포인트 폭파/방어 성공시 증가 기여도
#define ADD_CONTRIBUTIONPOINT_BOSS_MONSTER					1000		// 2007-05-15 by dhjin, 모선 폭파/방어 성공시 증가 기여도
#define ADD_WARPOINT_STRATEGYPOINT_MONSTER					300			// 2007-09-06 by dhjin 100=>300, // 2007-05-15 by dhjin, 전략포인트 폭파/방어 성공시 증가 WARPOINT 
#define ADD_WARPOINT_BOSS_MONSTER							500			// 2007-09-06 by dhjin 300=>500, // 2007-05-15 by dhjin, 모선 폭파/방어 성공시 증가 WARPOINT
#define ADD_WARPOINT_STRATEGYPOINT_MONSTER_BY_LOSE			100			// 2008-01-07 by dhjin, 세력 보상 수정 - 전략포인트 폭파/방어 패배시 증가 WARPOINT 
#define ADD_WARPOINT_BOSS_MONSTER_BY_LOSE					200			// 2008-01-07 by dhjin, 세력 보상 수정 - 모선 폭파/방어 패배시 증가 WARPOINT
#define ADD_WARPOINT_EVENT_MONSTER_BY_LOSE					250			// 2010-06-21 by jskim, 이벤트 몬스터 보상 워포인트

#define TERM_GAME_PLAYTIME_LIMIT_FIRST_SEC					10800		// 2006-11-23 by cmkwon, 10800초(3*60*60) = 3시간 - 경험치/SPI 50%
#define TERM_GAME_PLAYTIME_LIMIT_LAST_SEC					18000		// 2006-11-23 by cmkwon, 18000초(5*60*60) = 5시간 - 경험치/SPI 0%

// 2009-04-06 by cmkwon, 스킬 관련 속성 추가안 구현(사용 시간 저장) - 속성으로 처리함, 제거됨.
//#define TERM_TICK_MUST_SERVER_CHECK_SKILL_REATTACK_TIME		600000		// 2006-12-15 by cmkwon, 10분(10*60*1000) RaattackTime이 10분 초과인 스킬은 서버에서도 체크한다


#define WM_UPDATEFILE_DOWNLOAD_ERROR						WM_USER + 100	// 2007-01-05 by cmkwon
#define WM_UPDATEFILE_DOWNLOAD_INIT							WM_USER + 101	// 2007-01-05 by cmkwon
#define WM_UPDATEFILE_DOWNLOAD_PROGRESS						WM_USER + 102	// 2007-01-05 by cmkwon
#define WM_UPDATEFILE_DOWNLOAD_OK							WM_USER + 103	// 2007-01-05 by cmkwon

#define SIZE_MAX_SERVER_GROUP_COUNT							20				// 2007-01-18 by cmkwon, 서버 그룹 최대 개수

// 2008-12-18 by cmkwon, 일본 Arario 외부인증, 빌링 모듈 적용하기 - 아래와 같이 일본만 사이즈를 다르게 한다.
//#define SIZE_MAX_WEBLOGIN_AUTHENTICATION_KEY				30				// 2007-03-29 by cmkwon, 웹인증키 최대 스트링 사이즈(현재는 예당만 사용 예정)
#if defined(SERVICE_TYPE_JAPANESE_SERVER_1)
#define SIZE_MAX_WEBLOGIN_AUTHENTICATION_KEY				301				// 2008-12-18 by cmkwon, 일본 Arario 외부인증, 빌링 모듈 적용하기 - 세션키가 전달것임. AUTH_SESSIONKEY_LEN + 1 크기가 필요
#else
#define SIZE_MAX_WEBLOGIN_AUTHENTICATION_KEY				30				// 2007-03-29 by cmkwon, 웹인증키 최대 스트링 사이즈(현재는 예당만 사용 예정)
#endif

#define SIZE_MAX_GAME_PUBLISHER_NAME						20				// 2007-04-09 by cmkwon
#define SIZE_MAX_ADD_CHARACTER_NAME							5				// 2007-04-10 by cmkwon, 캐릭터명뒤에 붙이는 스트링 최대 사이트


#define SIZE_MAX_GAME_SERVER_GROUP_NAME						30				// 2007-05-02 by cmkwon
#define COUNT_MAX_GAME_SERVER_GROUP_LIST					10					

// 2008-09-17 by cmkwon, 클라이언트 실행파일도 체크섬 체크 추가 - 
//#define	SIZE_MAX_RESOBJ_FILE_NAME							20				// 2007-05-28 by cmkwon, 
#define	SIZE_MAX_RESOBJ_FILE_NAME							30				// 2008-09-17 by cmkwon, 클라이언트 실행파일도 체크섬 체크 추가 - 30 Bytes 로 수정

#define	TICKGAP_WARHEAD_LIFETIME							20000			// 2007-06-12 by cmkwon, 2형 무기 탄두가 발사 후 유효한 시간(ms)
#define	TICKGAP_WARHEAD_LIFETIME_LONG						50000			// 2007-06-12 by cmkwon, 2형 무기 탄두가 발사 후 유효한 시간(ms) - // 2011-03-28 by hskim, 인피니티 3차 - 몬스터 멀티 타겟팅 기능 추가 - 주포용 긴 시간 2형 탄두 무기

// 2007-06-27 by cmkwon, 파티원 경험치 분배 방식 시스템 추가 - 타입 정의
#define MAX_LEVEL_GAP_APPLY_PARTY_BONUS						14				// 2008-06-10 by dhjin, EP3 편대 수정 - 7->14로 변경 // 2007-06-27 by cmkwon, 파티 보너스 적용 최대 레벨차			
#define EXP_DISTRIBUTE_TYPE_DAMAGE							0				// 2007-06-27 by cmkwon, 몬스터에 준 데미지에 따른 경험치 분배
#define EXP_DISTRIBUTE_TYPE_EQUALITY						1				// 2007-06-27 by cmkwon, 균등 분배

#define TERM_10MINUTES_BY_SECOND							600				// 2007-06-28 by cmkwon, 예당 7월 PC방 콩이벤트 지급 시간 수정 -
#define TERM_30MINUTES_BY_SECOND							1800			// 2007-06-28 by cmkwon, 예당 7월 PC방 콩이벤트 지급 시간 수정 -
#define TERM_60MINUTES_BY_SECOND							3600			// 2007-06-28 by cmkwon, 예당 7월 PC방 콩이벤트 지급 시간 수정
#define TERM_10MINUTES_BY_MILLISECOND						600000			// 2007-06-28 by cmkwon, 중국 방심취관련(게임 시간 알림 구현) - 10분

#define SIZE_MAX_JUMIN_NUMBER								20				// 2007-06-29 by cmkwon, td_account 테이블에 주민번호저장하기 

#define RECHARGE_BULLET_ALL_CALIBER							255				// 2007-08-07 by cmkwon, 1형/2형 무기 총알 충전 아이템 구현 - Caliber 정의

#define SIZE_MAX_STRING_128									128				// 2007-08-09 by cmkwon, 모든 세력에 채팅 전송하기 - 정의 추가
#define SIZE_MAX_STRING_256									256				// 2007-08-09 by cmkwon, 모든 세력에 채팅 전송하기 - 정의 추가
#define SIZE_MAX_STRING_512									512				// 2007-08-09 by cmkwon, 모든 세력에 채팅 전송하기 - 정의 추가
#define SIZE_MAX_STRING_1024								1024			// 2007-08-09 by cmkwon, 모든 세력에 채팅 전송하기 - 정의 추가

#define SIZE_MAX_CONFERENCEROOM_USER						100				// 2007-08-30 by cmkwon, 회의룸 시스템 구현 - 회의름 허가 최대 인원수

#define	STR_INVALID_CHARACTER_NAME							" \r\n\t"		// 2007-10-22 by cmkwon, 캐릭터명에 유효하지 않은 문자
#define	STR_INVALID_PRE8SUFFIX_GUILD_NAME					" \r\n\t"		// 2007-10-22 by cmkwon, 여단명 시작과 끝에 유효하지 않은 문자


#define STR_XOR_KEY_STRING_SERVER_INFO						"~8xANs(^fP{)34$(fcbTN$(C-=x"					// 2007-10-24 by cmkwon, 서버 정보 암호화 - DB Server Password XOR Key
#define STR_XOR_KEY_STRING_PRE_SERVER_ADDRESS				"+-faNsf(^fP{)3>fnao??_+|23kdasf*^@`d{]s*&DS"	// 2008-04-23 by cmkwon, PreServer 주소를 IP와 도메인 둘다 지원 - 
#define STR_XOR_KEY_STRING_DB_ID_PWD						"@34ns%<<fdsa(Tflsd!sndsa^#)fndsla$nvsa$fndsla&nfdsJak(fnldsa!#F"	// 2008-09-01 by cmkwon, global.cfg 파일에 DB ID/PWD 암호화 - 
#define STR_XOR_KEY_STRING_SECURITY_COMMAND					"^@dk@11@<$HGJKAOkfjqpojg@1-09f-0102890jkfmlk!@#68f91!@jf902121Z"	// 2011-06-22 by hskim, 사설 서버 방지 (커맨드용 암호화 키)

#define COUNT_MAX_SECURITY_COMMAND							3				// 2011-06-22 by hskim, 사설 서버 방지 (커맨드용 암호화 키 명령의 최대 갯수)
#define SIZE_MAX_SECURITY_COMMAND							1024			// 2011-06-22 by hskim, 사설 서버 방지 (커맨드용 암호화 키의 최대 크기)
#define SIZE_THRESHOLD_SECURITY_COMMAND						50				// 2011-06-22 by hskim, 사설 서버 방지 (커맨드용 암호화인지 키의 길이로 판단하는 최소 값)

#define SIZE_MAX_DB_USER_ID									128				// 2007-12-13 by cmkwon, 128 bytes 로 변경, // 2007-10-24 by cmkwon, 서버 정보 암호화
#define SIZE_MAX_DB_USER_PWD								128				// 2007-12-13 by cmkwon, 128 bytes 로 변경, // 2007-10-24 by cmkwon, 서버 정보 암호화

#define SIZE_MAX_WINDOW_DEGREE_NAME							128				// 2007-12-27 by cmkwon, 윈도우즈 모드 기능 추가 - 추가

#define SIZE_MAX_ODBC_CONN_STRING							128		// 2008-03-03 by cmkwon, SIZE_MAX_ODBC_CONN_STRING 정의 위치 변경 - GlobalGameServer.h 에 있던것을 여기로 옮김

///////////////////////////////////////////////////////////////////////////////
// 2010-11-29 by shcho, 아르헨티나 외부인증 변경 SOAP 처리
#define SIZE_MAX_URL_STRNIG									512
#define SIZE_MAX_GAME_ID									10
// end 2010-11-29 by shcho, 아르헨티나 외부인증 변경 SOAP 처리
///////////////////////////////////////////////////////////////////////////////


// 2008-04-29 by cmkwon, 서버군 정보 DB에 추가(신규 계정 캐릭터 생성 제한 시스템추가) - 
#define SIZE_MAX_INIT_LIMIT_USER_COUNT_PER_SERVER_GROUP		500				// 2008-04-29 by cmkwon, 서버군 정보 DB에 추가(신규 계정 캐릭터 생성 제한 시스템추가) - 

#define MIN_SUPPORT_YEAR			1970		// 2008-06-27 by cmkwon, 날짜시간 관련 버그 수정(1970 ~ 2037) - 
#define MAX_SUPPORT_YEAR			2037		// 2008-06-27 by cmkwon, 날짜시간 관련 버그 수정(1970 ~ 2037) - 

#define MAX_ITEM_COUNT_FOR_PACKAGE_ITEM						10				// 2008-08-26 by cmkwon, ItemAttribute 추가 - 패키지(Package) 아이템, 최대 개수 정의


#define MAX_PACKET_SIZE_FOR_XIGNCODE						512				// 2008-11-28 by cmkwon, 대만 Netpower_Tpe XignCode(게임가드) 적용 - 

#define SIZE_MAX_ADDRESS									128				// 2009-01-15 by cmkwon, PreServer, DBServer 정보 DNS로 설정 가능하게 수정 - 


// 2010-06-01 by shcho, GLogDB 관련 -
#define SIZE_MAX_GLOG_CHARACTER_RACE_NAME						32
#define SIZE_MAX_GLOG_CHARACTER_CLASS_NAME						32
#define SIZE_MAX_GLOG_EVENT_DESCRIPTION							512

// 2011-01-26 by hskim, 인증 서버 구현
#define SIZE_MAX_AUTH_GAMENAME					30
#define SIZE_MAX_AUTH_CURRENTVER				30
#define SIZE_MAX_AUTH_PUBLISHER					35
#define SIZE_MAX_AUTH_ACCEPT_COMMENT			254
#define SIZE_MAX_AUTH_RESOURCE_FILE_NAME		254

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// 2007-01-06 by cmkwon
#define AU_SERVER_TYPE_FTP				0
#define AU_SERVER_TYPE_HTTP				1






#define SIZE_STRING_32								32
#define SIZE_STRING_64								64
#define SIZE_STRING_128								128

enum EN_DAY_OF_WEEK
{
	DAY_OF_WEEK_SUMDAY = 0,			// 2006-08-24 by cmkwon, 일요일
	DAY_OF_WEEK_MONDAY = 1,			// 2006-08-24 by cmkwon, 월요일
	DAY_OF_WEEK_TUESDAY = 2,			// 2006-08-24 by cmkwon, 화요일
	DAY_OF_WEEK_WEDNESDAY = 3,			// 2006-08-24 by cmkwon, 수요일
	DAY_OF_WEEK_THURSDAY = 4,			// 2006-08-24 by cmkwon, 목요일
	DAY_OF_WEEK_FRIDAY = 5,			// 2006-08-24 by cmkwon, 금요일
	DAY_OF_WEEK_SATURDAY = 6,			// 2006-08-24 by cmkwon, 토요일
	DAY_OF_WEEK_HAPPYHOUREVENT_PERIOD = 7,			// 2006-08-24 by cmkwon, 해피아워 이벤트 기간 설정 - 비율 필드는 사용하지 않음
	DAY_OF_WEEK_PCBANG_HAPPYHOUREVENT = 8				// 2006-08-24 by cmkwon, PCBang 해피아워 이벤트 기간 및 비율 설정
};

#define ATUM_PRE_SERVER								0
#define ATUM_IM_SERVER								1
#define ATUM_LOG_SERVER								2
#define ATUM_MONITOR_SERVER							3
#define ATUM_FIELD_SERVER_1							6
#define ATUM_NPC_SERVER_1							7
#define ATUM_FIELD_SERVER_2							8
#define ATUM_NPC_SERVER_2							9
#define ATUM_FIELD_SERVER_3							10
#define ATUM_NPC_SERVER_3							11
#define ATUM_FIELD_SERVER_4							12
#define ATUM_NPC_SERVER_4							13
#define ATUM_FIELD_SERVER_5							14
#define ATUM_NPC_SERVER_5							15

// 특성치 값들
#define OT_ATTACK_TRAIT_DEFAULT_VALUE	0.05f
#define DT_DEFENSE_TRAIT_DEFAULT_VALUE	0.03f
#define BT_AVOID_TRAIT_DEFAULT_VALUE	1.0f

///////////////////////////////////////////////////////////////////////////////
//	ATUM - CHaracter, Monster, Item - Parameter 정의
///////////////////////////////////////////////////////////////////////////////

// 2005-06-23 by cmkwon
// 비트 플래그 설정 - 세력 타입으로 다음 중에 하나의 값을 가진다.
#define INFLUENCE_TYPE_UNKNOWN				(BYTE)0x0000	// 알수 없음
#define INFLUENCE_TYPE_NORMAL				(BYTE)0x0001	// 2005-12-20 by cmkwon, 바이제니유 일반군
#define INFLUENCE_TYPE_VCN					(BYTE)0x0002	// 2005-12-20 by cmkwon, 바이제니유 정규군, 이전(V.C.U: Vijuenill City United.)
#define INFLUENCE_TYPE_ANI					(BYTE)0x0004	// 2005-12-20 by cmkwon, 알링턴 정규군, 이전(반 민족주의 연합 -알링턴 시티 반란군- (A.N.I: Anti Nationalism Influence))
#define INFLUENCE_TYPE_RRP					(BYTE)0x0008	// 로베니아 혁명 연방 - 바탈러스 연방군- (R.R.P: Robenia Revolution Federation)
#define INFLUENCE_TYPE_ALL_MASK				(BYTE)0x00FF	// 모든 세력, 255
#define INFLUENCE_TYPE_COUNT				4				// 2006-04-17 by cmkwon, 세력의 개수(총 4개 - Normal, VCN, ANI, ALL)
#define INFLUENCE_TYPE_COUNT_EX_ALL			3				// 2009-09-16 by cmkwon, 세력 초기화시 어뷰징 방지 구현 - 세력의 개수(총 3개 - Normal, VCN, ANI)
#define COMPARE_INFLUENCE(VAR, MASK)		(((VAR) & (MASK)) != 0)

#define IS_NORMAL_INFLUENCE_TYPE(charInfl)	(COMPARE_INFLUENCE((charInfl), INFLUENCE_TYPE_NORMAL))		// 2007-05-22 by cmkwon, 추가함
#define IS_VCN_INFLUENCE_TYPE(charInfl)		(COMPARE_INFLUENCE((charInfl), INFLUENCE_TYPE_VCN))			// 2007-05-22 by cmkwon
#define IS_ANI_INFLUENCE_TYPE(charInfl)		(COMPARE_INFLUENCE((charInfl), INFLUENCE_TYPE_ANI))
#define IS_VALID_INFLUENCE_TYPE(charInfl)	(INFLUENCE_TYPE_NORMAL==(charInfl)|| INFLUENCE_TYPE_VCN==(charInfl)||INFLUENCE_TYPE_ANI==(charInfl))		// 2006-02-08 by cmkwon

// 2010-06-01 by shcho, GLogDB 관련 -
#define INFLUENCE_TYPE_ENG_NORMAL			"NORMAL_INFLUENCE"
#define INFLUENCE_TYPE_ENG_VCN				"VCN_INFLUENCE"
#define INFLUENCE_TYPE_ENG_ANI				"ANI_INFLUENCE"
#define INFLUENCE_TYPE_ENG_ALL_MASK			"ALL_INFLUENCE"

#define UNITKIND_ENG_BGEAR					"B-Gear"
#define UNITKIND_ENG_MGEAR					"M-Gear"
#define UNITKIND_ENG_AGEAR					"A-Gear"
#define UNITKIND_ENG_IGEAR					"I-Gear"
#define UNITKIND_ENG_UNKNOWN				"UNKNOWN_Gear"


// 2005-12-26 by cmkwon
// 비트 플래그 설정 아님 - ti_MapInfo테이블의 MapInfluenceType 필드 맵 세력 타입 설정
#define MAP_INFLUENCE_NEUTRALITY		(USHORT)0		// 중립 영역
#define MAP_INFLUENCE_VCN_CITY			(USHORT)1000	// 바이제니유 도시맵
#define MAP_INFLUENCE_VCN_START			(USHORT)1001	// 바이제니유 시작맵
#define MAP_INFLUENCE_VCN_LAST			(USHORT)1999	// 바이제니유 마지막맵
#define MAP_INFLUENCE_ANI_CITY			(USHORT)2000	// 알링턴 도시맵
#define MAP_INFLUENCE_ANI_START			(USHORT)2001	// 알링턴 시작맵
#define MAP_INFLUENCE_ANI_LAST			(USHORT)2999	// 알링턴 마지막맵
#define MAP_INFLUENCE_NORMAL_CITY		(USHORT)3000	// 2007-05-22 by cmkwon, 일반군도시맵
#define MAP_INFLUENCE_INFINITY			(USHORT)5000	// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 
#define MAP_INFLUENCE_INFINITY_LAST		(USHORT)5999	// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 
#define MAP_INFLUENCE_OUTPOST			(USHORT)6000	// 2007-08-17 by dhjin, 전진기지 도시 맵 
#define MAP_INFLUENCE_OUTPOST_START		(USHORT)6001	// 2007-08-17 by dhjin, 전진기지 맵 
#define MAP_INFLUENCE_OUTPOST_LAST		(USHORT)6999	// 2007-08-17 by dhjin, 전진기지 맵
#define MAP_INFLUENCE_ARENA				(USHORT)7000	// 2007-05-04 by dhjin, ARENA 맵
#define MAP_INFLUENCE_ARENA_LAST		(USHORT)7999	// 2007-05-04 by dhjin, ARENA 맵
#define MAP_INFLUENCE_EVENT_CITY		(USHORT)8000	// 이벤트 도시맵(의미없음)
#define MAP_INFLUENCE_EVENT_START		(USHORT)8001	// 이벤트 시작맵, 2006-07-18 by cmkwon
#define MAP_INFLUENCE_EVENT_LAST		(USHORT)8999	// 이벤트 마지막맵, 2006-07-18 by cmkwon
#define MAP_INFLUENCE_CONFLICT_AREA_CITY		(USHORT)9000	// 분쟁 지역 시작맵(의미없음), // 2006-02-09 by cmkwon
#define MAP_INFLUENCE_CONFLICT_AREA_START		(USHORT)9001	// 분쟁 지역 시작맵, // 2006-02-09 by cmkwon
#define MAP_INFLUENCE_CONFLICT_AREA_LAST		(USHORT)9999	// 분쟁 지역 마지막맵, // 2006-02-09 by cmkwon
#define IS_MAP_INFLUENCE_VCN(mapInfl)			( MAP_INFLUENCE_VCN_CITY <= (mapInfl) && MAP_INFLUENCE_VCN_LAST >= (mapInfl) )	// 바이제니유 세력 맵(1000 ~ 1999)인가?
#define IS_MAP_INFLUENCE_ANI(mapInfl)			( MAP_INFLUENCE_ANI_CITY <= (mapInfl) && MAP_INFLUENCE_ANI_LAST >= (mapInfl) )	// 알링턴 세력 맵(2000 ~ 2999)인가?
#define IS_MAP_INFLUENCE_NORMAL(mapInfl)		( MAP_INFLUENCE_NORMAL_CITY == (mapInfl) )	// 2007-05-22 by cmkwon, 일반군도시맵(3000)인가?
#define IS_MAP_INFLUENCE_CONFLICT_AREA(mapInfl)	( MAP_INFLUENCE_CONFLICT_AREA_CITY <= (mapInfl) && MAP_INFLUENCE_CONFLICT_AREA_LAST >= (mapInfl) )	// 분쟁 지역 맵(9000 ~ 9999)인가?
#define IS_MAP_INFLUENCE_EVENT_AREA(mapInfl)	( MAP_INFLUENCE_EVENT_CITY <= (mapInfl) && MAP_INFLUENCE_EVENT_LAST >= (mapInfl) )	// 이벤트맵(8000 ~ 8999)인가?
#define IS_MAP_INFLUENCE_ARENA(mapInfl)			( MAP_INFLUENCE_ARENA <= (mapInfl) && MAP_INFLUENCE_ARENA_LAST >= (mapInfl) )	// 아레나 맵(7000 ~ 7999)인가?
#define IS_MAP_INFLUENCE_OUTPOST(mapInfl)		( MAP_INFLUENCE_OUTPOST_START <= (mapInfl) && MAP_INFLUENCE_OUTPOST_LAST >= (mapInfl) )	// 전진기지 맵(6000 ~ 6999)인가?
#define IS_MAP_INFLUENCE_INFINITY(mapInfl)		( MAP_INFLUENCE_INFINITY <= (mapInfl) && MAP_INFLUENCE_INFINITY_LAST >= (mapInfl) )	// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 

// 2009-10-12 by cmkwon, 프리스카 제거 방안 적용 - CAtumSJ::IsSameCharacterInfluence8MapInfluence#로 대체
// // 2007-05-22 by cmkwon, 일반군 도시맵 추가
// #define IS_SAME_CHARACTER_8_MAP_INFLUENCE(charInfl, mapInfl)	(  ( COMPARE_INFLUENCE((charInfl), INFLUENCE_TYPE_NORMAL) && IS_MAP_INFLUENCE_NORMAL(mapInfl) ) \
// 																|| ( COMPARE_INFLUENCE((charInfl), INFLUENCE_TYPE_VCN) && IS_MAP_INFLUENCE_VCN(mapInfl) ) \
//																|| ( COMPARE_INFLUENCE((charInfl), INFLUENCE_TYPE_ANI) && IS_MAP_INFLUENCE_ANI(mapInfl) )  )

// 2007-05-22 by cmkwon, 아래 #define으로 변경 처리함
//#define IS_OTHER_INFLUENCE_CITY(charInfl, mapInfl)	( (COMPARE_INFLUENCE(charInfl, INFLUENCE_TYPE_NORMAL|INFLUENCE_TYPE_VCN) && MAP_INFLUENCE_ANI_CITY == mapInfl) \
//																|| (COMPARE_INFLUENCE(charInfl, INFLUENCE_TYPE_ANI) && MAP_INFLUENCE_VCN_CITY == mapInfl) )
#define IS_MAP_INFLUENCE_CITY(mapInfl)				( MAP_INFLUENCE_VCN_CITY == (mapInfl) || MAP_INFLUENCE_ANI_CITY == (mapInfl) || MAP_INFLUENCE_NORMAL_CITY == (mapInfl))

// 2009-10-12 by cmkwon, 프리스카 제거 방안 적용 - CAtumSJ::IsOtherInfluenceMap#으로 대체함
//#define IS_OTHER_INFLUENCE_MAP(charInfl, mapInfl)	( (COMPARE_INFLUENCE(charInfl, INFLUENCE_TYPE_NORMAL|INFLUENCE_TYPE_VCN) && IS_MAP_INFLUENCE_ANI(mapInfl)) \
//																|| (COMPARE_INFLUENCE(charInfl, INFLUENCE_TYPE_ANI) && IS_MAP_INFLUENCE_VCN(mapInfl)) )

// 2008-12-23 by dhjin, 전쟁 보상 추가안
#define IS_MAP_INFLUENCE_WAR(mapInfl)				( IS_MAP_INFLUENCE_VCN(mapInfl) || IS_MAP_INFLUENCE_ANI(mapInfl) || IS_MAP_INFLUENCE_OUTPOST(mapInfl))

// check: 만약 첫 bit을 사용하게 된다면, 각종 DB schema의 Race의 type을 int로 변경해야 함.
#define RACE_BATTALUS				(USHORT)0x0001	// 바탈러스, 1
#define RACE_DECA					(USHORT)0x0002	// 데카, 2
#define RACE_PHILON					(USHORT)0x0004	// 필론, 4
#define RACE_SHARRINE				(USHORT)0x0008	// 샤린, 8
#define RACE_INFLUENCE_LEADER		(USHORT)0x0010	// 16, 세력전 리더, 2006-04-20 by cmkwon, RACE_MONSTER1(예비, 16)를 변경한 것임
// 2007-10-06 by cmkwon, 부지도자 2명의 호칭을 다르게 설정 - 정의 수정, 아래ㅇ와 같이 수정
//#define RACE_INFLUENCE_SUBLEADER	(USHORT)0x0020	// 32, 세력전 부지도자, 2006-12-08 by cmkwon, RACE_MONSTER2(예비, 32)를 변경한 것임 예비, 32
//#define RACE_NPC					(USHORT)0x0040	// NPC, 64
#define RACE_INFLUENCE_SUBLEADER_1	(USHORT)0x0020	// 32, 세력전 부지도자 1 - VCN(부사령관), ANI(부의장), // 2007-10-06 by cmkwon, 부지도자 2명의 호칭을 다르게 설정 -
#define RACE_INFLUENCE_SUBLEADER_2	(USHORT)0x0040	// 64, 세력전 부지도자 2 - VCN(참모총장), ANI(작전본부장), // 2007-10-06 by cmkwon, 부지도자 2명의 호칭을 다르게 설정 -
#define RACE_OPERATION				(USHORT)0x0080	// 관리자, 128
#define RACE_GAMEMASTER				(USHORT)0x0100	// 게임마스터, 256
#define RACE_MONITOR				(USHORT)0x0200	// 모니터, 512
#define RACE_GUEST					(USHORT)0x0400	// 게스트, 1024
#define RACE_DEMO					(USHORT)0x0800	// 시연(데모)용, 2048
#define RACE_DELETED_CHARACTER		(USHORT)0x4000	// 삭제된 캐릭터, 16384 // 2007-02-21 by cmkwon
#define RACE_ALL					(USHORT)0x000F	// 모든 종족, (RACE_BATTALUS|RACE_DECA|RACE_PHILON|RACE_SHARRINE), 15
#define RACE_ACCOUNT_TYPE_MASK		(RACE_OPERATION|RACE_GAMEMASTER|RACE_MONITOR|RACE_GUEST|RACE_DEMO)
#define RACE_INFLUENCE_SUBLEADER_MASK	(RACE_INFLUENCE_SUBLEADER_1|RACE_INFLUENCE_SUBLEADER_2)		// 2007-10-06 by cmkwon, 부지도자 2명의 호칭을 다르게 설정 - 정의 추가
#define COMPARE_RACE(VAR, MASK)		(((VAR) & (MASK)) != 0)
/* - 계정 관련 권한 -
			접속자수확인	몬스터소환	멥이동	이동/호출	아이템생성	아이템사용	전체메시지	스텔스	PK 여부
관리자		가능			가능		가능	가능		가능		모두가능	가능		가능	가능
게임마스터	가능			가능		가능	가능		불가		모두가능	가능		가능	가능
모니터		가능			불가		가능	이동만가능	불가		불가		불가		기본	불가
게스트		불가			불가		불가	불가		불가		레벨30고정	불가		불가	불가
데모		불가			불가		가능	불가		불가		레벨50고정	불가		가능	가능
일반		일반			일반		일반	일반		일반		일반		일반		일반	일반
*/


////////////////////////////////////
// 캐릭터 유닛의 종류
#define UNITKIND_BT01				(USHORT)0x0001	// BT - 01형, B-GEAR, 1
#define UNITKIND_BT02				(USHORT)0x0002	// BT - 02형, B-GEAR, 2
#define UNITKIND_BT03				(USHORT)0x0004	// BT - 03형, B-GEAR, 4
#define UNITKIND_BT04				(USHORT)0x0008	// BT - 04형, B-GEAR, 8

#define UNITKIND_OT01				(USHORT)0x0010	// OT - 01형, M-GEAR, 16
#define UNITKIND_OT02				(USHORT)0x0020	// OT - 02형, M-GEAR, 32
#define UNITKIND_OT03				(USHORT)0x0040	// OT - 03형, M-GEAR, 64
#define UNITKIND_OT04				(USHORT)0x0080	// OT - 04형, M-GEAR, 128

#define UNITKIND_DT01				(USHORT)0x0100	// DT - 01형, A-GEAR, 256
#define UNITKIND_DT02				(USHORT)0x0200	// DT - 02형, A-GEAR, 512
#define UNITKIND_DT03				(USHORT)0x0400	// DT - 03형, A-GEAR, 1024
#define UNITKIND_DT04				(USHORT)0x0800	// DT - 04형, A-GEAR, 2048

#define UNITKIND_ST01				(USHORT)0x1000	// ST - 01형, I-GEAR, 4096
#define UNITKIND_ST02				(USHORT)0x2000	// ST - 02형, I-GEAR, 8192
#define UNITKIND_ST03				(USHORT)0x4000	// ST - 03형, I-GEAR, 16384
#define UNITKIND_ST04				(USHORT)0x8000	// ST - 04형, I-GEAR, 32768

#define UNITKIND_BGEAR_MASK			(USHORT)0x000F	// B-GEAR, 15
#define UNITKIND_MGEAR_MASK			(USHORT)0x00F0	// M-GEAR, 240
#define UNITKIND_AGEAR_MASK			(USHORT)0x0F00	// A-GEAR, 3840
#define UNITKIND_IGEAR_MASK			(USHORT)0xF000	// I-GEAR, 61440
#define UNITKIND_ALL_MASK			(USHORT)0xFFFF	// 65535

#define IS_BT(x) ((x&UNITKIND_BGEAR_MASK) != 0)	// B-GEAR
#define IS_OT(x) ((x&UNITKIND_MGEAR_MASK) != 0)	// M-GEAR
#define IS_DT(x) ((x&UNITKIND_AGEAR_MASK) != 0)	// A-GEAR
#define IS_ST(x) ((x&UNITKIND_IGEAR_MASK) != 0)	// I-GEAR

#define UNITKIND_BGEAR		((USHORT)0x0001)	// B-GEAR, 1
#define UNITKIND_MGEAR		((USHORT)0x0010)	// M-GEAR, 16
#define UNITKIND_AGEAR		((USHORT)0x0100)	// A-GEAR, 256
#define UNITKIND_IGEAR		((USHORT)0x1000)	// I-GEAR, 4096

#define IS_BGEAR(x) ((x&UNITKIND_BGEAR_MASK) != 0)	// B-GEAR
#define IS_MGEAR(x) ((x&UNITKIND_MGEAR_MASK) != 0)	// M-GEAR
#define IS_AGEAR(x) ((x&UNITKIND_AGEAR_MASK) != 0)	// A-GEAR
#define IS_IGEAR(x) ((x&UNITKIND_IGEAR_MASK) != 0)	// I-GEAR
#define IS_SAME_UNITKIND(x1, x2) ( (IS_BGEAR(x1)&&IS_BGEAR(x2))	 ||	\
									(IS_MGEAR(x1)&&IS_MGEAR(x2)) ||	\
									(IS_AGEAR(x1)&&IS_AGEAR(x2)) ||	\
									(IS_IGEAR(x1)&&IS_IGEAR(x2)) )

////////////////////////////////////
// 캐릭터 신분, STATUS_XXX
#define STATUS_BEGINNER_AIRMAN		((BYTE)0)	// 훈련 에어맨, 1 ~ 100	
#define STATUS_3RD_CLASS_AIRMAN		((BYTE)1)	// 3rd 에어맨, 101 ~ 300, 미션으로 승급 가능
#define STATUS_2ND_CLASS_AIRMAN		((BYTE)2)	// 2nd 에어맨, 301 ~ 600, 미션으로 승급 가능
#define STATUS_1ST_CLASS_AIRMAN		((BYTE)3)	// 1st 에어맨, 601 ~ 1000, 미션으로 승급 가능
#define STATUS_3RD_CLASS_WINGMAN	((BYTE)4)	// 3rd 윙맨, 1001 ~ 1500, 미션으로 승급 가능
#define STATUS_2ND_CLASS_WINGMAN	((BYTE)5)	// 2nd 윙맨, 1501 ~ 2000, 미션으로 승급 가능
#define STATUS_1ST_CLASS_WINGMAN	((BYTE)6)	// 1st 윙맨, 2001 ~ 2500, 미션으로 승급 가능
#define STATUS_3RD_CLASS_LEADER		((BYTE)7)	// 3rd 리더, 2501 ~ 5000, 여단 설립
#define STATUS_2ND_CLASS_LEADER		((BYTE)8)	// 2nd 리더, 5000 ~ 10000, 여단 설립 후 1단계 여단 미션 클리어 시 (5명 추가 인원 확장), 해체 시 레벨에 따른 습득 계급으로 변경
#define STATUS_1ST_CLASS_LEADER		((BYTE)9)	// 1st 리더, 10001 ~ 15000, 여단 설립 후 2단계 여단 미션 클리어 시 (5명 추가 인원 확장 및 여단 마크 장착 가능), 해체 시 레벨에 따른 습득 계급으로 변경
#define STATUS_3RD_CLASS_ACE		((BYTE)10)	// 3rd 에이스, 15001 ~ 20000, 여단 설립 후 3단계 여단 미션 클리어 시 (5명 추가 인원 확장 및 여단 창고 공유 가능), 해체 시 레벨에 따른 습득 계급으로 변경
#define STATUS_2ND_CLASS_ACE		((BYTE)11)	// 2nd 에이스, 20000 ~ 25000, 여단 설립 후 4단계 여단 미션 클리어 시 (5명 추가 인원 확장 및 도시전투 신청 가능), 해체 시 레벨에 따른 습득 계급으로 변경
#define STATUS_1ST_CLASS_ACE		((BYTE)12)	// 1st 에이스, 25001 ~ 30000, 여단 설립 후 5단계 여단 미션 클리어 시 (10명 추가 인원 확장), 해체 시 레벨에 따른 습득 계급으로 변경
#define STATUS_COPPER_CLASS_GENERAL	((BYTE)13)	// 준장성, -, 여단 설립 후 계급 승진 미션 클리어 시 (10명 추가 인원 확장), 해체 시 레벨에 따른 습득 계급으로 변경
#define STATUS_SILVER_CLASS_GENERAL	((BYTE)14)	// 소장성, -, 1개의 도시에 대한 점령권 소유 , 소유 후 실패 시 레벨에 따른 습득 계급으로 변경
#define STATUS_GOLD_CLASS_GENERAL	((BYTE)15)	// 중장성, -, 2개의 도시에 대한 점령권 소유, 소유 후 실패 시 레벨에 따른 습득 계급으로 변경
#define STATUS_MASTER_GENERAL		((BYTE)16)	// 대장성, -, 대륙 내 전 도시에 대한 점령권 소유, 소유 후 실패 시 레벨에 따른 습득 계급으로 변경

////////////////////////////////////
// 캐릭터 & 몬스터의 상태
typedef UINT64 BodyCond_t;

#define NUM_OF_BODYCONDITION_BIT		64

// Body Conditions
#define BODYCON_SET_OR_CLEAR_MASK		(BodyCond_t)0x0000000000000001		// set(1) or clear(0)
// start - exclusive condition
#define BODYCON_FLY_MASK				(BodyCond_t)0x0000000000000002		// 비행
#define BODYCON_LANDING_MASK			(BodyCond_t)0x0000000000000040		// 착륙중, exclusive해야 한다고 요청됨, by kelovon w/ jinkin, 20040203
#define BODYCON_LANDED_MASK				(BodyCond_t)0x0000000000000004		// 착륙 완료
#define BODYCON_DEAD_MASK				(BodyCond_t)0x0000000000000008		// 폭발
#define BODYCON_NOT_USED1_MASK			(BodyCond_t)0x0000000000000010
// end - exclusive condition
// start - new bodycon
#define BODYCON_WEAPON_POSITION_MASK	(BodyCond_t)0x0000000000000020		// 2005-12-16 by cmkwon, 1형/2형 무기 포지션을 위한 바디컨디션, BODYCON_NOT_USED2_MASK를 변경함
#define BODYCON_BOOSTER1_MASK			(BodyCond_t)0x0000000000000080		// 부스터(1~10) - 평상시(가만히 있을 때)
#define BODYCON_BOOSTER2_MASK			(BodyCond_t)0x0000000000000100		// 부스터(10~15) - 전진시(W키를 누른 상태)
#define BODYCON_BOOSTER3_MASK			(BodyCond_t)0x0000000000000200		// 부스터(70~80) - 부스터시(Space키를 누른 상태)
#define BODYCON_BOOSTER4_MASK			(BodyCond_t)0x0000000000000400		// 부스터(81~100) - 정지시(S키를 누른 상태)
#define BODYCON_NIGHTFLY_MASK			(BodyCond_t)0x0000000000000800		// 야간비행(야간등)
#define BODYCON_EXPLOSION_MASK			(BodyCond_t)0x0000000000001000		// 폭발
#define BODYCON_DAMAGE1_MASK			(BodyCond_t)0x0000000000002000		// 데미지1, 지속형
#define BODYCON_DAMAGE2_MASK			(BodyCond_t)0x0000000000004000		// 데미지2, 지속형
#define BODYCON_DAMAGE3_MASK			(BodyCond_t)0x0000000000008000		// 데미지3, 지속형
#define BODYCON_CREATION_MASK			(BodyCond_t)0x0000000000010000		// 리스폰
#define BODYCON_FIRE_MASK				(BodyCond_t)0x0000000000020000		// 발사
#define BODYCON_BULLET_MASK				(BodyCond_t)0x0000000000040000		// 탄체
#define BODYCON_HIT_MASK				(BodyCond_t)0x0000000000080000		// 타격


///////////////////////////////////////////////////////////////////////////////
// 클라이언트에서만 사용되는 BodyCondition
// 레이다 바디 컨디션 설정
#define RADAR_BODYCON_BOOSTER_ON		(BodyCond_t)0x0000000000000008		// 켜진 상태
#define RADAR_BODYCON_BOOSTER_OFF		(BodyCond_t)0x0000000000000002		// 꺼진 상태

// cmkwon, 여기부터는 캐릭과 몬스터가 다르게 사용함

///////////////////////////////////////////////////////////////////////////////
// Strat --> Character BodyCondition, BODYCON_XXX
#define BODYCON_SPRAY_MASK					(BodyCond_t)0x0000000000100000		// 물보라,먼지,눈
#define BODYCON_APRE_MASK					(BodyCond_t)0x0000000000200000		// 2005-12-07 by cmkwon, A기어 포 지지대 Bodycondition
// end - new bodycon
#define BODYCON_SHAKEING_MASK				(BodyCond_t)0x0000000004000000		// 흔들림
#define BODYCON_FREEZING_MASK				(BodyCond_t)0x0000000008000000		// 동결
#define BODYCON_ATTACKSLOW_MASK				(BodyCond_t)0x0000000010000000		// 재공격 느려짐
#define BODYCON_SLOW_MASK					(BodyCond_t)0x0000000020000000		// 스피드 느려짐
#define BODYCON_NOATTACK_MASK				(BodyCond_t)0x0000000040000000		// 공격금지
#define BODYCON_ILLUSION_MASK				(BodyCond_t)0x0000000080000000		// 착각
#define BODYCON_FIGHTING_MASK				(BodyCond_t)0x0000000100000000		// 사기고양
#define BODYCON_EVENT_HANDLE_MASK			(BodyCond_t)0x0000000200000000		// 이벤트(워프, 상점) 처리중, 서버는 client의 이동 정보 무시
#define BODYCON_STOP_MASK					(BodyCond_t)0x0000000400000000		// 2010-03-30 by cmkwon, 필드창고 비행중 이용 버그 수정(E0044710) - 기어상태 일때 B+Enter 상태, // 정지상태	------> 여기 이하는 2002.11.25.에 추가
#define BODYCON_STEALTH_MASK				(BodyCond_t)0x0000000800000000		// 스텔스상태
#define BODYCON_GHOST_MASK					(BodyCond_t)0x0000001000000000		// 고스트상태
#define BODYCON_CLOAKING_MASK				(BodyCond_t)0x0000002000000000		// 클로킹상태
#define BODYCON_FALL_MASK					(BodyCond_t)0x0000004000000000		// 추락상태
#define BODYCON_SKILLBAN_MASK				(BodyCond_t)0x0000008000000000		// 스킬사용금지상태
#define BODYCON_RESIST_MASK					(BodyCond_t)0x0000010000000000		// 스킬저항상태
#define BODYCON_SHIELD_MASK					(BodyCond_t)0x0000020000000000		// 쉴드 상태, 20030917에 추가
#define BODYCON_BOOSTER5_MASK				(BodyCond_t)0x0000040000000000		// 역축진 부스터
#define BODYCON_TAKEOFF_MASK				(BodyCond_t)0x0000080000000000		// 이륙
#define BODYCON_SIEGE_ON_MASK				(BodyCond_t)0x0000100000000000		// 시즈 모드 온
#define BODYCON_SIEGE_OFF_MASK				(BodyCond_t)0x0000200000000000		// 시즈 모드 오프
#define BODYCON_DECOY_MASK					(BodyCond_t)0x0000400000000000		// 디코이 상태
#define BODYCON_CHARACTER_MODE_STOP			(BodyCond_t)0x0001000000000000		// 캐릭터 모드 - 멈춤
#define BODYCON_CHARACTER_MODE_WALK			(BodyCond_t)0x0002000000000000		// 캐릭터 모드 - 걷기
#define BODYCON_CHARACTER_MODE_RUN			(BodyCond_t)0x0004000000000000		// 캐릭터 모드 - 뛰기
#define BODYCON_EVENT_SELECTCHANNEL_MASK	(BodyCond_t)0x0008000000000000		// 채널 선택 창 상태, BODYCON_EVENT_HANDLE_MASK와 같이 쓰인다
#define BODYCON_ROLLING_MASK				(BodyCond_t)0x0010000000000000		// 2009-07-07 by cmkwon, 로봇 아머 관련 처리 추가 - 롤링 바디컨디션 추가
#define BODYCON_PET_POSITION_MASK			(BodyCond_t)0x0020000000000000		// 2010-06-15 by shcho&hslee 펫시스템 팩 장착 위치 BodyCon 추가
#define BODYCON_MARK_POSITION_MASK			(BodyCond_t)0x0040000000000000		// 2011-03-21 by jhAhn	마크시스템 창착위치 BodyCon 추가
// End --> Character BodyCondition
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Start --> Monster BodyCondition
#define COUNT_MONSTER_ATTACK_BODYCON	2		// 하나의 Attack당 가지는 상태의 숫자(PreAttack, FireAttack)

#define BODYCON_MON_PREATTACK1_MASK		(BodyCond_t)0x0000000000100000		// 공격1의 준비			(Effect = 20)
#define BODYCON_MON_FIREATTACK1_MASK	(BodyCond_t)0x0000000000200000		// 공격1의 발사			(Effect = 21)

#define BODYCON_MON_PREATTACK2_MASK		(BodyCond_t)0x0000000000400000		// 공격2의 준비			(Effect = 22)
#define BODYCON_MON_FIREATTACK2_MASK	(BodyCond_t)0x0000000000800000		// 공격2의 발사			(Effect = 23)

#define BODYCON_MON_PREATTACK3_MASK		(BodyCond_t)0x0000000001000000		// 공격3의 준비			(Effect = 24)
#define BODYCON_MON_FIREATTACK3_MASK	(BodyCond_t)0x0000000002000000		// 공격3의 발사			(Effect = 25)

#define BODYCON_MON_PREATTACK4_MASK		(BodyCond_t)0x0000000004000000		// 공격4의 준비			(Effect = 26)
#define BODYCON_MON_FIREATTACK4_MASK	(BodyCond_t)0x0000000008000000		// 공격4의 발사			(Effect = 27)

#define BODYCON_MON_PREATTACK5_MASK		(BodyCond_t)0x0000000010000000		// 공격5의 준비			(Effect = 28)
#define BODYCON_MON_FIREATTACK5_MASK	(BodyCond_t)0x0000000020000000		// 공격5의 발사			(Effect = 29)

////////////////////////////////////////////////////////////////////////////////
// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 컨트롤스킬로 이름 변경
//#define BODYCON_MON_PREATTACK6_MASK		(BodyCond_t)0x0000000040000000		// 공격6의 발사			(Effect = 30)
//#define BODYCON_MON_FIREATTACK6_MASK	(BodyCond_t)0x0000000080000000		// 공격6의 완료			(Effect = 31)
#define BODYCON_MON_PRECONTROLSKILL_MASK	(BodyCond_t)0x0000000040000000		// 컨트롤스킬의 발사			(Effect = 30)
#define BODYCON_MON_FIRECONTROLSKILL_MASK	(BodyCond_t)0x0000000080000000		// 컨트롤스킬의 완료			(Effect = 31)

#define BODYCON_MON_AUTODESTROYED_MASK	(BodyCond_t)0x0000000100000000		// 몬스터 자동 소멸		(Effect = 32)
#define BODYCON_MON_BUILDING			(BodyCond_t)0x0000001000000000		// 2007-09-06 by cmkwon, 몬스터 변신중			(Effect = 36)
#define BODYCON_MON_BUILDED				(BodyCond_t)0x0000002000000000		// 2007-09-06 by cmkwon, 몬스터 변신완료		(Effect = 37)
////////////////////////////////////////////////////////////////////////////////
// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 6~15까지 추가
#define BODYCON_MON_PREATTACK6_MASK		(BodyCond_t)0x0000010000000000		// 공격6의 준비			(Effect = 40)
#define BODYCON_MON_FIREATTACK6_MASK	(BodyCond_t)0x0000020000000000		// 공격6의 발사			(Effect = 41)
#define BODYCON_MON_PREATTACK7_MASK		(BodyCond_t)0x0000040000000000		// 공격7의 준비			(Effect = 42)
#define BODYCON_MON_FIREATTACK7_MASK	(BodyCond_t)0x0000080000000000		// 공격7의 발사			(Effect = 43)
#define BODYCON_MON_PREATTACK8_MASK		(BodyCond_t)0x0000100000000000		// 공격8의 준비			(Effect = 44)
#define BODYCON_MON_FIREATTACK8_MASK	(BodyCond_t)0x0000200000000000		// 공격8의 발사			(Effect = 45)
#define BODYCON_MON_PREATTACK9_MASK		(BodyCond_t)0x0000400000000000		// 공격9의 준비			(Effect = 46)
#define BODYCON_MON_FIREATTACK9_MASK	(BodyCond_t)0x0000800000000000		// 공격9의 발사			(Effect = 47)
#define BODYCON_MON_PREATTACK10_MASK	(BodyCond_t)0x0001000000000000		// 공격10의 준비			(Effect = 48)
#define BODYCON_MON_FIREATTACK10_MASK	(BodyCond_t)0x0002000000000000		// 공격10의 발사			(Effect = 49)
#define BODYCON_MON_PREATTACK11_MASK	(BodyCond_t)0x0004000000000000		// 공격11의 준비			(Effect = 50)
#define BODYCON_MON_FIREATTACK11_MASK	(BodyCond_t)0x0008000000000000		// 공격11의 발사			(Effect = 51)
#define BODYCON_MON_PREATTACK12_MASK	(BodyCond_t)0x0010000000000000		// 공격12의 준비			(Effect = 52)
#define BODYCON_MON_FIREATTACK12_MASK	(BodyCond_t)0x0020000000000000		// 공격12의 발사			(Effect = 53)
#define BODYCON_MON_PREATTACK13_MASK	(BodyCond_t)0x0040000000000000		// 공격13의 준비			(Effect = 54)
#define BODYCON_MON_FIREATTACK13_MASK	(BodyCond_t)0x0080000000000000		// 공격13의 발사			(Effect = 55)
#define BODYCON_MON_PREATTACK14_MASK	(BodyCond_t)0x0100000000000000		// 공격14의 준비			(Effect = 56)
#define BODYCON_MON_FIREATTACK14_MASK	(BodyCond_t)0x0200000000000000		// 공격14의 발사			(Effect = 57)
#define BODYCON_MON_PREATTACK15_MASK	(BodyCond_t)0x0400000000000000		// 공격15의 준비			(Effect = 58)
#define BODYCON_MON_FIREATTACK15_MASK	(BodyCond_t)0x0800000000000000		// 공격15의 발사			(Effect = 59)

////////////////////////////////////////////////////////////////////////////////
// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 6~15, 컨트롤스킬까지 추가
#define BODYCON_MON_ATTACK1_MASK		(BodyCond_t)(BODYCON_MON_PREATTACK1_MASK | BODYCON_MON_FIREATTACK1_MASK)	// 공격1
#define BODYCON_MON_ATTACK2_MASK		(BodyCond_t)(BODYCON_MON_PREATTACK2_MASK | BODYCON_MON_FIREATTACK2_MASK)	// 공격2
#define BODYCON_MON_ATTACK3_MASK		(BodyCond_t)(BODYCON_MON_PREATTACK3_MASK | BODYCON_MON_FIREATTACK3_MASK)	// 공격3
#define BODYCON_MON_ATTACK4_MASK		(BodyCond_t)(BODYCON_MON_PREATTACK4_MASK | BODYCON_MON_FIREATTACK4_MASK)	// 공격4
#define BODYCON_MON_ATTACK5_MASK		(BodyCond_t)(BODYCON_MON_PREATTACK5_MASK | BODYCON_MON_FIREATTACK5_MASK)	// 공격5
#define BODYCON_MON_ATTACK6_MASK		(BodyCond_t)(BODYCON_MON_PREATTACK6_MASK | BODYCON_MON_FIREATTACK6_MASK)	// 공격6
#define BODYCON_MON_ATTACK7_MASK		(BodyCond_t)(BODYCON_MON_PREATTACK7_MASK | BODYCON_MON_FIREATTACK7_MASK)	// 공격7
#define BODYCON_MON_ATTACK8_MASK		(BodyCond_t)(BODYCON_MON_PREATTACK8_MASK | BODYCON_MON_FIREATTACK8_MASK)	// 공격8
#define BODYCON_MON_ATTACK9_MASK		(BodyCond_t)(BODYCON_MON_PREATTACK9_MASK | BODYCON_MON_FIREATTACK9_MASK)	// 공격9
#define BODYCON_MON_ATTACK10_MASK		(BodyCond_t)(BODYCON_MON_PREATTACK10_MASK | BODYCON_MON_FIREATTACK10_MASK)	// 공격10
#define BODYCON_MON_ATTACK11_MASK		(BodyCond_t)(BODYCON_MON_PREATTACK11_MASK | BODYCON_MON_FIREATTACK11_MASK)	// 공격11
#define BODYCON_MON_ATTACK12_MASK		(BodyCond_t)(BODYCON_MON_PREATTACK12_MASK | BODYCON_MON_FIREATTACK12_MASK)	// 공격12
#define BODYCON_MON_ATTACK13_MASK		(BodyCond_t)(BODYCON_MON_PREATTACK13_MASK | BODYCON_MON_FIREATTACK13_MASK)	// 공격13
#define BODYCON_MON_ATTACK14_MASK		(BodyCond_t)(BODYCON_MON_PREATTACK14_MASK | BODYCON_MON_FIREATTACK14_MASK)	// 공격14
#define BODYCON_MON_ATTACK15_MASK		(BodyCond_t)(BODYCON_MON_PREATTACK15_MASK | BODYCON_MON_FIREATTACK15_MASK)	// 공격15
#define BODYCON_MON_CONTROLSKILL_MASK	(BodyCond_t)(BODYCON_MON_PRECONTROLSKILL_MASK | BODYCON_MON_FIRECONTROLSKILL_MASK)	// 컨트롤스킬
#define BODYCON_MON_PREATTACK_ALL_MASK	(BodyCond_t)(BODYCON_MON_PREATTACK1_MASK | BODYCON_MON_PREATTACK2_MASK \
													| BODYCON_MON_PREATTACK3_MASK | BODYCON_MON_PREATTACK4_MASK \
													| BODYCON_MON_PREATTACK5_MASK | BODYCON_MON_PREATTACK6_MASK \
													| BODYCON_MON_PREATTACK7_MASK | BODYCON_MON_PREATTACK8_MASK \
													| BODYCON_MON_PREATTACK9_MASK | BODYCON_MON_PREATTACK10_MASK \
													| BODYCON_MON_PREATTACK11_MASK | BODYCON_MON_PREATTACK12_MASK \
													| BODYCON_MON_PREATTACK13_MASK | BODYCON_MON_PREATTACK14_MASK \
													| BODYCON_MON_PREATTACK15_MASK | BODYCON_MON_PRECONTROLSKILL_MASK)	// 모든 공격 준비
#define BODYCON_MON_FIREATTACK_ALL_MASK	(BodyCond_t)(BODYCON_MON_FIREATTACK1_MASK | BODYCON_MON_FIREATTACK2_MASK \
													| BODYCON_MON_FIREATTACK3_MASK | BODYCON_MON_FIREATTACK4_MASK \
													| BODYCON_MON_FIREATTACK5_MASK | BODYCON_MON_FIREATTACK6_MASK \
													| BODYCON_MON_FIREATTACK7_MASK | BODYCON_MON_FIREATTACK8_MASK \
													| BODYCON_MON_FIREATTACK9_MASK | BODYCON_MON_FIREATTACK10_MASK \
													| BODYCON_MON_FIREATTACK11_MASK | BODYCON_MON_FIREATTACK12_MASK \
													| BODYCON_MON_FIREATTACK13_MASK | BODYCON_MON_FIREATTACK14_MASK \
													| BODYCON_MON_FIREATTACK15_MASK | BODYCON_MON_FIRECONTROLSKILL_MASK)	// 모든 공격 준비
#define BODYCON_MON_ATTACKALL_MASK		(BodyCond_t)(BODYCON_MON_ATTACK1_MASK | BODYCON_MON_ATTACK2_MASK \
													| BODYCON_MON_ATTACK3_MASK | BODYCON_MON_ATTACK4_MASK \
													| BODYCON_MON_ATTACK5_MASK | BODYCON_MON_ATTACK6_MASK \
													| BODYCON_MON_ATTACK7_MASK | BODYCON_MON_ATTACK8_MASK \
													| BODYCON_MON_ATTACK9_MASK | BODYCON_MON_ATTACK10_MASK \
													| BODYCON_MON_ATTACK11_MASK | BODYCON_MON_ATTACK12_MASK \
													| BODYCON_MON_ATTACK13_MASK | BODYCON_MON_ATTACK14_MASK \
													| BODYCON_MON_ATTACK15_MASK | BODYCON_MON_CONTROLSKILL_MASK)		// 몬스터 공격 관련 BodyCondition을 Clear하기 위한 define

// End --> Monster BodyCondition
///////////////////////////////////////////////////////////////////////////////

// bit 연산 매크로
#define CLEAR_BODYCON_BIT(VAR, MASK) { VAR &= ~(MASK); }
#define SET_BODYCON_BIT(VAR, MASK)								\
{																\
	if ((MASK & BODYCON_EX_STATE_CLEAR_MASK) != 0)				\
	{															\
		CLEAR_BODYCON_BIT(VAR, BODYCON_EX_STATE_CLEAR_MASK);	\
	}															\
	if ((MASK & BODYCON_BOOSTER_EX_STATE_CLEAR_MASK) != 0)		\
	{															\
		CLEAR_BODYCON_BIT(VAR, BODYCON_BOOSTER_EX_STATE_CLEAR_MASK);\
	}															\
	VAR |= MASK;												\
}
#define COMPARE_BODYCON_BIT(VAR, MASK) (((VAR) & (MASK)) != 0)
#define BODYCON_EX_STATE_CLEAR_MASK		(BodyCond_t)(BODYCON_FLY_MASK | BODYCON_LANDING_MASK | BODYCON_LANDED_MASK | BODYCON_DEAD_MASK | BODYCON_NOT_USED1_MASK | BODYCON_CHARACTER_MODE_STOP | BODYCON_CHARACTER_MODE_WALK | BODYCON_CHARACTER_MODE_RUN)
										// BODYCON_FLY_MASK | BODYCON_LANDED_MASK | BODYCON_LANDING_MASK | BODYCON_DEAD_MASK | BODYCON_NOT_USED_MASK
										// 위의 네가지 bit을 set할때는 항상 이 mask로 clear해주어야 함
										// 네 state가 exclusive하기 때문이다
										//
										// ex)
										// CLEAR_BODYCON_BIT( c, BODYCON_EX_STATE_CLEAR_MASK)
										// SET_BODYCON_BIT( c, BODYCON_FLY_MASK)
#define BODYCON_BOOSTER_EX_STATE_CLEAR_MASK	(BodyCond_t)(BODYCON_BOOSTER1_MASK | BODYCON_BOOSTER2_MASK | BODYCON_BOOSTER3_MASK | BODYCON_BOOSTER4_MASK \
											| BODYCON_BOOSTER5_MASK | BODYCON_SIEGE_ON_MASK | BODYCON_SIEGE_OFF_MASK)
											// BODYCON_BOOSTER1_MASK | BODYCON_BOOSTER2_MASK | BODYCON_BOOSTER3_MASK | BODYCON_BOOSTER4_MASK
#define BODYCON_KEEPING_MASK			(BodyCond_t)(BODYCON_EX_STATE_CLEAR_MASK)	// 지속형 body coditions
#define BODYCON_CHARACTER_MODE_MASK		(BodyCond_t)(BODYCON_CHARACTER_MODE_STOP|BODYCON_CHARACTER_MODE_WALK|BODYCON_CHARACTER_MODE_RUN)		// 2006-01-23 by cmkwon
#define BODYCON_MON_BUILD_MASK			(BodyCond_t)(BODYCON_MON_BUILDING|BODYCON_MON_BUILDED)		// 2007-09-10 by dhjin



////////////////////////////////////
// 몬스터의 계열
#define FACTION_GENERAL					0	// 일반적인 형태
#define FACTION_GUN						1	// 포형태 (기관포, 빔)
#define FACTION_ROCKET					2	// 로켓형태 (로켓, 유도탄)
#define FACTION_SPECIAL					3	// 특수한 형태 (부과적인 기능이 있는 무기)


///////////////////////////////////
// MonsterForm(몬스터의 형태)
#define FORM_FLYING_RIGHT				0	// 직선비행형 (비행기형태로 비행하며 공격)
#define FORM_FLYING_COPTER				1	// 헬기비행형 (헬기형태로 비행하며 공격)
#define FORM_GROUND_MOVE				2	// 지상형	  (땅 위를 이동하며 공격)
#define FORM_FLYINGandGROUND_RIGHT		3	// 지상비행형 (비행)
#define FORM_FLYINGandGROUND_COPTER		4	// 지상비행형 (비행)
#define FORM_SWIMMINGFLYING_RIGHT		5	// 유영비행형 (물속에서 물위로 나와 공격, 직선비행셩)
#define FORM_SWIMMINGFLYING_COPTER		6	// 유영비행형 (물속에서 물위로 나와 공격, 헬기 비행형)
//#define FORM_SWIMMING					7	// 물속유영형 (물속에서 유영)
#define FORM_OBJECT_STOP				8	// 오브젝트 몬스터 TargetVector의 변화가 전혀없음
#define FORM_OBJECT_PLANE_ROTATE		9	// 오브젝트 몬스터 TargetVector가 수평으로만 이동됨(2차원 변화)
#define FORM_OBJECT_CANNON				10	// 오브젝트 몬스터 TargetVector가 구형태로 이동 가능함

#define IS_OBJECT_MON_FORM(MonForm)		((MonForm) == FORM_OBJECT_STOP || (MonForm) == FORM_OBJECT_PLANE_ROTATE || (MonForm) == FORM_OBJECT_CANNON)		// 2008-04-16 by cmkwon, 몬스터 사망 시 몬스터 소환 이벤트 시스템 구현 - 

///////////////////////////////////
// Monster Attack Pattern(몬스터의 공격 형태)
#define ATTPAT_NORMAL					0	// 일반 적인 공격 형태
//#define ATTPAT_BODYSLAM					1	// 몸체를 이용한 몸통공격
#define ATTPAT_SELFDESTRUCTION			2	// 몸체를 이용한 자폭공격
#define ATTPAT_RETREAT					3	// HP가 30% 이하일 경우 후퇴와 공격을 반복
#define ATTPAT_HITANDRUN				4	// 공격 후 후퇴를 반복하는 형태
// 2005-05-02 by cmkwon, AttackObjec에 설정해야함
//#define ATTPAT_TIBE						5	// 동족 공격을 받으면 같이 공격하는 형태
#define ATTPAT_ONEATATTCK				6	// 처음 타겟을 잡은 유닛만 무조건 공격하는 형태
#define ATTPAT_PK						7	// PK 수치가 높은 사람을 공격

///////////////////////////////////
// Monster Move Pattern(몬스터의 이동형태)
#define MOVPAT_STOP						0	// 이동 없음
#define MOVPAT_STRAIGHT					1	// 직선 이동
#define MOVPAT_RIGHTANDLEFT				2	// 좌우로 직선 이동
#define MOVPAT_8RIGHTANDLEFT			3	// 좌우로 8자 이동
#define MOVPAT_PATROL					4	// 일정 구역에서만 순찰
#define MOVPAT_PARTY					5	// 무리를 지어 이동

#define MOVPAT_UPANDDOWN				10	// 상하로 이동
#define MOVPAT_OBLIQUE					11	// 대각선 사선으로 직선 이동
#define MOVPAT_OBLIQUEANDCURVE			12	// 대각선 사선으로 곡선 이동
#define MOVPAT_TELEPORT					13	// 순간 공간이동

// start 2011-05-23 by hskim, 인피니티 3차 - 웨이포인트 구현
#define MOVPAT_FOLLOWPATH				20	//  정해진 길로 이동 (웨이포인트 따라가기)
// end 2011-05-23 by hskim, 인피니티 3차 - 웨이포인트 구현

///////////////////////////////////
// Monster Belligerence(몬스터의 호전성)
#define BELL_ATATTACK					0	// 무조건 공격형태
#define BELL_DEFENSE					1	// 선 방어 후 공격형태
#define BELL_RETREAT					2	// HP가 30% 이하일 경우 무조건 공격형태
#define BELL_TAGETATATTACK				3	// 무조건 공격형태, 가장 먼저 설정된 타겟만 공격하는 형태
#define BELL_NOTATTACK					4	// 절대로 공격하지 않는형태
#define BELL_ATTACK_OUTPOST_PROTECTOR	5	// NPC소유의 보호막, 세력 구분없이 공격한다.

///////////////////////////////////////////////////////////////////////////////
// 2007-09-05 by dhjin, 규칙 정함 - 세력전 몬스터는 10 <= BELL_XXX <= 29이며 짝수=VCN, 홀수=ANI, // 2006-11-20 by cmkwon, 규칙 정함 - 세력전 몬스터는 10 <= BELL_XXX <= 19이며 짝수=VCN, 홀수=ANI
#define BELL_INFLUENCE_VCN				10	// 2005-12-27 by cmkwon, 바이제이니유 세력몬스터	- 알링턴 세력만을 공격한다.
#define BELL_INFLUENCE_ANI				11	// 2005-12-27 by cmkwon, 알링턴 세력몬스터			- 바이제니유 세력만을 공격한다.
#define BELL_STRATEGYPOINT_VCN			12	// 2005-12-27 by cmkwon, 전략포인트 세력몬스터		- 알링턴 세력만을 공격한다.
#define BELL_STRATEGYPOINT_ANI			13	// 2005-12-27 by cmkwon, 전략포인트 세력몬스터		- 바이제니유 세력만을 공격한다.
#define BELL_OUTPOST_PROTECTOR_VCN		14	// 2007-08-17 by dhjin,  바이제이니유 전진기지 보호막
#define BELL_OUTPOST_PROTECTOR_ANI		15	// 2007-08-17 by dhjin,  알링턴 전진기지 보호막
#define BELL_OUTPOST_RESET_VCN			16	// 2007-08-17 by dhjin,  바이제이니유 전진기지 중앙 처리 장치
#define BELL_OUTPOST_RESET_ANI			17	// 2007-08-17 by dhjin,  알링턴 전진기지 중앙 처리 장치
#define BELL_INFLUENCE_TELEPORT_VCN		18  // 2007-09-05 by dhjin,  바이제니유 모선전시 텔레포트 
#define BELL_INFLUENCE_TELEPORT_ANI		19  // 2007-09-05 by dhjin,  알링턴 모선전시 텔레포트 

#define BELL_ONEY_ATTACK_INFLUENCE_VCN	20	// 2010-07-06 by jskim, 기여도 없는 세력 몬스터 추가 바이제이니유 세력, 공격만 하는 몬스터 - 알링턴 세력만을 공격한다.
#define BELL_ONEY_ATTACK_INFLUENCE_ANI	21	// 2010-07-06 by jskim, 기여도 없는 세력 몬스터 추가 알링턴 세력, 공격만 하는 몬스터 - 바이제이니유 세력만을 공격한다.

#define BELL_INFINITY_DEFENSE_MONSTER			30	// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 유저 공격하지 않음, 값이 31인 몬스터 공격
#define BELL_INFINITY_ATTACK_MONSTER			31	// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 값이 30인 몬스터와 일반 유저 공격

#define IS_INFLWAR_MONSTER(monBell)				( ((monBell) >= 10) && ((monBell) <= 29) )		// 2007-09-05 by dhjin,  19 => 29
#define IS_MOTHERSHIPWAR_MONSTER(monBell)		( ((monBell) >= BELL_INFLUENCE_VCN) && ((monBell) <= BELL_INFLUENCE_ANI) )	// 2007-08-23 by cmkwon, 전략포인트는 모선이 아니다, // 2007-08-21 by dhjin, 모선전에 필요한 몬스터인지 체크
#define IS_STRATEGYPOINT_MONSTER(monBell)		( ((monBell) >= BELL_STRATEGYPOINT_VCN) && ((monBell) <= BELL_STRATEGYPOINT_ANI) )

#define IS_ONEY_ATTACK_MONSTER(monBell)			( ((monBell) >= BELL_ONEY_ATTACK_INFLUENCE_VCN) && ((monBell) <= BELL_ONEY_ATTACK_INFLUENCE_ANI)) // 2010-07-06 by jskim, 기여도 없는 세력 몬스터 추가

// 2007-09-19 by cmkwon, 수정함
#define IS_TELEPORT_MONSTER(monBell)			( ((monBell) >= BELL_INFLUENCE_TELEPORT_VCN) && ((monBell) <= BELL_INFLUENCE_TELEPORT_ANI) )	// 2007-09-19 by dhjin, 텔레포트 체크
#define IS_BELL_VCN(monBell)					(0 == (monBell)%2)		// 2006-11-20 by cmkwon, 
#define IS_BELL_ANI(monBell)					(1 == (monBell)%2)		// 2006-11-20 by cmkwon, 
#define IS_SAME_CHARACTER_MONSTER_INFLUENCE(charInfl, monBell)	(  IS_INFLWAR_MONSTER(monBell) \
																	&& ( (COMPARE_INFLUENCE((charInfl), INFLUENCE_TYPE_NORMAL|INFLUENCE_TYPE_VCN) && 0 == (monBell)%2) || (COMPARE_INFLUENCE((charInfl), INFLUENCE_TYPE_NORMAL|INFLUENCE_TYPE_ANI) && 1 == (monBell)%2) )  )

// 2009-12-11 by cmkwon, 데미지 어그로로 타겟을 변경하는 몬스터 구현 - 선공격 몬스터 인지 여부 체크
#define IS_BELL_ATTACK(monBell)					((monBell) != BELL_NOTATTACK)

// 2007-10-01 by cmkwon, 전진기지전 관련 몬스터 정의
#define IS_OUTPOST_MONSTER(monBell)				( ((monBell) >= BELL_OUTPOST_PROTECTOR_VCN) && ((monBell) <= BELL_OUTPOST_RESET_ANI) )

// 2006-11-29 by cmkwon, INFLUENCE_TYPE_XXX를 가지고 같은 세력몬스터 Belligerence를 구한다
// 2006-11-29 by cmkwon, 아래의 정의는 INFLUENCE_TYPE_NORMAL과 IS_INFLWAR_MONSTER()는 체크하지 않는다, !!! 사용하지 전에 꼭 체크해야함
#define GET_SAME_MONSTER_BELL_BY_CHARACTER_INFLTYPE(charInflTy)		( (INFLUENCE_TYPE_VCN==(charInflTy))?BELL_INFLUENCE_VCN:BELL_INFLUENCE_ANI )
#define GET_SAME_CHARACTER_INFL_BY_MONSTER_BELL(monBell)			( (IS_BELL_VCN(monBell))?INFLUENCE_TYPE_VCN:INFLUENCE_TYPE_ANI )
#define GET_OTHER_CHARACTER_INFL_BY_MONSTER_BELL(monBell)			( (IS_BELL_VCN(monBell))?INFLUENCE_TYPE_ANI:INFLUENCE_TYPE_VCN )				// 2009-01-12 by dhjin, 선전 포고
#define GET_OTHER_MONSTER_BELL_BY_CHARACTER_INFLTYPE(charInflTy)	( (INFLUENCE_TYPE_VCN==(charInflTy))?BELL_INFLUENCE_ANI:BELL_INFLUENCE_VCN )		// 2006-12-20 by cmkwon, 캐릭터와 적대세력

// 2010-03-16 by cmkwon, 인피2차 MtoM, MtoC 타겟 변경 관련 수정 - 
#define IS_WARABLE_M2M_BELL(AttMonBell, TarMonBell)		( (BELL_INFINITY_ATTACK_MONSTER == (AttMonBell) && BELL_INFINITY_DEFENSE_MONSTER == (TarMonBell)) || (BELL_INFINITY_DEFENSE_MONSTER == (AttMonBell) && BELL_INFINITY_ATTACK_MONSTER == (TarMonBell)) )

// 2006-12-13 by cmkwon
char* GetMonsterBellString(BYTE i_byMonBell);

///////////////////////////////////
// Monster Attack Object(몬스터의 공격 타겟 형태), ATTACKOBJ_XXX
#define ATTACKOBJ_CLOSERANGE			0	// 가장 근거리 유닛공격
#define ATTACKOBJ_FIRSTATTACK			1	// 먼저 공격한 유닛공격
#define ATTACKOBJ_LOWHP					2	// HP가 가장 적은 유닛공격
#define ATTACKOBJ_HIGHHP				3	// HP가 가장 많은 유닛공격
//#define ATTACKOBJ_PK					4	// PK 수치가 높은 사람을 공격 - 현재는 PK 시스템이 없음
#define ATTACKOBJ_SAMERACE				5	// 동적성향, 공격당한 몬스터 주위에 타입이 같은 몬스터도 같이 공격한다
#define ATTACKOBJ_RANDOM				6	// 랜덤으로 선택
#define ATTACKOBJ_AGGRO					7	// 2009-12-11 by cmkwon, 데미지 어그로로 타겟을 변경하는 몬스터 구현 - 


///////////////////////////////////
// Monster Move Pattern Option(몬스터의 이동 패턴 옵션, 비트 플래그 사용), MPOPTION_XXX,MPOPTION_BIT_XXX
// 2010-01-11 by cmkwon, 몬스터 MPOption 64bit로 변경 - 기존(8bit)
#define COMPARE_MPOPTION_BIT(VAR, MASK) (((VAR) & (MASK)) != 0)
#define MPOPTION_BIT_DEAD_FALL					((BitFlag64_t)0x0000000000000001)	// 1,	몬스터가 폭발시 추락할것인지의 플래그(0이면 폭발)
#define MPOPTION_BIT_MOVE_PARTY					((BitFlag64_t)0x0000000000000002)	// 2,	MPOptionParam1 = 편대 형태, MPOptionParam2 = 최대편대 마리수 ==> 동족성향도 동시에 갖는다
#define MPOPTION_BIT_PATTERN_MONSTER			((BitFlag64_t)0x0000000000000004)	// 4,	몬스터가 생성후 MONSTER_EVENT_MON_NOT_MOVE_AFTER_CREATED_TERM_TICK 이시간 동안 움직이지 않는다, (패턴과 애니메이션이 적용되는 시간)
#define MPOPTION_BIT_BOSS_MONSTER				((BitFlag64_t)0x0000000000000008)	// 8,	보스 몬스터 플래그 - MoveRange를 크게, 드랍SPI/드랍아이템/드랍레어 레벨차 손실 없음
#define MPOPTION_BIT_AUTO_DESTROY				((BitFlag64_t)0x0000000000000010)	// 16,	생성되고 MPOptionParam1 시간이 경과 하면 자동 소멸되는 형태의 몬스터(단위:분), 최소 1분 ~ 최대 255분
#define MPOPTION_BIT_NAMED_MONSTER				((BitFlag64_t)0x0000000000000020)	// 32,	2005-12-16 by cmkwon, 네임드 몬스터 - 드랍SPI/드랍아이템/드랍레어 레벨차 손실 없음
#define MPOPTION_BIT_RECOGNIZE_INVISIBLE		((BitFlag64_t)0x0000000000000040)	// 64,	2007-01-16 by cmkwon, 인비지블 스킬 상태의 캐릭터를 인식한다
#define MPOPTION_BIT_KEY_MONSTER				((BitFlag64_t)0x0000000000000080)	// 128,	// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 다음 이벤트가 발생할 수 있는 Key몬스터
#define MPOPTION_BIT_NO_ALPHABLENDING_IN_DEAD	((BitFlag64_t)0x0000000000000100)	// 256,	// 2010-01-11 by cmkwon, 몬스터 폭파시 알파블렌딩(AlphaBlending) 처리 없음 플래그 - 
#define MPOPTION_BIT_KEY_MONSTER_ALIVE_FOR_GAMECLEAR	((BitFlag64_t)0x0000000000000200)	// 512,	// 2010-03-31 by dhjin, 인피니티(기지방어) - 폭파시 인피니티 종료 되는 키몬스터

///////////////////////////////////
// Monster Move Pattern Option - MPOPTION_MOVE_PARTY, 편대 형태
#define FORMATION_COLUMN					0		// 종대
#define FORMATION_LINE						1		// 횡대
#define FORMATION_TRIANGLE					2		// 삼각
#define FORMATION_INVERTED_TRIANGLE			3		// 역삼각
#define FORMATION_BELL						4		// 종
#define FORMATION_INVERTED_BELL				5		// 역종


///////////////////////////////////////////////////////////////////////////////
// 몬스터 습성관련
#define DES_MONHABIT_NOT					0	// (무속성)
#define DES_MONHABIT_DAY					1	// (낮 명중률 10% 상승)
#define DES_MONHABIT_NIGHT					2	// (밤 명중률 10% 상승)


///////////////////////////////////
// 아이템 종류(기관포, 빔, 로켓.......), ITEMKIND_XXX
// 캐릭터용 아이템
#define IS_CHARACTER_ITEM(x)			((x) >= ITEMKIND_AUTOMATIC && (x) <= ITEMKIND_SKILL_ATTRIBUTE)
// 일반 아이템
#define IS_GENERAL_ITEM(x)				((x) >= ITEMKIND_AUTOMATIC && (x) <= ITEMKIND_GENERAL_ITEM_END)
// 무기류
#define IS_WEAPON(x)					((x) >= ITEMKIND_AUTOMATIC && (x) <= ITEMKIND_DECOY)
// 1형 무기
#define IS_PRIMARY_WEAPON(x)			((x) >= ITEMKIND_AUTOMATIC && (x) <= ITEMKIND_MASSDRIVE)
// 1-1형 무기
#define IS_PRIMARY_WEAPON_1(x)			((x) >= ITEMKIND_AUTOMATIC && (x) <= ITEMKIND_MASSDRIVE)	// 1-1형 무기인가?
#define ITEMKIND_AUTOMATIC				(BYTE)0		// 오토매틱류(1-1형)
#define ITEMKIND_VULCAN					(BYTE)1		// 발칸류(1-1형)
#define ITEMKIND_DUALIST				(BYTE)2		// 듀얼리스트류(1-1형)	// 2005-08-01 by hblee : GRENADE -> DUALIST 으로 변경.
#define ITEMKIND_CANNON					(BYTE)3		// 캐논류(1-1형)
#define ITEMKIND_RIFLE					(BYTE)4		// 라이플류(1-1형)
#define ITEMKIND_GATLING				(BYTE)5		// 개틀링류(1-1형)
#define ITEMKIND_LAUNCHER				(BYTE)6		// 런처류(1-1형)
#define ITEMKIND_MASSDRIVE				(BYTE)7		// 메스드라이브류(1-1형)
// 1-2형 무기
//#define IS_PRIMARY_WEAPON_2(x)			((x) >= ITEMKIND_RIFLE && (x) <= ITEMKIND_MASSDRIVE)	// 1-2형(BEAM류) 무기인가?
#define IS_PRIMARY_WEAPON_2(x)			(FALSE)		// 2005-09-27 by cmkwon, 1-2형 무기는 없다
// 2005-09-27 by cmkwon, 1-1형으로 변경함
//#define ITEMKIND_RIFLE					(BYTE)4		// 라이플류(1-2형)
//#define ITEMKIND_GATLING				(BYTE)5		// 개틀링류(1-2형)
//#define ITEMKIND_LAUNCHER				(BYTE)6		// 런처류(1-2형)
//#define ITEMKIND_MASSDRIVE				(BYTE)7		// 메스드라이브류(1-2형)
// 2형 무기
#define IS_SECONDARY_WEAPON(x)			((x) >= ITEMKIND_ROCKET && (x) <= ITEMKIND_DECOY)
// 2-1형 무기
#define IS_SECONDARY_WEAPON_1(x)		((x) >= ITEMKIND_ROCKET && (x) <= ITEMKIND_MINE)
#define ITEMKIND_ROCKET					(BYTE)8		// 로켓류(2-1형)
#define ITEMKIND_MISSILE				(BYTE)9		// 미사일류(2-1형)
#define ITEMKIND_BUNDLE					(BYTE)10	// 번들류(2-1형)
#define ITEMKIND_MINE					(BYTE)11	// 마인류(2-1형)
// 2-2형 무기
#define IS_SECONDARY_WEAPON_2(x)		((x) >= ITEMKIND_SHIELD && (x) <= ITEMKIND_DECOY)
#define ITEMKIND_SHIELD					(BYTE)12	// 쉴드류(2-2형)
#define ITEMKIND_DUMMY					(BYTE)13	// 더미류(2-2형)
#define ITEMKIND_FIXER					(BYTE)14	// 픽서류(2-2형)
#define ITEMKIND_DECOY					(BYTE)15	// 디코이류(2-2형)
// 나머지 아이템
#define ITEMKIND_DEFENSE				(BYTE)16	// 아머류
#define ITEMKIND_SUPPORT				(BYTE)17	// 기타보조장비류, 엔진 등
#define ITEMKIND_ENERGY					(BYTE)18	// 에너지류, countable
#define ITEMKIND_INGOT					(BYTE)19	// 2008-11-24 by dhjin, 럭키 아이템 // 오어 & 보드, countable
#define ITEMKIND_CARD					(BYTE)20	// 일반 카드(지금 존재하지 않음, 20040716, kelovon, 사용하게 되면 살림)
#define ITEMKIND_ENCHANT				(BYTE)21	// 인챈트 카드
#define ITEMKIND_TANK					(BYTE)22	// 탱크(EP 탱크 등)
#define ITEMKIND_BULLET					(BYTE)23	// 탄알류(=탄통), countable
#define ITEMKIND_QUEST					(BYTE)24	// 퀘스트용 아이템, countable
#define ITEMKIND_RADAR					(BYTE)25	// 레이더
#define ITEMKIND_COMPUTER				(BYTE)26	// 컴퓨터 아이템
#define ITEMKIND_GAMBLE					(BYTE)27	// RareFix 생성용 카드, 인챈트와 같은 방법 사용
#define ITEMKIND_PREVENTION_DELETE_ITEM	(BYTE)28	// 인챈트 시에 아이템 삭제 방지 아이템 
#define ITEMKIND_BLASTER				(BYTE)29	// 2005-08-01 by hblee : 블래스터류 아이템 추가.
#define ITEMKIND_RAILGUN				(BYTE)30	// 2005-08-01 by hblee : 레일건류 아이템 추가.
#define ITEMKIND_ACCESSORY_UNLIMITED	(BYTE)31	// 2006-03-17 by cmkwon, 사용시간이 <영원>인 액세서리 아이템
#define ITEMKIND_ACCESSORY_TIMELIMIT	(BYTE)32	// 2006-03-17 by cmkwon, 사용시간에 시간 제한이 있는 액세서리 아이템
#define ITEMKIND_INFLUENCE_BUFF			(BYTE)33	// 2009-01-05 by dhjin, 미션마스터 - 편대 버프 아이템 추가 - 실제로 ITEMKIND_BUFF 라는 의미로 변경, // 2006-04-21 by cmkwon, 세력 버프, 현재는 세력버프 아이템
#define ITEMKIND_INFLUENCE_GAMEEVENT	(BYTE)34	// 2006-04-21 by cmkwon, 세력 게임이벤트
#define ITEMKIND_RANDOMBOX				(BYTE)35	// 2006-08-10 by cmkwon, 랜덤 박스 - 판도라 박스
#define ITEMKIND_MARK					(BYTE)36	// 2006-08-21 by cmkwon, 마크 - 이펙트 아이템
#define ITEMKIND_SKILL_SUPPORT_ITEM		(BYTE)37	// 2006-09-29 by cmkwon, 보조스킬아이템
#define ITEMKIND_PET_ITEM				(BYTE)38	// 2010-06-15 by shcho&hslee 펫시스템 - 펫 아이템.
#define ITEMKIND_GENERAL_ITEM_END		(BYTE)39	// General Item의 끝을 표시함, 실재로 사용 안 됨

// DestParameter & ParamValue용 + ReqItemKind용, 실제 아이템의 Kind 필드에는 들어가지 않음, 현재 enchant, skill에만 사용, 20041019, kelovon with sjmin
#define ITEMKIND_ALL_ITEM				(BYTE)40	// 모든 아이템, ReqItemKind 확인할 필요 없음
#define ITEMKIND_ALL_WEAPON				(BYTE)43	// 모든 무기
#define ITEMKIND_PRIMARY_WEAPON_ALL		(BYTE)44	// 1형 무기
#define ITEMKIND_PRIMARY_WEAPON_1		(BYTE)45	// 1-1형 무기
#define ITEMKIND_PRIMARY_WEAPON_2		(BYTE)46	// 1-2형 무기
#define ITEMKIND_SECONDARY_WEAPON_ALL	(BYTE)47	// 2형 무기
#define ITEMKIND_SECONDARY_WEAPON_1		(BYTE)48	// 2-1형 공격 무기
#define ITEMKIND_SECONDARY_WEAPON_2		(BYTE)49	// 2-2형 방어 무기
// 스킬류 아이템
#define IS_SKILL_ITEM(x)				((x) >= ITEMKIND_SKILL_ATTACK && (x) <= ITEMKIND_SKILL_ATTRIBUTE)
#define ITEMKIND_SKILL_ATTACK			(BYTE)50	// 공격 스킬
#define ITEMKIND_SKILL_DEFENSE			(BYTE)51	// 방어 스킬
#define ITEMKIND_SKILL_SUPPORT			(BYTE)52	// 컨트롤 스킬 + 보조 스킬
#define ITEMKIND_SKILL_ATTRIBUTE		(BYTE)53	// 속성 스킬

#define ITEMKIND_COLOR_ITEM				(BYTE)60	// 아머 아이템의 색상 아이템, // 2005-12-06 by cmkwon

// 몬스터용 아이템
#define IS_MONSTER_ITEM(x)				((x) >= ITEMKIND_FOR_MON_PRIMARY && (x) <= ITEMKIND_FOR_MON_MAIN_ARMAMENT) // 2011-05-13 by hskim, 인피니티 3차
#define IS_PRIMARY_WEAPON_MONSTER(x)	((x) >= ITEMKIND_FOR_MON_PRIMARY && (x) <= ITEMKIND_FOR_MON_RANGE_ATTACK)		// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 몬스터 스킬 아이템 Kind 추가
#define IS_SECONDARY_WEAPON_MONSTER(x)	((x) >= ITEMKIND_FOR_MON_SECONDARY && (x) <= ITEMKIND_FOR_MON_MAIN_ARMAMENT) // 2011-05-13 by hskim, 인피니티 3차
#define ITEMKIND_FOR_MON_PRIMARY		(BYTE)100	// 1형 몬스터용 아이템
#define ITEMKIND_FOR_MON_GUN			(BYTE)101	// 몬스터 기관포류(1-1형)
#define ITEMKIND_FOR_MON_BEAM			(BYTE)102	// 몬스터 빔류(1-2형)
#define ITEMKIND_FOR_MON_ALLATTACK		(BYTE)103	// 몬스터 전체 공격
#define ITEMKIND_FOR_MON_SKILL			(BYTE)104	// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 몬스터 스킬 아이템 Kind 추가
#define ITEMKIND_FOR_MON_RANGE_ATTACK	(BYTE)105	// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 몬스터 범위 공격 
#define ITEMKIND_FOR_MON_SECONDARY		(BYTE)150	// 2형 몬스터용 아이템
#define ITEMKIND_FOR_MON_ROCKET			(BYTE)151	// 몬스터 로켓(2-1형)
#define ITEMKIND_FOR_MON_MISSILE		(BYTE)152	// 몬스터 미사일류(2-1형)
#define ITEMKIND_FOR_MON_BUNDLE			(BYTE)153	// 몬스터 번들류(2-1형)
#define ITEMKIND_FOR_MON_MINE			(BYTE)154	// 몬스터 마인류(2-1형)
#define ITEMKIND_FOR_MON_SHIELD			(BYTE)155	// 몬스터 쉴드류(2-2형)
#define ITEMKIND_FOR_MON_DUMMY			(BYTE)156	// 몬스터 더미류(2-2형)
#define ITEMKIND_FOR_MON_FIXER			(BYTE)157	// 몬스터 픽서류(2-2형)
#define ITEMKIND_FOR_MON_DECOY			(BYTE)158	// 몬스터 디코이류(2-2형)
#define ITEMKIND_FOR_MON_FIRE			(BYTE)159	// 몬스터 파이어류
#define ITEMKIND_FOR_MON_OBJBEAM		(BYTE)160	// 몬스터 충돌가능 빔류 e 직선 빔과 충돌할 경우 데미지 발생
#define ITEMKIND_FOR_MON_STRAIGHTBOOM	(BYTE)161	// 몬스터 직진 폭탄류 e 일정한 방향성을 가지고 무기가 발사되며 그 오브젝트에 맞을 경우 데미지 발생 (패턴으로 가능 예상, 검토바람)
#define ITEMKIND_FOR_MON_MAIN_ARMAMENT	(BYTE)162	// 몬스터 주포 공격류 (인피니티 3차 모선전) - // 2011-03-28 by hskim, 인피니티 3차 - 몬스터 멀티 타겟팅 기능 추가 - 메인 주포로 설정된 경우 일정 거리가 벗어나도 발사되는 이펙트를 볼 수 있음

#define ITEMKIND_UNKNOWN				(BYTE)255	// 2006-07-28 by cmkwon, 

// 각종 매크로
	// IS_COUNTABLE_ITEM		==> 개수를 계산하는 아이템류인가? 에너지류, INGOT, 탄알류 등
	// IS_BUNCH_COUNTABLE_ITEM	==> 묶음 개수를 계산하는 아이템류인가? 카드류, 인챈트류, 갬블류
#define COUNT_BUNCH_COUNTABLE_ITEM_UNIT			10	// 묶음 개수 아이템류 묶음 단위

// 2008-11-26 by cmkwon, 대만 Netpower_Tpe 웹에서 아이템 추가 프로시저 추가 - 
//							- IS_COUNTABLE_ITEM 수정시 반드시 dbo.atum_IsCountableItem 도 같이 수정 해야 한다.
#define IS_COUNTABLE_ITEM(_ITEM_KIND)			((_ITEM_KIND) == ITEMKIND_ENERGY || (_ITEM_KIND) == ITEMKIND_INGOT || (_ITEM_KIND) == ITEMKIND_CARD || (_ITEM_KIND) == ITEMKIND_ENCHANT || (_ITEM_KIND) == ITEMKIND_BULLET || (_ITEM_KIND) == ITEMKIND_QUEST || (_ITEM_KIND) == ITEMKIND_GAMBLE || (_ITEM_KIND) == ITEMKIND_PREVENTION_DELETE_ITEM || (_ITEM_KIND) == ITEMKIND_INFLUENCE_BUFF || (_ITEM_KIND) == ITEMKIND_INFLUENCE_GAMEEVENT)
#define IS_SPECIAL_COUNTABLE_ITEM(_ITEM_KIND)	((_ITEM_KIND) == ITEMKIND_CARD || (_ITEM_KIND) == ITEMKIND_ENCHANT || (_ITEM_KIND) == ITEMKIND_GAMBLE || (_ITEM_KIND) == ITEMKIND_PREVENTION_DELETE_ITEM)

// 2010-04-20 by cmkwon, 신규 러키 머신 구현 - 아머(ITEMKIND_DEFENSE) 추가
#define COMPARE_ITEMKIND(_REQ_ITEM_KIND, _TARGET_KIND_VAR)											\
	((_REQ_ITEM_KIND == ITEMKIND_ALL_ITEM) || (_REQ_ITEM_KIND == _TARGET_KIND_VAR)				\
	|| ((_REQ_ITEM_KIND == ITEMKIND_ALL_WEAPON) && IS_WEAPON(_TARGET_KIND_VAR))						\
	|| ((_REQ_ITEM_KIND == ITEMKIND_PRIMARY_WEAPON_ALL) && IS_PRIMARY_WEAPON(_TARGET_KIND_VAR))		\
	|| ((_REQ_ITEM_KIND == ITEMKIND_PRIMARY_WEAPON_1) && IS_PRIMARY_WEAPON_1(_TARGET_KIND_VAR))		\
	|| ((_REQ_ITEM_KIND == ITEMKIND_PRIMARY_WEAPON_2) && IS_PRIMARY_WEAPON_2(_TARGET_KIND_VAR))		\
	|| ((_REQ_ITEM_KIND == ITEMKIND_SECONDARY_WEAPON_ALL) && IS_SECONDARY_WEAPON(_TARGET_KIND_VAR))	\
	|| ((_REQ_ITEM_KIND == ITEMKIND_SECONDARY_WEAPON_1) && IS_SECONDARY_WEAPON_1(_TARGET_KIND_VAR))	\
	|| ((_REQ_ITEM_KIND == ITEMKIND_DEFENSE) && (ITEMKIND_DEFENSE == _TARGET_KIND_VAR))	\
	|| ((_REQ_ITEM_KIND == ITEMKIND_SECONDARY_WEAPON_2) && IS_SECONDARY_WEAPON_2(_TARGET_KIND_VAR)))

// 2008-11-26 by cmkwon, 대만 Netpower_Tpe 웹에서 아이템 추가 프로시저 추가 - 
//							- IS_CHARGABLE_ITEM 수정시 반드시 dbo.atum_IsChargableItem 도 같이 수정 해야 한다.
//							- 카운터블 아이템을 Chargable Item 이 될수 없다. Chargable Item은 반드시 넌카운터블 아이템만 가능하다.
#define IS_CHARGABLE_ITEM(_ITEM_KIND)	(IS_WEAPON(_ITEM_KIND)||(_ITEM_KIND)==ITEMKIND_TANK || (_ITEM_KIND)==ITEMKIND_ACCESSORY_UNLIMITED || (_ITEM_KIND)==ITEMKIND_ACCESSORY_TIMELIMIT)	// ITEM::Charging을 ITEM_GENERAL::CurrentCount에 할당해서 쓰는 아이템

// 2007-08-29 by cmkwon, 조합시 아머도 무기와 같이 레어/인챈트 정보 유지하기 - 
#define IS_ITEMKIND_REMAIN_RARE8ENCHANT_AS_MIX(_ITEM_KIND)	(IS_WEAPON(_ITEM_KIND) || ITEMKIND_DEFENSE==(_ITEM_KIND))

// 2009-02-17 by cmkwon, 인챈트 할 수 있는 아이템 카인드 수정 - 무기, 아머, 레이더, 엔진
#define IS_ENCHANT_TARGET_ITEMKIND(_IT_)		(IS_WEAPON(_IT_) || ITEMKIND_DEFENSE == (_IT_) || ITEMKIND_RADAR == (_IT_) || ITEMKIND_SUPPORT == (_IT_) || ITEMKIND_ACCESSORY_UNLIMITED == (_IT_))	// 2009-09-09 ~ 2010-02-10 by dhjin, 인피니티 - 발동류장착아이템

// 2010-04-20 by cmkwon, 신규 러키 머신 구현 - 아머(ITEMKIND_DEFENSE)도 추가
#define IS_RARE_TARGET_ITEMKIND(_IT_)			(IS_WEAPON(_IT_) || ITEMKIND_DEFENSE == (_IT_))	// 2009-09-09 ~ 2010-02-10 by dhjin, 인피니티 - 발동류장착아이템

// 2009-08-26 by cmkwon, 그래픽 리소스 변경 시스템 구현 - 
//						- 외형 변경 가능 Kind 총 5종, 1형/2형 무기, 마크, 아머, 레이더
//						- 아이템의 이펙트 변경 가능 Kind 총 2종, 1형/2형 무기
#define IS_ENABLE_CHANGE_ShapeItemNum(_ITEM_KIND)		(IS_WEAPON(_ITEM_KIND) || ITEMKIND_MARK == (_ITEM_KIND) || ITEMKIND_DEFENSE == (_ITEM_KIND) || ITEMKIND_RADAR == (_ITEM_KIND))
#define IS_ENABLE_CHANGE_EffectItemNum(_ITEM_KIND)		(IS_WEAPON(_ITEM_KIND))


///////////////////////////////////////////////////////////////////////////////
// 유료화 아이템 kind - ITEM 구조체에서 SummonMonster 필드를 사용한다
// 2009-01-28 by cmkwon, 캐쉬�?수정(추천탭,신상품 추가) - 아래의 컬러 탭만 고정하고 다른 탭은 의미를 두지 않는다. 단지 탭의 순서만을 의미하게 수정함.
// #define CASH_ITEMKIND_PREMIUM_CARD			(BYTE)0
// #define CASH_ITEMKIND_OPTION_ITEM			(BYTE)1
// #define CASH_ITEMKIND_CARD_ITEM				(BYTE)2
// #define CASH_ITEMKIND_ACCESSORY_ITEM		(BYTE)3
// #define CASH_ITEMKIND_COLOR_ITEM			(BYTE)4			// 2007-08-09 by cmkwon, 유료상점에 아머 컬러 상점 탭 추가
// #define CASH_ITEMKIND_PACKAGE_ITEM			(BYTE)5			// 2008-10-20 by cmkwon, 유료상점에 캐쉬 상점 탭 추가

#define CASH_ITEMKIND_RECOMMEND_ITEM				((BYTE)0x00)	// 2009-01-28 by cmkwon, 캐쉬�?수정(추천탭,신상품 추가) - 첫번째 탭은 추천탭
#define CASH_ITEMKIND_COLOR_ITEM					((BYTE)0x09)	// 2009-01-28 by cmkwon, 캐쉬�?수정(추천탭,신상품 추가) - 컬러탭은 고정 해야 하므로 일단 제일 뒤로 지정함.

#define CASHSHOP_BIT_TAPINDEX_MASK					((BYTE)0x0F)	// 2009-01-28 by cmkwon, 캐쉬�?수정(추천탭,신상품 추가) - 
#define CASHSHOP_BIT_RECOMMEND						((BYTE)0x10)	// 2009-01-28 by cmkwon, 캐쉬�?수정(추천탭,신상품 추가) - 
#define CASHSHOP_BIT_NEW							((BYTE)0x20)	// 2009-01-28 by cmkwon, 캐쉬�?수정(추천탭,신상품 추가) - 
#define GET_TABINDEX_BY_CASHSHOPINDEX(idx)				((idx)&CASHSHOP_BIT_TAPINDEX_MASK)				// 2009-01-28 by cmkwon, 캐쉬�?수정(추천탭,신상품 추가) - 0~15까지가 탭인덱스임
#define GET_CASHSHOP_BIT_BY_CASHSHOPINDEX(idx)			((idx)&((BYTE)(~CASHSHOP_BIT_TAPINDEX_MASK)))	// 2009-01-28 by cmkwon, 캐쉬�?수정(추천탭,신상품 추가) - 16~255까지가 캐쉬아이템 비트플래그
#define IS_NEW_CASHSHOPITEM_BY_CASHSHOPINDEX(idx)		(0 != ((idx)&CASHSHOP_BIT_NEW))				// 2009-01-28 by cmkwon, 캐쉬�?수정(추천탭,신상품 추가) - 신상품 체크
#define IS_RECOMMEND_CASHSHOPITEM_BY_CASHSHOPINDEX(idx)	(0 != ((idx)&CASHSHOP_BIT_RECOMMEND))		// 2009-01-28 by cmkwon, 캐쉬�?수정(추천탭,신상품 추가) - 추천상품 체크


///////////////////////////////////////////////////////////////////////////////
// ITEM에 OrbitType 필드에 사용 define 값으로 미사일, 로켓 등의 궤적을 나타낸다
#define ORBIT_SINGLE_CROSS_FIRE			1            // 한발로 다음 리어택타임동안 균등하게 엇갈려 발사한다.
#define ORBIT_SINGLE_FIRE_100			32        // 한발 발사_100,150,200,250,300,320,350, 한발만 발사되며 일정 시간 후 다음 발이 발사된다.
#define ORBIT_SINGLE_FIRE_150			33
#define ORBIT_SINGLE_FIRE_200			2	// 한발 발사_200,250,300,320,350, 한발만 발사되며 일정 시간 후 다음 발이 발사된다.
#define ORBIT_SINGLE_FIRE_250			3
#define ORBIT_SINGLE_FIRE_300			4
#define ORBIT_SINGLE_FIRE_320			5
#define ORBIT_SINGLE_FIRE_350			6
#define ORBIT_TWIN_CROSS_FIRE			7	// 쌍발로 다음 리어택타임동안 균등하게 엇갈려 발사한다.
#define ORBIT_TWIN_FIRE_100				34        // 쌍발 발사_100,150,200,250,300,320,350, 쌍발로 발사되며 일정 시간 후 다음 발이 발사된다.
#define ORBIT_TWIN_FIRE_150				35
#define ORBIT_TWIN_FIRE_200				8	// 쌍발 발사_200,250,300,320,350, 쌍발로 발사되며 일정 시간 후 다음 발이 발사된다.
#define ORBIT_TWIN_FIRE_250				9
#define ORBIT_TWIN_FIRE_300				10
#define ORBIT_TWIN_FIRE_320				11
#define ORBIT_TWIN_FIRE_350				12
#define ORBIT_CROSS_FIRE				13	// 엇갈려 발사, 쌍발로 다음 리어택타임동안 균등하게 엇갈려 발사한다.
#define ORBIT_STRAIGHT_ROCKET_250		14	// 직선 로켓 발사_250, 직선으로 발사된다.
#define ORBIT_FALL_ROCKET_250			15	// 하강 로켓 발사_250, 하강 후 직선으로 로켓이 발사된다.
#define ORBIT_LEFT_ROCKET_200			16	// 왼쪽 직선 로켓 발사_200, 왼쪽부터 직선 로켓이 발사된다.
#define ORBIT_RIGHT_ROCKET_200			17	// 오른쪽 직선 로켓 발사_200, 오른쪽부터 직선 로켓이 발사된다.
#define ORBIT_THREE_ROCKET				18	// 3단 직선 로켓 발사, 로켓의 라이프 타임을 3단계로 하여 각각 타임에서 단이 분리되면서 타겟쪽으로 방향을 움직여 발사된다.
#define ORBIT_CHILD_ROCKET				19	// 자폭탄 로켓 발사, 타겟의 근처에 까지 이동한 후 주변으로 자폭탄이 분리되어 발사된다.
#define ORBIT_STRAIGHT_MISSILE_300		20	// 직선 유도 미사일 발사_300, 직선으로 출발하여 유도된다.
#define ORBIT_FALL_MISSILE_300			21	// 하강 유도 미사일 발사_300, 하강 후 직선으로 유도 미사일이 발사된다.
#define ORBIT_LEFT_MISSILE_300			22	// 안쪽 유도 미사일 발사_300, 안쪽부터 직선으로 유도 미사일이 발사된다.
#define ORBIT_RIGHT_MISSILE_270			23	// 바깥쪽 유도 미사일 발사_270, 바깥쪽부터 직선으로 유도 미사일이 발사된다.
#define ORBIT_UPDOWN_ROCKET_270			24	// 상승 곡선형 로켓 발사_270, 위로 상승 후 타겟까지 곡선형태로 떨어지는 로켓이 발사된다.
#define ORBIT_UPDOWN_MISSILE_300		25	// 상승 유도형 미사일 발사_300, 위로 상승 후 타겟까지 유도형 미사일이 발사된다.
#define ORBIT_FLAME_THROWER				26	// 분사형 무기 발사, 화염이나 냉기등 분사가 가능한 무기가 발사된다.
#define ORBIT_BODYSLAM					27	// 몸통 공격 발사, 직접 타격하여 공격한다.
#define ORBIT_MINE_300					28	// 마인 발사_300,400, 특정한 포트를 공간에 발사한다.
#define ORBIT_MINE_400					29
#define ORBIT_RANGE_ROCKET_300			30	// 로켓 난사_300,400, 적의 주변으로 로켓을 발사한다.
#define ORBIT_RANGE_ROCKET_400			31
#define ORBIT_FIRE						100	// 몬스터 파이어류
#define ORBIT_OBJBEAM					101	// 몬스터 충돌가능 빔류 e 직선 빔과 충돌할 경우 데미지 발생
#define ORBIT_STRAIGHTBOOM				102	// 몬스터 직진 폭탄류 e 일정한 방향성을 가지고 무기가 발사되며 그 오브젝트에 맞을 경우 데미지 발생 (패턴으로 가능 예상, 검토바람)
#define ORBIT_CATCH						103	// 몬스터 잡기공격류
#define ORBIT_STICK						104	// 몬스터 부착공격류
#define ORBIT_ATTACK_ALL				105	// 몬스터 전체공격류
#define ORBIT_SKILL_DEBUFF_TIMELIMIT	200	// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 시간형 DEBUFF
#define ORBIT_SKILL_DOT_TIMELIMIT		210	// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 시간형 DOT
#define IS_ORBIT_SKILL(x)				((x) >= ORBIT_SKILL_DEBUFF_TIMELIMIT && (x) <= ORBIT_SKILL_DOT_TIMELIMIT)		// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 

///////////////////////////////////
// 건물(상점) 종류, BUILDINGKIND_XXX
#define BUILDINGKIND_1ST_WEAPONSHOP		(BYTE)0		// 기본무기파트
#define BUILDINGKIND_2ND_WEAPONSHOP		(BYTE)1		// 고급무기파트
#define BUILDINGKIND_COMPONENTSHOP		(BYTE)2		// 소모품파트
#define BUILDINGKIND_PETSHOP			(BYTE)3		// 펫파트
#define BUILDINGKIND_ANTIQUESHOP		(BYTE)4		// 골동품파트
#define BUILDINGKIND_CITYWARP			(BYTE)5		// 워프상점(구 도시워프, 구 BUILDINGKIND_HANGAR)
#define BUILDINGKIND_PUBLICOFFICE		(BYTE)6		// 관제파트
#define BUILDINGKIND_ACTIONHOUSE		(BYTE)7		// 경매파트
#define BUILDINGKIND_RACETRACK			(BYTE)8		// 레이싱파트
#define BUILDINGKIND_REFINERY			(BYTE)9		// 수리파트 - 보급 상점
#define BUILDINGKIND_LABORATORY			(BYTE)10	// 연구파트
#define BUILDINGKIND_FACTORY			(BYTE)11	// 공장파트, 구 BUILDINGKIND_ROBOTHANGAR
#define BUILDINGKIND_MILITARYACADEMY	(BYTE)12	// 사관학교파트
#define BUILDINGKIND_STORE				(BYTE)13	// 창고
#define BUILDINGKIND_SKILL_SHOP			(BYTE)14	// 스킬 상점
#define BUILDINGKIND_AUCTION			(BYTE)15	// 경매, 물품 대행 상점
#define BUILDINGKIND_CITY_OCCUPY_INFO	(BYTE)16	// 도시 점령 정보 상점
#define BUILDINGKIND_TUNING_COLOR		(BYTE)17	// 2005-11-11 by cmkwon, 튜닝 색상 상점
#define BUILDINGKIND_ARENA				(BYTE)18	// 2007-04-23 by dhjin, ARENA
#define BUILDINGKIND_WARPOINT_SHOP		(BYTE)19	// 2007-05-17 by dhjin, WARPOINT SHOP
#define BUILDINGKIND_BRIEFING_ROOM		(BYTE)20	// 2007-07-16 by dhjin, BRIEFING_ROOM
#define BUILDINGKIND_TUTORIAL			(BYTE)21	// 2007-07-16 by dhjin, BUILDINGKIND_TUTORIAL
#define BUILDINGKIND_CITYLEADER_LEADER  (BYTE)22	// 2007-08-27 by dhjin, BUILDINGKIND_CITYLEADER_LEADER
#define BUILDINGKIND_CITYLEADER_OUTPOST (BYTE)23	// 2007-08-27 by dhjin, BUILDINGKIND_CITYLEADER_OUTPOST
#define BUILDINGKIND_LUCKY				(BYTE)24	// 2010-04-20 by cmkwon, 신규 러키 머신 구현 - 아머/무기/해피만 사용, 옵션머신은 아래에 따로 추가// 2008-11-04 by dhjin, 럭키머신, BUILDINGKIND_LUCKY
#define BUILDINGKIND_WORLDRANKING		(BYTE)25	// 2009-02-12 by cmkwon, EP3-3 월드랭킹시스템 구현 - 
#define BUILDINGKIND_INFINITY			(BYTE)30	// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 
#define BUILDINGKIND_INFINITY_SHOP		(BYTE)31	// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 상점
#define BUILDINGKIND_LUCKY_OPTION_MACHINE	(BYTE)32	// 2010-04-20 by cmkwon, 신규 러키 머신 구현 - 옵션머신을 위한 추가
#define BUILDINGKIND_DISSOLUTION		(BYTE)33	// 2010-08-31 by shcho&jskim 아이템용해 시스템 -

#define BUILDINGKIND_CASH_SHOP			(BYTE)100	// 유료화 상품 상점




///////////////////////////////////
// 건물 및 담당 NPC 정보
typedef struct _BUILDINGNPC {
	UINT		BuildingIndex;							// 건물(가게 등) 고유 번호
	char		BuildingName[SIZE_MAX_BUILDING_NAME];
	BYTE		BuildingKind;							// 건물 종류, BUILDINGKIND_XXX
	MapIndex_t	MapIndex;								// 속해 있는 맵 Index
	UINT		NPCIndex;								// 담당 NPC
	char		NPCName[SIZE_MAX_NPC_NAME];
	char		GreetingTalk[SIZE_MAX_BUILDING_NPC_TALK_STRING];	// 인사말
	MapIndex_t	OwnerCityMapIndex;						// 이 상점을 소유한 도시맵의 맵인덱스
	INT			OwnerOrderNumber;						// 도시맵이 소유가능한 상점들의 소유 순서
} BUILDINGNPC;	// 건물 및 담당 NPC 정보

//////////////////////////////////////////////////////////////////////
// 2010-06-15 by shcho&hslee 펫시스템 - 펫 타입 값
enum PARTNER_TYPE
{	// 파트너(팻) 타입 열거자.

	PARTNER_TYPE_NORMAL = 0,		// 일반형.

	PARTNER_TYPE_ATT = 1,			// 공격형.
	PARTNER_TYPE_DEF,				// 방어형.
	PARTNER_TYPE_BUFF,				// 버프형.
	PARTNER_TYPE_STORE,			// 개인상점형.

	MAX_PARTNER_TYPE

};


///////////////////////////////////
// 2010-06-15 by shcho&hslee 펫시스템 - 장착 슬롯 값들 Enum값으로 변경.
// 아이템 장착 위치(POS_XXX)
enum EQUIP_POS
{
	POS_NONE = -1,

	POS_PROW = 0,
	POS_PROWIN,
	POS_PROWOUT,
	POS_WINGIN,
	POS_WINGOUT,

	POS_CENTER,
	POS_REAR,
	POS_ACCESSORY_UNLIMITED,
	POS_ACCESSORY_TIME_LIMIT,
	POS_PET,

	MAX_EQUIP_POS,

	POS_INVALID_POSITION = 99

};

/*
// 아이템 장착 위치(POS_XXX)
#define POS_PROW						((BYTE)0)	// 레이더(선두 가운데)	--> 좌측 2번
#define POS_PROWIN						((BYTE)1)	// CPU 컴퓨터(중앙 좌측)	--> 우측 2번
#define POS_PROWOUT						((BYTE)2)	// 1형 무기(선두 좌측)	--> 좌측 1번
#define POS_WINGIN						((BYTE)3)	// 2006-07-20 by cmkwon, 이펙트 아이템 (중앙 위쪽), 마크 아이템
#define POS_WINGOUT						((BYTE)4)	// 2형 무기(선두 우측)	--> 우측 1번
#define POS_CENTER						((BYTE)5)	// 아머(중앙 가운데)	--> 좌측 4번
#define POS_REAR						((BYTE)6)	// 엔진(후미 가운데)	--> 우측 3번

// 2010-06-15 by shcho&hslee 펫시스템 - 선언 변경.
//#define POS_ATTACHMENT					((BYTE)7)	// 2006-03-30 by cmkwon, 무제한 악세사리 - 부착물(후미 우측-연료탱크|컨테이너계열), 지도자 광휘 --> 좌측 3번
#define POS_ACCESSORY_UNLIMITED			((BYTE)7)	// 2010-06-15 by shcho&hslee 펫시스템 - 무제한 악세사리

//#define POS_PET							((BYTE)8)	// 2006-03-30 by cmkwon, 시간제한 악세사리(후미 좌측)	--> 우측 4번
#define POS_ACCESSORY_TIME_LIMIT		((BYTE)8)	// 2010-06-15 by shcho&hslee 펫시스템 - 시간제한 악세사리
// End 2010-06-15 by shcho&hslee 펫시스템 - 선언 변경.


// 2010-06-15 by shcho&hslee 펫시스템 - 선언 변경.
#define POS_PET							((BYTE)9)	// 2010-06-15 by shcho&hslee 펫시스템 - 펫 아이템.

#define POS_INVALID_POSITION			((BYTE)99)	// 99,  invalid position
*/
// End 2010-06-15 by shcho&hslee 펫시스템 - 장착 슬롯 값들 Enum값으로 변경.



#define POS_ITEMWINDOW_OFFSET			((BYTE)100)	// 100, 이 번호부터 아이템창에 존재

// 2010-06-15 by shcho&hslee 펫시스템 - 아이탬 개수 변경. (펫) 추가. 계산. 9 -> MAX_EQUIP_POS
#define SIZE_MAX_POS					MAX_EQUIP_POS
//#define SIZE_MAX_POS					10			// 장착 아이템 slot의 개수
//#define SIZE_MAX_POS					9			// 장착 아이템 slot의 개수

#define IS_ATTACHABLE_POSITION(pos)		(SIZE_MAX_POS > (pos))							// 2009-10-22 by cmkwon, 시간 제한형류 아이템 시스템 정리 - 장착 가능 아이템 체크
#define IS_ATTACHABLE_ITEM(pItem)		(FALSE == IS_COUNTABLE_ITEM((pItem)->Kind) && IS_ATTACHABLE_POSITION((pItem)->Position))		// 2009-10-22 by cmkwon, 시간 제한형류 아이템 시스템 정리 - 장착 가능 아이템 체크

///////////////////////////////////
// WEAR - WEAR_XXX
#define WEAR_NOT_ATTACHED				0	// 미장착
#define WEAR_ATTACHED					1	// 장착

///////////////////////////////////////////////////////////////////////////////
// 2005-12-07 by cmkwon - ITEM_IN_XXX
#define ITEM_IN_CHARACTER				0	// 캐릭터인벤, 선택한 캐릭터 게임 시작시 한번만 호출됨
#define ITEM_IN_STORE					1	// 창고
#define ITEM_IN_GUILD_STORE             2   // 2006-09-14 by dhjin, 여단 창고 


///////////////////////////////////
// 아이템의 캐릭터 파라이터 - DES_XXX
#define DES_NULL							0		// 대상 파라미터가 없는 경우 사용
#define DES_ATTACK_PART						1		// 공격 파트
#define DES_DEFENSE_PART					2		// 방어 파트
#define DES_FUEL_PART						3		// 연료 파트
#define DES_SOUL_PART						4		// 감응 파트
#define DES_SHIELD_PART						5		// 쉴드 파트
#define DES_DODGE_PART						6		// 회피 파트
#define DES_BODYCONDITION					7		// 몸상태
#define DES_ENDURANCE_01					8		// 내구도 01
#define DES_ENDURANCE_02					9		// 내구도 02
#define DES_CHARGING_01						10		// 장탄수 01
#define DES_CHARGING_02						11		// 장탄수 02
#define DES_PROPENSITY						12		// 성향
#define DES_HP								13		// 히트포인트, MAX HP를 +VALUE만큼 올려줌
#define DES_DP								89		// 쉴드(DEFENSE)포인트
#define DES_SP								14		// 소울포인트
#define DES_EP								15		// 엔진포인트
#define DES_SPRECOVERY						16		// 소울포인트회복력
#define DES_HPRECOVERY						17		// 에너지포인트회복력
#define DES_MINATTACK_01					18		// (*) 최소 공격력 01
#define DES_MAXATTACK_01					71		// (*) 최대 공격력 01
#define DES_MINATTACK_02					19		// (*) 최소 공격력 02
#define DES_MAXATTACK_02					72		// (*) 최대 공격력 02
#define DES_ATTACKPROBABILITY_01			20		// 공격확률 01
#define DES_ATTACKPROBABILITY_02			21		// 공격확률 02
#define DES_DEFENSE_01						22		// (*) 방어력 01 (데미지 감소 확률) 20040622 추가
#define DES_DEFENSE_02						23		// (*) 방어력 02 (데미지 감소 확률) 20040622 추가
#define DES_DEFENSEPROBABILITY_01			24		// 방어확률 01 (회피 확률)
#define DES_DEFENSEPROBABILITY_02			25		// 방어확률 02 (회피 확률)
#define DES_SKILLPROBABILITY_01				26		// 스킬공격확률 01
#define DES_SKILLPROBABILITY_02				64		// 스킬공격확률 02
#define DES_FACTION_01						79		// 속성 01, check: 추가됨
#define DES_FACTION_02						80		// 속성 02, check: 추가됨
#define DES_FACTIONRESISTANCE_01			27		// 속성저항력 01
#define DES_FACTIONRESISTANCE_02			65		// 속성저항력 02
#define DES_SPEED							28		// (*) 이동속도, FIXER 등의 속도 감소량
#define DES_TRANSPORT						29		// 운반력
#define DES_MATERIAL						30		// 재질
#define DES_REATTACKTIME_01					31		// (*) 리어택타임 01 (- 증가)
#define DES_REATTACKTIME_02					32		// (*) 리어택타임 02 (- 증가)
#define DES_ABRASIONRATE_01					33		// 마모율 01
#define DES_ABRASIONRATE_02					34		// 마모율 02
#define DES_RANGE_01						35		// (*) 유효거리 01
#define DES_RANGE_02						36		// (*) 유효거리 02
#define DES_RANGEANGLE_01					37		// 유효각도 01
#define DES_RANGEANGLE_02					38		// 유효각도 02
#define DES_MULTITAGET_01					39		// 멀티타겟 01
#define DES_MULTITAGET_02					66		// 멀티타겟 02
#define DES_EXPLOSIONRANGE_01				40		// 폭발반경 01
#define DES_EXPLOSIONRANGE_02				67		// 폭발반경 02
#define DES_UNIT							41		// 유닛의 종류 (28 ~ 29이 같이 쓰여 유닛마다의 보정값으로 사용됨)
#define DES_REVISION						42		// 유닛의 보정값 (28 ~ 29이 같이 쓰여 유닛마다의 보정값으로 사용됨)
#define DES_FACTIONPROBABILITY_01			43		// 속성에 대한 방어확률 01
#define DES_FACTIONPROBABILITY_02			68		// 속성에 대한 방어확률 02
#define DES_SHOTNUM_01						44		// 일점사 당 발사 수 01
#define DES_SHOTNUM_02						69		// 일점사 당 발사 수 02
#define DES_MULTINUM_01						45		// 동시 발사 수 01
#define DES_MULTINUM_02						70		// 동시 발사 수 02
#define DES_ATTACKTIME_01					46		// 처음 공격 시의 타임 01 (- 증가)
#define DES_ATTACKTIME_02					47		// 처음 공격 시의 타임 02 (- 증가)
#define DES_TIME_01							48		// (*) 지속 시간 01, check: + -> *
#define DES_TIME_02							49		// (*) 지속 시간 02, check: + -> *
#define DES_OVERHITTIME_01					73		// (*) 오버힛회복시간 01, check: 추가됨
#define DES_OVERHITTIME_02					74		// (*) 오버힛회복시간 02, check: 추가됨
#define DES_UNITKIND						50		// 기체 업그레이드시 해당 기체
#define DES_ITEMKIND						51		// 아이템의 종류(ITEMKIND_XXX)
#define DES_SUMMON							52		// 몬스터 소환
#define DES_GRADUAL_HP_UP					53		// 에너지류, 현재 HP를 일정 시간(ITEM.Time에 저장)동안 점진적으로 VALUE만큼 올려줌, 중간에 부스터 켜거나 공격 받으면 cancel
#define DES_GRADUAL_DP_UP					81		// 에너지류, 현재 DP를 일정 시간(ITEM.Time에 저장)동안 점진적으로 VALUE만큼 올려줌, 중간에 부스터 켜거나 공격 받으면 cancel, check: 추가됨
#define DES_GRADUAL_SP_UP					54		// 에너지류, 현재 SP를 일정 시간(ITEM.Time에 저장)동안 점진적으로 VALUE만큼 올려줌, 중간에 뭐(?)들어오면 cancel
#define DES_GRADUAL_EP_UP					55		// 에너지류, 현재 EP를 일정 시간(ITEM.Time에 저장)동안 점진적으로 VALUE만큼 올려줌, 중간에 뭐(?)들어오면 cancel
#define DES_IN_TIME_HP_UP					56		// 에너지류, 현재 HP를 일정 시간(ITEM.Time에 저장)이 지난 후 VALUE만큼 올려줌
#define DES_IN_TIME_DP_UP					82		// 에너지류, 현재 DP를 일정 시간(ITEM.Time에 저장)이 지난 후 VALUE만큼 올려줌, check: 추가됨
#define DES_IN_TIME_SP_UP					57		// 에너지류, 현재 SP를 일정 시간(ITEM.Time에 저장)이 지난 후 VALUE만큼 올려줌
#define DES_IN_TIME_EP_UP					58		// 에너지류, 현재 EP를 일정 시간(ITEM.Time에 저장)이 지난 후 VALUE만큼 올려줌
#define DES_IMMEDIATE_HP_UP					59		// 에너지류, 현재 HP를 즉시 VALUE만큼 올려줌
#define DES_IMMEDIATE_DP_UP					83		// 에너지류, 현재 DP를 즉시 VALUE만큼 올려줌, check: 추가됨
#define DES_IMMEDIATE_SP_UP					60		// 에너지류, 현재 SP를 즉시 VALUE만큼 올려줌
#define DES_IMMEDIATE_EP_UP					61		// 에너지류, 현재 EP를 즉시 VALUE만큼 올려줌
#define DES_GROUNDMODE						62		// 폭격모드
#define DES_SIEGEMODE						63		// 시즈모드
#define DES_WEIGHT_01						75		// (*) 무게 01, check: 추가됨
#define DES_WEIGHT_02						76		// (*) 무게 02, check: 추가됨
#define DES_BULLET_01						77		// (*) 1형 총알 01, 2005-11-02 by cmkwon 빔소모초알량을 변경함
#define DES_BULLET_02						78		// (*) 2형 총알 02, 2005-11-02 by cmkwon 빔소모초알량을 변경함
#define DES_PRIMARY_WEAPON					84		// 1형 무기, 범용빔
#define DES_SECONDARY_WEAPON				85		// 2형 무기, 범용
#define DES_ALL_WEAPON						86		// 1,2형 무기 모두, 범용
#define DES_CRITICALHITRATE_01				87		// (*)크리티컬 확률 20040622 추가
#define DES_CRITICALHITRATE_02				88		// (*)크리티컬 확률 20040622 추가
#define DES_WARP							90		// 도시워프 아이템용
#define DES_REACTION_RANGE					91		// ITEM의 ReactionRange 변경
#define DES_RARE_FIX_NONE					92		// 접두사, 접미사 모두 없음, ITEMKIND_GAMEBLE의 DestParam1에 설정
#define DES_RARE_FIX_PREFIX					93		// 접두사, ITEMKIND_GAMEBLE의 DestParam1에 설정
#define DES_RARE_FIX_SUFFIX					94		// 접미사, ITEMKIND_GAMEBLE의 DestParam1에 설정
#define DES_RARE_FIX_BOTH					95		// 접두사, 접미사 모두 포함, ITEMKIND_GAMEBLE의 DestParam1에 설정
#define DES_REQ_MIN_LEVEL					96		// 아이템장착 요구 MinLevel을 낮춘다
#define DES_REQ_MAX_LEVEL					97		// 아이템장착 요구 MaxLevel을 낮춘다
#define DES_WARP_OUTPOST					98		// 2007-09-05 by dhjin, 전진기지 도시워프 아이템용
#define DES_CHAT_BLOCK						99		// 2008-12-30 by cmkwon, 지도자 채팅 제한 카드 구현 - 

#define DES_CASH_STAT_ALL_INITIALIZE		100		// 유료 모든 스탯 초기화 아이템
//#define DES_CASH_STAT_HALF_INITIALIZE		101		// (구현 미확정)유료 50% 스탯 초기화 아이템
#define DES_CASH_STAT_PART_INITIALIZE		102		// 유료 부분 스탯 초기화 아이템
#define DES_RARE_FIX_PREFIX_INITIALIZE		103		// 접두사 초기화, ITEMKIND_GAMEBLE의 DestParam1에 설정
#define DES_RARE_FIX_SUFFIX_INITIALIZE		104		// 접미사 초기화, ITEMKIND_GAMEBLE의 DestParam1에 설정
#define DES_ENCHANT_INITIALIZE				105		// 2007-04-03 by cmkwon, 인챈트 초기화, ITEMKIND_ENCHANT의 DestParam1에 설정

#define DES_CASH_STEALTH					108		// 스텔스 아이템
#define DES_CASH_HP_AND_DP_UP				109		// HP and DP UP 아이템
#define DES_CASH_GUILD_ALL_MEMBERS_SUMMON	110		// 모든 여단원 소환 - 여단장만 사용가능
#define DES_CASH_GUILD_MEMBER_SUMMON		111		// 여단원 1명 소환 - 여단장만 사용가능
#define DES_CASH_NORMAL_RESTORE				112		// 일반 부활 카드 - 사
#define DES_CASH_SUPER_RESTORE				113		// 슈퍼 부활 카드
#define DES_CASH_GUILD						114		// 일반/고급 여단 카드
#define DES_CASH_MONSTER_SUMMON				115		// 몬스터 소환 카드
#define DES_CASH_CHANGE_CHARACTERNAME		116		// 캐릭터명 변경 카드
#define DES_CASH_SKILL_INITIALIZE			117		// 스킬 초기화 카드
#define DES_CASH_CHANGE_PILOTFACE			118		// 얼굴 변경 카드
#define DES_CASH_CRACKER_CARD				119		// 종합 폭죽 카드


///////////////////////////////////////////////////////////////////////////////
// 2005-11-21 by cmkwon, 새로 추가된 DesParam
#define DES_SKILL_REDUCE_SHIELD_DAMAGE		121		// 쉴드에 가는 데미지를 줄여준다.
#define DES_SKILL_INVINCIBLE				122		// 무적 상태
#define DES_SKILL_BIG_BOOM					123		// 		미구현 - 자신의 HP를 모두 소모하여 주변에게 데미지를 입히고, 자신은 폭발한다.
#define DES_SKILL_HALLUCINATION				124		// 체프 사출.
#define DES_SKILL_RANGEDOWN_01				125		// 		미구현 - 적의 기본무기 사거리를 줄인다.
#define DES_SKILL_RANGEDOWN_02				126		// 		미구현 - 적의 고급 무기 사거리를 줄인다.
#define DES_SKILL_PROHIBITION_01			127		// 		미구현 - 적의 기본 무기 사용을 금지시킨다.
#define DES_SKILL_PROHIBITION_02			128		// 		미구현 - 적의 고급 무기 사용을 금지시킨다.
#define DES_ATTACK_RANGE_01					129		// 레이다의 기본 무기 조준 거리를 증가시킨다.(*)
#define DES_ATTACK_RANGE_02					130		// 레이다의 고급 무기 조준 거리를 증가시킨다.(*)
#define DES_INVISIBLE						131		//	스텔스 모드로서 적에게 보이지 않으며, 레이다에도 잡히지 않는다. 자신도 공격이 되지 않는다.
// 2005-12-02 by cmkwon, 154, 155, 156으로 나눔#define DES_SKILL_HYPERMOVING				132		// 유닛의 전체 이동속도가 좋아지고, 부스터 사용이 되지 않는다.(*)
#define DES_SKILL_DEFENSE_01				133		// 		미구현 - 적의 기본방어력을 떨어뜨린다.(*)
#define DES_SKILL_DEFENSE_02				134		// 		미구현 - 적의 고급방어력을 떨어뜨린다.(*)
#define DES_SKILL_FREEZINGBODY				135		// 		미구현 - 적의 HP,쉴드 회복을 불가능하게 만든다. 수리킷,쉴드킷,스킬회복(전체)이 안된다.
#define DES_SKILL_REVERSECONTROL			136		// 2010-03-31 by dhjin, 인피니티(기지방어) -	// 		미구현 - 적의 움직임을 반대로 움직이게 한다.
#define DES_SKILL_GRADUAL_HPSHIELD_DOWN		137		// 		미구현 - 적의 HP,쉴드를 점차 감소시킨다.
#define DES_SKILL_SLOWMOVING				138		// 적의 움직임을 둔하게 한다.(최대이동 속도, 부스터 속도, 이동 각도, 부스터 이동 각도)(*)
#define DES_SKILL_BOOSTEROFF				139		// 		미구현 - 적의 부스터 사용을 금지시킨다.
#define DES_SKILL_COLLISIONDAMAGE_DOWN		140		// 배경 오브젝트,바닥 충돌시 데미지를 감소시킨다.
//#define DES_SKILL_CAMOUFLAGE				141		// 		미구현 - 위장하여 적의 시야에 보이지 않는다. 타겟에는 잡힌다.
#define DES_SKILL_RANDOMTELEPORT			142		// 		미구현 - 같은 맵에서 랜덤하게 이동한다.
#define DES_SKILL_ATTACK_ALL				143		// 		미구현 - 전체 공격 스킬
#define DES_SKILL_SCANNING					144		// Invisible 상태의 유저를 볼 수 있도록 한다
#define DES_SKILL_REVERSEENGINE				145		// 엔진이 후진이 가능하게 한다.
#define DES_SKILL_LOCKDOWN					146		// 		미구현 - 상대방을 일시 정지시킨다.(전진,좌우선회,부스터 정지, 단, 공격기능은 가능)
#define DES_SKILL_STEALSP					147		// 		미구현 - 상대방의 SP를 일정량 뻇아온다.
#define DES_SKILL_SMARTSP					148		// 자신이 사용하는 모든 스킬의 사용량을 줄여준다.(*)
#define DES_SKILL_SUMMON_FORMATION_MEMBER	149		// 편대원 중 1명을 소환한다.
#define DES_SKILL_CANCEL_MAGIC				150		// 		미구현 - 적의 버프 스킬을 모두 해제시킨다.
#define DES_SKILL_RANDOM_CANCEL				151		// 		미구현 - 타겟의 디버프 스킬을 하나 랜덤하게 해제한다.
#define DES_SKILL_STOPMAGIC					152		// 		미구현 - 적의 스킬을 일정시간 사용금지시킨다.
#define DES_SKILL_CANCELALL					153		// 		미구현 - 대상의 버프 스킬을 모두 해제한다.
#define DES_SKILL_REACTIONSPEED				154		// (*)하이퍼 무빙(반응속도)
#define DES_SKILL_ENGINEANGLE				155		// (*)하이퍼 무빙(선회각)
#define DES_SKILL_ENGINEBOOSTERANGLE		156		// (*)하이퍼 무빙(부스터 선회각)

// 2006-03-30 by cmkwon
#define DES_DROP_EXP						157		// 경험치, 프리미엄과 중첩 불가
#define DES_DROP_SPI						158		// SPI, 프리미엄과 중첩 불가
#define DES_DROP_ITEM						159		// 아이템 드랍율, 프리미엄과 중첩 불가
#define DES_HP_REPAIR_RATE_FLIGHTING		160		// 비행시 HP 회복율
#define DES_DP_REPAIR_RATE					161		// DP 회복율
#define DES_SP_REPAIR_RATE					162		// SP 회복율

// 2006-07-26 by cmkwon
#define DES_BAZAAR_SELL						163		// 2006-07-26 by cmkwon, 개인 판매 상점
#define DES_BAZAAR_BUY						164		// 2006-07-26 by cmkwon, 개인 구매 상점

// 2006-08-14 by dhjin
#define DES_KILLMARK_EXP					165		// 2006-08-14 by dhjin, 킬마크 경험치

// 2006-10-11 by cmkwon
#define DES_HYPER_BOOSTER					166		// 2006-10-11 by cmkwon, 부스터 게이지 떨어지지 않음

// 2006-11-17 by dhjin, 2차 스킬로 인해 추가된 사항
#define DES_SKILL_CHAFF_HP					167		// 2006-11-17 by dhjin, 체프의 HP
#define DES_SKILL_AIR_BOMBING				168		// 2006-11-17 by dhjin, 공중 폭격
#define DES_SKILL_NO_WARNING				169		// 2006-11-17 by dhjin, 타기어에 스킬 사용시, 해당기어는 워닝음과 레이더 점멸이 울리지 않게 된다
#define DES_SKILL_ROLLING_TIME				170		// 2006-11-17 by dhjin, 30초동안 롤링 재사용 시간이 없다.
#define DES_SKILL_FULL_RECOVERY				171		// 2006-11-17 by dhjin, 기체의 HP, 쉴드, 연료, SP를 완전회복한다.
#define DES_SKILL_CAMOUFLAGE				172		// 2006-11-17 by dhjin, A기어의 위장 스킬
#define DES_SKILL_BARRIER					173		// 2006-11-17 by dhjin, A기어의 고급무기에 대한 무적 스킬
#define DES_SKILL_HYPERSHOT					174		// 2006-11-17 by dhjin, A기어의 기본무기 차징샷, 스플래쉬 데미지는 Range
#define DES_SKILL_SHIELD_PARALYZE			175		// 2006-11-17 by dhjin, A기어의 쉴드마비 스킬, 상대기어의 쉴드 회복율을 0으로 만든다.

#define DES_WARHEAD_SPEED					176		// 2007-06-11 by cmkwon, 탄두의 속도
#define DES_CHAT_ALL_INFLUENCE				177		// 2007-08-09 by cmkwon, 모든 세력에 채팅 전송하기 - desparam 추가, 유료아이템

// 2008-09-22 by dhjin, 신규 인첸트
#define DES_ENGINE_BOOSTER_TIME_UP			178		// 2008-09-22 by dhjin, 부스터 시간 증가
#define DES_ENGINE_MAX_SPEED_UP				179		// 2008-09-22 by dhjin, 엔진 일반속도(최대) 증가
#define DES_ENGINE_MIN_SPEED_UP				180		// 2008-09-22 by dhjin, 엔진 일반속도(최소) 증가
#define DES_ENGINE_BOOSTER_SPEED_UP			181		// 2008-09-22 by dhjin, 엔진 부스터속도 증가
#define DES_ENGINE_GROUND_SPEED_UP			182		// 2008-09-22 by dhjin, 엔진 지상속도 증가
#define DES_RADAR_OBJECT_DETECT_RANGE		183		// 2008-09-22 by dhjin, 레이더 물체 감지 반경
#define DES_PIERCE_UP_01					184		// 2008-09-22 by dhjin, 기본무기 피어스율 증가 카드
#define DES_PIERCE_UP_02					185		// 2008-09-22 by dhjin, 고급무기 피어스율 증가 카드
#define DES_ENGINE_ANGLE_UP                 186		// 2008-09-30 by dhjin, 엔진 회전각 증가 카드
#define DES_ENGINE_BOOSTERANGLE_UP          187		// 2008-09-30 by dhjin, 엔진 부스터 회전각 증가 카드

// 2009-01-05 by dhjin, 미션마스터 - 편대 버프 아이템 추가 
#define DES_ITEM_BUFF_INFLUENCE				188
#define DES_ITEM_BUFF_PARTY					189

// 2009-01-19 by dhjin, 인첸트 확률 증가, 10인첸 파방 카드 - 인첸트 확률 증가 카드
#define DES_ENCHANT_PREVENTION_DELETE_USE_ENCHANT	190		// 사용 하기 위한 아이템의 보유인챈트 카운트 설정
#define DES_ENCHANT_PREVENTION_DELETE_SAVE_ENCHANT	191		// 인챈트 실패시 남기는 인챈트 카운트 설정
#define DES_ENCHANT_INCREASE_PROBABILITY			192		// 인챈트 카드 확률 증가분 설정

///////////////////////////////////////////////////////////////////////////////
// 2009-08-03 by cmkwon, EP3-4 편대 대형 스킬 구현 - DES_ 추가
#define DES_SKILL_DAMAGE_DISTRIBUTION				193		// 데미지를 편대원에게 분산(분배) 처리 한다.

///////////////////////////////////////////////////////////////////////////////
// 2009-08-26 by cmkwon, 그래픽 리소스 변경 시스템 구현 - 
#define DES_SHAPE_ITEM								194		// 조합시 소스 아이템의 ShapeItemNum을 변경 할 Item, LinkItem을 사용
#define DES_EFFECT_ITEM								195		// 조합시 소스 아이템의 EffectItemNum을 변경 할 Item, 해당 ItemNum을 사용 

///////////////////////////////////////////////////////////////////////////////
// 2009-09-23 by cmkwon, 필드창고 캐쉬 아이템 구현 - 
#define DES_FIELD_STORE								196		// 필드창고

///////////////////////////////////////////////////////////////////////////////
// 2009-10-01 by cmkwon, 그래픽 리소스 변경 관련 초기화 기능 구현 - 
#define DES_INIT_SHAPE_ITEM							197		// 조합시 소스 아이템의 ShapeItemNum을 초기화 할 Item
#define DES_INIT_EFFECT_ITEM						198		// 조합시 소스 아이템의 EffectItemNum을 초기화 할 Item

///////////////////////////////////////////////////////////////////////////////
// 2009-11-02 by cmkwon, 캐쉬(인벤/창고 확장) 아이템 추가 구현 - DES_XXX 추가
#define DES_INCREASE_INVENTORY_SPACE				199		// 캐릭터 인벤토리 증가
#define DES_INCREASE_STORE_SPACE					200		// 캐릭터 창고 증가

////////////////////////////////////////////////////////////////////////////////
// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 
#define DES_ITEM_RESISTANCE							201		// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 저항 아이템 사용 체크 
#define DES_ITEM_ADDATTACK							202		// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 절대값 타격치 아이템 사용 체크 
#define DES_ITEM_IGNOREDEFENCE						203		// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 방어력 무시 아이템 사용 체크
#define DES_ITEM_IGNOREAVOID						204		// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 회피력 무시 아이템 사용 체크
#define DES_ITEM_REDUCEDAMAGE						205		// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 데미지 절대값 감소 아이템 사용 체크
#define DES_ITEM_ADDATTACK_SEC						206		// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 절대값 타격치 아이템 고급무기용(기무와 분류)
#define DES_ITEM_ONCE_RESISTANCE					207		// 2009-09-09 ~ 2010-01-19 by dhjin, 인피니티 - 한 번만 저항하고 없어지는 저항 아이템 추가
#define DES_SKILL_MON_SILENCE_PRIMARY				210		// 몬스터 사일런스 스킬 (1형무기 적용)
#define DES_SKILL_MON_SILENCE_SECOND				211		// 몬스터 사일런스 스킬 (2형무기 적용)
#define DES_SKILL_MON_FREEZE_HP						212		// 몬스터 프리즈 스킬 HP 회복 불가  
#define DES_SKILL_MON_FREEZE_DP						213		// 몬스터 프리즈 스킬 DP 회복 불가
#define DES_SKILL_MON_FREEZE_SP						214		// 몬스터 프리즈 스킬 SP 회복 불가
#define DES_SKILL_MON_HOLD							215		// 몬스터 홀드 스킬
#define DES_SKILL_MON_STEALING						216		// 몬스터 스틸링 스킬 
#define DES_SKILL_MON_DRAIN							217		// 몬스터 드레인 스킬
#define DES_SKILL_RELEASE							218		// M기어 릴리즈 스킬
#define DES_SKILL_MON_SILENCE_SKILL					219		// 몬스터 사일런스 스킬 (스킬 적용)

///////////////////////////////////////////////////////////////////////////////
// 2009-09-09 ~ 2010-02-10 by dhjin, 인피니티 - 발동류장착아이템
#define DES_PAIR_DRAIN_1_RATE						220		// 드레인 발동 확률
#define DES_PAIR_DRAIN_2_HP_DP_UP_RATE				221		// 드레인 회복량 HP->DP 회복 (데미지의 %)
#define DES_ANTI_DRAIN_RATE							222		// 드레인 발동 저항 확률
#define DES_PAIR_REFLECTION_1_RATE					223		// 데미지 반사 확률
#define DES_PAIR_REFLECTION_2_DAMAGE_RATE			224		// 반사 데미지량 %
#define DES_ANTI_REFLECTION_RATE					225		// 데미지 반사 저항 확률

///////////////////////////////////////////////////////////////////////////////
// 2010-03-31 by dhjin, 인피니티(기지방어) - 
#define DES_BLIND									226
#define DES_SUPERINTEND								227
#define DES_IMMEDIATE_HP_OR_DP_UP					228		// HP를 먼저 채우고 그 이후에 DP를 채운다.
#define DES_HIT_INVOKE_SKILL						229		// 명중시 해당 데스파람값에 스킬을 시전한다.
#define DES_TIME_BOMB								230

///////////////////////////////////////////////////////////////////////////////
// 2010-03-18 by cmkwon, 몬스터변신 구현 - 
#define DES_TRANSFORM_TO_MONSTER					231		// ParamValue에 MonsterUnitKind 입력

///////////////////////////////////////////////////////////////////////////////
// 2010-03-23 by cmkwon, 인피니티 입장 캐쉬 아이템 구현 - 1회만 추가 입장 가능
#define DES_INFINITY_REENTRY_TICKET					232		// 현재는 ParamValue는 사용하지 않음

///////////////////////////////////////////////////////////////////////////////
// 2010-04-05 by cmkwon, 몬스터변신관련 해제 카드 구현 - 
#define DES_TRANSFORM_TO_GEAR						233		// 현재는 ParamValue는 사용하지 않음.

///////////////////////////////////////////////////////////////////////////////
// 2010-05-18 by cmkwon, WarPoint 증가 아이템 구현(일본요청) - 
#define DES_PLUS_WARPOINT_RATE						234		// ParamValue: WarPoint 증가 Rate

///////////////////////////////////////////////////////////////////////////////
// 2010-06-01 by shcho, PC방 권한 획득(캐쉬) 아이템 - 
#define DES_PCROOM_USE_CARD							235		//PC방 플래그를 TRUE로 변환 시킨다.

///////////////////////////////////////////////////////////////////////////////
// 2010-08-26 by shcho&jsKim, 밤 아이템 구현 -
#define DES_MAX_SP_UP								236		// SP의 최대치를 증가시킨다.

///////////////////////////////////////////////////////////////////////////////
// 2010-08-27 by shcho&&jskim, WARPOINT 증가 아이템 구현
#define DES_WAR_POINT_UP							237		// WARPOINT 증가

///////////////////////////////////////////////////////////////////////////////
// 2010-11-30 by shcho, 레어아이템 드랍확률 증가 아이템 구현
#define DES_RARE_ITEM_DROP_RATE						238		// 레어 아이템 드랍확률 증가

///////////////////////////////////////////////////////////////////////////////
// 2010-12-21 by jskim, 마을 이동 속도 증가 아이템 구현
#define DES_RARE_ITEM_PARTNER_SPEED					239		// 마을 이동 스피드 증가

///////////////////////////////////////////////////////////////////////////////
// 2010-12-21 by jskim, 파트너 데미지 증가 아이템 구현
#define DES_RARE_ITEM_PARTNER_DAMAGE				240		// 파트너 데미지 증가

///////////////////////////////////////////////////////////////////////////////
// 2010-12-21 by jskim, HP, DP 키트 적용량 증가 아이템 구현
#define DES_RARE_ITEM_HPDP							241		// HP DP 키트 적용량

// start 2011-05-02 by hskim, 인피니티 3차 - 시네마 관련 기능 추가 - 특정 좌표에 소환
#define DES_SUMMON_POSITION_X						242		// 소환시 위치 변경 (상대값)
#define DES_SUMMON_POSITION_Y						243		// 소환시 위치 변경 (상대값)
#define DES_SUMMON_POSITION_Z						244		// 소환시 위치 변경 (상대값)
// end 2011-05-02 by hskim, 인피니티 3차 - 시네마 관련 기능 추가 - 특정 좌표에 소환

// 2009-04-21 by cmkwon, ITEM에 DesParam 필드 개수 8개로 늘리기 - ITEM::IsExistDesParam() 함수로 통합함
//#define IS_EXIST_DES_PARAM(pItemInfo, des)	((des) == (pItemInfo)->DestParameter1 || (des) == (pItemInfo)->DestParameter2 \
//												|| (des) == (pItemInfo)->DestParameter3 || (des) == (pItemInfo)->DestParameter4)

// 2008-10-21 by cmkwon, 마지막에 선택된 레어는 다시 나오지 않게 수정 - 
// 2009-04-21 by cmkwon, ITEM에 DesParam 필드 개수 8개로 늘리기 - 
//#define IS_DES_RARE_FIX_PREFIX(pItemInfo)	( DES_RARE_FIX_PREFIX == (pItemInfo)->DestParameter1 )
//#define IS_DES_RARE_FIX_SUFFIX(pItemInfo)	( DES_RARE_FIX_SUFFIX == (pItemInfo)->DestParameter1 )
#define IS_DES_RARE_FIX_PREFIX(pItemInfo)	( DES_RARE_FIX_PREFIX == (pItemInfo)->ArrDestParameter[0] )
#define IS_DES_RARE_FIX_SUFFIX(pItemInfo)	( DES_RARE_FIX_SUFFIX == (pItemInfo)->ArrDestParameter[0] )

// 2006-07-26 by cmkwon
// 2009-04-21 by cmkwon, ITEM에 DesParam 필드 개수 8개로 늘리기 - 아래와 같이 수정 함.
//#define IS_BAZAAR_SKILL(pItemInfo)			(IS_EXIST_DES_PARAM((pItemInfo), DES_BAZAAR_SELL) || IS_EXIST_DES_PARAM((pItemInfo), DES_BAZAAR_BUY))
#define IS_BAZAAR_SKILL(pItemInfo)			((pItemInfo)->IsExistDesParam(DES_BAZAAR_SELL) || (pItemInfo)->IsExistDesParam(DES_BAZAAR_BUY))

// 2006-08-14 by dhjin
// 2009-04-21 by cmkwon, ITEM에 DesParam 필드 개수 8개로 늘리기 - 
//#define IS_KILLMARK_EXP(pItemInfo)			(DES_KILLMARK_EXP==(pItemInfo)->DestParameter1)
#define IS_KILLMARK_EXP(pItemInfo)			(DES_KILLMARK_EXP==(pItemInfo)->ArrDestParameter[0])


///////////////////////////////////////////////////////////////////////////////
// 2009-04-21 by cmkwon, ITEM에 DesParam 필드 개수 8개로 늘리기 - 
#define SIZE_MAX_DESPARAM_COUNT_IN_ITEM			8


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// 2005-12-21 by cmkwon, 메모리핵 체크 타입 정의
#define HACK_CHECK_TYPE_SHOTNUM					1		// 2005-12-20 by cmkwon
#define HACK_CHECK_TYPE_MULTINUM				2		// 2005-12-20 by cmkwon
#define HACK_CHECK_TYPE_REATTACKTIME			3		// 2005-12-20 by cmkwon
#define HACK_CHECK_TYPE_REPEATTIME				4		// 2005-12-20 by cmkwon
#define HACK_CHECK_TYPE_TIME					5		// 2005-12-20 by cmkwon
#define HACK_CHECK_TYPE_RANGEANGLE				6		// 2005-12-20 by cmkwon
#define HACK_CHECK_TYPE_BOOSTERANGLE			7		// 2005-12-20 by cmkwon
#define HACK_CHECK_TYPE_ORBITTYPE				8		// 2005-12-20 by cmkwon
#define HACK_CHECK_TYPE_ABILITYMIN				9		// 2005-12-20 by cmkwon
#define HACK_CHECK_TYPE_ABILITYMAX				10		// 2005-12-20 by cmkwon
#define HACK_CHECK_TYPE_SPEEDPENALTY			11		// 2005-12-20 by cmkwon
#define HACK_CHECK_TYPE_RANGE					12		// 2005-12-20 by cmkwon
#define HACK_CHECK_TYPE_TRANSPORT				13		// 2005-12-20 by cmkwon
#define HACK_CHECK_TYPE_TOTALWEIGHT				14		// 2005-12-20 by cmkwon
#define HACK_CHECK_TYPE_POSITION				15		// 2005-12-20 by cmkwon
#define HACK_CHECK_TYPE_MAP_CHECK_SUM			16		// 2007-04-10 by cmkwon
#define HACK_CHECK_TYPE_RESOBJ_CHECK_SUM		17		// 2007-05-28 by cmkwon



///////////////////////////////////
// 아이템 재질
#define MAT_MATERIAL01						0	// 재질1
#define MAT_MATERIAL02						1	// 재질2
#define MAT_MATERIAL03						2	// 재질3
#define MAT_MATERIAL04						3	// 재질4
#define MAT_MATERIAL05						4	// 재질5

///////////////////////////////////////////////////////////////////////////////
// 보급 상점에서 회복시 필요한 SPI
#define COST_HP_REPAIR_PER_1HP				5		// 1HP 당 회복 비용
#define COST_DP_REPAIR_PER_1DP				3		// 1DP 당 회복 비용 - 쉴드
#define COST_EP_REPAIR_PER_1EP				1		// 1EP 당 회복 비용 - 연료
#define COST_SP_REPAIR_PER_1SP				200		// 1SP 당 회복 비용 - 

///////////////////////////////////
// Skills

/******************************************************************************
//  BEGIN - Deprecated - 2003. 04. 21.

// 구조체의 ItemInfo(skill)을 이용한 세팅에 다음의 종류와 레벨을 세팅한다
// skill & item 의 RequiredLevel field에 사용한다
#define LEVEL_TRANSMITTER			0x00	// 통신기 장착, 메신저 사용가능(레벨1)
#define LEVEL_BEAM					0x01	// 빔계열 장착(레벨3)
#define LEVEL_ROCKET				0x02	// 로켓 장착(레벨5)
#define LEVEL_PARTY					0x03	// 파티 생성,가입(레벨6)
#define LEVEL_PICKING				0x04	// 자원채취(레벨10)
#define LEVEL_BANK					0x05	// 은행사용가능(레벨11)
#define LEVEL_SALE					0x06	// 아이템 자동판매가능(레벨12)
#define LEVEL_TALKROOM				0x07	// 대화방 개설(레벨13)
#define LEVEL_GUIDED				0x08	// 유도탄계열 장착(레벨15)
#define LEVEL_PET					0x09	// 펫 사용가능(레벨20)
#define LEVEL_GUILD					0x0A	// 길드 생성(레벨30)
#define LEVEL_MAKING				0x0B	// 아이템 제조 능력(레벨50)
// END - Deprecated - 2003. 04. 21.
******************************************************************************/

///////////////////////////////////
// Skill - BaseNum & Macro

/* 스킬의 ItemNum 및 BaseNum을 만드는 법
	- ItemNum: 총 7자리 정수, DB에 저장
		1,2	자리: 78
		3	자리: UnitKind(BT:0, OT: 1, DT: 2, ST: 3)
		4	자리: Skill 종류(공격: 0, 방어: 1, 컨트롤: 2, 속성|보조: 3)
		5,6	자리: 스킬 번호
		7	자리: Skill Level
	- BaseNum: ItemNum에서 7번째 자리를 0으로 바꾼다, DB에 저장 안됨
*/

#define SKILL_BASE_NUM(x)	((int)x/10)*10						// 스킬의 ItemNum에서 BaseNum을 구함
#define SKILL_LEVEL(x)		(x - ((int)x/10)*10)				// 스킬의 ItemNum에서 SkillLevel을 구함
#define SKILL_NUMBER(x)		((int)x/10) - ((int)x/1000)*100		// 스킬 번호
#define SKILL_KIND(x)		((int)x/1000) - ((int)x/10000)*10	// Skill 종류(공격: 0, 방어: 1, 컨트롤: 2, 속성|보조: 3)
#define SKILL_UNIT_KIND(x)	((int)x/10000) - ((int)x/100000)*10	// UnitKind(BT:0, OT: 1, DT: 2, ST: 3)

#define SKILL_KIND_ATTACK		0				// 공격
#define SKILL_KIND_DEFENSE		1				// 방어
#define SKILL_KIND_CONTROL		2				// 컨트롤
#define SKILL_KIND_ATTRIBUTE	3				// 속성/보조
//#define SKILL_KIND_SUPPORT		4

///////////////////////////////////////////////////////////////////////////////
// 2005-11-22 by cmkwon, 스킬 BaseNum 정의
// B-Gear
#define BGEAR_SKILL_BASENUM_BACKMOVEMACH		7802010	// 컨트롤	- 백무브마하
#define BGEAR_SKILL_BASENUM_TURNAROUND			7802020	// 컨트롤	- 턴어라운드	
#define BGEAR_SKILL_BASENUM_GROUNDBOMBINGMODE	7800040	// 토글		- 지상폭격모드
#define BGEAR_SKILL_BASENUM_AIRBOMBINGMODE		7800070	// 토글		- 공중폭격모드
#define BGEAR_SKILL_BASENUM_INVISIBLE			7803030	// 토글		- 인비지블
#define BGEAR_SKILL_BASENUM_BIG_BOOM			7803040	// 액티브	- 빅붐

// M-Gear
#define MGEAR_SKILL_BASENUM_SMARTSP				7813020	// 시간		- 스마트SP
#define MGEAR_SKILL_BASENUM_CALLOFHERO			7813030	// 클릭		- 콜오브히어로
#define MGEAR_SKILL_BASENUM_REVERSEENGINE		7812020	// 토글		- 리버스엔진
#define MGEAR_SKILL_BASENUM_INVICIBLE			7811100	// 액티브 	- 무적
#define MGEAR_SKILL_BASENUM_SCANNING			7813060	// 버프 	- 스캔

// A-Gear
#define AGEAR_SKILL_BASENUM_SIEGEMODE			7820050	// 토글		- 시즈모드
#define AGEAR_SKILL_BASENUM_SIEGEDEFENSEMODE	7821040	// 토글		- 시즈디펜스모드
#define AGEAR_SKILL_BASENUM_GROUNDACCELERATOR	7822010	// 토글 	- 그라운드엑셀레이터
#define AGEAR_SKILL_BASENUM_AIRSIEGEMODE    	7820060	// 토글 	- 에어시즈모드
#define AGEAR_SKILL_BASENUM_CAMOUFLAGE	    	7823040	// 토글 	- 위장

// I-Gear
#define IGEAR_SKILL_BASENUM_BACKMOVEMACH		7832010	// 컨트롤	- 백무브마하
#define IGEAR_SKILL_BASENUM_TURNAROUND			7832020	// 컨트롤	- 턴어라운드
#define IGEAR_SKILL_BASENUM_SILENCE				7833040	// 액티브	- 침묵
#define IGEAR_SKILL_BASENUM_FRENZY				7830030	// 액티브	- 프렌지
#define IGEAR_SKILL_BASENUM_BERSERKER			7833050	// 액티브	- 폭주

// 2005-11-22 by cmkwon, 임시용으로 현재 클라이언트에서 사용 중 이어서 정의 함, 향후 제거해야함
#define SMART_SPEED								7812020
#define FLASH_ACCELERATOR						7822030

// 2005-11-22 by cmkwon
//// BT
//#define BT_SKILL_QUICKTURN			7802010	// 클릭형
//#define BT_SKILL_REVERSETURN		7802020	// 클릭형
//#define BT_SKILL_COPTERFLIGHT		7802030	// 클릭형
//
//// OT
//#define OT_SKILL_GRENADEMASTERY		7810010	// 지속형
//#define OT_SKILL_LAUNCHERMASTERY	7810020	// 지속형
//#define OT_SKILL_DUALSHOT			7810030	// 시간형
//#define OT_SKILL_SCORPING			7810040	// 시간형
//#define OT_SKILL_FRENZY				7810050	// 시간형
//#define OT_SKILL_CONVERGINGSHOT		7810060	// 시간형
//#define OT_SKILL_BUNDLEMASTERY		7810070	// 지속형
//#define OT_SKILL_OVERRADAR			7810080	// 시간형
//#define OT_SKILL_CRAZYSHOT			7810090	// 시간형
//#define OT_SKILL_EYEFORANEYE		7810100	// 시간형
//#define OT_SKILL_BURSTSHOT			7810110	// 시간형
//#define OT_SKILL_FLYINGWORM			7811010	// 시간형
//#define OT_SKILL_DIFFUSION			7811020	// 시간형
//#define OT_SKILL_PARALLELMOVEMENT	7812030	// 클릭형
//#define OT_SKILL_SCREWPUSHING		7812040	// 클릭형
//#define OT_SKILL_OVERRISING			7812050	// 클릭형
////#define OT_SKILL_NONAME			7812060	// 시간형
//
//// DT
//#define DT_SKILL_CANNONMASTERY		7820010	// 지속형
//#define DT_SKILL_MASSDRIVEMASTERY	7820020	// 지속형
//#define DT_SKILL_CHARGINGSHOT		7820030	// 시간형
//#define DT_SKILL_WILDSHOT			7820040	// 시간형
//#define DT_SKILL_WIDERANGE			7820050	// 시간형
//#define DT_SKILL_HAWKEYE			7820060	// 시간형
//#define DT_SKILL_MINEMASTERY		7820070	// 지속형
//#define DT_SKILL_SPHERETARGET		7820080	// 시간형
//#define DT_SKILL_CARPETBLAST		7820090	// 시간형
//#define DT_SKILL_ASSASSINSCOPE		7820100	// 시간형
//#define DT_SKILL_MINEDISTURBANCE	7820110	// 시간형
//#define DT_SKILL_CAMOUFLAGE			7821010	// 시간형
//#define DT_SKILL_SMOKESCREEN		7821020	// 시간형
//#define DT_SKILL_MIRRORIMAGE		7821030	// 시간형
//#define DT_SKILL_DASH				7822010	// 클릭형
//#define DT_SKILL_AUTODRIVING		7822020	// 클릭형
//#define DT_SKILL_CONCENTRATION		7822030	// 시간형
//#define DT_SKILL_OREGATHERING		7822040	// 클릭형
//#define DT_SKILL_OREFINDING			7822050	// 클릭형
//#define DT_SKILL_ORESEARCH			7822060	// 클릭형
//#define DT_SKILL_OREREFINING		7822070	// 클릭형
//
//// ST
//#define ST_SKILL_VULCANMASTERY		7830010	// 지속형
//#define ST_SKILL_GATLINGMASTERY		7830020	// 지속형
//#define ST_SKILL_STRAFESHOT			7830030	// 시간형
//#define ST_SKILL_SNIPESHOT			7830040	// 시간형
//#define ST_SKILL_BURSTSHOT			7830050	// 시간형
//#define ST_SKILL_WIDESHOT			7830060	// 시간형
//#define ST_SKILL_MISSILEMASTERY		7830070	// 지속형
//#define ST_SKILL_STRAFEBLAST		7830080	// 시간형
//#define ST_SKILL_MULTIPLEBLAST		7830090	// 시간형
//#define ST_SKILL_FRENZYBLAST		7830100	// 시간형
//#define ST_SKILL_WIDEBLAST			7830110	// 시간형
//#define ST_SKILL_BLASTPROTECTION	7831010	// 시간형
//#define ST_SKILL_BLASTREFLECTION	7831020	// 시간형
//#define ST_SKILL_YOYOSPINNING		7832010	// 클릭형
//#define ST_SKILL_OVERBOOST			7832020	// 클릭형
//#define ST_SKILL_COPTERFLIGHT		7832030	// 시간형
//#define ST_SKILL_CONCENTRATION		7832040	// 시간형

// 2005-11-22 by cmkwon
// BT
//#define 	BT_SKILL_AUTOMATICMASTERY		7800010		// 지속형
//#define 	BT_SKILL_RIFLEMASTERY			7800020		// 지속형
//#define 	BT_SKILL_STRAFESHOT				7800030		// 지속형
//#define 	BT_SKILL_SNIPESHOT				7800040		// 시간형
//#define 	BT_SKILL_BURSTSHOT				7800050		// 시간형
//#define 	BT_SKILL_WIDESHOT				7800060		// 시간형
//#define 	BT_SKILL_ROCKETMASTERY			7800070		// 지속형
//#define 	BT_SKILL_STRAFEBLAST			7800080		// 지속형
//#define 	BT_SKILL_SNIPEBLAST				7800090		// 시간형
//#define 	BT_SKILL_BURSTBLAST				7800100		// 시간형
//#define 	BT_SKILL_WIDEBLAST				7800200		// 시간형
//#define 	BT_SKILL_DODGE					7801010		// 시간형
//#define 	BT_SKILL_STRATEGICFIELD			7801020		// 시간형
//#define 	BT_SKILL_QUICKTURN				7802010		// 클릭형
//#define 	BT_SKILL_REVERSETURN			7802020		// 클릭형
//#define 	BT_SKILL_COPTERFLIGHT			7802030		// 클릭형
//#define 	BT_SKILL_CONCENTRATION			7802040		// 시간형
//
//// OT
//#define 	OT_SKILL_GRENADEMASTERY			7811010		// 지속형
//#define 	OT_SKILL_LAUNCHERMASTERY		7811020		// 지속형
//#define 	OT_SKILL_DUALSHOT				7811030		// 시간형
//#define 	OT_SKILL_SCORPING				7811040		// 시간형
//#define 	OT_SKILL_FRENZY					7811050		// 시간형
//#define 	OT_SKILL_CONVERGINGSHOT	 		7811060		// 시간형
//#define 	OT_SKILL_BUNDLEMASTERY			7811070		// 지속형
//#define 	OT_SKILL_OVERRADAR				7811080		// 시간형
//#define 	OT_SKILL_CRAZYSHOT	 			7811090		// 시간형
//#define 	OT_SKILL_EYEFORANEYE 			7811100		// 시간형
//#define 	OT_SKILL_BURSTSHOT				7811110		// 시간형
//#define 	OT_SKILL_FLYINGWORM	 			7812010		// 시간형
//#define 	OT_SKILL_DIFFUSION	 			7812020		// 클릭형
//#define 	OT_SKILL_PARALLELMOVEMENT 		7812030		// 클릭형
//#define 	OT_SKILL_SCREWPUSHING 			7812040		// 클릭형
//#define 	OT_SKILL_OVERRISING	 			7812050		// 시간형
////#define 		편대 회복				7812060
//
//// DT
//#define 	DT_SKILL_CANNONMASTERY			7820010		// 지속형
//#define 	DT_SKILL_MASSDRIVEMASTERY		7820020		// 지속형
//#define 	DT_SKILL_CHARGINGSHOT			7820030		// 시간형
//#define 	DT_SKILL_WILDSHOT				7820040		// 시간형
//#define 	DT_SKILL_WIDERANGE				7820050		// 시간형
//#define 	DT_SKILL_HAWKEYE				7820060		// 시간형
//#define 	DT_SKILL_MINEMASTERY			7820070		// 지속형
//#define 	DT_SKILL_SPHERETARGET			7820080		// 시간형
//#define 	DT_SKILL_CARPETBLAST			7820090		// 클릭형
//#define 	DT_SKILL_ASSASSINSCOPE			7820100		// 시간형
//#define 	DT_SKILL_MINEDISTURBANCE		7820110		// 시간형
//#define 	DT_SKILL_CAMOUFLAGE				7821010		// 시간형
//#define 	DT_SKILL_SMOKESCREEN			7821020		// 시간형
//#define 	DT_SKILL_MIRRORIMAGE			7821030		// 시간형
//#define 	DT_SKILL_DASH					7822010		// 클릭형
//#define 	DT_SKILL_AUTODRIVING			7822020		// 시간형
//#define 	DT_SKILL_CONCENTRATION			7822030		// 시간형
//#define 	DT_SKILL_OREGATHERING			7822040		// 지속형
//#define 	DT_SKILL_OREFINDING				7822050		// 지속형
//#define 	DT_SKILL_ORESEARCH				7822060		// 시간형
//#define 	DT_SKILL_OREREFINING			7822070		// 클릭형
//
//// ST
//#define 	ST_SKILL_VULCANMASTERY			7830010		// 지속형
//#define 	ST_SKILL_GATLINGMASTERY			7830020		// 지속형
//#define 	ST_SKILL_STRAFESHOT				7830030		// 지속형
//#define 	ST_SKILL_SNIPESHOT				7830040		// 시간형
//#define 	ST_SKILL_BURSTSHOT				7830050		// 시간형
//#define 	ST_SKILL_WIDESHOT				7830060		// 시간형
//#define 	ST_SKILL_MISSILEMASTERY			7830070		// 지속형
//#define 	ST_SKILL_STRAFEBLAST			7830080		// 지속형
//#define 	ST_SKILL_MULTIPLEBLAST			7830090		// 시간형
//#define 	ST_SKILL_FRENZYBLAST			7830100		// 시간형
//#define 	ST_SKILL_WIDEBLAST				7830110		// 시간형
//#define 	ST_SKILL_BLASTPROTECTION		7831010		// 시간형
//#define 	ST_SKILL_BLASTREFLECTION		7831020		// 시간형
//#define 	ST_SKILL_YOYOSPINNING			7832010		// 클릭형
//#define 	ST_SKILL_OVERBOOST				7832020		// 시간형
//#define 	ST_SKILL_COPTERFLIGHT			7832030		// 클릭형
//#define 	ST_SKILL_CONCENTRATION			7832040		// 시간형
////


///////////////////////////////////////////////////////////////////////////////
// Monster Target Type
#define MONSTER_TARGETTYPE_NORMAL			0			// 일반 타겟 타입 몬스터
#define MONSTER_TARGETTYPE_TUTORIAL			1			// 튜토리얼 타겟 타입 몬스터	- 특정 유저에게만 보이고 떨어지는 아이템도 특정 유저에게만 보인다
#define MONSTER_TARGETTYPE_MISSION			2			// 미션 타겟 타입 몬스터		- 미션을 받은 유저들에게만 보이고 떨어지는 아이템도 특정 유저들에게만 보인다


///////////////////////////////////////////////////////////////////////////////
// Event-Related Definitions
///////////////////////////////////////////////////////////////////////////////
// Event 구조체
struct EVENTINFO
{
	// 2010-04-14 by cmkwon, 서버 메모리 부족 문제 수정 - 아래와 같이 수정
	// 	BYTE		m_EventReceiver;							// EVENT_RECEIVER_XXX
	// 	INT			m_TileOrObjectIndex;						// TileIndex or ObjectIndex
	// 	D3DXVECTOR3 m_vPosition;								// 서버에서는 강제 워프시에만 사용한다. 서버서는 로딩 시 무조건 0으로 만든다, 단, ObjectEvent인 경우는 Object의 Position, by kelovon, 20030713
	// 	BYTE		m_bEventType;								// EVENT_TYPE_XXX
	// 	short		m_EventwParam1;								// 원래 event area index, Building Index, ~0이면 나중에 T_FP_EVENT_NOTIFY_WARP_OK 에서 m_EventwParam1을 확인해서 ~0이면 SAFE_DELETE()한다
	// 	short		m_EventwParam2;								// 찾아갈 event area index, Building Kind, ~0이면 defaultWarpTargetIndex를 사용한다
	// 	short		m_EventwParam3;								// 맵 이름
	// 	INT			m_NextEventIndex;							// 2005-07-15 by cmkwon, 타겟 event area index
	// 	BYTE		m_byObjectMonsterCreated;
	// 	BYTE		m_byBossMonster;							// 2006-11-22 by cmkwon, 변수명 변경(m_byIsCityWarMonster->m_byBossMonster) - 도시점령전은 없어짐
	// 	INT			m_nObejctMonsterUnitKind;					// 2009-10-12 by cmkwon, 프리스카 제거 방안 적용 - 워프일 경우는 사용불가 세력 설정(비트플래그)으로 사용됨, 
	// 	DWORD		m_dwLastTimeObjectMonsterCreated;
	// 	//	char		m_EventstrParam[SIZE_MAX_EVENT_PARAM_NAME];	// 맵 이름
		///////////////////////////////////////////////////////////////////////////////
		// 2010-04-14 by cmkwon, 서버 메모리 부족 문제 수정 - 
	D3DXVECTOR3 m_vPosition;								// 서버에서는 강제 워프시에만 사용한다. 서버서는 로딩 시 무조건 0으로 만든다, 단, ObjectEvent인 경우는 Object의 Position, by kelovon, 20030713
	INT			m_nObejctMonsterUnitKind;					// 2009-10-12 by cmkwon, 프리스카 제거 방안 적용 - 워프일 경우는 사용불가 세력 설정(비트플래그)으로 사용됨, 
	INT			m_NextEventIndex;							// 2005-07-15 by cmkwon, 타겟 event area index
	DWORD		m_dwLastTimeObjectMonsterCreated;
	short		m_EventwParam1;								// 원래 event area index, Building Index, ~0이면 나중에 T_FP_EVENT_NOTIFY_WARP_OK 에서 m_EventwParam1을 확인해서 ~0이면 SAFE_DELETE()한다
	short		m_EventwParam2;								// 찾아갈 event area index, Building Kind, ~0이면 defaultWarpTargetIndex를 사용한다
	short		m_EventwParam3;								// 맵 이름
	BYTE		m_EventReceiver;							// EVENT_RECEIVER_XXX
	BYTE		m_bEventType;								// EVENT_TYPE_XXX
	BYTE		m_byObjectMonsterCreated;
	BYTE		m_byBossMonster;							// 2006-11-22 by cmkwon, 변수명 변경(m_byIsCityWarMonster->m_byBossMonster) - 도시점령전은 없어짐

	EVENTINFO()
	{
		ResetEVENTINFO();
	}
	void ResetEVENTINFO(void)
	{
		m_EventReceiver = 0;
		// 2010-04-14 by cmkwon, 서버 메모리 부족 문제 수정 - 필요 없어서 제거됨
		//		m_TileOrObjectIndex					= 0;
		m_vPosition = D3DXVECTOR3(0, 0, 0);
		m_bEventType = 0;
		m_EventwParam1 = 0;
		m_EventwParam2 = 0;
		m_EventwParam3 = 0;
		m_NextEventIndex = 0;
		m_byObjectMonsterCreated = FALSE;
		m_byBossMonster = FALSE;		// 2006-11-22 by cmkwon, 변수명 변경(m_byIsCityWarMonster->m_byBossMonster) - 도시점령전은 없어짐
		m_nObejctMonsterUnitKind = 0;
		m_dwLastTimeObjectMonsterCreated = 0;
	}


	void* operator new(size_t size);
	void operator delete(void* p);
};

#define EVENT_RECEIVER_NONE		(BYTE)0		// 그냥 이벤트
#define	EVENT_RECEIVER_TILE		(BYTE)1		// TILE에 의한 이벤트
#define	EVENT_RECEIVER_OBJECT	(BYTE)2		// OBJECT에 의한 이벤트

// PK Type
#define PK_TYPE_PK						0x00
#define PK_TYPE_COMBAT					0x01
#define PK_TYPE_SAFE					0x02

// Event Type
typedef BYTE EventType_t;

#define EVENT_TYPE_NO_OBJECT_MONSTER		(EventType_t)0	// 
#define EVENT_TYPE_NOEVENT					(EventType_t)0
#define EVENT_TYPE_WARP						(EventType_t)1
#define EVENT_TYPE_WARP_TARGET				(EventType_t)2
#define EVENT_TYPE_ENTER_BUILDING			(EventType_t)3		// 상점영역 이벤트 - EventParam1(EventAreaIndex), EventParam2(이륙시 이동 할 이륙시작 오브젝트 EventAreaIndex)
#define EVENT_TYPE_LANDING					(EventType_t)4		// 착륙 Object
#define EVENT_TYPE_RACING_CHECK_POTINT		(EventType_t)5		// 레이싱 체크 포인트 Object
#define EVENT_TYPE_OBJECT_MONSTER			(EventType_t)6		// ObjectMonster Position Information Object
//#define EVENT_TYPE_OBJECT_MONSTER_STOP		(EventType_t)6	// 정지형, ObjectMonster Position Object
//#define EVENT_TYPE_OBJECT_MONSTER_ROTATE	(EventType_t)7		// 타겟벡터가 변하는 형태, ObjectMonster Position Object
#define EVENT_TYPE_PATTERN_POINT			(EventType_t)8		// 캐릭터 워프시 패턴의 시작/끝 오브젝트
#define EVENT_TYPE_OBJ_BUILDING_NPC			(EventType_t)9		// 2005-07-21 by cmkwon, 상점 NPC 오브젝트 - EventParam1(EventAreaIndex), NextEventIndex(NPCIndex)
#define EVENT_TYPE_LANDING_PATTERN_START	(EventType_t)10		// 2005-07-14 by cmkwon, 기어모드에서 착륙 패턴의 시작 오브젝트 - EventParam1(EventAreaIndex), NextEventIndex(착륙 목표 오브젝트 EventAreaIndex)
#define EVENT_TYPE_LANDING_PATTERN_END		(EventType_t)11		// 2005-07-14 by cmkwon, 기어모드에서 착륙 패턴의 종료 오브젝트, 오브젝트를 만나면 착륙 상태가 된다. - EventParam1(EventAreaIndex), NextEventIndex(착륙 후 이동 할 목표 오브젝트 EventAreaIndex)
#define EVENT_TYPE_TAKEOFF_PATTERN_START	(EventType_t)12		// 2005-07-14 by cmkwon, 기어모드에서 이륙 패턴의 시작 오브젝트 - EventParam1(EventAreaIndex), NextEventIndex(이륙 목표 오브젝트 EventAreaIndex)
#define EVENT_TYPE_TAKEOFF_PATTERN_END		(EventType_t)13		// 2005-07-14 by cmkwon, 기어모드에서 이륙 패턴의 종료 오브젝트 - EventParam1(EventAreaIndex)
#define EVENT_TYPE_OBJ_ENTER_BUILDING		(EventType_t)14		// 2005-07-22 by cmkwon, 기어가 착륙 후  상점으로 이동할 좌표 오브젝트 - EventParam1(EventAreaIndex)
#define EVENT_TYPE_OBJ_QUEST_OBJECT			(EventType_t)15		// 2005-08-17 by cmkwon, 퀘스트에서 이용되는 충돌 오브젝트 - EventParam1(EventAreaIndex)
#define EVENT_TYPE_CHARACTERMODE_WARP			(EventType_t)21		// 2006-07-14 by cmkwon, 캐릭터모드에서 워프 소스 오브젝트
#define EVENT_TYPE_CHARACTERMODE_WARP_TARGET	(EventType_t)22		// 2006-07-14 by cmkwon, 캐릭터모드에서 워프 타겟 오브젝트
#define EVENT_TYPE_ENTER_BUILDING_BAZAAR		(EventType_t)23		// 2006-07-19 by cmkwon, 개인상점 영역
#define EVENT_TYPE_CHARACTERMODE_DIRECTLY_WARP	(EventType_t)24		// 2007-12-14 by cmkwon, 캐릭터모드에서 바로 워프 시스템 구현 - 이 오브젝트와 충돌시 바로 워프됨

#define EVENT_TYPE_INFI_CINEMA				(EventType_t)30		// 2010. 05. 27 by jskim 시네마 적용 카메라 구현
#define EVENT_TYPE_PARAM_INFI_CINEMA		701					// 2010. 05. 27 by jskim 시네마 적용 카메라 구현

#define EVENT_TYPE_INFI_CINEMA_THIRD				(EventType_t)31		// 2011-06-23 by jhahn 인피3차 시네마 적용 카메라 구현
#define EVENT_TYPE_PARAM_INFITHIRD_CINEMA_FAIL			702						// 2011-06-23 by jhahn 인피3차 시네마 적용 카메라 구현
#define EVENT_TYPE_PARAM_INFITHIRD_CINEMA_SUCCESS		703						// 2011-06-23 by jhahn 인피3차 시네마 적용 카메라 구현

#define EVENT_TYPE_TUTORIAL_GATE_POINT		(EventType_t)100	// 

extern char* Get_EVENT_TYPE_String(EventType_t i_evType);

// Event Result
typedef BYTE EventResult_t;

//#define EVENT_RESULT_ERROR				0x00	// check: 불필요하다고 판단, EVENT_RESULT_CLOSE_CONNECTION로 전환함, 필요하면 살림, 20030812, kelovon
#define EVENT_RESULT_BREAK				0x01	// 이벤트가 처리되지 않았음
#define EVENT_RESULT_CONTINUE			0x02	// 이벤트가 성공적으로 처리됨, 계속 진행하면 됨
#define EVENT_RESULT_CLOSE_CONNECTION	0x03	// 심각한 에러 발생, 연결 종료 요구

///////////////////////////////////////////////////////////////////////////////
// Variable Type Definitions
///////////////////////////////////////////////////////////////////////////////
typedef USHORT ClientIndex_t;
typedef vector<ClientIndex_t>		vectorClientIndex;
typedef set<ClientIndex_t>			setClientIndex_t;		// 2009-12-11 by cmkwon, 데미지 어그로로 타겟을 변경하는 몬스터 구현 - 

// MapIndex 및 ChannelIndex 관리용
struct MAP_CHANNEL_INDEX
{
	// member variables
	MapIndex_t		MapIndex;
	ChannelIndex_t	ChannelIndex;

	// overloaded operators
	inline bool operator==(MAP_CHANNEL_INDEX& rhs)
	{
		return (this->MapIndex == rhs.MapIndex && this->ChannelIndex == rhs.ChannelIndex);
	}

	inline bool operator!=(MAP_CHANNEL_INDEX& rhs)
	{
		return (this->MapIndex != rhs.MapIndex || this->ChannelIndex != rhs.ChannelIndex);
	}
	inline bool IsSameMapChannelIndex(const MAP_CHANNEL_INDEX& rhs)
	{
		return (this->MapIndex == rhs.MapIndex && this->ChannelIndex == rhs.ChannelIndex);
	}

	// functions
	MAP_CHANNEL_INDEX() : MapIndex(0), ChannelIndex(0) {}
	MAP_CHANNEL_INDEX(MapIndex_t mapIdx, ChannelIndex_t channIdx) : MapIndex(mapIdx), ChannelIndex(channIdx) {}
	inline BOOL IsValid() { return (MapIndex != 0); }
	inline void Invalidate() { MapIndex = 0; }
	inline void Validate(MapIndex_t i_MapIndex, ChannelIndex_t i_ChannelIndex)
	{
		MapIndex = i_MapIndex; ChannelIndex = i_ChannelIndex;
	}
};

struct GEAR_STAT
{
	Stat_t	AttackPart;		// 공격파트
	Stat_t	DefensePart;	// 방어파트
	Stat_t	FuelPart;		// 연료파트
	Stat_t	SoulPart;		// 감응파트
	Stat_t	ShieldPart;		// 쉴드파트
	Stat_t	DodgePart;		// 회피파트, 0 ~ 255의 확률
};

///////////////////////////////////////////////////////////////////////////////
//	ATUM - Character - Parameter Struct 정의
///////////////////////////////////////////////////////////////////////////////
struct CHARACTER_DB_EX;

struct CHARACTER
{
	ClientIndex_t		ClientIndex;
	char				AccountName[SIZE_MAX_ACCOUNT_NAME];			// 사용자 아이디
	UID32_t				AccountUniqueNumber;						//  계정 고유 번호
	char				CharacterName[SIZE_MAX_CHARACTER_NAME];		// 유닛(캐릭터) 이름
	UID32_t				CharacterUniqueNumber;						// 캐릭터 고유번호
	BYTE				Gender;							// false(0) : 여, true(1) : 남
	BYTE				PilotFace;						// 화면에 나타나는 인물 케릭터
	BYTE				CharacterMode;					// 2005-07-13 by cmkwon, 현재 캐릭터 상태 플래그
	USHORT				Race;							// 종족
	USHORT				UnitKind;						// 유닛의 종류
	BYTE				InfluenceType;					// 세력 타입으로
	BYTE				SelectableInfluenceMask;		// 2005-12-07 by cmkwon, 세력선택시 선택가능한 세력Mask, 한계정에는 하나의 세력만 선택 가능함
	BYTE				AutoStatType;					// 자동 분배 스탯 타입
	GEAR_STAT			GearStat;						// 기어 스탯
	GEAR_STAT			TotalGearStat;					// 통합 기어 스탯 - 컴퓨터 아이템 스탯 포함
	char				GuildName[SIZE_MAX_GUILD_NAME];	// 길드 이름
	UID32_t				GuildUniqueNumber;				// 길드 번호, 0이면 길드 없음
	BYTE				Level;							//
	Experience_t		Experience;						//
	Experience_t		DownExperience;					// 캐릭이 죽을때 떨어진 경험치
	INT					DownSPIOnDeath;					// 2006-04-10 by cmkwon, 캐릭이 죽을때 떨어진 SPI
	BodyCond_t			BodyCondition;					// 상태, bit flag 사용
	INT					Propensity;						// 명성치, 성향(선, 악)
	BYTE				Status;							// 신분
	USHORT				PKWinPoint;						// PK 승리 수치
	USHORT				PKLossPoint;					// PK 패배 수치
	USHORT				Material;						// 재질(HI : Main, LOW : Sub)
	SHORT				HP;								// Health Point
	float				CurrentHP;						// Current Health Point
	SHORT				DP;								// 쉴드, Defense Point
	float				CurrentDP;						// 현재 쉴드, Current Defense Point
	SHORT				SP;								// Skill Point
	SHORT				CurrentSP;						//
	SHORT				EP;								// Fuel
	float				CurrentEP;						// Current Fuel
	char				PetName[SIZE_MAX_PET_NAME];
	BYTE				PetLevel;
	Experience_t		PetExperience;
	MAP_CHANNEL_INDEX	MapChannelIndex;				// 캐릭터가 속한 맵 및 채널
	D3DXVECTOR3			PositionVector;					// 캐릭터 좌표
	D3DXVECTOR3			TargetVector;					//
	D3DXVECTOR3			UpVector;						//
	BYTE				MaxLevel;
	BYTE				BonusStat;						// 추가 2002.12.13
// 2005-11-15 by cmkwon, 삭제함
//	BYTE				BonusSkillPoint;				// 추가 2002.12.13
	BYTE				BonusStatPoint;					// 2005-11-15 by cmkwon, 레벨업이 아닌 다른방법으로 받은 보너스 스탯 포인트, BonusSkillPoint를 변경함 // 추가 2002.12.13
	PartyID_t			LastPartyID;					// 마지막 파티 ID, 비정상적으로 종료되었을 때 파티 유지를 위해 쓰임
	INT					RacingPoint;					// 2009-11-02 by cmkwon, 캐쉬(인벤/창고 확장) 아이템 추가 구현 - 하위첫번째1Byte:인벤추가개수, 하위두번째1Byte:창고추가개수, 하위세번째/네번째2Byte는 사용하지 않음, // Racing 결과 Point
	LONGLONG			TotalPlayTime;					// 초단위
	ATUM_DATE_TIME		CreatedTime;					// 캐릭터 생성 시간
	ATUM_DATE_TIME		LastStartedTime;				// 최종 게임 시작 시간
	ATUM_DATE_TIME		LevelUpTime;					// 2006-12-18 by dhjin, 레벨업 시간
	INT					WarPoint;						// 2007-04-17 by dhjin, WP
	INT					CumulativeWarPoint;				// 2007-05-28 by dhjin, 누적WP
	INT					ArenaWin;						// 2007-06-07 by dhjin, 아레나 승패 전적 승
	INT					ArenaLose;						// 2007-06-07 by dhjin, 아레나 승패 전적 패
	INT					ArenaDisConnect;				// 2007-06-07 by dhjin, 아레나 강제 종료
	LONGLONG			PCBangTotalPlayTime;			// 2007-06-07 by dhjin, PC방 총 플레이 시간, 초단위
	INT					SecretInfoOption;				// 2008-06-23 by dhjin, EP3 유저정보옵션 -
	char				NickName[SIZE_MAX_CHARACTER_NAME];	// 2009-02-12 by cmkwon, EP3-3 월드랭킹시스템 구현 - 월드 랭킹을 위한 NickName

	// operator overloading
	CHARACTER& operator=(const CHARACTER_DB_EX& rhs);
	// 2009-10-12 by cmkwon, 프리스카 제거 방안 적용 - 
	// 	BYTE GetInfluenceMask(void)
	// 	{
	// 		if(COMPARE_INFLUENCE(InfluenceType, INFLUENCE_TYPE_NORMAL|INFLUENCE_TYPE_VCN))
	// 		{
	// 			return INFLUENCE_TYPE_NORMAL|INFLUENCE_TYPE_VCN;
	// 		}
	// 		return InfluenceType;
	// 	}
		///////////////////////////////////////////////////////////////////////////////
		// 2009-10-12 by cmkwon, 프리스카 제거 방안 적용 - 
	BYTE GetInfluenceMask(void)
	{
		if (IS_NORMAL_INFLUENCE_TYPE(InfluenceType))
		{
			if (IS_ANI_CITY_MAP_INDEX(Material))
			{
				return INFLUENCE_TYPE_NORMAL | INFLUENCE_TYPE_ANI;
			}
			return INFLUENCE_TYPE_NORMAL | INFLUENCE_TYPE_VCN;
		}

		return InfluenceType | INFLUENCE_TYPE_NORMAL;
	};
	///////////////////////////////////////////////////////////////////////////////
	/// \fn			
	/// \brief		// 2009-10-12 by cmkwon, 프리스카 제거 방안 적용 - 
	/// \author		cmkwon
	/// \date		2009-10-12 ~ 2009-10-12
	/// \warning	
	///
	/// \param		
	/// \return		
	///////////////////////////////////////////////////////////////////////////////
	USHORT GetStartCityMapIndex(void)
	{
		switch (InfluenceType)
		{
		case INFLUENCE_TYPE_NORMAL:
		{
			if (IS_ANI_CITY_MAP_INDEX(Material))
			{
				return Material;
			}
			return VCN_CITY_MAP_INDEX;	// 2009-10-12 by cmkwon, 설정되지 않은 유저 기본
		}
		case INFLUENCE_TYPE_VCN:				return VCN_CITY_MAP_INDEX;
		case INFLUENCE_TYPE_ANI:				return ANI_CITY_MAP_INDEX;
		}

		return VCN_CITY_MAP_INDEX;		// 2009-10-12 by cmkwon, 기본맵
	}

	///////////////////////////////////////////////////////////////////////////////
	// 2009-11-02 by cmkwon, 캐쉬(인벤/창고 확장) 아이템 추가 구현 - 
	BYTE GetAddedPermanentInventoryCount(BYTE i_enStorage = ITEM_IN_CHARACTER);
	BOOL SetAddedPermanentInventoryCount(BYTE i_byAddCount, BYTE i_enStorage = ITEM_IN_CHARACTER);
};

// 공격 타입: C(캐릭터), M(몬스터), I(필드아이템), CI(캐릭터에 종속된 아이템)
typedef enum
{
	ERR2ERR = 0,
	C2C = 1,
	C2M,
	C2I,
	C2CI,
	C2NULL,			// NULL Target
	M2C,
	M2M,			// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 추가
	M2I,
	M2CI,
	M2NULL			// NULL Target
} enumAttackToTarget;

///////////////////////////////////////////////////////////////////////////////
// 2009-09-09 ~ 2010-02-10 by dhjin, 인피니티 - 발동류장착아이템
struct INVOKING_WEAR_ITEM_DESTPARAM {
	InvokingDestParamID_t	InvokingDestParamID;
	DestParam_t				InvokingDestParam;
	ParamValue_t			InvokingDestParamValue;
	EffectIdx_t				InvokingEffectIdx;
};
typedef vector<INVOKING_WEAR_ITEM_DESTPARAM>		InvokingWearItemDestParamList;
typedef ez_map<InvokingDestParamID_t, InvokingWearItemDestParamList>	ezmapInvokingDPIdDPList;

struct MEX_ITEM_INFO;

///////////////////////////////////////////////////////////////////////////////
//	ATUM - Item - Parameter Struct 정의
///////////////////////////////////////////////////////////////////////////////
 /*
struct ITEM
{
	INT			ItemNum;						// 아이템 고유번호, 장착 아이템일 때 (ITEM_BASE*)
	BYTE		Kind;							// 아이템 종류(기관포, 빔, 로켓, 스킬.....), ITEMKIND_XXX
	char		ItemName[SIZE_MAX_ITEM_NAME];	// 아이템 이름
	float		AbilityMin;						// 아이템최소성능
	float		AbilityMax;						// 아이템최대성능
	USHORT		ReqRace;						// 필요종족
	GEAR_STAT	ReqGearStat;					// 필요 기어 스탯
	USHORT		ReqUnitKind;					// 필요유닛종류
	BYTE		ReqMinLevel;					// 필요 최저 레벨
	BYTE		ReqMaxLevel;					// 필요 최저 레벨
	BYTE		ReqItemKind;					// 필요아이템종류, ITEMKIND_XXX, check: 스킬에만 사용, 20040818, kelovon
	USHORT		Weight;							// 무게
	float		HitRate;						// 명중확률(0~255)	// 2010-07-19 by dhjin, 확률 수식 변경
	BYTE		Defense;						// 방어력
	float		FractionResistance;				// 2008-10-06 by dhjin, 피어스율로 일단 사용 // 속성저항력(0~255) // 2010-07-19 by dhjin, 확률 수식 변경
	BYTE		NaturalFaction;					// 천적계열, 종족(몬스터, 캐릭터) Index (천적)
	BYTE		SpeedPenalty;					// 스피드페널티, 이동속도에미치는 영향(-:감소)
	USHORT		Range;							// 공격범위, 엔진류인 경우에는 부스터 가동 시 속도, 스킬의 경우 적용 범위
	BYTE		Position;						// 장착위치
	BYTE		Scarcity;						// 희귀성, 게임상에 나올 확률, define해서 사용, see below
	float		Endurance;						// 내구성, 내구도
	Prob256_t	AbrasionRate;					// 마모율, 내구도가 줄어드는 단위량(0~255)
	USHORT		Charging;						// 무기류에서는 최대 장탄 수, 에너지는 한번에 적용되는 개수, TANK류는 양
	BYTE		Luck;							// 행운
	USHORT		MinTradeQuantity;				// 최소 거래 수량, Price는 이 수량에 대한 가격이다
	UINT		Price;							// 최소 거래 수량의 가격
	UINT		CashPrice;						// 최소 거래 수량의 현금 가격

// 2009-04-21 by cmkwon, ITEM에 DesParam 필드 개수 8개로 늘리기 - 아래와 같이 배열로 수정 함.
// 	BYTE		DestParameter1;					// 대상파라미터1
// 	float		ParameterValue1;				// 수정파라미터1
// 	BYTE		DestParameter2;					// 대상파라미터2
// 	float		ParameterValue2;				// 수정파라미터2
// 	BYTE		DestParameter3;					// 대상파라미터3
// 	float		ParameterValue3;				// 수정파라미터3
// 	BYTE		DestParameter4;					// 대상파라미터4
// 	float		ParameterValue4;				// 수정파라미터4
	BYTE		ArrDestParameter[SIZE_MAX_DESPARAM_COUNT_IN_ITEM];	// 2009-04-21 by cmkwon, ITEM에 DesParam 필드 개수 8개로 늘리기 - 
	float		ArrParameterValue[SIZE_MAX_DESPARAM_COUNT_IN_ITEM];	// 2009-04-21 by cmkwon, ITEM에 DesParam 필드 개수 8개로 늘리기 - 

	UINT		ReAttacktime;					// 재 공격시간(ms)
	INT			Time;							// 지속 시간(스킬류 등)
	USHORT		RepeatTime;						// 무기류에서는 남은 총알 수로 사용, 나머지는 개수, 시간형 스킬류에선 남은 시간, 나머지 스킬은 사용 여부
	USHORT		Material;						// 재질
	USHORT		ReqMaterial;					// 필요한 재질 수(제작,수리시 필요)
	float		RangeAngle;						// 범위각도(0 ~ PI), 화망
	BYTE		UpgradeNum;						// 업그레이드 수, 업그레이드의 한계를 나타냄.
	INT			LinkItem;						// 링크아이템, 아이템과 연관된 아이템(총알)
	BYTE		MultiTarget;					// 동시에 잡을 수 있는 타겟의 수
	USHORT		ExplosionRange;					// 폭발반경(폭발 시 데미지의 영향이 미치는 반경)
	USHORT		ReactionRange;					// 반응반경(마인 등이 반응하는 반경)
	BYTE		ShotNum;						// 점사 수,	점사 시 발사 수를 나타낸다.
	BYTE		MultiNum;						// 동시 발사 탄 수,	1번 발사에 몇발이 동시에 나가느냐
	USHORT		AttackTime;						// 공격시간, 공격을 하기 위해 필요한 시간
	BYTE		ReqSP;							// SP 소모량(스킬)
	INT			SummonMonster;					// 2006-06-08 by cmkwon, 유료화 상점의 탭구분자로 사용한다.(CASH_ITEMKIND_XXXX)
	INT			NextSkill;						// 다음 단계의 스킬 아이템 넘버(스킬)
	BYTE		SkillLevel;						// 레벨
	Prob256_t	SkillHitRate;					// 스킬명중확률(0~255)
	BYTE		SkillType;						// 스킬형태(시간 및 발동 관련), 지속|클릭|시간|유지
	BYTE		SkillTargetType;				// 스킬 타켓 타입, SKILLTARGETTYPE_XXX
	BYTE		Caliber;						// 구경(총알, 탄두 등)
	BYTE		OrbitType;						// 미사일, 로켓 등의 궤적
	BitFlag64_t	ItemAttribute;					// 아이템의 속성, ITEM_ATTR_XXX
	FLOAT		BoosterAngle;					// 부스터시에 유닛의 회전각, 현재는 엔진에만 사용
	INT			CameraPattern;					// 카메라 패턴
	INT			SourceIndex;					// 2005-08-22 by cmkwon, 이펙트, 아이콘(빅/스몰) 리소스 데이타
	vectINT* pParamOverlapIdxList;			// 2010-01-18 by cmkwon, 아이템 사용시 Parameter 중복 체크 시스템 구현 - 
	char		Description[SIZE_MAX_ITEM_DESCRIPTION];	// 아이템 설명
	BYTE		EnchantCheckDestParam;			// 2009-09-09 ~ 2010-02-10 by dhjin, 인피니티 - 발동류장착아이템
	InvokingDestParamID_t	InvokingDestParamID;	// 2009-09-09 ~ 2010-02-10 by dhjin, 인피니티 - 발동류장착아이템
	InvokingDestParamID_t	InvokingDestParamIDByUse;// 2009-09-09 ~ 2010-02-10 by dhjin, 인피니티 - 발동류장착아이템	
	InvokingWearItemDestParamList* pInvokingDestParamList;			// 2009-09-09 ~ 2010-02-10 by dhjin, 인피니티 - 발동류장착아이템
	InvokingWearItemDestParamList* pInvokingDestParamByUseList;	// 2009-09-09 ~ 2010-02-10 by dhjin, 인피니티 - 발동류장착아이템	
	BYTE		IsTenderDropItem;				// 2010-04-09 by cmkwon, 인피2차 추가 수정(단계별 보상 추가) - CFieldIOCP::SetTenderItemList#에서 설정됨 
};
 */


#pragma pack(push, 1)
struct ITEM
{
	char pad0[4];
	float ArrParameterValue[8];
	uint8_t Kind;
	char pad37[3];
	float AbilityMin;
	char pad44[4];
	int32_t SummonMonster;
	BYTE ArrDestParameter[8];
	char pad54[152];
	uint8_t ReqMinLevel;
	uint8_t ReqMaxLevel;
	char pad214[1];
	uint8_t ReqItemKind;
	uint16_t Weight;
	char pad218[2];
	float HitRate;
	char pad224[1];
	char ItemName[40];
	char pad226[3];
	float FractionResistance;
	char pad272[12];
	uint8_t SpeedPenalty;
	char pad285[3];
	uint16_t Range;
	uint8_t Position;
	uint8_t Scarcity;
	char pad292[4];
	int32_t ItemNum;
	float Endurance;
	char pad304[4];
	uint16_t Charging;
	char pad310[110];
	uint16_t RepeatTime;
	char pad422[6];
	float AbilityMax;
	uint16_t ReqRace;
	uint16_t MinTradeQuantity;
	uint32_t CashPrice;
	char pad440[5];
	uint8_t ShotNum;
	char pad446[9];
	uint8_t MultiNum;
	uint32_t ReAttacktime;
	char pad460[4];
	int32_t Time;
	GEAR_STAT ReqGearStat;
	uint16_t ReqUnitKind;
	char pad482[4];
	uint8_t ReqSP;
	char pad487[13];
	float RangeAngle;
	uint8_t SkillType;
	uint8_t SkillTargetType;
	char pad506[2];
	int32_t LinkItem;
	char pad512[8];
	char Description[200];
	uint16_t ExplosionRange;
	uint16_t ReactionRange;
	uint8_t SkillLevel;
	char pad725[1];
	int16_t SkillHitRate;
	uint8_t Caliber;
	uint8_t OrbitType;
	char pad730[6];
	uint64_t ItemAttribute;
	float BoosterAngle;
	int32_t CameraPattern;
	int32_t SourceIndex;
	char pad756[20];
};
#pragma pack(pop)

typedef vector<ITEM*>			vectItemPtr;		// 2009-08-26 by cmkwon, 그래픽 리소스 변경 시스템 구현 - 


// 2006-08-24 by dhjin, 이벤트 아이템 정보
struct SITEM_EVENT_INFO
{
	int				ItemEventUID;
	int				ItemEventType;		// ITEM_EVENT_TYPE_XXX
	int				OnlyPCBang;
	BYTE			byInfluenceType;
	int				ItemNum;
	int				Count;
	ATUM_DATE_TIME  StartTime;
	ATUM_DATE_TIME	EndTime;
	BOOL			MemberShip;			// 2006-09-29 by dhjin, 맴버쉽 유저만 지급
	BYTE			ReqLevel;			// 2007-07-20 by dhjin, ITEM_EVENT_TYPE_NEWMEMBER_LEVELUP 추가로 레벨 필드 추가
	BOOL			NewMember;			// 2007-07-23 by dhjin, 이벤트 기간안에 가입한 유저에게만 지급
	INT				UnitKind;			// 2007-07-24 by dhjin, 지급 대상 유닛
	INT				PrefixCodeNum;		// 2007-07-25 by dhjin, 아이템 접두 옵션
	INT				SuffixCodeNum;		// 2007-07-25 by dhjin, 아이템 접미 옵션
	BOOL			UseLastGameEndDate;	// 2008-02-01 by cmkwon, ItemEvent 에 LastGameEndDate 체크 루틴 추가 - SITEM_EVENT_INFO 에 필드 추가
	ATUM_DATE_TIME  atLastGameEndDate;	// 2008-02-01 by cmkwon, ItemEvent 에 LastGameEndDate 체크 루틴 추가 - SITEM_EVENT_INFO 에 필드 추가
	BOOL			CheckWithCharacterUID;	// 2009-11-19 by cmkwon, 아이템 이벤트에 Account/Character 체크 기능 추가 - FALSE(0)이면 AccountUID로 체크
	INT				iLevelMin;
	INT				iLevelMax;
	INT				LoginCheckNumber;		// 2011-08-25 by shcho, 횟수별 아이템 지급기능 구현 - 0인경우 사용안함으로 처리. 2값일 경우, 하루에 한번 기한까지 2번 접속해야 지급
};

typedef	vector<SITEM_EVENT_INFO>	vectItemEventInfo;
// ITEM_EVENT_TYPE_XXX
#define ITEM_EVENT_TYPE_ONLYONE					1
#define ITEM_EVENT_TYPE_ONEDAY					2
#define ITEM_EVENT_TYPE_INFLCHANGE				3
#define ITEM_EVENT_TYPE_LEVELUP					4
#define ITEM_EVENT_TYPE_COUPON_ONLYONE			5	// 2008-01-10 by cmkwon, 아이템 이벤트 시스템에 신 쿠폰 시스템 추가 - 한계정당 한번만 가능한 쿠폰 이벤트
#define ITEM_EVENT_TYPE_COUPON_ONEDAY			6	// 2008-01-10 by cmkwon, 아이템 이벤트 시스템에 신 쿠폰 시스템 추가 - 한계정당 하루에 한번 가능한 쿠폰 이벤트
#define ITEM_EVENT_TYPE_LOGIN					7	// 2011-08-25 by shcho, 횟수별 아이템 지급기능 구현

struct MAP_AREA {
	INT		MapIndex;
	INT		X;
	INT		Y;
	INT		Radius;

	

	void Reset() { MapIndex = 0; X = 0; Y = 0; Radius = 0; }
};

typedef struct
{
	ITEM* pItemInfo;
	DWORD		dwUsingPercent;
	BYTE		byArrayIndex;
	BYTE		byBodyConArrayIndex;		// 2006-12-15 by cmkwon, DB의 순서 - 이펙트 바디컨디션과 연관 있다
} MONSTER_ITEM;

// start 2011-03-21 by hskim, 인피니티 3차 - 몬스터 멀티 타겟팅 기능 추가
typedef struct
{
	D3DXVECTOR3		Position;
} MONSTER_TARGET;
// end 2011-03-21 by hskim, 인피니티 3차 - 몬스터 멀티 타겟팅 기능 추가

struct ITEM_W_COUNT {
	INT		ItemNum;
	INT		Count;

	void Reset() { ItemNum = 0; Count = 0; }
};

struct ITEM_W_COUNT_CHECK
{
	BOOL	bChecked;		// 2006-08-28 by cmkwon
	INT		ItemNum;
	INT		Count;

	void Reset(void) { bChecked = FALSE; ItemNum = 0; Count = 0; }
};

struct MONSTER_W_COUNT	// 2005-10-19 by cmkwon
{
	INT		MonsterUniqueNumber;
	INT		Count;
	MAP_AREA		MapArea;			// 2007-03-14 by cmkwon, 몬스터 위치 좌표를 미니맵에 보여주기 위해

	void Reset() { MonsterUniqueNumber = 0; Count = 0; }
};
typedef vector<MONSTER_W_COUNT>			vectMONSTER_W_COUNT;

struct ITEM_W_COUNT_PROB {
	INT			ItemNum;
	INT			Count;
	Prob100_t	Prob100;		// 확률

	void Reset() { ItemNum = 0; Count = 0; Prob100 = 0; }
};

struct ITEM_UNIQUE_NUMBER_W_COUNT {
	UID64_t	ItemUniqueNumber;
	INT		Count;

	void Reset() { ItemUniqueNumber = 0; Count = 0; }
};

struct ItemID_t
{
	UID64_t	ItemUID;
	INT		ItemNum;

	ItemID_t() {}
	ItemID_t(UID64_t i_ItemUID, INT i_ItemNum)
	{
		ItemUID = i_ItemUID;
		ItemNum = i_ItemNum;
	}
};

struct ITEM_UID_W_ITEMNUM_COUNT			// 2008-09-26 by cmkwon, 조합시 GameLog 수정 - 선언 추가 함
{
	UID64_t		ItemUID;
	INT			ItemNum;
	INT			Count;
};


///////////////////////////////////////////////////////////////////////////////
//	ATUM - Monster - Parameter Struct 정의
///////////////////////////////////////////////////////////////////////////////
//#define ARRAY_SIZE_MONSTER_SECONDARY_ITEM			5
#define ARRAY_SIZE_MONSTER_ITEM						16			// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 10개 추가 6 -> 16
#define ARRAY_SIZE_MONSTER_TARGET					10			// 2011-03-21 by hskim, 인피니티 3차 - 몬스터 멀티 타겟팅 기능 추가 - 10개로 제한
#define ARRAY_INDEX_MONSTER_SKILL_ITEM				15			// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 10개 추가 5 -> 15
#define ARRAY_SIZE_MONSTER_SKILL_ITEM				10			// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 기존 아이템은 공통아이템으로 사용하고 추가된 10개 아이템은 스킬아이템으로 사용한다.
#define SIZE_MAX_FILE_NAME			50	// 2010-03-31 by dhjin, 인피니티(기지방어) - 
struct MONSTER_INFO
{
	//	ClientIndex_t	MonsterIndex;					// 인덱스
	//	SHORT			CurrentHP;						// 현재 에너지
	//	BodyCond_t		BodyCondition;					// 캐릭터 BodyCondition
	//	ITEM			*ItemInfoPrimary;				// Primary 공격 Item, DB에서 읽을 때는 ItemNum을 할당하고, 그 이후에 pointer를 할당함, by kelovon
	//	ITEM			*ItemInfoSecondary[ARRAY_SIZE_MONSTER_SECONDARY_ITEM];			// Secondary 공격 Item
	//	D3DXVECTOR3		PositionVector;					// 캐릭터 좌표
	//	D3DXVECTOR3		TargetVector;					//
	//	D3DXVECTOR3		UpVector;						//
	INT				MonsterUnitKind;				// 몬스터 고유번호
	char			MonsterName[SIZE_MAX_MONSTER_NAME];	// 몬스터 이름
	BYTE			Level;							// 몬스터의 Level
	INT				MonsterHP;						// 만피
	USHORT			Race;							// 종족
	float			Defense;						// 방어력, 0 ~ 255		// 2010-07-19 by dhjin, 확률 수식 변경, // 2009-12-17 by cmkwon, 데미지 계산식 관련한 필드(방어력,회피,피어스,확률)에 255이상 값을 설정 가능하게 수정 - 기존자료형(BYTE)
	float			DefenseProbability;				// 방어성공확률, 20030630, 추가됨 // 2010-07-19 by dhjin, 확률 수식 변경
	BYTE			Speed;							// 이동속도
	MONSTER_ITEM	ItemInfo[ARRAY_SIZE_MONSTER_ITEM];	// 몬스터가 가지고 있는 모든 아이템
	USHORT			Size;							// 필드 서버는 SizeForClient를 loading,  NPC 서버는 SizeForServer를 loading
	BYTE			Faction;						// 계열
	SHORT			MonsterForm;					// Monster 형태
	BYTE			AttackPattern;					//
	SHORT			MovePattern;					//
	BYTE			Belligerence;					// 호전성
	BYTE			AttackObject;					// ATTACKOBJ_XXX
	SHORT			AttackRange;					// 공격성향 몬스터의 몬스터가 타겟팅가능한 거리
	LONGLONG		Experience;						// 폭파시 주는 경험치
	BYTE			AlphaBlending;					// alpha blending 여부, TRUE(1), FALSE(0), client측 사용을 위해 추가, 20030616
	USHORT			HPRecoveryTime;					// HP 차는 시간
	SHORT			HPRecoveryValue;				// 한번에 차는 HP의 양
	USHORT			RenderIndex;
	float			ScaleValue;
	BYTE			TextureIndex;
	UINT			SourceIndex;
	BYTE			QuickTurnAngle;					// 최대각 범위
	BYTE			QuickSpeed;						// 빠르게 이동시 속도
	USHORT			QuickTurnTerm;					// 빠르게 이동하는 Term
	BitFlag64_t		MPOption;						// 2010-01-11 by cmkwon, 몬스터 MPOption 64bit로 변경 - 기존(BYTE), MPOPTION_BIT_XXX
	BYTE			MPOptionParam1;
	BYTE			MPOptionParam2;
	USHORT			Range;
	FLOAT			TurnAngle;
	BYTE			MonsterHabit;					// 습성, ex) 야간 공격력 증가 등
	BYTE			ClickEvent;						// 2007-09-05 by dhjin, 몬스터 클릭 이벤트
	HPActionIdx_t	HPActionIdx;					// 2009-09-09 ~ 2010 by dhjin, 인피니티 - HP 행동
	MonIdx_t		MonsterTarget;					// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 몬스터 강제 공격 대상 번호
	ChangeTarget_t	ChangeTarget;					// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 몬스터 공격 받을 경우 타겟값 변경 여부
	MonIdx_t		MonsterTarget2;					// 2010-03-31 by dhjin, 인피니티(기지방어) - 몬스터 강제 공격 대상 번호 2번째 우선 순위
	char			PortraitFileName[SIZE_MAX_FILE_NAME];	// 2010-03-31 by dhjin, 인피니티(기지방어) - 몬스터 초상화 파일
	INT				ChangeTargetTime;				// 2010-04-14 by cmkwon, 인피2차 몬스터 랜텀 타겟 변경 처리 - 
	MONSTER_TARGET	MultiTargetInfo[ARRAY_SIZE_MONSTER_TARGET];				// 2011-03-21 by hskim, 인피니티 3차 - 몬스터 멀티 타겟팅 기능 추가
																			// 주의 사항 => 인덱스는 내부적으로는 0부터 관리
																			// 대외적인 인덱스는 1부터 시작, 0은 멀티 타겟이 없는 값을 의미
	INT				WayPointPattern;				// 2011-05-23 by hskim, 인피니티 3차 - 웨이포인트 구현 - WayPointPattern 필드 추가
};


// 2010. 05. 19 by hsLee 인피니티 필드 2차 난이도 조절. (신호처리 + 몬스터 처리(서버) )
//////////////////////////////////////////////////////////////////////////////////////////////////

// 2010-05-24 by shcho, 인피니티 난이도 조절 -
struct INFINITY_DIFFICULTY_BONUS_INFO
{
	int iIncreaseStep; //난이도 단계
	int iExp; //경험치 확률
	int iDrop_Item_Persent;//드랍 아이템 확률
	int iItem_EA_persent;//아이템 개수 확률
};
typedef vector<INFINITY_DIFFICULTY_BONUS_INFO>	vectorInfinity_DifficultyInfo_Bonus; //난이도 리스트 벡터

// 2010-05-24 by shcho, 인피니티 난이도 조절 -
struct INFINITY_DIFFICULTY_MONSTER_SETTING_INFO
{
	int iIncreaseStep; //난이도 단계
	int iMonsterHP; //적용 될 HP
	int iMonsterDefense;//적용 될 방어력
	int iMonsterEvasion;//적용 될 회피력
	int iMonsterAttackItem;//적용 될 몬스터 아이템 데미지 & 스킬 지속시간
	int iMonsterPopulation;//적용 될 몬스터 개체수 
};
typedef vector<INFINITY_DIFFICULTY_MONSTER_SETTING_INFO>	vectorInfinity_DifficultyInfo_Monster; //난이도 몬스터 적용 리스트 벡터

struct MONSTER_BALANCE_DATA						// 몬스터 밸런스 확장 정보.
{
	MONSTER_BALANCE_DATA(const INT a_Step = 0)
	{

		this->DifficultyStep = a_Step;

		this->fMaxHPRatio = 1.0f;
		this->fDefenseRatio = 1.0f;
		this->fDefenseProbabilityRatio = 1.0f;
		this->fAtkMsgRatio = 1.0f;
		this->fIncreaseExpRatio = 1.0f;
		this->fIncreaseDropItemProbabilityRatio = 1.0f;
		this->fIncreaseDropItemCountRatio = 1.0f;
		this->fSummonCountRatio = 1.0f;
	}

	void Reset(void)
	{
		memset(this, 0x00, sizeof(MONSTER_BALANCE_DATA));
	}

	void Init(const INT a_Step)
	{
		this->DifficultyStep = a_Step;

		this->fMaxHPRatio = 1.0f;
		this->fDefenseRatio = 1.0f;
		this->fDefenseProbabilityRatio = 1.0f;
		this->fAtkMsgRatio = 1.0f;
		this->fIncreaseExpRatio = 1.0f;
		this->fIncreaseDropItemProbabilityRatio = 1.0f;
		this->fIncreaseDropItemCountRatio = 1.0f;
		this->fSummonCountRatio = 1.0f;
	}

	void operator= (const MONSTER_BALANCE_DATA& a_MonsterBalanceData)
	{
		memcpy(this, &a_MonsterBalanceData, sizeof(MONSTER_BALANCE_DATA));
	}

	void operator= (const INFINITY_DIFFICULTY_BONUS_INFO& a_Infinity_BonusInfo)
	{
		if (this->DifficultyStep != a_Infinity_BonusInfo.iIncreaseStep)
			return;

		this->fIncreaseExpRatio = (float)a_Infinity_BonusInfo.iExp * 0.01f;
		this->fIncreaseDropItemProbabilityRatio = (float)a_Infinity_BonusInfo.iDrop_Item_Persent * 0.01f;
		this->fIncreaseDropItemCountRatio = (float)a_Infinity_BonusInfo.iItem_EA_persent * 0.01f;
	}

	void operator = (const INFINITY_DIFFICULTY_MONSTER_SETTING_INFO& a_Infinity_MonsterInfo)
	{
		if (this->DifficultyStep != a_Infinity_MonsterInfo.iIncreaseStep)
			return;

		this->fMaxHPRatio = (float)a_Infinity_MonsterInfo.iMonsterHP * 0.01f;
		this->fDefenseRatio = (float)a_Infinity_MonsterInfo.iMonsterDefense * 0.01f;
		this->fDefenseProbabilityRatio = (float)a_Infinity_MonsterInfo.iMonsterEvasion * 0.01f;
		this->fAtkMsgRatio = (float)a_Infinity_MonsterInfo.iMonsterAttackItem * 0.01f;
		this->fSummonCountRatio = (float)a_Infinity_MonsterInfo.iMonsterPopulation * 0.01f;
	}

	void operator += (const INFINITY_DIFFICULTY_BONUS_INFO& a_Infinity_BonusInfo)
	{
		if (this->DifficultyStep != a_Infinity_BonusInfo.iIncreaseStep)
			return;

		this->fIncreaseExpRatio += (float)a_Infinity_BonusInfo.iExp * 0.01f;
		this->fIncreaseDropItemProbabilityRatio += (float)a_Infinity_BonusInfo.iDrop_Item_Persent * 0.01f;
		this->fIncreaseDropItemCountRatio += (float)a_Infinity_BonusInfo.iItem_EA_persent * 0.01f;
	}

	void operator += (const INFINITY_DIFFICULTY_MONSTER_SETTING_INFO& a_Infinity_MonsterInfo)
	{
		if (this->DifficultyStep != a_Infinity_MonsterInfo.iIncreaseStep)
			return;

		this->fMaxHPRatio += (float)a_Infinity_MonsterInfo.iMonsterHP * 0.01f;
		this->fDefenseRatio += (float)a_Infinity_MonsterInfo.iMonsterDefense * 0.01f;
		this->fDefenseProbabilityRatio += (float)a_Infinity_MonsterInfo.iMonsterEvasion * 0.01f;
		this->fAtkMsgRatio += (float)a_Infinity_MonsterInfo.iMonsterAttackItem * 0.01f;
		this->fSummonCountRatio += (float)a_Infinity_MonsterInfo.iMonsterPopulation * 0.01f;
	}

	// 2010. 07. 05 by hsLee. 몬스터 소환 관련. (밸런스 데이터 누락 수정.) - MaxHp는 0이하가 될수 없음.
	const bool IsValidData(void) const
	{
		return (fMaxHPRatio > .0f);
	}

	INT		DifficultyStep;

	float	fMaxHPRatio;							// 몬스터 HP 증가율.
	float	fDefenseRatio;							// 몬스터 방어력 증가율.
	float	fDefenseProbabilityRatio;				// 몬스터 방어성공(회피) 증가율.
	float	fAtkMsgRatio;							// 몬스터 공력력 증가율.
	float	fSummonCountRatio;						// 몬스터 소환 증가율.

	float	fIncreaseExpRatio;						// 몬스터 처치 경험치 획득 증가율.
	float	fIncreaseDropItemProbabilityRatio;		// 몬스터 처치 아이템 드랍율의 증가율.
	float	fIncreaseDropItemCountRatio;			// 몬스터 처치 아이템 드랍 개수 증가율.

};
// End 2010. 05. 19 by hsLee 인피니티 필드 2차 난이도 조절. (신호처리 + 몬스터 처리(서버) )

// 2010. 05. 19 by hsLee 인피니티 필드 2차 난이도 조절. (신호처리 + 몬스터 처리(서버) )
struct MONSTER_INFO_EXTEND
{

	float			fMaxHP;								// 몬스터 최대 HP.
	float			Defense;							// 몬스터 방어력.	// 2010-07-19 by dhjin, 확률 수식 변경
	float			DefenseProbability;					// 몬스터 방어율.	// 2010-07-19 by dhjin, 확률 수식 변경
	float			fAtkDmgRatio;						// 몬스터 공격력 증가율.

	float			fIncreaseExpRatio;					// 몬스터 처치시 획득 경험치 증가율.
	float			fIncreaseDropProbabilityRatio;		// 몬스터 처치시 아이템 드랍확률의 증가율.
	float			fIncreaseDropItemCountRatio;		// 몬스터 처치시 아이템 드랍 개수 증가율.
};
// End. 2010. 05. 19 by hsLee 인피니티 필드 2차 난이도 조절. (신호처리 + 몬스터 처리(서버) )


class MONSTER
{
public:
	MONSTER_INFO* MonsterInfoPtr;					// 몬스터 정보 포인터
	ClientIndex_t		MonsterIndex;					// 인덱스
	float				CurrentHP;						// 현재 에너지
	D3DXVECTOR3			PositionVector;					// 캐릭터 좌표
	D3DXVECTOR3			TargetVector;					//
	D3DXVECTOR3			UpVector;						//
	BodyCond_t			BodyCondition;					// 캐릭터 BodyCondition

// 2010. 05. 19 by hsLee 인피니티 필드 2차 난이도 조절. (신호처리 + 몬스터 처리(서버) )
	MONSTER_INFO_EXTEND	MonsterInfoExtend;				// 몬스터 확장 정보. 
	MONSTER_BALANCE_DATA MonsterInfoBalance;			// 몬스터 밸런스 정보.
// End 2010. 05. 19 by hsLee 인피니티 필드 2차 난이도 조절. (신호처리 + 몬스터 처리(서버) )

protected:
	MONSTER() {};
};


///////////////////////////////////////////////////////////////////////////////
// 2009-12-23 by cmkwon, 충돌 체크는 하지만 충돌 데미지 입지 않는 오브젝트 구현 - COLLISION_TYPE_XXX
#define COLLISION_TYPE_NONE					0
#define COLLISION_TYPE_NORMAL				1
#define COLLISION_TYPE_NO_DAMAGE			2

typedef struct _MAPOBJECTINFO
{
	_MAPOBJECTINFO()
	{
		Code = 0;
		Alpha = 0;
		Collision = 0;
		CollisionForServer = 0;
		ObjectRenderType = 0;
		RenderIndex = 0;
	}
	INT		Code;						// Object Type
	BYTE	Alpha;						//
	BYTE	Collision;					// 충돌 처리 플래그, // 2009-12-23 by cmkwon, 충돌 체크는 하지만 충돌 데미지 입지 않는 오브젝트 구현 - COLLISION_TYPE_XXX
	BYTE	CollisionForServer;
	BYTE	ObjectRenderType;
	USHORT	RenderIndex;

	// 2009-12-23 by cmkwon, 충돌 체크는 하지만 충돌 데미지 입지 않는 오브젝트 구현 - 
	BOOL IsCheckDamage(void)
	{
		if (FALSE == Collision
			|| COLLISION_TYPE_NO_DAMAGE == Collision)
		{
			return FALSE;
		}

		return TRUE;
	}
} MAPOBJECTINFO;

/*
typedef struct _MAPOBJECTINFO
{
	INT		Code;						// Object Type
	BOOL	Alpha;						//
	USHORT	RadiusForServer;			// Ojbect 반지름, 서버용
	USHORT	RadiusForClient;			// Ojbect 반지름, 클라이언트용
	BOOL	Collision;					// 충돌 처리 플래그
	BOOL	CollisionForServer;
	USHORT	RenderIndex;
	char	ObjectName[SIZE_MAX_OBJECT_NAME];
	BYTE	ObjectRenderType;
} MAPOBJECTINFO;
*/


// 스킬형태(시간 및 발동 관련)
#define SKILLTYPE_PERMANENT		0	// 지속형
#define SKILLTYPE_CLICK			1	// 클릭형
#define SKILLTYPE_TIMELIMIT		2	// 시간형
#define SKILLTYPE_TOGGLE		3	// 토글형
#define SKILLTYPE_CHARGING		4	// 차징형, 스킬 사용 이후 바로 다음의 동작(발사 등)에만 1회 적용되는 스킬

// 스킬 타겟 타입, SKILLTARGETTYPE_XXX
#define SKILLTARGETTYPE_ME								0	// 자기 자신
#define SKILLTARGETTYPE_ONE								1	// 하나의 타겟
#define SKILLTARGETTYPE_PARTY_WITH_ME					2	// 주위의 파티원, 자신 포함
#define SKILLTARGETTYPE_INRANGE_WITH_ME					3	// 주위, 자신 포함
#define SKILLTARGETTYPE_PARTY_WITHOUT_ME				4	// 주위의 파티원, 자신 포함 안 함
#define SKILLTARGETTYPE_INRANGE_WITHOUT_ME				5	// 주위, 자신 포함 안 함
#define SKILLTARGETTYPE_ONE_OURS_INRANGE_WITHOUT_ME		6	// 2010-03-31 by dhjin, 인피니티(기지방어) - 사거리 안에 자신을 제외한 하나의 아군
#define SKILLTARGETTYPE_ALL_OURS_INRANGE_WITHOUT_ME		7	// 2010-03-31 by dhjin, 인피니티(기지방어) - 사거리 안에 자신을 제외한 모든 아군
#define SKILLTARGETTYPE_ONE_ENEMY_INRANGE				8	// 2010-03-31 by dhjin, 인피니티(기지방어) - 사거리 안에 하나의 적
#define SKILLTARGETTYPE_MUTI_ENEMY_INRANGE				9	// 2010-03-31 by dhjin, 인피니티(기지방어) - 사거리 안에 멀티 타겟 수 만큼에 적
#define SKILLTARGETTYPE_ONE_EXCLUDE_ME					11	// 하나의 타겟, 자신은 제외
#define SKILLTARGETTYPE_PARTY_ONE						21	// 아무나 하나의 파티원, // 2005-12-05 by cmkwon
#define SKILLTARGETTYPE_PARTY_ONE_EXCLUDE_ME			22	// 자신을 제외한 하나의 파티원, // 2005-12-05 by cmkwon
#define SKILLTARGETTYPE_ALL_ENEMY						23	// 2006-11-17 by dhjin, 자신을 중심으로 한 적기(타세력, 몬스터, 1:1, 편대전, 여단전)
#define SKILLTARGETTYPE_ONE_EXCEPT_OURS					24	// 2006-11-17 by dhjin, 하나의 타겟, 아군은 제외
#define SKILLTARGETTYPE_ALL_OURS						25  // 2007-02-06 by dhjin, 자신을 중심으로 한 아군기



// 회귀도(Scarcity) 종류
#define SCARCITY_100000			0	// 확률 0~99999
#define SCARCITY_1000000		1	// 확률 0~999999
#define SCARCITY_10000000		2	// 확률 0~9999999

// 아이템의 속성, ITEM_ATTR_XXX
#define ITEM_ATTR_AUTO_PICK_UP			0x00000001		// 1, 몬스터가 터지면 자동으로 먹기(바닥에 안 떨어짐)
#define ITEM_ATTR_NO_TRANSFER			0x00000002		// 2, 창고 이동, 버리기, 상점에서 구입, 상점에 판매, 유저간 거래 불가
#define ITEM_ATTR_QUEST_ITEM			0x00000004		// 4, 퀘스트 아이템, 보통의 경우는 떨어지지 않고, 퀘스트 수행중이며 조건에 만족할 때만 떨어짐, check: deprecated, ITEMKIND_QUEST를 사용, 20040714, kelovon
#define ITEM_ATTR_TIME_LIMITE			0x00000008		// 8, 시간 제한 아이템, 아이템 사용시 사용 시간 제한이 있다
#define ITEM_ATTR_KILL_MARK_ITEM		0x00000010		// 16, 세력전 킬마크 아이템(창고이동/버리기/상점에판매 가능, 유저간거래/상점에서구입 불가), 2006-02-09 by cmkwon
#define ITEM_ATTR_SKILL_SUPPORT_ITEM	0x00000020		// 32, 스킬 보조 아이템, 2006-09-29 by cmkwon 추가 됨
#define ITEM_ATTR_DELETED_TIME_LIMITE	0x00000040		// 64, 아이템이 생성 후 유효 시간(ti_item.Endurance)이 경과하면 자동으로 삭제되는 아이템, 2006-09-29 by cmkwon
#define ITEM_ATTR_ACCOUNT_POSSESSION	0x00000080		// 128, 계정소유아이템(개인창고이동/버리기/상점에판매/상점에서구입 가능, 유저간거래/여단창고이동 불가), // 2007-09-17 by cmkwon, 예당 캐쉬상점 캐쉬아이템 거래 불가 기능 추가 - 

#define ITEM_ATTR_ARENA_ITEM					0x00000100		// 256, 아레나에서만 사용 가능한 아이템, 2007-06-01 by dhjin
#define ITEM_ATTR_SUPER_GAMBLE_ITEM				0x00000200		// 512, // 2007-11-07 by cmkwon, 갬블/슈갬 붙는 시스템 수정 - 슈퍼갬블슈퍼갬블 옵션이 붙을 갬블카드아이템
#define	ITEM_ATTR_PACKAGE_ITEM					0x00000400		// 1024, // 2008-08-26 by cmkwon, ItemAttribute 추가 - 패키지(Package) 아이템, 현재는 미스테리캡슐만 적용됨
#define	ITEM_ATTR_FOR_ONLY_GAME_MASTER			0x00000800		// 2048, // 2008-08-26 by cmkwon, ItemAttribute 추가 - GM용 아이템, RACE_GAMEMASTER 만 사용 가능한 아이템

#define ITEM_ATTR_UNIQUE_ITEM					0x00001000		// 4096, 유니크 아이템, 인챈트/갬블 불가, 2005-11-21 by cmkwon
#define ITEM_ATTR_BAZAAR_ITEM					0x00002000		// 8192, 2006-07-26 by cmkwon, 개인상점에 구입/판매 가능 아이템
#define ITEM_ATTR_LEGEND_ITEM					0x00004000		// 16384, // 2007-08-22 by cmkwon, 레전드 아이템, 기본은 유니크아이템 속성이며 조합시 타겟 아이템이 레전드 이면 인챈트가 유지된다
#define ITEM_ATTR_FORBID_ARENA_COPY_ITEM		0x00008000		// 32768, // 2008-01-07 by dhjin, 아레나 통합 - atum2_db_n => atum2_db_arena 로 td_store를 복사하면 안되는 아이템

#define ITEM_ATTR_CASH_ITEM						0x00010000		// 65536, 유료화 아이템
#define ITEM_ATTR_CASH_ITEM_PREMIUM_CARD		0x00020000		// 131072, // 2008-08-26 by cmkwon, ItemAttribute 추가 - 멤버쉽(프리미엄) 아이템,  

#define ITEM_ATTR_LUCKY_ITEM					0x00040000		// 262144, // 2008-11-04 by dhjin, 럭키머신
#define ITEM_ATTR_DELETED_TIME_LIMITE_AFTER_USED	0x00080000		// 524288, // 2008-11-26 by cmkwon, 사용 후 시간(절대시간) 제한 아이템 구현 - 추가 함

#define ITEM_ATTR_MISSION_MASTER				0x00100000		// 1048576, // 2008-12-15 by dhjin, 미션마스터
#define ITEM_ATTR_ROBOT_ARMOR					0x00200000		// 2097152, // 2009-07-07 by cmkwon, 로봇 아머 관련 처리 추가 - 로봇아머 아이템 속성 추가

#define ITEM_ATTR_CANNOT_USE_INFINITY			0x00400000		// 4194304, // 2009-09-09 ~ 2010 by dhjin, 인피니티 - 인피니티에서 사용 불가 아이템
#define ITEM_ATTR_ONLY_USE_INFINITY				0x00800000		// 8388608, // 2009-09-09 ~ 2010 by dhjin, 인피니티 - 인피니티에서만 사용 가능 아이템
#define ITEM_ATTR_CHECK_SKILL_RESISTANCE_STATE	0x01000000		// 16777216, // 2009-09-09 ~ 2010 by dhjin, 인피니티 - 레지스탕스 키트 적용 여부를 체크해야되는 아이템

#define ITEM_ATTR_NOT_STORE_SAVE				0x02000000		// 33554432, // 2011-06-07 by shcho, 베트남 요청 창고에만 저장 불가 속성 구현

///////////////////////////////////////////////////////////////////////////////
// 2009-04-06 by cmkwon, 스킬 관련 속성 추가안 구현(사용 시간 저장) - ITEM.ItemAttribute 필드를 사용한다.
#define SKILL_ATTR_STORE_USING_TIME				0x00000001		// 1, // 2009-04-06 by cmkwon, 스킬 관련 속성 추가안 구현(사용 시간 저장) - 1, 스킬 사용 시간 저장해야 하는 스킬
#define SKILL_ATTR_PARTY_FORMATION_SKILL		0x00000002		// 2, // 2009-08-03 by cmkwon, EP3-4 편대 대형 스킬 구현 - 편대 대형 스킬

#define SIZE_MAX_STORE_ITEM		sizeof(ITEM_GENERAL)		// check: 아이템의 타입 중 가장 크기가 큰 구조체의 크기

struct ITEM_BASE
{
	INT			ItemNum;						// 아이템 번호
	BYTE		Kind;							// 아이템 종류(기관포, 빔, 로켓, 스킬.....)
	ITEM*		ItemInfo;						// ITEM에 대한 pointer
	UID64_t		UniqueNumber;					// 아이템 고유번호 	
};

#pragma pack(push, 1)
// 일반 아이템(무기류, 방어류, ...)
struct ITEM_GENERAL : public ITEM_BASE
{
	char dunno0[24];
	BYTE			Wear;						// 0: 미장착, 1: 장착, 2:장전, WEAR_XXX
	char dunno1[3];

	INT				CurrentCount;				// 무기: 남은 발수, 에너지: 남은 개수
	UID32_t			AccountUniqueNumber;
	char dunno4[4];
	UID32_t			Possess;					// CharacterUniqueNumber or POSSESS_STORE_NUMBER
	INT				ItemWindowIndex;			// 게임 화면에서 아이템 창에 들어가는 자리
	ATUM_DATE_TIME	CreatedTime;				// 아이템 생성 시간, 2006-09-29 by cmkwon 추가 함 - 일정 시간 후 자동 삭제되는 아이템
	char dunno7[4];
	INT				SuffixCodeNum;				// 접미사, 없으면 0
	char dunno8[20];
	INT				PrefixCodeNum;				// 접두사, 없으면 0
	char dunno9[8];
	/*
	// store-item-specific fields

	BYTE			ItemStorage;				// 0:캐릭터인벤, 1:창고 // 2005-12-07 by cmkwon, 한계정의 캐릭간 창고 공유를 막는다. ITEM_IN_XXX

	// 2009-08-25 by cmkwon, 사용하지 않는 필드 제거(td_Store.ScarcityNumber) -
	//	LONGLONG		ScarcityNumber;




	// derived from 'struct ITEM'
	float			CurrentEndurance;			// 일반 아이템: 남은 내구도, 에너지류(TIMED_HP_UP): 남은 시간

	INT				ColorCode;				// 2009-08-26 by cmkwon, 그래픽 리소스 변경 시스템 구현 - EffectItemNum, 실제로는 무기의 탄두 이펙트 ItemNum을 의미한다, // 튜닝시 아머의 ColorCode
	INT				ShapeItemNum;			// 2009-08-26 by cmkwon, 그래픽 리소스 변경 시스템 구현 -
	UID64_t			MainSvrItemUID;			// 2009-09-09 ~ 2010 by dhjin, 인피니티 - Main서버 아이템 UID 추가

	INT				UsingTimeStamp;				// 아이템이 사용된 시간 초단위(second)
	ATUM_DATE_TIME	UsingStartTime;				// 아이템 사용 시작 시간
	float			DesWeight;					// 중량 인챈트 수치, 2006-01-24 by cmkwon


	INT				CoolingTimeStamp;				// 2009-09-09 ~ 2010-02-10 by dhjin, 인피니티 - 발동류장착아이템
	ATUM_DATE_TIME	CoolingStartTime;				// 2009-09-09 ~ 2010-02-10 by dhjin, 인피니티 - 발동류장착아이템
	*/

	inline ITEM_GENERAL()
	{// 2007-11-27 by cmkwon, 선물하기 로그 수정 - 추가함
		memset(this, 0x00, sizeof(ITEM_GENERAL));
	}
};
#pragma pack(pop)

struct LOG_GUILDSTORE_ITEM_INFO
{// 2006-09-27 by dhjin, 여단 로그 테이블에서 얻어오는 값 저장 구조체
	BYTE			LogType;
	ATUM_DATE_TIME	Time;
	UID32_t			GuildUID;
	CHAR			GuildName[SIZE_MAX_GUILD_NAME];
	UID32_t			AccountUID;
	CHAR			AccountName[SIZE_MAX_ACCOUNT_NAME];
	UID32_t			CharacterUID;
	CHAR			CharacterName[SIZE_MAX_CHARACTER_NAME];
	UID64_t			ItemUID;
	INT				ItemNum;
	CHAR			ItemName[SIZE_MAX_ITEM_NAME];
	INT				PrefixCodeNum;
	INT				SuffixCodeNum;
	INT				ItemResultCount;
	INT				ItemChangeCount;
};

// 스킬류 아이템
struct ITEM_SKILL : public ITEM_BASE
{
	// store-item-specific fields
	UID32_t		AccountUniqueNumber;
	UINT		Possess;
	INT			ItemWindowIndex;				// 게임 화면에서 아이템 창에 들어가는 자리
	ATUM_DATE_TIME	UseTime;					// 2006-11-17 by dhjin, 스킬 사용한 시간					

#ifdef _ATUM_SERVER
//	ITEM_SKILL() {};
	inline ITEM_SKILL(ITEM* pItem)
	{
		if (pItem != NULL)
		{
			*this = *pItem;
			ItemInfo = pItem;
		}
	}
	inline ITEM_SKILL& operator=(const ITEM& rhs)
	{
		this->ItemNum = rhs.ItemNum;
		this->Kind = rhs.Kind;

		return *this;
	}

	void* operator new(size_t size);
	void operator delete(void* p);
#endif // _ATUM_SERVER
};


///////////////////////////////////////////////////////////////////////////////
// 2009-08-03 by cmkwon, EP3-4 편대 대형 스킬 구현 - 
typedef ez_map<INT, ITEM_SKILL*>	mapINT2ItemSkillPtr;		// ItemNum and ITEN_SKILL pointer




///////////////////////////////////////////////////////////////////////////////
// Enchant
///////////////////////////////////////////////////////////////////////////////
struct ENCHANT
{
	UID64_t		TargetItemUniqueNumber;
	INT			TargetItemNum;				// 대상 아이템의 ItemNum
	INT			EnchantItemNum;				// enchant로 쓰인 아이템의 ItemNum

//#ifdef _ATUM_SERVER
//	void * operator new(size_t size);
//	void operator delete(void* p);
//#endif // _ATUM_SERVER
};

struct ENCHANT_INFO
{
	INT			EnchantItemNum;			// 필요한 재료 아이템 넘버
	INT			EnchantItemCount;		// 필요한 재료 개수
	INT			EnchantCost;			// 재료 조합을 위한 수수료
	Prob10K_t	ProbabilityPerLevel[SIZE_MAX_ENCHANT_PER_ITEM];	// 각 레벨에 대한 인첸트 시 조합될 확률
};

#define COUNT_ITEM_MIXING_SOURCE	5
#define COUNT_MAX_MIXING_COUNT		9999	// 2008-03-17 by cmkwon, 조합 시스템 기능 추가 - 한번에 조합 가능한 최대카운트
struct ITEM_MIXING_INFO
{
	INT				TargetItemNum;			// 완성된 재료 ItemNum
	Prob10K_t		MixingProbability;		// 제작될 확률(1~10000)
	INT				MixingCost;				// 재료 조합을 위한 수수료
	ITEM_W_COUNT	SourceItem[COUNT_ITEM_MIXING_SOURCE];	// 필요한 재료 ItemNum 및 개수
	INT				NumOfSourceItems;		// 조합할 아이템의 개수(로딩 시 계산해서 할당하기!)
};

// DBGOUT
#ifdef _ATUM_SERVER
#ifdef _DEBUG
extern void DbgOut(LPCTSTR pFormat, ...);
#define DBGOUT ::DbgOut
#else
#define DBGOUT ((void)0)
#endif
#endif // _ATUM_SERVER

#define SIZE_DES_PARAM_PER_RARE_ITEM_INFO	9

#define RARE_ITEM_USE_TYPE_NORMAL			1		// 일반(드롭시) 사용
#define RARE_ITEM_USE_TYPE_GAMBLE			2		// 갬블 사용
#define RARE_ITEM_USE_TYPE_SUPERGAMBLE		4		// 슈퍼갬블 사용

struct RARE_ITEM_INFO
{
	INT			ReqUseType;			// BitFlag 사용
	INT			ReqMinLevel;
	INT			CodeNum;			// 접두사, 접미사 구분됨
	char		Name[SIZE_MAX_RARE_FIX_NAME];
	BYTE		ReqItemKind;		// 필요아이템종류, 레어가 적용되는 아이템 종류, ITEMKIND_XXX
	GEAR_STAT	ReqGearStat;		// 필요 기어 스탯
	INT			ReqMaxLevel;
	FLOAT		ParameterValue[SIZE_DES_PARAM_PER_RARE_ITEM_INFO];
	Prob100K_t	Probability;		// 레어 아이템 성공 확률, 범위: 1 ~ 100000
	BYTE		DesParameter[SIZE_DES_PARAM_PER_RARE_ITEM_INFO];
};
typedef vector<RARE_ITEM_INFO*>			vectRARE_ITEM_INFOPtrList;		// 2010-04-20 by cmkwon, 신규 러키 머신 구현 - 
typedef map<int, RARE_ITEM_INFO*>		mapRARE_ITEM_INFOPtrList;		// 2010-04-20 by cmkwon, 신규 러키 머신 구현 - <CodeNum, RARE_ITEM_INFO*>

// 1000번대 접두사 5000번대 접미사 1형 아이템
// 2000번대 접두사 6000번대 접미사 2형 아이템
#define IS_RARE_PREFIX(_CODE_NUM)	(_CODE_NUM > 0 && _CODE_NUM < 5000)
#define IS_RARE_SUFFIX(_CODE_NUM)	(_CODE_NUM >= 5000)


///////////////////////////////////////////////////////////////////////////////
// 2010-04-09 by cmkwon, 인피2차 추가 수정(단계별 보상 추가) - DROP_TYPE_XXX
typedef INT		DropType_t;
#define DROP_TYPE_DEAD_MONSTER						0		// 일반 몬스터 폭파시 드랍되는 아이템
#define DROP_TYPE_DEAD_ALL_INFINITY_KEY_MONSTER		1		// 인피니티 보상으로 해당 단계 키몬스터가 모두 폭파시 드랍되는 아이템 리스트

struct MONSTER2ITEM
{
	INT				MonsterUniqueNumber;	// 몬스터 종류
	INT				ItemNumber;				// 아이템고유넘버
	INT				MinCount;				// 생성할 아이템의 최소 개수
	INT				MaxCount;				// 생성할 아이템의 최대 개수, 만약 개수가 정해져 있다면 MinCount = MixCount
	Prob1000K_t		Probability;			// 생성 확률: 0 ~ 1000000
	Prob100K_t		PrefixProbability;		// 접두사가 붙을 확률, 0 ~ 100000
	Prob100K_t		SuffixProbability;		// 접미사가 붙을 확률, 0 ~ 100000
	INT				QuestIndex;				// 퀘스트 아이템일 경우 QuestIndex 저장, 아니면 0
	DropType_t		DropType;				// DROP_TYPE_XXX // 2010-04-09 by cmkwon, 인피2차 추가 수정(단계별 보상 추가) - 
};

struct CHARACTER2ITEM		// 2006-03-02 by cmkwon
{
	INT				ItemNumber;				// 아이템고유넘버
	INT				MinCount;				// 생성할 아이템의 최소 개수
	INT				MaxCount;				// 생성할 아이템의 최대 개수, 만약 개수가 정해져 있다면 MinCount = MixCount
	Prob1000K_t		Probability;			// 생성 확률: 0 ~ 1000000
	INT				QuestIndex;				// 퀘스트 아이템일 경우 QuestIndex 저장, 아니면 0
};
typedef vector<CHARACTER2ITEM>			vectCHARACTER2ITEM;

struct CHARACTER2ITEMLIST		// 2006-03-02 by cmkwon
{
	BYTE				InfluenceType0;			// 세력 타입으로
	USHORT				UnitKindMask0;			// 유닛의 종류
	vectCHARACTER2ITEM	vectCharacter2Item;
};
typedef vector<CHARACTER2ITEMLIST>		vectCHARACTER2ITEMLIST;


#ifndef _ATUM_CLIENT
struct PROJECTINFO
{
	int				m_useTileSetIndex;
	MapIndex_t		m_nMapIndex;
	USHORT			m_nCreateChannelCounts;
	char			m_strFieldIP[SIZE_MAX_IPADDRESS];
	short			m_sFieldListenPort;
	short			m_sFieldUDPPort;
	char			m_strNPCIP[SIZE_MAX_IPADDRESS];
	short			m_sNPCListenPort;
	short			m_sNPCUDPPort;
	short			m_sXSize;						// map의 가로 타일 수
	short			m_sYSize;						// map의 세로 타일 수
	short			m_sMaximumAltitude;				// map의 최대 이동 가능 고도
	short			m_sMinimumAltitude;				// map의 최저 이동 가능 고도
	short			m_sWaterAltitude;				// map의 물 높이
	float			m_fFrontPositionDistance;		// 2004-04-09 by cmkwon, 몬스터의 다음 좌표를 구하기 위한 거리, 맵별로 다를수 있다.
	BOOL			m_bCreateNPCThread;
	BOOL			m_bAutoCreateMonster;
	MapIndex_t		m_DeadDefaultMapIndex;			// 2004-03-26 by cmkwon, 캐릭이 죽었을 때 가야하는 default map과 관련
//	BOOL			m_bGuildWarMap;					// 길드전 전용 맵인지 여부
	BOOL			m_bAutoDPRecovery;				// 2004-03-26 by cmkwon, 자동 DP 회복 여부
//	BOOL			m_bTutorialMap;					// 2004-03-26 by cmkwon, 튜토리얼 맵인지 여부
	DWORD			m_dwMaxUserCounts;				// 2004-11-22 by cmkwon, 채널당 Max 유저 카운트(혼잡도계산을 위해 필요) //2004-03-26 by cmkwon, 해당 맵이각 채널당 사용가능한 Bandwidth (config 화일에는 Mbps 로 저장 되어있고 loading시에 bps 단위로 변경한다)
	D3DXVECTOR3		m_CityWarpTargetPosition;		// 도시 맵의 강제 워프 타겟 좌표 설정 위해
	int				m_nUserVisibleDiameter;			// 유저 Move 전송 거리, 지름
	int				m_nMonsterVisibleDiameter;		// 몬스터 Move 전송 거리, 지름
	int				m_nQuestIndexForWarp;			// 이맵으로 가기 위해서는 이퀘스트를 꼭 완료해야한다.
	int				m_nMapInfluenceType;			// 2005-12-28 by cmkwon, 맵의 세력 설정(MAP_INFLUENCE_XXX)
	MapIndex_t		m_nBeforeMapIndex;				// 2006-08-02 by cmkwon, 타세력맵에서 죽었을 경우 부활시 여기에 설정된 맵에서 부활됨
	INT				m_VCNWarpObjectIndex;			// 2006-12-08 by cmkwon
	INT				m_ANIWarpObjectIndex;			// 2006-12-08 by cmkwon
	INT				m_TeleportWarpObjectIndex;		// 2007-09-15 by dhjin
	MapIndex_t		m_nBeforeMapIndex2;				// 2008-06-20 by cmkwon, EP3 백맵 시스템 수정(맵당 백맵을 2개 설정 할 수 있다) - 


	PROJECTINFO()
	{
	}
	PROJECTINFO(PROJECTINFO& i_refPrj)
	{
		*this = i_refPrj;
	}

	///////////////////////////////////////////////////////////////////////////////
	// 2008-06-20 by cmkwon, EP3 백맵 시스템 수정(맵당 백맵을 2개 설정 할 수 있다) - 
	BOOL IsValidBeforeMapIndex(void)
	{
		if (0 != m_nBeforeMapIndex
			|| 0 != m_nBeforeMapIndex2)
		{
			return TRUE;
		}

		return FALSE;
	}
};
#endif // _ATUM_CLIENT

struct GBUFFER
{
	char	ptr[SIZE_MAX_LONG_PACKET];
	int		size;

	void Reset() { size = 0; }
	char* GetPtr() { return ptr; }
	//int GetSize() { ASSERT_ASSERT(size <= SIZE_MAX_LONG_PACKET); return size; }
};

#ifndef SIZE_MAX_PACKET
#define SIZE_MAX_PACKET						1492	// 패킷 최대 사이즈(여러개의 메세지가 하나의 패킷으로 전송될수 있음)
#endif

struct GBUFFER_SIZE_MAX_PACKET
{
	char	ptr[SIZE_MAX_PACKET];
	int		size;

	void Reset() { size = 0; }
	char* GetPtr() { return ptr; }
	//int GetSize() { ASSERT_ASSERT(size <= SIZE_MAX_PACKET); return size; }
};

// Field Server의 ID의 관리를 위해
struct SERVER_ID
{
	// member functions
	SERVER_ID() { Reset(); }
	SERVER_ID(char* IP, int port) { Reset(); SetValue(IP, port); }
	SERVER_ID(const char* szIPPort) { Reset(); SetValue(szIPPort); }
	inline void SetValue(char* IP, int port);
	inline void SetValue(const char* szIPPort);
	inline bool CompareValue(char* IP, int port);
	inline const char* GetString(char* buffer);
	inline const char* GetString(std::string& str);
	inline bool operator==(SERVER_ID& rhs);
	inline bool operator!=(SERVER_ID& rhs);
	inline void Reset() { memset(this, 0, sizeof(SERVER_ID)); }

	// member variables
	char	IP[SIZE_MAX_IPADDRESS];
	int		port;
};




///////////////////////////////////////////////////////////////////////////////
// Version Management
///////////////////////////////////////////////////////////////////////////////
class VersionInfo
{
public:
	VersionInfo()
	{
		memset(this, 0x00, sizeof(VersionInfo));
		m_bIsValid = FALSE;				// 2006-12-28 by cmkwon
	}

protected:
	BOOL	m_bIsValid;				// 2006-12-28 by cmkwon, 
	USHORT	version[SIZE_MAX_VERSION];
	char	strBuf[SIZE_MAX_VERSION_STRING];
};
typedef mt_map<VersionInfo, VersionInfo>					mtmapVersionInfo;

bool operator<(const VersionInfo& v1, const VersionInfo& v2);

struct MAP_INFO
{
	MapIndex_t		MapIndex;						// 
	MapIndex_t		RenderMapIndex;					// Render 관련 정보는 이맵의 인덱스 정보와 같음, 아래 파라미터는 설정하지 않아도됨
	MapIndex_t		BeforeMapIndex;					// 2006-08-02 by cmkwon, 타세력맵에서 죽었을 경우 부활시 여기에 설정된 맵에서 부활됨
	char			MapName[SIZE_MAX_MAP_NAME];
	SHORT			MapInfluenceType;				// 맵의 세력 타입 설정(MAP_INFLUENCE_XXX)
	MapIndex_t		CityMapIndex;					// 도시점령전 점령 격납고 맵인덱스
	INT				CityWarQuestIndex;				// 
	INT				CityWarQuestNPCIndex;
	INT				CityWarQuestMonsterUID;
	SHORT			MaxUserCount;
	SHORT			MaxGroundHeight;				// 지상으로부터 최대 높이
	SHORT			MinGroundHeight;				// 지상으로부터 최소 높이
	SHORT			WaterHeight;
	SHORT			UserVisibleDistance;
	SHORT			MonsterVisibleDistance;
	INT				QuestIndexForWarp;
	SHORT			FrontPositionDistance;
	BYTE			AutoRecoveryFlag;
	MapIndex_t		DefaultMapIndex;
	AVECTOR3		CityWarpTargetPosition;
	SHORT			ClientMaxAltitudeHeight;		// 클라이언트 최대 높이, 2005-07-11 by cmkwon
	DWORD			DayFogColor;
	DWORD			NightFogColor;
	SHORT			DayFogStartDistance;
	SHORT			DayFogEndDistance;
	SHORT			NightFogStartDistance;
	SHORT			NightFogEndDistance;
	AVECTOR3		DaySunDirection;
	AVECTOR3		NightSunDirection;
	BYTE			WaterType;
	BYTE			PKZoneFlag;
	BYTE			TileRenderingFlag;
	BYTE			SkyRenderingFlag;
	BYTE			SunRenderingFlag;
	BYTE			FogRenderingFlag;
	INT				VCNWarpObjectIndex;			// 2006-12-08 by cmkwon
	INT				ANIWarpObjectIndex;			// 2006-12-08 by cmkwon
	MapIndex_t		Dat;						// 2007-03-15 by dhjin
	MapIndex_t		Map;						// 2007-03-15 by dhjin
	MapIndex_t		Tex;						// 2007-03-15 by dhjin
	MapIndex_t		Cloud;						// 2007-03-15 by dhjin
	MapIndex_t		Sky;						// 2007-03-15 by dhjin
	MapIndex_t		Nsky;						// 2007-03-15 by dhjin
	MapIndex_t		Bgm;						// 2007-03-15 by dhjin
	INT				TeleportWarpObjectIndex;	// 2007-09-05 by dhjin
	MapIndex_t		BeforeMapIndex2;			// 2008-06-20 by cmkwon, EP3 백맵 시스템 수정(맵당 백맵을 2개 설정 할 수 있다) - 
	char			MapDescription[SIZE_MAX_MAP_DESCRIPTION];		// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 
	void ResetMAP_INFO(void)
	{
		memset(this, 0x00, sizeof(*this));
	}
};
typedef vector<MAP_INFO>		vectorMAP_INFO;



enum EN_CHECK_TYPE
{
	CHECK_TYPE_BATTLE_P2P_PK = 0,		// 1:1 대결 
	CHECK_TYPE_BATTLE_PARTY_WAR = 1,		// 편대전
	CHECK_TYPE_CHARACTER_MENT = 2,		// "/멘트' 명령어
	CHECK_TYPE_PENALTY_ON_DEAD = 3,		// 캐릭터 죽었을 때 패널티(경험치 다운 or SPI 다운) 적용 레벨
	CHECK_TYPE_TRADE = 4,		// 유저간 거래// 2005-12-06 by cmkwon
	CHECK_TYPE_BATTLE_GUILD_WAR = 5,		// 여단전
	CHECK_TYPE_LOWLEVEL_ADVANTAGE = 6,		// 낮은 레벨 혜택
	CHECK_TYPE_BAZAAR = 7,		// 2006-08-07 by cmkwon, 개인 상점 거래(구입/판매 상점)

	CHECK_TYPE_GUILD_CREATE = 10,		// 길드 생성
	CHECK_TYPE_GUILD_JOIN = 11,		// 여단 가입// 2005-12-07 by cmkwon

	CHECK_TYPE_PARTY_JOIN = 20,		// 파티 가입// 2005-12-07 by cmkwon

	CHECK_TYPE_CHAT_ALL = 100,		// 채팅 - 전체채팅// 2005-12-07 by cmkwon
	CHECK_TYPE_CHAT_MAP = 101,		// 채팅 - 맵채팅// 2005-12-07 by cmkwon
	CHECK_TYPE_CHAT_REGION = 102,		// 채팅 - 지역채팅// 2005-12-07 by cmkwon
	CHECK_TYPE_CHAT_PTOP = 103,		// 채팅 - 귓말채팅// 2005-12-07 by cmkwon
	CHECK_TYPE_CHAT_SELL_ALL = 104,		// 매매 채팅
	CHECK_TYPE_CHAT_CASH_ALL = 105,		// 채팅 - 유료전체채팅// 2005-12-07 by cmkwon
	//////////////////////////////////////////////////////////////////////////
	// 2008-06-17 by dhjin, EP3 VOIP - 시스템 변경으로 밑과 같이 수정
//	CHECK_TYPE_VOIP_1to1			= 106,		// 음성채팅 - 1:1 채팅// 2005-12-07 by cmkwon
//	CHECK_TYPE_CHAT_WAR				= 107		// 2008-05-19 by dhjin, EP3 - 채팅 시스템 변경, 전쟁 채팅
CHECK_TYPE_CHAT_WAR = 106,		// 2008-05-19 by dhjin, EP3 - 채팅 시스템 변경, 전쟁 채팅

CHECK_TYPE_VOIP_NONE = 201,		// 2008-06-17 by dhjin, EP3 VOIP - 음성채팅중이 아니다.
CHECK_TYPE_VOIP_1to1 = 202,		// 음성채팅 - 1:1 채팅// 2005-12-07 by cmkwon
CHECK_TYPE_VOIP_PARTY = 203,		// 2008-06-17 by dhjin, EP3 VOIP - 파티 음성 채팅
CHECK_TYPE_VOIP_GUILD = 204		// 2008-06-17 by dhjin, EP3 VOIP - 여단 음성 채팅

};
BOOL GCheckLimitLevel(EN_CHECK_TYPE i_checkType, int i_nLevel);
BOOL GCheckRaceAndInfluenceType(EN_CHECK_TYPE i_checkType, USHORT i_usRace, BYTE i_byInfluenceTy, USHORT i_usPeerRace, BYTE i_byPeerInfluenceTy);

// UID32_t(Unique Number) Generator
class CUID32Generator
{
public:
	CUID32Generator(UID32_t min = 1, UID32_t max = ((UID32_t)~0) - 1)
	{
		m_num = min - 1;
		m_min = min;
		m_max = max;
	}
	inline UID32_t GetNext()
	{
		if (m_num < m_min - 1) return INVALID_UID32;
		if (m_num > m_max) Reset();
		return ++m_num;
	}
	inline UID32_t GetCurrent() { return m_num; }
	inline void Reset() { m_num = m_min - 1; }
	inline UID32_t GetMin() { return m_min; }
	inline UID32_t GetMax() { return m_max; }
private:
	UID32_t	m_num;	// 현재 생성된 UID32
	UID32_t	m_min;	// 최소 UID32
	UID32_t	m_max;	// 최대 UID32
};

// UID16_t(Unique Number) Generator
class CUID16Generator
{
public:
	CUID16Generator(UID16_t min = 1, UID16_t max = ((UID16_t)~0) - 1)
	{
		m_num = min - 1;
		m_min = min;
		m_max = max;
	}
	inline UID16_t GetNext()
	{
		if (m_num < m_min - 1) return INVALID_UID16;
		if (m_num > m_max) Reset();
		return ++m_num;
	}
	inline UID16_t GetCurrent() { return m_num; }
	inline void Reset() { m_num = m_min - 1; }
	inline UID16_t GetMin() { return m_min; }
	inline UID16_t GetMax() { return m_max; }
private:
	UID16_t	m_num;	// 현재 생성된 UID16
	UID16_t	m_min;	// 최소 UID16
	UID16_t	m_max;	// 최대 UID16
};

///////////////////////////////////////////////////////////////////////////////
// Admin Tool용 Server List
///////////////////////////////////////////////////////////////////////////////
// 2007-10-24 by cmkwon, 서버 정보 암호화 - 아래와 같이 수정함
//struct GAME_SERVER_INFO_FOR_ADMIN
//{
//	const char	*ServerName;
//	const char	*ServerIP;
//	const char	*DBIP;
//	int			DBPort;
//	const char	*DBUID;
//	const char	*DBPWD;
//	const char	*DBName;
//};
struct GAME_SERVER_INFO_FOR_ADMIN
{
	const char* ServerName;
	// 2009-01-15 by cmkwon, PreServer, DBServer 정보 DNS로 설정 가능하게 수정 - 아래와 같이 수정 함.
	//	char		XOREncodedServerIP[2*SIZE_MAX_IPADDRESS];		// 2007-10-24 by cmkwon, 서버 정보 암호화 - 추가된 필드
	//	char		XOREncodedDBIP[2*SIZE_MAX_IPADDRESS];			// 2007-10-24 by cmkwon, 서버 정보 암호화 - 추가된 필드
	char		XOREncodedServerIP[2 * SIZE_MAX_ADDRESS];		// 2009-01-15 by cmkwon, PreServer, DBServer 정보 DNS로 설정 가능하게 수정 - 
	char		XOREncodedDBIP[2 * SIZE_MAX_ADDRESS];			// 2009-01-15 by cmkwon, PreServer, DBServer 정보 DNS로 설정 가능하게 수정 - 
	int			DBPort;
	char		XOREncodedDBUID[2 * SIZE_MAX_DB_USER_ID];		// 2007-10-24 by cmkwon, 서버 정보 암호화 - 추가된 필드
	char		XOREncodedDBPWD[2 * SIZE_MAX_DB_USER_PWD];		// 2007-10-24 by cmkwon, 서버 정보 암호화 - 추가된 필드
	const char* DBName;
	// 2009-01-15 by cmkwon, PreServer, DBServer 정보 DNS로 설정 가능하게 수정 - 아래와 같이 수정 함.
	//	char		LogDBIP[2*SIZE_MAX_IPADDRESS];			// 2007-11-07 by cmkwon, 로그 DB 서버 따로 구축하기 - XOR 암호화되어 있음, 복호화 하여 사용 해야 함
	char		LogDBIP[2 * SIZE_MAX_ADDRESS];			// 2009-01-15 by cmkwon, PreServer, DBServer 정보 DNS로 설정 가능하게 수정 - 
	int			LogDBPort;								// 2007-11-07 by cmkwon, 로그 DB 서버 따로 구축하기 - XOR 암호화되어 있음, 복호화 하여 사용 해야 함
	char		LogDBUID[2 * SIZE_MAX_DB_USER_ID];		// 2007-11-07 by cmkwon, 로그 DB 서버 따로 구축하기 - XOR 암호화되어 있음, 복호화 하여 사용 해야 함
	char		LogDBPWD[2 * SIZE_MAX_DB_USER_PWD];		// 2007-11-07 by cmkwon, 로그 DB 서버 따로 구축하기 - XOR 암호화되어 있음, 복호화 하여 사용 해야 함
// 2009-01-15 by cmkwon, PreServer, DBServer 정보 DNS로 설정 가능하게 수정 - 아래와 같이 수정 함.
//	char		ServerIP[SIZE_MAX_IPADDRESS];
//	char		DBIP[SIZE_MAX_IPADDRESS];
	char		ServerIP[SIZE_MAX_ADDRESS];				// 2009-01-15 by cmkwon, PreServer, DBServer 정보 DNS로 설정 가능하게 수정 - 
	char		DBIP[SIZE_MAX_ADDRESS];					// 2009-01-15 by cmkwon, PreServer, DBServer 정보 DNS로 설정 가능하게 수정 - 
	char		DBUID[SIZE_MAX_DB_USER_ID];
	char		DBPWD[SIZE_MAX_DB_USER_PWD];
};



///////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////
enum EN_CASH_PREMIUM_CARD_STATE
{
	CASH_PREMIUM_CARD_STATE_NOT_EXIST = 0,
	CASH_PREMIUM_CARD_STATE_NORMAL = 1,
	CASH_PREMIUM_CARD_STATE_INSERTING = 2,
	CASH_PREMIUM_CARD_STATE_UPDATING = 3,
	CASH_PREMIUM_CARD_STATE_DELETING = 4
};

struct SCASH_PREMEIUM_CARD_INFO
{
	EN_CASH_PREMIUM_CARD_STATE	enCardState;
	UID64_t			n64UniqueNumber10;
	UID32_t			nAccountUID10;
	INT				nCardItemNum;
	ATUM_DATE_TIME	atumTimeCreatedTime;	// 생성된 시간
	ATUM_DATE_TIME	atumTimeUpdatedTime;	// 수정된 시간
	ATUM_DATE_TIME	atumTimeExpireTime;		// 만료 시간

	float			fExpRate;
	float			fSPIRate;
	float			fDropRate;
	float			fDropRareRate;
	float			fExpRepairRate;

	int				nInventoryPlusCounts;		// 2006-09-06 by cmkwon, 인벤토리 추가 카운트
	int				nStorePlusCounts;			// 2006-09-06 by cmkwon, 창고 추가 카운트
	int				nGuildCapacityPlusCounts;	// 2006-09-06 by cmkwon, 여단원 추가 카운트
};

struct SCITY_OCCUPY_INFO
{
	UID32_t			OccupyGuildUID;
	char			OccupyGuildName[SIZE_MAX_GUILD_NAME];
	UID32_t			OccupyGuildMasterCharacterUID;
	float			fTexPercent;								// 세금 퍼센트(2 ~ 100)
	ATUM_DATE_TIME	CityWarDefaultTime;
	ATUM_DATE_TIME	CityWarSettingTime;
	INT				nDefenseCounts;
	INT				nSumOfTex;
	char			szBriefing[SIZE_MAX_CITY_BRIEFING_LENGTH];

	void ResetCITY_OCCUPY_INFO(void);
};

struct SCOUPON
{
	INT					nCouponUniqueNumber;
	char				szCouponNumber[SIZE_MAX_COUPON_NUMBER];
	ATUM_DATE_TIME		atimeExpireTime;
	BOOL				bUsedFlag;
	char				szUsedAccountName[SIZE_MAX_ACCOUNT_NAME];
	ATUM_DATE_TIME		atimeUsedTime;
};


enum EN_BLOCKED_TYPE
{
	T_BLOCKEDACCOUNT_UNKNOWN = 0,		// 알수 없음
	T_BLOCKEDACCOUNT_NORMAL = 1,		// 특별한 사유 없음, 임시로
	T_BLOCKEDACCOUNT_MONEY_RELATED = 2,		// 돈 관련 - SPI, 			
	T_BLOCKEDACCOUNT_ITEM_RELATED = 3,		// 아이템 관련 - 사기(아이템 구매, 판매)  
	T_BLOCKEDACCOUNT_SPEEDHACK_RELATED = 4,		// 스피드핵 관련
	T_BLOCKEDACCOUNT_CHAT_RELATED = 5,		// 채팅 관련 - 욕설 
	T_BLOCKEDACCOUNT_CHAT_GAMEBUG = 6			// 게임 버그 관련 - 게임 버그 이용한 유저
};

char* GetStringBLOCKED_TYPE(int i_blocktype);
int GetBlockTypeBYBlockTypeString(char* i_szTyString);	// 2008-01-30 by cmkwon, 계정 블럭 로그 남기기 구현 - GetBlockTypeBYBlockTypeString() 추가
struct SBLOCKED_ACCOUNT_INFO
{
	char			szBlockedAccountName[SIZE_MAX_ACCOUNT_NAME];
	EN_BLOCKED_TYPE	enBlockedType;
	ATUM_DATE_TIME	atimeStartTime;
	ATUM_DATE_TIME	atimeEndTime;
	INT				AdminFieldServerClientIndex;		// 2008-01-31 by cmkwon, 계정 블럭/해제 명령어로 가능한 시스템 구현 - PreServer<->FieldServer 에서만 사용함
	char			szBlockAdminAccountName[SIZE_MAX_ACCOUNT_NAME];
	char			szBlockedReasonForUser[SIZE_MAX_BLOCKED_ACCOUNT_REASON];
	char			szBlockedReasonForOnlyAdmin[SIZE_MAX_BLOCKED_ACCOUNT_REASON];		// 2007-01-10 by cmkwon
};

///////////////////////////////////////////////////////////////////////////////
// 2006-04-12 by cmkwon, 세력전 보강 시스템으로 추가됨
#define MAX_INFLUENCEWAR_WARTIMESTAGE			5		// 2006-04-13 by cmkwon, 0 ~ 5
#define MAX_INFLUENCEWAR_EVENT_SUMMON_COUNT		5		// 2006-04-13 by cmkwon
#define	STRATEGYPOINT_MONSTER_NUM_VCN			2052000	// 2007-11-07 by dhjin, 전략포인트 VCN번호
#define	STRATEGYPOINT_MONSTER_NUM_ANI			2052100	// 2007-11-07 by dhjin, 전략포인트 ANI번호

struct SDB_INFLUENCE_WAR_INFO
{
	BYTE			InfluenceType;					// INFLUENCE_TYPE_VCN(2) or INFLUENCE_TYPE_ANI(4)
	BYTE			WartimeStage;					// 전시단계
	INT				ReqContributionPoint;			// 전시단계가 되기 위한 필요 기여도(ContributionPoint)
	float			HPRepairRate;					// 해당 전시단계 일 때 HP회복률                            
	float			DPRepairRate;					// 해당 전시단계 일 때 DP회복률                            
	float			SPRepairRate;					// 해당 전시단계 일 때 SP회복률                            
	INT				EventTime;						// 세력전보스몬스터 격추 후 해당 전시단계에 시작되는 이벤트 지속 시간(단위:분)
	float			EventExperience;				// 세력전보스몬스터 격추 후 해당 전시단계에 시작되는 이벤트 이벤트 - 경험치          
	float			EventDropSPI;					// 세력전보스몬스터 격추 후 해당 전시단계에 시작되는 이벤트 이벤트 - 드랍 SPI        
	float			EventDownExperience;			// 세력전보스몬스터 격추 후 해당 전시단계에 시작되는 이벤트 이벤트 - 경험치 드랍     
	float			EventDropItem;					// 세력전보스몬스터 격추 후 해당 전시단계에 시작되는 이벤트 이벤트 - 드랍 Item       
	float			EventDropRareItem;				// 세력전보스몬스터 격추 후 해당 전시단계에 시작되는 이벤트 이벤트 - 드랍 레어 Item  
	INT				SupplyItemNum;					// 세력전보스몬스터 격추 후 해당 전시단계에 지급되는 ItemNum
	INT				SupplyItemCount;				// 세력전보스몬스터 격추 후 해당 전시단계에 지급되는 Item Count
	BYTE			IsSummonJacoMonster;
	INT				BossMonsterUnitKind;			// 각 단계 필요 기여도를 넘어서는 시점에 소환되는 세력전보스몬스터 MonsterUnitKind          
	INT				BossMonsterCount;				// 각 단계 필요 기여도를 넘어서는 시점에 소환되는 Monster count
	INT				BossMonsterSummonTerm;			// 각 단계 필요 기여도를 넘어서는 시점에 소환되는 세력전보스몬스터가 소환되는 시간 텀(예상 15분, 단위:분)
	SHORT			BossMonsterSummonMapIndex;		// 각 단계 필요 기여도를 넘어서는 시점에 소환되는 세력전보스몬스터가 소환되는 MapIndex        
	SHORT			BossMonsterSummonPositionX;		// 각 단계 필요 기여도를 넘어서는 시점에 소환되는 세력전보스몬스터가 소환되는 좌표 x                   
	SHORT			BossMonsterSummonPositionY;		// 각 단계 필요 기여도를 넘어서는 시점에 소환되는 세력전보스몬스터가 소환되는 좌표 y                   
	SHORT			BossMonsterSummonPositionZ;		// 각 단계 필요 기여도를 넘어서는 시점에 소환되는 세력전보스몬스터가 소환되는 좌표 z                   
	INT				SummonMonsterUnitKind[MAX_INFLUENCEWAR_EVENT_SUMMON_COUNT];		// 세력전보스몬스터 격추 후 해당 전시단계에 소환되는 MonsterUnitKind
	INT				SummonCount[MAX_INFLUENCEWAR_EVENT_SUMMON_COUNT];				//  소환되는 Monster Count
	SHORT			SummonMapIndex[MAX_INFLUENCEWAR_EVENT_SUMMON_COUNT];			//  몬스터가 소환되는 MapIndex
	SHORT			SummonPositionX[MAX_INFLUENCEWAR_EVENT_SUMMON_COUNT];			//  소환되는 좌표 x
	SHORT			SummonPositionY[MAX_INFLUENCEWAR_EVENT_SUMMON_COUNT];			//  소환되는 좌표 y
	SHORT			SummonPositionZ[MAX_INFLUENCEWAR_EVENT_SUMMON_COUNT];			//  소환되는 좌표 z
	INT				SupplyItemNum2;					// 세력전보스몬스터 격추 후 해당 전시단계에 지급되는 ItemNum	// 2007-05-16 by dhjin, 추가됨
	INT				SupplyItemCount2;				// 세력전보스몬스터 격추 후 해당 전시단계에 지급되는 Item Count	// 2007-05-16 by dhjin, 추가됨
	INT				WinBossMonsterUnitKind;			// 2009-03-10 by dhjin, 단계별 모선 시스템 - 공격 모선 승리 세력일 경우 소환되어야 되는 모선UID
	INT				LossBossMonsterUnitKind;		// 2009-03-10 by dhjin, 단계별 모선 시스템 - 공격 모선 패배 세력일 경우 소환되어야 되는 모선UID

	// 2008-05-20 by cmkwon, 모든 이벤트(HappyHoure,MotherShip,Item) 그룹 동시에 가능하게 - 
	BOOL IsValidGameEvent(void)
	{
		if (0 >= EventTime)
		{
			return FALSE;
		}

		if (0.0f < EventExperience
			|| 0.0f < EventDropSPI
			|| 0.0f < EventDownExperience
			|| 0.0f < EventDropItem
			|| 0.0f < EventDropRareItem)
		{
			return TRUE;
		}

		return FALSE;
	}
};
typedef vector<SDB_INFLUENCE_WAR_INFO>			vectDB_INFLUENCE_WAR_INFO;

struct SINFLUENCE_WAR_DATA
{
	BYTE			InfluenceType;			// INFLUENCE_TYPE_VCN(2) or INFLUENCE_TYPE_ANI(4)
	INT				MGameServerID;			// 서버군 채널 고유 번호 - global.cfg 파일에 설정한다.
	BYTE			WartimeStage;			// 현재 전시단계
	INT				ContributionPoint;		// 누적 기여도 - 아마 한달 누적 기여도가 될것이다
	UID32_t			InflLeaderCharacterUID;	// 세력 지도자 CharacterUID
	UID32_t			InflSub1LeaderCharacterUID;	// 2006-12-08 by dhjin, 부지도자1
	UID32_t			InflSub2LeaderCharacterUID; // 2006-12-08 by dhjin, 부지도자2
	CHAR			InflLeaderCharacterName[SIZE_MAX_CHARACTER_NAME];		// 2007-12-03 by dhjin, 지도자 
	CHAR			InflSubLeader1CharacterName[SIZE_MAX_CHARACTER_NAME];	// 2007-12-03 by dhjin, 부지도자1
	CHAR			InflSubLeader2CharacterName[SIZE_MAX_CHARACTER_NAME];	// 2007-12-03 by dhjin, 부지도자2
	SHORT			MSWarOptionType;		// 2008-04-10 by dhjin, 모선전 정보 표시 기획안 - 
};

struct SINFLBOSS_MONSTER_SUMMON_DATA
{
	MONSTER_INFO* pMonsterInfo;				// 세력전보스몬스터 정보
	INT				SummonCount;				// 소환될 Monster Count
	INT				SummonTerm;					// 소환되기 위힌 시간 텀(예상 15분, 단위:분)
	ATUM_DATE_TIME	atimeInsertedTime;			// 소환 몬스터 추가된 시간 - 소환되기 우한 시간 텀 처리를 위해 필요
	SHORT			SummonMapIndex;				// 세력전보스몬스터가 소환되는 MapIndex
	AVECTOR3		SummonPosition;				// 세력전보스몬스터가 소환되는 좌표
	BYTE			BossStep;					// 2009-03-10 by dhjin, 단계별 모선 시스템 - 모선 단계
	BYTE			BeforeWinCheck;				// 2009-03-10 by dhjin, 단계별 모선 시스템 - 전 단계 승패 여부
};

int GDelimiterIndex(char* i_szStr, int i_nMinIndex);

struct SSUMMONBOSSMONSTER_INFO
{// 2007-02-06 by dhjin, 소환 몬스터 정보 
	BOOL			bSummonBossMonster;
	ATUM_DATE_TIME	SummonBossTime;
	INT				SummonMonsterUnitkind;
	INT				ContributionPoint;			// 2008-04-01 by dhjin, 모선전, 거점전 정보창 기획안 - 
	BYTE			BossStep;					// 2009-03-10 by dhjin, 단계별 모선 시스템 - 모선 단계
	BYTE			BeforeWinCheck;				// 2009-03-10 by dhjin, 단계별 모선 시스템 - 전 단계 승패 여부
};

struct SDELETED_CHARACTER_INFO
{// 2007-02-22 by dhjin, 케릭터 복구 정책으로 인한 삭제된 케릭터 정보 구조체.
	UID32_t			AccountUID;
	CHAR 			AccountName[SIZE_MAX_ACCOUNT_NAME];
	UID32_t			CharacterUID;
	CHAR 			CharacterName[SIZE_MAX_CHARACTER_NAME];
	BYTE			InflueceType0;			// 2008-01-17 by cmkwon, T_A: 삭제 상태의 캐릭터 의 세력, 선택 가능한 세력 보여주기 추가 - SDELETED_CHARACTER_INFO 에 필드 추가
	BYTE			SelectableInflueceMask;	// 2008-01-17 by cmkwon, T_A: 삭제 상태의 캐릭터 의 세력, 선택 가능한 세력 보여주기 추가 - SDELETED_CHARACTER_INFO 에 필드 추가
	ATUM_DATE_TIME	atDeletedDTime;			// 2008-03-03 by cmkwon, 삭제 상태의 캐릭터리스트 정보에 삭제 된 날짜 보여 주기 - 
};

struct SSUMMON_STRATEGYPOINT_INFO
{// 2007-02-23 by dhjin, /거점정보 명령어
	MapIndex_t		MapIndex;
	BYTE			InfluenceType;
	CHAR			MapName[SIZE_MAX_MAP_NAME];
	ATUM_DATE_TIME	SummonStrategyPointTime;
};

struct SSTRATEGYPOINT_SUMMONTIME_INFO
{// 2007-02-28 by dhjin, 전략포인트 생성 정보 구조체
	MapIndex_t		MapIndex;
	BYTE			SummonCount;
	ATUM_DATE_TIME	SummonTime;
	BOOL			SummonAttribute;		// 2008-04-08 by dhjin, 소환 가능 시간 설정 - 
};
typedef vector<SSTRATEGYPOINT_SUMMONTIME_INFO>	vectSSTRATEGYPOINT_SUMMONTIME_INFO;

struct SSTRATEGYPOINT_SUMMON_RANGE
{// 2007-02-28 by dhjin, 전략포인트 생성 주기 구조체
	SHORT			SummonRange;
	BOOL			StrategyPointSummonCheck;
	BYTE			MaxSummonCountDaily;
	ATUM_DATE_TIME	StartTime;
	ATUM_DATE_TIME	EndTime;
	SHORT			NewSummonRange;
	BYTE			NewMaxSummonCountDaily;
};

struct SSTRATEGYPOINT_NOT_SUMMON_TIME
{// 2007-02-28 by dhjin, 전략포인트 생성되면 안되는 요일별 시간 정보 구조체
	SHORT			DayOfWeek;
	ATUM_DATE_TIME	StartTime;
	ATUM_DATE_TIME	EndTime;
	BOOL			CheckSummon;			// 2008-04-04 by dhjin, 소환 가능 시간 설정 - 0:금지시간 , 1:소환시간
};
typedef vector<SSTRATEGYPOINT_NOT_SUMMON_TIME>	vectSSTRATEGYPOINT_NOT_SUMMON_TIME;

struct SSTRATEGYPOINT_DAY
{// 2007-03-07 by dhjin, 전략포인트 생성 체크 요일.
	USHORT			Year;
	BYTE			Month;
	BYTE			Day;
	BYTE			MaxCount;
};

struct SSPPossibleTimeInfo
{// 2009-03-23 by dhjin, 전략포인트 시간 설정 수정 - 전략포인트 소환 가능한 시간값 전부 저장
	ATUM_DATE_TIME	StartTime;
	ATUM_DATE_TIME	EndTime;
	INT				PossibleMinRange;
	BOOL			CheckSummon;			// 2008-04-04 by dhjin, 소환 가능 시간 설정 - 0:금지시간 , 1:소환시간
};
typedef vector<SSPPossibleTimeInfo>		vectSSPPossibleTimeInfo;

///////////////////////////////////////////////////////////////////////////////
// 2006-07-25 by cmkwon, 개인상점 관련
#define SIZE_MAX_BAZAAR_ITEM_COUNT		16			// 2006-07-25 by cmkwon, 판매 혹은 구입 리스트 최대 개수
#define SIZE_MAX_BAZAAR_NAME			32			// 2006-07-25 by cmkwon, 
#define SIZE_MAX_BAZAAR_NAME			32			// 2006-07-25 by cmkwon, 
#define REQUERED_BAZAAR_DISTANCE		100.0f		// 2006-08-01 by cmkwon, 개인 상점과 거래하기 위한 거리

#define BAZAAR_TYPE_NONE				0		// 2006-07-25 by cmkwon
#define BAZAAR_TYPE_SELL				1		// 개인 판매 상점
#define BAZAAR_TYPE_BUY					2		// 개인 구매 상점

#define BAZAAR_STATE_NONE				0		// 2006-07-25 by cmkwon
#define BAZAAR_STATE_READY				1		// 2006-07-26 by cmkwon, 개인 상점 준비 상태 - 스킬 사용은 시작되었지만 개인 상점은 시작하지 않은 상태
#define BAZAAR_STATE_ACTIVE				2		// 2006-07-26 by cmkwon, 타유저가 개인 상점 판매/구입 가능 상태
#define BAZAAR_STATE_END				3		// 2006-07-26 by cmkwon, 품절

///////////////////////////////////////////////////////////////////////////////
// 2006-08-25 by cmkwon
struct SHAPPY_HOUR_EVENT
{
	INT				EventUniqueNumber;		// 
	INT				ServerGroupID;			// 2006-08-25 by cmkwon, 0(=AllServerGroup), 1(=10061), 2(10062), ...
	INT				DayOfWeek;				// 요일	- 일(0) 월(1) 화(2) 수(3) 목(4) 금(5) 토(6) 해당세력HappyHourEvent기간(7) PCBangHappyHourEvent기간내용(8)
	ATUM_DATE_TIME	atimeStartTime2;		//
	ATUM_DATE_TIME	atimeEndTime2;			//
	float			fEXPRate2;
	float			fSPIRate2;
	float			fEXPRepairRate2;
	float			fDropItemRate2;
	float			fDropRareItemRate2;
	float			fWarPointRate2;			// 2007-06-26 by dhjin, WarPoint 이벤트
	BYTE			InfluenceType3;			// 2007-10-30 by cmkwon, 세력별 해피아워 이벤트 구현 - SHAPPY_HOUR_EVENT 구조체에 필드 추가
	INT				MinLevel;				// 2008-03-13 by dhjin, Level별 해피아워 이벤트 구현 -
	INT				MaxLevel;				// 2008-03-13 by dhjin, Level별 해피아워 이벤트 구현 -
};

struct SHAPPY_HOUR_EVENT_PERIOD
{// 2007-10-30 by cmkwon, 세력별 해피아워 이벤트 구현 구조체 추가
	INT				EventUniqueNumber;		// 
	ATUM_DATE_TIME	atimeStartTime2;		//
	ATUM_DATE_TIME	atimeEndTime2;			//
	BYTE			InfluenceType3;			//

	void InitSHAPPY_HOUR_EVENT_PERIOD(BYTE i_byInflTy)
	{
		EventUniqueNumber = 0;
		atimeStartTime2.Reset();
		atimeEndTime2.Reset();
		InfluenceType3 = i_byInflTy;
	}
};

#define SERVERGROUP_START_ID			10061					// 2006-08-25 by cmkwon, global.cfg 파일의 atum2_db_1 DB에 사용하는 번호와 같도록 해야한다.
#define STR_ALL_SERVERGROUP_NAME		"All ServerGroup"		// 2006-08-25 by cmkwon



///////////////////////////////////////////////////////////////////////////////
// 2006-10-02 by cmkwon, WebLauncher 관련
#define SIZE_MAX_ARGV_COUNT					10					// 2006-10-02 by cmkwon, 실행 인자 최대 개수
// 2008-12-18 by cmkwon, 일본 Arario 런처 수정 - 아래와 같이 400 으로 수정
//#define SIZE_MAX_ARGV_PARAM_STRING_SIZE		50					// 2006-10-02 by cmkwon, 하나의 실행 인자 스트링 최대 길이
#define SIZE_MAX_ARGV_PARAM_STRING_SIZE		400		// 2008-12-18 by cmkwon, 일본 Arario 런처 수정 - SessionKey(301 Bytes) 보다 커야 한다. // 2006-10-02 by cmkwon, 하나의 실행 인자 스트링 최대 길이

#define EXCUTE_FILE_TYPE_SC_EXE				1
#define EXCUTE_FILE_TYPE_SC_LAUNCHER_ATM	2
#define EXCUTE_FILE_TYPE_SC_ATM				3
#define EXCUTE_FILE_TYPE_SC_WEBLAUNCHER		10


struct SEXCUTE_PARAMETER
{
	int			i_nExcuteFileType;
	char		o_szAccountName0[SIZE_MAX_ACCOUNT_NAME];
	char		o_szPreServerIP0[SIZE_MAX_IPADDRESS];
	int			o_nBirthYear;								// 2007-06-05 by cmkwon, 출생년도
	char		o_szPassword[SIZE_MAX_PASSWORD_MD5_STRING];				// 2008-12-18 by cmkwon, 일본 Arario 런처 수정 - SEXCUTE_PARAMETER 에 멤버 변수 추가
	char		o_szSessionKey[SIZE_MAX_WEBLOGIN_AUTHENTICATION_KEY];	// 2008-12-18 by cmkwon, 일본 Arario 런처 수정 - SEXCUTE_PARAMETER 에 멤버 변수 추가
};

extern int		g_nargvCount;
extern char		g_szArrargv[SIZE_MAX_ARGV_COUNT][SIZE_MAX_ARGV_PARAM_STRING_SIZE];

// 2008-04-25 by cmkwon, 지원 언어/서비스 추가시 꼭 추가 되어야 하는 사항 - [서비스-필수] C_Exe1, C_Exe2 실행시 실행 파라미터 처리 함수 선언 추가
Err_t GSetExcuteParameterList(int i_nParamCount, char** i_ppszParamString);
Err_t GCheckExcuteParameterList(SEXCUTE_PARAMETER* io_pExeParam);
Err_t GCheckExcuteParameterList_Kor(SEXCUTE_PARAMETER* io_pExeParam);
Err_t GCheckExcuteParameterList_Kor2(SEXCUTE_PARAMETER* io_pExeParam);
Err_t GCheckExcuteParameterList_Eng(SEXCUTE_PARAMETER* io_pExeParam);
Err_t GCheckExcuteParameterList_Eng_Server_2(SEXCUTE_PARAMETER* io_pExeParam);		// 2007-12-21 by cmkwon, Gameforge(Europe) 프로젝트 추가 - GCheckExcuteParameterList_Eng_Server_2() 추가
Err_t GCheckExcuteParameterList_Viet(SEXCUTE_PARAMETER* io_pExeParam);
Err_t GCheckExcuteParameterList_Chn(SEXCUTE_PARAMETER* io_pExeParam);
Err_t GCheckExcuteParameterList_Tha(SEXCUTE_PARAMETER* io_pExeParam);		// 2008-05-02 by cmkwon, WinnerOnline_Tha 추가하기 - 
Err_t GCheckExcuteParameterList_Rus(SEXCUTE_PARAMETER* io_pExeParam);		// 2008-05-29 by cmkwon, 지원 서비스 추가(Innova_Rus 러시아어 추가) - 
Err_t GCheckExcuteParameterList_Tpe(SEXCUTE_PARAMETER* io_pExeParam);		// 2008-09-23 by cmkwon, 지원 서비스 추가(대만 Netpower_Tpe) - 
Err_t GCheckExcuteParameterList_Jpn(SEXCUTE_PARAMETER* io_pExeParam);		// 2008-12-03 by cmkwon, 지원 서비스 추가(일본 Arario_Jpn) - 

///////////////////////////////////////////////////////////////////////////////
// 2007-05-09 by cmkwon
struct SREG_DATA_EXE_2
{
	VersionInfo		ClientVersion;
	VersionInfo		DVersion;		// DeleteFileListVersion
	VersionInfo		NVersion;		// NoticeFileVersion
// 2007-12-27 by cmkwon, 윈도우즈 모드 기능 추가 - 해상도 저장 시스템 수정
//	int				WindowDegree;	// 해상도 선택 인덱스
	char			WindowDegree[SIZE_MAX_WINDOW_DEGREE_NAME];		// 2007-12-27 by cmkwon, 윈도우즈 모드 기능 추가 - 추가
	char			BeforeAccountName[SIZE_MAX_ACCOUNT_NAME];
	char			SelectedServerGroupName[SIZE_MAX_SERVER_NAME];
	int				IsWindowMode;	// 2008-01-03 by cmkwon, 윈도우모드 상태 저장하기 - SREG_DATA_EXE_2 에 필드 추가

	
};
Err_t GLoadExe1VersionInfo(VersionInfo* o_pLauncherVerInfo, char* i_szVersionInfoFileName);
Err_t GLoadExe2VersionInfo(SREG_DATA_EXE_2* o_pRegDataEXE2, char* i_szVersionInfoFileName);
Err_t GSaveExe1VersionInfo(VersionInfo* i_pLauncherVerInfo, char* i_szVersionInfoFileName);
Err_t GSaveExe2VersionInfo(SREG_DATA_EXE_2* i_pRegDataEXE2, char* i_szVersionInfoFileName);

struct PCBANG_INFO
{// 2007-01-22 by dhjin, PC방 DB정보 구조체
	UID32_t		PCBangUID;
	char		ST_IP[SIZE_MAX_IPADDRESS];
	char		ED_IP[4];
	char		User_Id[SIZE_MAX_ACCOUNT_NAME];
	char		Branch_Name[50];
	char		Branch_RegNO[12];
	char		Branch_Tel[14];
	char		ZipCode[15];
	char		Addr_Sido[10];
	char		Addr_SiGuGun[20];
	char		Addr_Dong[100];
	char		Addr_Detail[50];
	BYTE		User_Level;				// 2007-06-25 by dhjin, PC방 등급 추가



	
};
typedef vector<PCBANG_INFO>		vectorPCBANG_INFO;


//////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// 2007-04-17 by dhjin, 아레나에 관련된 상태.
#define	ARENA_STATE_NONE				0	// 아레나에 관련된 일을 하고 있지 않다.
#define	ARENA_STATE_JOINING				1	// 아레나팀에 참가한 상태, 아직 팀원이 꽉 차지 않았다.
#define	ARENA_STATE_READY				2	// 아레나팀원이 꽉 차서 팀원들의 준비 완료를 기다리는 상태.
#define	ARENA_STATE_READY_FINISH		3	// 아레나팀원이 꽉 차서 팀원이 준비 완료를 누른상태 (FieldIOCPSocket에서만 사용)
#define	ARENA_STATE_FIGHTING_WARREADY	101	// 아레나방에 입장하여 1분간 대기하는 상태.
#define	ARENA_STATE_FIGHTING_WARING		102	// 아레나방에서 전쟁중인 상태.
#define	ARENA_STATE_FIGHTING_WARFINISH	103	// 아레나방에서 전쟁이 끝나고 보상을 받는 상태, 마을로 워프하기 전까지의 상태.

const char* GET_ARENA_STATE_STRING(BYTE i_byAState);

#define	SIZE_MAX_TEAM_PW			5

// 2007-04-17 by dhjin, 아레나 모드.
#define	ARENAMODE_DEATHMATCH		1
#define	ARENAMODE_ROUND				2

// 2007-04-17 by dhjin, 케릭터 레벨 랭크 이름.
#define	SIZE_MAX_LEVELRANK			40

// 2007-04-17 by dhjin, 서버에서 지원할 수 있는 팀 최대 수 
#define SIZE_MAX_TEAM				500

// 2007-04-19 by dhjin, 서버에서 지원하는 아레나 수
#define SIZE_MAX_ARENA_ROOM			80

// 2007-04-17 by dhjin, 입장가능한 레벨별 방
#define	ARENA_STAGE_D_START_LEVEL			11	// 입장가능한 D방 시작레벨 11~
#define ARENA_STAGE_D_END_LEVEL				31	// 입장가능한 D방 마지막레벨 31
#define ARENA_STAGE_C_START_LEVEL			32	// 입장가능한 C방 시작레벨 32~
#define ARENA_STAGE_C_END_LEVEL				51	// 입장가능한 C방 마지막레벨 51
#define ARENA_STAGE_B_START_LEVEL			52	// 입장가능한 B방 시작레벨 52~
#define ARENA_STAGE_B_END_LEVEL				71	// 입장가능한 B방 마지막레벨 71
#define ARENA_STAGE_A_START_LEVEL			72	// 입장가능한 A방 시작레벨 72~
// 2010-03-03 by cmkwon, 최대레벨상향 관련 아레나 입장시 레벨 버그 - 110으로 수정, 캐릭터 최대레벨 상향시마다 수정 필요
//#define ARENA_STAGE_A_END_LEVEL				100	// 입장가능한 A방 마지막레벨 100
#define ARENA_STAGE_A_END_LEVEL				110	// 입장가능한 A방 마지막레벨 100

// 2007-04-18 by dhjin, 에러값
#define STATE_ERROR							-1

// 2007-04-20 by dhjin, 아레나 승패 여부 
#define ARENA_ISSUE_WIN						1
#define ARENA_ISSUE_LOSE					2
#define ARENA_ISSUE_DRAW					3

// 2007-05-16 by dhjin, 아레나 승패 여부 조건
#define ARENA_END_TYPE_POINT				1	// 2007-05-16 by dhjin, 포인트가 0이 되어 게임이 종료
#define ARENA_END_TYPE_TIME					2	// 2007-05-16 by dhjin, 경기 제한 시간 초과로 게임이 종료
#define ARENA_END_TYPE_GIVEUP				3	// 2007-05-16 by dhjin, 어느 한팀이 전부 아레나 맵에서 나가 게임이 종료

// 2007-04-20 by dhjin, 아레나 틱 간격. 1초
#define ARENA_TICK_INTERVAL			1000

// 2011-06-22 by hskim, 사설 서버 방지
#define SECURITY_TICK_INTERVAL		1000

// 2011-07-21 by hskim, 인증 서버 구현 - 접속후 Timeout 처리
#define SPTOMP_TICK_INTERVAL		1000

// 2007-04-27 by dhjin, 요청한 팀 목록을 한 번에 전해주는 양
#define ARENA_MAX_REQUEST_TEAM				20

// 2007-05-09 by dhjin, 아레나 준비 버튼 딜레이 단위 : 초
#define ARENA_READYBUTTON_INTERVAL			3

// 2007-06-05 by dhjin, 아레나 대기 팀 정보 요청 정의
#define ARENA_REQUEST_TEAM_STATE_OUR		1	// 2007-06-05 by dhjin, 모두 보기
#define ARENA_REQUEST_TEAM_STATE_JOINING	2	// 2007-06-05 by dhjin, 대기 팀
#define ARENA_REQUEST_TEAM_STATE_OTHER		3	// 2007-06-05 by dhjin, 상대 팀

///////////////////////////////////////////////////////////////////////////////
// 2007-04-17 by dhjin, Arena 시스템에 필요한 구조체 정의
struct SDBARENA_INFO
{// 2007-04-17 by dhjin, ti_ArenaInfo 값
	BYTE	ArenaMode;				// 아레나 모드 1 : DeathMatch, 2 : Round
	BYTE	ReqMemberNum;			// 팀 인원 제한
	INT		PayInfluencePointWIN;	// 승리 세력에게 보상되는 세력포인트값
	INT		PayInfluencePointLOSE;	// 패배 세력에게 보상되는 세력포인트값
	INT		PayWarPointWIN;			// 승리 팀에게 보상되는 WP값
	INT		PayWarPointLOSE;		// 패배 팀에게 보상되는 WP값
};
typedef vector<SDBARENA_INFO>	vectorSDBARENA_INFO;

struct SDBARENA_MAPINFO
{// 2007-04-17 by dhjin, ti_ArenaMapInfo 값 
	MapIndex_t 	ArenaMapIndex;			// 맵 인덱스
	BYTE 	ArenaMode;					// 아레나 모드 1 : DeathMatch, 2 : Round
	BYTE 	ReqMemberNum; 				// 팀 인원 제한
	BYTE 	PlayLimitedTime;			// 경기 제한 시간
	BYTE 	WINCondition;				// 경기 승리 조건
	INT		LvDSupplyItemNum1;				// 아레나 전용 지급 아이템1
	INT		LvDSupplyItemCount1;			// 아레나 전용 지급 아이템1 수 
	INT		LvDSupplyItemNum2;				// 아레나 전용 지급 아이템2
	INT		LvDSupplyItemCount2;			// 아레나 전용 지급 아이템2 수
	INT		LvDSupplyItemNum3;				// 아레나 전용 지급 아이템3
	INT		LvDSupplyItemCount3;			// 아레나 전용 지급 아이템3 수
};
typedef vector<SDBARENA_MAPINFO>	vectorSDBARENA_MAPINFO;

struct SARENA_INFO
{// 2007-04-17 by dhjin, 유저가 가지고 있는 정보.
	BYTE	ArenaMode;				// Arena 모드 정보
	BYTE	State;					// Arena 상태 정보
	BYTE	ShootingDown;			// Arena 방에서 격추시킨 정보
	BYTE	SufferingAttack;		// Arena 방에서 피격당한 정보
	BYTE	LostPoint;				// Arena 방에서 피격 당하지 않고 죽은 카운트
	SHORT	SaveSP;					// Arena 방 입장 전 SP
	SHORT	SaveEP;					// Arena 방 입장 전 EP
	INT		TeamNum;				// Arena 팀 번호
	INT		DeathMatchRoomNum;		// Arena 데스매치 방 번호
	BodyCond_t	SaveBodyCondition;	// Arena 방 입장 전 BodyCondition
	float	SaveHP;					// Arena 방 입장 전 HP
	float	SaveDP;					// Arena 방 입장 전 DP
	ATUM_DATE_TIME	ReadyButtonClickTime;	// Arena 준비 완료 버튼 누른 시간 저장, 3초 딜레이 필요
	BOOL	WatchState;				// Arena 관전 상태 0 : 관전 상태가 아니다. 1 : 관전 상태				
	BOOL	Command;				// 2008-02-21 by dhjin, 아레나 통합 - '/아레나이동' 명령어 사용으로 아레나 서버로 온것인지 체크 비트

	///////////////////////////////////////////////////////////////////////////////
	/// \fn			void ResetArenaInfo(void)
	/// \brief		
	/// \author		cmkwon
	/// \date		2007-05-14 ~ 2007-05-14
	/// \warning	
	///
	/// \param		
	/// \return		
	///////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////
	/// \fn			BOOL IsValidArenaState(void)
	/// \brief		
	/// \author		cmkwon
	/// \date		2007-05-14 ~ 2007-05-14
	/// \warning	
	///
	/// \param		
	/// \return		
	///////////////////////////////////////////////////////////////////////////////
	BOOL IsValidArenaState(void)
	{
		if (ARENA_STATE_NONE == State)
		{
			return FALSE;
		}

		if (0 > TeamNum
			&& 0 > DeathMatchRoomNum)
		{
			return FALSE;
		}

		return TRUE;
	}
};

struct SARENA_PAY_INFO
{// 2007-04-17 by dhjin, 아레나 보상 정보
	INT		PayInfluencePointWIN;	// 승리 세력에게 보상되는 세력포인트값
	INT		PayInfluencePointLOSE;	// 패배 세력에게 보상되는 세력포인트값
	INT		PayWarPointWIN;			// 승리 팀에게 보상되는 WP값
	INT		PayWarPointLOSE;		// 패배 팀에게 보상되는 WP값
};

struct SARENA_MAP_MANAGER
{// 2007-05-02 by dhjin, 아레나 맵 정보
	MapIndex_t		ArenaMap;			// 2007-04-30 by dhjin, 아레나 맵
	ChannelIndex_t	ArenaMapChannel;	// 2007-04-30 by dhjin, 아레나 채널
	BOOL			bArenaChannelSet;	// 2007-04-30 by dhjin, 아레나 채널 할당 여부 0 : 할당되지 않음, 1 : 할당됨
};
typedef mt_vector<SARENA_MAP_MANAGER>				mtvectSARENA_MAP_MANAGER;

typedef mt_vector<ClientIndex_t>					mtvectorClientIndex_t;

struct SARENA_OTHER_TEAM_INFO
{// 2007-05-28 by dhjin, 상대팀 정보 저장 후 클라이언트에게 전송
	BYTE ArenaMode;								// 아레나 모드 1 : DeathMatch, 2 : Round
	BYTE TeamSize;								// 팀 최대 인원수
};
typedef vector<SARENA_OTHER_TEAM_INFO>				vectSARENA_OTHER_TEAM_INFO;

struct SARENA_GM_COMMAND_INFO_TEAM
{// 2007-05-28 by dhjin, /아레나 GM명령어 정보 전송
	BYTE 	ArenaMode;							// 아레나 모드 1 : DeathMatch, 2 : Round
	BYTE 	TeamState;							// 상태 정보
	BYTE	Level;								// 팀 레벨
	BYTE	MemberCount;						// 팀 최대 인원수
	INT		CurrenMemberCount;					// 현재 팀 인원수
};
typedef vector<SARENA_GM_COMMAND_INFO_TEAM>				vectSARENA_GM_COMMAND_INFO_TEAM;


///////////////////////////////////////////////////////////////////////////////
// 2007-05-11 by cmkwon, 미스테리캡슐 시스템
struct MYSTERY_ITEM_DROP
{
	INT				MysteryItemDropNum;
	USHORT			ReqUnitKind;					// 필요유닛종류
	BYTE			ReqMinLevel;					// 필요 최저 레벨
	BYTE			ReqMaxLevel;					// 필요 최저 레벨
	INT				DropItemNum;
	INT				MinCount;
	INT				MaxCount;
	Prob1000K_t		Probability;			// 지급 확률(상대값으로 처리됨): 0 ~ 1000000
	Prob100K_t		PrefixProbability;		// 접두사가 붙을 확률, 0 ~ 100000
	Prob100K_t		SuffixProbability;		// 접미사가 붙을 확률, 0 ~ 100000
	USHORT			Period;					// 럭키머신 기간, 2008-11-04 by dhjin, 럭키머신
	INT				CountPerPeriod;			// 기간동안 드랍될 최대 아이템 수, 2008-11-04 by dhjin, 럭키머신
	INT				DropCount;				// 기간동안 현재 드랍된 아이템 수, 2008-11-04 by dhjin, 럭키머신
	ATUM_DATE_TIME	Starttime;				// 럭키머신 시작 시간, 2008-11-04 by dhjin, 럭키머신
};
typedef multimap<INT, MYSTERY_ITEM_DROP>		mmapINT2MYSTERY_ITEM_DROP;		// 2007-05-14 by cmkwon
typedef mt_multimap<INT, MYSTERY_ITEM_DROP>		mtmapINT2MYSTERY_ITEM_DROP;		// 2008-11-10 by dhjin, 럭키머신 multimap -> mt_multimap으로 변경
typedef vector<MYSTERY_ITEM_DROP*>				vectMYSTERY_ITEM_DROPPtr;			// 2007-05-14 by cmkwon

// 2008-11-04 by dhjin, 럭키머신
struct LUCKYITEM_DROP_INFO
{
	BOOL			LuckItemUsing;
	USHORT			Period;
	UID64_t			MysteryItemDropNumUID;
	INT				MysteryItemDropNum;
	INT				DropItemNum;
	INT				MinCount;
	INT				MaxCount;
	Prob100K_t		PrefixProbability;		// 접두사가 붙을 확률, 0 ~ 100000
	Prob100K_t		SuffixProbability;		// 접미사가 붙을 확률, 0 ~ 100000
};

///////////////////////////////////////////////////////////////////////////////
// 2007-05-28 by cmkwon
struct SRESOBJ_CHECKSUM
{
	char		szResObjFileName[SIZE_MAX_RESOBJ_FILE_NAME];
	int			nFileSize;
	// 2009-05-29 by cmkwon, Hash알고리즘 추가(SHA256) - 
	//UINT		uiObjCheckSum;	
	BYTE		byDigest[32];		// 2009-05-29 by cmkwon, Hash알고리즘 추가(SHA256) - 

	// 2009-05-29 by cmkwon, Hash알고리즘 추가(SHA256) - 
	BOOL IsSame(int i_nLen, BYTE i_byCheckSum[32])
	{
		if (i_nLen != nFileSize)
		{
			return FALSE;
		}

		for (int i = 0; i < 4; i++)
		{
			if (((INT64*)i_byCheckSum)[i] != ((INT64*)byDigest)[i])
			{
				return FALSE;
			}
		}

		return TRUE;
	}
};
typedef map<std::string, SRESOBJ_CHECKSUM>			mapstring2SRESOBJ_CHECKSUM;		// 2007-05-28 by cmkwon

//////////////////////////////////////////////////////////////////////////
// 2007-07-06 by dhjin, Tutorial
struct STUTORIAL_INFO
{// 2007-07-06 by dhjin, Tutorial 정보
	INT			TutorialUID;					// Tutorial 번호 
	INT			TutorialPayItem1;				// Tutorial 아이템 번호 
	INT			TutorialPayItemCount1;			// Tutorial 아이템 수
	INT			TutorialPayItem2;
	INT			TutorialPayItemCount2;
	INT			TutorialPayItem3;
	INT			TutorialPayItemCount3;
};
typedef vector<STUTORIAL_INFO>	vectSTutorialInfo;			// 2007-07-06 by dhjin
typedef vector<INT>				vectTutorial;				// 2007-07-06 by dhjin
// 2010-01-18 by cmkwon, 아이템 사용시 Parameter 중복 체크 시스템 구현 - 위쪽으로 이동
//typedef vector<INT>				vectINT;					// 2008-01-31 by cmkwon, 시간제한 아이템 DB 에 추가 중 체크 - 

// 2008-01-31 by cmkwon, 시간제한 아이템 DB 에 추가 중 체크 - find_if() 함수자
struct Sfind_if_INT
{
	Sfind_if_INT(int i_nValue) : m_nFindValue(i_nValue) {};
	bool operator()(INT i_nValue)
	{
		return i_nValue == m_nFindValue;
	}
	int m_nFindValue;
};


// 2007-07-09 by dhjin, 기본 무기
#define FIRST_WEAPON_AGEAR					7000050
#define SECOND_WEAPON_AGEAR					7900440
#define FIRST_WEAPON_BGEAR					7001950
#define SECOND_WEAPON_BGEAR					7900000
#define FIRST_WEAPON_MGEAR					7001950
#define SECOND_WEAPON_MGEAR					7900000
#define FIRST_WEAPON_IGEAR					7001950
#define SECOND_WEAPON_IGEAR					7900000

// 2007-07-11 by dhjin, 몬스터 소환 시간 단위 MS
#define TICK_CREATE_MONSTER_TERM			1000

//////////////////////////////////////////////////////////////////////////
// 2007-08-03 by dhjin, PC방 IP리스트 수정과 관련된 구조체
struct SIPClassD
{
	UID32_t		PCBangUID;			// 2007-08-03 by dhjin, PC방 UID 
	BYTE		IPClassDStart;		// 2007-08-03 by dhjin, 시작 IP Class D
	BYTE		IPClassDEnd;		// 2007-08-03 by dhjin, 끝 IP Class D
};
typedef vector<SIPClassD>					vectorSIPClassD;
typedef mt_map<DWORD, vectorSIPClassD>		mtmapDWORDvectorSIPClassD;

//////////////////////////////////////////////////////////////////////////
// 2007-08-13 by dhjin, OutPost 관련
#define	OUTPOST_NORMAL		0x00
#define	OUTPOST_WARSTART	0x10
#define	OUTPOST_WARING		0x20
#define	OUTPOST_WAREND		0x30
#define	OUTPOST_RESETSTART	0x01
#define	OUTPOST_RESETING	0x02
#define	OUTPOST_RESETEND	0x03
#define IS_OUTPOST(x)		( (x & 0xFF) > 0 )
#define IS_OUTPOST_WAR(x)	( (x & 0xF0) > 0 )
#define IS_OUTPOST_RESET(x)	( (x & 0x0F) > 0 )
#define IS_OUTPOST_RESETING(x) ( (x &  OUTPOST_RESETING) == OUTPOST_RESETING)

//////////////////////////////////////////////////////////////////////////
// 2007-08-13 by dhjin, 공지사항 지도자, 전진기지 여단장인지 구분 상수
#define	NOTICE_LEADER			1
#define	NOTICE_GUILDCOMMANDER	2

// 2007-08-13 by dhjin, 공지사항 문자열 크기
#define	SIZE_MAX_NOTICE			512

// 2007-11-06 by dhjin, 전진기지 승리시 받을 아이템 
#define	OUTPOST_PAY_ITEM		7010720	// 보급상자 아이템
#define	OUTPOST_PAY_ITEM_COUNT	1		// 보급상자 아이템 수

//////////////////////////////////////////////////////////////////////////
// 2007-08-16 by dhjin, 전진기지 관련 정보
struct	SOUTPOST_INFO
{
	BYTE			OutPostInfluence;						// 전진기지 소유 세력
	BYTE			OutPostNextWarTimeSet;					// 전진기지 다음 전쟁 시간 설정
	INT				OutPostMapIndex;						// 전진기지 맵 번호
	INT				OutPostCityMapIndex;					// 전진기지 도시 맵 번호
	UID32_t			OutPostGuildUID;						// 전진기지 소유 여단
	CHAR			OutPostGuildName[SIZE_MAX_GUILD_NAME];	// 전진기지 소유 여단명
	ATUM_DATE_TIME	OutPostGetTime;							// 전진기지 소유 시작 시간
	ATUM_DATE_TIME	OutPostNextWarTime;						// 전진기지 다음 전쟁 시간
};
typedef vector<SOUTPOST_INFO>			vectSOutPostInfo;

// 2009-07-08 by cmkwon, 전쟁 관련 정의 위치 이동(LocalizationDefineCommon.h) - 
//// 2007-08-16 by dhjin, 전진기지 관련 define
//#define	OUTPOST_WARTIME					120	// 전진기지전 시간, 120분
//#define OUTPOST_WARTIME_FOR_TESTSERVER	60	// 2008-10-29 by cmkwon, 테섭은 전진기지전 1시간(60분)으로 설정 - 

// 2009-05-12 by cmkwon, (일본요청) 일본만 전진 기지전 주기 7일로 수정 - LocalizationDefineCommon.h 로 위치 이동
//#define	OUTPOST_NEXTWARGAP				5	// 2008-10-22 by dhjin, 전진기지 3차 10 -> 5일로 수정 // 다음 전진기지전까지의 일 수, 10일 

#define	OUTPOST_RESET					5	// 전진기지 각인 시키는 시간, 1분
#define	OUTPOST_PAY_WARPOINT			300	// 전진기지전 승리 세력 지급 WarPoint
#define	OUTPOST_PAY_WARPOINT_BY_LOSE	100	// 2008-01-07 by dhjin, 세력 보상 수정 - 전진기지전 패배 세력 지급 WarPoint

//////////////////////////////////////////////////////////////////////////
// 2007-08-16 by dhjin, 도시 지도자, 여단장 관련 정보
struct	SCITYLEADER_INFO
{
	INT			MapIndex;					// 관리되는 도시 맵 번호 ex)1001 : 지도자 관련 맵
	BYTE		Influence;					// 세력
	UID32_t		CharacterUID;				// 유저 UID
	INT			ExpediencyFundCumulative;	// 누적 판공 비
	INT			ExpediencyFund;				// 가용 판공 비
	INT			ExpediencyFundRate;			// 판공비율, %단위, 1000단위로 계산 10 => 1%
	CHAR		Notice[SIZE_MAX_NOTICE];	// 공지사항
};
typedef vector<SCITYLEADER_INFO>		vectSCityLeaderInfo;

// 2007-08-16 by dhjin, 판공비 관련 define, 판공비율, %단위, 1000단위로 계산 10 => 1%
#define	EXPEDIENCYFUND_LEADER				10		// 세력 지도자 판공비율
#define	EXPEDIENCYFUND_GUILDCOMMANDER		10		// 전진기지 소유 여단 판공비율
#define	EXPEDIENCYFUND_LEADER_OUTPOST		5		// 전진기지 소유 세력 지도자 추가 판공비율
#define	EXPEDIENCYFUND_LEADER_INFLUENCEWAR	2		// 모선전 공격 성공 시 추가 상승 비율
#define EXPEDIENCYFUND_RATE_VALUE			1000	// 판공비율, %단위, 1000단위로 계산 10 => 1%

// 2007-08-16 by dhjin, 공지사항 관련 define
#define	NOTICE_LEADER						1	// 공지사항 지도자
#define	NOTICE_GUILDCOMMANDER				2	// 공지사항 전진기지 여단장
#define	SIZE_MAX_NOTICE						512	// 공지사항 문자열 크기

// 2007-08-30 by dhjin, 모선전시 전략포인트 생성 시간 
#define STRATEGYPOINT_SUMMONTIME_BY_INFLUENCEBOSS	120 // 모선전시 전략포인트 생성 시간 120분

// 2007-09-03 by dhjin, 전략포인트 생성 시간 다시 설정 시 가져야되는 Gap
#define STRATEGYPOINT_SUMMON_GAP_BY_INFLUENCEWAR	4	// 세력전쟁 시 가져야되는 GAP
#define STRATEGYPOINT_SUMMON_GAP_BY_OUTPOST			8	// 전진기지 전쟁 시 가져야되는 GAP

// 2007-09-04 by dhjin, 모선전시 텔레포트 관련
#define TELEPORT_BUILDING_TIME_SECOND				180   // 모선전시 텔레포트가 만들어지는 시간(180초)

// 2007-09-05 by dhjin, 텔레포트 상태값
#define TELEPORT_STATE_NOT_SUMMON					0	// 텔레포트 소환 상태가 아닌 값
#define TELEPORT_STATE_NONE							1	// 텔레포트 평상시 상태값
#define TELEPORT_STATE_READY						2   // 전략포인트가 파괴되어 텔레포트 설치가 가능한 상태
#define TELEPORT_STATE_BUILDING						3   // 텔레포트 빌딩 중
#define TELEPORT_STATE_COMPLETE						4	// 텔레포트 설치되어 있는 상태

// 2007-09-05 by dhjin, Monster ClickEvent 필드 값
#define MONSTER_CLICKEVENT_OUTPOST_RESET			1	// 전진기지 중앙처리장치 클릭 이벤트 (리셋)
#define MONSTER_CLICKEVENT_TELEPORT_BUILDING		2	// 텔레포트 클릭 이벤트 (빌딩)

struct STELEPORT_INFO_BUILDING
{// 2007-09-07 by dhjin, 현재 생성되어 있는 텔레포트 정보
	BOOL			bBuilded;		// 텔레포트가 완성되었으면 TRUE, 빌딩중이라면 FALSE
	INT				MapInfluence;	// 세력 
	MapIndex_t		MapIndex;
	ATUM_DATE_TIME	BuildStartTime;
};

// 2007-10-06 by cmkwon, 부지도자 2명의 호칭을 다르게 설정 -
char* GetLeader8SubLeaderString(BYTE i_byInflTy, USHORT i_usRace);

// 2007-10-10 by dhjin, 맴버쉽 유저 워프비용 절감 %
#define	MEMBERSHIP_DISCOUNT_WARPFEE		50		// 2007-10-10 by dhjin, 50%

// 2007-10-16 by cmkwon, 로그 추가 - OutPost.h 파일에 있던것을 여기로 이동함
struct SOutPostProtectorDamage
{
	BYTE	Influence;
	UID32_t	GuildUID;
	CHAR 	GuildName[SIZE_MAX_GUILD_NAME];
	float	Damage;
};
typedef	mt_vector<SOutPostProtectorDamage>		mtvectSOutPostProtectorDamage;

// 2007-10-24 by cmkwon, 서버 정보 암호화 - 추가함
extern GAME_SERVER_INFO_FOR_ADMIN g_arrGameServers[];
extern void GDecryptGameServerInfoByXOR(void);

// 2007-10-30 by cmkwon, 세력별 해피아워 이벤트 구현 -
extern char* GetDayOfWeekString(int i_nDayOfWeek);

// 2007-10-30 by cmkwon, 세력별 해피아워 이벤트 구현 -
extern int GetArrayIndexByInfluenceType(BYTE i_byInflTy);
extern BYTE GetInfluenceTypeByArrayIndex(int i_nArrIdx);


//////////////////////////////////////////////////////////////////////////
// 2007-10-26 by dhjin, Poll 관련

struct SACTION_BY_LEVEL_DB
{// 2007-10-26 by dhjin, 레벨에 따른 여러 행동들
	BYTE		Level;
	INT			PollPoint;		// 레벨에 따른 투표 점수
};
typedef vector<SACTION_BY_LEVEL_DB>		vectSACTION_BY_LEVEL_DB;

struct SPOLLDATE_DB
{// 2007-10-26 by dhjin, 선거 일정
	ATUM_DATE_TIME	ApplicationStartDate;		// 후보 신청 시작 날
	ATUM_DATE_TIME	ApplicationEndDate;			// 후보 시청 끝나는 날
	ATUM_DATE_TIME	VoteStartDate;				// 투표 시작 날
	ATUM_DATE_TIME	VoteEndDate;				// 투표 마지막 날
	ATUM_DATE_TIME	Election;					// 선출일
};

struct SVOTER_LIST
{// 2007-10-26 by dhjin, 투표자 리스트 
	UID32_t		AccountUID;						//	투표자 계정 UID
	UID32_t		CharacterUID;					//	투표자 UID
	INT			LeaderCandidateNum;				//	투표자가 투표한 후보자 번호
};
typedef mt_vector<SVOTER_LIST>			mtvectSVOTER_LIST;

#define SIZE_MAX_CAMPAIGNPROMISES				512

struct SLEADER_CANDIDATE
{// 2007-10-26 by dhjin, 지도자 후보들
	BYTE			Influence;									//  지도자 후보의 세력
	BOOL			DeleteCandidate;							//  이번 선거 기간에 후보 탈퇴 했는지 여부, TRUE = 탈퇴
	INT				LeaderCandidateNum;							//	지도자 후보 번호
	INT				PollCount;									//  지도자 후보 득표수
	UID32_t			AccountUID;									//	지도자 후보 계정 UID
	UID32_t			CharacterUID;								//	지도자 후보 UID
	UID32_t			GuildUID;									//  지도자 후보 길드 UID
	CHAR			CharacterName[SIZE_MAX_CHARACTER_NAME];		//  지도자 후보 이름
	CHAR			GuildName[SIZE_MAX_GUILD_NAME];				//  지도자 후보 길드명
	CHAR			CampaignPromises[SIZE_MAX_CAMPAIGNPROMISES];//  지도자 후보 공약	
};
typedef mt_vector<SLEADER_CANDIDATE>		mtvectSLEADER_CANDIDATE;

#define LEADERCANDIDATE_REQUIRE_LEVEL			60
#define LEADERCANDIDATE_REQUIRE_PROPENSITY		1000
#define LEADERCANDIDATE_REQUIRE_GUILDMEMBERNUM  1		// 2007-11-28 by dhjin, 여단원 인원 체크 없음 - 기획 요청
#define LEADERCANDIDATE_REQUIRE_GUILDFAME		1000
#define LEADERVOTE_REQUIRE_LEVEL				11

///////////////////////////////////////////////////////////////////////////////
// 2007-11-28 by cmkwon, 통지시스템 구현 -
#define SIZE_MAX_NOTIFY_MSG_STRING				512		// 2007-11-28 by cmkwon, 스트링 최대 길이
#define NOTIFY_MSG_TYPE_TEXT					1		// 통지메시지타입 - 일단 스트링
#define NOTIFY_MSG_TYPE_RECV_GIFT				2		// 통지메시지타입 - 아이템 선물 받은 메시지
struct SNOTIFY_MSG		// 2007-11-28 by cmkwon, 통지시스템 구현 -
{
	UID64_t			NotifyMsgUID;				// 
	UID32_t			CharacterUID;				// 통지메시지 받을 캐릭터 UID, 0 이면 모든 캐릭터에게 전송(0 인것은 유저가 지울 수 없다)
	BYTE			NotifyMsgType;				// NOTIFY_MSG_TYPE_XXX
	char			NotifyMsgString[SIZE_MAX_NOTIFY_MSG_STRING];	// 통지메시지 스트링
	UID32_t			SenderCharacterUID;								// 통지메시지 전송한 CharacterUID
	char			SenderCharacterName[SIZE_MAX_CHARACTER_NAME];	// 통지메시지 전송한 CharacterName
	ATUM_DATE_TIME	CreateTime;										// 통지메시지 DB에 생성된 시간
};
typedef mt_vector<SNOTIFY_MSG>		mtvectSNOTIFY_MSG;


//////////////////////////////////////////////////////////////////////////
// 2007-12-26 by dhjin, 아레나 통합 - 아레나 서버 정보
struct SARENA_SERVER_INFO
{
	BOOL			ArenaFieldServerCheck;		// 아레나 필드 서버인지 체크, TRUE=>아레나필드서버	
	char			ArenaServerName[SIZE_MAX_SERVER_NAME];
	INT				ArenaServerID;
	char			ArenaFieldServerIP[SIZE_MAX_IPADDRESS];
	int				ArenaFieldServerPort;
	char			ArenaIMServerIP[SIZE_MAX_IPADDRESS];
	int				ArenaIMServerPort;
};

struct SAFS_NEED_MFSINFO
{// 2008-01-03 by dhjin, 아레나 통합 - MFS와 AFS 케릭터 정보 매칭 저장
	ClientIndex_t	MFSClientIdx;
	UID32_t			MFSCharacterUID;
	INT				MFSServerID;
};

#define	JAMBOREE_SERVER_ID			10080			// 2008-03-05 by dhjin, 아레나 통합 - 대회 서버 ID

//////////////////////////////////////////////////////////////////////////
// 2008-03-24 by dhjin, 모선전 정보 표시 기획안 - 
#define MS_WAR_HP_RATE					10				// 2008-03-26 by dhjin, 모선전 정보 표시 기획안 - 모선전 HP 보여주는 비율
#define MS_WAR_MIN_HP_RATE				0				// 2008-03-26 by dhjin, 모선전 정보 표시 기획안 - 모선전 HP 보여주는 최저HP 비율

INT CalcGradeByRate(float i_nMaxValue, float i_nValue, INT i_nRate); // 2008-03-24 by dhjin, 모선전 정보 표시 기획안 - 비율에 따른 등급을 계산한다.

// 2008-03-24 by dhjin, 모선전 정보 표시 기획안 - 비트 플래그 설정
#define MS_WAR_OPTION_TYPE_UNKNOWN					(USHORT)0x0000	// 알수 없음
#define MS_WAR_OPTION_TYPE_NONE						(USHORT)0x0001	// 1 - 모선전 정보 표시 설정 안됨
#define MS_WAR_OPTION_TYPE_ATT_ACTIVATED			(USHORT)0x0002	// 2 - (공) 활성화 완료 표시
#define MS_WAR_OPTION_TYPE_ATT_ACTIVE				(USHORT)0x0004	// 4 - (공) 활성화 진행 중 표시
#define MS_WAR_OPTION_TYPE_ATT_ACTIVE_TIME			(USHORT)0x0008	// 8 - (공) 활성화 진행 시간 표시
#define MS_WAR_OPTION_TYPE_ATT_TELEPORT_HP			(USHORT)0x0010	// 16 - (공) 텔레포트 HP 표시
#define MS_WAR_OPTION_TYPE_ATT_STRATEGYPOINT_LIVE	(USHORT)0x0020	// 32 - (공) 전략포인트 생존여부 표시
#define MS_WAR_OPTION_TYPE_DEF_STRATEGYPOINT_HP		(USHORT)0x0040	// 64 - (수) 전략포인트 HP 표시
#define MS_WAR_OPTION_TYPE_DEF_STRATEGYPOINT_LIVE	(USHORT)0x0080	// 128 - (수) 전략포인트 생존여부 표시
#define MS_WAR_OPTION_TYPE_LEADER					(USHORT)0x0100	// 256 - 지도부 적용

#define IS_MS_WAR_OPTION_TYPE(_CurrentOption, _CompareOption)   ((_CurrentOption & _CompareOption) != 0)

struct MSWARINFO_DISPLAY
{// 2008-03-26 by dhjin, 모선전 정보 표시 기획안 - 유저에게 필요한 정보 표시 데이타
	MapIndex_t		MapIndex;
	INT				MapInfluenceType;
	BYTE			Belligerence;
	INT				HPRate;
	INT				TelePortState;
	ATUM_DATE_TIME  TelePortBuildingStartTime;
	ATUM_DATE_TIME  TelePortBuildingEndTime;
};
typedef vector<MSWARINFO_DISPLAY>		vectMSWARINFO_DISPLAY;

enum EN_MSWARINFO_MODIFY_TYPE
{// 2008-03-27 by dhjin, 모선전 정보 표시 기획안 - 모선 정보 표시 수정되는 타입
	T_MSWARINFO_MODIFY_UNKNOWN = 0,		// 알수 없음
	T_MSWARINFO_MODIFY_HPRATE = 1,		// HP등급 변경
	T_MSWARINFO_MODIFY_CREATE_TELEPORT = 2,		// Teleport 생성
	T_MSWARINFO_MODIFY_CHANGE_TELEPORT_STATE = 3			// Teleport 상태값 변경
};

//////////////////////////////////////////////////////////////////////////
// 2008-04-01 by dhjin, 모선전, 거점전 정보창 기획안 - 
struct SMSWAR_INFO_RESULT
{// 2008-04-01 by dhjin, 모전전 전장정보
	BYTE			AttInfluence;
	INT				MonsterUID;
	INT				ContributionPoint;
	ATUM_DATE_TIME	MSWarStartTime;
	ATUM_DATE_TIME	MSWarEndTime;
	BYTE			WinInfluence;
};
typedef vector<SMSWAR_INFO_RESULT>		vectSMSWAR_INFO_RESULT;

struct SSPWAR_INFO_RESULT
{// 2008-04-01 by dhjin, 거점전 전장정보
	BYTE			AttInfluence;
	INT				SPSummonMapIndex;
	ATUM_DATE_TIME	SPWarStartTime;
	ATUM_DATE_TIME	SPWarEndTime;
	BYTE			WinInfluence;
};
typedef vector<SSPWAR_INFO_RESULT>		vectSSPWAR_INFO_RESULT;
typedef SSPWAR_INFO_RESULT				MSG_FC_INFO_SPWARINFO_RESULT_OK;

///////////////////////////////////////////////////////////////////////////////
// 2008-04-16 by cmkwon, 몬스터 사망 시 몬스터 소환 이벤트 시스템 구현 - 
typedef UINT32 ExceptMon_t;
#define EXCEPTMON_OBJECT_MONSTER_MASK		(ExceptMon_t)0x00000001			// 오브젝트 몬스터 MonsterForm 값이 8,9,10
#define EXCEPTMON_INFLUENCE_TYPE_MASK		(ExceptMon_t)0x00000002			// 세력전 몬스터 Belligerence
#define EXCEPTMON_BELL_NOTATTACK_MASK		(ExceptMon_t)0x00000004			// 공격 성향이 없는 몬스터 Belligerence 값이 4인 몬스터

struct SEVENT_MONSTER
{
	INT					EventMonsterUID;
	INT					ServerGroupID;				// ServerGroupID ( 0이면 모든 서버군에 적용, 0이 아니면 해당 서버군만 적용)
	ATUM_DATE_TIME		StartDateTime;				// EventMonster 시작 날짜시간
	ATUM_DATE_TIME		EndDateTime;				// EventMonster 종료 날짜시간
	MapIndex_t			SummonerMapIndex;			// 소환되는 맵인덱스(0이면 모든맵에서 소환됨, 0이 아니면 지정한 맵에서만 소환됨)
	BYTE				SummonerReqMinLevel;		// 소환하는 몬스터의 최소 레벨 체크(0이면 체크하지 않음)
	BYTE				SummonerReqMaxLevel;		// 소환하는 몬스터의 최고 레벨 체크(0이면 제크하지 않음)
	ExceptMon_t			SummonerExceptMonster;		// 소환하는 몬스터 제외 체크  Bit Flag
	INT					SummonMonsterNum;			// 소환되는 MonsterUniqueNumber
	INT					SummonMonsterCount;			// 소환시 소환되는 몬스터 숫자
	INT					SummonDelayTime;			// 몬스터 사망 후 소환까지 걸리는 지연시간(단위:초)
	Prob10K_t			SummonProbability;			// 소환 성공 확률(0~10000)
};
typedef mt_vector<SEVENT_MONSTER>				mtvectSEVENT_MONSTER;

struct SSUMMON_EVENT_MONSTER
{
	BOOL				IsSummonChecked;			// 소환 여부 체크 플래그
	INT					SummonMonsterNum;			// 소환되는 MonsterUniqueNumber
	INT					SummonMonsterCount;			// 소환시 소환되는 몬스터 숫자
	INT					SummonDelayTime;			// 몬스터 사망 후 소환까지 걸리는 지연시간(단위:초)
	Prob10K_t			SummonProbability;			// 소환 성공 확률(0~10000)	

	inline SSUMMON_EVENT_MONSTER& operator=(const SEVENT_MONSTER& rhs)
	{
		this->SummonMonsterNum = rhs.SummonMonsterNum;
		this->SummonMonsterCount = rhs.SummonMonsterCount;
		this->SummonDelayTime = rhs.SummonDelayTime;
		this->SummonProbability = rhs.SummonProbability;
		return *this;
	}
};
typedef mt_vector<SSUMMON_EVENT_MONSTER>		mtvectSSUMMON_EVENT_MONSTER;


///////////////////////////////////////////////////////////////////////////////
// 2008-04-29 by cmkwon, 서버군 정보 DB에 추가(신규 계정 캐릭터 생성 제한 시스템추가) - 
struct SDBSERVER_GROUP
{
	int				ServerGroupID;
	char			ServerGroupName[SIZE_MAX_SERVER_NAME];
	int				LimitUserCount;
	BOOL			LockCreateCharacterForNewAccount;
};

//////////////////////////////////////////////////////////////////////////
// 2008-04-15 by dhjin, EP3 편지 시스템 - 
#define	LETTER_PASSED_RANGE_DAY		14			// 2008-04-29 by dhjin, EP3 편지 시스템 - 편지 삭제 기간, 단위 날
#define	SIZE_MAX_LETTER_TITLE		40		// 2008-04-15 by dhjin, EP3 편지 시스템 - 편지 제목
#define	SIZE_MAX_LETTER_CONTENT		1000		// 2008-04-15 by dhjin, EP3 편지 시스템 - 편지 내용
struct SLETTER_INFO
{
	UID64_t			LetterUID;
	UID32_t			RecvCharacterUID;
	CHAR			SendCharacterName[SIZE_MAX_CHARACTER_NAME];
	ATUM_DATE_TIME  SendDate;
	BOOL			CheckRead;
	CHAR			Title[SIZE_MAX_LETTER_TITLE];
	CHAR			Content[SIZE_MAX_LETTER_CONTENT];
};
typedef vector<SLETTER_INFO>			vectSLETTER_INFO;

// 2008-06-03 by cmkwon, AdminTool, DBTool 사용시 아이템 검색시 콤보박스에서 검색 기능 추가(K0000143) - 
char* StringCullingForValidChar(char* i_szSource, int i_nCullingSize);

//////////////////////////////////////////////////////////////////////////
// 2008-05-27 by dhjin, EP3 - 여단 수정 사항 - 여단 지원자 관리
#define	GUILDINTRODUCTION_PASSED_RANGE_DAY		5			// 2008-05-27 by dhjin, EP3 - 여단 수정 사항 - 여단 지원자 관리
struct SGUILD_INTRODUCTION
{
	char			IntroductionContent[SIZE_MAX_NOTICE];
	ATUM_DATE_TIME	RegDate;
};

struct SGUILD_APPLICANT_INFO
{
	UID32_t		CharacterUID;
	char		CharacterName[SIZE_MAX_CHARACTER_NAME];
	USHORT		UnitKind;
	BYTE		Level;
};
typedef vector<SGUILD_APPLICANT_INFO>	vectSGUILD_APPLICANT_INFO;

struct SGUILD_SEARCH_INTRODUCTION
{// 2008-05-27 by dhjin, EP3 - 여단 수정 사항 - 여단 소개 검색
	UID32_t			GuildUID;
	char			GuildName[SIZE_MAX_GUILD_NAME];
	ATUM_DATE_TIME	WriteDate;
	char			GuildIntroduction[SIZE_MAX_NOTICE];
	char			CharacterName[SIZE_MAX_CHARACTER_NAME];
};
typedef vector<SGUILD_SEARCH_INTRODUCTION>	vectSGUILD_SEARCH_INTRODUCTION;

//////////////////////////////////////////////////////////////////////////
// 2008-06-02 by dhjin, EP3 편대 수정 - 
#define ITEM_DISTRIBUTE_TYPE_DAMAGE			0	// 2008-06-02 by dhjin, EP3 편대 수정 - 개인 습득	
#define ITEM_DISTRIBUTE_TYPE_ORDER			1	// 2008-06-02 by dhjin, EP3 편대 수정 - 순차 습득 
#define ITEM_DISTRIBUTE_TYPE_RANDOM			2	// 2008-06-02 by dhjin, EP3 편대 수정 - 랜덤 습득

#define PARTY_JOIN_TYPE_INVITE_MASTER		0	// 2008-06-02 by dhjin, EP3 편대 수정 - 편대장 초대 참여 방식 
#define PARTY_JOIN_TYPE_FREE				1	// 2008-06-02 by dhjin, EP3 편대 수정 - 자유 참여 방식

#define SIZE_MAX_PARTY_NAME					32	// 2008-06-02 by dhjin, EP3 편대 수정 - 파티 이름 최대 길이

#define SIZE_MAX_RECOMMENDATION				5	// 2008-06-04 by dhjin, EP3 편대 수정 -  추천 케릭터 전송 최대 수

struct SPARTY_INFO
{// 2008-06-02 by dhjin, EP3 편대 수정 - 편대 정보
	BYTE		PartyInfluence;
	char		PartyName[SIZE_MAX_PARTY_NAME];
	BYTE		PartyJoinType;
	BYTE		ExpDistributeType;
	BYTE		ItemDistributeType;
	BOOL		PartyLock;
	CHAR		PartyPW[SIZE_MAX_TEAM_PW];
	INT			MinLevel;
	INT			MaxLevel;
	BYTE		FormationType;
	BYTE		IsAppliedFormationSkill;	// 2009-08-03 by cmkwon, EP3-4 편대 대형 스킬 구현 - 
};

//////////////////////////////////////////////////////////////////////////
// 2008-06-09 by dhjin, EP3 채팅방 -
#define SIZE_MAX_CHATROOM_NAME				34		// 2008-06-09 by dhjin, EP3 채팅방 - 채팅방 이름 최대 수	
#define SIZE_MAX_CHATROOM_COUNT				1000	// 2008-06-16 by dhjin, EP3 채팅방 - 채팅방 최대 수

//////////////////////////////////////////////////////////////////////////
// 2008-06-20 by dhjin, EP3 유저정보옵션 -
#define USER_INFO_OPTION_SECRET_LEVEL				(USHORT)0x0001			// 2008-06-23 by dhjin, EP3 유저정보옵션 - 계급 (일반)
#define USER_INFO_OPTION_SECRET_POSITION			(USHORT)0x0002			// 2008-06-23 by dhjin, EP3 유저정보옵션 - 위치 (일반)
#define USER_INFO_OPTION_SECRET_PROPENSITY			(USHORT)0x0004			// 2008-06-23 by dhjin, EP3 유저정보옵션 - 명성 (일반)
#define USER_INFO_OPTION_SECRET_GUILD				(USHORT)0x0008			// 2008-06-23 by dhjin, EP3 유저정보옵션 - 소속 (일반)
#define USER_INFO_OPTION_SECRET_LASTLOGIN			(USHORT)0x0010			// 2008-06-23 by dhjin, EP3 유저정보옵션 - 최종 접속일 (일반)
#define USER_INFO_OPTION_SECRET_GUILD_LEVEL			(USHORT)0x0100			// 2008-06-23 by dhjin, EP3 유저정보옵션 - 계급 (여단)
#define USER_INFO_OPTION_SECRET_GUILD_POSITION		(USHORT)0x0200			// 2008-06-23 by dhjin, EP3 유저정보옵션 - 위치 (여단)
#define USER_INFO_OPTION_SECRET_GUILD_PROPENSITY	(USHORT)0x0400			// 2008-06-23 by dhjin, EP3 유저정보옵션 - 명성 (여단)
#define USER_INFO_OPTION_SECRET_GUILD_GUILD			(USHORT)0x0800			// 2008-06-23 by dhjin, EP3 유저정보옵션 - 소속 (여단)
#define USER_INFO_OPTION_SECRET_GUILD_LASTLOGIN		(USHORT)0x1000			// 2008-06-23 by dhjin, EP3 유저정보옵션 - 최종 접속일 (여단)
#define USER_INFO_OPTION_MISSIONMASTER				(USHORT)0x2000			// 2008-12-08 by dhjin, 미션마스터 - 유저가 미션 마스터 설정을 했는지에 대한 내용

struct SUSER_INFO_OPTION
{// 2008-06-20 by dhjin, EP3 유저정보옵션 -
	BYTE				PilotFace;
	char				CharacterName[SIZE_MAX_CHARACTER_NAME];
	USHORT				UnitKind;
	UID32_t				GuildUID;
	char				GuildName[SIZE_MAX_GUILD_NAME];
	BYTE				Level;
	MAP_CHANNEL_INDEX	MapChannelIndex;
	INT					Propensity;
	ATUM_DATE_TIME		LastStartedTime;
	INT					SecretInfoOption;
	char				NickName[SIZE_MAX_CHARACTER_NAME];			// 2009-02-12 by cmkwon, EP3-3 월드랭킹시스템 구현 - 
};

//////////////////////////////////////////////////////////////////////////
// 2008-08-18 by dhjin, 1초 텀 시스템 기획안
#define INTERVAL_SYSTEM_MS			200   

//////////////////////////////////////////////////////////////////////////
// 2008-08-25 by dhjin, 태국 PC방 IP정보 로딩
#define MinPCBangMinTick			10
#define MaxPCBangMinTick			1440


typedef vector<MapIndex_t>			vectMapIndexList;		// 2008-09-10 by cmkwon, 통합아레나 맵설정(map.cfg) 관련 수정 - 

//////////////////////////////////////////////////////////////////////////
// 2008-10-13 by dhjin, 여단장 위임 가능 레벨 체크 추가.
#define GuildCommanderMinLevel		20

//////////////////////////////////////////////////////////////////////////
// 2008-11-10 by dhjin, 럭키머신
struct SLUCKY_MACHINE
{
	INT			BuildingIndex;
	BYTE		MachineKind;		// 2009-03-03 by dhjin, 럭키머신 수정안
	INT			MachineNum;			// 2009-03-03 by dhjin, 럭키머신 수정안
	INT			CoinItemNum;
	BYTE		SlotNum;			// 2009-03-03 by dhjin, 럭키머신 수정안
	INT			SlotProbability;
	INT			MysteryItemDropNum;
};
typedef vector<SLUCKY_MACHINE>		vectSLUCKY_MACHINE;
typedef vector<SLUCKY_MACHINE*>		vectSLUCKY_MACHINEPtr;	// 2010-04-20 by cmkwon, 신규 러키 머신 구현 - 기존 소스 수정 - 

#define MaxPayLuckyMachineItem		3			// 최대 슬롯 카운트(MAX_LUCKY_MACHINE_SLOT)와 같은 의미로 사용

//////////////////////////////////////////////////////////////////////////
// 2008-12-08 by dhjin, 미션마스터
#define SIZE_MAX_MISSIONMASTER_HELP_COUNT	5

//////////////////////////////////////////////////////////////////////////
// 2008-12-23 by dhjin, 전쟁 보상 추가안
#define	BGEAR_WAR_CONTRIBUTION		0.7f
#define	IGEAR_WAR_CONTRIBUTION		1
#define	MGEAR_WAR_CONTRIBUTION		3
#define	AGEAR_WAR_CONTRIBUTION		1	
#define PAY_WAR_CONTRIBUTION_BY_BOSS				2000000
#define PAY_WAR_CONTRIBUTION_BY_OUTPOST				1000000
#define PAY_WAR_CONTRIBUTION_BY_STRATEGYPOINT		500000
#define PAY_WAR_CONTRIBUTION_LEADER_BY_BOSS			200
#define PAY_WAR_CONTRIBUTION_1_GUILD_BY_BOSS		100
#define PAY_WAR_CONTRIBUTION_2_GUILD_BY_BOSS		80
#define PAY_WAR_CONTRIBUTION_3_GUILD_BY_BOSS		50
#define PAY_WAR_CONTRIBUTION_1_GUILD_BY_BOSS_PLUS	30000000
#define PAY_WAR_CONTRIBUTION_2_GUILD_BY_BOSS_PLUS	20000000
#define PAY_WAR_CONTRIBUTION_3_GUILD_BY_BOSS_PLUS	10000000
#define PAY_TYPE_BOSS				(BYTE)0
#define PAY_TYPE_OUTPOST			(BYTE)1
#define PAY_TYPE_STRATEGYPOINT		(BYTE)2
#define PAY_TYPE_BOSS_LEADER		(BYTE)10
#define PAY_TYPE_BOSS_1_GUILD		(BYTE)11
#define PAY_TYPE_BOSS_2_GUILD		(BYTE)12
#define PAY_TYPE_BOSS_3_GUILD		(BYTE)13

// 2009-07-08 by cmkwon, 전쟁 관련 정의 위치 이동(LocalizationDefineCommon.h) - 
//#define PAY_MINIMUN_COUNT			10

#define PAY_MINIMUN_BY_BOSS				100000
#define PAY_MINIMUN_BY_OUTPOST			100000	
#define PAY_MINIMUN_BY_STRATEGYPOINT	50000
#define PAY_MAXMUN_BY_BOSS				10000000	// 2009-03-18 by cmkwon, 전쟁 보상 추가안 수정(개인 보상 최대값 설정) - 모선전 천만
#define PAY_MAXMUN_BY_OUTPOST			10000000	// 2009-03-18 by cmkwon, 전쟁 보상 추가안 수정(개인 보상 최대값 설정) - 전진기지전 천만
#define PAY_MAXMUN_BY_STRATEGYPOINT		5000000		// 2009-03-18 by cmkwon, 전쟁 보상 추가안 수정(개인 보상 최대값 설정) - 거점전 5백만

#define NOT_OTHER_INFL_STAY			0
#define OTHER_INFL_STAY				1
#define NONE_DAMAGE_CONTRIBUTION	0
#define DAMAGE_CONTRIBUTION			1

struct SWAR_CONTRIBUTION_INFO
{// 유저가 상대세력맵에 머문 시간과 죽은 수를 관리한다.
	ATUM_DATE_TIME	OtherInflStayStartTime;
	INT				OtherInflStayTime;
	BOOL			CheckOtherInflStay;		// NOT_OTHER_INFL_STAY : 상대세력맵이 아님, OTHER_INFL_STAY : 상대세력맵, 0->1 : 상대세력맵으로 이동, 1->0 : 상대세력이 아닌 맵으로 이동
	INT				DeathCount;
	UID64_t			Contribution;
	BOOL			CheckDamageContribution; // NONE_DAMAGE_CONTRIBUTION : 아직 데미지준 기여도 없음, DAMAGE_CONTRIBUTION : 데미지 기여도가 있음
};

///////////////////////////////////////////////////////////////////////////////
// 2009-01-14 by cmkwon, 운영자 자동 공지 시스템 구현 - 
#define SIZE_MAX_ADMIN_NOTICE_STRING			256		// 최대 공지 사항 길이 
#define SIZE_MAX_COUNT_ADMIN_NOTICE_STRING		20		// 공지 사항 최대 개수
#define MIN_LOOP_SECONDS_OF_ADMIN_NOTICE		60		// 자동 공지 시스템이 다시 시작하는 최소 Interval time(second), 60초 = 1분
#define MAX_LOOP_SECONDS_OF_ADMIN_NOTICE		604800	// 자동 공지 시스템이 다시 시작하는 최대 Interval time(second), 604800초 = 10080분 = 168시간 = 7일
#define MIN_INTERVAL_SECONDS_OF_ADMIN_NOTICE	5		// 공지 스트링을 전송하고 다음 공지 스트링 전송하기 까지의 최소 Interval time(second), 5초
#define MAX_INTERVAL_SECONDS_OF_ADMIN_NOTICE	86400	// 공지 스트링을 전송하고 다음 공지 스트링 전송하기 까지의 최소 Interval time(second), 86400초 = 1440분 = 24시간 = 1일
#define DELAY_SEC_AFTER_SERVER_STARTED			300		// 서버 시작 후 자동 공지 시스템이 다시 시작하는 지연 시간 300초 = 5분

struct SANoticeInfo
{
	BOOL			UsingFlag;
	INT				LoopSec;					// 단위:초
	INT				IntervalSec;				// 단위:초
	char			EditorAccountName[SIZE_MAX_ACCOUNT_NAME];
	ATUM_DATE_TIME	LastStartedTime;
	INT				LastSentNoticeStringIndex;
};
struct SANoticeString		// AdminNoticeString
{
	INT				NoticeStringIndex;
	char			NoticeString[SIZE_MAX_ADMIN_NOTICE_STRING];
};
typedef vector<SANoticeString>			vectSANoticeString;
typedef mt_vector<SANoticeString>		mtvectSANoticeString;

struct sort_SANoticeString_by_StrIdx
{
	bool operator()(SANoticeString op1, SANoticeString op2)
	{
		return op1.NoticeStringIndex < op2.NoticeStringIndex;		// 오림차순 정렬
	}
};

//////////////////////////////////////////////////////////////////////////
// 2009-01-12 by dhjin, 선전 포고
#define MSWAR_NOT_START		0
#define MSWARING_BEFORE		1
#define MSWARING			2
#define MSWAR_END_WIN		11
#define MSWAR_END_LOSS		21
#define MSWAR_FORBID_GAP_HOUR 12
#define MSWAR_NEXT_LEADER_SETP	99
#define MSWAR_FINAL_SETP	5

struct SDECLARATION_OF_WAR
{
	BYTE			Influence;
	BYTE			MSWarStep;
	INT				NCP;
	INT				MSNum;
	MapIndex_t		MSAppearanceMap;
	ATUM_DATE_TIME	MSWarStepStartTime;
	ATUM_DATE_TIME	MSWarStepEndTime;
	ATUM_DATE_TIME	MSWarStartTime;
	ATUM_DATE_TIME	MSWarEndTime;
	BYTE			SelectCount;
	BOOL			GiveUp;
	BYTE			MSWarEndState;		// MSWAR_NOT_START : 전쟁 시작하지 않음, MSWARING : 전쟁중, MSWAR_END_WIN : 승리, MSWAR_END_LOSS : 패배
};

struct SDECLARATION_OF_WAR_FORBID_TIME
{
	INT				DayOfWeek;
	ATUM_DATE_TIME	ForbidStartTime;
	ATUM_DATE_TIME	ForbidEndTime;
};


///////////////////////////////////////////////////////////////////////////////
// 2009-01-22 by cmkwon, 전쟁 관련 게임 로그 수정 - WPUT_XXX, WarPointUpdateType
#define WPUT_UNKNOWN				0	
#define WPUT_GENERAL				1	
#define WPUT_ARENA					2	
#define WPUT_MOTHERSHIPWAR			3	
#define WPUT_STRATEGYPOINTWAR		4	
#define WPUT_OUTPOSTWAR				5	
#define WPUT_SHOP					6	
#define WPUT_ADMIN_COMMAND			7	
extern char* GetWPUTString(BYTE i_byWPUT);

///////////////////////////////////////////////////////////////////////////////
// 2009-01-23 by cmkwon, 터키 i,I 문자 문제 처리 - LowercaseOnly_i_forTurkish() 추가, 터키 서비스만 i문자만 소문자로 변경
extern char* LowercaseOnly_i_forTurkish(char* i_szString, int i_nMaxLen);


///////////////////////////////////////////////////////////////////////////////
// 2009-02-12 by cmkwon, EP3-3 월드랭킹시스템 구현 - 
#define SIZE_MAX_SERVICE_NAME			20						// 월드 랭키에서 서비스 군을 위한 서비스명 최대 글자수, 최대 영문 19글자
#define SIZE_MAX_NAME_FOR_RANKING		SIZE_MAX_CHARACTER_NAME	// 
#define SIZE_MAX_SERVICE_SYMBOL_IMAGE	2000					// 48x28 jpg 파일,
#define SIZE_MAX_WRK_COUNT				100						// 월드랭킹 필수 랭킹
#define SIZE_MAX_REQUEST_COUNT			20						// 한번에 요청 가능한 최대 랭킹리스트

#define RANKING_SCOPE_LOCAL				0		// 현재 서비스 로컬 랭킹, Name 이 NickName
#define RANKING_SCOPE_WORLD				1		// 월드 랭킹 정보, Name 이 CharacterName
#define IS_VALID_RANKING_SCOPE(s)		((s) == 0 || (s) == 1)

#define RANKING_TYPE_LEVEL				0		// Level 랭킹
#define RANKING_TYPE_FAME				1		// 개인 명성 랭킹
#define RANKING_TYPE_PVP				2		// 1:1 PvP 랭킹

struct SWRK_SERVICE_INFO
{
	INT			ServiceUID;
	char		ServiceName[SIZE_MAX_SERVICE_NAME];
	BYTE		ServiceSymbolIamge[SIZE_MAX_SERVICE_SYMBOL_IMAGE];
	INT			SymbolImageSize;
};
struct SWRK_SERVER_GROUP
{
	INT			ServerGroupID;
	char		ServerGroupNameforRK[SIZE_MAX_SERVER_NAME];
};
struct SWRK_BASE
{
	INT				ServiceUID;
	INT				UnitKind;
	char			ServerGroupNameforRK[SIZE_MAX_SERVER_NAME];
	char			NameforRK[SIZE_MAX_NAME_FOR_RANKING];
	BYTE			InfluenceType;
	BYTE			Level;
	BYTE			RankingScope;		// RANKING_SCOPE_XXX
};
typedef SWRK_BASE	SWRK_LEVEL;
struct SWRK_LEVEL_FOR_DB : public SWRK_LEVEL
{
	INT				ServerGroupID;
	UID32_t			CharacterUID;
	Experience_t	Experience;
	ATUM_DATE_TIME	LevelUpTime;
};

struct SWRK_FAME : public SWRK_BASE
{
	INT				Fame;
};
struct SWRK_FAME_FOR_DB : public SWRK_FAME
{
	INT				ServerGroupID;
	UID32_t			CharacterUID;
};

struct SWRK_PVP : public SWRK_BASE
{
	INT			WinPoint;
	INT			LossPoint;
	INT			Score;
};
struct SWRK_PVP_FOR_DB : public SWRK_PVP
{
	INT				ServerGroupID;
	UID32_t			CharacterUID;
};
typedef vector<SWRK_SERVER_GROUP>		vectSWRK_SERVER_GROUP;

typedef mt_vector<SWRK_SERVICE_INFO>	mtvectSWRK_SERVICE_INFO;

typedef mt_vector<SWRK_LEVEL>			mtvectSWRK_LEVEL;
typedef mt_vector<SWRK_LEVEL*>			mtvectSWRK_LEVELPtr;
typedef mt_vector<SWRK_LEVEL_FOR_DB>	mtvectSWRK_LEVEL_FOR_DB;

typedef mt_vector<SWRK_FAME>			mtvectSWRK_FAME;
typedef mt_vector<SWRK_FAME*>			mtvectSWRK_FAMEPtr;
typedef mt_vector<SWRK_FAME_FOR_DB>		mtvectSWRK_FAME_FOR_DB;

typedef mt_vector<SWRK_PVP>				mtvectSWRK_PVP;
typedef mt_vector<SWRK_PVP*>			mtvectSWRK_PVPPtr;
typedef mt_vector<SWRK_PVP_FOR_DB>		mtvectSWRK_PVP_FOR_DB;

extern int GetArrIdxByUnitMaskforWRK(INT i_unitMask);
extern int GetUnitMaskByArrIdxforWRK(INT i_arrIdx);


//////////////////////////////////////////////////////////////////////////
// 2009-03-03 by dhjin, 럭키머신 수정안
#define SIZE_MAX_LUCKYMACHINE_DESCRIPTION		200
struct LUCKY_MACHINE_OMI
{
	INT			order;
	INT			BuildingInx;
	BYTE		MachineKind;
	INT			MachineNum;
	INT			CoinItemNum;
	BYTE		SlotNum;
	INT			SourceIndex;
	char		szDescription[SIZE_MAX_LUCKYMACHINE_DESCRIPTION];
};


///////////////////////////////////////////////////////////////////////////////
// 2009-03-09 by cmkwon, 일본 Arario nProtect에 CS인증 적용하기 - 
#define MAX_PACKET_SIZE_FOR_NPROTECT	128			// 2009-03-09 by cmkwon, 일본 Arario nProtect에 CS인증 적용하기 - 최대 프로토콜 크기

//////////////////////////////////////////////////////////////////////////
// 2009-03-10 by dhjin, 단계별 모선 시스템
#define MSBOSSSTEP_UNKNOWN_BEFOREWAR	0			// 전 주기에 모선전 정보가 없거나 첫 주기 모선
#define MSBOSSSTEP_WIN_BEFOREWAR		1			// 전 주기에 모선전 승리
#define MSBOSSSTEP_LOSS_BEFOREWAR		2			// 전 주기에 모선전 패배



///////////////////////////////////////////////////////////////////////////////
// 2009-03-31 by cmkwon, 세력초기화 시스템 구현 - 
#define QUEST_INDEX_OF_SELECT_INFLUENCE				112		// 세력 선택 미션 QuestIndex, 모든 서비스 동일함

struct SQUEST_MATCHING
{
	INT		QuestIndexForBCU;
	INT		QuestIndexForANI;
};
typedef vector<SQUEST_MATCHING>			vectSQUEST_MATCHING;

struct SQUEST_MATCH_CHANGE
{
	INT		FromQuestIndex;
	INT		ToQuestIndex;
};
typedef vector<SQUEST_MATCH_CHANGE>		vectSQUEST_MATCH_CHANGE;

struct SITEM_MATCHING
{
	INT		ItemNumForBCU;
	INT		ItemNumForANI;
};
typedef vector<SITEM_MATCHING>			vectSITEM_MATCHING;

struct SITEM_MATCH_CHANGE
{
	INT		FromItemNum;
	INT		ToItemNum;
};
typedef vector<SITEM_MATCH_CHANGE>		vectSITEM_MATCH_CHANGE;



///////////////////////////////////////////////////////////////////////////////
// 2009-04-06 by cmkwon, 콜오브 히어로 스킬 시스템 변경 - 
struct SSKILL_CONFIRM_USE
{
	int					SkillConfirmUseUID;
	DWORD				ExpireTick;
	UID32_t				TargetCharacterUID;
	int					UsingSkillItemNum;		// 사용 스킬 ItemNum
	MAP_CHANNEL_INDEX	MapChannelIndex;		// 스킬 사용자의 MapChannelIndex
	D3DXVECTOR3			PositionVec3;
};
typedef mt_vector<SSKILL_CONFIRM_USE>			mtvectSSKILL_CONFIRM_USE;


///////////////////////////////////////////////////////////////////////////////
// 2009-07-09 by jwlee, 게임 정보 테이블 데이터 DB에 밀어넣기 툴 구현 -
#define SIZE_MAX_ITEM_INFO_NAME					250
#define SIZE_MAX_TABINDEX						250
#define SIZE_MAX_ITEMDESCRIPTION				250
#define SIZE_MAX_OBJECT_DESCRIPTION				250

typedef struct
{
	int		ShopOrder;
	int		UniqueNumber;
	int		ItemNum;
}SHOP_INFO;
typedef mt_vector<SHOP_INFO>			vectSHOP_INFO;

typedef struct
{
	int		MapIndex;
	int		BuildingIndex;
	int		WarpTargetMapIndex;
	int		WarpTargetIndex;
	char	WarpTargetName[SIZE_MAX_WARP_TARGET_NAME];
	int		Fee;
}CITY_TARGET_WARPMAP;
typedef mt_vector<CITY_TARGET_WARPMAP>			vectCITY_TARGET_WARPMAP;

typedef struct
{
	char			MapName[SIZE_MAX_MAP_NAME];
	MapIndex_t		MapIndex;
	int				StratrgyPiontNum;
}STRATEGYPOINT_SUMMON_MAPINDEX;
typedef mt_vector<STRATEGYPOINT_SUMMON_MAPINDEX>			vectSTRATEGYPOINT_SUMMON_MAPINDEX;

struct MONSTER_DATA : public MONSTER_INFO
{
	int		ControlSkil;
	int		SizeForServer;
	int		SizeForClient;
	int		MonsterItem[ARRAY_SIZE_MONSTER_ITEM];
};
typedef mt_vector<MONSTER_DATA>			vectMONSTER_DATA;

struct MAPOBJECT : public _MAPOBJECTINFO
{
	char	ObjectName[SIZE_MAX_OBJECT_NAME];
	USHORT	RadiusForServer;
	USHORT	RadiusForClient;
	char	ObjectDescription[SIZE_MAX_OBJECT_DESCRIPTION];
};
typedef mt_vector<MAPOBJECT>			vectMAPOBJECT;

struct LUCKY_MACHINE : public LUCKY_MACHINE_OMI
{
	int		SlotProbability;
	int		MysteryItemDropNum;
};
typedef mt_vector<LUCKY_MACHINE>			vectLUCKY_MACHINE;

typedef vector<MYSTERY_ITEM_DROP>				vectMYSTERY_ITEM_DROP;

typedef struct
{
	float	IsDisable;
	float	GameUID;
	float	ItemNum;
	char	ItemName[SIZE_MAX_ITEM_NAME];
	float	TabIndex;
	char	IconFileName[SIZE_MAX_TABINDEX];
	float	ItemUnitPrice;
	char	ItemDescription[SIZE_MAX_ITEMDESCRIPTION];
}ITEM_INFO;
typedef vector<ITEM_INFO>			vectItem_Info;

// 2009-09-16 by cmkwon, 세력 초기화시 어뷰징 방지 구현 - ti_InfluenceRate 테이블 추가, 
struct STI_INFLUENCERATE
{
	BYTE	StartLevel;
	BYTE	EndLevel;
};
typedef vector<STI_INFLUENCERATE>		vectSTI_INFLUENCERATE;


///////////////////////////////////////////////////////////////////////////////
// 2009-08-03 by cmkwon, EP3-4 편대 대형 스킬 구현 - AtumProtocol.h에 정의되어 있는것을 여기로 옮김
#define FLIGHT_FORM_NONE				(BYTE)0 // 편대 비행 안 함
#define FLIGHT_FORM_2_COLUMN			(BYTE)1 // 이렬 종대, 이렬 종대 모양으로 두 줄로 나란히 선 모양이다
#define FLIGHT_FORM_2_LINE				(BYTE)2 // 이렬 횡대, 이렬 횡대 모양으로 두 줄로 나란히 선 모양이다
#define FLIGHT_FORM_TRIANGLE			(BYTE)3 // 삼각 편대, 삼각형 모양으로 상단부터 1, 2, 3개의 유닛이 위치한다
#define FLIGHT_FORM_INVERTED_TRIANGLE	(BYTE)4 // 역삼각 편대, 역 삼각형 모양으로 상단부터 3, 2, 1개의 유닛이 위치한다
#define FLIGHT_FORM_BELL				(BYTE)5 // 종 형태, 종 모양으로 상단부터 1, 3, 2개의 유닛이 위치한다
#define FLIGHT_FORM_INVERTED_BELL		(BYTE)6 // 역종 형태, 역종 모양으로 상단부터 2, 3, 1개의 유닛이 위치한다
#define FLIGHT_FORM_X					(BYTE)7 // X자 형태
#define FLIGHT_FORM_STAR				(BYTE)8 // 별 형태

#define ITEM_UID_FOR_PARTY_FLIGHT_FORMATION_SKILL_START			(INVALID_UID64-1000)	// 제일 뒤에 1000개를 편대 스킬을 UID로 사용하도록 한다.


///////////////////////////////////////////////////////////////////////////////
// 2009-09-16 by cmkwon, 세력 초기화시 어뷰징 방지 구현 - 
#define PERIOD_OF_DAY_FOR_VALID_INFLUENCE		30		// 유효한 세력 최접 접속 일수

struct SINFL_USER_COUNT
{
	BYTE			StartLevel;
	BYTE			EndLevel;
	ATUM_DATE_TIME	UpdatedTime;
	INT				AllowablePercent;
	INT				arrUserCount[INFLUENCE_TYPE_COUNT_EX_ALL];		// index ==> 0:Normal, 1:BCU, 2:ANI

	BOOL AddUserCount(BYTE i_byInflTy, int i_nValues = 1)
	{
		switch (i_byInflTy)
		{
		case INFLUENCE_TYPE_NORMAL:		arrUserCount[0] += i_nValues;		break;
		case INFLUENCE_TYPE_VCN:		arrUserCount[1] += i_nValues;		break;
		case INFLUENCE_TYPE_ANI:		arrUserCount[2] += i_nValues;		break;
		default:
		{
			return FALSE;
		}
		}
		return TRUE;
	}
	BOOL SubtractUserCount(BYTE i_byInflTy, int i_nValues = 1)
	{
		switch (i_byInflTy)
		{
		case INFLUENCE_TYPE_NORMAL:		arrUserCount[0] = max(0, arrUserCount[0] - i_nValues);		break;
		case INFLUENCE_TYPE_VCN:		arrUserCount[1] = max(0, arrUserCount[1] - i_nValues);		break;
		case INFLUENCE_TYPE_ANI:		arrUserCount[2] = max(0, arrUserCount[2] - i_nValues);		break;
		default:
		{
			return FALSE;
		}
		}
		return TRUE;
	}
	BOOL IsSetForAll(void)
	{
		if (0 == StartLevel && 0 == EndLevel)
		{
			return TRUE;
		}
		return FALSE;
	}
};
typedef mt_vector<SINFL_USER_COUNT>		mtvectSINFL_USER_COUNT;

///////////////////////////////////////////////////////////////////////////////
// 2009-10-06 by cmkwon, 베트남 게임 가드 X-TRAP으로 변경 - 
#define XTRAP_SIZE_MAX_SESSIONBUF		320			// 2009-10-06 by cmkwon, 베트남 게임 가드 X-TRAP으로 변경 - 최대 프로토콜 크기
#define XTRAP_CSFILE_NUM				5			// 2009-10-06 by cmkwon, 베트남 게임 가드 X-TRAP으로 변경 - 실시간 지원 실행파일 업데이트 개수
// 2009-10-29 by cmkwon, 베트남 X-TRAP 자동업데이트 기능 적용 - 
#if defined(SERVICE_TYPE_VIETNAMESE_SERVER_1)
#define XTRAP_KEY_STRING				"660970B4E839D8FFE53D6D9844CFE862B5FBE52B2875C638EC78A75D5FDB5C182F76A736AABEA256E36B6165D77729DD9C3419ED86B2D75179618347974228D00F7D04245246E41FB1670C4E95407F04E2D092B9A3C70452972B692C3EF35811"		
#endif
#if defined(SERVICE_TYPE_ARGENTINA_SERVER_1)
#define XTRAP_KEY_STRING				"660970B4963BD8A390256D9844CFE862F4BDBA635141DB3F0785BDC3E5836D033AFA4B1C226F9494F98192EBFF893A88756E0C810FF0175398D854AF913E10F40F7D04245246E406A670095295516F08D696B66EAE38D3BD5E287A3A23"
#endif


///////////////////////////////////////////////////////////////////////////////
// 2009-10-22 by cmkwon, 시간 제한형류 아이템 시스템 정리 - 
extern int GetNumberOfBits(INT64 i_n64Mask);
typedef enum {
	TIME_TERM_USING_ITEM = 1,		//
	TIME_TERM_DELETE_ITEM,				//
	TIME_TERM_PREMIUM,					//
	TIME_TERM_EVENT						//
										//
} TIME_TERM_t;

// 2009. 10. 27 by jskim 진행률 확인
#define WM_PROGRESSBAR_RANGE							WM_USER + 400	
#define WM_PROGRESSBAR_POS								WM_USER + 401	
//end 2009. 10. 27 by jskim 진행률 확인


///////////////////////////////////////////////////////////////////////////////
// 2009-11-04 by cmkwon, 태국 게임가드 Apex로 변경 - 
#define SECURITY_APEX_MaxPacketLen			1024	
#define SECURITY_APEX_ClientIpFlag			0x01
#define SECURITY_APEX_Cmd_Login				0x11
#define SECURITY_APEX_Cmd_Logout			0x12
#define SECURITY_APEX_Cmd_ApexData			0x13
#define SECURITY_APEX_Cmd_SimpleInputMsg	0x14
#define SECURITY_APEX_Cmd_ClientRet			0x15 

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// 2010. 05. 19 by hsLee 인피니티 필드 2차 난이도 조절. (신호처리 + 몬스터 처리(서버) )
#define DEFAULT_LEVEL_INFINITY_DIFFICULTY	25					// 인피니티 방 생성시 기본 선택 난이도. ( 모드 정보가 [확장-수정]된다면 외부 참조로 바꿀 수 있음. )


////////////////////////////////////////////////////////////////////////////////
// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 

#define TICK_CREATE_MONSTER_TERM_ONLY_INFINITY		2592000000		// 1000Msec * 60 Sec * 60 Min * 24 Hour * 30 Day : 약 한 달 뒤에 소환 되는 텀
#define TICK_FIRST_FORCED_CREATE_MONSTER_TERM		120000		// 1000Msec * 60 Sec * 2ㄴ Min : 첫 강제 소환 텀
#define COUNT_DELAY_FORCED_CREATE_MONSTER_TERM		60			// 60 Sec * 1 Min : 강제 소환 후 다시 강제 소환 체크까지 텀
#define TICK_TENDER_PROCESSING_TERM					20000		// 1000Msec * 20 Sec : Tender 진행 텀

typedef enum
{
	HPACTION_TALK_CONDITION_NONE = 0,
	HPACTION_TALK_CONDITION_CREATE = 1,				// 생성시 대화 출력
	HPACTION_TALK_CONDITION_DEAD = 2,				// 죽음시 대화 출력
	HPACTION_TALK_CONDITION_HP_RATE = 3,				// HP상태에 따라 대화 출력
	HPACTION_TALK_CONDITION_DAMAGED_RANDOM = 4,				// 피해 받을 경우 랜덤 대화 출력
	HPACTION_TALK_CONDITION_ATTACK = 5,				// 해당 HPAction  공격시 대화 출력
	HPACTION_TALK_CONDITION_TARGET_CHANGE = 6,				// 타겟 변경 시 대화 출력
} eHPACTION_TALK_CONDITION;
typedef enum
{
	HPACTION_TALK_IMPORTANCE_NONE = 0,
	HPACTION_TALK_IMPORTANCE_ALL = 1,				// 모든 유저에게 대화 전송
	HPACTION_TALK_IMPORTANCE_INFL = 2,				// 같은 세력 유저에게 대화 전송
	HPACTION_TALK_IMPORTANCE_CHANNEL = 3,				// 같은 채널 유저에게 대화 전송
//	HPACTION_TALK_IMPORTANCE_PARTY				= 4,				// 파티원에게 대화 전송
} eHPACTION_TALK_IMPORTANCE;

#define SIZE_MAX_HPTALK_DESCRIPTION					SIZE_MAX_CHAT_MESSAGE
#define HPTALK_DAMAGED_RANDOM_RATE				3					// 피격시 대사 할 확률 3%
#define SIZE_MAX_CINEMATALK_DESCRIPTION				SIZE_MAX_HPTALK_DESCRIPTION

struct HPACTION
{
	HPActionUID_t					HPActionUID;
	HPActionIdx_t					HPActionNum;
	HPValueRate_t					HPMaxValueRate;
	HPValueRate_t					HPMinValueRate;
	ItemIdx_t						UseItemArrayIdx;
	ItemIdx_t						NextUseItemArrayIdx;
	HPHitRate_t						HitRate;
	HPUseCount_t					UseCount;
	eHPACTION_TALK_CONDITION		HPTalkCondition;
	eHPACTION_TALK_IMPORTANCE		HPTalkImportance;
	MSec_t							PreHPCameraTremble;
	HPTalk_t						PreHPTalk[SIZE_MAX_HPTALK_DESCRIPTION];
	MSec_t							HPCameraTremble;
	HPTalk_t						HPTalk[SIZE_MAX_HPTALK_DESCRIPTION];
};
typedef vector<HPACTION>			vectHPAction;
struct HPACTION_TALK_DAMAGED_RANDOM
{
	HPTalk_t						HPTalk[SIZE_MAX_HPTALK_DESCRIPTION];
};
typedef vector<HPACTION_TALK_DAMAGED_RANDOM>	vectHPActionTalkDamagedRandom;
struct HPACTION_TALK_HPRATE
{
	HPValueRate_t					HPValueRate;
	eHPACTION_TALK_IMPORTANCE		HPTalkImportance;
	MSec_t							HPCameraTremble;
	ClientIndex_t					TargetClientIdx;			// 대상에 관련된 대사가 있다면 설정한다.
	HPTalk_t						HPTalk[SIZE_MAX_HPTALK_DESCRIPTION];
};
typedef vector<HPACTION_TALK_HPRATE>	vectHPActionTalkHPRate;
struct HPACTION_ATTACK_HPRATE
{
	HPActionUID_t					HPActionUID;		// 2009-09-09 ~ 2010-01-13 by dhjin, 인피니티 - 한 아이템으로 여러 대사 가능하게 수정
	HPValueRate_t					HPMaxValueRate;
	HPValueRate_t					HPMinValueRate;
	ItemIdx_t						UseItemArrayIdx;
	ItemIdx_t						NextUseItemArrayIdx;
	HPHitRate_t						HitRate;
	HPUseCount_t					UseCount;
};
typedef vector<HPACTION_ATTACK_HPRATE>	vectHPActionAttackHPRate;

struct HPACTION_TALK_ATTACK
{
	ItemIdx_t						ItemNum;
	HPActionUID_t					HPActionUID;		// 2009-09-09 ~ 2010-01-13 by dhjin, 인피니티 - 한 아이템으로 여러 대사 가능하게 수정
	ItemIdx_t						UseItemArrayIdx;
	MSec_t							PreHPCameraTremble;
	HPTalk_t						PreHPTalk[SIZE_MAX_HPTALK_DESCRIPTION];
	MSec_t							HPCameraTremble;
	HPTalk_t						HPTalk[SIZE_MAX_HPTALK_DESCRIPTION];
};
typedef vector<HPACTION_TALK_ATTACK>	vectHPActionTalkAttack;

struct DEBUFFINFO {
	INT			ItemNum;						// 아이템 고유번호, 장착 아이템일 때 (ITEM_BASE*)
	BYTE		Kind;							// 104 : 몬스터 스킬 // 아이템 종류(기관포, 빔, 로켓, 스킬.....), ITEMKIND_XXX
	BYTE		DesParam;
	float		DesParamValue;
	INT			Time;							// 지속 시간(스킬류 등) 단위 : ms
	BYTE		SkillLevel;						// 레벨
	BYTE		SkillType;						// 스킬형태(시간 및 발동 관련), 지속|클릭|시간|유지
	DWORD		dwUseTime;						// 디버프 적용 시간
};
typedef mt_vector<DEBUFFINFO>					mtvectorDebuffInfo;

struct DOTINFO {
	UID32_t				FirstTimerUID;
	ClientIndex_t		ClientIndex;
	INT					ItemNum;						// 아이템 고유번호, 장착 아이템일 때 (ITEM_BASE*)
	BYTE				Kind;							// 104 : 몬스터 스킬 // 아이템 종류(기관포, 빔, 로켓, 스킬.....), ITEMKIND_XXX
	BYTE				DesParam;
	float				DesParamValue;
	INT					Time;							// 지속 시간(스킬류 등) 단위 : ms
};
typedef mt_vector<DOTINFO>					mtvectorDotInfo;

typedef enum
{
	INFINITY_MODE_NONE = 0,
	INFINITY_MODE_BOSSRUSH = 1,
	INFINITY_MODE_DEFENCE = 2,
	INFINITY_MODE_MSHIPBATTLE = 3					// 2011-02-18 by hskim, 인피니티 3차 - 모선배틀

} eINFINITY_MODE;

// start 2011-04-21 by hskim, 인피니티 3차 - 시네마 단계별 기능 구현
// typedef enum
// {
// 	INFINITY_KEYMONSTER_NONE					= 0,
// 	INFINITY_KEYMONSTER_DEAD_FOR_NEXT_STEP		= 1,
// 	INFINITY_KEYMONSTER_ALIVE_FOR_GAME_CLEAR	= 2,
// 
// } eINFINITY_KEYMONSTER;
// end 2011-04-21 by hskim, 인피니티 3차 - 시네마 단계별 기능 구현

typedef enum		// 인피니티 스킵 상태값.
{
	INFINITY_SKIP_CINEMA_NONE = 0,
	INFINITY_SKIP_CINEMA_NORMAL,			// 스킵 - 정상 종료.
	INFINITY_SKIP_CINEMA_REQ_SKIP,			// 스킵 - 유저 요청.

} eINFINITY_SKIP_CINEMA;


struct CINEMAINFO {	// 2010-03-31 by dhjin, 인피니티(기지방어) - 구조 변경
	CinemaNum_t			CinemaNum;
	CinemaOrder_t		CinemaOrder;		// 51000 : 성공 종료 시네마, 52000 : 실패 종료 시네마, CINEMA_FIN_XXX
	MSec_t				StartTime;			// msec
	EffectIdx_t			EffectIdx;
	Position_t			EffectPosition_X;
	Position_t			EffectPosition_Y;
	Position_t			EffectPosition_Z;
	MSec_t				EffectPlayTime;		// msec	
	EffectPlayCount_t	EffectPlayCount;
	ObjectIdx_t			ObjectIdx;					// 맵에 찍힌 Object의 EvnetParamIndex
	ObjectNum_t			ChangeObjectIdx;			// 변경될 ObjectNum
	MSec_t				ChangeTime;			// msec			
	MSec_t				CameraTremble;		// msec	
	KeyMonster_t		KeyMonster;		// 2011-04-21 by hskim, 인피니티 3차 - 시네마 단계별 기능 구현
	MonIdx_t			MonsterIdx;					// 소환될 MonsterUnitkind
	SummonCnt_t			SummonCount;
	Distance_t			SummonRandomPos;	// M
	ObjectIdx_t			ObjectBodyConditionIdx;		// 맵에 찍힌 Object의 EvnetParamIndex
	BodyCond_t			BodyCondition;				// ObjectBodyConditionIdx Object에 설정 할 BodyCondition(성공:1024, 실패:32)
	FileName_t			TipFileName[SIZE_MAX_FILE_NAME];
	FileName_t			SkyFileName[SIZE_MAX_FILE_NAME];
	CinemaTalk_t		CinemaTalk[SIZE_MAX_CINEMATALK_DESCRIPTION];
	FileName_t			SoundFileName[SIZE_MAX_FILE_NAME];		// 2010-03-29 by cmkwon, 인피2차 시네마에 효과음 파일 설정 추가 - 
	// start 2011-04-28 by hskim, 인피니티 3차 - 시네마 관련 기능 추가
	QuestIndex_t		QuestIndex;					// 2011-03-09 by hskim, 시네마 퀘스트 인덱스 설정 추가
	eCINEMA_MONSTER_INDEX_TYPE	MonsterIdxType;		// CINEMA_MONSTER_INDEX_CREATE = 0 ,	CINEMA_MONSTER_INDEX_CREATE = 1
	CustomIdx_t			CustomIdx;					// 1xxx = 시네마 1번 , 2xxx = 시네마 2번 , 3xxx = 시네마 3번
	MonIdx_t			UpdateMonsterIdx;			// 적용할 몬스터 인덱스
	// end 2011-04-28 by hskim, 인피니티 3차 - 시네마 관련 기능 추가
};
typedef vector<CINEMAINFO>					vectorCinemaInfo;

struct REVISIONINFO {
	RevisionNum_t		RevisionNum;
	INT					UnitKind;
	Lv_t				RevisionLevel;
	RevisionHP_t		RevisionHP;
	RevisionDP_t		RevisionDP;
	RevisionWeapon1_t	RevisionStandardWeapon;
	RevisionWeapon2_t	RevisionAdvancedWeapon;
};
typedef vector<REVISIONINFO>				vectorRevisionInfo;

struct INFINITY_MONSTERINFO {
	UID32_t				InfinityMonsterUID;
	MonIdx_t			InfinityMonsterIdx;
	MonIdx_t			MonsterIdx;
	InfiMonTargetType_t	TargetType;
	InfiMonTargetCount_t	TargetCount;
};
typedef vector<INFINITY_MONSTERINFO>		vectorInfinityMonsterInfo;

struct INFINITY_MODEINFO {
	InfiModeUID_t		InfinityModeUID;
	MapIndex_t			MapIdx;
	eINFINITY_MODE		ModeTypeNum;
	MonIdx_t			InfinityMonsterIdx;
	CinemaNum_t			CinemaNum;
	RevisionNum_t		RevisionNum;
	ResetCycle_t		ResetCycle;
	EntranceCount_t		EntranceCount;
	MSec_t				LimitTime;
	Lv_t				MinLv;
	Lv_t				MaxLv;
	AdmissionCount_t	MinAdmissionCount;
	AdmissionCount_t	MaxAdmissionCount;
	Minute_t			TimePenaltyValue;		// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 인피 사망시 패널티 추가
	Penalty_t			HPPenaltyValue;			// 2011-06-14 by hskim, 인피니티 3차 - 패널티 기능 추가 (HP 및 시간 동시 지원을 위해)
};
typedef vector<INFINITY_MODEINFO>		vectorInfinityModeInfo;

struct INFINITY_IMPUTE {
	InfiModeUID_t		InfinityModeUID;
	EntranceCount_t		EntranceCount;
};
typedef mt_vector<INFINITY_IMPUTE>			mt_vectorInfinityImpute;
typedef vector<INFINITY_IMPUTE>				vectINFINITY_IMPUTE;			// 2010-04-05 by cmkwon, 인피 재입장 카드 관련 시스템 수정 - 

typedef enum
{
	INFINITY_STATE_NONE = 0,
	INFINITY_STATE_UNPREPARED = 1,				// 인피니티 입장은 했지만 래뒤는 누르지 않은 상태
	INFINITY_STATE_READY = 2,				// 인피니티 맵에 입장 전 상태
	INFINITY_STATE_READY_ENTER_CHECK = 3,				// 2010-03-23 by cmkwon, 인피니티 입장 캐쉬 아이템 구현 - MF로부터 Start 인증을 보낸 상태
	INFINITY_STATE_READY_ENTER_CHECKED = 4,				// 2010-03-23 by cmkwon, 인피니티 입장 캐쉬 아이템 구현 - MF로부터 Start 인증을 받은 상태
	INFINITY_STATE_ENTERING = 5,				// 2009-09-09 ~ 2010-01-29 by dhjin, 인피니티 - 인피니티 시작 버튼 누른 상태 추가
	INFINITY_STATE_MAPLOADED = 6,				// 인피니티 맵 로딩 완료
	INFINITY_STATE_PLAYING = 7,				// 인피니티 맵에 입장하여 진행중 상태 
	INFINITY_STATE_DONE_SUCCESS = 8,				// 2010-03-31 by dhjin, 인피니티(기지방어) - // 인피니티 종료 성공 상태
	INFINITY_STATE_DONE_FAIL = 9,				// 2010-03-31 by dhjin, 인피니티(기지방어) - // 인피니티 종료 실패 상태

	// PLAYING_STEP 아닌 경우 여기에 추가하세요

// start 2011-04-08 by hskim, 인피니티 3차 - 시네마 단계별 기능 구현
// [주의] 스텝이 추가될경우 아래 사항 수정해주기
// IS_INFINITY_STATE_PLAYING_LAST/IS_INFINITY_STATE_PLAYING/IS_INFINITY_STATE_PLAYING_STEP/CINEMA_PLAYING_STEP_MAX
// CFieldIOCPSocket::InfinityOnCharacterGameEndRoutine 함수 내 switch 문

INFINITY_STATE_PLAYING_STEP1 = 101,				// 인피니티 3차 스텝 1 - 주포 파괴
INFINITY_STATE_PLAYING_STEP2 = 102,				// 인피니티 3차 스텝 2 - 활주로 파괴
INFINITY_STATE_PLAYING_STEP3 = 103,				// 인피니티 3차 스텝 3 - 격납고 침투
INFINITY_STATE_PLAYING_STEP4 = 104,				// 인피니티 3차 스텝 4 - 레이더 기지 파괴
INFINITY_STATE_PLAYING_STEP5 = 105,				// 인피니티 3차 스텝 5-1	- 엔진실 파괴 1단계 (보호막 파괴)
INFINITY_STATE_PLAYING_STEP6 = 106,				// 인피니티 3차 스텝 5-2	- 엔진실 파괴 2단계 (엔진 파괴)
INFINITY_STATE_PLAYING_STEP7 = 107,				// 인피니티 3차 스텝 5-3	- 연출 (적군 모선 침몰 연출)
INFINITY_STATE_PLAYING_STEP8 = 108,				// 인피니티 3차 스텝 6		- 보너스 스텝 (탈출선 잡기)
INFINITY_STATE_PLAYING_STEP9 = 109				// 인피니티 3차 스텝 7		- 종료 처리
// end 2011-04-08 by hskim, 인피니티 3차 - 시네마 단계별 기능 구현
} eINFINITY_STATE;

// start 2011-04-11 by hskim, 인피니티 3차 - 시네마 단계별 기능 구현
#define IS_INFINITY_STATE_PLAYING_LAST(_IT_)		(INFINITY_STATE_PLAYING_STEP9 == (_IT_))		// 마지막 스텝은 누구? - 꼭 설정해주기
#define IS_INFINITY_STATE_PLAYING(_IT_)		(INFINITY_STATE_PLAYING == (_IT_) || INFINITY_STATE_PLAYING_STEP1 == (_IT_) ||	\
											INFINITY_STATE_PLAYING_STEP2 == (_IT_) || INFINITY_STATE_PLAYING_STEP3 == (_IT_) ||		\
											INFINITY_STATE_PLAYING_STEP4 == (_IT_) || INFINITY_STATE_PLAYING_STEP5 == (_IT_) ||		\
											INFINITY_STATE_PLAYING_STEP6 == (_IT_) || INFINITY_STATE_PLAYING_STEP7 == (_IT_) ||	\
											INFINITY_STATE_PLAYING_STEP8 == (_IT_) || INFINITY_STATE_PLAYING_STEP9 == (_IT_))

#define IS_INFINITY_STATE_PLAYING_STEP(_IT_)		( INFINITY_STATE_PLAYING_STEP1 == (_IT_) ||	INFINITY_STATE_PLAYING_STEP2 == (_IT_) ||	\
													INFINITY_STATE_PLAYING_STEP3 == (_IT_) || INFINITY_STATE_PLAYING_STEP4 == (_IT_) ||	\
													INFINITY_STATE_PLAYING_STEP5 == (_IT_) || INFINITY_STATE_PLAYING_STEP6 == (_IT_) || \
													INFINITY_STATE_PLAYING_STEP7 == (_IT_) || INFINITY_STATE_PLAYING_STEP8 == (_IT_) || \
													INFINITY_STATE_PLAYING_STEP9 == (_IT_))
// end 2011-04-11 by hskim, 인피니티 3차 - 시네마 단계별 기능 구현


struct INFINITY_PLAYING_INFO {
	InfinityCreateUID_t InfinityCreateUID;
	InfiModeUID_t		InfinityModeUID;
	MapIndex_t			MapIdx;
	eINFINITY_MODE		ModeTypeNum;
	eINFINITY_STATE		InfinityState;
	Lv_t				RevisionLevel;
	RevisionHP_t		RevisionHP;
	RevisionDP_t		RevisionDP;
	RevisionWeapon1_t	RevisionStandardWeapon;
	RevisionWeapon2_t	RevisionAdvancedWeapon;
	KillCnt_t			KillCount;
	DeathCnt_t			DeathCount;
	Minute_t			TimePenaltyValue;			// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 인피 사망시 패널티 추가
	BOOL				bHaveReentryTicket;			// 2010-03-23 by cmkwon, 인피니티 입장 캐쉬 아이템 구현 - 해당 아이템을 소유하기 있는지 여부
	Penalty_t			HPPenaltyValue;				// 2011-06-14 by hskim, 인피니티 3차 - 패널티 기능 추가 (HP 및 시간 동시 지원을 위해)
};

#define INFINITY_CREATE_MAP_CHANNEL_IDX_ERROR	-1

struct INFINITY_INSERT_ITEM_INFO {
	UID64_t			ItemUID;
	INT				ItemNum;
	INT				ItemWindowIndex;
	INT				CurrentCount;
	INT				PrefixCodeNum;
	INT				SuffixCodeNum;
	BYTE			Wear;
	INT				ShapeItemNum;
	INT				UsingTimeStamp;
	ATUM_DATE_TIME	CreatedTime;
	INT				CoolingTimeStamp;		// 2009-09-09 ~ 2010-02-10 by dhjin, 인피니티 - 발동류장착아이템
};
typedef mt_vector<INFINITY_INSERT_ITEM_INFO>			mtvectorInfinityInsertItemInfo;

struct INFINITY_UPDATE_ITEM_INFO {
	UID64_t			ItemUID;
	UID64_t			MainSvrItemUID;
	INT				ItemWindowIndex;
	INT				CurrentCount;
	BYTE			Wear;
	INT				UsingTimeStamp;
	INT				CoolingTimeStamp;		// 2009-09-09 ~ 2010-02-10 by dhjin, 인피니티 - 발동류장착아이템
};
typedef mt_vector<INFINITY_UPDATE_ITEM_INFO>			mtvectorInfinityUpdateItemInfo;

struct INFINITY_DELETE_ITEM_INFO {
	UID64_t			MainSvrItemUID;
};
typedef mt_vector<INFINITY_DELETE_ITEM_INFO>			mtvectorInfinityDeleteItemInfo;


///////////////////////////////////////////////////////////////////////////////
// 2009-12-11 by cmkwon, 데미지 어그로로 타겟을 변경하는 몬스터 구현 - 
#define TICK_MONSTER_TARGET_UNCHANGE_TERM			15000			// 15초간 타겟 유지
#define TICK_MONSTER_DELETE_TARGET_TERM				15000			// 2010-03-02 by cmkwon, 몬스터 타겟 삭제 체크 15초로 변경 - // 몬스터가 30초간 공격하지 못한 타겟은 삭제한다.

struct TENDER_INFO {
	TenderUID_t		TenderUID;
	ItemNum_t		TenderItemNum;
};
typedef vector<TENDER_INFO>								vectorTenderInfo;


#define MAX_DICE_COUNT						100
#define MIN_DICE_COUNT						1
#define EXIT_DICE_COUNT						100		// 2009-09-09 ~ 2010-01 by dhjin, 인피니티 - 소스 체크, 무한 루프 대비용

///////////////////////////////////////////////////////////////////////////////
// 2009-12-29 by cmkwon, 캐릭터 최대 레벨 상향(110으로) - 1~100~110
#define CHARACTER_LEVEL_100					100
#define CHARACTER_LEVEL_100_MAX_STAT_POINT	300
#define CHARACTER_LEVEL_110					125/*110*/
#define CHARACTER_LEVEL_110_MAX_STAT_POINT	340

// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 
#define GET_MAX_STAT_POINT(level)			( ((level) <= CHARACTER_LEVEL_100) ? CHARACTER_LEVEL_100_MAX_STAT_POINT : CHARACTER_LEVEL_110_MAX_STAT_POINT)

// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 인피 상점
struct INFINITY_SHOP_INFO {
	InfinityShopUID_t		InfinityShopUID;
	ItemNum_t				BuyItemNum;
	InfinityShopItemCnt_t	BuyItemCount;
	ItemNum_t				TradeItemNum1;
	InfinityShopItemCnt_t	TradeItemCount1;
	ItemNum_t				TradeItemNum2;
	InfinityShopItemCnt_t	TradeItemCount2;
	ItemNum_t				TradeItemNum3;
	InfinityShopItemCnt_t	TradeItemCount3;
	ItemNum_t				TradeItemNum4;
	InfinityShopItemCnt_t	TradeItemCount4;
	ItemNum_t				TradeItemNum5;
	InfinityShopItemCnt_t	TradeItemCount5;
};
typedef vector<INFINITY_SHOP_INFO>						vectorInfinityShopInfo;


///////////////////////////////////////////////////////////////////////////////
// 2010-01-18 by cmkwon, 아이템 사용시 Parameter 중복 체크 시스템 구현 - 
struct SITEM_PARAM_OVERLAP
{
	INT			ItemNum;
	INT			OverlapIndex;		// 같은 OverlapIndex가 있으면 사용 불가
};
typedef vector<SITEM_PARAM_OVERLAP>		vectSITEM_PARAM_OVERLAP;	// 
typedef ez_map<INT, vectINT>			ezmapINT2vectINT;			// ITEMNUM and OverlapIndexVector

///////////////////////////////////////////////////////////////////////////////
// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 팅긴 유저 재접속 처리
struct INFINITY_DISCONNECTUSER_INFO {
	char					CharacterName[SIZE_MAX_CHARACTER_NAME];
	InfinityCreateUID_t		InfinityCreateUID;		// 해당 방의 고유 번호
	USHORT					MainServerID;			// 입장한 캐릭터의 서버
	eINFINITY_MODE			InfinityMode;
};
typedef mt_vector<INFINITY_DISCONNECTUSER_INFO>		mtvectorInfinityDisConnectUser;

///////////////////////////////////////////////////////////////////////////////
// 2009-09-09 ~ 2010-02-10 by dhjin, 인피니티 - 발동류장착아이템
struct INVOKING_ITEM_DESTPARAM_TYPE {
	ItemUID_t				InvokingItemUID;
	DestParam_t				InvokingDestParam;
	ParamValue_t			InvokingDestParamValue;
	EffectIdx_t				InvokingEffectIdx;
};
typedef vector<INVOKING_ITEM_DESTPARAM_TYPE>		InvokingItemDestParamTypeList;
typedef mt_vector<INVOKING_ITEM_DESTPARAM_TYPE>		mtInvokingItemDestParamTypeList;

///////////////////////////////////////////////////////////////////////////////
// 2010-03-31 by dhjin, 인피니티(기지방어) - CINEMA_FIN_XXX
#define CINEMA_FIN_SUCCESS				51000
#define CINEMA_FIN_FAIL					52000
#define PENALTY_REMAIN_HP				100

// start 2011-04-08 by hskim, 인피니티 3차 - 시네마 단계별 기능 구현
#define CINEMA_PLAYING_STEP_MAX			9			// 최대 지원하는 Playing Step 수 - 최대 수 변경시 eINFINITY_STATE / IS_INFINITY_STATE_PLAYING 수정할 것

#define CINEMA_PLAYING_STEP_START_NUMBER			10001		// PLAYING 스텝 시작 번호	- STEP1 = 10001,	STEP2 = 10002,	STEP3 = 10003,	STEP4 = 10004,	STEP5 = 10005,	STEP6 = 10006, STEP7 = 10007, STEP8 = 10008
// end 2011-04-08 by hskim, 인피니티 3차 - 시네마 단계별 기능 구현

// 2010-04-07 by cmkwon, 인피2차 추가 수정 - 
typedef enum
{
	INFINITY_FIN_UNKNOWN = 0,		// 알 수 없음
	INFINITY_FIN_SUCCESS_BY_PASS_ALL_STEP = 100,		// 성공: 모든 단계(Step)을 통과
	INFINITY_FIN_SUCCESS_BY_TIMEOVER,					// 성공: 제한 시간 경과
	INFINITY_FIN_SUCCESS_BY_DEAD_ALL_KEY_MONSTER_FOR_NEXTSTEP,	// 2010-04-09 by cmkwon, 인피2차(성공 조건 추가) - MPOPTION_BIT_KEY_MONSTER를 설정한 몬스터가 모두 제거됨
	INFINITY_FIN_FAIL_BY_TIMEOVER = 200,		// 실패: 세한 시간 경과
	INFINITY_FIN_FAIL_BY_DEAD_KEYMONSTER				// 실패: 키몬스터 파괴됨
} INFINITY_FIN_t;


///////////////////////////////////////////////////////////////////////////////
// 2010-04-20 by cmkwon, 신규 러키 머신 구현 - 기존 소스 수정 - LUCKY_MACHINE_KIND_XXX, LUCKY_MACHINE_XXX
#define LUCKY_MACHINE_KIND_UNKNOWN				0		// 알수 없음
#define LUCKY_MACHINE_KIND_HAPPY_MACHINE		1		// 해피머신
#define LUCKY_MACHINE_KIND_WEAPON_MACHINE		2		// 무기머신
#define LUCKY_MACHINE_KIND_ARMOR_MACHINE		3		// 아머머신

// 2010-06-01 by shcho, GLogDB 관련 -
struct MOSTSTAYED_MAP_INFO
{
	MapIndex_t  MapIndex;	 // 머무른 맵 인덱스
	DWORD		StayedTime;	 // 머물렀던 총 누적시간
};

// 2010-08-05 by dhjin, 버닝맵 - 
typedef INT		BurningMapUID_t;
typedef	USHORT	UnitKind_t;
struct BURNING_MAP_INFO {
	BurningMapUID_t		BurningMapUID;
	MapIndex_t			MapIndex;
	UnitKind_t			ReqUnitKind;
	Lv_t				ReqMinLv;
	Lv_t				ReqMaxLv;
};
typedef vector<BURNING_MAP_INFO>	BurningMapInfoList;

// 2010-06-15 by shcho&hslee 펫시스템
#define SIZE_MAX_PETSKILLITEM 6			// 펫의 스킬 아이템 개수.
#define SIZE_MAX_PETSOCKETITEM 6		// 펫의 소켓 슬롯 개수.

typedef struct
{	// 펫의 기본 정보.

	char	szPetName[SIZE_MAX_PET_NAME];

	INT		UniqueNumber;
	INT		PetIndex;
	INT		PetKind;
	BOOL	EnableName;
	BOOL	EnableLevel;

} tPET_BASEDATA;

typedef std::vector< tPET_BASEDATA > vectorPetBaseData;

typedef struct
{	// 펫 레벨업 관련 정보.

	INT				UniqueNumber;
	INT				Level;
	Experience_t	NeedExp;
	DOUBLE			Stamina;
	INT				CitySourceIndex;
	INT				FieldSourceIndex;
	INT				PetAttackIndex; // 2010-06-15 by shcho&hslee 펫시스템 - 펫 공격 처리 총알 인덱스 필드 추가

	INT				PetSkillItemIndex[SIZE_MAX_PETSKILLITEM];

} tPET_LEVEL_DATA;

typedef std::vector< tPET_LEVEL_DATA > vectorPetLevelData;

struct tPET_BASE_ALL_DATA
{
	tPET_BASEDATA		BaseData;
	vectorPetLevelData  vectPetLevelDataInfo;

	tPET_LEVEL_DATA* rtn_LevelData(const int a_iLevel)
	{
		for (unsigned ui = 0; ui < this->vectPetLevelDataInfo.size(); ++ui)
		{
			if (this->vectPetLevelDataInfo[ui].Level == a_iLevel)
				return &this->vectPetLevelDataInfo[ui];
		}
		return NULL;
	}

};

typedef std::vector< tPET_BASE_ALL_DATA > vectorPetDataInfo;

struct tPET_CURRENTINFO
{	// 소유한 펫 정보.

	UID64_t			CreatedPetUID;

	BOOL			EnableEditPetName;
	BOOL			EnableLevelUp;

	char			szPetName[SIZE_MAX_PET_NAME];

	INT				PetIndex;
	INT				PetLevel;

	Experience_t	PetExp;

	DOUBLE			Stamina;

	INT				SourceIndex_Field;
	INT				SourceIndex_City;

	const ITEM* pItem_PetSkill[SIZE_MAX_PETSKILLITEM];
	const ITEM* pItem_PetSocketItem[SIZE_MAX_PETSOCKETITEM];

#ifdef _ATUM_SERVER

	tPET_CURRENTINFO(tPET_CURRENTINFO* pPetCurInfo)
	{
		if (pPetCurInfo)
			memcpy(this, pPetCurInfo, sizeof(tPET_CURRENTINFO));
		else
			memset(this, 0x00, sizeof(tPET_CURRENTINFO));
	}

	void* operator new(size_t size);
	void operator delete(void* p);
#endif

};

typedef std::vector		< tPET_CURRENTINFO* > vecPetCurrentInfo;

typedef mt_vector		< tPET_CURRENTINFO* > mtvectPetCurrentInfo;
// End 2010-06-15 by shcho&hslee 펫시스템

// 2010-06-15 by shcho&hslee 펫시스템 - 오퍼레이터 정보

struct OperatorInfo
{	// 오퍼레이터 정보.
	int		ActionType;
	int		Itemnum;
	int		FunctionIndex;
	double	FunctionValue;
	int		SourceIndex;
	char	ActionDesc[128];
};

typedef std::vector< OperatorInfo > vectorOperatorInfo;

// END 2010-06-15 by shcho&hslee 펫시스템 - 오퍼레이터 정보

// 2010-08-31 by shcho&jskim 아이템용해 시스템 - 용해 아이템 정보 구조체 

#define SIZE_MAX_DISSOLUTION_ITEMS	3

struct tDissolutionItemInfo
{
	INT		SourceItemnum;				// 용해 할 아이템 번호
	INT		ResultItemNum[SIZE_MAX_DISSOLUTION_ITEMS];			// 결과 아이템 번호
	INT		ResultItemMinCount[SIZE_MAX_DISSOLUTION_ITEMS];		// 아이템 최소 갯수
	INT		ResultItemMaxCount[SIZE_MAX_DISSOLUTION_ITEMS];		// 아이템 최대 갯수
	INT		ResultItemProbabillity[SIZE_MAX_DISSOLUTION_ITEMS];	// 아이템 나올 확률
};

struct DissolutionItems
{
	INT Itemnum[SIZE_MAX_DISSOLUTION_ITEMS];
	INT Itemcount[SIZE_MAX_DISSOLUTION_ITEMS];
};

typedef std::vector<tDissolutionItemInfo> vectorDissolutionItemInfo; // 툴에서 사용
typedef mt_map<INT, tDissolutionItemInfo> mtmapDissolutionItemInfo; // 맵에 저장

// END 2010-08-31 by shcho&jskim 아이템용해 시스템 - 용해 아이템 정보 구조체 

// start 2011-03-17 by hskim, 인피니티 3차 - 몬스터 멀티 타겟팅 기능 추가

// 2011-03-18 by hskim, 인피니티 3차 - 작업중 클라와 서버 공통된 자료형 통합
typedef enum
{
	DB_ITEM,
	DB_MONSTER_INFO,
	DB_MAPOBJECT,
	DB_RARE_ITEM,
	DB_BUILDINGNPC,
	DB_GUILD_MARK,
	DB_MAP_INFO,
	DB_MIXING_INFO,
	DB_MYSTERY_ITEM_DROP,
	// 2009-03-04 by bhsohn 럭키 머신 수정안
	DB_LUCKYMACHINE,
	// end 2009-03-04 by bhsohn 럭키 머신 수정안
	// 2010. 02. 11 by ckPark 발동류 장착아이템
	DB_INVOKINGWEARITEM_DPNUM,			// 2009-09-09 ~ 2010-02-10 by dhjin, 인피니티 - 발동류장착아이템
	DB_INVOKINGWEARITEM_DPNUM_BY_USE,	// 2009-09-09 ~ 2010-02-10 by dhjin, 인피니티 - 발동류장착아이템
	// end 2010. 02. 11 by ckPark 발동류 장착아이템

	// 2010-08-10 by dgwoo 버닝맵 시스템
	DB_BURNING_MAP,
	// 2010-08-10 by dgwoo 버닝맵 시스템

	// 2010-06-15 by shcho&hslee 펫시스템
	DB_PET_BASEDATA,						// 2010-06-15 by shcho&hslee 펫시스템 - 펫 기본 정보.
	DB_PET_LEVELDATA,						// 2010-06-15 by shcho&hslee 펫시스템 - 펫 레벨업 관련정보.
	DB_PET_OPERATOR,						// 2010-06-15 by shcho&hslee 펫시스템 - 오퍼레이터 정보
	// End 2010-06-15 by shcho&hslee 펫시스템
	DB_DISSOLUTIONITEM,					// 2010-08-31 by shcho&&jskim, 용해 시스템 구현
	DB_MONSTER_MULTI_TARGET					// 2011-03-17 by hskim, 인피니티 3차 - 몬스터 멀티 타겟팅 기능 추가

} DB_TYPE;

// 2011. 03. 08 by jskim 인피3차 구현
struct DATA_HEADER
{
	DB_TYPE nType;
	int nDataCount;
};
// end 2011. 03. 08 by jskim 인피3차 구현

///////////////////////////////////////////////////////////////////////////////
// MonsterMultiTarget - Parameter Struct 정의
// 2011-03-17 by hskim, 인피티티 3차 몬스터 멀티 타겟팅 기능 추가
///////////////////////////////////////////////////////////////////////////////
struct MONSTER_MULTI_TARGET
{
	INT			MonsterIndex;						// 몬스터 고유 번호
	INT			PointIndex;							// 추가된 몬스터 타겟의 번호
	D3DXVECTOR3	TargetPosition;						// 추가된 실제 좌표 (x,y,z)
};
typedef std::vector<MONSTER_MULTI_TARGET>	vectorMonsterMultiTarget;
typedef std::vector<MONSTER_MULTI_TARGET>::iterator vectoritMonsterMultiTarget;
// end 2011-03-17 by hskim, 인피니티 3차 - 몬스터 멀티 타겟팅 기능 추가

// 2010-11 by dhjin, 아라리오 채널링 로그인.
typedef enum
{
	CONNECT_PUBLISHER_DEFAULT = 0,
	CONNECT_PUBLISHER_NHN_JPN = 1
} eCONNECT_PUBLISHER;

char* GetConnectPublisherName(eCONNECT_PUBLISHER i_eCONNECT_PUBLISHER);

// start 2011-05-17 by hskim, 인피니티 3차 - 시네마 연출
///////////////////////////////////////////////////////////////////////////////
// 시네마(DB:account, ti_Cinema) 커스텀 인덱스(CustomIdx) 정의
// 2011-05-17 by hskim, 인피니티 3차 - 시네마 연출
//
// 시네마에서 범용적으로 사용하지 않을 기능은 여기에 추가 구현한다.
///////////////////////////////////////////////////////////////////////////////
enum
{
	INFINITY3_STEP5_MOVIE_START = 1,		// 인피니티 3차 - 스텝 5 - 적군 모선 침몰 연출 시작
	INFINITY3_STEP5_MOVIE_END = 2,		// 인피니티 3차 - 스텝 5 - 적군 모선 침몰 연출 종료
	INFINITY3_STEP5_TIMELIMIT_SET = 3,		// 인피니티 3차 - 스텝 6 - 모선 탈출 시간 재설정
	INFINITY3_STEP6_MOVE_SUCCESS_POSITION = 4,		// 인피니티 3차 - 스텝 7 - 캐릭터 위치 이동 (성공) - 시네마 파일 제작시 삭제 예정
	INFINITY3_STEP6_MOVE_FAIL_POSITION = 5,		// 인피니티 3차 - 스텝 7 - 캐릭터 위치 이동 (실패) - 시네마 파일 제작시 삭제 예정
	INFINITY3_FAIL_MOVIE_START = 6			// 인피니티 3차 - 실패시 - 아군 모선 침몰 연출 시작
};


///////////////////////////////////////////////////////////////////////////////
// MSG_FC_INFINITY_MOVIE 메시지 연출 번호(UniqueNumber) 정의
// 2011-05-17 by hskim, 인피니티 3차 - 시네마 연출
///////////////////////////////////////////////////////////////////////////////
enum
{
	INFINITY_MOVIE_001_INF3_STEP5 = 1,		// 인피니티 3차 - 적군 모선 침몰 연출
	INFINITY_MOVIE_002_INF3_FAIL = 2			// 인피니티 3차 - 아군 모선 침몰 연출
};

///////////////////////////////////////////////
// MSG_FC_INFINITY_MOVIE 메시지 Command 정의
enum
{
	MOVIE_COMMAND_START = 1,		// 연출 시작
	MOVIE_COMMAND_END = 2			// 연출 종료
};
// end 2011-05-17 by hskim, 인피니티 3차 - 시네마 연출

///////////////////////////////////////////////////////////////////////////////
// WayPoint 관련 - Parameter Struct 및 Define 정의
// 2011-05-23 by hskim, 인피니티 3차 - 웨이포인트 구현
///////////////////////////////////////////////////////////////////////////////

// SWAY_POINT.byPostionAttribute 속성
#define WAY_POINT_POSITION_ATTRIBUTE_RELATIVE			0			// 상대 좌표						- 추후 개발
#define WAY_POINT_POSITION_ATTRIBUTE_ABSOLUTE			1			// 절대 좌표		- 기능 개발

// CWayPointPattern.m_byCompletionAction 속성
#define WAY_POINT_COMPLETION_ACTION_REPEAT				0			// 반복
#define WAY_POINT_COMPLETION_ACTION_RECIPROCATION		1			// 왕복
#define WAY_POINT_COMPLETION_ACTION_STOP				2			// 정지

#define WAY_POINT_COLLISION_THRESHOLD					2000.0f		// WAY_POINT 도착 판정용 Threshold 값

struct SWAY_POINT
{
	UINT dwPatternIndex;				// 패턴 번호
	UINT dwSequenceNum;					// 웨이포인트 순서
	BYTE byPostionAttribute;			// 속성				(절대 좌표, 상대 좌표)								/ 구현 사항 : 절대 좌표
	D3DXVECTOR3 vPoint;					// 좌표

	SWAY_POINT()
	{
		dwPatternIndex = 0;
		dwSequenceNum = 0;
		byPostionAttribute = WAY_POINT_POSITION_ATTRIBUTE_RELATIVE;
		vPoint = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	SWAY_POINT(UINT i_dwPatternNum, UINT i_dwSequenceNum, BYTE i_byPostionAttribute, D3DXVECTOR3 i_vPoint)
	{
		dwPatternIndex = i_dwPatternNum;
		dwSequenceNum = i_dwSequenceNum;
		byPostionAttribute = i_byPostionAttribute;
		vPoint = i_vPoint;
	}
};

struct SWAY_POINT_MOVE
{
	UINT dwIndex;						// 패턴 번호
	BYTE byCompletionAction;			// 완료 후 동작		(반복, 왕복, 정지)
};

typedef vector<SWAY_POINT>	vectorWayPoint;
typedef vector<SWAY_POINT_MOVE>	vectorWayPointMove;


// end 2011-05-23 by hskim, 인피니티 3차 - 웨이포인트 구현

// start 2011-05-30 by hskim, 인피니티 3차 - 플레이 시간 재설정 기능
#define INFINITY3_STEP6_TIMELIMIT_VALUE			60000		// (1 min * 60 sec * 1000 ms)
// end 2011-05-30 by hskim, 인피니티 3차 - 플레이 시간 재설정 기능

// start 2011-06-01 인피니티 3차 - 스텝 7 - 캐릭터 위치 이동
#define INFINITY3_STEP6_MOVE_SUCCESS_POSTION_X			500.0f
#define INFINITY3_STEP6_MOVE_SUCCESS_POSTION_Y			2500.0f
#define INFINITY3_STEP6_MOVE_SUCCESS_POSTION_Z			3500.0f

#define INFINITY3_STEP6_MOVE_FAIL_POSTION_X				9800.0f
#define INFINITY3_STEP6_MOVE_FAIL_POSTION_Y				3500.0f
#define INFINITY3_STEP6_MOVE_FAIL_POSTION_Z				5000.0f
// end 2011-06-01 인피니티 3차 - 스텝 7 - 캐릭터 위치 이동

// start 2011-07-15 by shcho - 캐쉬아이템 체크 시스템 구현
struct cashItemCheckData
{
	int ItemNumber;
	int	Price;
	int	CashPrice;
	int	Time;
	int ItemAttribute;
	int UniqueNumber;
};

typedef vector<cashItemCheckData> vectCashCheckData;

#define OLD_DATA	0
#define NEW_DATA	1
// end 2011-07-15 by shcho - 캐쉬아이템 체크 시스템 구현

// START 2011-11-03 by shcho, yedang 셧다운제 구현 - 셧다운제에 체크될 나이
struct ShutdownUserData
{ // 추가되 정보가 있으므로 일단 만들어 두자
	UID32_t			Account_UniqueNumber;
	UID32_t			CharacterUniqueNumber[3];
};
typedef vector<ShutdownUserData> vectShutDownUserData;

#define SHUTDOWNMINORS_YEARS_OLD	16
// END 2011-11-03 by shcho, yedang 셧다운제 구현 - 셧다운제에 체크될 나이


#endif
