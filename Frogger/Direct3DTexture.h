#ifndef DIRECT3D_TEXTURE
#define DIRECT3D_TEXTURE

#include <d3d9.h>
#include <d3dx9.h>

class Direct3DTexture {
	IDirect3DTexture9* data;
	D3DXIMAGE_INFO srcInfo;

	int width, height;

public:
	Direct3DTexture(char* fileName, LPDIRECT3DDEVICE9* d3dDevice, int width, int height);
	~Direct3DTexture();

	D3DXIMAGE_INFO getImageInfo();

	IDirect3DTexture9* getData();

	int getWidth() { return this->width; };
	int getHeight() { return this->height; };
};

#endif DIRECT3D_TEXTURE