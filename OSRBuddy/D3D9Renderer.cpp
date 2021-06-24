#include "D3D9Renderer.h"
#include <d3dx9core.h>


D3D9Renderer::D3D9Renderer(IDirect3DDevice9* device)
{
	m_d3d9device = device;
	m_standardfont = std::make_unique<D3D9Font>(device, "Tahoma", 14, 6, FW_BOLD);
}

D3D9Renderer::~D3D9Renderer()
{
	m_d3d9device = nullptr;
}

void D3D9Renderer::Begin()
{
	//m_d3d9device->CreateStateBlock(D3DSBT_ALL, &m_stateBlock);
}

void D3D9Renderer::End()
{
	//m_stateBlock->Apply();
}

IDirect3DDevice9* D3D9Renderer::GetDevice()
{
	return m_d3d9device;
}

void D3D9Renderer::RenderRect(int x, int y, int width, int height, D3DCOLOR color)
{
	D3DRECT rect{ x, y, x + width, y + height};
	m_d3d9device->Clear(1, &rect, D3DCLEAR_TARGET, color, 1.0f, NULL);
}

void D3D9Renderer::RenderText(std::string text, int x, int y, int width, int height, D3DCOLOR color, D3D9Font* font)
{
	if (!font) {
		m_standardfont->RenderText(text, x, y, width, height, color);
	}
	else {
		font->RenderText(text, x, y, width, height, color);
	}
}

HRESULT D3D9Renderer::OnLostDevice()
{
	return m_standardfont->OnLostDevice();
}

HRESULT D3D9Renderer::OnResetDevice()
{
	return m_standardfont->OnResetDevice();
}
