#include "OpenGLTexture.h"

OpenGLTexture::~OpenGLTexture() {}

OpenGLTexture::OpenGLTexture(char* file, Vec2 dimension) {
	//this->width = dimension.x;
	//this->height = dimension.y;

	FILE *f = fopen(file, "rb");

	// obtain file size:
	fseek(f, 0, SEEK_END);
	auto lSize = ftell(f);
	rewind(f);

	auto data = new unsigned char[lSize];
	fread(data, lSize, 1, f);
	fclose(f);

	
	/*if (file == "../textures/tilesetp.raw") {
		loadAdvanced(string, fsize);
	}
	else {
		char* a = (char*)string;
		load(a);
	}*/

	//char* a = (char*)string;
	//load(a);

	loadAdvanced(data, 174, 54, 158);
}

void OpenGLTexture::load(char* rawData) {
	int pixelCount = getWidth() * getHeight();
	int bands = 3;

	imageData = new unsigned char[pixelCount * bands];
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

		CALC_PIXEL_RGB(pixelData, imageData);
		imageData += bands;
		ctr += bands;
	}

	imageData -= pixelCount * bands;
}

void OpenGLTexture::loadAdvanced(unsigned char* rawData, unsigned short transR, unsigned short transG, unsigned short transB) {
	width = *reinterpret_cast<int*>(&rawData[18]);
	height = *reinterpret_cast<int*>(&rawData[22]);

	int padding = 0;
	while ((width * 3 + padding) % 4 != 0) {
		padding++;
	}
	int widthnew = width * 3 + padding;

	unsigned char* ret = new unsigned char[width * 4 * height];

	for (int line = 0; line < height; line++) {
		for (int column = 0, retcolumn = 0; column < widthnew - padding; column += 3, retcolumn += 4) {
			int ri = line * (width * 4) + retcolumn;
			int gi = ri + 1;
			int bi = ri + 2;
			int ai = ri + 3;

			ret[ri] = rawData[line * widthnew + column + 54 + 2];
			ret[gi] = rawData[line * widthnew + column + 54 + 1];
			ret[bi] = rawData[line * widthnew + column + 54 + 0];

			if (transR != 256 && transB != 265 && transG != 265 && 
				ret[ri] == static_cast<unsigned char>(transR) && 
				ret[gi] == static_cast<unsigned char>(transG) && 
				ret[bi] == static_cast<unsigned char>(transB)) {
				ret[ai] = 0;
			} else {
				ret[ai] = 255;
			}
		}
	}

	delete[] rawData;
	imageData = ret;
	/*data = new unsigned char[549919];
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
	}*/
}

void OpenGLTexture::configure() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, getWidth(), getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	delete[] imageData;

	configured = true;
}

void OpenGLTexture::bind() {
	if (!configured) {
		configure();
	}

	glBindTexture(GL_TEXTURE_2D, textureId);
}