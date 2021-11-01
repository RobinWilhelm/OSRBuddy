#include "AceColouredString.h"
#include "OSRImGuiMenu.h"

AceColouredString::AceColouredString()
{
	m_ace_color = 0;
}

AceColouredString::AceColouredString(std::string text)
{
	m_original_text = text;
	m_text = text;
	if (m_original_text[0] == '\\')  // check if name has a colorcode in its name
	{
		m_ace_color = OSRImGuiMenu::TranslateAceCharToColor(m_original_text[1]);
		m_text.erase(m_text.begin(), m_text.begin() + 2);
		if (m_original_text[m_original_text.length() -2] == '\\')
		{
			m_text.erase(m_text.end() - 2, m_text.end());
		}
	}
	else
	{
		m_ace_color = 0xFFFFFFFF;
	}
}

ImColor AceColouredString::GetColor()
{
	return m_ace_color;
}

std::string AceColouredString::GetCleanText()
{
	return m_text;
}

std::string AceColouredString::GetOriginalText()
{
	return m_original_text;
}