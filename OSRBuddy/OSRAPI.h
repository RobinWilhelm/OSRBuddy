#pragma once
#include "SDK/AtumApplication.h"
#include <memory>
#include "OSRBuddyDefine.h"
#include <d3d9.h>
   

class OldSchoolRivalsAPI
{			
	OldSchoolRivalsAPI() { };
	OldSchoolRivalsAPI(const OldSchoolRivalsAPI& other) = delete;
	OldSchoolRivalsAPI& operator=(const OldSchoolRivalsAPI& other) = delete;

public:
	static bool CreateAndCheckConsistence();
	static OldSchoolRivalsAPI* GetInstance();
		 
	CAtumApplication* GetAtumApplication();
	CInterface* GetInterface();	
	CAtumDatabase* GetDatabase();
	CFieldWinSocket* GetFieldWinSocket(UINT nSocketNotifyType = 0);	  
	CSceneData* GetSceneData();	  
	CINFGameMainChat* GetINFGameMainChat();

	HWND GetMainWindow();
	IDirect3DDevice9* GetD3D9Device();

	float GetElapsedTime(); // in seconds

	bool IsShuttleDead();
	int GetCurrentEnergy();
	int GetCurrentShield();			
	int GetCurrentSkillp();	 
	int GetCurrentFuel();
	int GetMaxEnergy();
	int GetMaxShield();
	int GetMaxSkillp();
	int GetMaxFuel();			   

	int GetPrimaryWeaponAmmo();
	int GetSecondaryWeaponAmmo(); 
	void UsePrimaryWeapon(bool use);
	void UseSecondaryWeapon(bool use);
	float GetRadarRangePrimary();
	float GetRadarRangeSecondary();

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
	int GetCurrentBuildingKind();
	BUILDINGNPC GetCurrentBuilding();
	CINFBase* FindBuildingShop(int buildingkind);

	// CINFCityLab
	void OnButtonClick(int button, bool factory = false);
	void InvenToSourceItem(CItemInfo* pItemInfo, int nCount, bool factory = false, bool useMacroSource = false /*true if you want to move the item to Inetpubs macrogamblebot*/);
	CItemInfo* FindItemFromTarget(UID64_t UniqueNumber);
	CItemInfo* FindItemFromSource(UID64_t UniqueNumber);

	//CINFGameMain
	INVEN_DISPLAY_INFO* GetSelectedItem();

	// CINFInvExtend
	void SendUseItem(ITEM_GENERAL* item); 
	void DeleteItem(ITEM_GENERAL* item, int count);


	// CINFCharacterInfoExtend
	void SendUseSkill(ITEM_BASE* skill);

	// CStoreData
	CItemInfo* FindItemInInventoryByItemNum(INT itemnum);
	CItemInfo* FindItemInInventoryByItemNum(ItemNumber itemnum); 
	CItemInfo* FindItemInInventoryByUniqueNumber(UID64_t hyUniqueNumber);
					
	// CAtumDatabase
	RARE_ITEM_INFO* GetServerRareItemInfo(int nCodeNum);

	//CSceneData
	CUnitData* FindUnitDataByClientIndex(ClientIndex_t nIndex);

	// AtumDatabase
	MAP_INFO* GetMapInfo(unsigned short mapindex);

	// CAtumapplication
	void WorldToScreen(D3DXVECTOR3 world, int& screen_x, int& screen_y);

	// CWinSocket
	int WritePacket(byte* packet, int length);

	bool HasPremium();
	int GetMaxInventorySize();
	int GetCurrentInventorySize();
	bool IsInventoryFull();	 
	bool IsLanded();
	GearType UnitKindToGearType(USHORT unitkind);

	int GetInventorySPI();

	// Checks if a given monster is a boss monster. Ignores useless bosses without drops
	bool IsGoodBossMonster(CMonsterData* monster);
	   	

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
	CAtumApplication*			m_atumapplication;
};

#ifndef OSR_API
#define OSR_API OldSchoolRivalsAPI::GetInstance()
#endif // !OSR_API

