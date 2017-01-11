#include "Direct3DRenderer.h"

Direct3DRenderer::Direct3DRenderer() {
	
}

Direct3DRenderer::~Direct3DRenderer() {}

void Direct3DRenderer::init(HWND hwnd) {
	this->d3d = Direct3DCreate9(D3D_SDK_VERSION);

	ZeroMemory(&this->d3dPP, sizeof(this->d3dPP));

	this->d3dPP.Windowed = TRUE;
	this->d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	this->d3dPP.hDeviceWindow = hwnd;

	this->d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &this->d3dPP, &this->d3dDevice);
}

void Direct3DRenderer::render() {
	this->d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(128, 0, 0), 1.f, 0);
	this->d3dDevice->BeginScene();

	// RENDER

	this->d3dDevice->EndScene();
	this->d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void Direct3DRenderer::clean() {
	this->d3d->Release();
	this->d3dDevice->Release();
}