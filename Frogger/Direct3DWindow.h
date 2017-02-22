#ifndef DIRECT_3D_WINDOW
#define DIRECT_3D_WINDOW

#include <windows.h>
#include <string>
#include <d3d9.h>
#include <d3dx9.h>
#include <chrono>

#include "Constants.h"
#include "Util.h"
#include "Direct3DTexture.h"
#include "Game.h"

using namespace util;

class Direct3DWindow {
public:
	Direct3DWindow(HINSTANCE hInstance);
	virtual ~Direct3DWindow(void);


	/*
		Führt die Hauptschleife aus.
	*/
	int Run();


	/*
		Initialisiert alle für Direct3D benötigten Parametern.
	*/
	bool initDirect3D();


	/*
		Lädt die Texturen.
	*/
	void initTextures();
	

	/*
		Stellt die Haupt-Initialisierung dar. Das Fester, sowie alle für Direct3D benötigten Parametern werden gesetzt.
	*/
	virtual bool Init();


	/*
		Rendert ein Drawable mit gegebener Textur.
		@param d das Drawable, das gerendert werden soll.
		@param textur ist die Textur, die zum Rendern verwendet werden soll.
	*/
	virtual void Render(Drawable& d, Direct3DTexture* texture) = 0;


	/*
		Rendert den Hintergrund.
	*/
	virtual void RenderBackground() = 0;
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


	/*
		Muss vor jedem Rendern aufgerufen werden.
	*/
	virtual void Begin() = 0;


	/*
		Muss nach jedem Rendern aufgerufen werden.
	*/
	virtual void End() = 0;

	IDirect3D9* d3d;
	IDirect3DDevice9* d3dDevice;
	D3DPRESENT_PARAMETERS d3dPP;

	Direct3DTexture* background;
	Direct3DTexture* tileset;

	Game* logic;

protected:

	HWND m_hAppWindow;
	HINSTANCE m_hAppInstance;
	UINT m_ClientWidth;
	UINT m_ClientHeight;
	std::string	m_AppTitle;
	DWORD m_WindowStyle;
	bool m_Paused;
	bool m_EnableFullscreen;
	float m_FPS;

protected:

	bool InitMainWindow();
};


#endif DIRECT_3D_WINDOW