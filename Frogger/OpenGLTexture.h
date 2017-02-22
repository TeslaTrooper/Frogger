#ifndef TEXTURE
#define TEXTURE

#include <SOIL.h>
#include <GL/glew.h>
#include <string>

#include "Util.h"

using namespace std;

class OpenGLTexture {
	unsigned char* imageData;

	int width, height;
	GLuint textureId;
	bool configured = false;

	void load(char* rawData);
	void loadAdvanced(unsigned char* rawData, unsigned short transR, unsigned short transG, unsigned short transB);
	void configure();

public:
	/*
		Erzeugt eine neue OpenGLTexture.
		@param file ist der Dateipfad
	*/
	OpenGLTexture(char* file);

	~OpenGLTexture();


	/*
		@return gibt die Breite der Textur zur�ck.
	*/
	int getWidth() const { return this->width; };


	/*
		Gibt die H�he der Textur zur�ck.
	*/
	int getHeight() const { return this->height; };


	/*
		Die Textur wird von OpenGL verwendet.
	*/
	void bind();
};

#endif TEXTURE