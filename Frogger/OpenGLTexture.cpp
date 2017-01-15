#include "OpenGLTexture.h"

OpenGLTexture::~OpenGLTexture() {}

OpenGLTexture::OpenGLTexture(char* file, Vec2 dimension) {
	this->width = dimension.x;
	this->height = dimension.y;

	FILE *f = fopen(file, "rb");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);

	//char *string = (char *) malloc(fsize + 1);
	//fread(string, fsize, 1, f);
	
	unsigned char *string = (unsigned char *)malloc(fsize + 1);
	fread(string, fsize, 1, f);
	fclose(f);

	string[fsize] = 0;

	
	/*if (file == "../textures/tilesetp.raw") {
		loadAdvanced(string, fsize);
	}
	else {
		char* a = (char*)string;
		load(a);
	}*/

	char* a = (char*)string;
	load(a);
}

void OpenGLTexture::load(char* rawData) {
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

void OpenGLTexture::loadAdvanced(unsigned char* rawData, long fsize) {
	data = new unsigned char[549919];
	int ctr = 0;
	vector<char> octal;

	for (int i = 0; i < fsize; i++) {
		if (i == 638338) {
			int a = 0;
			a += 1;
		}

		unsigned char prevChar;
		if (i > 0) {
			prevChar = *(rawData - 1);
		}
		unsigned char currentChar = *(rawData++);


		if (currentChar == ' ') {
			continue;
		}

		if (currentChar == '\"') {
			continue;
		}

		if (currentChar == '\r') {
			continue;
		}

		if (currentChar == '\n') {
			continue;
		}

		if ((int)currentChar < 48 || (int)currentChar > 55 && !((int)currentChar == 92)) {
			continue;
		}
			

		if (currentChar == '\\') {
			if (octal.size() == 0)
				continue;

			//if ((int)prevChar >= 48 || (int)prevChar <= 55) {
				string res;
				for (int j = 0; j < octal.size(); j++) {
					res += octal.at(j);
				}

				int octalNumber = stoi(res);

				int decimalNumber = 0, a = 0, rem;
				while (octalNumber != 0)
				{
					rem = octalNumber % 10;
					octalNumber /= 10;
					decimalNumber += rem * pow(8, a);
					++a;
				}

				unsigned char abc = static_cast<unsigned char>(decimalNumber);

				*(data + ctr) = abc;
				ctr++;

				octal.clear();
			//}

			continue;
		}

		if(((int)prevChar >= 48 || (int)prevChar <= 55) && octal.size() < 3)
			octal.push_back(currentChar);
	}
}

void OpenGLTexture::configure() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, getWidth(), getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	delete[] data;

	configured = true;
}

void OpenGLTexture::bind() {
	if (!configured) {
		configure();
	}

	glBindTexture(GL_TEXTURE_2D, textureId);
}