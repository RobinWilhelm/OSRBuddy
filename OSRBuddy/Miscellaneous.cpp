#include "Miscellaneous.h"
#include "imgui/imgui.h" 
#include "OSRAPI.h";
#include "OSRBuddy.h"

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
					break;
				}
			}
		}
	}
}

void Miscellaneous::RenderImGui()
{
	ImGui::NewLine();
	ImGui::Checkbox("Whisperwarner", &m_whisperwarner_active);
}

void Miscellaneous::OnMessageBoxClose(int result)
{
	m_popup_open = false;
}
