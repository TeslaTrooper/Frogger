#ifndef CONTROLLER
#define CONTROLLER

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GameLogic.h"

class Controller {
	static GameLogic* gameLogic;

public:
	Controller();
	~Controller();

	GameLogic* getLogic();
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
};

#endif CONTROLLER