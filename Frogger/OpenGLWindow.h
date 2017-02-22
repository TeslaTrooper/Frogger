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
		@return gibt einen Wert zurück, der Angibt, ob das Fenster sich schließen soll.
				Ein Wert != 0 bedeuted, dass das Fenster sich schließen soll.
	*/
	int isWindowClosing();


	/*
		Führt die Hauptschleife aus.
	*/
	void render();
};

#endif WINDOW