#include "osrb_pch.h"
#include "AntiMTRand.h"
#include "MTRandSimulator.h"

#include "nlohmann/json.hpp"
#include "PersistingTools.h"
#include "Utility.h"

#include "SDK/AtumError.h"

#include <string>


#define COLOR_GREEN (ImColor(0x00, 0xFF, 0x00).Value) // green
#define COLOR_RED	(ImColor(0xFF, 0x00, 0x00).Value) // red

using namespace Features;

AntiMTRandBot::AntiMTRandBot(OSRBuddyMain* buddy) : BuddyFeatureBase(buddy)
{
	m_seed = ANTIRAND_SEED;
	m_sequence_search_start = 0;
	m_sequence_search_length = ANTIMTRAND_GENERATED_SEQUENCE_LENGTH;
	m_mtrandsim = std::make_unique<MTRandSimulator>(m_seed);
	m_randomhelper = std::make_unique<RandomBreakHelper>();
	m_mtrandsim->GenerateRandomSequence(ANTIMTRAND_GENERATED_SEQUENCE_LENGTH);
	m_in_seq = false;
	m_current_entropy = 0.0f;
	m_current_enchant_target = 0;
	m_next_numbers.clear();
	m_recommended_entropy_buffer = Utility::string_format("%.2f bit", log2(m_sequence_search_length));
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
	ImGui::BeginColumns("AntiMTRandColumns", 2, ImGuiColumnsFlags_NoResize);
	{

		ImGui::Text("Current Seed (Restart: Dienstag, 20. April 2023 17:12:00)");
		ImGui::Text(std::to_string(m_seed).c_str());
		ImGui::NewLine();
		ImGui::InputInt("Search Start", reinterpret_cast<int*>(&m_sequence_search_start));
		if (ImGui::InputInt("Length", reinterpret_cast<int*>(&m_sequence_search_length)))
		{
			m_recommended_entropy_buffer = Utility::string_format("%.2f bit", log2(m_sequence_search_length));
		}
		if (ImGui::Button("Re-Generate"))
		{
			m_mtrandsim->Reset();
			m_mtrandsim->GenerateRandomSequence(m_sequence_search_start + m_sequence_search_length);
		}
		ImGui::NewLine();
		if (!m_logging_active)
		{
			if (ImGui::Button("Start Logging"))
			{
				m_logging_active = true;
				m_enchant_logs.clear();
				m_current_entropy = 0.0f;
				m_current_entropy_buffer = Utility::string_format("%.2f bit", m_current_entropy);
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

		if (ImGui::Button("Save Log"))
		{
			SaveEnchantLog();
		}


		ImGui::Text("Log entries:");
		ImGui::SameLine();
		ImGui::Text(std::to_string(m_enchant_logs.size()).c_str());

		ImGui::Text("Current log entries information:");
		ImGui::SameLine();
		ImGui::Text(m_current_entropy_buffer.c_str());

		ImGui::Text("Minimum recommended information:");
		ImGui::SameLine();
		ImGui::Text(m_recommended_entropy_buffer.c_str());


		if (ImGui::Button("Search"))
		{
			m_seq_search_result = m_randomhelper->SearchEnchantResultSequence(m_mtrandsim.get(), m_enchant_logs, m_sequence_search_start, m_sequence_search_length);
			if (m_seq_search_result.found)
			{
				m_in_seq = true;
				CreateNextRandomNumbersForDisplay(ANTIMTRAND_NEXT_NUMBER_COUNT);
			}
		}
		if (m_in_seq)
		{
			ImGui::Text(std::to_string(m_seq_search_result.sequence_end).c_str());
		}
	}
	ImGui::NextColumn();
	{
		ImGui::Text("Next numbers:");  	
		ImGui::PushStyleColor(ImGuiCol_Text, m_in_seq ? COLOR_GREEN : COLOR_RED);	
		if (m_seq_search_result.found)
		{
			// display the next numbers in the random sequence
			for (auto number : m_next_numbers)
			{
				ImGui::Text(std::to_string(number).c_str());
			}
		}
		ImGui::PopStyleColor();
	}
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
	{
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
	case T_FC_ITEM_MIX_ITEMS_RESULT:
	{
		MSG_FC_ITEM_MIX_ITEMS_RESULT* msg = reinterpret_cast<MSG_FC_ITEM_MIX_ITEMS_RESULT*>(packet);  	
		OnItemMix(msg->Err != ERR_NO_ERROR);
		break;
	}
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
	m_current_entropy_buffer = Utility::string_format("%.2f bit", m_current_entropy);

	if (m_seq_search_result.found)
	{
		uint32_t randnum = m_mtrandsim->GetRandInt32(m_seq_search_result.sequence_end, 0, MAX_RAND10K_VALUE);

		if (success != (randnum <= RandomBreakHelper::GetEnchantProb(er.try_enchant_to)))
		{
			m_in_seq = false;
		}
		CreateNextRandomNumbersForDisplay(ANTIMTRAND_NEXT_NUMBER_COUNT);
	}
}

void Features::AntiMTRandBot::OnItemMix(bool success)
{
	if (m_seq_search_result.found)
	{  		
		// dont care about result here, just pull one number to advance the prng state just like the server
		m_mtrandsim->GetRandInt32(m_seq_search_result.sequence_end, 0, MAX_RAND10K_VALUE); 
		
		CreateNextRandomNumbersForDisplay(ANTIMTRAND_NEXT_NUMBER_COUNT);
	}
}

void Features::AntiMTRandBot::SaveEnchantLog()
{
	auto er_persisting = m_buddy->GetPersistingTools()->GetEnchantResultPeristence();
	er_persisting->Clear();
	nlohmann::json er_log_json;

	for (const auto& result : m_enchant_logs)
	{
		nlohmann::json er;
		er["try_enchant_to"] = result.try_enchant_to;
		er["success"] = result.success;
		er_log_json["EnchantResults"].push_back(er);
		er_log_json["Entropy"] = m_current_entropy;
		er_persisting->Save(er_log_json);
	}
}

void Features::AntiMTRandBot::CreateNextRandomNumbersForDisplay(uint32_t count)
{
	m_next_numbers.clear();
	uint32_t offset = m_seq_search_result.sequence_end;
	for (int i = 0; i < count; i++)
	{
		uint32_t randnum = m_mtrandsim->GetRandInt32(offset, 0, MAX_RAND10K_VALUE);
		m_next_numbers.push_back(randnum);
	}
}
