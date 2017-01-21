#include "Direct3DRenderer.h"

Direct3DRenderer::Direct3DRenderer() {}

Direct3DRenderer::~Direct3DRenderer() {}

void Direct3DRenderer::init(HWND hWnd) {
	this->d3d = Direct3DCreate9(D3D_SDK_VERSION);

	ZeroMemory(&this->d3dPP, sizeof(this->d3dPP));

	this->d3dPP.Windowed = TRUE;
	this->d3dPP.SwapEffect = D3DSWAPEFFECT_FLIP;
	this->d3dPP.hDeviceWindow = hWnd;
	this->d3dPP.BackBufferCount = 1;

	D3DDISPLAYMODE d3ddm;
	RECT rWindow;

	//Get display mode
	d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

	//Get window bounds
	GetClientRect(hWnd, &rWindow);

	//Setup screen dimensions
	int resWidth = rWindow.right - rWindow.left;
	int resHeight = rWindow.bottom - rWindow.top;

	//Setup backbuffer
	this->d3dPP.BackBufferFormat = d3ddm.Format;
	this->d3dPP.BackBufferWidth = rWindow.right - rWindow.left;
	this->d3dPP.BackBufferHeight = rWindow.bottom - rWindow.top;

	this->d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &this->d3dPP, &this->d3dDevice);

	initRendering(resWidth, resHeight);

	this->bg = new Direct3DTexture("../textures/bg.png", &this->d3dDevice);
	this->tileset = new Direct3DTexture("../textures/tileset.png", &this->d3dDevice);
}

void Direct3DRenderer::initRendering(int width, int height) {
	D3DXMATRIX ortho;
	D3DXMATRIX identityMatrix;

	D3DXMatrixOrthoOffCenterLH(&ortho, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 1.0f, 10.0f);
	D3DXMatrixIdentity(&identityMatrix);

	this->d3dDevice->SetTransform(D3DTS_PROJECTION, &ortho);
	this->d3dDevice->SetTransform(D3DTS_VIEW, &identityMatrix);
	this->d3dDevice->SetTransform(D3DTS_WORLD, &identityMatrix);

	this->d3dDevice->CreateVertexBuffer(sizeof(TLVERTEX) * 4, NULL,
		D3DFVF_TLVERTEX, D3DPOOL_MANAGED, &vertexBuffer, NULL);
	this->d3dDevice->SetStreamSource(0, vertexBuffer, 0, sizeof(TLVERTEX));

	this->d3dDevice->SetVertexShader(NULL);
	this->d3dDevice->SetFVF(D3DFVF_TLVERTEX);

	setupQuad();

	this->d3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	this->d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	this->d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	this->d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	this->d3dDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
}

//void Direct3DRenderer::setupQuad(const Drawable& d, Vec2 texSize) {
void Direct3DRenderer::setupQuad() {
	TLVERTEX* vertices;

	vertexBuffer->Lock(0, 4 * sizeof(TLVERTEX), (void**)&vertices, NULL);

	D3DCOLOR vertexColour = 0xFFFFFFFF;

	/*float u = d.textureRegion.position.x*X_TILE_SIZE/texSize.x;
	float v = d.textureRegion.position.y*Y_TILE_SIZE / texSize.y;
	float w = d.textureRegion.size.x*X_TILE_SIZE / texSize.x;
	float h = d.textureRegion.size.y*Y_TILE_SIZE / texSize.y;*/

	float u = 0.0f;
	float v = 0.0f;
	float w = 1.0f;
	float h = 1.0f;

	vertices[0].x = 0.0f;
	vertices[0].y = 0.0f;
	vertices[0].u = u;
	vertices[0].v = v;

	vertices[1].x = 1.0f;
	vertices[1].y = 0.0f;
	vertices[1].u = u + w;
	vertices[1].v = v;

	vertices[2].x = 1.0f;
	vertices[2].y = 1.0f;
	vertices[2].u = u + w;
	vertices[2].v = v + h;

	vertices[3].x = 0.0f;
	vertices[3].y = 1.0f;
	vertices[3].u = u;
	vertices[3].v = v + h;

	for (int i = 0; i < 4; i++) {
		vertices[i].z = 1.0f;
		vertices[i].colour = vertexColour;
		//vertices[i].x -= 0.5f/texSize.x;
		//vertices[i].y -= 0.5f/texSize.y;
	}

	vertexBuffer->Unlock();
}

void Direct3DRenderer::render(const Drawable& drawable) {
	renderTexture(this->tileset, drawable);
}

void Direct3DRenderer::renderBg(const Drawable& drawable) {
	renderTexture(this->bg, drawable);
}

void Direct3DRenderer::beginRendering() {
	this->d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(128, 0, 0), 1.f, 0);
	this->d3dDevice->BeginScene();
}

void Direct3DRenderer::endRenderering() {
	this->d3dDevice->EndScene();
	this->d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void Direct3DRenderer::clean() {
	this->d3d->Release();
	this->d3dDevice->Release();
}

void Direct3DRenderer::renderTexture(Direct3DTexture* texture, const Drawable& drawable) {
	D3DXMATRIX translation;
	D3DXMATRIX scaling;
	D3DXMATRIX transformation;
	D3DXMATRIX textureCoords;
	D3DXMATRIX textureScaling;
	D3DXMATRIX textureTransformation;

	D3DXMatrixIdentity(&translation);
	D3DXMatrixIdentity(&scaling);
	D3DXMatrixIdentity(&transformation);
	D3DXMatrixIdentity(&textureCoords);
	D3DXMatrixIdentity(&textureScaling);
	D3DXMatrixIdentity(&textureTransformation);

	D3DXMatrixTranslation(&translation, drawable.position.x, drawable.position.y, 0.0f);

	float sx, sy;
	if (texture->getHeight() == 400) {
		sx = 1.32f;
		sy = 1.12f;
	}
	else {
		sx = 1.84f;
		sy = 1.89f;
	}

	D3DXMatrixScaling(&scaling, drawable.size.x*sx, drawable.size.y*sy, 1.0f);

	transformation = scaling * translation;

	D3DXMatrixTranslation(&textureCoords, (drawable.textureRegion.position.x*X_TILE_SIZE) / texture->getWidth(), (drawable.textureRegion.position.y*Y_TILE_SIZE) / texture->getHeight(), 0.0f);
	D3DXMatrixScaling(&textureScaling, (float)drawable.textureRegion.size.x*(float)X_TILE_SIZE / (float)texture->getWidth(), (float)drawable.textureRegion.size.y*(float)Y_TILE_SIZE / (float)texture->getHeight(), 1.0f);
	/*D3DXMatrixScaling(&textureScaling, (float) X_TILE_SIZE / (float) texture->getWidth(), (float) Y_TILE_SIZE / (float) texture->getHeight(), 1.0f);

	float x = drawable.textureRegion.position.x*(float)X_TILE_SIZE;
	float y = drawable.textureRegion.position.y*(float)Y_TILE_SIZE;

	textureCoords._13 = x / (float)texture->getWidth(); // X origin
	textureCoords._23 = y / (float)texture->getHeight(); // Y origin
	textureCoords._41 = drawable.textureRegion.size.x*X_TILE_SIZE / (float)texture->getWidth();  // Width;   
	textureCoords._42 = drawable.textureRegion.size.y*Y_TILE_SIZE / (float)texture->getHeight(); // Height

	D3DXMATRIX trpos_matTrans;
	D3DXMatrixTranspose(&trpos_matTrans, &textureCoords);

	textureTransformation = textureScaling * trpos_matTrans;*/

	textureTransformation = textureScaling * textureCoords;
	D3DXMATRIX trpos_matTrans;
	D3DXMatrixTranspose(&trpos_matTrans, &textureTransformation);

	d3dDevice->SetTransform(D3DTS_WORLD, &transformation);
	this->d3dDevice->SetTransform(D3DTS_TEXTURE0, &trpos_matTrans);
	d3dDevice->SetTexture(0, texture->getData());
	d3dDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 2);
}

/*void Direct3DRenderer::renderTexture(Direct3DTexture* texture, const Drawable& drawable) {

	/*TLVERTEX* vertices;

	vertexBuffer->Lock(0, 0, (void**)&vertices, NULL);

	D3DCOLOR vertexColour = 0xFFFFFFFF;
	float rhw = 1.0f;
	float z = 0.0f;

	for (int i = 0; i < 4; i++) {
		vertices[i].z = 0.0f;
		vertices[i].colour = vertexColour;
	}

	util::Rectangle cropping = drawable.textureRegion;

	float x = cropping.position.x * X_TILE_SIZE;
	float y = cropping.position.y * Y_TILE_SIZE;
	float w = cropping.size.x * X_TILE_SIZE;
	float h = cropping.size.y * Y_TILE_SIZE;

	float u = x / texture->getWidth();
	float v = y / texture->getHeight();

	float width = w / texture->getWidth();
	float height = h / texture->getHeight();*/

	/**vertices = {
		{ drawable.position.x, drawable.position.y, z, rhw, vertexColour, u, v},
		{ drawable.position.x + drawable.size.x, drawable.position.y, z, rhw, vertexColour, u+width, v},
		{ drawable.position.x + drawable.size.x, drawable.position.y + drawable.size, z, rhw, vertexColour, u+width, v+height},
		{ drawable.position.x, drawable.position.y + drawable.size.y, z, rhw, vertexColour, u, v+height}
	};*/

	

	/*D3DXMATRIX transform;
	D3DXMatrixTranslation(&transform, drawable.position.x, drawable.position.y, 0.0f);
	d3dDevice->SetTransform(D3DTS_WORLD, &transform);*/

	/*D3DXMATRIX matView;    // the view transform matrix

	D3DXMatrixLookAtLH(&matView,
		&D3DXVECTOR3(100.0f, 100.0f, -1.0f),    // the camera position
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),    // the look-at position
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));    // the up direction

	d3dDevice->SetTransform(D3DTS_VIEW, &matView);    // set the view transform to matView*/
	/*D3DXMATRIX viewMatrix = D3DXMATRIX(
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	(FLOAT)(560 / 2), (FLOAT)(540 / 2), 0, 1
	);+*/
	
	//setupQuad(drawable, Vec2(texture->getWidth(), texture->getHeight()));

	/*D3DXMATRIX translation;
	D3DXMatrixTranslation(&translation, drawable.position.x/WINDOW_WIDTH, drawable.position.y/WINDOW_HEIGHT, 0.0f);
	D3DXMATRIX scaling;
	D3DXMatrixScaling(&scaling, drawable.size.x*1.84, drawable.size.y*2, 0.0f); // 1.84, 2

	D3DXMATRIX textureCoords;
	D3DXMatrixTranslation(&textureCoords, (drawable.textureRegion.position.x*X_TILE_SIZE) / texture->getWidth(), (drawable.textureRegion.position.y*Y_TILE_SIZE) / texture->getHeight(), 0.0f);
	D3DXMATRIX textureScaling;
	D3DXMatrixScaling(&textureScaling, (drawable.textureRegion.size.x*X_TILE_SIZE) / texture->getWidth(), (drawable.textureRegion.size.y*Y_TILE_SIZE) / texture->getHeight(), 0.0f);

	D3DXMATRIX transformation = translation * scaling;
	D3DXMATRIX textureTransformation = textureCoords * textureScaling;
	
	this->d3dDevice->SetTransform(D3DTS_WORLD, &transformation);
	//this->d3dDevice->SetTransform(D3DTS_TEXTURE0, &textureTransformation);
	this->d3dDevice->SetTexture(0, texture->getData());
	this->d3dDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 2);
}*/