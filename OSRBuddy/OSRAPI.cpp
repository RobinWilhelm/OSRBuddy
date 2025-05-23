#include "osrb_pch.h"
#include "OSRAPI.h"

#include "Utility.h"
#include "PatternManager.h"

#include "SDK/AtumApplication.h"
#include "SDK/SceneData.h"

#include "OSRBuddy.h"
#include "IOPacketManager.h"


class CINFInven;

#define SIZE_MAX_ADDABLE_INVENTORY_COUNT 150
#define SIZE_MAX_ITEM_GENERAL 60
#define COUNT_IN_MEMBERSHIP_ADDED_INVENTORY	40

using SendUseItemType = void(__thiscall*)(CINFInvenExtend * ecx, ITEM_BASE * item);
using SendUseSkillType = void(__stdcall*)(ITEM_BASE* skill);
using OnButtonClickType = void(__thiscall*)(CINFCityLab * ecx, int button);
using InvenToSourceItemType = void(__thiscall*)(CINFCityLab * ecx, CItemInfo * pItemInfo, int nCount, bool useMacroSource);
using GetServerRareItemInfoType = RARE_ITEM_INFO * (__thiscall*)(CAtumDatabase * ecx, int nCodeNum);
using ChangeSkillState = void(__thiscall*)(CSkillInfo * ecx, int dwState, int nTempSkillItemNum);
using CalcObjectSourceScreenCoordsType = void(__stdcall*)(float x, float y, float z, int iScreenWidth, int iScreenHeight, int& iCoordX, int& iCoordY, int& iCoordW);
using DeleteSelectItemType = void(__thiscall*)(CINFInvenExtend * ecx, int count);
using SendChangeWearWindowPosType = void(__thiscall*)(CINFInvenExtend* ecx, int nWindowPosition);
using SetSelectItemType = void(__thiscall*)(CINFInven* ecx, INVEN_DISPLAY_INFO* pDisplayInfo);
using UpdateItemCountType = void(__stdcall*)(UID64_t nUniqueNumber, INT nCount, DWORD unknown);
using GetServerItemInfoType = ITEM * (__thiscall*)(CAtumDatabase* ecx, int nItemNum);
using RqInvitePartyInfoType = void(__fastcall*)(CINFCommuPartyInvite* ecx);


OldSchoolRivalsAPI* OldSchoolRivalsAPI::instance  = nullptr;

bool OldSchoolRivalsAPI::CreateAndCheckConsistence(IOPacketManager* packetmanager)
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
#ifndef RELEASE_DEBUG
	if (!COMPARE_INFLUENCE(atumapplication->m_pShuttleChild->m_myShuttleInfo.InfluenceType, INFLUENCE_TYPE_ANI)) {
		return false;
	}
#endif
		  
	// Create game API and return  
	OldSchoolRivalsAPI::instance = new OldSchoolRivalsAPI();
	OldSchoolRivalsAPI::instance->m_atumapplication	= atumapplication;
	OldSchoolRivalsAPI::instance->m_packetmanager = packetmanager;
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

CIMSocket* OldSchoolRivalsAPI::GetIMSocket(UINT nSocketNotifyType)
{
	if (WM_IM_ARENA_NOTIFY == nSocketNotifyType)
	{
		return m_atumapplication->m_pIMSocket->m_pArenaIMSocket;
	}
	return m_atumapplication->m_pIMSocket->m_pMainIMSocket;
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

FLOAT OldSchoolRivalsAPI::GetCurrentEnergy()
{
	return TO_INT(m_atumapplication->m_pShuttleChild->m_fNextHP);
}

FLOAT OldSchoolRivalsAPI::GetCurrentShield()
{
	return TO_INT(m_atumapplication->m_pShuttleChild->m_fNextDP);
}

SHORT OldSchoolRivalsAPI::GetMaxEnergy()
{
	return m_atumapplication->m_pShuttleChild->m_myShuttleInfo.HP;
}

SHORT OldSchoolRivalsAPI::GetMaxShield()
{
	return m_atumapplication->m_pShuttleChild->m_myShuttleInfo.DP;
}

FLOAT OldSchoolRivalsAPI::GetCurrentSkillp()
{
	return TO_INT(m_atumapplication->m_pShuttleChild->m_fNextSP);
}

FLOAT OldSchoolRivalsAPI::GetCurrentFuel()
{
	return TO_INT(m_atumapplication->m_pShuttleChild->m_fNextEP);
}

SHORT OldSchoolRivalsAPI::GetMaxSkillp()
{
	return m_atumapplication->m_pShuttleChild->m_myShuttleInfo.SP;
}

SHORT OldSchoolRivalsAPI::GetMaxFuel()
{
	return m_atumapplication->m_pShuttleChild->m_myShuttleInfo.EP;
}
	  	   
CItemInfo* OldSchoolRivalsAPI::GetRadarItemInfo()
{
	return m_atumapplication->m_pShuttleChild->m_pRadarItemInfo;
}

int OldSchoolRivalsAPI::GetPrimaryWeaponAmmo()
{
	if (!GetPrimaryWeapon())
	{
		// no weapon equipped
		return -1;
	}
	return m_atumapplication->m_pShuttleChild->m_pPrimaryWeapon->m_pItemInfo->CurrentCount;
}

int OldSchoolRivalsAPI::GetSecondaryWeaponAmmo()
{
	if (!GetSecondaryWeapon())
	{
		// no weapon equipped
		return -1;
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

float OldSchoolRivalsAPI::GetRadarRangePrimary(float paramfactors)
{
	CItemInfo* radar = GetRadarItemInfo();
	if (!radar) {
		return 0.0f;
	}	 
	float range = radar->m_pItemInfo->AbilityMin;
	return (range *= paramfactors);
}

float OldSchoolRivalsAPI::GetRadarRangePrimaryParamfactors()
{
	return 1.0f + m_atumapplication->m_pShuttleChild->m_paramFactor.pfm_ATTACK_RANGE_01;
}

float OldSchoolRivalsAPI::GetRadarRangeSecondary(float paramfactors)
{
	CItemInfo* radar = GetRadarItemInfo();
	if (!radar) {
		return 0.0f;
	}
	float range = radar->m_pItemInfo->AbilityMax;
	return (range *= paramfactors);
}

float OldSchoolRivalsAPI::GetRadarRangeSecondaryParamfactors()
{
	return 1.0f + m_atumapplication->m_pShuttleChild->m_paramFactor.pfm_ATTACK_RANGE_02;
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

CUnitData* OldSchoolRivalsAPI::GetTarget()
{
	return (CUnitData*)m_atumapplication->m_pShuttleChild->m_pOrderTarget;
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

						pdeCur = 0;
						if (pObjectMonster->m_pObjMesh) {
							pdeCur = pObjectMonster->m_pObjMesh->m_pdeHead;
						}

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
					if (pObjectMonster->m_pObjMesh)
					{
						pObjectMonster->m_pObjMesh->m_mWorld = pObjectMonster->m_mMatrix;
					}

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
#ifdef CHRISTMAS_EVENT
#pragma optimize( "", off )
#endif //  CHRISTMAS_EVENT

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
#ifdef CHRISTMAS_EVENT
#pragma optimize( "", on ) 
#endif
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

	return GearType::Unknown;
}

MapIndex OldSchoolRivalsAPI::GetCurrentMap()
{
	switch (GetCurrentMapChannelIndex().MapIndex)
	{
		case 9002: return MapIndex::WatermelonIsland;
		case 9050: return MapIndex::InvasionWorld;
		case 9007: return MapIndex::XMAS_Event_Map_ANI;
		default:
			return MapIndex::Unknown;
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

BYTE OldSchoolRivalsAPI::GetCurrentBuildingKind()
{
	return m_atumapplication->m_pInterface->m_pCityBase->m_pCurrentBuildingNPC ? m_atumapplication->m_pInterface->m_pCityBase->m_pCurrentBuildingNPC->buildingInfo.BuildingKind : BUILDINGKIND_NO_BUILDING;
}

BUILDINGNPC OldSchoolRivalsAPI::GetCurrentBuilding()
{
	return m_atumapplication->m_pInterface->m_pCityBase->m_pCurrentBuildingNPC ? m_atumapplication->m_pInterface->m_pCityBase->m_pCurrentBuildingNPC->buildingInfo : BUILDINGNPC();
}

CINFBase* OldSchoolRivalsAPI::FindBuildingShop(int buildingkind)
{
	CINFCityBase* citybase = m_atumapplication->m_pInterface->m_pCityBase;
	if (!citybase) {
		return nullptr;
	}

	CMapCityShopIterator it = citybase->m_mapCityShop.find(buildingkind);
	if (it != citybase->m_mapCityShop.end())
	{
		return it->second;
	}	
	return nullptr;
}

void OldSchoolRivalsAPI::OnButtonClick(int button, bool factory)
{
	static OnButtonClickType onButtonClickFn = reinterpret_cast<OnButtonClickType>(PatternManager::Get(OffsetIdentifier::CINFCityLab__OnButtonClicked).address);
	CINFCityLab* citylab = static_cast<CINFCityLab*>((factory) ? FindBuildingShop(BUILDINGKIND_FACTORY) : FindBuildingShop(BUILDINGKIND_LABORATORY));;
	if (onButtonClickFn && citylab) {
		onButtonClickFn(citylab, button);
	}
}

void OldSchoolRivalsAPI::InvenToSourceItem(CItemInfo* pItemInfo, int nCount, bool factory, bool useMacroSource)
{
	static InvenToSourceItemType invenToSourceItemFn = reinterpret_cast<InvenToSourceItemType>(PatternManager::Get(OffsetIdentifier::CINFCityLab__InvenToSourceItem).address);
	CINFCityLab* citylab = static_cast<CINFCityLab*>((factory) ? FindBuildingShop(BUILDINGKIND_FACTORY) : FindBuildingShop(BUILDINGKIND_LABORATORY));
	if (invenToSourceItemFn && citylab) {
		invenToSourceItemFn(citylab, pItemInfo, nCount, useMacroSource);
	}
}

CItemInfo* OldSchoolRivalsAPI::FindItemFromTarget(UID64_t UniqueNumber)
{
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
	return nullptr;
}

CItemInfo* OldSchoolRivalsAPI::FindItemFromTarget(INT itemnum)
{
	CINFCityLab* citylab = static_cast<CINFCityLab*>(FindBuildingShop(BUILDINGKIND_LABORATORY));
	if (!citylab) {
		return nullptr;
	}

	vector<CItemInfo*>::iterator it = citylab->m_vecTarget.begin();
	while (it != citylab->m_vecTarget.end())
	{
		if (itemnum == (*it)->ItemNum)
		{
			return (*it);
		}
		it++;
	}
	return nullptr;
}

CItemInfo* OldSchoolRivalsAPI::FindItemFromSource(UID64_t UniqueNumber)
{
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
	return nullptr;
}

CItemInfo* OldSchoolRivalsAPI::FindItemFromSource(INT itemnum)
{
	CINFCityLab* citylab = static_cast<CINFCityLab*>(FindBuildingShop(BUILDINGKIND_LABORATORY));
	if (!citylab) {
		return nullptr;
	}

	vector<CItemInfo*>::iterator it = citylab->m_vecSource.begin();
	while (it != citylab->m_vecSource.end())
	{
		if (itemnum == (*it)->ItemNum)
		{
			return (*it);
		}
		it++;
	}
	return nullptr;
}

INVEN_DISPLAY_INFO* OldSchoolRivalsAPI::GetSelectedItem()
{
	 return m_atumapplication->m_pInterface->m_pGameMain->m_stSelectItem.pSelectItem;
}

void OldSchoolRivalsAPI::SendUseItem(ITEM_GENERAL* item)
{
	static SendUseItemType sendUseItemFn = reinterpret_cast<SendUseItemType>(PatternManager::Get(OffsetIdentifier::CINFInvenExtend__SendUseItem).address);
	CINFInvenExtend* inven = m_atumapplication->m_pInterface->m_pGameMain->m_pInven;
	if (sendUseItemFn && inven)
	{
		sendUseItemFn(inven, static_cast<ITEM_BASE*>(item));
	}  	
}

void OldSchoolRivalsAPI::DeleteItem(ITEM_GENERAL* item, int count)
{
	static DeleteSelectItemType deleteSelectItemFn = reinterpret_cast<DeleteSelectItemType>(PatternManager::Get(OffsetIdentifier::CINFInvenExtend__DeleteSelectItem).address);
	CINFInvenExtend* inven = m_atumapplication->m_pInterface->m_pGameMain->m_pInven;
	if (deleteSelectItemFn && inven && item && count > 0)
	{
		structDelItemInfo buffer = inven->m_struDeleteItem;
		ZeroMemory(&inven->m_struDeleteItem, sizeof(structDelItemInfo));

		inven->m_struDeleteItem.UniqueNumber = item->UniqueNumber;
		inven->m_struDeleteItem.CurrentCount = item->CurrentCount;

		deleteSelectItemFn(inven, count);

		inven->m_struDeleteItem = buffer;
	}
}

void OldSchoolRivalsAPI::SendUseSkill(ITEM_BASE* skill)
{
	static SendUseSkillType sendUseSkillFn = reinterpret_cast<SendUseSkillType>(PatternManager::Get(OffsetIdentifier::CINFCharacterInfoExtend__SendUseSkill).address);
	//CINFCharacterInfoExtend* charinfo = m_atumapplication->m_pInterface->m_pGameMain->m_pCharacterInfo;
	if (sendUseSkillFn) {
		sendUseSkillFn(static_cast<ITEM_BASE*>(skill));
	}
}

CItemInfo* OldSchoolRivalsAPI::FindItemInInventoryByItemNum(INT itemnum, bool find_lowest_time)
{
	CStoreData* storedata = m_atumapplication->m_pShuttleChild->m_pStoreData;
	if (!storedata) {
		return nullptr;
	}

	float passtime = -1.0f;
	CItemInfo* lowest_time_item = nullptr;
	CMapItemInventoryIterator it = storedata->m_mapItemUniqueNumber.begin();
	while (it != storedata->m_mapItemUniqueNumber.end())
	{
		if (it->second->ItemNum == itemnum)
		{
			if (find_lowest_time)
			{
			   if(it->second->m_fItemPassTime > passtime)
			   {
				   passtime = it->second->m_fItemPassTime;
				   lowest_time_item = it->second;
			   }
			}
			else {
				return it->second;
			}
		}
		it++;
	}

	if (find_lowest_time) {
		return lowest_time_item;
	}
	return nullptr;
}

CItemInfo* OldSchoolRivalsAPI::FindItemInInventoryByItemNum(ItemNumber itemnum, bool find_lowest_time)
{
	return FindItemInInventoryByItemNum(TO_INT(itemnum), find_lowest_time);
}

CItemInfo* OldSchoolRivalsAPI::FindItemInInventoryByUniqueNumber(UID64_t hyUniqueNumber)
{
	CStoreData* storedata = m_atumapplication->m_pShuttleChild->m_pStoreData;
	if (!storedata) {
		return nullptr;
	}

	CMapItemInventoryIterator it = storedata->m_mapItemUniqueNumber.find(hyUniqueNumber);
	if (it != storedata->m_mapItemUniqueNumber.end())
	{
		return it->second;
	}
	return nullptr;
}

uint32_t OldSchoolRivalsAPI::GetInventoryItemCount(INT itemnum)
{
	CStoreData* storedata = m_atumapplication->m_pShuttleChild->m_pStoreData;
	if (!storedata) {
		return 0;
	}

	uint32_t item_counter = 0;
	CMapItemInventoryIterator it = storedata->m_mapItemUniqueNumber.begin();
	while (it != storedata->m_mapItemUniqueNumber.end())
	{
		if (it->second->ItemNum == itemnum)
		{
			if (IS_COUNTABLE_ITEM(it->second->Kind) || IS_SPECIAL_COUNTABLE_ITEM(it->second->Kind))
			{
				return it->second->CurrentCount;
			}
			else
			{
				item_counter++;
			}
		}
		it++;
	}
	return item_counter;
}

void OldSchoolRivalsAPI::UpdateItemCount(UID64_t nUniqueNumber, INT nCount)
{
	static 	UpdateItemCountType updateItemCountFn = reinterpret_cast<UpdateItemCountType>(PatternManager::Get(OffsetIdentifier::CStoreData__UpdateItemCount).address);
	//CStoreData* storedata = m_atumapplication->m_pShuttleChild->m_pStoreData;
	if (updateItemCountFn )
	{
		updateItemCountFn(nUniqueNumber, nCount, 0);
	}
}

RARE_ITEM_INFO* OldSchoolRivalsAPI::GetServerRareItemInfo(int nCodeNum)
{
	static GetServerRareItemInfoType getServerRareItemInfoFn = reinterpret_cast<GetServerRareItemInfoType>(PatternManager::Get(OffsetIdentifier::CAtumDatabase__GetServerRareItemInfo).address);
	CAtumDatabase* database = m_atumapplication->m_pDatabase;
	RARE_ITEM_INFO* rif = nullptr;
	if (getServerRareItemInfoFn && database) {
		rif = getServerRareItemInfoFn(database, nCodeNum);
	}
	return rif;
}

ITEM* OldSchoolRivalsAPI::GetServerItemInfo(int nItemNum)
{
	static GetServerItemInfoType getServerRareItemInfoFn = reinterpret_cast<GetServerItemInfoType>(PatternManager::Get(OffsetIdentifier::CAtumDatabase__GetServerItemInfo).address);
	CAtumDatabase* database = m_atumapplication->m_pDatabase;
	ITEM* item = nullptr;
	if (getServerRareItemInfoFn && database) {
		item = getServerRareItemInfoFn(database, nItemNum);
	}
	return item;
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
	static CalcObjectSourceScreenCoordsType calcObjectSourceScreenCoordsFn = reinterpret_cast<CalcObjectSourceScreenCoordsType>(PatternManager::Get(OffsetIdentifier::CAtumApplication__CalcObjectSourceScreenCoords).address);
	int screen_w;
	if (calcObjectSourceScreenCoordsFn) {
		calcObjectSourceScreenCoordsFn(world.x, world.y, world.z, m_atumapplication->m_d3dsdBackBuffer.Width, m_atumapplication->m_d3dsdBackBuffer.Height, screen_x, screen_y, screen_w);
	}
}

int OldSchoolRivalsAPI::WritePacket(byte* packet, int length)
{
	static CWinSocketWriteType writePacketFn = reinterpret_cast<CWinSocketWriteType>(PatternManager::Get(OffsetIdentifier::CWinSocket__Write).address);
	CWinSocket* winsocket = GetFieldWinSocket();
	if (writePacketFn && winsocket) {
		return writePacketFn(winsocket, reinterpret_cast<LPCSTR>(packet), length);
	}
	return 0;
}

void OldSchoolRivalsAPI::RqInvitePartyInfo()
{
	static RqInvitePartyInfoType rqInvitePartyInfoFn = reinterpret_cast<RqInvitePartyInfoType>(PatternManager::Get(OffsetIdentifier::CINFCommuPartyInvite__RqInvitePartyInfo).address);
	static CINFCommuPartyInvite* partyInvite = m_atumapplication->m_pInterface->m_pGameMain->m_pCommunity->m_pCommuPartyInvite;
	if (rqInvitePartyInfoFn && partyInvite)
	{
		rqInvitePartyInfoFn(partyInvite);
	}
}

bool OldSchoolRivalsAPI::HasPremium()
{
	return true; // fix this
	return m_atumapplication->m_PremiumCardInfo.nCardItemNum1 > 0;
}

uint32_t OldSchoolRivalsAPI::GetMaxInventorySize()
{
	uint32_t invspace = SIZE_MAX_ITEM_GENERAL + min(m_atumapplication->m_pShuttleChild->m_myShuttleInfo.RacingPoint & 0xFF, SIZE_MAX_ADDABLE_INVENTORY_COUNT);
	if (HasPremium()) {
		invspace += COUNT_IN_MEMBERSHIP_ADDED_INVENTORY;
	}
	return invspace;
}

uint32_t OldSchoolRivalsAPI::GetCurrentInventorySize()
{
	return m_atumapplication->m_pShuttleChild->m_pStoreData->m_mapItemUniqueNumber.size();
}

bool OldSchoolRivalsAPI::IsInventoryFull()
{
	return GetCurrentInventorySize() >= GetMaxInventorySize();
}

bool OldSchoolRivalsAPI::IsLanded()
{
	return !OSR_API->GetAtumApplication()->m_pShuttleChild->m_bIsAir;
}

GearType OldSchoolRivalsAPI::UnitKindToGearType(USHORT unitkind)
{
	if (IS_BGEAR(unitkind))
		return GearType::BGear;

	if (IS_IGEAR(unitkind))
		return GearType::IGear;

	if (IS_MGEAR(unitkind))
		return GearType::MGear;

	if (IS_AGEAR(unitkind))
		return GearType::AGear;

	return GearType::Unknown;
}

int OldSchoolRivalsAPI::GetInventorySPI()
{
	return m_atumapplication->m_pInterface->m_pGameMain->m_pInven->m_nItemSpi;
}

UID64_t OldSchoolRivalsAPI::GetSPIUniqueNumber()
{
	return m_atumapplication->m_pInterface->m_pGameMain->m_pInven->m_hyItemSpiUniqueNumber;
}

bool OldSchoolRivalsAPI::IsGoodBossMonster(CMonsterData* monster)
{
	if (monster && monster->m_pMonsterInfo)
	{
		switch (TO_ENUM(MonsterUnitKind, monster->m_pMonsterInfo->MonsterUnitKind))
		{  		
		case MonsterUnitKind::Black_Widow:
		case MonsterUnitKind::Echelon:
		case MonsterUnitKind::Guardian_of_Vatallus:
		case MonsterUnitKind::Unfinished_Ordin:
		case MonsterUnitKind::Messenger:
		case MonsterUnitKind::Energy_Core:
		case MonsterUnitKind::Mountain_Sage:
		case MonsterUnitKind::Mountain_Sage_2:
		case MonsterUnitKind::Mountain_Sage_3:
		case MonsterUnitKind::Pathos:
		case MonsterUnitKind::Pathos_2:
		case MonsterUnitKind::Prog_Military_Base:
		case MonsterUnitKind::Nipar_Bridge:
		case MonsterUnitKind::Shirne:
		case MonsterUnitKind::Shirne_2:
		case MonsterUnitKind::Hornian_Queen:
		case MonsterUnitKind::Hornian_Queen_2:
		case MonsterUnitKind::Hornian_King:
		case MonsterUnitKind::Hornian_King_2:
		case MonsterUnitKind::Hornian_King_3:
		case MonsterUnitKind::Quetzalcoatl:
		case MonsterUnitKind::Gryphon:
		case MonsterUnitKind::Rock_Emperor:
		case MonsterUnitKind::Rock_Emperor_2:
		case MonsterUnitKind::Egma_Schill:
		case MonsterUnitKind::Skadi:
		case MonsterUnitKind::Ordin:
		case MonsterUnitKind::Gigantic_God:
		case MonsterUnitKind::Bishop_Blue:
		case MonsterUnitKind::Bishop_Black:
		case MonsterUnitKind::Bishop_Red:
		case MonsterUnitKind::Sekhmete:
		case MonsterUnitKind::Murena:
		case MonsterUnitKind::Skarish:
		case MonsterUnitKind::Fx_01:
		case MonsterUnitKind::InvasionLeadSpider:
			return true;
		}
	}
	return false;

	// sadly the game is too inconsitent to get the bosses like this:
	/* 	
	if (COMPARE_MPOPTION_BIT(monster->m_pMonsterInfo->MPOption, MPOPTION_BIT_BOSS_MONSTER)
		|| monster->m_pMonsterInfo->MonsterUnitKind == static_cast<int>(MonsterUnitKind::Black_Widow)) // black widow is not marked as a boss
	{
		// ignore some useless bosses
		switch (static_cast<MonsterUnitKind>(monster->m_pMonsterInfo->MonsterUnitKind))
		{
		case MonsterUnitKind::ESP_Crystal:
		case MonsterUnitKind::ESP_Crystal_2:
		case MonsterUnitKind::Crazy_Orbituary:
		case MonsterUnitKind::Cylinder_Control_Panel:
		case MonsterUnitKind::Gigantic_God_Heart:
		case MonsterUnitKind::Gigantic_God_Heart_2:
		case MonsterUnitKind::Shrine_Laboratory:
		case MonsterUnitKind::Shrine_Laboratory_2:
		case MonsterUnitKind::Symbol_of_Vatallus:
			return false;
		}

		return true;
	}

	return false;
	*/
}

bool OldSchoolRivalsAPI::PlayerIsInSellBuilding()
{
	if (OSR_API->IsInBuilding() &&
		(IS_ITEM_SHOP_TYPE(OSR_API->GetCurrentBuilding().BuildingKind) || 
		IS_WARPOINT_SHOP_TYPE(OSR_API->GetCurrentBuilding().BuildingKind)))
	{
		return true;
	}
	return false;
}

void OldSchoolRivalsAPI::SendSellItem(CItemInfo* item, int count)
{
	if (item && count <= item->CurrentCount && PlayerIsInSellBuilding())
	{
		MSG_FC_SHOP_SELL_ITEM sMsg;
		memset(&sMsg, 0x00, sizeof(sMsg));
		char buffer[SIZE_MAX_PACKET];

		if (IS_COUNTABLE_ITEM(item->Kind)) {
			sMsg.Amount = count;
		}
		else {
			sMsg.Amount = 1;
		}
		sMsg.ItemKind = item->Kind;
		sMsg.ItemUniqueNumber = item->UniqueNumber;
		sMsg.BuildingIndex = OSR_API->GetCurrentBuilding().BuildingIndex;
		int nType = T_FC_SHOP_SELL_ITEM;
		memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
		memcpy(buffer + SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
		WritePacket(reinterpret_cast<byte*>(buffer), SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
	}
}

bool OldSchoolRivalsAPI::IsActiveItem(INT itemnumber)
{
	for (auto iteminfo : OSR_API->GetInterface()->m_pGameMain->m_pInfSkill->m_vecItemFontInfo)
	{
		if (itemnumber == iteminfo->pItemInfo->ItemNum) {
			return true;
		}
	}
	return false;
}

bool OldSchoolRivalsAPI::IsActiveItem(ItemNumber itemnumber)
{
	return IsActiveItem(TO_INT(itemnumber));
}

bool OldSchoolRivalsAPI::IsStealthCardActive()
{
	bool stealthcard_active = false;
	for (auto iteminfo : OSR_API->GetInterface()->m_pGameMain->m_pInfSkill->m_vecItemFontInfo)
	{
		// check if a stealth card is active
		switch (TO_ENUM(ItemNumber, iteminfo->pItemInfo->ItemNum))
		{
		case ItemNumber::Mini_Stealth_Card:
		case ItemNumber::Starter_Mini_Stealth_Card:
		case ItemNumber::Stealth_Card_30m:
		case ItemNumber::Stealth_Card_2h:
			stealthcard_active = true;
			break;
		default:
			continue;
		}
		break;
	}
	return stealthcard_active;
}

void OldSchoolRivalsAPI::SendChangeWearWindowPos(int nWindowPosition)
{
	static SendChangeWearWindowPosType sendChangeWearWindowPosFn = reinterpret_cast<SendChangeWearWindowPosType>(PatternManager::Get(OffsetIdentifier::CINFInvenExtend__SendChangeWearWindowPos).address);
	CINFInvenExtend* inven = m_atumapplication->m_pInterface->m_pGameMain->m_pInven;
	if (sendChangeWearWindowPosFn && inven){
		sendChangeWearWindowPosFn(inven, nWindowPosition);
	}
}

bool OldSchoolRivalsAPI::TryEquipItem(CItemInfo* item)
{
	if (item && !m_packetmanager->ChangeWindowPositionWaitingOk())
	{
		switch (item->ItemInfo->Position)
		{
		case POS_PROWIN:
		case POS_PROWOUT:
		case POS_WINGIN:
		case POS_WINGOUT:
		case POS_PROW:
		case POS_CENTER:
		case POS_REAR:
		case POS_ACCESSORY_UNLIMITED:
		case POS_ACCESSORY_TIME_LIMIT:	// 2006-03-31 by ispark
		case POS_PET:
			stSelectItem buffer = m_atumapplication->m_pInterface->m_pGameMain->m_stSelectItem;
			m_atumapplication->m_pInterface->m_pGameMain->m_stSelectItem = stSelectItem();

			INVEN_DISPLAY_INFO idi;
			idi.pItem = item;
			m_atumapplication->m_pInterface->m_pGameMain->m_stSelectItem.pSelectItem = &idi;
			SendChangeWearWindowPos(item->ItemInfo->Position);
			m_atumapplication->m_pInterface->m_pGameMain->m_stSelectItem = buffer;
			return true;
		}
	}
	return false;
}

ITEM_BASE* OldSchoolRivalsAPI::GetEquippedItem(EQUIP_POS position)
{
	switch (position)
	{
	case POS_PROWIN:
	case POS_PROWOUT:
	case POS_WINGIN:
	case POS_WINGOUT:
	case POS_PROW:
	case POS_CENTER:
	case POS_REAR:
	case POS_ACCESSORY_UNLIMITED:
	case POS_ACCESSORY_TIME_LIMIT:	// 2006-03-31 by ispark
	case POS_PET:
		CINFInvenExtend* inven = m_atumapplication->m_pInterface->m_pGameMain->m_pInven;
		if (inven && inven->m_pWearDisplayInfo[position])
		{
			return inven->m_pWearDisplayInfo[position]->pItem;
		}
	}
	return nullptr;
}

bool OldSchoolRivalsAPI::TrySendUseItem(ITEM_GENERAL* item)
{
	if (!item)	{
		return false;
	}
	
	if (item->ItemInfo->Kind == ITEMKIND_RANDOMBOX) {
		if (m_packetmanager->OpenRandomBoxWaitingOk()) {
			return false;
		} 			
	}
	else {
		if (m_packetmanager->UseItemWaitingOk(item->ItemNum)) {
			return false;
		}
	}

	SendUseItem(item);
	return true;
}

bool OldSchoolRivalsAPI::TrySendUseSkill(ITEM_BASE* skill)
{
	if (!skill || m_packetmanager->UseItemWaitingOk(skill->ItemNum)) {
		return false;
	}

	SendUseSkill(skill);
	return true;
}

bool OldSchoolRivalsAPI::TrySendSellItem(CItemInfo* item, int count)
{
	if (!item || m_packetmanager->SellItemWaitingOk()) {
		return false;
	}

	SendSellItem(item, count);
	return true;
}

bool OldSchoolRivalsAPI::TryDeleteItem(CItemInfo* item, int count)
{
	if (!item || m_packetmanager->DeleteItemWaitingOk()) {
		return false;
	}

	DeleteItem(item, count);
	return true;
}

bool OldSchoolRivalsAPI::IsCountableItem(ITEM* item)
{
	if (item && (IS_COUNTABLE_ITEM(item->Kind) || IS_SPECIAL_COUNTABLE_ITEM(item->Kind)))
	{
		return true;
	}
	return false;
}

bool OldSchoolRivalsAPI::CanInsertItemToInventory(INT itemnum)
{
	if (GetMaxInventorySize() - GetCurrentInventorySize() <= 0)
	{
		// only insert if item is countable	and item is in inventory already
		CItemInfo* iteminfo = FindItemInInventoryByItemNum(itemnum);
		if (!iteminfo || !IsCountableItem(iteminfo->ItemInfo))
		{
			return false;
		}
	}
	return true;
}

bool OldSchoolRivalsAPI::IsStaffMember(const char* charName)
{
	if (!charName) {
		return false;
	}

	char lc_charName[SIZE_MAX_CHARACTER_NAME];
	strcpy_s(lc_charName, SIZE_MAX_CHARACTER_NAME, charName);

	for (auto& c : lc_charName) {
		c = tolower(c);
	}

	if (strstr(lc_charName, "romu"))			return true;
	if (strstr(lc_charName, "inetpub"))			return true;
	if (strstr(lc_charName, "bergi9"))			return true;
	if (strstr(lc_charName, "_kube"))			return true;
	if (strstr(lc_charName, "_falcon"))			return true;
	if (strstr(lc_charName, "_rigel"))			return true;
	if (strstr(lc_charName, "_layla_"))			return true;
	if (strstr(lc_charName, "_mangoo_"))		return true;
	if (strstr(lc_charName, "_masteroogway"))	return true;
	if (strstr(lc_charName, "_valkyrie"))		return true;
	if (strstr(lc_charName, "_yearzero"))		return true;

	return false;
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

#ifdef CHRISTMAS_EVENT
#pragma optimize( "", off )
#endif //  CHRISTMAS_EVENT
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
#ifdef CHRISTMAS_EVENT
#pragma optimize( "", on )
#endif //  CHRISTMAS_EVENT

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

	return m_atumapplication->m_pDatabase->m_DefMapInfo.TileRenderingFlag;
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
