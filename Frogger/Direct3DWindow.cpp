#include "Direct3DWindow.h"

namespace {
	Direct3DWindow* mainWin = NULL;
}

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//Forward messages
	if (mainWin)
		return (mainWin->MsgProc(hwnd, msg, wParam, lParam));
	else
		return DefWindowProc(hwnd, msg, wParam, lParam);
}

Direct3DWindow::Direct3DWindow(HINSTANCE hInstance) {
	m_hAppInstance = hInstance;
	m_hAppWindow = NULL;
	m_AppTitle = "Frogger | DirectX";
	m_ClientWidth = WINDOW_WIDTH;
	m_ClientHeight = WINDOW_HEIGHT;
	m_EnableFullscreen = false; //not used yet anyway
	m_Paused = false; //application starts unpaused
	m_FPS = 0;
	m_WindowStyle = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX; //Standard non-resizeable window
	mainWin = this; //Set our global pointer
}

Direct3DWindow::~Direct3DWindow() {}

int Direct3DWindow::Run() {
	MSG msg = { 0 }; //sets all members to null. (empty set)

	std::chrono::time_point<std::chrono::steady_clock> start, finish;
	long dt = 0;

	while (WM_QUIT != msg.message) { //While our message doesn't equal WM_QUIT {
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) {
			TranslateMessage(&msg); //Translate message
			DispatchMessage(&msg); //Dispatch message
		} else {
			if (!m_Paused) {
				Update(0.0f); //pass in 0 for now until later tutorial

				start = std::chrono::high_resolution_clock::now();
				logic->gameLoop(dt / 1e9);

				Begin();

				RenderBackground();

				/*Drawable d = {
					Vec2(100, 100),
					Vec2(40, 40),
					{Vec2(1, 1), Vec2(51.2f, 51.2f)}
				};

				Render(d, tileset);*/

				map<DrawableType, std::vector<Drawable>> drawables = logic->getDrawables();
				for (int i = 0; i < drawables.at(DrawableType::OBJECT).size(); i++) {
					Render(drawables.at(DrawableType::OBJECT).at(i), tileset);
				}
				for (int i = 0; i < drawables.at(DrawableType::FONT).size(); i++) {
					Render(drawables.at(DrawableType::FONT).at(i), tileset);
				}

				End();

				finish = std::chrono::high_resolution_clock::now();

				dt = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
			} else {
				Sleep(100); //Free up cpu for 1/10 of a second
			}
		}
	}

	return static_cast<int>(msg.wParam);
}

bool Direct3DWindow::Init() {
	//Initialize main window
	if (!InitMainWindow())
		return false;
	if (!initDirect3D())
		return false;
	initTextures();

	//If all succeeds return true
	return true;
}

bool Direct3DWindow::InitMainWindow() {
	//First step:
	//Create a window class structure to define our window
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEX)); //ZERO it out
	wcex.cbClsExtra = 0; //no extra bytes
	wcex.cbWndExtra = 0; //no extra bytes
	wcex.cbSize = sizeof(WNDCLASSEX); //set size in bytes
	wcex.style = CS_HREDRAW | CS_VREDRAW; //Basically states that window should be redraw both HORIZ. and VERT.
	wcex.hInstance = m_hAppInstance; //Set handle to application instance;
	wcex.lpfnWndProc = MainWndProc; //Set message procedure to our globally defined one
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION); //Set window icon (standard application icon)
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW); //Set window arrow (standard windows arrow)
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); //Set clear background
	wcex.lpszClassName = "WIN32WINDOWCLASS"; //Name it w.e you like. 
	wcex.lpszMenuName = NULL; //We are not using a menu at this time.
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION); //Set small window icon (standard application icon)

													//Now we must register the window class
													//Here is an example of some simple error checking
													//This can be quite useful for larger projects to debug errors
	if (!RegisterClassEx(&wcex)) {
		MessageBox(NULL, "Failed to register window class", NULL, NULL);
		return false;
	}

	//Second step:
	//Cache the correct window dimensions
	RECT r = { 0, 0, m_ClientWidth, m_ClientHeight };
	AdjustWindowRect(&r, m_WindowStyle, false); //Use our window style
	int width = r.right - r.left;  //correct width based on requested client size
	int height = r.bottom - r.top;  //correct height based on requested client size
	int x = GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2; //Centers window on desktop
	int y = GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2; //Centers window on desktop

															//Third step:
															//Create our window
															//lpClassName: MUST BE SAME AS ABOVE FROM WINDOW CLASS
															//lpWindowTitle: SHOULD BE m_AppTitle.c_str()
	m_hAppWindow = CreateWindow("WIN32WINDOWCLASS", m_AppTitle.c_str(), m_WindowStyle, x, y,
		width, height, NULL, NULL, m_hAppInstance, NULL);
	//Check window creation
	if (!m_hAppWindow){
		MessageBox(NULL, "Failed to create window", NULL, NULL);
		return false;
	}

	GameLogic* logic = new GameLogic();
	logic->create();

	this->logic = logic;

	//Fourth step:
	//Show window
	//SW_SHOW: Stand window display code, take the place of nCmdShow from entry point.
	ShowWindow(m_hAppWindow, SW_SHOW);

	//If all succeeded return true
	return true;
}

bool Direct3DWindow::initDirect3D() {
	this->d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9 caps;
	this->d3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	int vp;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) {
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	} else {
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	if (caps.DevCaps & D3DPTEXTURECAPS_POW2) {
		MessageBox(NULL, "Only pow 2 textures supported!", NULL, NULL);
	}

	if (caps.DevCaps & D3DPTEXTURECAPS_SQUAREONLY) {
		MessageBox(NULL, "Only squared textures supported!", NULL, NULL);
	}

	ZeroMemory(&this->d3dPP, sizeof(D3DPRESENT_PARAMETERS));
	this->d3dPP.BackBufferWidth = WINDOW_WIDTH;
	this->d3dPP.BackBufferHeight = WINDOW_HEIGHT;
	this->d3dPP.BackBufferFormat = D3DFMT_A8R8G8B8; //32 bit format
	this->d3dPP.Windowed = true; //start windowed
	this->d3dPP.BackBufferCount = 1; //Double buffered. 
	this->d3dPP.MultiSampleType = D3DMULTISAMPLE_NONE; //No multisampling (way too intensive)
	this->d3dPP.MultiSampleQuality = 0;
	this->d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	this->d3dPP.hDeviceWindow = m_hAppWindow;
	this->d3dPP.Flags = 0;
	this->d3dPP.EnableAutoDepthStencil = true;
	this->d3dPP.AutoDepthStencilFormat = D3DFMT_D24S8;
	this->d3dPP.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	this->d3dPP.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	this->d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hAppWindow, vp, &this->d3dPP, &this->d3dDevice);
	if (!this->d3dDevice)
		MessageBox(NULL, "Error creating device", NULL, NULL);

	D3DVIEWPORT9 viewport;
	ZeroMemory(&viewport, sizeof(D3DVIEWPORT9));
	viewport.X = 0;
	viewport.Y = 0;
	viewport.Width = WINDOW_WIDTH;
	viewport.Height = WINDOW_HEIGHT;
	viewport.MinZ = -1;
	viewport.MaxZ = 1;

	this->d3dDevice->SetViewport(&viewport);

	return true;
}

void Direct3DWindow::initTextures() {
	this->background = new Direct3DTexture("../textures/bg.png", &this->d3dDevice);
	this->tileset = new Direct3DTexture("../textures/tileset.png", &this->d3dDevice);
}

LRESULT Direct3DWindow::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	//Switch statement on the message passed to us
	switch (msg) {
		//CASE: WM_DESTROY, our application is told to destroy itself
		case WM_DESTROY: 
			PostQuitMessage(0); //Tell the application to quit
			return 0;

		case WM_ACTIVATE:
			if (LOWORD(wParam) == WA_INACTIVE)
				//Application should pause itself
				m_Paused = true;
			else //Otherwise, the application is not paused
				m_Paused = false;
			return 0;

		//CASE: WM_KEYDOWN, user pressed a key on keyboard
		case WM_KEYDOWN:
			//Switch on the WPARAM, (which stores the keycode)
			switch (wParam) {
				//CASE: VK_ESCAPE, user pressed the escape key
				case VK_ESCAPE:
					PostQuitMessage(0); //Tell application to quit
					return 0;
				case VK_RIGHT:
					logic->moveFrog(Direction::RIGHT); break;
				case VK_LEFT:
					logic->moveFrog(Direction::LEFT); break;
				case VK_UP:
					logic->moveFrog(Direction::UP); break;
				case VK_DOWN:
					logic->moveFrog(Direction::DOWN); break;
				case VK_SPACE:
					logic->restart(); break;
			}
			return 0;
	}

	//Always return the default window procedure if we don't catch anything
	return DefWindowProc(hwnd, msg, wParam, lParam);
}