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

private:
	std::string m_original_text;
	std::string m_text;
	ImColor		m_ace_color;
};