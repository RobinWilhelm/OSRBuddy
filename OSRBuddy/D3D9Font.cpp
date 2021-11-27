#include "osrb_pch.h"
#include "D3D9Font.h"
#include <d3dx9.h>
#include <D3dx9core.h>


D3D9Font::D3D9Font(IDirect3DDevice9* device, std::string name, int size, bool bold, bool italic)
{
	m_initialised = false;
	HRESULT res = D3DXCreateFont(device, size, 0, (bold) ? FW_BOLD : FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, name.c_str(), &m_d3dfont);

	if (res == S_OK) {
		m_initialised = true;
	}
}

D3D9Font::~D3D9Font()
{
	if (m_d3dfont) { 
		m_d3dfont->Release();
	}
}

SIZE D3D9Font::GetSize(std::string text)
{
	if (!m_initialised)
		return SIZE();

	RECT rcRect = { 0,0,0,0 };
	if (m_d3dfont) {
		m_d3dfont->DrawText(NULL, text.c_str(), text.length(), &rcRect, DT_CALCRECT, D3DCOLOR_XRGB(0, 0, 0));
	}
	return SIZE{ rcRect.right - rcRect.left, rcRect.bottom - rcRect.top };
}

void D3D9Font::RenderText(std::string text, int x, int y, int height, int width, D3DCOLOR color)
{
	if (!m_initialised)
		return;

	RECT rect{ x, y, x + width, y + height };
	if (m_d3dfont) {
		m_d3dfont->DrawText(NULL, text.c_str(), text.size(), &rect, 0, color);
	}
}

HRESULT D3D9Font::OnLostDevice()
{
	if (!m_initialised)
		return S_OK;

	return m_d3dfont->OnLostDevice();
}

HRESULT D3D9Font::OnResetDevice()
{
	if (!m_initialised)
		return S_OK;

	return m_d3dfont->OnResetDevice();
}