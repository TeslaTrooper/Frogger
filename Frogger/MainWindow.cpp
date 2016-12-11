#include <iostream>

#include "Window.h"

Window::Window() {
	this->window = glfwCreateWindow(560, 590, "Frogger", nullptr, nullptr);
	glfwSetWindowPos(this->window, 500, 100);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	initViewport();

	this->background = new Texture("../textures/bg.raw", Vec2(560, 540));

	this->renderer = new Renderer();

	Texture* tileset = new Texture("../textures/tilesetNoAlpha.raw", Vec2(400, 400));
	renderer->setTileset(tileset);

	initProjectionMatrix();

	this->controller = new Controller();
	controller->getLogic()->create();

	glfwSetKeyCallback(window, Controller::key_callback);

	vector<int> a = vector<int>();
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);

	std::cout << a.front() << endl;
	vector<int>::iterator b = std::find(a.begin(), a.end(), 3);
	a.erase(b);
	a.clear();
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

		Rectangle r = { Vec2(0.0f, 0.0f), Vec2(560.0f, 540.0f) };
		renderer->draw(background, r);

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