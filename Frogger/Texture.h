#ifndef TEXTURE
#define TEXTURE

#include <SOIL.h>
#include <GL/glew.h>
#include <string>

#include "Util.h"

using namespace std;

class Texture {
	unsigned char* data;

	int width, height;
	GLuint textureId;
	bool configured = false;

	void load(char* rawData);
	void configure();

public:
	Texture(char* file, Vec2 dimension);

	~Texture();

	int getWidth() { return this->width; };
	int getHeight() { return this->height; };
	void bind();
};

#endif TEXTURE