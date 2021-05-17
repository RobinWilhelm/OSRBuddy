#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_internal.h"
#include <vector>
#include <string>    
#include <OSRBuddyDefine.h>

static ImVector<ImRect> s_GroupPanelLabelStack;




namespace ImGui 
{
    //https://eliasdaler.github.io/using-imgui-with-sfml-pt2/#arrays
    bool EnchantList(const char* label, int* currIndex, EnchantListType& values, int heightInItems = -1);

    void BeginGroupPanel(const char* name, const ImVec2& size);
    void EndGroupPanel();

    bool FancyCheckbox(const char* label, bool* v);
    bool FancyButton(const char* label, float rounding = 0.5f, ImVec2 size = ImVec2( 0,0 ));
    bool FancyCombo(const char* label, int* current_item, void* data, int items_count, int popup_max_height_in_items = -1, bool leftSideText = true, float max_width = 0);

    bool BeginComboLeftSidedText(const char* label, const char* preview_value, ImGuiComboFlags flags);
}