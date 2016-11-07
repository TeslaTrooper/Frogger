#ifndef TEXTURE
#define TEXTURE

#include <SOIL.h>
#include <GL/glew.h>
#include <string>

class Texture {
	unsigned char* binaryData;
	int width, height;
	int imageType;
	std::string file;
	GLuint textureId;
	bool configured = false;

	void load();
	void configure();

public:
	Texture(std::string file) : file(file), imageType(SOIL_LOAD_RGBA) {
		this->load();
	};

	~Texture();

	unsigned char* getBinaryData();
	int getImageType() { return this->imageType; };
	void setImageType(int type) { this->imageType = imageType; };
	int getWidth() { return this->width; };
	int getHeight() { return this->height; };
	GLuint getTextureId() { return this->textureId; };
	void bind();
};

#endif TEXTURE