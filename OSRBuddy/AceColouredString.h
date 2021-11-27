#pragma once

#include "imgui/imgui.h"
#include <string>

class AceColouredString
{
public:
	AceColouredString();
	AceColouredString(std::string text, ImColor defaultcol = 0xFFFFFFFF);

	ImColor GetColor() const;
	std::string GetCleanText() const;
	std::string GetOriginalText() const;

	void Clear();
	void RenderImGui() const;

	static ImColor TranslateAceCharToColor(char color);

    AceColouredString& operator=(const AceColouredString& other)
    {
        if (this != &other) 
		{ // protect against invalid self-assignment
			m_original_text = other.m_original_text;
			m_ace_color		= other.m_ace_color;
			m_text			= other.m_text;
        }
        // by convention, always return *this
        return *this;
    }

	AceColouredString& operator=(const std::string& string)
	{
		if (m_original_text != string)
		{ // protect against invalid self-assignment
			SetString(string);
		}
		// by convention, always return *this
		return *this;
	}
private:
	void SetString(const std::string& text, ImColor defaultcol = 0xFFFFFFFF);

private:
	std::string m_original_text;
	std::string m_text;
	ImColor		m_ace_color;
};