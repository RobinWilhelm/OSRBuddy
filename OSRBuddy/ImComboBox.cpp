#include "osrb_pch.h"
#include "ImComboBox.h"

namespace ImGui
{
	bool VectorCombo(const char* label, std::vector<ComboItem>& items, ComboItem& selected_item, ImGuiComboFlags flags)
	{
		ImGui::Text(label);
		ImGui::SameLine();
		bool is_open = false;
		ImGui::PushStyleColor(ImGuiCol_Text, selected_item.GetTextColor().Value);
		if (ImGui::BeginCombo("", selected_item.GetImGuiText().c_str(), ImGuiComboFlags_None)) // The second parameter is the label previewed before opening the combo.
		{
			is_open = true;
			for (auto& item : items)
			{
				bool is_selected = (selected_item.GetKey() == item.GetKey());
				ImGui::PushStyleColor(ImGuiCol_Text, item.GetTextColor().Value);
				if (ImGui::Selectable(item.GetImGuiText().c_str(), is_selected))
				{
					selected_item = item;
				}						
				ImGui::PopStyleColor();
				if (is_selected)
					ImGui::SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
			}
			ImGui::EndCombo();
		}
		ImGui::PopStyleColor();
		return is_open;
	}
}