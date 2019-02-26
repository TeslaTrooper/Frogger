#include "OpenGLTexture.h"


void OpenGLTexture::load(char* rawData) {
	/*int pixelCount = getWidth() * getHeight();
	int bands = 3;

	imageData = new unsigned char[pixelCount * bands];
	int ctr = 0;

	while (*rawData != '\0') {
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

	imageData -= pixelCount * bands;*/
}

TextureInfo OpenGLTexture::readTexture(const unsigned char * rawImageData) const {
	const int width = *reinterpret_cast<const int*>(&rawImageData[18]);
	const int height = *reinterpret_cast<const int*>(&rawImageData[22]);

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

			ret[ri] = rawImageData[line * widthnew + column + 54 + 2];
			ret[gi] = rawImageData[line * widthnew + column + 54 + 1];
			ret[bi] = rawImageData[line * widthnew + column + 54 + 0];

			if (TRANS_R != 256 && TRANS_B != 265 && TRANS_G != 265 &&
				ret[ri] == static_cast<unsigned char>(TRANS_R) &&
				ret[gi] == static_cast<unsigned char>(TRANS_G) &&
				ret[bi] == static_cast<unsigned char>(TRANS_B)) {
				ret[ai] = 0;
			} else {
				ret[ai] = 255;
			}
		}
	}

	return { width, height, ret };
}
