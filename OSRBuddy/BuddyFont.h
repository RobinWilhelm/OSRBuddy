#pragma once
#include <string>
#include <d3d9.h>


class ID3DXFont;


class BuddyFont
{
friend class D3D9Renderer;
public:
	BuddyFont(IDirect3DDevice9* device, std::string name, int height, int width, int weight);
	~BuddyFont();

	SIZE GetSize(std::string text);   
	void RenderText(std::string text, int x, int y, int height, int width, D3DCOLOR color);

	HRESULT OnLostDevice();
	HRESULT OnResetDevice();

private:
	ID3DXFont* m_d3dfont;
};