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
	void RenderRect(int x, int y, int width, int height, D3DCOLOR color);
	void RenderText(std::string text, int x, int y, int width, int height, D3DCOLOR color, D3D9Font* font = nullptr);

	HRESULT OnLostDevice();
	HRESULT OnResetDevice();
									  
private:
	IDirect3DDevice9* m_d3d9device;
	std::unique_ptr<D3D9Font> m_standardfont;

	IDirect3DStateBlock9* m_stateBlock = nullptr;
};