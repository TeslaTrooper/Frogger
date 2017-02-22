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
	OpenGLTexture* background;

	void initViewport();
	void initProjectionMatrix();
	void initOpenGL();
public:
	OpenGLWindow();
	~OpenGLWindow();


	/*
		@return gibt einen Wert zur�ck, der Angibt, ob das Fenster sich schlie�en soll.
				Ein Wert != 0 bedeuted, dass das Fenster sich schlie�en soll.
	*/
	int isWindowClosing();


	/*
		F�hrt die Hauptschleife aus.
	*/
	void render();
};

#endif WINDOW