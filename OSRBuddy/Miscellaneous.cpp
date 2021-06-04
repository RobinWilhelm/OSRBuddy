#include "Miscellaneous.h"
#include "imgui/imgui.h" 
#include "OSRAPI.h";
#include "OSRBuddy.h"
#include "SDK/AtumApplication.h"

#define WHISPER_WARNING_TIME 10s

Miscellaneous::Miscellaneous(OSRBuddyMain* buddy) : BuddyFeatureBase(buddy)
{
	m_whisperwarner_active = false;
}

Miscellaneous::~Miscellaneous()
{
}

FeatureType Miscellaneous::GetType() const
{
	return FeatureType::Miscellaneous;
}

std::string Miscellaneous::GetName() const
{
	return "Misc";
}

void Miscellaneous::Tick()
{
	auto currenttime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	if (m_whisperwarner_active && (currenttime - m_last_whisperwarn) >= WHISPER_WARNING_TIME)
	{
		CINFGameMainChat* chat = OSR_API->GetINFGameMainChat();
		if (chat)
		{
			for (auto whisperchat : chat->m_vectorINFiGameMainWisperChatPtr)
			{
				if (whisperchat->m_bNewMassage) 
				{						
					m_buddy->NotifySound(NotifyType::Warning);
					if (!m_popup_open && m_buddy->NotificationPopupAllowed())
					{							
						std::string msg = std::string(whisperchat->m_szWisperCharacterName) + " has whispered you!";
						m_buddy->OpenMessageBoxAsync(msg, "Whisper Warning!", NotifyType::Warning, std::bind(&Miscellaneous::OnMessageBoxClose, this, std::placeholders::_1));
						m_popup_open = true;
					}					
					m_last_whisperwarn = currenttime;
					
					if (m_whisperwarner_closeall) {
						m_buddy->DisableAllFeatures();
					}
					break;
				}
			}
		}
	}

	
	if (use_stealthcard)
	{
		CItemInfo* stealthcard = FindStealthCardInInventory();
		if (stealthcard)
		{

		}
	}
}

void Miscellaneous::RenderImGui()
{
	ImGui::NewLine();
	ImGui::Checkbox("Whisperwarner", &m_whisperwarner_active);
	if (ImGui::IsItemHovered()) {
		ImGui::SetTooltip("Will notify the user whenever there is a new / unread whisper message.");
	}
	ImGui::BeginDisabledMode(!m_whisperwarner_active);
	ImGui::Checkbox("Close all features when getting whispered.", &m_whisperwarner_closeall);
	ImGui::EndDisabledMode();
}

void Miscellaneous::OnMessageBoxClose(int result)
{
	m_popup_open = false;
}

CItemInfo* Miscellaneous::FindStealthCardInInventory()
{
	CItemInfo* sc = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Starter_Mini_Stealth_Card);
	if (!sc) {
		sc = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Mini_Stealth_Card);
		if (!sc) {
			sc = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Stealth_Card_30m);
			if (!sc) {
				sc = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Stealth_Card_2h);
			}
		}
	}	

	return sc;
}
