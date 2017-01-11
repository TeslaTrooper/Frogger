#ifndef DIRECT3D_RENDERER
#define DIRECT3D_RENDERER

#include <d3d9.h>

class Direct3DRenderer {

	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3dDevice;
	D3DPRESENT_PARAMETERS d3dPP;

public:
	Direct3DRenderer();
	~Direct3DRenderer();

	void init(HWND hwnd);
	void render();
	void clean();
};

#endif DIRECT3D_RENDERER