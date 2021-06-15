#include "Miscellaneous.h"
#include "imgui/imgui.h" 
#include "OSRAPI.h";
#include "OSRBuddy.h"
#include "SDK/AtumApplication.h"

#define WHISPER_WARNING_TIME 10s

Miscellaneous::Miscellaneous(OSRBuddyMain* buddy) : BuddyFeatureBase(buddy)
{
	m_whisperwarner_active = false;	   
	m_clean_inventory = false;
	m_open_watermelongift = true;
	m_open_spicapsule = true;
	m_open_fantasyglobemineralcapsule = true;
	m_open_mineralcapsule = true;
	m_open_wpcapsule = true;
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

	if (m_clean_inventory && (!m_only_clean_while_stopped || OSR_API->GetAtumApplication()->m_pShuttleChild->m_bUnitStop)) {  
		TickCleanInventory();
	}
}

void Miscellaneous::RenderImGui()
{
	ImGui::BeginColumns("MiscColumns", 2, ImGuiColumnsFlags_NoResize);
	{
		ImGui::BeginChild("MiscColumn1", ImVec2(), false);
		{
			ImGui::Separator();
			ImGui::Text("Inventory Cleaning");
			ImGui::Separator();

			ImGui::NewLine();			
			ImGui::Checkbox("Active", &m_clean_inventory);
			if (ImGui::IsItemHovered()) {
				ImGui::SetTooltip("Will automatically open the below specified items.");
			}
			ImGui::Checkbox("Only while stopped", &m_only_clean_while_stopped);

			ImGui::NewLine();
			ImGui::Checkbox("Watermelon Gifts", &m_open_watermelongift);
			ImGui::Checkbox("SPI Capsules", &m_open_spicapsule);
			ImGui::Checkbox("Mineral Capsules", &m_open_mineralcapsule);
			ImGui::Checkbox("Fantasy Globe Mineral Capsules", &m_open_fantasyglobemineralcapsule);
			ImGui::Checkbox("WP Capsules", &m_open_wpcapsule);
		}
		ImGui::EndChild();
	}
	ImGui::NextColumn();
	{
		ImGui::BeginChild("MiscColumn2", ImVec2(), false);
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
		ImGui::EndChild();
	}
	ImGui::EndColumns();



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

void Miscellaneous::TickCleanInventory()
{
	if (m_open_mineralcapsule && TryOpenCapsule(ItemNumber::Mineral_Capsule))	{
		return;
	}

	if (m_open_fantasyglobemineralcapsule && TryOpenCapsule(ItemNumber::Fantasy_Globe_Mineral_Capsule)) {
		return;
	}

	if (m_open_watermelongift && TryOpenCapsule(ItemNumber::Square_Watermelon_Gift)) {
		return;
	}

	if (m_open_spicapsule && TryOpenCapsule(ItemNumber::SPI_capsule))	{
		return;
	}  

	if (m_open_wpcapsule)
	{
		if (TryOpenCapsule(ItemNumber::WP_Capsule_100)) {
			return;
		}

		if (TryOpenCapsule(ItemNumber::WP_Capsule_500)) {
			return;
		}

		if (TryOpenCapsule(ItemNumber::WP_Capsule_1000)) {
			return;
		}
	}
}


bool Miscellaneous::TryOpenCapsule(ItemNumber capsule)
{
	auto current = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	if (current - m_last_capsule_opened > CAPSULE_OPEN_REATTACK)
	{
		CItemInfo* item = OSR_API->FindItemInInventoryByItemNum(capsule);
		if (item)
		{
			OSR_API->SendUseItem(item);
			m_last_capsule_opened = current;
			return true;
		}
	}
	return false;	
}
