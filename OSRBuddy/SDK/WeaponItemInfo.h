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
	vector<CWeaponMineData*>	m_vecMine;					// 현재 발사된 마인
	int							m_nMaxMineNumber;			// 최대 마인 숫자
};
// 2006-02-01 by ispark, 타겟 거리 비교해서 타겟 정렬 리스트

// 2011. 03. 08 by jskim 인피3차 구현 - 넌 타겟 시스템
struct TARGET_DATA
{
	int nTargetIndex;
	int nTargetMultiIndex;
};
// end 2011. 03. 08 by jskim 인피3차 구현 - 넌 타겟 시스템

struct stTargetList
{
	int		nTargetIndex;
	float	fTargetLength;
	// 2011. 03. 08 by jskim 인피3차 구현
	int		nMultiIndex;
	// end 2011. 03. 08 by jskim 인피3차 구현

	stTargetList()
	{
		nTargetIndex = 0;
		fTargetLength = 0.0f;
		// 2011. 03. 08 by jskim 인피3차 구현
		nMultiIndex = 0;
		// end 2011. 03. 08 by jskim 인피3차 구현
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
/// \brief		장착 무기에 대한 사용
/// \author		dhkwon
/// \version	
/// \date		2004-07-20 ~ 2004-07-20
/// \warning	ShuttleChild만 뽑는다. UnitData는 안뽑는다.
///////////////////////////////////////////////////////////////////////////////
class CWeaponItemInfo
{
public:
	CWeaponItemInfo(CItemInfo* pItemInfo, CParamFactor* pParamFactor, float fOverHeatTime = 0, BOOL bOverHeat = FALSE);
	virtual ~CWeaponItemInfo();	  

public:
	// 2011. 03. 08 by jskim 인피3차 구현 - 넌 타겟 시스템
	//vector<INT>		m_vecTargetIndex;				// ClientIndex : 10000>=0 ? monster : enemy
	vector<TARGET_DATA>		m_vecTargetIndexData;				// ClientIndex : 10000>=0 ? monster : enemy
	// end 2011. 03. 08 by jskim 인피3차 구현 - 넌 타겟 시스템
	MINE_DATA* m_pMineData;		
	CItemInfo* m_pItemInfo;
	CParamFactor* m_pCharacterParamFactor;		// 캐릭터의 ParamFactor

	BOOL			m_bOverHeat;//m_bWeaponAction;				// 과열 상태
	FLOAT			m_fOverHeatCheckTime;//m_fWeaponActionCheckTime;	// 과열 체크 타임
	FLOAT			m_fReattackCheckTime;//m_fWeaponRACheckTime;		// 리어택 체크 타임
	FLOAT			m_fPrepareCheckTime;			// 발동 준비 체크 타임
	FLOAT			m_fAttackCheckTime;				// 공격 시간 체크 타임
	int				m_nAttackCount;					// 공격 가능한 총알 수
	BYTE			m_nAttackMode;					// 공격 타입(0 : 공중 공격 모드  1 : 지상 공격 모드)


	DWORD			m_dwLastAttackTick;
	//	BYTE			m_nServerSyncShotNum;			// 총알의 싱크를 맞추기위해 서버로 부터 확인 통보를 받고 발사하게 된다.
	vector<int>		m_vecSoundCheck;				// 2형 무기 사운드 체크용
	BOOL			m_bUseToggleWeapon;				// 2-2형 토글형 무기의 사용 여부
//	float			m_fAutoSyncReattackOkTime;		// 시간이 지나면 자동으로 reattacktime * 2 만큼 세팅

	vector<stTargetList> m_vecTargetOrderList;		// 타겟 거리순 리스트

	// 2007-05-16 by bhsohn 1형무기 타켓 처리
	deque<stTargetList> m_vecTmpTargetOrderList;		// 1형무기 정렬을 위한 임시 버퍼
};

#endif // !defined(AFX_WEAPONITEMINFO_H__103FED3F_02AF_4D41_9EC6_B76719B779E3__INCLUDED_)
