#pragma once
#include <utility>
#include <vector>
#include "AceColouredString.h"

namespace ImGui
{
	class ComboItem
	{
	public:
		ComboItem()
		{
			m_key = 0;
		}

		ComboItem(uint32_t key, const char* text, size_t size)
		{
			m_key = key;
			m_combotext = AceColouredString(std::string(text));
			m_imgui_text = m_combotext.GetCleanText() + "###" + std::to_string(key);
		}

	public:
		uint32_t GetKey() { return m_key; };
		std::string GetImGuiText() { return m_imgui_text; };
		std::string GetText() { return m_combotext.GetCleanText(); };
		ImColor GetTextColor() { return m_combotext.GetColor(); }

	private:
		uint32_t m_key;
		std::string m_imgui_text; // unique
		AceColouredString m_combotext;
	};
	

	bool VectorCombo(const char* lable, std::vector<ComboItem>& items, ComboItem& selected_item, ImGuiComboFlags flags);

}