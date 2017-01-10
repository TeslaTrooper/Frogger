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

class OpenGLWindow {
	int width, height;

	Controller* controller;
	OpenGLRenderer* renderer;
	GLFWwindow* window;
	GLuint shaderProgram, vbo, vao, ebo;
	Texture* background;

	void initViewport();
	void initProjectionMatrix();
public:
	OpenGLWindow();
	~OpenGLWindow();

	int isWindowClosing();
	void render();
};

#endif WINDOW