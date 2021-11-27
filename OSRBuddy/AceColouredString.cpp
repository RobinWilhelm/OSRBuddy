#include "osrb_pch.h"
#include "AceColouredString.h"
#include "OSRImGuiMenu.h"


AceColouredString::AceColouredString()
{
	m_ace_color = 0;
}

AceColouredString::AceColouredString(std::string text, ImColor defaultcol)
{
	SetString(text, defaultcol);
}

ImColor AceColouredString::GetColor() const
{
	return m_ace_color;
}

std::string AceColouredString::GetCleanText() const
{
	return m_text;
}

std::string AceColouredString::GetOriginalText() const
{
	return m_original_text;
}

void AceColouredString::Clear()
{
	m_ace_color = 0;
	m_text.clear();
	m_original_text.clear();
}

void AceColouredString::RenderImGui() const
{
	ImGui::PushStyleColor(ImGuiCol_Text, m_ace_color.Value);
	ImGui::Text(m_text.c_str());
	ImGui::PopStyleColor();
}

ImColor AceColouredString::TranslateAceCharToColor(char color)
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
		return ImColor(0xFF, 0xFF, 0xFF);
	}
}

void AceColouredString::SetString(const std::string& text, ImColor defaultcol)
{
	m_original_text = text;
	m_text = text;
	if (m_original_text[0] == '\\')  // check if name has a colorcode in its name
	{
		m_ace_color = TranslateAceCharToColor(m_original_text[1]);
		m_text.erase(m_text.begin(), m_text.begin() + 2);
		if (m_original_text[m_original_text.length() - 2] == '\\')
		{
			m_text.erase(m_text.end() - 2, m_text.end());
		}
	}
	else
	{
		m_ace_color = defaultcol;
	}
}
