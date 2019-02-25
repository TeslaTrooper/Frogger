#ifndef WINDOW
#define WINDOW

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Controller.h"
#include "Vec2.h"
#include "Mat4.h"
#include "OpenGLRenderer.h"
#include "Util.h"
#include "BaseOpenGLWindow.h"
#include "BaseOpenGLRenderer.h"

class OpenGLWindow : public BaseOpenGLWindow {
	BaseOpenGLRenderer* renderer;

	Controller* controller;
	GLuint shaderProgram, vbo, vao, ebo;
	OpenGLTexture* background;

public:

	OpenGLWindow();
	~OpenGLWindow();

	void loop(float dt) override;

};

#endif WINDOW