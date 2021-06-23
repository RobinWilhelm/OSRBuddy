#include "BuddyFont.h"
#include <d3dx9.h>


BuddyFont::BuddyFont(IDirect3DDevice9* device, std::string name, int height, int width, int weight)
{
	D3DXCreateFont(device, height, width, weight, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, name.c_str(), &m_d3dfont);
}

BuddyFont::~BuddyFont()
{
	delete m_d3dfont;
}

SIZE BuddyFont::GetSize(std::string text)
{
	RECT rcRect = { 0,0,0,0 };
	if (m_d3dfont) {
		m_d3dfont->DrawText(NULL, text.c_str(), text.length(), &rcRect, DT_CALCRECT, D3DCOLOR_XRGB(0, 0, 0));
	}
	return SIZE{ rcRect.right - rcRect.left, rcRect.bottom - rcRect.top };
}

void BuddyFont::RenderText(std::string text, int x, int y, int height, int width, D3DCOLOR color)
{
	RECT rect{ x, y, x + width, y + height };
	if (m_d3dfont) {
		m_d3dfont->DrawText(NULL, text.c_str(), text.size(), &rect, 0, color);
	}
}

HRESULT BuddyFont::OnLostDevice()
{
	return m_d3dfont->OnLostDevice();
}

HRESULT BuddyFont::OnResetDevice()
{
	return m_d3dfont->OnResetDevice();
}
