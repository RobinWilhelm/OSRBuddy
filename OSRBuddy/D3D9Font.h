#pragma once
#include <string>
#include <d3d9.h>


class ID3DXFont;


class D3D9Font
{
friend class D3D9Renderer;
public:
	D3D9Font(IDirect3DDevice9* device, std::string name, int size, bool bold, bool italic);
	~D3D9Font();

	SIZE GetSize(std::string text);   
	void RenderText(std::string text, int x, int y, int height, int width, D3DCOLOR color);

	HRESULT OnLostDevice();
	HRESULT OnResetDevice();

private:
	bool m_initialised;
	ID3DXFont* m_d3dfont;
};