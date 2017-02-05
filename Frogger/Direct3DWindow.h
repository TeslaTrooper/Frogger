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
#include "GameLogic.h"

using namespace util;

class Direct3DWindow {
public:
	Direct3DWindow(HINSTANCE hInstance);
	virtual ~Direct3DWindow(void);

	int Run();
	bool initDirect3D();
	void initTextures();
	
	virtual bool Init();
	virtual void Update(float dt) = 0;
	virtual void Render(Drawable& d, Direct3DTexture* texture) = 0;
	virtual void RenderBackground() = 0;
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	virtual void Begin() = 0;
	virtual void End() = 0;

	IDirect3D9* d3d;
	IDirect3DDevice9* d3dDevice;
	D3DPRESENT_PARAMETERS d3dPP;

	Direct3DTexture* background;
	Direct3DTexture* tileset;

	GameLogic* logic;

protected:
	//Members

	HWND m_hAppWindow;				//HANDLE to application window
	HINSTANCE m_hAppInstance;			//HANDLE to application instance
	UINT m_ClientWidth;			//Requested client width
	UINT m_ClientHeight;			//Requested client height
	std::string	m_AppTitle;				//Application title (window title bar)
	DWORD m_WindowStyle;			//Window style (e.g. WS_OVERLAPPEDWINDOW)
	bool m_Paused;				//True if application pause, false otherwise
	bool m_EnableFullscreen;		//True to enable fullscreen, false otherwise
	float m_FPS;					//Frames per second of our application

protected:

	bool InitMainWindow();
};


#endif DIRECT_3D_WINDOW