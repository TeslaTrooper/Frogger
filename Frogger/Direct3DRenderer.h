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
	Direct3DTexture* tileset;

	float screenWidth;
	float screenHeight;

	const DWORD D3DFVF_TLVERTEX = D3DFVF_XYZ | D3DFVF_DIFFUSE;

	struct TLVERTEX {
		float x;
		float y;
		float z;
		D3DCOLOR colour;
	};

	//void setupQuad(const Drawable& d, Vec2 texSize);
	void setupQuad();
	void renderTexture(Direct3DTexture* texture, const Drawable& drawable);

	void initRendering(float width, float height);

public:
	Direct3DRenderer();
	~Direct3DRenderer();


	void beginRendering();
	void endRenderering();
	void init(HWND hwnd);
	void render(const Drawable& drawable);
	void renderBg();
	void clean();
};

#endif DIRECT3D_RENDERER