#pragma once
// AtumDatabase.h: interface for the CAtumDatabase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ATUMDATABASE_H__3842E2DD_C6C4_4D3B_9CFB_18F7EA62E851__INCLUDED_)
#define AFX_ATUMDATABASE_H__3842E2DD_C6C4_4D3B_9CFB_18F7EA62E851__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000  
// 2011. 03. 08 by jskim ����3�� ���� - ����Ʈ �ý���		
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
// 	// 2009-03-04 by bhsohn ��Ű �ӽ� ������
// 	DB_LUCKYMACHINE,
// 	// end 2009-03-04 by bhsohn ��Ű �ӽ� ������
// 	// 2010. 02. 11 by ckPark �ߵ��� ����������
// 	DB_INVOKINGWEARITEM_DPNUM,			// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������
// 	DB_INVOKINGWEARITEM_DPNUM_BY_USE,	// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������
// 	// end 2010. 02. 11 by ckPark �ߵ��� ����������
// 
// 	// 2010-08-10 by dgwoo ���׸� �ý���
// 	DB_BURNING_MAP,
// 	// 2010-08-10 by dgwoo ���׸� �ý���
// 
// 	// 2010-06-15 by shcho&hslee ��ý���
// 	DB_PET_BASEDATA,						// 2010-06-15 by shcho&hslee ��ý��� - �� �⺻ ����.
// 	DB_PET_LEVELDATA,						// 2010-06-15 by shcho&hslee ��ý��� - �� ������ ��������.
// 	DB_OPERATOR_ACTION,						// 2010-06-15 by shcho&hslee ��ý��� - ���۷����� ����
// 	// End 2010-06-15 by shcho&hslee ��ý���
// 	DB_DISSOLUTION_ITEM,						// 2010-08-31 by shcho&&jskim, ���� �ý��� ����
// 	DB_MONSTER_ADD_TARGET,	
// 
// } DB_TYPE;

// ITEM
// struct DATA_HEADER
// {
// 	DB_TYPE nType;
// 	int nDataCount;
// };

// end 2011. 03. 08 by jskim ����3�� ���� - ����Ʈ �ý���		

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


	CMapItemInfoList			m_mapItemInfo;					// �� Item Data
	CMapItemInfoList			m_mapItemInfoTemp;				// �� Item Data �ӽ�
	CMapIsLoadingList			m_mapItemGetInfo;				// �� Item Data - ������ ��û�ߴ��� 
	CMapRareItemInfoList		m_mapRareItemInfo;				// �� Rare Item Data
	CMapRareItemInfoList		m_mapRareItemInfoTemp;			// �� Rare Item Data �ӽ�
	CMapIsLoadingList			m_mapRareItemGetInfo;			// �� Rare Item Data - ������ ��û�ߴ��� 
	CMapMonsterInfoList			m_mapMonsterInfo;				// �� Monster Data
	CMapMonsterInfoList			m_mapMonsterInfoTemp;			// �� Monster Data �ӽ�
	CMapIsLoadingList			m_mapMonsterGetInfo;			// �� Monster Data - ������ ��û�ߴ��� 
	CMapObjectInfoList			m_mapObjectInfo;				// �� Object Data
	CMapObjectInfoList			m_mapObjectInfoTemp;			// �� Object Data �ӽ�
	CMapIsLoadingList			m_mapObjectGetInfo;				// �� Object Data - ������ ��û�ߴ��� 
	CMapBuildingNPCList			m_mapBuildingNPCInfo;			// �� BUILDINGNPC
	CMapBuildingNPCList			m_mapBuildingNPCInfoTemp;		// �� BUILDINGNPC �ӽ�
	CMapIsLoadingList			m_mapBuildingNPCGetInfo;		// �� BUILDINGNPC - ������ ��û�ߴ���
	CMapGuildMark				m_mapGuildMark;					// ��� ���� ����
	CMapIsLoadingList			m_mapGuildMarkGetInfo;			// ��� ���� ���� - ������ ��û�ߴ���
	CMapOtherGuildInfo			m_mapOtherGuildInfo;			// �ٸ� ĳ�� ��� ����
	CMapIsLoadingList			m_mapOtherGuildInfoGetInfo;		// �ٸ� ĳ�� ��� ����
	CMapMapInfo					m_mapMapInfo;					// �� ����(���̸�)
	CVectorMysteryItemDrop		m_VecMysteryItem;				// �̽��͸� ������, ��Ű �ӽ� ������.
	CVectorMixingInfo			m_VecMixingInfo;				// ���� ����
	// 2009-03-04 by bhsohn ��Ű �ӽ� ������
	CVectorLuckyMachine			m_VecLuckyMachine;				// ��Ű �ӽ� ������ ������
	// end 2009-03-04 by bhsohn ��Ű �ӽ� ������

	// 2010. 02. 11 by ckPark �ߵ��� ����������
	CVectorInvokingWearItemDP	m_VecInvokingWearItemDPNum;
	CVectorInvokingWearItemDP	m_VecInvokingWearItemDPNumByUse;
	// end 2010. 02. 11 by ckPark �ߵ��� ����������

	// 2009. 01. 12 by ckPark MapInfo ���� ���� ���� ���� �ȶ���

	MAP_INFO					m_DefMapInfo;

	// end 2009. 01. 12 by ckPark MapInfo ���� ���� ���� ���� �ȶ���

	// 2010-06-15 by shcho&hslee ��ý���
	CVectorPetAllData			m_VecPetAllData;
	vectorPreOperatorInfo		m_vecOptratorAction;
	// End 2010-06-15 by shcho&hslee ��ý���

	// 2010-08-10 by dgwoo ���׸� �ý���
	CVectorBurningData			m_VecBurningMapData;

	// 2010-08-31 by shcho&&jskim, ���� �ý��� ����
	vectorDissolutionItemInfo	m_vecDissolutionItemInfo;
	// end 2010-08-31 by shcho&&jskim, ���� �ý��� ����
	// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
	map<INT, vectorMonsterMultiTarget>	m_mapMultiTagetInfo;
	// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
};

#endif // !defined(AFX_ATUMDATABASE_H__3842E2DD_C6C4_4D3B_9CFB_18F7EA62E851__INCLUDED_)
