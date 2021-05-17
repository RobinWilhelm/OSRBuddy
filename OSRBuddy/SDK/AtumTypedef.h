#ifndef _ATUM_TYPEDEF_H__32E91AE4_C7F3_424D_B983_17488DDA215B__INCLUDED_
#define _ATUM_TYPEDEF_H__32E91AE4_C7F3_424D_B983_17488DDA215B__INCLUDED_

#include "mt_stl.h"

class CEnemyData;
class CMonsterData;
class CObjectChild;
class DSound3D;
class CQuest;
class CINFImage;
class CItemInfo;
struct GUILD_MARK_VERSION;
struct MAP_INFO;


typedef vector<CEnemyData*>				CVecEnemyList;			// Block ������ �ٷ�� Enemy List�� Vector
typedef vector<CEnemyData*>::iterator		CVecEnemyIterator;		// Block ������ �ٷ�� Enemy List�� Vector iterator 
typedef vector<CMonsterData*>				CVecMonsterList;		// Block ������ �ٷ�� Monster List�� Vector
typedef vector<CMonsterData*>::iterator	CVecMonsterIterator;	// Block ������ �ٷ�� Monster List�� Vector iterator
typedef map<INT, CEnemyData*>				CMapEnemyList;			// Enemy List�� Map
typedef map<INT, CEnemyData*>::iterator		CMapEnemyIterator;		// Enemy List�� Map iterator
typedef map<INT, CMonsterData*>				CMapMonsterList;		// Monster List�� Map
typedef map<INT, CMonsterData*>::iterator	CMapMonsterIterator;	// Monster List�� Map iterator
typedef map<INT, CObjectChild*>				CMapObjectList;			// ������ �Ǿ��� Object List�� Map
typedef vector<CObjectChild*>				vectorCObjectChildPtr;
typedef map<INT, CObjectChild*>::iterator	CMapObjectIterator;		// ������ �Ǿ��� Object List�� Map iterator
typedef map<int, DSound3D*>				CMapSound3DList;		// effect sound file map
typedef map<int, DSound3D*>::iterator		CMapSound3DIterator;		// effect sound file map


typedef map<int, ITEM*>						CMapItemInfoList;			// ������ ����
typedef map<int, ITEM*>::iterator			CMapItemInfoIterator;
typedef map<int, RARE_ITEM_INFO*>			CMapRareItemInfoList;			// ���� ������ ����
typedef map<int, RARE_ITEM_INFO*>::iterator	CMapRareItemInfoIterator;
typedef map<int, MEX_MONSTER_INFO*>		CMapMonsterInfoList;// ���� ����
typedef map<int, MEX_MONSTER_INFO*>::iterator CMapMonsterInfoIterator;
typedef map<int, MAPOBJECTINFO*>			CMapObjectInfoList;			// ������Ʈ ����
typedef map<int, MAPOBJECTINFO*>::iterator	CMapObjectInfoIterator;
typedef map<int, BOOL>						CMapIsLoadingList;			// �� Item Data - ������ ��û�ߴ���
typedef map<int, BOOL>::iterator			CMapIsLoadingIterator;
typedef map<int, BUILDINGNPC*>				CMapBuildingNPCList;			// building info
typedef map<int, BUILDINGNPC*>::iterator	CMapBuildingNPCIterator;
typedef map<UINT, GUILD_MARK_VERSION*>		CMapGuildMark;				// ��� ��ũ
typedef map<UINT, GUILD_MARK_VERSION*>::iterator CMapGuildMarkIterator;
typedef map<int, MEX_OTHER_GUILD_INFO*>		CMapOtherGuildInfo;
typedef map<int, MEX_OTHER_GUILD_INFO*>::iterator CMapOtherGuildInfoIterator;
typedef map<USHORT, MAP_INFO*>				CMapMapInfo;
typedef map<USHORT, MAP_INFO*>::iterator	CMapMapInfoIterator;
typedef map<USHORT, ITEM_MIXING_INFO*>		CMapMixingInfo;
typedef map<USHORT, ITEM_MIXING_INFO*>::iterator CMapMixingInfoIterator;


//typedef map<LONGLONG, ITEM_ENCHANT*>		CMapItemEnchantList;		// enchant info
//typedef map<LONGLONG, ITEM_ENCHANT*>::iterator CMapItemEnchantIterator;
typedef map<UID64_t, CItemInfo*>			CMapItemInventory;			// new inventory
typedef map<UID64_t, CItemInfo*>::iterator	CMapItemInventoryIterator;
typedef map<int, CItemInfo*>				CMapItemWindowInventory;			// new inventory
typedef map<int, CItemInfo*>::iterator		CMapItemWindowInventoryIterator;
typedef vector<CItemInfo*>					CVectorItemInfo;			// store��
typedef vector<CItemInfo*>::iterator		CVectorItemInfoIterator;

typedef ez_map<INT, CQuest*>				CMapQuest;
typedef ez_map<INT, CQuest*>::iterator		CMapQuestIterator;
typedef map<int, MEX_QUEST_INFO*>			CMapCharacterQuest;
typedef map<int, MEX_QUEST_INFO*>::iterator	CMapCharacterQuestIterator;

typedef vector<WARP_TARGET_MAP_INFO_4_EXCHANGE*> CVectorWarpTargetInfo;
typedef vector<WARP_TARGET_MAP_INFO_4_EXCHANGE*>::iterator CVectorWarpTargetInfoIterator;

typedef vector<MEX_CHANNEL_INFO*>				CVectorChannel;
typedef vector<MEX_CHANNEL_INFO*>::iterator		CVectorChannelIterator;

typedef vector<ITEM_MIXING_INFO*>			CVectorMixingInfo;					// 2006-06-22 by ispark
typedef vector<ITEM_MIXING_INFO*>::iterator CVectorMixingInfoIterator;

typedef vector<ITEM*>						vectorItemInfoList;					// 2006-07-31 by ispark
//typedef map<INT,MYSTERY_ITEM_DROP*>			CMapMysteryItemDrop;				// 2008-11-04 by dgwoo
typedef vector<MYSTERY_ITEM_DROP*>				CVectorMysteryItemDrop;				// 2008-11-04 by dgwoo
typedef vector<MYSTERY_ITEM_DROP*>::iterator	CVectorMysteryItemDropIterator;

// 2009-03-04 by bhsohn ��Ű �ӽ� ������
typedef vector<LUCKY_MACHINE_OMI*>				CVectorLuckyMachine;
typedef vector<LUCKY_MACHINE_OMI*>::iterator	CVectorLuckyMachineIterator;
// end 2009-03-04 by bhsohn ��Ű �ӽ� ������

// 2010. 02. 11 by ckPark �ߵ��� ����������
typedef vector<INVOKING_WEAR_ITEM_DESTPARAM*>			CVectorInvokingWearItemDP;
typedef vector<INVOKING_WEAR_ITEM_DESTPARAM*>::iterator	CVectorInvokingWearItemDPIt;
// end 2010. 02. 11 by ckPark �ߵ��� ����������


typedef vector<tPET_BASE_ALL_DATA*>				CVectorPetAllData;
typedef vector<tPET_BASE_ALL_DATA*>::iterator	CVectorPetAllDataItr;


// 2010-08-10 by dgwoo ���׸� �ý���
typedef vector<BURNING_MAP_INFO*>				CVectorBurningData;
typedef vector<BURNING_MAP_INFO*>::iterator		CVectorBurningDataItr;

#endif // _ATUM_TYPEDEF_H__32E91AE4_C7F3_424D_B983_17488DDA215B__INCLUDED_endif