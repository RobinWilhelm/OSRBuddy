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
	//char		MapName[SIZE_MAX_MAP_NAME];	// IS_VALID_MAP_NAME()�� FALSE�̸�, ��Ƽ �Ҽ��̳� �������� �ƴ� ĳ����(�׾ ���� ĳ���� ��)
	MAP_CHANNEL_INDEX	MapChannelIndex;	// IsValid()�� FALSE�̸�, ��Ƽ �Ҽ��̳� �������� �ƴ� ĳ����(�׾ ���� ĳ���� ��)
	EN_CHECK_TYPE	VoipType;		// 2008-07-16 by dhjin, EP3 - Voip ����	 
} IM_PARTY_MEMBER_INFO;
  */

// 2009. 09. 21 by ckPark ���Ǵ�Ƽ �ʵ� ���� ��ų ����
struct sDebuffDotInfo
{
	INT		nSkillItemNum;	// ����� ��Ʈ, ����� ������ �ѹ�
	INT		nSourceIndex;	// ��Ʈ, ����� �ҽ� �ε���

	sDebuffDotInfo(ITEM* pSkillItem)
	{
		nSkillItemNum = pSkillItem->ItemNum;
		nSourceIndex = SKILL_BASE_NUM(pSkillItem->SourceIndex);
	}
};
// end 2009. 09. 21 by ckPark ���Ǵ�Ƽ �ʵ� ���� ��ų ����

typedef struct
{
	LONGLONG		m_nUniqueNumber;		// ������ UniqueNumber
	PARTY_TYPE		m_bPartyType;
	BOOL			m_bFormationFlight;		// ��� �������� ��Ƽ���ΰ�?
	BYTE			m_bFormationFlyingType;
	BYTE			m_bFormationFlyingPositionType;
	IM_PARTY_MEMBER_INFO m_ImPartyMemberInfo;
	CEnemyData* m_pEnemyData;
	BOOL			m_bSpeakingRender;
	EN_CHECK_TYPE	VoipType;
	BOOL			m_bSpeakingAuth;		// ���ϱ� ����	// 2008-10-14 by bhsohn VOIP����
	BOOL			m_bUserLogOn;		// 2008-12-02 by bhsohn ���� �¿������� ����üũ

	// 2009. 09. 21 by ckPark ���Ǵ�Ƽ �ʵ� ���� ��ų ����
	std::vector<sDebuffDotInfo> m_vecDebuffDotInfo;
	// end 2009. 09. 21 by ckPark ���Ǵ�Ƽ �ʵ� ���� ��ų ����
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
	vector<PARTYENEMYINFO*>		m_vecPartyEnemyInfo;		// ���� ������� EnemyList
	vector<PEER_PARTY_MEMBER>	m_vecPeerPartyEnemyInfo;	// �츮 ���� �������� �ٸ� ��Ƽ�� List

	BOOL		m_bParty;								// ���� ��Ƽ���ΰ�?
	BOOL		m_bFormationFlight;						// ���� ���������ΰ�?
	PARTYINFO	m_infoParty;							// ���� ��Ƽ����
	MASTERINFO	m_infoMaster;							// ��� ������ ����
	BOOL		m_bNtoNCallState;						// ��� ��ȭ ��?

	// 2008-06-03 by bhsohn EP3 ��� ���� ó��
	SPARTY_INFO			m_stPartyInfo;

	int				m_nOldFormationFlyingType;
	BOOL			m_bFirstPartySetupInfo;

	// 2008-10-20 by bhsohn VOIP ���� ����
	BOOL			m_bMyShuttleSpeakingAuth;	// ���� ���ϰ� �ִ��� ����
	EN_CHECK_TYPE	m_VoipTypeMyShuttle;

	// 2008-12-16 by dgwoo �̼Ǹ����� �ӽ� ��Ƽ ��ȣ.
	PartyID_t		m_nTempMMasterPartyID;
};

#endif // !defined(AFX_CLIENTPARTY_H__DB818FDB_228D_4091_B3DF_73DF6410F56E__INCLUDED_)
