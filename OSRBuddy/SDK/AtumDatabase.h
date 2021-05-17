#pragma once
// AtumDatabase.h: interface for the CAtumDatabase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ATUMDATABASE_H__3842E2DD_C6C4_4D3B_9CFB_18F7EA62E851__INCLUDED_)
#define AFX_ATUMDATABASE_H__3842E2DD_C6C4_4D3B_9CFB_18F7EA62E851__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000  
// 2011. 03. 08 by jskim 인피3차 구현 - 퀘스트 시스템		
#include "AtumParam.h"

// typedef enum 
// {
// 	DB_ITEM,
// 	DB_MONSTER_INFO,
// 	DB_MAPOBJECT,
// 	DB_RARE_ITEM,
// 	DB_BUILDINGNPC,
// 	DB_GUILD_MARK,
// 	DB_MAP_INFO,
// 	DB_MIXING_INFO,
// 	DB_MYSTERY_ITEM_DROP,
// 	// 2009-03-04 by bhsohn 럭키 머신 수정안
// 	DB_LUCKYMACHINE,
// 	// end 2009-03-04 by bhsohn 럭키 머신 수정안
// 	// 2010. 02. 11 by ckPark 발동류 장착아이템
// 	DB_INVOKINGWEARITEM_DPNUM,			// 2009-09-09 ~ 2010-02-10 by dhjin, 인피니티 - 발동류장착아이템
// 	DB_INVOKINGWEARITEM_DPNUM_BY_USE,	// 2009-09-09 ~ 2010-02-10 by dhjin, 인피니티 - 발동류장착아이템
// 	// end 2010. 02. 11 by ckPark 발동류 장착아이템
// 
// 	// 2010-08-10 by dgwoo 버닝맵 시스템
// 	DB_BURNING_MAP,
// 	// 2010-08-10 by dgwoo 버닝맵 시스템
// 
// 	// 2010-06-15 by shcho&hslee 펫시스템
// 	DB_PET_BASEDATA,						// 2010-06-15 by shcho&hslee 펫시스템 - 펫 기본 정보.
// 	DB_PET_LEVELDATA,						// 2010-06-15 by shcho&hslee 펫시스템 - 펫 레벨업 관련정보.
// 	DB_OPERATOR_ACTION,						// 2010-06-15 by shcho&hslee 펫시스템 - 오퍼레이터 정보
// 	// End 2010-06-15 by shcho&hslee 펫시스템
// 	DB_DISSOLUTION_ITEM,						// 2010-08-31 by shcho&&jskim, 용해 시스템 구현
// 	DB_MONSTER_ADD_TARGET,	
// 
// } DB_TYPE;

// ITEM
// struct DATA_HEADER
// {
// 	DB_TYPE nType;
// 	int nDataCount;
// };

// end 2011. 03. 08 by jskim 인피3차 구현 - 퀘스트 시스템		

// GUILD_MARK_VERSION FILE STRUCT
//----------------------------------------------------------------------------------------------------
//	          8           |				   	  ARRAY_(GUILD_MARK_VERSION):nNumber                      |
//----------------------------------------------------------------------------------------------------
//	          	          |       4     |      4             |      4       |ARRAY_(char):nSizeOfImage|
//----------------------------------------------------------------------------------------------------
//    nType   |  nNumber  |    nVersion | nGuildUniqueNumber | nSizeOfImage |              char       |
//----------------------------------------------------------------------------------------------------

struct GUILD_MARK_VERSION
{
	int nVersion;
	int nGuildUniqueNumber;
	int nSizeOfImage;
	CINFImage* pImage;
	char* pData;
};

typedef std::vector< OperatorInfo* > vectorPreOperatorInfo;

class CAtumDatabase
{
public:
	CAtumDatabase();
	virtual ~CAtumDatabase();


	CMapItemInfoList			m_mapItemInfo;					// 각 Item Data
	CMapItemInfoList			m_mapItemInfoTemp;				// 각 Item Data 임시
	CMapIsLoadingList			m_mapItemGetInfo;				// 각 Item Data - 정보를 요청했는지 
	CMapRareItemInfoList		m_mapRareItemInfo;				// 각 Rare Item Data
	CMapRareItemInfoList		m_mapRareItemInfoTemp;			// 각 Rare Item Data 임시
	CMapIsLoadingList			m_mapRareItemGetInfo;			// 각 Rare Item Data - 정보를 요청했는지 
	CMapMonsterInfoList			m_mapMonsterInfo;				// 각 Monster Data
	CMapMonsterInfoList			m_mapMonsterInfoTemp;			// 각 Monster Data 임시
	CMapIsLoadingList			m_mapMonsterGetInfo;			// 각 Monster Data - 정보를 요청했는지 
	CMapObjectInfoList			m_mapObjectInfo;				// 각 Object Data
	CMapObjectInfoList			m_mapObjectInfoTemp;			// 각 Object Data 임시
	CMapIsLoadingList			m_mapObjectGetInfo;				// 각 Object Data - 정보를 요청했는지 
	CMapBuildingNPCList			m_mapBuildingNPCInfo;			// 각 BUILDINGNPC
	CMapBuildingNPCList			m_mapBuildingNPCInfoTemp;		// 각 BUILDINGNPC 임시
	CMapIsLoadingList			m_mapBuildingNPCGetInfo;		// 각 BUILDINGNPC - 정보를 요청했는지
	CMapGuildMark				m_mapGuildMark;					// 길드 문장 정보
	CMapIsLoadingList			m_mapGuildMarkGetInfo;			// 길드 문장 정보 - 정보를 요청했는지
	CMapOtherGuildInfo			m_mapOtherGuildInfo;			// 다른 캐릭 길드 정보
	CMapIsLoadingList			m_mapOtherGuildInfoGetInfo;		// 다른 캐릭 길드 정보
	CMapMapInfo					m_mapMapInfo;					// 맵 정보(맵이름)
	CVectorMysteryItemDrop		m_VecMysteryItem;				// 미스터리 아이템, 럭키 머신 아이템.
	CVectorMixingInfo			m_VecMixingInfo;				// 조합 정보
	// 2009-03-04 by bhsohn 럭키 머신 수정안
	CVectorLuckyMachine			m_VecLuckyMachine;				// 럭키 머신 아이템 수정안
	// end 2009-03-04 by bhsohn 럭키 머신 수정안

	// 2010. 02. 11 by ckPark 발동류 장착아이템
	CVectorInvokingWearItemDP	m_VecInvokingWearItemDPNum;
	CVectorInvokingWearItemDP	m_VecInvokingWearItemDPNumByUse;
	// end 2010. 02. 11 by ckPark 발동류 장착아이템

	// 2009. 01. 12 by ckPark MapInfo 없는 맵은 모선전 정보 안띄우기

	MAP_INFO					m_DefMapInfo;

	// end 2009. 01. 12 by ckPark MapInfo 없는 맵은 모선전 정보 안띄우기

	// 2010-06-15 by shcho&hslee 펫시스템
	CVectorPetAllData			m_VecPetAllData;
	vectorPreOperatorInfo		m_vecOptratorAction;
	// End 2010-06-15 by shcho&hslee 펫시스템

	// 2010-08-10 by dgwoo 버닝맵 시스템
	CVectorBurningData			m_VecBurningMapData;

	// 2010-08-31 by shcho&&jskim, 용해 시스템 구현
	vectorDissolutionItemInfo	m_vecDissolutionItemInfo;
	// end 2010-08-31 by shcho&&jskim, 용해 시스템 구현
	// 2011. 03. 08 by jskim 인피3차 구현 - 넌 타겟 시스템
	map<INT, vectorMonsterMultiTarget>	m_mapMultiTagetInfo;
	// end 2011. 03. 08 by jskim 인피3차 구현 - 넌 타겟 시스템
};

#endif // !defined(AFX_ATUMDATABASE_H__3842E2DD_C6C4_4D3B_9CFB_18F7EA62E851__INCLUDED_)
