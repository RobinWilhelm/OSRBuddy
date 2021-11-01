#include "OSRImGuiMenu.h"
#include "OSRBuddy.h"
#include "Utility.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"   

#include "OSRAPI.h"

#define FEATURE_ACTIVE_TEXTCOL ImColor(0x00, 0xFF, 0x00)

void OSRImGuiMenu::Render()
{      
    ImGui::SetNextWindowSize(ImVec2(700, 500));                   
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
                        if (ImGui::Button("ImGui Standard")) {
                            LoadStandardTheme();
                        }
                        if (ImGui::Button("Classic Steam")) {
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
}
 
ImColor OSRImGuiMenu::TranslateAceCharToColor(char color)
{
    switch (std::tolower(color))
    {
    case 'c':   // cyan
        return ImColor(0x00, 0xFF, 0xFF);
    case 'q':   // light grey
        return ImColor(0xBA, 0xBA, 0xFF);
    case 'e':   // orange
        return ImColor(0xFF, 0xBB, 0x33);
    case 'r':   // red
        return ImColor(0xFF, 0x00, 0x00);
    case 'a':   // grey
        return ImColor(0xDE, 0xDE, 0xDE);
    case 'g':   // green
        return ImColor(0x00, 0xFF, 0x00);
    case 'y':   // yellow
        return ImColor(0xFF, 0xFF, 0x00);
    case 'b':   // blue
        return ImColor(0x00, 0x00, 0xFF);
    case 'w':   // white
        return ImColor(0xFF, 0xFF, 0xFF);
    case 'm':   // violett / magenta
        return ImColor(0xFF, 0x00, 0xFF);
    default:    // white
        return ImColor(0xFF, 0xFF,0xFF);
    }
}

void OSRImGuiMenu::DrawOsrItemName(const OsrItemInfo& item)
{
    if (item.GetUID() == 0) {
        return;
    }

    if (item.IsWeapon() && !item.GetCleanPrefixName().empty())
    {
        ImGui::PushStyleColor(ImGuiCol_Text, item.GetPrefixColor().Value);
        ImGui::Text(item.GetCleanPrefixName().c_str());
        ImGui::SameLine();
        ImGui::PopStyleColor();
    }

    ImGui::PushStyleColor(ImGuiCol_Text, item.GetItemNameColor().Value);
    ImGui::Text(item.GetCleanName().c_str());
    ImGui::PopStyleColor();

    ImGui::SameLine();

    if (item.IsWeapon() || item.IsArmor())
    {
        ImGui::PushStyleColor(ImGuiCol_Text, ImColor(0xFF, 0xBB, 0x33).Value);
        ImGui::Text(item.GetEnchantText().c_str());
        ImGui::PopStyleColor();
    }

    if (item.IsWeapon() && !item.GetCleanSuffixName().empty())
    {
        ImGui::PushStyleColor(ImGuiCol_Text, item.GetSuffixColor().Value);
        ImGui::SameLine();
        ImGui::Text(item.GetCleanSuffixName().c_str());
        ImGui::PopStyleColor();
    }
}

