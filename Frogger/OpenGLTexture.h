#ifndef TEXTURE
#define TEXTURE

#include <SOIL.h>
#include <GL/glew.h>
#include <string>

#include "Util.h"

using namespace std;

class OpenGLTexture {
	unsigned char* data;

	int width, height;
	GLuint textureId;
	bool configured = false;

	void load(char* rawData);
	void loadAdvanced(unsigned char* rawData, long fsize);
	void configure();

public:
	OpenGLTexture(char* file, Vec2 dimension);

	~OpenGLTexture();

	int getWidth() const { return this->width; };
	int getHeight() const { return this->height; };
	void bind();
};

#endif TEXTURE