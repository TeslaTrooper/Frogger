#include "OpenGLWindow.h"

OpenGLWindow::OpenGLWindow() : BaseOpenGLWindow(500, 100, WINDOW_WIDTH, WINDOW_HEIGHT, "Frogger | OpenGL") {
	registerKeyCallback(Controller::key_callback);

	this->controller = new Controller();
	controller->getLogic()->create();

	this->renderer = new OpenGLRenderer(controller->getLogic());
}

void OpenGLWindow::loop(float dt) {
	controller->getLogic()->gameLoop(dt);
	renderer->update(dt);
}

OpenGLWindow::~OpenGLWindow() {
	delete controller;
	delete renderer;
}