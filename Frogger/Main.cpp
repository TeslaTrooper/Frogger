#include "OpenGLWindow.h"
#include "OpenGLRenderer.h"
#include "APIFactory.h"

int main(void) {
	Game* game = APIFactory::getInstance();
	BaseOpenGLRenderer* renderer = new OpenGLRenderer(game);

	BaseOpenGLWindow* window = new OpenGLWindow(renderer, game);
	window->run();

	delete window;

	return 0;
}