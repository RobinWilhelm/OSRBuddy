#include "osrb_pch.h"
#include "OSRImGuiMenu.h"

#include "OSRBuddy.h"
#include "BuddyFeatureBase.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"   


#define FEATURE_ACTIVE_TEXTCOL ImColor(0x00, 0xFF, 0x00)

void OSRImGuiMenu::Render()
{      
    ImGui::SetNextWindowSize(ImVec2(700, 510));                   
#ifdef RELEASE_SETHIA
    const std::string windowname = "OSRBuddy - customized for Sethia";      
#else
    const std::string windowname = "OSRBuddy";
#endif // RELEASE_SETHIA   
    
    ImGui::Begin(windowname.c_str(), &m_isOpen, ImGuiWindowFlags_NoResize);
    {         
        if (ImGui::Button("Unload")) {
            m_osrbuddy->InitiateAppShutdown();
        }
        ImGui::BeginTabBar("Features", ImGuiTabBarFlags_::ImGuiTabBarFlags_None);
        {
            if (ImGui::BeginTabItem("Settings"))
            {
                ImGui::Separator();
                ImGui::Text("HotKeys");
                ImGui::Separator();

                ImGui::Text("Insert (Einfg):    Open / Close this menu");
                ImGui::Text("End (Ende):        Disable all features and close menu");
                ImGui::Text("Delete (Entf):     Unload osrbuddy");

                ImGui::NewLine();

                ImGui::BeginColumns("SettingsColumns", 2, ImGuiColumnsFlags_NoResize | ImGuiColumnsFlags_NoBorder);
                {
                    //ImGui::SetColumnWidth(0, 500);
                    ImGui::BeginChild("SettingsTabCol1", ImVec2(), false);
                    {
                        ImGui::Separator();
                        ImGui::Text("Menu Settings");
                        ImGui::Separator();

                        ImGui::Checkbox("Block input when menu is open", &m_blockInput);
                        ImGui::NewLine();

                        ImGui::Separator();
                        ImGui::Text("Allow Notifications");
                        ImGui::Separator();

                        ImGui::Checkbox("Sound", &m_osrbuddy->m_allow_notify_sounds);
                        ImGui::Checkbox("Messagebox", &m_osrbuddy->m_allow_notify_popups);
                    }
                    ImGui::EndChild();
                }
                ImGui::NextColumn();
                {
                    ImGui::BeginChild("SettingsTabCol2", ImVec2(), false);
                    {
                        ImGui::Separator();
                        ImGui::Text("UI Themes");
                        ImGui::Separator();
                        if (ImGui::Button("ImGui Standard")) 
                        {
                            LoadStandardTheme();
                        }
                        if (ImGui::Button("Classic Steam")) 
                        {
                            LoadClassicSteamTheme();
                        }
                    }
                    ImGui::EndChild();
                }
                ImGui::EndColumns();

                ImGui::EndTabItem();
            }

            for (auto& feature : m_osrbuddy->GetAllFeatures())
            {
                std::string tabname = feature->GetName();
                if (feature->IsEnabled()) {
                    ImGui::PushStyleColor(ImGuiCol_Text, FEATURE_ACTIVE_TEXTCOL.Value);
                }                                               

                bool tab_open = ImGui::BeginTabItem(tabname.c_str());
                if (feature->IsEnabled()) {
                    ImGui::PopStyleColor();
                }

                if (tab_open)
                {
                    feature->RenderImGui();
                    ImGui::EndTabItem();
                }
            }
        }
        ImGui::EndTabBar();
    }
    ImGui::End();

    // Render toasts on top of everything, at the end of your code!
    // You should push style vars here
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.f);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(43.f / 255.f, 43.f / 255.f, 43.f / 255.f, 100.f / 255.f));
    ImGui::RenderNotifications();
    ImGui::PopStyleVar(1); // Don't forget to Pop()
    ImGui::PopStyleColor(1);
}