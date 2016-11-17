#include "Window.h"
#include <iostream>

Window::Window() {
	this->window = glfwCreateWindow(560, 590, "Frogger", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	initViewport();

	this->background = new Texture("../textures/bg.jpg");

	this->renderer = new Renderer();

	initProjectionMatrix();

	this->controller = new Controller();
	glfwSetKeyCallback(window, Controller::key_callback);
}

void Window::render() {
	GLfloat start = 0;
	GLfloat dt = 0;

	while(!this->isWindowClosing()) {
		start = (GLfloat)glfwGetTime();
		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		GameLogic* logic = controller->getLogic();

		logic->doLogic(dt);

		vec3 color = vec3(0.0f, 0.0f, 0.0f);

		renderer->draw(background, Vec2(0.0f, 0.0f), Vec2(560.0f, 540.0f), color);

		for (int i = 0; i < logic->getObjects().size(); i++) {
			logic->getObjects().at(i)->draw(renderer);
		}

		logic->drawLabels(renderer);

		glfwSwapBuffers(window);

		dt = (GLfloat)glfwGetTime() - start;
	}
}

int Window::isWindowClosing() {
	return glfwWindowShouldClose(window);
}

void Window::initViewport() {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	this->width = width;
	this->height = height;

	glViewport(0, 0, width, height);
}

void Window::initProjectionMatrix() {
	Mat4 projection = Mat4::ortho(0.0f, static_cast<GLfloat>(this->width), static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);

	renderer->getShader()->use();
	renderer->getShader()->setUniformMatrix4("projection", projection);
}

Window::~Window() {
	delete controller;
	delete renderer;
}