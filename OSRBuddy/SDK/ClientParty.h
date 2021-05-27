#pragma once
// ClientParty.h: interface for the CClientParty class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENTPARTY_H__DB818FDB_228D_4091_B3DF_73DF6410F56E__INCLUDED_)
#define AFX_CLIENTPARTY_H__DB818FDB_228D_4091_B3DF_73DF6410F56E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AtumParam.h"
#include "SDK/ObjectDefine.h"
#include "AtumProtocol.h"


class CEnemyData;

/*
typedef struct _IM_PARTY_MEMBER_INFO
{
	UID32_t		CharacterUniqueNumber;
	char		CharacterName[SIZE_MAX_CHARACTER_NAME];
	BYTE		PilotFace;
	USHORT		UnitKind;
	USHORT		Race;
	BYTE		Level;
	//char		MapName[SIZE_MAX_MAP_NAME];	// IS_VALID_MAP_NAME()이 FALSE이면, 파티 소속이나 게임중이 아닌 캐릭임(죽어서 나간 캐릭터 등)
	MAP_CHANNEL_INDEX	MapChannelIndex;	// IsValid()이 FALSE이면, 파티 소속이나 게임중이 아닌 캐릭임(죽어서 나간 캐릭터 등)
	EN_CHECK_TYPE	VoipType;		// 2008-07-16 by dhjin, EP3 - Voip 정보	 
} IM_PARTY_MEMBER_INFO;
  */

// 2009. 09. 21 by ckPark 인피니티 필드 몬스터 스킬 구현
struct sDebuffDotInfo
{
	INT		nSkillItemNum;	// 적용된 도트, 디버프 아이템 넘버
	INT		nSourceIndex;	// 도트, 디버프 소스 인덱스

	sDebuffDotInfo(ITEM* pSkillItem)
	{
		nSkillItemNum = pSkillItem->ItemNum;
		nSourceIndex = SKILL_BASE_NUM(pSkillItem->SourceIndex);
	}
};
// end 2009. 09. 21 by ckPark 인피니티 필드 몬스터 스킬 구현

typedef struct
{
	LONGLONG		m_nUniqueNumber;		// 편대원의 UniqueNumber
	PARTY_TYPE		m_bPartyType;
	BOOL			m_bFormationFlight;		// 편대 비행중인 파티원인가?
	BYTE			m_bFormationFlyingType;
	BYTE			m_bFormationFlyingPositionType;
	IM_PARTY_MEMBER_INFO m_ImPartyMemberInfo;
	CEnemyData* m_pEnemyData;
	BOOL			m_bSpeakingRender;
	EN_CHECK_TYPE	VoipType;
	BOOL			m_bSpeakingAuth;		// 말하기 권한	// 2008-10-14 by bhsohn VOIP개선
	BOOL			m_bUserLogOn;		// 2008-12-02 by bhsohn 편대원 온오프라인 상태체크

	// 2009. 09. 21 by ckPark 인피니티 필드 몬스터 스킬 구현
	std::vector<sDebuffDotInfo> m_vecDebuffDotInfo;
	// end 2009. 09. 21 by ckPark 인피니티 필드 몬스터 스킬 구현
} PARTYENEMYINFO;

/*
struct PEER_PARTY_MEMBER
{
	ClientIndex_t	ClientIndex;
	UID32_t			CharacterUniqueNumber;
};
*/

typedef struct
{
	LONGLONG		m_nUniqueNumber;
	D3DXVECTOR3		m_vPos;
	D3DXVECTOR3		m_vVel;
	D3DXVECTOR3		m_vSide;
	D3DXVECTOR3		m_vUp;
} MASTERINFO;

typedef struct
{
	ClientIndex_t	ClientIndex;
	UID32_t			CharacterUniqueNumber;
} OTHERPARTYINFO;

class CClientParty
{
public:
	CClientParty();
	virtual ~CClientParty();

public:
	vector<PARTYENEMYINFO*>		m_vecPartyEnemyInfo;		// 나와 편대중인 EnemyList
	vector<PEER_PARTY_MEMBER>	m_vecPeerPartyEnemyInfo;	// 우리 편대와 전투중인 다른 파티원 List

	BOOL		m_bParty;								// 내가 파티중인가?
	BOOL		m_bFormationFlight;						// 내가 편대비행중인가?
	PARTYINFO	m_infoParty;							// 나의 파티정보
	MASTERINFO	m_infoMaster;							// 편대 마스터 정보
	BOOL		m_bNtoNCallState;						// 편대 통화 중?

	// 2008-06-03 by bhsohn EP3 편대 관련 처리
	SPARTY_INFO			m_stPartyInfo;

	int				m_nOldFormationFlyingType;
	BOOL			m_bFirstPartySetupInfo;

	// 2008-10-20 by bhsohn VOIP 버그 수정
	BOOL			m_bMyShuttleSpeakingAuth;	// 내가 말하고 있는지 여부
	EN_CHECK_TYPE	m_VoipTypeMyShuttle;

	// 2008-12-16 by dgwoo 미션마스터 임시 파티 번호.
	PartyID_t		m_nTempMMasterPartyID;
};

#endif // !defined(AFX_CLIENTPARTY_H__DB818FDB_228D_4091_B3DF_73DF6410F56E__INCLUDED_)
