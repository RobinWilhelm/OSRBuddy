#include "osrb_pch.h"
#include "DebugInfo.h"

#include "SDK/AtumProtocol.h"

namespace Features
{
	DebugInfo::DebugInfo(OSRBuddyMain* buddy) : BuddyFeatureBase(buddy)
	{
		m_pdl_timer = BuddyTimer(std::chrono::milliseconds(1000 / AVG_PDL_UPDATES_PER_SECOND));
		ZeroMemory(&m_pdl_current, sizeof(PacketDebugLog));
		m_packetlog.resize(UINT16_MAX);
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
		/*
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
		*/

		if (m_pdl_timer.IsReady())
		{
			int last_index = m_pdi_old_next_index++;
			if (m_pdi_old_next_index == AVG_PDL_UPDATES_PER_SECOND) {
				m_pdi_old_next_index = 0;
			}

			for (auto& pdi : m_packetlog)
			{
				if (pdi.count_total == 0) 
				{
					continue;
				}
				pdi.count_old[last_index] = pdi.count_total;
				pdi.count_last_second = pdi.count_old[last_index] - pdi.count_old[m_pdi_old_next_index];
			}

			m_total_recv.count_old[last_index] = m_total_recv.count_total;
			m_total_sent.count_old[last_index] = m_total_sent.count_total;

			m_total_recv.count_last_second = m_total_recv.count_old[last_index] - m_total_recv.count_old[m_pdi_old_next_index];
			m_total_sent.count_last_second = m_total_sent.count_old[last_index] - m_total_sent.count_old[m_pdi_old_next_index];
			m_pdl_timer.Reset();
		}

	}

	void DebugInfo::RenderImGui()
	{
		ImGui::BeginTabBar("DebugInfos", ImGuiTabBarFlags_::ImGuiTabBarFlags_None);
		{
			if (ImGui::BeginTabItem("Network"))
			{
				ImGui::NewLine();
				ImGui::BeginChild("PacketInfo", ImVec2(), false);
				{
					ImGui::BeginColumns("PacketInfoColumns", 3, ImGuiColumnsFlags_NoResize);
					{
						ImGui::SetColumnWidth(0, 350);
						ImGui::SetColumnWidth(1, 150);
						ImGui::SetColumnWidth(2, 150);
						ImGui::Text("Packet type sent");
						ImGui::NewLine();
						/*
						ImGui::Text("T_FC_SKILL_USE_SKILL");
						ImGui::Text("T_FC_SKILL_CANCEL_SKILL");
						ImGui::Text("T_FC_ITEM_USE_ITEM");
						ImGui::Text("T_FC_ITEM_USE_ENERGY");
						ImGui::Text("T_FC_ITEM_THROW_AWAY_ITEM");
						ImGui::Text("T_FC_SHOP_SELL_ITEM");
						ImGui::Text("T_FC_ITEM_USE_RANDOMBOX");
						ImGui::Text("T_FC_ITEM_CHANGE_WINDOW_POSITION");
						*/
						for (auto entry : m_packetlog_lookup_sent)
						{
							ImGui::Text(m_packetlog[entry].name.c_str());
						}

						ImGui::Text("All sent:");
						ImGui::NewLine();
						ImGui::Text("Packet type recieved");
						ImGui::NewLine();
						for (auto entry : m_packetlog_lookup_recv)
						{
							ImGui::Text(m_packetlog[entry].name.c_str());
						}
						//ImGui::Text("T_ERROR");
						ImGui::Text("All recieved:");
					}
					ImGui::NextColumn();
					{
						ImGui::Text("Total count sent");
						ImGui::NewLine();
						/*
						ImGui::Text(std::to_string(m_pdl_current.use_skill_sent).c_str());
						ImGui::Text(std::to_string(m_pdl_current.cancel_skill_sent).c_str());
						ImGui::Text(std::to_string(m_pdl_current.use_item_sent).c_str());
						ImGui::Text(std::to_string(m_pdl_current.use_energy_sent).c_str());
						ImGui::Text(std::to_string(m_pdl_current.throw_away_item_sent).c_str());
						ImGui::Text(std::to_string(m_pdl_current.sell_item_sent).c_str());
						ImGui::Text(std::to_string(m_pdl_current.use_randombox_sent).c_str());
						ImGui::Text(std::to_string(m_pdl_current.change_window_postion_sent).c_str());
						ImGui::Text(std::to_string(m_pdl_current.total_sent).c_str());
						*/
						for (auto entry : m_packetlog_lookup_sent)
						{
							ImGui::Text(std::to_string(m_packetlog[entry].count_total).c_str());
						}
						ImGui::Text(std::to_string(m_total_sent.count_total).c_str());
						ImGui::NewLine();
						ImGui::Text("Total count recieved");
						ImGui::NewLine();
						for (auto entry : m_packetlog_lookup_recv)
						{
							ImGui::Text(std::to_string(m_packetlog[entry].count_total).c_str());
						}
						ImGui::Text(std::to_string(m_total_recv.count_total).c_str());
						//ImGui::Text(std::to_string(m_pdl_current.errors_recieved).c_str());
						//ImGui::Text(std::to_string(m_pdl_current.total_recieved).c_str());
					}
					ImGui::NextColumn();
					{
						ImGui::Text("Last second sent"); 
						ImGui::NewLine();
						/*
						ImGui::Text(std::to_string(m_pdl_last_second.use_skill_sent).c_str());
						ImGui::Text(std::to_string(m_pdl_last_second.cancel_skill_sent).c_str());
						ImGui::Text(std::to_string(m_pdl_last_second.use_item_sent).c_str());
						ImGui::Text(std::to_string(m_pdl_last_second.use_energy_sent).c_str());
						ImGui::Text(std::to_string(m_pdl_last_second.throw_away_item_sent).c_str());
						ImGui::Text(std::to_string(m_pdl_last_second.sell_item_sent).c_str());
						ImGui::Text(std::to_string(m_pdl_last_second.use_randombox_sent).c_str());
						ImGui::Text(std::to_string(m_pdl_last_second.change_window_postion_sent).c_str());
						ImGui::Text(std::to_string(m_pdl_last_second.total_sent).c_str());
						*/
						for (auto entry : m_packetlog_lookup_sent)
						{
							ImGui::Text(std::to_string(m_packetlog[entry].count_last_second).c_str());
						}

						ImGui::Text(std::to_string(m_total_sent.count_last_second).c_str());
						ImGui::NewLine();
						ImGui::Text("Last second recieved");   						
						ImGui::NewLine();
						for (auto entry : m_packetlog_lookup_recv)
						{
							ImGui::Text(std::to_string(m_packetlog[entry].count_last_second).c_str());
						}
						ImGui::Text(std::to_string(m_total_recv.count_last_second).c_str());
						//ImGui::Text(std::to_string(m_pdl_last_second.errors_recieved).c_str());
						//ImGui::Text(std::to_string(m_pdl_last_second.total_recieved).c_str());
					}
					ImGui::EndColumns();
				}
				ImGui::EndChild();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Players"))
			{
				ImGui::NewLine();
				ImGui::BeginChild("PlayerList", ImVec2(), false);
				{
					ImGui::BeginColumns("PlayerListColumns", 3, ImGuiColumnsFlags_NoResize);
					{
						ImGui::SetColumnWidth(0, 200);
						{
							ImGui::Text("Character Name");
						}
						ImGui::NextColumn();
						{
							ImGui::Text("Account Type");
						}
						ImGui::NextColumn();
						{
							ImGui::Text("Lead position");
							ImGui::SeparatorEx(ImGuiSeparatorFlags_SpanAllColumns | ImGuiSeparatorFlags_Horizontal);
						}
						ImGui::NextColumn();
						auto scenedata = OSR_API->GetSceneData();
						if (scenedata)
						{
							auto it = scenedata->m_mapEnemyList.begin();
							while (it != scenedata->m_mapEnemyList.end())
							{
								CEnemyData* enemy = it->second;
								{
									ImGui::Text(enemy->m_infoCharacter.CharacterInfo.CharacterName);
								}
								ImGui::NextColumn();
								{
									std::string race;
									if (COMPARE_RACE(enemy->m_infoCharacter.CharacterInfo.Race, RACE_DECA))
									{
										race += "Player";
									}
									if (COMPARE_RACE(enemy->m_infoCharacter.CharacterInfo.Race, RACE_OPERATION))
									{
										if (!race.empty()) { race += "; "; }
										race += "Operation";
									}
									if (COMPARE_RACE(enemy->m_infoCharacter.CharacterInfo.Race, RACE_GAMEMASTER))
									{
										if (!race.empty()) { race += "; "; }
										race += "GM";
									}
									if (COMPARE_RACE(enemy->m_infoCharacter.CharacterInfo.Race, RACE_MONITOR))
									{
										if (!race.empty()) { race += "; "; }
										race += "Monitor";
									}
									if (COMPARE_RACE(enemy->m_infoCharacter.CharacterInfo.Race, RACE_GUEST))
									{
										if (!race.empty()) { race += "; "; }
										race += "Guest";
									}
									if (COMPARE_RACE(enemy->m_infoCharacter.CharacterInfo.Race, RACE_DEMO))
									{
										if (!race.empty()) { race += "; "; }
										race += "Demo";
									}
									if (COMPARE_RACE(enemy->m_infoCharacter.CharacterInfo.Race, RACE_BATTALUS))
									{
										if (!race.empty()) { race += "; "; }
										race += "Battalus";
									}
									if (COMPARE_RACE(enemy->m_infoCharacter.CharacterInfo.Race, RACE_PHILON))
									{
										if (!race.empty()) { race += "; "; }
										race += "Philon";
									}
									if (COMPARE_RACE(enemy->m_infoCharacter.CharacterInfo.Race, RACE_SHARRINE))
									{
										if (!race.empty()) { race += "; "; }
										race += "Sharrine";
									}
									ImGui::Text(race.c_str());
								}
								ImGui::NextColumn();
								{
									std::string position;
									if (COMPARE_RACE(enemy->m_infoCharacter.CharacterInfo.Race, RACE_INFLUENCE_LEADER))
									{
										position = "Leader";
									}
									if (COMPARE_RACE(enemy->m_infoCharacter.CharacterInfo.Race, RACE_INFLUENCE_SUBLEADER_1))
									{
										position = "Subleader 1";
									}
									if (COMPARE_RACE(enemy->m_infoCharacter.CharacterInfo.Race, RACE_INFLUENCE_SUBLEADER_2))
									{
										position = "Subleader 2";
									}
									ImGui::Text(position.c_str());
								}
								ImGui::NextColumn();
								it++;
							}
						}				
					}
					ImGui::EndColumns();
				}
				ImGui::EndChild();
				ImGui::EndTabItem();
			}
		}  	
		ImGui::EndTabBar();
	}
	bool DebugInfo::OnReadPacket(unsigned short msgtype, byte* packet)
	{
		if (m_packetlog[msgtype].count_total == 0)
		{
			m_packetlog[msgtype].name = std::string(GetProtocolTypeString(msgtype));
			m_packetlog[msgtype].count_last_second = 0;
			ZeroMemory(&m_packetlog[msgtype].count_old, sizeof(uint32_t) * AVG_PDL_UPDATES_PER_SECOND);
			m_packetlog_lookup_recv.push_back(msgtype);
		}
		m_packetlog[msgtype].count_total++;
		m_total_recv.count_total++;
		return false;
	}
	bool DebugInfo::OnWritePacket(unsigned short msgtype, byte* packet)
	{
		if (m_packetlog[msgtype].count_total == 0)
		{
			m_packetlog[msgtype].name = std::string(GetProtocolTypeString(msgtype));
			m_packetlog[msgtype].count_last_second = 0;
			ZeroMemory(&m_packetlog[msgtype].count_old, sizeof(uint32_t) * AVG_PDL_UPDATES_PER_SECOND);
			m_packetlog_lookup_sent.push_back(msgtype);
		}
		m_packetlog[msgtype].count_total++;
		m_total_sent.count_total++;
		return false;
	}
}