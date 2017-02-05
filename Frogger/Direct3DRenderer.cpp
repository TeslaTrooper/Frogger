#include "Direct3DRenderer.h"

Direct3DRenderer::Direct3DRenderer() {}

Direct3DRenderer::~Direct3DRenderer() {}

void Direct3DRenderer::init(HWND hWnd) {
	this->d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9 caps;
	d3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	int vp;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) {
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	} else {
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	ZeroMemory(&this->d3dPP, sizeof(this->d3dPP));

	

	D3DDISPLAYMODE d3ddm;
	RECT rWindow;

	//Get display mode
	d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

	//Get window bounds
	GetClientRect(hWnd, &rWindow);

	//Setup screen dimensions
	float resWidth = rWindow.right - rWindow.left;
	float resHeight = rWindow.bottom - rWindow.top;

	//Setup backbuffer
	this->d3dPP.BackBufferWidth = WINDOW_WIDTH;
	this->d3dPP.BackBufferHeight = WINDOW_HEIGHT;
	this->d3dPP.BackBufferFormat = D3DFMT_A8R8G8B8; //32 bit format
	this->d3dPP.Windowed = true; //start windowed
	this->d3dPP.BackBufferCount = 1; //Double buffered. 
	this->d3dPP.MultiSampleType = D3DMULTISAMPLE_NONE; //No multisampling (way too intensive)
	this->d3dPP.MultiSampleQuality = 0;
	this->d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	this->d3dPP.hDeviceWindow = hWnd;
	this->d3dPP.Flags = 0;
	this->d3dPP.EnableAutoDepthStencil = true;
	this->d3dPP.AutoDepthStencilFormat = D3DFMT_D24S8;
	this->d3dPP.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	this->d3dPP.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	this->d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, vp, &this->d3dPP, &this->d3dDevice);
	if (!d3dDevice) {
		MessageBox(NULL, "kk", NULL, NULL);
	}

	initRendering(WINDOW_WIDTH, WINDOW_HEIGHT);

	this->bg = new Direct3DTexture("../textures/tile.png", &this->d3dDevice);
	this->tileset = new Direct3DTexture("../textures/tile.png", &this->d3dDevice);
}

void Direct3DRenderer::initRendering(float width, float height) {
	this->screenWidth = width;
	this->screenHeight = height;

	D3DXMATRIX ortho, world, view;

	D3DXMatrixIdentity(&ortho);
	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&view);

	D3DVIEWPORT9 view_port;

	view_port.X = 0;
	view_port.Y = 0;
	view_port.Width = width;
	view_port.Height = height;
	view_port.MinZ = 0.0f;
	view_port.MaxZ = 1.0f;

	d3dDevice->SetViewport(&view_port);

	//D3DXMatrixOrthoOffCenterLH(&ortho, 0.0f, width, height, 0.0f, 0.0f, 1.0f);
	D3DXMatrixPerspectiveFovLH(&ortho, D3DX_PI / 4, static_cast<float>(WINDOW_WIDTH) / WINDOW_HEIGHT, 1.0f, 1000.0f);
	
	D3DXVECTOR3 camera;
	camera.x = 0.0f;
	camera.y = 0.0f;
	camera.z = -5.0f;
	D3DXVECTOR3 cameraTarget;
	cameraTarget.x = 0.0f;
	cameraTarget.y = 0.0f;
	cameraTarget.z = 1.0f;
	D3DXVECTOR3 cameraUp;
	cameraUp.x = 0.0f;
	cameraUp.y = 1.0f;
	cameraUp.z = 0.0f;
	D3DXMatrixLookAtLH(&view, &camera, &cameraTarget, &cameraUp);


	this->d3dDevice->SetTransform(D3DTS_PROJECTION, &ortho);
	this->d3dDevice->SetTransform(D3DTS_VIEW, &view);
	//this->d3dDevice->SetTransform(D3DTS_WORLD, &world);

	d3dDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	this->d3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	

	
	//this->d3dDevice->SetStreamSource(0, vertexBuffer, 0, sizeof(TLVERTEX));

	//this->d3dDevice->SetVertexShader(NULL);
	//this->d3dDevice->SetFVF(D3DFVF_TLVERTEX);

	setupQuad();

	
	//this->d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//this->d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//this->d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//this->d3dDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
}

//void Direct3DRenderer::setupQuad(const Drawable& d, Vec2 texSize) {
void Direct3DRenderer::setupQuad() {
	D3DCOLOR vertexColour = 0xffffff55;

	TLVERTEX vertices[3] = {
		{0, 1, 0, vertexColour},
		{1, -1, 0, vertexColour},
		{-1, -1, 0, vertexColour}
	};
	

	/*float u = d.textureRegion.position.x*X_TILE_SIZE/texSize.x;
	float v = d.textureRegion.position.y*Y_TILE_SIZE / texSize.y;
	float w = d.textureRegion.size.x*X_TILE_SIZE / texSize.x;
	float h = d.textureRegion.size.y*Y_TILE_SIZE / texSize.y;*/

	/*for (int i = 0; i < count; i++) {
		vertices[i].z = 1.0f;
		vertices[i].colour = vertexColour;
		//vertices[i].rhw = 1.0f;
		//vertices[i].x -= 0.5f/texSize.x;
		//vertices[i].y -= 0.5f/texSize.y;
	}*/

	this->d3dDevice->CreateVertexBuffer(3*sizeof(TLVERTEX), NULL,
		D3DFVF_TLVERTEX, D3DPOOL_MANAGED, &vertexBuffer, NULL);

	VOID* pVerts;
	vertexBuffer->Lock(0, sizeof(vertices), (void**)&pVerts, NULL);
	memcpy(pVerts, &vertices, sizeof(vertices));
	vertexBuffer->Unlock();
}

void Direct3DRenderer::render(const Drawable& drawable) {
	renderTexture(this->tileset, drawable);
}

void Direct3DRenderer::renderBg() {
	Drawable a;

	//a.size.x = this->bg->getWidth()+462;
	//a.size.y = this->bg->getHeight()+483;

	a.size.x = this->bg->getWidth();
	a.size.y = this->bg->getHeight();

	renderTexture(this->bg, a);
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

	float sx = 1, sy = 1;
	/*if (texture->getHeight() == 400) {
		sx = 1.32f;
		sy = 1.12f;
	}
	else {
		sx = 1.84f;
		sy = 1.89f;
	}*/

	D3DXMatrixScaling(&scaling, drawable.size.x, drawable.size.y, 1.0f);

	transformation = scaling * translation;

	D3DXMatrixTranslation(&textureCoords, (drawable.textureRegion.position.x*X_TILE_SIZE) / texture->getWidth(), (drawable.textureRegion.position.y*Y_TILE_SIZE) / texture->getHeight(), 0.0f);
	//D3DXMatrixScaling(&textureScaling, (float)drawable.textureRegion.size.x*(float)X_TILE_SIZE / (float)texture->getWidth(), (float)drawable.textureRegion.size.y*(float)Y_TILE_SIZE / (float)texture->getHeight(), 1.0f);
	D3DXMatrixScaling(&textureScaling, 1.0f, 1.0f, 1.0f);

	if (texture != bg) {
		float x = drawable.textureRegion.position.x*(float)X_TILE_SIZE;
		float y = drawable.textureRegion.position.y*(float)Y_TILE_SIZE;

		textureCoords._13 = x / (float)texture->getWidth(); // X origin
		textureCoords._23 = y / (float)texture->getHeight(); // Y origin
		textureCoords._41 = drawable.textureRegion.size.x*X_TILE_SIZE / (float)texture->getWidth();  // Width;   
		textureCoords._42 = drawable.textureRegion.size.y*Y_TILE_SIZE / (float)texture->getHeight(); // Height

		D3DXMATRIX trpos_matTrans, trpos_matTrans1;
		D3DXMatrixTranspose(&trpos_matTrans, &textureCoords);
		D3DXMatrixTranspose(&trpos_matTrans1, &textureScaling);

		textureTransformation = trpos_matTrans1 * trpos_matTrans;
	}

	

	
	D3DXMATRIX trpos_matTrans, trpos_matTrans1;
	D3DXMatrixTranspose(&trpos_matTrans, &trpos_matTrans);
	D3DXMatrixTranspose(&trpos_matTrans1, &textureScaling);
	//textureTransformation = trpos_matTrans1 * trpos_matTrans;

	d3dDevice->SetFVF(D3DFVF_TLVERTEX);
	this->d3dDevice->SetStreamSource(0, vertexBuffer, 0, sizeof(TLVERTEX));
	d3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

	//d3dDevice->SetTransform(D3DTS_WORLD, &transformation);
	//this->d3dDevice->SetTransform(D3DTS_TEXTURE0, &textureScaling);
	//d3dDevice->SetTexture(0, texture->getData());
	
	//d3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertexBuffer, sizeof(TLVERTEX));
	//this->d3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
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