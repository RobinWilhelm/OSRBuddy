#include "OSRAPI.h"

#include "Utility.h"
#include "PatternManager.h"

#include "SDK/AtumApplication.h"
#include "SDK/SceneData.h"

#include <d3dx9.h>
#pragma comment(lib,"d3dx9.lib")

OldSchoolRivalsAPI* OldSchoolRivalsAPI::instance  = nullptr;

bool OldSchoolRivalsAPI::CreateAndCheckConsistence()
{
	// correct process?
	uintptr_t ace_modulebase = (uintptr_t)GetModuleHandle("ACEonline.atm");
	if (!ace_modulebase) {
		return false;
	}
	 
	CAtumApplication*** pppatumapplication = reinterpret_cast<CAtumApplication***>(PatternManager::Get(OffsetIdentifier::Pointer_CD3DApplication).address);
	CAtumApplication* atumapplication = **pppatumapplication;
	
	if (!atumapplication) {
		return false;
	}
		  	
	// ANI only h3h3
	if (!COMPARE_INFLUENCE(atumapplication->m_pShuttleChild->m_myShuttleInfo.InfluenceType, INFLUENCE_TYPE_ANI)) {
		return false;
	}
		  
	// Create game API and return  
	OldSchoolRivalsAPI::instance = new OldSchoolRivalsAPI();
	OldSchoolRivalsAPI::instance->m_atumapplication					= atumapplication;
	OldSchoolRivalsAPI::instance->m_SendUseItem						= reinterpret_cast<SendUseItemType>(PatternManager::Get(OffsetIdentifier::CINFInvenExtend__SendUseItem).address);
	OldSchoolRivalsAPI::instance->m_OnButtonClick					= reinterpret_cast<OnButtonClickType>(PatternManager::Get(OffsetIdentifier::CINFCityLab__OnButtonClicked).address);
	OldSchoolRivalsAPI::instance->m_InvenToSourceItem				= reinterpret_cast<InvenToSourceItemType>(PatternManager::Get(OffsetIdentifier::CINFCityLab__InvenToSourceItem).address);
	OldSchoolRivalsAPI::instance->m_GetServerRareItemInfo			= reinterpret_cast<GetServerRareItemInfoType>(PatternManager::Get(OffsetIdentifier::CAtumDatabase__GetServerRareItemInfo).address);
	OldSchoolRivalsAPI::instance->m_SendUseSkill					= reinterpret_cast<SendUseSkillType>(PatternManager::Get(OffsetIdentifier::CINFCharacterInfoExtend__SendUseSkill).address);
	OldSchoolRivalsAPI::instance->m_CalcObjectSourceScreenCoords	= reinterpret_cast<CalcObjectSourceScreenCoordsType>(PatternManager::Get(OffsetIdentifier::CAtumApplication__CalcObjectSourceScreenCoords).address);

	return true;
}

OldSchoolRivalsAPI* OldSchoolRivalsAPI::GetInstance()
{  
	return OldSchoolRivalsAPI::instance;
}


CAtumApplication* OldSchoolRivalsAPI::GetAtumApplication()
{
    return m_atumapplication;
}

CInterface* OldSchoolRivalsAPI::GetInterface()
{
	return m_atumapplication->m_pInterface;
}

CAtumDatabase* OldSchoolRivalsAPI::GetDatabase()
{
	return m_atumapplication->m_pDatabase;
}

CFieldWinSocket* OldSchoolRivalsAPI::GetFieldWinSocket(UINT nSocketNotifyType)
{
	if (nSocketNotifyType == WM_PACKET_ARENA_NOTIFY)
	{
		return m_atumapplication->m_pFieldWinSocket->m_pArenaFieldWinSocket;
	}  
	return m_atumapplication->m_pFieldWinSocket->m_pMainFieldWinSocket;
}

CSceneData* OldSchoolRivalsAPI::GetSceneData()
{
	return m_atumapplication->m_pScene;
}

CINFGameMainChat* OldSchoolRivalsAPI::GetINFGameMainChat()
{
	return m_atumapplication->m_pInterface->m_pGameMain->m_pChat;
}

HWND OldSchoolRivalsAPI::GetMainWindow()
{
	return m_atumapplication->m_hWnd;
}

IDirect3DDevice9* OldSchoolRivalsAPI::GetD3D9Device()
{
	return m_atumapplication->m_pd3dDevice;
}

float OldSchoolRivalsAPI::GetElapsedTime()
{ 
	return m_atumapplication->m_fElapsedTime;
}

bool OldSchoolRivalsAPI::IsShuttleDead()
{
	if (!m_atumapplication->m_pShuttleChild) {
		return false;
	}
    return UNIT_STATE_DEAD(m_atumapplication->m_pShuttleChild->m_dwState) ? true : false;  // kekw
}

int OldSchoolRivalsAPI::GetCurrentEnergy()
{
	return m_atumapplication->m_pShuttleChild->m_fNextHP;
}

int OldSchoolRivalsAPI::GetCurrentShield()
{
	return m_atumapplication->m_pShuttleChild->m_fNextDP;
}

int OldSchoolRivalsAPI::GetMaxEnergy()
{
	return m_atumapplication->m_pShuttleChild->m_myShuttleInfo.HP;
}

int OldSchoolRivalsAPI::GetMaxShield()
{
	return m_atumapplication->m_pShuttleChild->m_myShuttleInfo.DP;
}

int OldSchoolRivalsAPI::GetCurrentSkillp()
{
	return m_atumapplication->m_pShuttleChild->m_fNextSP;
}

int OldSchoolRivalsAPI::GetCurrentFuel()
{
	return m_atumapplication->m_pShuttleChild->m_fNextEP;
}

int OldSchoolRivalsAPI::GetMaxSkillp()
{
	return m_atumapplication->m_pShuttleChild->m_myShuttleInfo.SP;
}

int OldSchoolRivalsAPI::GetMaxFuel()
{
	return m_atumapplication->m_pShuttleChild->m_myShuttleInfo.EP;
}
	  	   
int OldSchoolRivalsAPI::GetPrimaryWeaponAmmo()
{
	if (!GetPrimaryWeapon())
	{
		// no weapon equipped
		return 0;
	}
	return m_atumapplication->m_pShuttleChild->m_pPrimaryWeapon->m_pItemInfo->CurrentCount;
}

int OldSchoolRivalsAPI::GetSecondaryWeaponAmmo()
{
	if (!GetSecondaryWeapon())
	{
		// no weapon equipped
		return 0;
	}
	return m_atumapplication->m_pShuttleChild->m_pSecondaryWeapon->m_pItemInfo->CurrentCount;
}

void OldSchoolRivalsAPI::UsePrimaryWeapon(bool use)
{
	m_atumapplication->m_pShuttleChild->m_bLButtonState = use;
}

void OldSchoolRivalsAPI::UseSecondaryWeapon(bool use)
{
	m_atumapplication->m_pShuttleChild->m_bRButtonState = use;
}

float OldSchoolRivalsAPI::GetRadarRangePrimary()
{
	if (!m_atumapplication->m_pShuttleChild->m_pRadarItemInfo) {
		return 0.0f;
	}	 		

	return m_atumapplication->m_pShuttleChild->m_pRadarItemInfo->m_pItemInfo->AbilityMin;
}

float OldSchoolRivalsAPI::GetRadarRangeSecondary()
{
	if (!m_atumapplication->m_pShuttleChild->m_pRadarItemInfo) {
		return 0.0f;
	}

	return m_atumapplication->m_pShuttleChild->m_pRadarItemInfo->m_pItemInfo->AbilityMax;
}

D3DXVECTOR3 OldSchoolRivalsAPI::GetShuttlePosition()
{
	return m_atumapplication->m_pShuttleChild->m_vPos;
}

CWeaponItemInfo* OldSchoolRivalsAPI::GetPrimaryWeapon()
{
	return m_atumapplication->m_pShuttleChild->m_pPrimaryWeapon;
}

CWeaponItemInfo* OldSchoolRivalsAPI::GetSecondaryWeapon()
{
	return m_atumapplication->m_pShuttleChild->m_pSecondaryWeapon;
}

void OldSchoolRivalsAPI::SetTarget(CUnitData* target)
{
	m_atumapplication->m_pShuttleChild->m_pOrderTarget = target;
}

bool OldSchoolRivalsAPI::IsHitablePrimary(CUnitData* target)
{
	D3DXVECTOR3 vTargetPos = target->m_vPos;
	D3DXVECTOR3 vShuttlePos = m_atumapplication->m_pShuttleChild->m_vPos;
	D3DXVECTOR3 vShuttleUp = m_atumapplication->m_pShuttleChild->m_vUp;
	D3DXVECTOR3 vTargetVel;
	D3DXVECTOR3 vTargetPosObject, vTargetPosGround;
		

	D3DXVECTOR3 delta = vTargetPos - vShuttlePos;

	D3DXVec3Normalize(&vTargetVel, &delta);

	CUnitData* pTarget = target;
	CMonsterData* pMonster = NULL;
	if (pTarget && pTarget->m_dwPartType == _MONSTER)
	{
		pMonster = (CMonsterData*)pTarget;
	}

	// 초기값 셋팅
	vTargetPosObject = vTargetPos;
	vTargetPosGround = vTargetPos;

	D3DXMATRIX mat;
	D3DXMatrixLookAtLH(&mat, &vShuttlePos, &(vShuttlePos + vTargetVel), &vShuttleUp);

	float fDistance = D3DXVec3Length(&(vShuttlePos - vTargetPos));
	float fMovingDistance = MAX_WEAPON_SPEED * m_atumapplication->m_fElapsedTime;
	//	float fCheckDistance = g_pScene->m_pObjectRender->CheckCollMeshRangeObject(mat,vShuttlePos,fMovingDistance,pMonster).fDist;
	float fCheckDistance = CheckCollMeshRangeObject(GetSceneData()->m_pObjectRender, mat, vShuttlePos, fDistance, pMonster).fDist;

	// 오브젝트와 충돌검사
	if (fDistance > fCheckDistance)
	{	
		return false;
	}

	// 2006-06-02 by ispark
	// 지형과 충돌검사
	if (IsTileMapRenderEnable(m_atumapplication->m_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex))
	{
		float fTempDistance = 0.0f;
		D3DXVECTOR3 vTempPos;
		while (fTempDistance < fDistance)	// 지형 및 물과 충돌 검사
		{
			vTempPos = vShuttlePos + vTargetVel * fTempDistance;
			if (CheckHeightMap(m_atumapplication->m_pScene->m_pGround, vTempPos) > vTempPos.y)
			{	// 지형 및 물과 충돌 했다.
				vTargetPosGround = vTempPos;	
				break;
			}
			fTempDistance += TILE_SIZE;
		}
	}

	if (fDistance > D3DXVec3Length(&(vTargetPosGround - vShuttlePos)))
	{ // 지형과 먼저 충돌한다.
		return false;
	}

	return true;
}

COLLISION_RESULT OldSchoolRivalsAPI::CheckCollMeshRangeObject(CObjRender* objrender, D3DXMATRIX mat, D3DXVECTOR3 vPos, float fMovingDistance, CMonsterData* pTarget)
{
	COLLISION_RESULT collResult, checkcollResult;

	vectorCObjectChildPtr::iterator itObj(GetSceneData()->m_vectorRangeObjectPtrList.begin());
	// 사용함..
	while (itObj != GetSceneData()->m_vectorRangeObjectPtrList.end())
	{
		CObjectChild* pObject = *itObj;
		if (pObject && pObject->m_pObjectInfo && pObject->m_pObjectInfo->Collision && pObject->m_pObjMesh)
		{
			float fRadius = pObject->m_pObjMesh->m_fRadius;
			if (D3DXVec3Length(&(pObject->m_vOriPos - vPos)) < fRadius * 2.0f + fMovingDistance)
			{
				//pObject->m_pObjMesh->Tick(pObject->m_fCurrentTime);
				{
					SDrawElement* pdeCur;
					SFrame* pframeCur;

					pdeCur = pObject->m_pObjMesh->m_pdeHead;
					while (pdeCur != NULL)
					{
						pdeCur->fCurTime = pObject->m_fCurrentTime * 160;
						pframeCur = pdeCur->pframeAnimHead;
						while (pframeCur != NULL)
						{
							pframeCur->SetTime(pdeCur->fCurTime);
							pframeCur = pframeCur->pframeAnimNext;
						}

						pdeCur = pdeCur->pdeNext;
					} 
				} 
				
				//pObject->m_pObjMesh->SetWorldMatrix(pObject->m_mMatrix);
				pObject->m_pObjMesh->m_mWorld = pObject->m_mMatrix;

				//checkcollResult = pObject->m_pObjMesh->CheckCollision(mat, vPos, DEFAULT_COLLISION_DISTANCE, TRUE, FALSE);
				checkcollResult = CheckCollision(pObject->m_pObjMesh, mat, vPos, DEFAULT_COLLISION_DISTANCE, TRUE, FALSE);

				if (collResult.fDist > checkcollResult.fDist)
				{
					collResult = checkcollResult;
				}
			}
		}
		itObj++;
	}

	if (collResult.fDist == DEFAULT_COLLISION_DISTANCE)	// 충돌 안했다면..
	{
		// 2004-11-29 by jschoi - 오브젝트 몬스터 오브젝트를 충돌 리스트에 추가
		CObjectChild* pObjectMonster = (CObjectChild*)(GetSceneData()->m_pGround)->m_pObjectMonster->m_pChild;

		while (pObjectMonster)
		{
			if (pObjectMonster->m_pObjectInfo &&
				pObjectMonster->m_bEnableObjectMonsterObject == FALSE &&
				(pTarget == NULL || pObjectMonster->m_dwObjectMonsterUniqueNumber != pTarget->m_pMonsterInfo->SourceIndex))
			{
				float fRadius = 0;
				if (pObjectMonster->m_pObjMesh)
				{
					fRadius = pObjectMonster->m_pObjMesh->m_fRadius;
				}

				if (D3DXVec3Length(&(pObjectMonster->m_vOriPos - vPos)) < fRadius * 2.0f + fMovingDistance)
				{
					//pObjectMonster->m_pObjMesh->Tick(pObjectMonster->m_fCurrentTime);
					{
						SDrawElement* pdeCur;
						SFrame* pframeCur;

						pdeCur = pObjectMonster->m_pObjMesh->m_pdeHead;
						while (pdeCur != NULL)
						{
							pdeCur->fCurTime = pObjectMonster->m_fCurrentTime * 160;
							pframeCur = pdeCur->pframeAnimHead;
							while (pframeCur != NULL)
							{
								pframeCur->SetTime(pdeCur->fCurTime);
								pframeCur = pframeCur->pframeAnimNext;
							}

							pdeCur = pdeCur->pdeNext;
						}
					}

					//pObjectMonster->m_pObjMesh->SetWorldMatrix(pObjectMonster->m_mMatrix);   
					pObjectMonster->m_pObjMesh->m_mWorld = pObjectMonster->m_mMatrix;

					//checkcollResult = pObjectMonster->m_pObjMesh->CheckCollision(mat, vPos, DEFAULT_COLLISION_DISTANCE, TRUE, FALSE);
					checkcollResult = CheckCollision(pObjectMonster->m_pObjMesh, mat, vPos, DEFAULT_COLLISION_DISTANCE, TRUE, FALSE);
					if (collResult.fDist > checkcollResult.fDist)
					{
						collResult = checkcollResult;
					}
				}
			}
			pObjectMonster = (CObjectChild*)pObjectMonster->m_pNext;
		}
	}
	return collResult;
}

COLLISION_RESULT OldSchoolRivalsAPI::CheckCollision(CSkinnedMesh* skinnedmesh, D3DXMATRIX mat, D3DXVECTOR3 vPos, float fCheckDistance, BOOL bUpdateFrame, BOOL bWithNormal)
{
	COLLISION_RESULT collResult, checkcollResult;
	SDrawElement* pdeCur;
	pdeCur = skinnedmesh->m_pdeHead;
	//	collResult.fDist = 10000.0f;
	//	collResult.vNormalVector = D3DXVECTOR3(0,0,0);
	while (pdeCur != NULL)
	{
		if (bUpdateFrame)
		{
			UpdateFrames(skinnedmesh, pdeCur->pframeRoot, skinnedmesh->m_mWorld, vPos, fCheckDistance);
		}
		checkcollResult = CheckCollDist(skinnedmesh, pdeCur->pframeRoot, mat, vPos, fCheckDistance, bWithNormal);
		if (collResult.fDist > checkcollResult.fDist)
		{
			collResult = checkcollResult;

		}
		pdeCur = pdeCur->pdeNext;
	}
	return collResult;
}

COLLISION_RESULT OldSchoolRivalsAPI::CheckCollDist(CSkinnedMesh* skinnedmesh, SFrame* pframeCur, D3DXMATRIX mat, D3DXVECTOR3 vPos, float fCheckDistance, BOOL bWithNormal)
{
	COLLISION_RESULT collResult, checkcollResult;
	SMeshContainer* pmcMesh;
	SFrame* pframeChild;
	if (pframeCur->pmcMesh != NULL)
	{
		skinnedmesh->m_pd3dDevice->SetTransform(D3DTS_WORLD, &pframeCur->matCombined);
	}
	pmcMesh = pframeCur->pmcMesh;

	D3DXVECTOR3 vMeshCenter;

	while (pmcMesh != NULL)
	{
		//		D3DXVec3TransformCoord(&vMeshCenter,&pmcMesh->vCenter,&m_mWorld);				
		//		if(D3DXVec3Length(&(vMeshCenter - g_pShuttleChild->m_vPos)) - pmcMesh->fRadius < fCheckDistance )
		//		{
		//			checkcollResult = CheckCollDistDetail(pmcMesh,mat,bWithNormal);
		//			if(collResult.fDist > checkcollResult.fDist)
		//				collResult = checkcollResult;
		//		}
		checkcollResult = CheckCollDistDetail(skinnedmesh, pmcMesh, mat, bWithNormal);
		if (collResult.fDist > checkcollResult.fDist)
			collResult = checkcollResult;

		pmcMesh = pmcMesh->pmcNext;
	}
	pframeChild = pframeCur->pframeFirstChild;

	while (pframeChild != NULL)
	{
		// 2005-01-05 by jschoi
		pmcMesh = pframeChild->pmcMesh;
		if (pmcMesh)
		{
			D3DXVec3TransformCoord(&vMeshCenter, &pmcMesh->vCenter, &skinnedmesh->m_mWorld);
			if (D3DXVec3Length(&(vMeshCenter - vPos)) - pmcMesh->fRadius < fCheckDistance)
			{
				checkcollResult = CheckCollDist(skinnedmesh, pframeChild, mat, vPos, fCheckDistance, bWithNormal);
				if (collResult.fDist > checkcollResult.fDist)
					collResult = checkcollResult;
			}
		}
		else
		{
			checkcollResult = CheckCollDist(skinnedmesh, pframeChild, mat, vPos, fCheckDistance, bWithNormal);
			if (collResult.fDist > checkcollResult.fDist)
				collResult = checkcollResult;
		}

		//		checkcollResult = CheckCollDist(pframeChild,mat,fCheckDistance,bWithNormal);
		//		if(collResult.fDist > checkcollResult.fDist)
		//			collResult = checkcollResult;

		pframeChild = pframeChild->pframeSibling;
	}
	return collResult;
}
	   
GearType OldSchoolRivalsAPI::GetPlayerGearType()
{
	if (IS_BT(m_atumapplication->m_pShuttleChild->m_myShuttleInfo.UnitKind)) {
		return GearType::BGear;
	}

	if (IS_OT(m_atumapplication->m_pShuttleChild->m_myShuttleInfo.UnitKind)) {
		return GearType::MGear;
	}

	if (IS_DT(m_atumapplication->m_pShuttleChild->m_myShuttleInfo.UnitKind)) {
		return GearType::AGear;
	}

	if (IS_ST(m_atumapplication->m_pShuttleChild->m_myShuttleInfo.UnitKind)) {
		return GearType::IGear;
	}
}

MapIndex OldSchoolRivalsAPI::GetCurrentMap()
{
	switch (m_atumapplication->m_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex)
	{
		case 9002: return MapIndex::WatermelonIsland;
		case 9050: return MapIndex::InvasionWorld;
			// lazy
	}

	return MapIndex();
}

MAP_CHANNEL_INDEX OldSchoolRivalsAPI::GetCurrentMapChannelIndex()
{
	return m_atumapplication->m_pShuttleChild->m_myShuttleInfo.MapChannelIndex;
}

UID32_t OldSchoolRivalsAPI::GetPlayerUniqueNumber()
{
	return m_atumapplication->m_pShuttleChild->m_myShuttleInfo.CharacterUniqueNumber;
}

ClientIndex_t OldSchoolRivalsAPI::GetPlayerClientIndex()
{
	return m_atumapplication->m_pShuttleChild->m_myShuttleInfo.ClientIndex;
}

bool OldSchoolRivalsAPI::IsInBuilding()
{
	// m_nCurrentEnterBuildingIndex is set to -1 if not in building
	return m_atumapplication->m_pInterface->m_pCityBase->m_nCurrentEnterBuildingIndex != -1;
}

int OldSchoolRivalsAPI::GetCurrentyBuildingKind()
{
	return m_atumapplication->m_pInterface->m_pCityBase->m_pCurrentBuildingNPC ? m_atumapplication->m_pInterface->m_pCityBase->m_pCurrentBuildingNPC->buildingInfo.BuildingKind : -1;
}

CINFBase* OldSchoolRivalsAPI::FindBuildingShop(int buildingkind)
{
#ifndef _DEBUG	  // structure of std::map is different in debugmode which leads to crash 
	CINFCityBase* citybase = m_atumapplication->m_pInterface->m_pCityBase;
	if (!citybase) {
		return nullptr;
	}

	CMapCityShopIterator it = citybase->m_mapCityShop.find(buildingkind);
	if (it != citybase->m_mapCityShop.end())
	{
		return it->second;
	}					
#endif
	return nullptr;
}

void OldSchoolRivalsAPI::OnButtonClick(int button)
{
	CINFCityLab* citylab = static_cast<CINFCityLab*>(FindBuildingShop(BUILDINGKIND_LABORATORY));
	if (!citylab) {
		return;
	}
	
	m_OnButtonClick(citylab, button);
}

void OldSchoolRivalsAPI::InvenToSourceItem(CItemInfo* pItemInfo, int nCount, bool useMacroSource = false)
{
	CINFCityLab* citylab = static_cast<CINFCityLab*>(FindBuildingShop(BUILDINGKIND_LABORATORY));
	if (!citylab) {
		return;
	}

	m_InvenToSourceItem(citylab, pItemInfo, nCount, useMacroSource);
}

CItemInfo* OldSchoolRivalsAPI::FindItemFromTarget(UID64_t UniqueNumber)
{
#ifndef _DEBUG	  // structure of std::map is different in debugmode which leads to crash 
	CINFCityLab* citylab = static_cast<CINFCityLab*>(FindBuildingShop(BUILDINGKIND_LABORATORY));
	if (!citylab) {
		return nullptr;
	}

	vector<CItemInfo*>::iterator it = citylab->m_vecTarget.begin();
	while (it != citylab->m_vecTarget.end())
	{
		if (UniqueNumber == (*it)->UniqueNumber)
		{
			return (*it);
		}
		it++;
	}
#endif
	return nullptr;
}

CItemInfo* OldSchoolRivalsAPI::FindItemFromSource(UID64_t UniqueNumber)
{
#ifndef _DEBUG	  // structure of std::map is different in debugmode which leads to crash 
	CINFCityLab* citylab = static_cast<CINFCityLab*>(FindBuildingShop(BUILDINGKIND_LABORATORY));
	if (!citylab) {
		return nullptr;
	}				 

	vector<CItemInfo*>::iterator it = citylab->m_vecSource.begin();
	while (it != citylab->m_vecSource.end())
	{
		if (UniqueNumber == (*it)->UniqueNumber)
		{
			return (*it);
		}
		it++;
	}
#endif // ! _DEBUG
	return nullptr;
}

INVEN_DISPLAY_INFO* OldSchoolRivalsAPI::GetSelectedItem()
{
	 return m_atumapplication->m_pInterface->m_pGameMain->m_stSelectItem.pSelectItem;
}

void OldSchoolRivalsAPI::SendUseItem(ITEM_GENERAL* item)
{
	CINFInvenExtend* inven = m_atumapplication->m_pInterface->m_pGameMain->m_pInven;
	if (inven) {
		m_SendUseItem(inven, static_cast<ITEM_BASE*>(item));
	}  	
}

void OldSchoolRivalsAPI::SendUseSkill(ITEM_BASE* skill)
{
	CINFCharacterInfoExtend* charinfo = m_atumapplication->m_pInterface->m_pGameMain->m_pCharacterInfo;
	if (charinfo) {
		m_SendUseSkill(charinfo, static_cast<ITEM_BASE*>(skill));
	}
}

CItemInfo* OldSchoolRivalsAPI::FindItemInInventoryByItemNum(INT itemnum)
{
#ifndef _DEBUG	  // structure of std::map is different in debugmode which leads to crash 
	CStoreData* storedata = m_atumapplication->m_pShuttleChild->m_pStoreData;
	if (!storedata) {
		return nullptr;
	}

	CMapItemInventoryIterator it = storedata->m_mapItemUniqueNumber.begin();
	while (it != storedata->m_mapItemUniqueNumber.end())
	{
		if (it->second->ItemNum == itemnum)
		{
			return it->second;
		}
		it++;
	}
#endif // ! _DEBUG
	return nullptr;
}

CItemInfo* OldSchoolRivalsAPI::FindItemInInventoryByItemNum(ItemNumber itemnum)
{
	return FindItemInInventoryByItemNum(TO_INT(itemnum));
}

CItemInfo* OldSchoolRivalsAPI::FindItemInInventoryByUniqueNumber(UID64_t hyUniqueNumber)
{
#ifndef _DEBUG	  // structure of std::map is different in debugmode which leads to crash 
	CStoreData* storedata = m_atumapplication->m_pShuttleChild->m_pStoreData;
	if (!storedata) {
		return nullptr;
	}

	CMapItemInventoryIterator it = storedata->m_mapItemUniqueNumber.find(hyUniqueNumber);
	if (it != storedata->m_mapItemUniqueNumber.end())
	{
		return it->second;
	}
#endif // ! _DEBUG
	return nullptr;
}

RARE_ITEM_INFO* OldSchoolRivalsAPI::GetServerRareItemInfo(int nCodeNum)
{
	CAtumDatabase* database = m_atumapplication->m_pDatabase;
	RARE_ITEM_INFO* rif = nullptr;
	if (database) {
		rif = m_GetServerRareItemInfo(database, nCodeNum);
	}
	return rif;
}

CUnitData* OldSchoolRivalsAPI::FindUnitDataByClientIndex(ClientIndex_t nIndex)
{
	if (m_atumapplication->m_pShuttleChild == NULL)
	{
		return NULL;
	}
	if (nIndex == m_atumapplication->m_pShuttleChild->m_myShuttleInfo.ClientIndex)
	{
		return m_atumapplication->m_pShuttleChild;
	}
	else if (IS_CHARACTER_CLIENT_INDEX(nIndex))//pMsg->AttackIndex < 10000)
	{
		CMapEnemyIterator itEnemy = GetSceneData()->m_mapEnemyList.find(nIndex);
		if (itEnemy != GetSceneData()->m_mapEnemyList.end())
		{
			return itEnemy->second;
		}
	}
	else if (IS_MONSTER_CLIENT_INDEX(nIndex))
	{
		CMapMonsterIterator itMonster = GetSceneData()->m_mapMonsterList.find(nIndex);
		if (itMonster != GetSceneData()->m_mapMonsterList.end())
		{
			return itMonster->second;
		}
	}
	return NULL;
}

MAP_INFO* OldSchoolRivalsAPI::GetMapInfo(unsigned short mapindex)
{
	if (!m_atumapplication->m_pDatabase) {
		return nullptr;
	}

	CMapMapInfoIterator it = m_atumapplication->m_pDatabase->m_mapMapInfo.find((USHORT)mapindex);
	if (it != m_atumapplication->m_pDatabase->m_mapMapInfo.end())
	{
		return it->second;
	}
}

void OldSchoolRivalsAPI::WorldToScreen(D3DXVECTOR3 world, int& screen_x, int& screen_y)
{
	int screen_w;
	m_CalcObjectSourceScreenCoords(m_atumapplication, world, m_atumapplication->m_d3dsdBackBuffer.Width, m_atumapplication->m_d3dsdBackBuffer.Height, screen_x, screen_y, screen_w);
}

HRESULT OldSchoolRivalsAPI::UpdateFrames(CSkinnedMesh* skinnedmesh, SFrame* pframeCur, D3DXMATRIX& matCur, D3DXVECTOR3 vPos, float fCheckDistance)
{
	D3DXMatrixMultiply(&pframeCur->matCombined, &pframeCur->matRot, &matCur);
	D3DXMatrixMultiply(&pframeCur->matCombined, &pframeCur->matCombined, &pframeCur->matTrans);
	SFrame* pframeChild = pframeCur->pframeFirstChild;
	SMeshContainer* pmcMesh;
	D3DXVECTOR3 vMeshCenter;
	while (pframeChild != NULL)
	{
		pmcMesh = pframeChild->pmcMesh;
		if (pmcMesh)
		{
			D3DXVec3TransformCoord(&vMeshCenter, &pmcMesh->vCenter, &skinnedmesh->m_mWorld);
			if (D3DXVec3Length(&(vMeshCenter - vPos)) - pmcMesh->fRadius < fCheckDistance)
			{
				UpdateFrames(skinnedmesh,pframeChild, pframeCur->matCombined, vPos, fCheckDistance);
			}
		}
		else
		{
			UpdateFrames(skinnedmesh, pframeChild, pframeCur->matCombined, vPos, fCheckDistance);
		}

		pframeChild = pframeChild->pframeSibling;
	}

	return S_OK;
}

COLLISION_RESULT OldSchoolRivalsAPI::CheckCollDistDetail(CSkinnedMesh* skinnedmesh, SMeshContainer* pmcMesh, D3DXMATRIX mat, BOOL bWithNormal)
{
	//	FLOG( "CSkinnedMesh::CheckCollDistDetail(SMeshContainer *pmcMesh,D3DXMATRIX mat)" );
	COLLISION_RESULT collResult;
	//	collResult.fDist = DEFAULT_COLLISION_DISTANCE;
	if (pmcMesh->m_pSkinMesh)
	{
		if (skinnedmesh->m_method == SOFTWARE)
		{
			D3DXMATRIX  Identity;
			DWORD       cBones = pmcMesh->m_pSkinMeshInfo->GetNumBones();
			// set up bone transforms
			for (DWORD iBone = 0; iBone < cBones; ++iBone)
			{
				D3DXMatrixMultiply
				(
					&skinnedmesh->m_pBoneMatrices[iBone],                 // output
					&pmcMesh->m_pBoneOffsetMat[iBone],
					pmcMesh->m_pBoneMatrix[iBone]
				);
			}
			// set world transform
			D3DXMatrixIdentity(&Identity);
			skinnedmesh->m_pd3dDevice->SetTransform(D3DTS_WORLD, &Identity);
			// generate skinned mesh
			if (!pmcMesh->pMesh)
			{
				//				collResult.fDist = DEFAULT_COLLISION_DISTANCE;
				return collResult;
			}
			//            pmcMesh->m_pSkinMesh->UpdateSkinnedMesh(m_pBoneMatrices, NULL, pmcMesh->pMesh);
		}
	}

	BOOL bHit, bIntersections;
	DWORD dwFace;
	FLOAT fBary1, fBary2, fDist;

	//	D3DXMATRIX matProj;
	D3DXVECTOR3 vPickRayDir, vPickRayOrig;
	D3DXMATRIX m, matWorld;
	//	g_pD3dDev->GetTransform( D3DTS_PROJECTION, &matProj );
		// Get the inverse view matrix
	GetD3D9Device()->GetTransform(D3DTS_WORLD, &matWorld);
	m = matWorld * mat;
	D3DXMatrixInverse(&m, NULL, &m);
	vPickRayDir.x = m._31;
	vPickRayDir.y = m._32;
	vPickRayDir.z = m._33;
	vPickRayOrig.x = m._41;
	vPickRayOrig.y = m._42;
	vPickRayOrig.z = m._43;

	D3DXIntersect(pmcMesh->pMesh, &vPickRayOrig, &vPickRayDir, &bHit, &dwFace, &fBary1, &fBary2, &fDist,
		NULL, NULL);
	if (bHit)
	{
		bIntersections = TRUE;
		skinnedmesh->m_Intersection.dwFace = dwFace;
		skinnedmesh->m_Intersection.fBary1 = fBary1;
		skinnedmesh->m_Intersection.fBary2 = fBary2;
		skinnedmesh->m_Intersection.fDist = fDist;
	}
	else
	{
		bIntersections = FALSE;
	}

	if (bIntersections)
	{
		if (bWithNormal) // 2004-11-03 by jschoi 법선 벡터가 필요할때만 구한다.
		{
			WORD* pIndices;
			D3DVERTEX* pVertices;

			D3DVERTEX vThisTri[3];
			WORD* iThisTri;

			//			LPDIRECT3DVERTEXBUFFER9 pVB;
			//			LPDIRECT3DINDEXBUFFER9  pIB;	
			//			pmcMesh->pMesh->GetVertexBuffer(&pVB);
			//			pmcMesh->pMesh->GetIndexBuffer( &pIB );
			//			pIB->Lock( 0,0,(void**)&pIndices, 0 );
			//			pVB->Lock( 0,0,(void**)&pVertices, 0 );

			pmcMesh->pMesh->LockVertexBuffer(D3DLOCK_READONLY, (LPVOID*)&pVertices);
			pmcMesh->pMesh->LockIndexBuffer(D3DLOCK_READONLY, (LPVOID*)&pIndices);

			iThisTri = &pIndices[3 * skinnedmesh->m_Intersection.dwFace];
			// get vertices hit
			vThisTri[0] = pVertices[iThisTri[0]];
			vThisTri[1] = pVertices[iThisTri[1]];
			vThisTri[2] = pVertices[iThisTri[2]];

			pmcMesh->pMesh->UnlockVertexBuffer();
			pmcMesh->pMesh->UnlockIndexBuffer();
			//			pVB->Unlock();
			//			pIB->Unlock();

			//			pVB->Release();
			//			pIB->Release();	

			D3DXVec3TransformCoord(&vThisTri[0].p, &vThisTri[0].p, &matWorld);
			D3DXVec3TransformCoord(&vThisTri[1].p, &vThisTri[1].p, &matWorld);
			D3DXVec3TransformCoord(&vThisTri[2].p, &vThisTri[2].p, &matWorld);
			//			D3DXVec3TransformNormal(&vThisTri[0].n, &vThisTri[0].n, &matWorld);
			//			D3DXVec3TransformNormal(&vThisTri[1].n, &vThisTri[1].n, &matWorld);
			//			D3DXVec3TransformNormal(&vThisTri[2].n, &vThisTri[2].n, &matWorld);

						// 법선을 구하자.

			D3DXVECTOR3 vTempNormal, vNormalVector;
			D3DXVECTOR3 vCross1, vCross2;
			vCross1 = vThisTri[0].p - vThisTri[1].p;
			vCross2 = vThisTri[1].p - vThisTri[2].p;
			D3DXVec3Cross(&vTempNormal, &vCross1, &vCross2);
			D3DXVec3Normalize(&vNormalVector, &vTempNormal);

			//			vNormalVector = vThisTri[0].n + vThisTri[1].n + vThisTri[2].n;
			//			D3DXVec3Normalize(&vNormalVector,&vNormalVector);

			collResult.vNormalVector = vNormalVector;
		}

		collResult.fDist = fDist;

		return collResult; // 어쩌구 구조체;
	}

	return collResult;// 어쩌구 구조체 충돌 없다.;
}

COLLISION_RESULT OldSchoolRivalsAPI::CheckCollMeshWaterObject(CObjRender* objrender, D3DXMATRIX mat, D3DXVECTOR3 vPos)
{
	COLLISION_RESULT collResult, checkcollResult;

	vectorCObjectChildPtr::iterator itObj(GetSceneData()->m_vectorCollisionObjectPtrList.begin());
	// 사용함..
	while (itObj != GetSceneData()->m_vectorCollisionObjectPtrList.end())
	{
		CObjectChild* pObject = *itObj;
		if (pObject &&
			pObject->m_pObjectInfo &&
			pObject->m_pObjectInfo->ObjectRenderType == OBJECT_WATER &&
			pObject->m_pObjectInfo->Collision &&
			pObject->m_pObjMesh)
		{
			float fRadius = pObject->m_pObjMesh->m_fRadius;
			if (D3DXVec3Length(&(pObject->m_vOriPos - vPos)) < fRadius)
			{
				//pObject->m_pObjMesh->Tick(pObject->m_fCurrentTime);
				{
					SDrawElement* pdeCur;
					SFrame* pframeCur;

					pdeCur = pObject->m_pObjMesh->m_pdeHead;
					while (pdeCur != NULL)
					{
						pdeCur->fCurTime = pObject->m_fCurrentTime * 160;
						pframeCur = pdeCur->pframeAnimHead;
						while (pframeCur != NULL)
						{
							pframeCur->SetTime(pdeCur->fCurTime);
							pframeCur = pframeCur->pframeAnimNext;
						}

						pdeCur = pdeCur->pdeNext;
					}
				}

				//pObject->m_pObjMesh->SetWorldMatrix(pObject->m_mMatrix);
				pObject->m_pObjMesh->m_mWorld = pObject->m_mMatrix;
				checkcollResult = CheckCollision(pObject->m_pObjMesh, mat, vPos, DEFAULT_COLLISION_DISTANCE, TRUE, FALSE);
				if (collResult.fDist > checkcollResult.fDist)
					collResult = checkcollResult;
			}
		}
		itObj++;
	}

	return collResult;
}

BOOL OldSchoolRivalsAPI::IsTileMapRenderEnable(USHORT nMapIndex)
{
	CMapMapInfoIterator it = m_atumapplication->m_pDatabase->m_mapMapInfo.find((USHORT)nMapIndex);
	if (it != m_atumapplication->m_pDatabase->m_mapMapInfo.end())
	{
		return it->second->TileRenderingFlag;
	}

	m_atumapplication->m_pDatabase->m_DefMapInfo.TileRenderingFlag;
}

BOOL OldSchoolRivalsAPI::CheckIsWater(CShuttleChild* shuttlechild, D3DXVECTOR3 vPos)
{
	// 2005-02-11 by jschoi 물 오브젝트 먼저 검사
	D3DXMATRIX mat;
	D3DXVECTOR3 vSide(0, 0, 1), vUp(0, 1, 0);
	D3DXMatrixLookAtLH(&mat, &shuttlechild->m_vPos, &(shuttlechild->m_vPos - shuttlechild->m_vUp), &vSide);		// 아래

	if (m_atumapplication->m_pScene &&
		m_atumapplication->m_pScene->m_pObjectRender)
	{
		COLLISION_RESULT collResult = CheckCollMeshWaterObject(m_atumapplication->m_pScene->m_pObjectRender, mat, shuttlechild->m_vPos);
		if (collResult.fDist != DEFAULT_COLLISION_DISTANCE)
		{
			return TRUE;
		}
	}

	int i, j;
	i = (int)(vPos.x / TILE_SIZE);
	j = (int)(vPos.z / TILE_SIZE);
	if (i >= 0 && i < GetSceneData()->m_pGround->m_projectInfo.sXSize && j >= 0 && j < GetSceneData()->m_pGround->m_projectInfo.sYSize)
	{
		int k = (i * GetSceneData()->m_pGround->m_projectInfo.sYSize + j);

		// 2005-04-06 by jschoi
//		return g_pGround->m_pTileInfo[k].useWater;
		return GetSceneData()->m_pGround->m_pTileInfo[k].dwWaterType == 1 ? TRUE : FALSE;
	}

	return FALSE;
}

float OldSchoolRivalsAPI::CheckHeightMap(CBackground* background, D3DXVECTOR3 vPos)
{
	if (IsTileMapRenderEnable(m_atumapplication->m_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex) == FALSE)
	{
		// 2006-06-07 by ispark, 동굴맵에서는 맵 체크 안함
		return 0.0f;
	}
	//	FLOAT fBary1, fBary2;
	FLOAT fDist;
	int i, j;
	i = (int)(vPos.x / TILE_SIZE);
	j = (int)(vPos.z / TILE_SIZE);
	D3DXVECTOR3 v, dir;
	dir = D3DXVECTOR3(0, -1, 0);
	if (i >= 0 && i < background->m_projectInfo.sXSize && j >= 0 && j < background->m_projectInfo.sYSize)
	{
		BOOL bIsWater = CheckIsWater(m_atumapplication->m_pShuttleChild, vPos);
		if (IntersectTriangle(background, vPos, dir, background->m_pTileVertexArray[i * (background->m_projectInfo.sYSize + 1) + j].pos,
			background->m_pTileVertexArray[i * (background->m_projectInfo.sYSize + 1) + (j + 1)].pos,
			background->m_pTileVertexArray[(i + 1) * (background->m_projectInfo.sYSize + 1) + (j)].pos,
			&fDist))//, &fBary1, &fBary2 ))
		{
			v = vPos + dir * fDist;
			if (bIsWater)
			{
				if (v.y > background->m_projectInfo.fWaterHeight)
				{
					return v.y;
				}
				else
				{
					return background->m_projectInfo.fWaterHeight;
				}
			}
			else
			{
				return v.y;
			}
		}
		else if (IntersectTriangle(background, vPos, dir, background->m_pTileVertexArray[i * (background->m_projectInfo.sYSize + 1) + j + 1].pos,
			background->m_pTileVertexArray[(i + 1) * (background->m_projectInfo.sYSize + 1) + (j)].pos,
			background->m_pTileVertexArray[(i + 1) * (background->m_projectInfo.sYSize + 1) + j + 1].pos,
			&fDist))//, &fBary1, &fBary2 ))
		{
			v = vPos + dir * fDist;
			if (bIsWater)
			{
				if (v.y > background->m_projectInfo.fWaterHeight)
				{
					return v.y;
				}
				else
				{
					return background->m_projectInfo.fWaterHeight;
				}
			}
			else
			{
				return v.y;
			}
		}
	}
	else
	{
		// 좌표가 맵체크에서 벗어났을때 터지게 만든다.
		return 1000.0f;
	}
	// 좌표가 맵체크에서 벗어났을때 터지게 만든다.
	return 1000.0f;
}

BOOL OldSchoolRivalsAPI::IntersectTriangle(CBackground* background, const D3DXVECTOR3& orig, const D3DXVECTOR3& dir, D3DXVECTOR3& v0, D3DXVECTOR3& v1, D3DXVECTOR3& v2, FLOAT* t)
{
	float u, v;
	// Find vectors for two edges sharing vert0
	D3DXVECTOR3 edge1 = v1 - v0;
	D3DXVECTOR3 edge2 = v2 - v0;

	// Begin calculating determinant - also used to calculate U parameter
	D3DXVECTOR3 pvec;
	D3DXVec3Cross(&pvec, &dir, &edge2);

	// If determinant is near zero, ray lies in plane of triangle
	FLOAT det = D3DXVec3Dot(&edge1, &pvec);

	D3DXVECTOR3 tvec;
	if (det > 0)
	{
		tvec = orig - v0;
	}
	else
	{
		tvec = v0 - orig;
		det = -det;
	}

	if (det < 0.0001f)
		return FALSE;

	// Calculate U parameter and test bounds
	u = D3DXVec3Dot(&tvec, &pvec);
	if (u < 0.0f || u > det)
		return FALSE;

	// Prepare to test V parameter
	D3DXVECTOR3 qvec;
	D3DXVec3Cross(&qvec, &tvec, &edge1);

	// Calculate V parameter and test bounds
	v = D3DXVec3Dot(&dir, &qvec);
	if (v < 0.0f || u + v > det)
		return FALSE;

	// Calculate t, scale parameters, ray intersects triangle
	*t = D3DXVec3Dot(&edge2, &qvec);
	FLOAT fInvDet = 1.0f / det;
	*t *= fInvDet;
	//	*u *= fInvDet;
	//	*v *= fInvDet;

	return TRUE;
}
