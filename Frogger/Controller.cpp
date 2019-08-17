#include "Controller.h"

Controller::Controller(BaseRenderer* const renderer, Game* const game) :
	BaseController(game, renderer, 500, 100, WINDOW_WIDTH, WINDOW_HEIGHT, "Frogger | OpenGL"), game(game) {
	registerKeyListener();
}

void Controller::checkInput(float dt) {
	bool space = KeyCallbackHandler::isKeyPressed(KEY_SPACE);
	bool left = KeyCallbackHandler::isKeyPressed(KEY_LEFT);
	bool right = KeyCallbackHandler::isKeyPressed(KEY_RIGHT);
	bool down = KeyCallbackHandler::isKeyPressed(KEY_DOWN);
	bool up = KeyCallbackHandler::isKeyPressed(KEY_UP);

	if (space) game->restart();
	if (up)		game->moveFrog(Direction::UP);
	if (left)	game->moveFrog(Direction::LEFT);
	if (right)	game->moveFrog(Direction::RIGHT);
	if (down)	game->moveFrog(Direction::DOWN);
}