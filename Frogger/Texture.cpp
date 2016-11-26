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

		if (*rawData == '\n' || *rawData == '\r' || *rawData == '\n' || *rawData == '\t') { // Kontrollzeichen überspringen
			rawData++;
			continue;
		}

		if (*rawData == '\"' && *(rawData + 1) == '\r') { // " zeichen am Ende einer Zeile erkennen
			rawData += 2;
			continue;
		}

		if (*rawData == '\"' && *(rawData - 1) == '\t') { // " zeichen am Anfang einer Zeile erkennen
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

		HEADER_PIXEL(pixelData, data);
		data += bands;
		ctr += bands;
	}

	data -= pixelCount * bands;





	//const char* f = this->file.c_str();

	//char a = '0';

	/*if (this->file == "../textures/carOrange.jpg") {
		useSOIL = false;
		this->width = imgWidth;
		this->height = imgHeight;

		data = new unsigned char[imgWidth*imgHeight*3];
		for (int i = 0; i < imgWidth*imgHeight; i++) {
			if (*header_data == '`') {
				int a = 5;
			}
			
			data+=3;
		}

		data -= imgWidth * imgHeight * 3;
	} else {*/
		//useSOIL = true;
		//this->binaryData = SOIL_load_image(f, &this->width, &this->height, 0, this->imageType);
	//}

	//const char* res = SOIL_last_result();
}

void Texture::configure() {
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	//if(!useSOIL)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, getWidth(), getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	//else
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, getWidth(), getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, getBinaryData());
	glGenerateMipmap(GL_TEXTURE_2D);
	//delete[] data;
	//SOIL_free_image_data(getBinaryData());
	glBindTexture(GL_TEXTURE_2D, 0);

	configured = true;
}

void Texture::bind() {
	if (!configured) {
		configure();
	}

	glBindTexture(GL_TEXTURE_2D, textureId);
}