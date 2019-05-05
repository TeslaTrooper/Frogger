#ifndef WINDOW
#define WINDOW

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Vec2.h"
#include "Mat4.h"
#include "OpenGLRenderer.h"
#include "Util.h"
#include "BaseOpenGLWindow.h"
#include "BaseOpenGLRenderer.h"

class OpenGLWindow : public BaseOpenGLWindow {

	Game* const game;

public:

	OpenGLWindow(BaseOpenGLRenderer* const renderer, Game* const game);

	void checkInput(float dt) override;

};

#endif WINDOW