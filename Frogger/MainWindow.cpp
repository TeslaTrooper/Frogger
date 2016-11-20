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

		logic->gameLoop(dt);

		renderer->draw(background, Vec2(0.0f, 0.0f), Vec2(560.0f, 540.0f));

		map<DrawableType, std::vector<Drawable>> drawables = logic->getDrawables();
		for (int i = 0; i < drawables.at(DrawableType::OBJECT).size(); i++) {
			renderer->draw(drawables.at(DrawableType::OBJECT).at(i));
		}
		for (int i = 0; i < drawables.at(DrawableType::FONT).size(); i++) {
			renderer->draw(drawables.at(DrawableType::FONT).at(i));
		}

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