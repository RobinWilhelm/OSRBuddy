#include "osrb_pch.h"
#include "D3D9Renderer.h"
#include <d3dx9core.h>


D3D9Renderer::D3D9Renderer(IDirect3DDevice9* device)
{
	m_d3d9device = device;
	m_standardfont = std::make_unique<D3D9Font>(device, "Tahoma", 14, 6, FW_BOLD);
	D3DXCreateLine(device, &m_d3dline);
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

void D3D9Renderer::RenderRect2D(int x, int y, int width, int height, D3DCOLOR color)
{
	D3DRECT rect{ x, y, x + width, y + height};
	m_d3d9device->Clear(1, &rect, D3DCLEAR_TARGET, color, 1.0f, NULL);
}

void D3D9Renderer::RenderText(std::string text, int x, int y, int width, int height, D3DCOLOR color, D3D9Font* font)
{
	if (!font) 
	{
		m_standardfont->RenderText(text, x, y, width, height, color);
	}
	else 
	{
		font->RenderText(text, x, y, width, height, color);
	}
}

void D3D9Renderer::RenderLine2D(int x, int y, int x2, int y2, float width, D3DCOLOR color)
{
	D3DXVECTOR2 vertices[2];
	vertices[0].x = x;
	vertices[0].y = y;
	vertices[1].x = x2;
	vertices[1].y = y2;

	m_d3dline->SetWidth(width);
	m_d3dline->Begin();
	m_d3dline->Draw(vertices, 2, color);
	m_d3dline->End();
}

void D3D9Renderer::RenderBox2D(int x, int y, int width, int height, float halflinewidth, D3DCOLOR color)
{
	// function is not finished
	return;
	D3DXVECTOR2 vertices[2];
	vertices[0].x = x - halflinewidth;
	vertices[0].y = y - halflinewidth;

	vertices[1].x = x + width + halflinewidth;
	vertices[1].y = y - halflinewidth;

	vertices[2].x = x + width + halflinewidth;
	vertices[2].y = y + height + halflinewidth;

	vertices[3].x = x - halflinewidth;
	vertices[3].y = y + height + halflinewidth;

	vertices[4].x = x - halflinewidth;
	vertices[4].y = y - halflinewidth;

	m_d3dline->SetWidth(halflinewidth * 2.0f);
	m_d3dline->Begin();

	vertices[0].x = x;
	vertices[0].y = y - halflinewidth;
	vertices[1].x = x + width;
	vertices[1].y = y - halflinewidth;
	m_d3dline->Draw(vertices, 2, color);

	vertices[0].x = x - halflinewidth;
	vertices[0].y = y;
	vertices[1].x = x + width;
	vertices[1].y = y - halflinewidth;
	m_d3dline->Draw(vertices, 2, color);
	m_d3dline->Draw(vertices, 2, color);
	m_d3dline->Draw(vertices, 2, color);

	m_d3dline->End();
}

HRESULT D3D9Renderer::OnLostDevice()
{
	m_d3dline->OnLostDevice();
	m_standardfont->OnLostDevice();
	return D3D_OK;
}

HRESULT D3D9Renderer::OnResetDevice()
{
	m_d3dline->OnResetDevice();
	m_standardfont->OnResetDevice();
	return D3D_OK;
}
