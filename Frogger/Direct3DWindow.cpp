#include <Windows.h>
#include <chrono>

#include "Constants.h"
#include "Direct3DRenderer.h"
#include "GameLogic.h"

Direct3DRenderer renderer;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// the handle for the window, filled by a function
	HWND hWnd;
	// this struct holds information for the window class
	WNDCLASSEX wc;

	// clear out the window class for use
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	// fill in the struct with the needed information
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = "WindowClass1";

	// register the window class
	RegisterClassEx(&wc);

	// create the window and use the result as the handle
	hWnd = CreateWindowEx(NULL,
		"WindowClass1",    // name of the window class
		"Frogger | Direct3D",   // title of the window
		WS_OVERLAPPEDWINDOW,    // window style
		500,    // x-position of the window
		100,    // y-position of the window
		WINDOW_WIDTH,    // width of the window
		WINDOW_HEIGHT,    // height of the window
		NULL,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		hInstance,    // application handle
		NULL);    // used with multiple windows, NULL

				  // display the window on the screen
	renderer.init(hWnd);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	// enter the main loop:

	// this struct holds Windows event messages
	MSG msg;

	GameLogic* logic = new GameLogic();
	logic->create();

	std::chrono::time_point<std::chrono::steady_clock> start, finish;
	long dt = 0;

	while (true) {
		// wait for the next message in the queue, store the result in 'msg'
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// translate keystroke messages into the right format
			TranslateMessage(&msg);

			// send the message to the WindowProc function
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT) {
			return FALSE;
		}

		start = std::chrono::high_resolution_clock::now();
		//if (dt < (float)(1000.f / FRAME_RATE) / 1000.f && dt > 0) {


		logic->gameLoop(dt / 1e9);

		renderer.beginRendering();

		const Drawable d = {
			Vec2(0, 0),
			Vec2(560, 540),
			{Vec2(0,0), Vec2(TILES_X, 13.5)}
		};
		renderer.renderBg(d);

		map<DrawableType, std::vector<Drawable>> drawables = logic->getDrawables();
		for (int i = 0; i < drawables.at(DrawableType::OBJECT).size(); i++) {
			renderer.render(drawables.at(DrawableType::OBJECT).at(i));
		}
		for (int i = 0; i < drawables.at(DrawableType::FONT).size(); i++) {
			renderer.render(drawables.at(DrawableType::FONT).at(i));
		}

		renderer.endRenderering();

		finish = std::chrono::high_resolution_clock::now();

		dt = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
	}

	renderer.clean();

	// return this part of the WM_QUIT message to Windows
	return msg.wParam;
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	// sort through and find what code to run for the message given
	switch (message) {
		// this message is read when the window is closed
		case WM_DESTROY: {
			// close the application entirely
			PostQuitMessage(0);
			return 0;
		} break;
	}

	// Handle any messages the switch statement didn't
	return DefWindowProc(hWnd, message, wParam, lParam);
}