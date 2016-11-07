#ifndef WINDOW
#define WINDOW

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Controller.h"

class Window {
	int width, height;

	Controller* controller;
	Renderer* renderer;
	GLFWwindow* window;
	GLuint shaderProgram, vbo, vao, ebo;
	Texture* background;

	void initViewport();
	void initProjectionMatrix();
public:
	Window();
	~Window();

	int isWindowClosing();
	void render();
};

#endif WINDOW