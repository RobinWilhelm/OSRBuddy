#include "osrb_pch.h"
#include "AntiMTRand.h"
#include "MTRandSimulator.h"
#include <string>
#include "EnchantBot.h"

#define COLOR_GREEN (ImColor(0x00, 0xFF, 0x00).Value) // green
#define COLOR_RED	(ImColor(0xFF, 0x00, 0x00).Value) // red

using namespace Features;

AntiMTRandBot::AntiMTRandBot(OSRBuddyMain* buddy) : BuddyFeatureBase(buddy)
{
	m_seed = 4160871962;
	m_sequence_search_start = 0;
	m_sequence_search_end = 100000;
	m_mtrandsim = std::make_unique<MTRandSimulator>(m_seed);
	m_randomhelper = std::make_unique<RandomBreakHelper>();
	m_mtrandsim->GenerateRandomSequence(1000000);
	m_in_seq = false;
	m_current_entropy = 0.0f;
	m_current_enchant_target = 0;
}

AntiMTRandBot::~AntiMTRandBot()
{

}

void AntiMTRandBot::Tick()
{

}

void AntiMTRandBot::RenderImGui()
{
	DrawEnableCheckBox();

	ImGui::NewLine();

	ImGui::Text("Current Seed (Restart: 20.12.2021 - 20:03:08");
	ImGui::Text(std::to_string(m_seed).c_str());
	ImGui::InputInt("Search Start", reinterpret_cast<int*>(&m_sequence_search_start));
	ImGui::InputInt("Search End", reinterpret_cast<int*>(&m_sequence_search_end));
	if (!m_logging_active)
	{
		if (ImGui::Button("Start Logging"))
		{
			m_logging_active = true;
			m_enchant_logs.clear();
			m_current_entropy = 0.0f;
			m_seq_search_result.found = false;
		}
	}
	else
	{
		if (ImGui::Button("Stop Logging"))
		{
			m_logging_active = false;
		}
	}

	ImGui::Text("Log entries:");
	ImGui::SameLine();
	ImGui::Text(std::to_string(m_enchant_logs.size()).c_str());

	ImGui::Text("Current log entries entropy:");
	ImGui::SameLine();
	ImGui::Text(std::to_string(m_current_entropy).c_str());

	if (ImGui::Button("Search"))
	{
		m_seq_search_result = m_randomhelper->SearchEnchantResultSequence(m_mtrandsim.get(), m_enchant_logs, m_sequence_search_start);	
		if (m_seq_search_result.found)
		{
			m_in_seq = true;
		}
	}

	if (m_in_seq)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, COLOR_GREEN);
	}
	else
	{
		ImGui::PushStyleColor(ImGuiCol_Text, COLOR_RED);
	}

	if (m_seq_search_result.found)
	{
		ImGui::SameLine();
		ImGui::Text(std::to_string(m_seq_search_result.sequence_end).c_str());
		uint32_t offset = m_seq_search_result.sequence_end;
		for(int i = 0; i < 10; i++)
		{
			ImGui::Text(std::to_string(m_mtrandsim->GetRandInt32(offset, 0, MAX_RAND10K_VALUE)).c_str());
		}
	}

	ImGui::PopStyleColor();
}


std::string AntiMTRandBot::GetName() const
{
	return "AntiRand";
}

FeatureType Features::AntiMTRandBot::GetType() const
{
	return FeatureType::AntiRandomness;
}

bool Features::AntiMTRandBot::OnReadPacket(unsigned short msgtype, byte* packet)
{
	if (!IsEnabled() || !m_logging_active)
	{
		return false;
	}

	switch (msgtype)
	{
	case T_FC_ITEM_USE_ENCHANT_OK:
		MSG_FC_ITEM_USE_ENCHANT_OK* msg = reinterpret_cast<MSG_FC_ITEM_USE_ENCHANT_OK*>(packet);
		CINFCityLab* citylab = static_cast<CINFCityLab*>(OSR_API->FindBuildingShop(BUILDINGKIND_LABORATORY));
		if (!citylab) {
			return nullptr;
		}

		for (auto& item : citylab->m_vecTarget)
		{
			if (IS_ENCHANT_TARGET_ITEMKIND(item->Kind) && item->UniqueNumber == m_current_enchant_target)
			{
				OnEnchant(item, msg->bSuccessFlag);
			}
		}
		break;
	}

	return false;
}

bool Features::AntiMTRandBot::OnWritePacket(unsigned short msgtype, byte* packet)
{
	if (!IsEnabled() || !m_logging_active)
	{
		return false;
	}

	switch (msgtype)
	{
	case T_FC_ITEM_USE_ENCHANT:
	{
		MSG_FC_ITEM_USE_ENCHANT* msg = reinterpret_cast<MSG_FC_ITEM_USE_ENCHANT*>(packet);
		m_current_enchant_target = msg->TargetItemUniqueNumber;
	}
	break;
	}
	return false;
}

void Features::AntiMTRandBot::OnEnchant(CItemInfo* item, bool success)
{
	EnchantResult er;
	er.success = success;
	er.try_enchant_to = item->m_nEnchantNumber + 1; // game has not updated this number yet

	m_enchant_logs.push_back(er);
	float prob = RandomBreakHelper::GetEnchantProb(er.try_enchant_to) / 10000.0f;
	m_current_entropy += (-1) * log2f(success ? prob : 1 - prob);

	if (m_seq_search_result.found)
	{
		uint32_t randnum = m_mtrandsim->GetRandInt32(m_seq_search_result.sequence_end, 0, MAX_RAND10K_VALUE);

		if (success != (randnum <= RandomBreakHelper::GetEnchantProb(er.try_enchant_to)))
		{
			m_in_seq = false;
		}
	}
}
