#include "D3D9Renderer.h"


void D3D9Helper::SetRect(IDirect3DDevice9* device, int x, int y, int width, int height, D3DCOLOR color)
{
	D3DRECT rect{ x, y, x + width, y + height};
	device->Clear(1, &rect, D3DCLEAR_TARGET, color, 1.0f, NULL);
}
