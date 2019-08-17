#include "Controller.h"
#include "Renderer.h"
#include "APIFactory.h"

int main(void) {
	Game* game = APIFactory::getInstance();
	BaseRenderer* renderer = new Renderer(game);

	BaseController* controller = new Controller(renderer, game);
	controller->run();

	delete controller;

	return 0;
}