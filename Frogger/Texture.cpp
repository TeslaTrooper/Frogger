#include "Texture.h"

Texture::~Texture() {}

void Texture::load() {
	const char* f = this->file.c_str();

	this->binaryData = SOIL_load_image(f, &this->width, &this->height, 0, this->imageType);
	const char* res = SOIL_last_result();
}

unsigned char* Texture::getBinaryData() {
	return this->binaryData;
}

void Texture::configure() {
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, getWidth(), getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, getBinaryData());
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(getBinaryData());
	glBindTexture(GL_TEXTURE_2D, 0);

	configured = true;
}

void Texture::bind() {
	if (!configured) {
		configure();
	}

	glBindTexture(GL_TEXTURE_2D, textureId);
}