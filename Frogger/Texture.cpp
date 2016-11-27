#include "Texture.h"

Texture::~Texture() {}

Texture::Texture(char* file, Vec2 dimension) {
	this->width = dimension.x;
	this->height = dimension.y;

	FILE *f = fopen(file, "rb");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);

	char *string = (char *) malloc(fsize + 1);
	fread(string, fsize, 1, f);
	fclose(f);

	string[fsize] = 0;

	load(string);
}

void Texture::load(char* rawData) {
	int pixelCount = getWidth() * getHeight();
	int bands = 3;

	data = new unsigned char[pixelCount * bands];
	int ctr = 0;

	while(*rawData != '\0') {
		char* pixelData = new char[4];
		int validCharsCount = 0;

		if (*rawData == '\n' || *rawData == '\r' || *rawData == '\n' || *rawData == '\t') {
			rawData++;
			continue;
		}

		if (*rawData == '\"' && *(rawData + 1) == '\r') {
			rawData += 2;
			continue;
		}

		if (*rawData == '\"' && *(rawData - 1) == '\t') {
			rawData++;
			continue;
		}

		while (validCharsCount < 4) {
			if (*rawData == '\\' && *(rawData + 1) == '\"') {
				rawData++;
				continue;
			}

			if (*rawData == '\\' && *(rawData + 1) == '\\') {
				rawData++;
				continue;
			}

			*pixelData = *rawData;

			pixelData++;
			rawData++;

			validCharsCount++;
		}

		pixelData -= 4;

		if (*rawData == '\0') {
			break;
		}

		CALC_PIXEL_RGB(pixelData, data);
		data += bands;
		ctr += bands;
	}

	data -= pixelCount * bands;
}

void Texture::configure() {
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, getWidth(), getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	delete[] data;

	configured = true;
}

void Texture::bind() {
	if (!configured) {
		configure();
	}

	glBindTexture(GL_TEXTURE_2D, textureId);
}