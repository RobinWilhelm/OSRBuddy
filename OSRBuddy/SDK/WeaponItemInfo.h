// WeaponItemInfo.h: interface for the CWeaponItemInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WEAPONITEMINFO_H__103FED3F_02AF_4D41_9EC6_B76719B779E3__INCLUDED_)
#define AFX_WEAPONITEMINFO_H__103FED3F_02AF_4D41_9EC6_B76719B779E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ItemInfo.h"

class CItemInfo;
class CWeaponMineData;
class CParamFactor;
class CAtumData;
class CItemData;
class CUnitData;
struct MINE_DATA
{
	vector<CWeaponMineData*>	m_vecMine;					// ���� �߻�� ����
	int							m_nMaxMineNumber;			// �ִ� ���� ����
};
// 2006-02-01 by ispark, Ÿ�� �Ÿ� ���ؼ� Ÿ�� ���� ����Ʈ

// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
struct TARGET_DATA
{
	int nTargetIndex;
	int nTargetMultiIndex;
};
// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���

struct stTargetList
{
	int		nTargetIndex;
	float	fTargetLength;
	// 2011. 03. 08 by jskim ����3�� ����
	int		nMultiIndex;
	// end 2011. 03. 08 by jskim ����3�� ����

	stTargetList()
	{
		nTargetIndex = 0;
		fTargetLength = 0.0f;
		// 2011. 03. 08 by jskim ����3�� ����
		nMultiIndex = 0;
		// end 2011. 03. 08 by jskim ����3�� ����
	}
};

struct sort_List
{
	bool operator()(stTargetList p1, stTargetList p2)
	{
		return p1.fTargetLength < p2.fTargetLength;
	}
};

///////////////////////////////////////////////////////////////////////////////
/// \class		CWeaponItemInfo
///
/// \brief		���� ���⿡ ���� ���
/// \author		dhkwon
/// \version	
/// \date		2004-07-20 ~ 2004-07-20
/// \warning	ShuttleChild�� �̴´�. UnitData�� �Ȼ̴´�.
///////////////////////////////////////////////////////////////////////////////
class CWeaponItemInfo
{
public:
	CWeaponItemInfo(CItemInfo* pItemInfo, CParamFactor* pParamFactor, float fOverHeatTime = 0, BOOL bOverHeat = FALSE);
	virtual ~CWeaponItemInfo();	  

public:
	// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
	//vector<INT>		m_vecTargetIndex;				// ClientIndex : 10000>=0 ? monster : enemy
	vector<TARGET_DATA>		m_vecTargetIndexData;				// ClientIndex : 10000>=0 ? monster : enemy
	// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
	MINE_DATA* m_pMineData;		
	CItemInfo* m_pItemInfo;
	CParamFactor* m_pCharacterParamFactor;		// ĳ������ ParamFactor

	BOOL			m_bOverHeat;//m_bWeaponAction;				// ���� ����
	FLOAT			m_fOverHeatCheckTime;//m_fWeaponActionCheckTime;	// ���� üũ Ÿ��
	FLOAT			m_fReattackCheckTime;//m_fWeaponRACheckTime;		// ������ üũ Ÿ��
	FLOAT			m_fPrepareCheckTime;			// �ߵ� �غ� üũ Ÿ��
	FLOAT			m_fAttackCheckTime;				// ���� �ð� üũ Ÿ��
	int				m_nAttackCount;					// ���� ������ �Ѿ� ��
	BYTE			m_nAttackMode;					// ���� Ÿ��(0 : ���� ���� ���  1 : ���� ���� ���)


	DWORD			m_dwLastAttackTick;
	//	BYTE			m_nServerSyncShotNum;			// �Ѿ��� ��ũ�� ���߱����� ������ ���� Ȯ�� �뺸�� �ް� �߻��ϰ� �ȴ�.
	vector<int>		m_vecSoundCheck;				// 2�� ���� ���� üũ��
	BOOL			m_bUseToggleWeapon;				// 2-2�� ����� ������ ��� ����
//	float			m_fAutoSyncReattackOkTime;		// �ð��� ������ �ڵ����� reattacktime * 2 ��ŭ ����

	vector<stTargetList> m_vecTargetOrderList;		// Ÿ�� �Ÿ��� ����Ʈ

	// 2007-05-16 by bhsohn 1������ Ÿ�� ó��
	deque<stTargetList> m_vecTmpTargetOrderList;		// 1������ ������ ���� �ӽ� ����
};

#endif // !defined(AFX_WEAPONITEMINFO_H__103FED3F_02AF_4D41_9EC6_B76719B779E3__INCLUDED_)
