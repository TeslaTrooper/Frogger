#ifndef DIRECT3D_RENDERER
#define DIRECT3D_RENDERER

#include <d3d9.h>
#include <d3dx9.h>

#include "Util.h"
#include "Direct3DTexture.h"

using namespace util;

class Direct3DRenderer {

	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3dDevice;
	D3DPRESENT_PARAMETERS d3dPP;

	IDirect3DVertexBuffer9* vertexBuffer;
	Direct3DTexture* bg;

	const DWORD D3DFVF_TLVERTEX = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;

	struct TLVERTEX {
		float x;
		float y;
		float z;
		float rhw;
		D3DCOLOR colour;
		float u;
		float v;
	};

	void renderTexture(Direct3DTexture* texture, float x, float y);
	void renderTexture(Direct3DTexture* texture, Drawable drawable);

public:
	Direct3DRenderer();
	~Direct3DRenderer();

	void init(HWND hwnd);
	void render();
	void clean();
};

#endif DIRECT3D_RENDERER