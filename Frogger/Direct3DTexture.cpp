#include "Direct3DTexture.h"

Direct3DTexture::Direct3DTexture(char* fileName, LPDIRECT3DDEVICE9* d3dDevice, int width, int height) 
	: width(width), height(height) {
	D3DCOLOR colorkey = 0xFFFF00FF;

	D3DXCreateTextureFromFileEx(*d3dDevice, fileName, 0, 0, 1, 0,
		D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT,
		colorkey, &srcInfo, NULL, &this->data);
}

Direct3DTexture::~Direct3DTexture() {}

D3DXIMAGE_INFO Direct3DTexture::getImageInfo() {
	return this->srcInfo;
}

IDirect3DTexture9* Direct3DTexture::getData() {
	return this->data;
}