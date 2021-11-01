#pragma once
#include "imgui/imgui.h"
#include <string>

class AceColouredString
{
public:
	AceColouredString();
	AceColouredString(std::string text);

	ImColor GetColor();
	std::string GetCleanText();
	std::string GetOriginalText();

private:
	std::string m_original_text;
	std::string m_text;
	ImColor		m_ace_color;
};