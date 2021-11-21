#include "TestItemUse.h"
#include <string>
#include "OSRBuddy.h"
#include "OSRAPI.h"
#include "KitBot.h"

#define WEATHER_DEFAULT_FOG_START	50.0f
#define WEATHER_DEFAULT_FOG_END		640.0f
//#define WEATHER_SUNNY_FOG_START		19000.0f//4000.0f
//#define WEATHER_SUNNY_FOG_END		25000.0f//6300.0f
#define WEATHER_RAINY_FOG_START		100.0f
#define WEATHER_RAINY_FOG_END		400.0f
#define WEATHER_SNOWY_FOG_START		1000.0f//0.0f			// 2006-12-11 by ispark
#define WEATHER_SNOWY_FOG_END		1800.0f//600.0f			// 2006-12-11 by ispark
#define WEATHER_CLOUDY_FOG_START	300.0f
#define WEATHER_CLOUDY_FOG_END		2250.0f
#define WEATHER_FOGGY_FOG_START		0.0f
#define WEATHER_FOGGY_FOG_END		200.0f


#define WEATHER_DEFAULT		(BitFlag16_t)0x0000	// 기본
#define WEATHER_SUNNY		(BitFlag16_t)0x0001	// 맑음
#define WEATHER_RAINY		(BitFlag16_t)0x0002	// 비
#define WEATHER_SNOWY		(BitFlag16_t)0x0004	// 눈
#define WEATHER_CLOUDY		(BitFlag16_t)0x0008	// 흐림
#define WEATHER_FOGGY		(BitFlag16_t)0x0010	// 안개

TestItemUse::TestItemUse(OSRBuddyMain* buddy) : BuddyFeatureBase(buddy)
{
}

void TestItemUse::Tick()
{


	/*
	auto scene = osr->GetSceneData();
	scene->m_fChangeWeatherCheckTime = 0;
	scene->m_fOrgFogStartValue = WEATHER_SUNNY_FOG_START;				// 안개 시작지점-거리(실제값)
	scene->m_fOrgFogEndValue = WEATHER_SUNNY_FOG_END;					// 안개 끝지점-거리(질제값)
	scene->m_fFogStartValue = WEATHER_SUNNY_FOG_START;				// 안개 시작지점-거리(현재값)
	scene->m_fFogEndValue = WEATHER_SUNNY_FOG_END;					// 안개 끝지점-거리(현재값)
	//scene->m_fBeforeFogStartValue = WEATHER_SUNNY_FOG_START;			// 방금전의 안개 시작지점-거리
	//scene->m_fBeforeFogEndValue = WEATHER_SUNNY_FOG_END;
	*/
}

void TestItemUse::RenderImGui()
{
	static OldSchoolRivalsAPI* osr = OSR_API;
	auto shuttle = osr->GetAtumApplication()->m_pShuttleChild;
	auto scene = osr->GetAtumApplication()->m_pScene;

	ImGui::NewLine();

	CINFCityLab* lab = static_cast<CINFCityLab*>(OSR_API->FindBuildingShop(BUILDINGKIND_LABORATORY));
	if (lab)
	{
		ImGui::InputInt("LastTime: ", (int*)&lab->m_lasttime);
		ImGui::NewLine();
		int counter = 0;
		for (auto item : lab->m_saved_times)
		{
			std::string elem_str = std::to_string(item);
			ImGui::Text(elem_str.c_str());
		}
		ImGui::NewLine();
		
	}


	// test 
	if (ImGui::Button("Use Healing target")) 
	{
		KitBuffBot* kitbot = (KitBuffBot*)m_buddy->GetFeatureByType(FeatureType::KitBuffBot);
		if (kitbot)
		{
			PlayerSkillInfo* pskill = kitbot->FindPlayerSkill(SkillType::Heal_Target);
			kitbot->TryUseSkill(pskill);

			auto skill = OSR_API->GetAtumApplication()->m_pShuttleChild->m_pSkill;
			skill->m_bSkillTargetState = FALSE;
			skill->m_nTargetIndex = OSR_API->GetAtumApplication()->m_pShuttleChild->m_myShuttleInfo.ClientIndex;
		}
	}

	if(m_item_reattack > 0)
		m_item_reattack -= static_cast<int>(osr->GetElapsedTime());

	static std::string test1;
	test1 = std::to_string(osr->GetAtumApplication()->m_dwInetAnticheatCheckTime);

	static std::string test2;
	test2 = std::to_string(osr->GetAtumApplication()->m_dwInetAnticheatCheckTime2);


	ImGui::Text(test1.c_str());
	ImGui::Text(test2.c_str());


	ImGui::Checkbox("Active", &m_active_switch);
	ImGui::InputInt("Item Number", &m_input_itemnumber);
	
	ImGui::Checkbox("Fog", (bool*)&osr->GetSceneData()->m_bFog);
	if(ImGui::Button("RemoveFog"))
	{
		auto scene = osr->GetSceneData();
		scene->m_dwFogColor = D3DCOLOR_ARGB(0,0,0,0);					// 안개색
		//scene->m_fOrgFogStartValue = WEATHER_SUNNY_FOG_START;				// 안개 시작지점-거리(실제값)
		//scene->m_fOrgFogEndValue = WEATHER_SUNNY_FOG_END;					// 안개 끝지점-거리(질제값)
		//scene->m_fFogStartValue = WEATHER_SUNNY_FOG_START;				// 안개 시작지점-거리(현재값)
		//scene->m_fFogEndValue = WEATHER_SUNNY_FOG_END;					// 안개 끝지점-거리(현재값)
		//scene->m_fBeforeFogStartValue = WEATHER_SUNNY_FOG_START;			// 방금전의 안개 시작지점-거리
		//scene->m_fBeforeFogEndValue = WEATHER_SUNNY_FOG_END;
	}
	osr->GetSceneData()->m_dwFogColor = D3DCOLOR_ARGB(0, 0, 0, 0);

	static bool movemouse = false;
	ImGui::Checkbox("Move Mouse Test", &movemouse);
	if (movemouse)
	{
		POINT curPos;
		GetCursorPos(&curPos); 

		uint32_t new_x = 1;
		uint32_t new_y = 0;

		Utility::MoveMouse(new_x, new_y);
	}



	if (ImGui::Button("Check Availability"))
	{
		m_item = osr->FindItemInInventoryByItemNum(m_input_itemnumber);
		m_item_reattack = 0;
	}
	
	if (m_item) {
		// recheck item availability
		if (m_item->m_pRefPrefixRareInfo) {
			std::string prefix = std::string(m_item->m_pRefPrefixRareInfo->Name);
			ImGui::Text(prefix.c_str());  
		}
		ImGui::SameLine(); 		
		ImGui::Text(m_item->m_pItemInfo->ItemName);
		ImGui::SameLine();
		if (m_item->m_pRefSuffixRareInfo) {
			std::string suffix = std::string(m_item->m_pRefSuffixRareInfo->Name);
			ImGui::Text(suffix.c_str());
		}
		
		if (m_item && ImGui::Button("Use Item"))
		{
			bool del_item = false;
			if (m_item->CurrentCount == 1)
				del_item = true;
			osr->SendUseItem(m_item);
			if (del_item) {
				m_item = nullptr;
				return;
			}
			m_item_reattack = m_item->m_pItemInfo->ReAttacktime;
		}
		
		if (m_item && ImGui::Button("Put Item in Lab"))
		{ 
			osr->InvenToSourceItem(m_item, 1, false);
			m_item = nullptr; 			
		}
	}
	if(ImGui::Button("Reset item in lab")) {
		m_item_in_lab = false;
	}
	ImGui::SameLine();
	if (ImGui::Button("Simulate Button 0")) {
		osr->OnButtonClick(0);
	}
	ImGui::SameLine();
	if (ImGui::Button("Simulate Button 1")) {
		osr->OnButtonClick(1);
	}
	ImGui::SameLine();	

	if (ImGui::Button("Simulate Button 2")) {
		osr->OnButtonClick(2);
	}

	if (ImGui::Button("Find RareItem")) {
		m_rif = osr->GetServerRareItemInfo(m_input_itemnumber);
	}
	if (m_rif) {
		ImGui::Text(m_rif->Name);
	}


	if (ImGui::Button("Dump all RareItem")) 
	{
		FILE* fd;
		fopen_s(&fd, "rareitems.csv", "w");
		if (fd) {
			DumpRareItemInfoToFile(fd);
			fclose(fd);
			MessageBox(0, "Finished", "Dump all RareItem", 0);
		}
	}

	if (ImGui::Button("Save Mystery Info")) 
	{
		FILE* fd;
		fopen_s(&fd, "mystery.csv", "w");
		if (fd) {
			SaveMysterInfoToFile(fd);
			fclose(fd);
			MessageBox(0, "Finished", "Save Mistery Info", 0);
		}
	}


	ImGui::NewLine();
	ImGui::Text("mousedir");
	CShuttleChild* shuttlechild = OSR_API->GetAtumApplication()->m_pShuttleChild;

	ImGui::InputFloat("mousedir_x", &shuttlechild->m_vMouseDir.x);
	ImGui::InputFloat("mousedir_y", &shuttlechild->m_vMouseDir.y);
	ImGui::InputFloat("mousedir_z", &shuttlechild->m_vMouseDir.z);

	/*
	ImGui::Text(mousedir_x.c_str());
	ImGui::Text(mousedir_y.c_str());
	ImGui::Text(mousedir_z.c_str());
	*/
	ImGui::Text("mousepos");
	std::string mousepos_x = std::to_string(shuttlechild->m_vMousePos.x);
	std::string mousepos_y = std::to_string(shuttlechild->m_vMousePos.y);
	std::string mousepos_z = std::to_string(shuttlechild->m_vMousePos.z);

	ImGui::Text(mousepos_x.c_str());
	ImGui::Text(mousepos_y.c_str());
	ImGui::Text(mousepos_z.c_str());
}

std::string TestItemUse::GetName() const
{
	return "Test";
}

void TestItemUse::DumpRareItemInfoToFile(FILE* fd)
{
	std::vector<RARE_ITEM_INFO*> rareitems;

	for (int i = 0; i < 10000; i++)
	{
		RARE_ITEM_INFO* ri = OSR_API->GetServerRareItemInfo(i);
		Sleep(20);
		if (ri)
		{
			rareitems.push_back(ri);
		}
	}

	std::string header = "CodeNum,Name,ReqUseType,ReqMinLevel,ReqMaxLevel,ReqItemKind,Probability";
	fwrite(header.c_str(), header.size(), 1, fd);
	fwrite("\n", sizeof(char), 1, fd);

	std::vector<RARE_ITEM_INFO*>::iterator it = rareitems.begin();
	while (it != rareitems.end())
	{
		RARE_ITEM_INFO* rareItem = *it;
		std::string line = std::string() + std::to_string(rareItem->CodeNum) + "," + rareItem->Name + "," + std::to_string(rareItem->ReqUseType) + "," + std::to_string(rareItem->ReqMinLevel) + "," + std::to_string(rareItem->ReqMaxLevel) + "," + std::to_string(rareItem->ReqItemKind) + "," + std::to_string(rareItem->Probability);

		fwrite(line.c_str(), line.size(), 1, fd);
		fwrite("\n", sizeof(char), 1, fd);
		it++;
	}
}

FeatureType TestItemUse::GetType() const
{
	return FeatureType::TestItemUse;
}

void TestItemUse::SaveMysterInfoToFile(FILE* fd)
{
	CAtumDatabase* db = OSR_API->GetDatabase();
	std::string header = "MysteryItemDropNum,ReqUnitKind,ReqMinLevel,ReqMaxLevel,DropItemNum,MinCount,MaxCount,Probability,PrefixProbability,SuffixProbability,Period,CountPerPeriod,DropCount,Starttime";
	fwrite(header.c_str(), header.size(), 1, fd);
	fwrite("\n", sizeof(char), 1, fd);

	CVectorMysteryItemDropIterator it = db->m_VecMysteryItem.begin();
	while (it != db->m_VecMysteryItem.end())
	{
		MYSTERY_ITEM_DROP* pMysterIntmDropInfo = *it;
		std::string line = std::string() + std::to_string(pMysterIntmDropInfo->MysteryItemDropNum) + "," + std::to_string(pMysterIntmDropInfo->ReqUnitKind) + "," + std::to_string(pMysterIntmDropInfo->ReqMinLevel) + "," + std::to_string(pMysterIntmDropInfo->ReqMaxLevel) + "," + std::to_string(pMysterIntmDropInfo->DropItemNum) + "," + std::to_string(pMysterIntmDropInfo->MinCount) + "," + std::to_string(pMysterIntmDropInfo->MaxCount) + "," + std::to_string(pMysterIntmDropInfo->Probability) + "," + std::to_string(pMysterIntmDropInfo->PrefixProbability) + "," + std::to_string(pMysterIntmDropInfo->SuffixProbability) + "," + std::to_string(pMysterIntmDropInfo->Period) + "," + std::to_string(pMysterIntmDropInfo->CountPerPeriod) + "," + std::to_string(pMysterIntmDropInfo->DropCount) + "," + std::to_string(pMysterIntmDropInfo->Starttime.Year) + std::to_string(pMysterIntmDropInfo->Starttime.Month) + std::to_string(pMysterIntmDropInfo->Starttime.Day) + std::to_string(pMysterIntmDropInfo->Starttime.Hour) + std::to_string(pMysterIntmDropInfo->Starttime.Minute) + std::to_string(pMysterIntmDropInfo->Starttime.Second);

		fwrite(line.c_str(), line.size(), 1, fd);
		fwrite("\n", sizeof(char), 1, fd);
		it++;
	}
}
