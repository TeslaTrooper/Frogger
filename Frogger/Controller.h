#ifndef CONTROLLER
#define CONTROLLER

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Game.h"

class Controller {
	static Game* gameLogic;

public:
	Controller();
	~Controller();

	Game* getLogic();
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
};

#endif CONTROLLER