#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_internal.h"
#include <vector>
#include <string>    
#include <OSRBuddyDefine.h>



namespace ImGui 
{
    static ImVector<ImRect> s_GroupPanelLabelStack;
    static ImVector<bool> s_disabled;


    using ListVector = std::vector<std::string>;

    // helper to simplify and shorten the use of a simple dropdown box
// returns true if the selection has changed
// NOTE: dont add more elements in valueList than selectedIndex can hold 
    bool SimpleCombo(std::string label, const std::vector<std::string>& valueList, int* selectedIndex, ImGuiComboFlags flags = ImGuiComboFlags_None);

    template <typename KeyType>
    bool SimpleCombo(std::string label, const std::vector<std::pair<KeyType, std::string>>& keyvalueList, int* selectedIndex, ImGuiComboFlags flags = ImGuiComboFlags_None)
    {
        bool selection_changed = false;
        if (ImGui::BeginCombo(label.c_str(), keyvalueList[*selectedIndex].second.c_str(), flags))
        {
            for (int n = 0; n < keyvalueList.size(); n++)
            {
                bool is_selected = (*selectedIndex == n);
                if (ImGui::Selectable(keyvalueList[n].second.c_str(), is_selected))
                {
                    *selectedIndex = n;
                    selection_changed = true;
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        return selection_changed;
    }

    void BeginDisabledMode(bool disabled);
    void EndDisabledMode();

    void DrawTextCentered(std::string text, float total_width = ImGui::GetWindowContentRegionMax().x);
    void DrawTextRightAligned(std::string text, float total_width = ImGui::GetWindowContentRegionMax().x);

    //https://eliasdaler.github.io/using-imgui-with-sfml-pt2/#arrays
    bool VectorListBox(const char* label, int* currIndex, ListVector values, int heightInItems = -1);

    void BeginGroupPanel(const char* name, const ImVec2& size = ImVec2(0.0f, 0.0f));
    void EndGroupPanel();

    bool FancyCheckbox(const char* label, bool* v);
    bool FancyButton(const char* label, float rounding = 0.5f, ImVec2 size = ImVec2( 0,0 ));
    bool ComboEx(const char* label, int* current_item, void* data, int items_count, int popup_max_height_in_items = -1, bool leftSideText = true, float max_width = 0);

    bool BeginComboLeftSidedText(const char* label, const char* preview_value, ImGuiComboFlags flags);

    ImColor ARGB_2_RGBA(unsigned long argb);
    void AceText(std::string text);
}