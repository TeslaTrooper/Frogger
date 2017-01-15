#include "Direct3DRenderer.h"

Direct3DRenderer::Direct3DRenderer() {}

Direct3DRenderer::~Direct3DRenderer() {}

void Direct3DRenderer::init(HWND hwnd) {
	this->d3d = Direct3DCreate9(D3D_SDK_VERSION);

	ZeroMemory(&this->d3dPP, sizeof(this->d3dPP));

	this->d3dPP.Windowed = TRUE;
	this->d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	this->d3dPP.hDeviceWindow = hwnd;

	this->d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &this->d3dPP, &this->d3dDevice);

	this->d3dDevice->SetVertexShader(NULL);
	this->d3dDevice->SetFVF(D3DFVF_TLVERTEX);
	this->d3dDevice->CreateVertexBuffer(sizeof(TLVERTEX) * 4, NULL,
		D3DFVF_TLVERTEX, D3DPOOL_MANAGED, &vertexBuffer, NULL);
	this->d3dDevice->SetStreamSource(0, vertexBuffer, 0, sizeof(TLVERTEX));

	this->d3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	this->d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	this->d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	this->d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	this->d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	this->bg = new Direct3DTexture("../textures/bg.png", &this->d3dDevice, 560, 540);
}

void Direct3DRenderer::render() {
	this->d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(128, 0, 0), 1.f, 0);
	this->d3dDevice->BeginScene();

	renderTexture(this->bg, 0, 0);

	this->d3dDevice->EndScene();
	this->d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void Direct3DRenderer::clean() {
	this->d3d->Release();
	this->d3dDevice->Release();
}

void Direct3DRenderer::renderTexture(Direct3DTexture* texture, float x, float y) {
	TLVERTEX* vertices;

	vertexBuffer->Lock(0, 0, (void**)&vertices, NULL);

	D3DCOLOR vertexColour = 0xFFFFFFFF;

	for (int i = 0; i < 4; i++) {
		vertices[i].colour = vertexColour;
		vertices[i].z = 0.0f;
		vertices[i].rhw = 1.0f;
	}

	vertices[0].x = x;
	vertices[0].y = y;
	vertices[0].u = 0.5f;
	vertices[0].v = 0.5;

	vertices[1].x = x + texture->getWidth();
	vertices[1].y = y;
	vertices[1].u = 1.0f;
	vertices[1].v = 0.5f;

	vertices[2].x = x + texture->getWidth();
	vertices[2].y = y + texture->getHeight();
	vertices[2].u = 1.0f;
	vertices[2].v = 1.0f;

	vertices[3].x = x;
	vertices[3].y = y + texture->getHeight();
	vertices[3].u = 0.5f;
	vertices[3].v = 1.0f;

	vertexBuffer->Unlock();

	this->d3dDevice->SetTexture(0, texture->getData());
	this->d3dDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 2);
}

void Direct3DRenderer::renderTexture(Direct3DTexture* texture, Drawable drawable) {

}