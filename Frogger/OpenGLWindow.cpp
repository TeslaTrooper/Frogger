#include "OpenGLWindow.h"

OpenGLWindow::OpenGLWindow() {
	initOpenGL();

	this->window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Frogger", nullptr, nullptr);
	glfwSetWindowPos(this->window, 500, 100);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	initViewport();

	Texture* tileset = new Texture("../textures/tilesetNoAlpha.raw", Vec2(400, 400));
	this->background = new Texture("../textures/bg.raw", Vec2(560, 540));
	
	

	this->renderer = new OpenGLRenderer();

	//Texture* tileset = new Texture("../textures/tilesetNoAlpha.raw", Vec2(400, 400));
	
	renderer->setTileset(tileset);

	initProjectionMatrix();

	this->controller = new Controller();
	controller->getLogic()->create();

	glfwSetKeyCallback(window, Controller::key_callback);
}

void OpenGLWindow::render() {
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

	glfwTerminate();
}

int OpenGLWindow::isWindowClosing() {
	return glfwWindowShouldClose(window);
}

void OpenGLWindow::initViewport() {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	this->width = width;
	this->height = height;

	glViewport(0, 0, width, height);
}

void OpenGLWindow::initProjectionMatrix() {
	Mat4 projection = Mat4::ortho(0.0f, static_cast<GLfloat>(this->width), static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);

	renderer->getShader()->use();
	renderer->getShader()->setUniformMatrix4("projection", projection);
}

void OpenGLWindow::initOpenGL() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

OpenGLWindow::~OpenGLWindow() {
	delete controller;
	delete renderer;
}