#pragma once
#include "SDK/AtumApplication.h"
#include "OSRBuddyDefine.h"
#include "Content.h"

#include <d3d9.h>
#include <memory>   

class IOPacketManager;

class OldSchoolRivalsAPI 
{			
	OldSchoolRivalsAPI() 
	{ 
		m_atumapplication = nullptr;
		m_packetmanager = nullptr;
	};
	OldSchoolRivalsAPI(const OldSchoolRivalsAPI& other) = delete;
	OldSchoolRivalsAPI& operator=(const OldSchoolRivalsAPI& other) = delete;

public:
	static bool CreateAndCheckConsistence(IOPacketManager* packetmanager);
	static OldSchoolRivalsAPI* GetInstance();
		 
	CAtumApplication* GetAtumApplication();
	CInterface* GetInterface();	
	CAtumDatabase* GetDatabase();
	CFieldWinSocket* GetFieldWinSocket(UINT nSocketNotifyType = 0);	  
	CIMSocket* GetIMSocket(UINT nSocketNotifyType = 0);
	CSceneData* GetSceneData();	  
	CINFGameMainChat* GetINFGameMainChat();

	HWND GetMainWindow();
	IDirect3DDevice9* GetD3D9Device();

	FLOAT GetElapsedTime(); // in seconds

	bool IsShuttleDead();
	FLOAT GetCurrentEnergy();
	FLOAT GetCurrentShield();
	FLOAT GetCurrentSkillp();
	FLOAT GetCurrentFuel();
	SHORT GetMaxEnergy();
	SHORT GetMaxShield();
	SHORT GetMaxSkillp();
	SHORT GetMaxFuel();			   

	CItemInfo* GetRadarItemInfo();
	INT GetPrimaryWeaponAmmo();
	INT GetSecondaryWeaponAmmo();
	void UsePrimaryWeapon(bool use);
	void UseSecondaryWeapon(bool use);
	// with include_paramfactor = true, range boost like siege mode or goggles will be considered
	float GetRadarRangePrimary(float paramfactors = 1.0f); 
	float GetRadarRangePrimaryParamfactors();
	// with include_paramfactor = true, range boost like siege mode or goggles will be considered
	float GetRadarRangeSecondary(float paramfactors = 1.0f);
	float GetRadarRangeSecondaryParamfactors();

	D3DXVECTOR3 GetShuttlePosition();

	CWeaponItemInfo* GetPrimaryWeapon();
	CWeaponItemInfo* GetSecondaryWeapon();

	void SetTarget(CUnitData* target);
	CUnitData* GetTarget();

	bool IsHitablePrimary(CUnitData* target);

	GearType GetPlayerGearType();
	MapIndex GetCurrentMap();
	MAP_CHANNEL_INDEX GetCurrentMapChannelIndex();
	UID32_t GetPlayerUniqueNumber();
	ClientIndex_t GetPlayerClientIndex();

	// CINFCityBase
	bool IsInBuilding();
	BYTE GetCurrentBuildingKind();
	BUILDINGNPC GetCurrentBuilding();
	CINFBase* FindBuildingShop(int buildingkind);

	// CINFCityLab
	void OnButtonClick(int button, bool factory = false);
	void InvenToSourceItem(CItemInfo* pItemInfo, int nCount, bool factory = false, bool useMacroSource = false /*true if you want to move the item to Inetpubs macrogamblebot*/);
	CItemInfo* FindItemFromTarget(UID64_t UniqueNumber);
	CItemInfo* FindItemFromTarget(INT itemnum);
	CItemInfo* FindItemFromSource(UID64_t UniqueNumber);  	
	CItemInfo* FindItemFromSource(INT itemnum);

	//CINFGameMain
	INVEN_DISPLAY_INFO* GetSelectedItem();
	

	// CINFInvExtend
	void SendUseItem(ITEM_GENERAL* item); 
	void DeleteItem(ITEM_GENERAL* item, int count);
	void SendChangeWearWindowPos(int nWindowPosition);
	//void SetSelectItem(INVEN_DISPLAY_INFO* pDisplayInfo);

	// CINFCharacterInfoExtend
	void SendUseSkill(ITEM_BASE* skill);

	// CStoreData
	CItemInfo* FindItemInInventoryByItemNum(INT itemnum, bool find_lowest_time = false);
	CItemInfo* FindItemInInventoryByItemNum(ItemNumber itemnum, bool find_lowest_time = false);
	CItemInfo* FindItemInInventoryByUniqueNumber(UID64_t hyUniqueNumber);
	// returns the count for countable items or the the sum of all noncountable items 
	uint32_t GetInventoryItemCount(INT itemnum);
	// WARNING: this only updates the client side!!!! 
	void UpdateItemCount(UID64_t nUniqueNumber, INT nCount);  
					
	// CAtumDatabase
	RARE_ITEM_INFO* GetServerRareItemInfo(int nCodeNum);
	ITEM* GetServerItemInfo(int nItemNum);

	//CSceneData
	CUnitData* FindUnitDataByClientIndex(ClientIndex_t nIndex);

	// AtumDatabase
	MAP_INFO* GetMapInfo(unsigned short mapindex);

	// CAtumapplication
	void WorldToScreen(D3DXVECTOR3 world, int& screen_x, int& screen_y);

	// CWinSocket
	int WritePacket(byte* packet, int length);

	// CINFCommuPartyInvite
	void RqInvitePartyInfo();

	bool HasPremium();
	uint32_t GetMaxInventorySize();
	uint32_t GetCurrentInventorySize();
	bool IsInventoryFull();	 
	bool IsLanded();
	GearType UnitKindToGearType(USHORT unitkind);

	int GetInventorySPI();
	UID64_t GetSPIUniqueNumber();

	// Checks if a given monster is a boss monster. Ignores useless bosses without drops
	bool IsGoodBossMonster(CMonsterData* monster);
	
	// returns true if player can sell items right now
	bool PlayerIsInSellBuilding();

	// sell the specified items to npc
	void SendSellItem(CItemInfo* item, int count);

	//
	bool IsActiveItem(INT itemnumber);
	bool IsActiveItem(ItemNumber itemnumber);
	bool IsStealthCardActive();	

	bool TryEquipItem(CItemInfo* item);
	ITEM_BASE* GetEquippedItem(EQUIP_POS position);

	bool TrySendUseItem(ITEM_GENERAL* item);
	bool TrySendUseSkill(ITEM_BASE* skill);
	bool TrySendSellItem(CItemInfo* item, int count);
	bool TryDeleteItem(CItemInfo* item, int count);

	bool IsCountableItem(ITEM* item);
	bool CanInsertItemToInventory(INT itemnum);

	bool IsStaffMember(const char* charName);

private:
	// collision stuff
	COLLISION_RESULT CheckCollMeshRangeObject(CObjRender* objrender, D3DXMATRIX mat, D3DXVECTOR3 vPos, float fMovingDistance, CMonsterData* pTarget);
	COLLISION_RESULT CheckCollision(CSkinnedMesh* skinnedmesh, D3DXMATRIX mat, D3DXVECTOR3 vPos, float fCheckDistance, BOOL bUpdateFrame, BOOL bWithNormal);
	COLLISION_RESULT CheckCollDist(CSkinnedMesh* skinnedmesh, SFrame* pframeCur, D3DXMATRIX mat, D3DXVECTOR3 vPos, float fCheckDistance, BOOL bWithNormal);
	HRESULT UpdateFrames(CSkinnedMesh* skinnedmesh, SFrame* pframeCur, D3DXMATRIX& matCur, D3DXVECTOR3 vPos, float fCheckDistance);
	COLLISION_RESULT CheckCollDistDetail(CSkinnedMesh* skinnedmesh, SMeshContainer* pmcMesh, D3DXMATRIX mat, BOOL bWithNormal);
	COLLISION_RESULT CheckCollMeshWaterObject(CObjRender* objrender, D3DXMATRIX mat, D3DXVECTOR3 vPos);
	BOOL IsTileMapRenderEnable(USHORT nMapIndex);
	BOOL CheckIsWater(CShuttleChild* shuttlechild, D3DXVECTOR3 vPos);
	float CheckHeightMap(CBackground* background, D3DXVECTOR3 vPos);
	BOOL IntersectTriangle(CBackground* background, const D3DXVECTOR3& orig, const D3DXVECTOR3& dir, D3DXVECTOR3& v0, D3DXVECTOR3& v1, D3DXVECTOR3& v2, FLOAT* t);

private:
	static OldSchoolRivalsAPI* instance;
	IOPacketManager* m_packetmanager;
	CAtumApplication* m_atumapplication;
};

#ifndef OSR_API
#define OSR_API OldSchoolRivalsAPI::GetInstance()
#endif // !OSR_API

