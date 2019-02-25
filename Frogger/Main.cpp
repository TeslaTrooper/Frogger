#include "OpenGLWindow.h"
#include "Direct3DWindow.h"

int main(void) {
	BaseOpenGLWindow* window = new OpenGLWindow();
	window->run();

	return 0;
}