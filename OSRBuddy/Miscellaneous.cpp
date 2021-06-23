#include "Miscellaneous.h"
#include "imgui/imgui.h" 
#include "OSRAPI.h";
#include "OSRBuddy.h"
#include "SDK/AtumApplication.h"

#define WHISPER_WARNING_TIME 10s
#define CAPSULE_OPEN_REATTACK 200ms
#define WHIPSER_SNOOZE_TIME 1min

Miscellaneous::Miscellaneous(OSRBuddyMain* buddy) : BuddyFeatureBase(buddy)
{
	m_whisperwarner_active = false;	
	m_whisperwarner_snooze_enabled = true;

	m_inv_action_check_time = 0ms;
	m_clean_inventory = false;
	m_only_clean_while_overheat = false;
	m_only_clean_while_stopped = false;
	m_open_watermelongift = true;
	m_open_spicapsule = true;
	m_open_fantasyglobemineralcapsule = true;
	m_open_mineralcapsule = true;
	m_open_wpcapsule = true;
	m_open_soccer_ball_capsule = true;
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
	if (m_inv_action_check_time > 0ms) {
		m_inv_action_check_time -= std::chrono::duration_cast<std::chrono::milliseconds>(m_buddy->GetTickTime());
	}
	if (m_inv_action_check_time < 0ms) {
		m_inv_action_check_time = 0ms;
	}
		 	
	TickWhisperWarner();
	TickInventoryCleaning();
}

void Miscellaneous::RenderImGui()
{
	ImGui::BeginColumns("MiscColumns", 2, ImGuiColumnsFlags_NoResize);
	{
		ImGui::BeginChild("MiscColumn1", ImVec2(), false);
		{
			ImGui::Separator();
			ImGui::Text("Whisperwarner");
			ImGui::Separator();
			ImGui::Checkbox("Active", &m_whisperwarner_active);
			if (ImGui::IsItemHovered()) {
				ImGui::SetTooltip("Will notify the user whenever there is a new / unread whisper message.");
			}
			ImGui::Checkbox("Snooze enabled", &m_whisperwarner_snooze_enabled);
			ImGui::Checkbox("Close all features when getting whispered.", &m_whisperwarner_closeall);  			
		}
		ImGui::EndChild();
	}
	ImGui::NextColumn();
	{
		ImGui::BeginChild("MiscColumn2", ImVec2(), false);
		{
			ImGui::Separator();
			ImGui::Text("Inventory Cleaning");
			if (ImGui::IsItemHovered()) {
				ImGui::SetTooltip("This works for all gears. Grindbot does not have to be enabled for this to work.");
			}
			ImGui::Separator();

			ImGui::Checkbox("Active", &m_clean_inventory);
			if (ImGui::IsItemHovered()) {
				ImGui::SetTooltip("Will automatically open the below specified items.");
			}
			ImGui::SameLine();
			ImGui::Checkbox("Stopped", &m_only_clean_while_stopped);
			if (ImGui::IsItemHovered()) {
				ImGui::SetTooltip("Only clean inventory while gear is stopped.");
			}
			ImGui::SameLine();
			ImGui::Checkbox("Overheated", &m_only_clean_while_overheat);
			if (ImGui::IsItemHovered()) {
				ImGui::SetTooltip("Only clean inventory standard weapon is overheated.");
			}

			ImGui::NewLine();
			ImGui::BeginColumns("InventoryCleaningColumns", 2, ImGuiColumnsFlags_NoResize | ImGuiColumnsFlags_NoBorder);
			{
				ImGui::Checkbox("Watermelon Gifts", &m_open_watermelongift);
				ImGui::Checkbox("SPI Capsules", &m_open_spicapsule);
				ImGui::Checkbox("Fantasy Globe MC", &m_open_fantasyglobemineralcapsule);
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Mineral Capsules", &m_open_mineralcapsule);
				ImGui::Checkbox("WP Capsules", &m_open_wpcapsule);
				ImGui::Checkbox("Soccer Ball Capsule", &m_open_soccer_ball_capsule);
			}
			ImGui::EndColumns();
		}
		ImGui::EndChild();
	}
	ImGui::EndColumns();
}

void Miscellaneous::ActivateInventoryCleaning(bool active)
{
	m_clean_inventory = active;
}

void Miscellaneous::OnMessageBoxClose(int result)
{
	if (result == 1) // ok button
	{
		// set all messages as read 
		CINFGameMainChat* chat = OSR_API->GetINFGameMainChat();
		if (chat)
		{
			for (auto whisperchat : chat->m_vectorINFiGameMainWisperChatPtr)
			{
				whisperchat->m_bNewMassage = false;
			}
		}

		if (m_whisperwarner_snooze_enabled)
		{
			auto currenttime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
			m_ignore_whisperwarn_time = currenttime + WHIPSER_SNOOZE_TIME;
		}
	}	  
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

void Miscellaneous::TickWhisperWarner()
{
	auto currenttime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	if (currenttime < m_ignore_whisperwarn_time) {
		return;
	}

	if (m_whisperwarner_active && (currenttime - m_last_whisperwarn) >= WHISPER_WARNING_TIME)
	{
		CINFGameMainChat* chat = OSR_API->GetINFGameMainChat();
		if (chat)
		{
			std::vector<string> whisperer;
			for (auto whisperchat : chat->m_vectorINFiGameMainWisperChatPtr)
			{
				if (whisperchat->m_bNewMassage)
				{
					whisperer.push_back(std::string(whisperchat->m_szWisperCharacterName));
				}
			}

			if (whisperer.size() > 0)
			{ 			
				m_buddy->NotifySound(NotifyType::Warning);
				if (!m_popup_open && m_buddy->NotificationPopupAllowed())
				{
					std::string msg;
					bool first = true;
					for (auto wp : whisperer)
					{
						if (!first) {
							msg += ", ";
						}															
						msg += wp;
					}
					msg += (first) ? " has whispered you!" : " have whispered you!";					
					m_buddy->OpenMessageBoxAsync(msg, "Whisper Warning!", NotifyType::Warning, std::bind(&Miscellaneous::OnMessageBoxClose, this, std::placeholders::_1));
					m_popup_open = true;
				}
				m_last_whisperwarn = currenttime;

				if (m_whisperwarner_closeall) {
					m_buddy->DisableAllFeatures();
				}
			}
		}
	}
}

bool Miscellaneous::InventoryActionCheckTimeReady()
{
	return m_inv_action_check_time <= 0ms;
}

void Miscellaneous::ResetInventoryActionCheckTime()
{
	m_inv_action_check_time = CAPSULE_OPEN_REATTACK + std::chrono::milliseconds(m_buddy->GetRandInt32(0, 300));
}

void Miscellaneous::TickInventoryCleaning()
{
	if (m_clean_inventory && (!m_only_clean_while_stopped || OSR_API->GetAtumApplication()->m_pShuttleChild->m_bUnitStop)
		&& (!m_only_clean_while_overheat || OSR_API->GetPrimaryWeapon()->m_bOverHeat))
	{
		if (InventoryActionCheckTimeReady())
		{
			if (m_open_mineralcapsule && TryOpenCapsule(ItemNumber::Mineral_Capsule)) {
				return;
			}

			if (m_open_fantasyglobemineralcapsule && TryOpenCapsule(ItemNumber::Fantasy_Globe_Mineral_Capsule)) {
				return;
			}

			if (m_open_watermelongift && TryOpenCapsule(ItemNumber::Square_Watermelon_Gift)) {
				return;
			}


			if (m_open_soccer_ball_capsule && TryOpenCapsule(ItemNumber::Soccer_Ball_Capsule)) {
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

			if (m_open_spicapsule && TryOpenCapsule(ItemNumber::SPI_capsule)) {
				return;
			}
		}
	}
}

bool Miscellaneous::TryOpenCapsule(ItemNumber capsule)
{
	CItemInfo* item = OSR_API->FindItemInInventoryByItemNum(capsule);
	if (item)
	{
		OSR_API->SendUseItem(item);
		ResetInventoryActionCheckTime();
		return true;
	}
	return false;
}