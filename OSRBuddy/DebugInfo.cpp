#include "osrb_pch.h"
#include "DebugInfo.h"

namespace Features
{
	DebugInfo::DebugInfo(OSRBuddyMain* buddy) : BuddyFeatureBase(buddy)
	{
		m_pdl_timer = BuddyTimer(std::chrono::milliseconds(1000 / AVG_PDL_UPDATES_PER_SECOND));
		ZeroMemory(&m_pdl_current, sizeof(PacketDebugLog));
	}

	DebugInfo::~DebugInfo()
	{
	}

	FeatureType DebugInfo::GetType() const
	{
		return FeatureType::DebugInfo;
	}

	std::string DebugInfo::GetName() const
	{
		return "Debug Info";
	}

	void DebugInfo::Tick()
	{
		m_pdl_current = m_buddy->GetPacketManager()->GetDebugInfo();
		if (m_pdl_timer.IsReady())
		{
			m_pdl_old[m_pdl_old_next_index] = m_pdl_current;
			int last_index = m_pdl_old_next_index++;
			if (m_pdl_old_next_index == AVG_PDL_UPDATES_PER_SECOND) {
				m_pdl_old_next_index = 0;
			}

			m_pdl_last_second.use_skill_sent = m_pdl_old[last_index].use_skill_sent - m_pdl_old[m_pdl_old_next_index].use_skill_sent;
			m_pdl_last_second.cancel_skill_sent = m_pdl_old[last_index].cancel_skill_sent - m_pdl_old[m_pdl_old_next_index].cancel_skill_sent;
			m_pdl_last_second.use_item_sent = m_pdl_old[last_index].use_item_sent - m_pdl_old[m_pdl_old_next_index].use_item_sent;
			m_pdl_last_second.use_energy_sent = m_pdl_old[last_index].use_energy_sent - m_pdl_old[m_pdl_old_next_index].use_energy_sent;
			m_pdl_last_second.throw_away_item_sent = m_pdl_old[last_index].throw_away_item_sent - m_pdl_old[m_pdl_old_next_index].throw_away_item_sent;
			m_pdl_last_second.sell_item_sent = m_pdl_old[last_index].cancel_skill_sent - m_pdl_old[m_pdl_old_next_index].cancel_skill_sent;
			m_pdl_last_second.use_randombox_sent = m_pdl_old[last_index].use_randombox_sent - m_pdl_old[m_pdl_old_next_index].use_randombox_sent;
			m_pdl_last_second.change_window_postion_sent = m_pdl_old[last_index].change_window_postion_sent - m_pdl_old[m_pdl_old_next_index].change_window_postion_sent;
			m_pdl_last_second.total_sent = m_pdl_old[last_index].total_sent - m_pdl_old[m_pdl_old_next_index].total_sent;
			m_pdl_last_second.errors_recieved = m_pdl_old[last_index].errors_recieved - m_pdl_old[m_pdl_old_next_index].errors_recieved;
			m_pdl_last_second.total_recieved = m_pdl_old[last_index].total_recieved - m_pdl_old[m_pdl_old_next_index].total_recieved;

			m_pdl_timer.Reset();
		}
	}

	void DebugInfo::RenderImGui()
	{
		ImGui::NewLine();
		ImGui::BeginChild("PacketInfo", ImVec2(), false);
		{
			ImGui::BeginColumns("PacketInfoColumns", 3, ImGuiColumnsFlags_NoResize);
			{
				ImGui::Text("Packet type sent");
				ImGui::NewLine();
				ImGui::Text("T_FC_SKILL_USE_SKILL");
				ImGui::Text("T_FC_SKILL_CANCEL_SKILL");
				ImGui::Text("T_FC_ITEM_USE_ITEM");
				ImGui::Text("T_FC_ITEM_USE_ENERGY");
				ImGui::Text("T_FC_ITEM_THROW_AWAY_ITEM");
				ImGui::Text("T_FC_SHOP_SELL_ITEM");
				ImGui::Text("T_FC_ITEM_USE_RANDOMBOX");
				ImGui::Text("T_FC_ITEM_CHANGE_WINDOW_POSITION");
				ImGui::Text("All sent:");
				ImGui::NewLine();
				ImGui::Text("Packet type recieved");
				ImGui::NewLine();
				ImGui::Text("T_ERROR");
				ImGui::Text("All recieved:");
			}
			ImGui::NextColumn();
			{
				ImGui::Text("Total count sent");
				ImGui::NewLine();
				ImGui::Text(std::to_string(m_pdl_current.use_skill_sent).c_str());
				ImGui::Text(std::to_string(m_pdl_current.cancel_skill_sent).c_str());
				ImGui::Text(std::to_string(m_pdl_current.use_item_sent).c_str());
				ImGui::Text(std::to_string(m_pdl_current.use_energy_sent).c_str());
				ImGui::Text(std::to_string(m_pdl_current.throw_away_item_sent).c_str());
				ImGui::Text(std::to_string(m_pdl_current.sell_item_sent).c_str());
				ImGui::Text(std::to_string(m_pdl_current.use_randombox_sent).c_str());
				ImGui::Text(std::to_string(m_pdl_current.change_window_postion_sent).c_str());
				ImGui::Text(std::to_string(m_pdl_current.total_sent).c_str());
				ImGui::NewLine();
				ImGui::Text("Total count recieved");
				ImGui::NewLine();
				ImGui::Text(std::to_string(m_pdl_current.errors_recieved).c_str());
				ImGui::Text(std::to_string(m_pdl_current.total_recieved).c_str());
			}
			ImGui::NextColumn();
			{
				ImGui::Text("Last second sent");
				ImGui::NewLine();
				ImGui::Text(std::to_string(m_pdl_last_second.use_skill_sent).c_str());
				ImGui::Text(std::to_string(m_pdl_last_second.cancel_skill_sent).c_str());
				ImGui::Text(std::to_string(m_pdl_last_second.use_item_sent).c_str());
				ImGui::Text(std::to_string(m_pdl_last_second.use_energy_sent).c_str());
				ImGui::Text(std::to_string(m_pdl_last_second.throw_away_item_sent).c_str());
				ImGui::Text(std::to_string(m_pdl_last_second.sell_item_sent).c_str());
				ImGui::Text(std::to_string(m_pdl_last_second.use_randombox_sent).c_str());
				ImGui::Text(std::to_string(m_pdl_last_second.change_window_postion_sent).c_str());
				ImGui::Text(std::to_string(m_pdl_last_second.total_sent).c_str());
				ImGui::NewLine();
				ImGui::Text("Last second recieved");
				ImGui::NewLine();
				ImGui::Text(std::to_string(m_pdl_last_second.errors_recieved).c_str());
				ImGui::Text(std::to_string(m_pdl_last_second.total_recieved).c_str());
			}
			ImGui::EndColumns();
		}
		ImGui::EndChild();
	}
}