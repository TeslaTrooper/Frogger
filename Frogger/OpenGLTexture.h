#ifndef OPENGL_TEXTURE
#define OPENGL_TEXTURE

#include <SOIL.h>
#include <GL/glew.h>
#include <string>

#include "Util.h"
#include "Texture.h"

#define TRANS_R 174
#define TRANS_G 54
#define TRANS_B 158

using namespace std;

class OpenGLTexture : public Texture {

	void load(char* rawData);

public:
	/*
		Erzeugt eine neue OpenGLTexture.
		@param file ist der Dateipfad
	*/
	OpenGLTexture(char* file) : Texture(file, PixelDataType::RGBA) {
		prepare();
	};


	/*
		@return gibt die Breite der Textur zurück.
	*/
	int getWidth() const { return Texture::getWidth(); };


	/*
		Gibt die Höhe der Textur zurück.
	*/
	int getHeight() const { return Texture::getHeight(); };

	TextureInfo readTexture(const unsigned char* rawImageData) const override;
};

#endif OPENGL_TEXTURE