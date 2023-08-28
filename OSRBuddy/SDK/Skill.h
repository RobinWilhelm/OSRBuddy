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
	char				szAttackCharacterName[SIZE_MAX_CHARACTER_NAME];	// ��ų ������� CharacterName;
	UID32_t				AttackCharacterUID;		// ��ų ����� CharacterUID
	UID32_t				TargetCharacterUID;		// ��ų Ÿ�� CharacterUID
	int					UsingSkillItemNum;		// ��� ��ų ItemNum
	MAP_CHANNEL_INDEX	MapChannelIndex;		// ��ų ������� MapChannelIndex
	int					SkillConfirmUseUID;		// 2009-04-06 by cmkwon, �ݿ��� ����� ��ų �ý��� ���� - �ش� ��û�� UID
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

	map<int, CSkillInfo*>	m_mapEnemySkillInfo;		// �ٸ� ����� ����� ��ų(key:ItemNum, value:skill info)
	map<int, CSkillInfo*>	m_mapSkill;					// ��� ������ ��� ��ų (key:ItemNum, value:skill info)

	char _pad01[8];
	vector<CSkillInfo*>		m_vecUsingSkill;			// �� �ڽſ��� ����� ��ų.
	vector<CSkillInfo*>		m_vecEnemyUsingSkillForMe;	// �ٸ� ������ ������ �� ��ų.
	// 2007-04-19 by bhsohn ��ġ���� ������ �߰�
	//D3DXVECTOR3				m_vScanPosition;			// ��ĵ�� �߽� ��ǥ.

	BOOL					m_bSmartSpeed;				// SmartSpeed ��ų�� ������ΰ�?
	// 2009. 09. 21 by ckPark ���Ǵ�Ƽ �ʵ� ���� ��ų ����
	BOOL					m_bMonsterHold;
	// end 2009. 09. 21 by ckPark ���Ǵ�Ƽ �ʵ� ���� ��ų ����
	int						m_nSkillPatternType;		// ���� ������� ���� Ÿ��
	int						m_nChargingShotState;		// ��¡���� ����
	BOOL					m_bScan;					// ���� ��ĵ������ų�� �ް� �ִ� �����ΰ�?
	//float					m_fScanRange;
	CSkillInfo* m_pPriSkillInfo;			// ���� ������� 1������ Skill �� �����ϱ����� �ӽú���
	CSkillInfo* m_pSecSkillInfo;			// ���� ������� 2������ Skill �� �����ϱ����� �ӽú���
	BOOL					m_bSkillTargetState;		// ���� ���콺 ������ Ÿ�� Ŭ�� ����
	ClientIndex_t			m_nTargetIndex;				// Ÿ���� �ִ� ��ų�� ��� TargetIndex;
	UID32_t					m_nCharacterUID;			// Ŭ���̾�Ʈ �ε����� ��ȿ���� ���� �� ����ũ�ѹ��� �Է�
	MSG_FC_SKILL_CONFIRM_USE m_stSkillConfirm;

	// 2007-04-05 by bhsohn ��� ���� ó��
	INT						m_nPreSkillItemNum;			// ����� �õ����� ���

	// 2007-04-19 by bhsohn ��ġ���� ������ �߰�
	INT						m_nScanState;
	D3DXVECTOR3				m_vScanPosition[MAX_SCAN];			// ��ĵ�� �߽� ��ǥ.
	float					m_fScanRange[MAX_SCAN];				// ��ĵ ���� 

	// 2009. 04. 06 by ckPark �ݿ�������ν� �ٸ� Ÿ���� ��ų ������ ����
};

#endif // !defined(AFX_SKILL_H__5A26A431_9BF7_4616_8ADB_BBBEF7A4D820__INCLUDED_)
