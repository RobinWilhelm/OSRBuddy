#pragma once
#include <d3d9.h>
#include <d3d9helper.h>

class D3D9Helper
{
public:
	static void SetRect(IDirect3DDevice9* device,int x, int y, int width, int height, D3DCOLOR color);
};