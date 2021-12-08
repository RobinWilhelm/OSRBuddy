#pragma once
#include "D3D9Font.h"

#include <d3d9.h>
#include <memory>

class D3D9Renderer
{	   
public:
	D3D9Renderer(IDirect3DDevice9* device);
	~D3D9Renderer();

	void Begin();
	void End();

	IDirect3DDevice9* GetDevice();

	void RenderText(std::string text, int x, int y, int width, int height, D3DCOLOR color, D3D9Font* font = nullptr);
	void RenderRect2D(int x, int y, int width, int height, D3DCOLOR color);
	void RenderLine2D(int x, int y, int x2, int y2, float width, D3DCOLOR color);
	void RenderBox2D(int x, int y, int width, int height, float halflinewidth, D3DCOLOR color);

	HRESULT OnLostDevice();
	HRESULT OnResetDevice();
									  
private:
	IDirect3DDevice9* m_d3d9device;
	std::unique_ptr<D3D9Font> m_standardfont;
	ID3DXLine* m_d3dline = nullptr;

	IDirect3DStateBlock9* m_stateBlock = nullptr;
};