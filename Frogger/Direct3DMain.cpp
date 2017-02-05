#include "Direct3DWindow.h"

struct Vertex {
	Vertex() {};
	Vertex(float _x, float _y, float _z, float _u, float _v, float _color) {
		x = _x; y = _y; z = _z; u = _u; v = _v; color = _color;
	}

	float x, y, z;
	D3DCOLOR color;
	float u, v;
	
	static const DWORD FVF;
};

const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;

class AppMain : public Direct3DWindow {
public:
	AppMain(HINSTANCE hInstance);
	~AppMain();

	bool Init() override;
	void Update(float dt) override;
	void Render(Drawable& d, Direct3DTexture* texture) override;
	void RenderBackground() override;
	void Begin() override;
	void End() override;
};

IDirect3DVertexBuffer9* vertexBuffer;
IDirect3DIndexBuffer9* indexBuffer;


//Calls the base class (DXApp) constructor
AppMain::AppMain(HINSTANCE hInstance) : Direct3DWindow(hInstance) {

}

//Destructor
AppMain::~AppMain() {

}

//Calls the based class (DXApp) Init()
bool AppMain::Init() {
	//If it fails return false;
	if (!Direct3DWindow::Init())
		return false;

	const int vertsCount = 4;
	const int indexCount = 6;

	D3DCOLOR color = D3DCOLOR_ARGB(0, 255, 255, 255);

	Vertex verts[vertsCount] = {
		Vertex(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, color), // top left
		Vertex(1.0f, 0.0f, 0.0f, 1.0f, 0.0f, color), // top right
		Vertex(1.0f, 1.0f, 0.0f, 1.0f, 1.0f, color), // bottom right
		Vertex(0.0f, 1.0f, 0.0f, 0.0f, 1.0f, color) // bottom left
	};

	WORD indices[indexCount] = {
		0, 1, 2,
		0, 2, 3
	};

	this->d3dDevice->CreateVertexBuffer(vertsCount * sizeof(Vertex), 0, Vertex::FVF, D3DPOOL_MANAGED, &vertexBuffer, NULL);
	this->d3dDevice->CreateIndexBuffer(indexCount * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuffer, NULL);

	VOID* pVerts;
	vertexBuffer->Lock(0, sizeof(verts), (void**)&pVerts, 0);
	memcpy(pVerts, &verts, sizeof(verts));
	vertexBuffer->Unlock();

	VOID* pIndices;
	indexBuffer->Lock(0, sizeof(indices), (void**)&pIndices, 0);
	memcpy(pIndices, indices, sizeof(indices));
	indexBuffer->Unlock();

	D3DXMATRIX projection;

	D3DXMatrixOrthoOffCenterLH(&projection, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f);
	this->d3dDevice->SetTransform(D3DTS_PROJECTION, &projection);

	this->d3dDevice->SetRenderState(D3DRS_LIGHTING, false);
	this->d3dDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	this->d3dDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
	this->d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	this->d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	this->d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	return true;
}

//Update test app
void AppMain::Update(float dt) {

}

void AppMain::RenderBackground() {
	Drawable d = {
		Vec2(),
		Vec2(X_TILE_SIZE * TILES_X, Y_TILE_SIZE * TILES_Y+20),
		{ Vec2(), Vec2(512, 512) }
	};

	Render(d, this->background);
}

void AppMain::Begin() {
	this->d3dDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	this->d3dDevice->BeginScene();
}

//Render test app
void AppMain::Render(Drawable& d, Direct3DTexture* texture) {
	D3DXMATRIX s, trans, texScale, texTrans;
	D3DXMatrixIdentity(&s);
	D3DXMatrixIdentity(&trans);
	D3DXMatrixIdentity(&texScale);
	D3DXMatrixIdentity(&texTrans);



	D3DXMatrixScaling(&s, d.size.x, d.size.y, 1.0f);
	D3DXMatrixTranslation(&trans, d.position.x, d.position.y, 0.0f);

	if (texture == tileset) {
		D3DXMatrixScaling(&texScale, d.textureRegion.size.x*51.2f / texture->getWidth(), d.textureRegion.size.y*51.2f / texture->getHeight(), 1.0f);
	}
	
	//D3DXMatrixTranslation(&texTrans, d.size.x/2, d.size.y, 0.0f);

	float x = d.textureRegion.position.x*(float)51.2f;
	float y = d.textureRegion.position.y*(float)51.2f;

	texTrans._13 = x / (float)texture->getWidth(); // X origin
	texTrans._23 = y / (float)texture->getHeight(); // Y origin
	texTrans._41 = X_TILE_SIZE / (float)texture->getWidth();  // Width;   
	texTrans._42 = Y_TILE_SIZE / (float)texture->getHeight(); // Height

	D3DXMATRIX trpos_matTrans;
	D3DXMatrixTranspose(&trpos_matTrans, &texTrans);


	this->d3dDevice->SetTexture(0, texture->getData());
	this->d3dDevice->SetTransform(D3DTS_WORLD, &(s*trans));
	this->d3dDevice->SetTransform(D3DTS_TEXTURE0, &(texScale*trpos_matTrans));
	this->d3dDevice->SetStreamSource(0, vertexBuffer, 0, sizeof(Vertex));
	this->d3dDevice->SetIndices(indexBuffer);
	this->d3dDevice->SetFVF(Vertex::FVF);
	this->d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 6, 0, 2);
}

void AppMain::End() {
	this->d3dDevice->EndScene();
	this->d3dDevice->Present(0, 0, 0, 0);
}

//Application Entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	//Create instance of test app object
	AppMain* app = new AppMain(hInstance);

	//Initialize our test app
	if (!app->Init())
		return 1;

	return (app->Run());
}