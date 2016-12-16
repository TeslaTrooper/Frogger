#include "Controller.h"

GameLogic* Controller::gameLogic = new GameLogic();

Controller::Controller() {}

void Controller::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (action == GLFW_PRESS) {
		switch (key) {
			case GLFW_KEY_LEFT: Controller::gameLogic->moveFrog(Direction::LEFT); break;
			case GLFW_KEY_UP: Controller::gameLogic->moveFrog(Direction::UP); break;
			case GLFW_KEY_RIGHT: Controller::gameLogic->moveFrog(Direction::RIGHT); break;
			case GLFW_KEY_DOWN: Controller::gameLogic->moveFrog(Direction::DOWN); break;
			default: return;
		}
	}
};

GameLogic* Controller::getLogic() {
	return Controller::gameLogic;
}

Controller::~Controller() {
	delete Controller::gameLogic;
}