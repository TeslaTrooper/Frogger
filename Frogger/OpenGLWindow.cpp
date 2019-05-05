#include "OpenGLWindow.h"

OpenGLWindow::OpenGLWindow(BaseOpenGLRenderer* const renderer, Game* const game) :
	BaseOpenGLWindow(game, renderer, 500, 100, WINDOW_WIDTH, WINDOW_HEIGHT, "Frogger | OpenGL"), game(game) {
	registerKeyListener();
}

void OpenGLWindow::checkInput(float dt) {
	bool space = UserInputController::isKeyPressed(KEY_SPACE);
	bool left = UserInputController::isKeyPressed(KEY_LEFT);
	bool right = UserInputController::isKeyPressed(KEY_RIGHT);
	bool down = UserInputController::isKeyPressed(KEY_DOWN);
	bool up = UserInputController::isKeyPressed(KEY_UP);

	if (space) game->restart();
	if (up)		game->moveFrog(Direction::UP);
	if (left)	game->moveFrog(Direction::LEFT);
	if (right)	game->moveFrog(Direction::RIGHT);
	if (down)	game->moveFrog(Direction::DOWN);
}