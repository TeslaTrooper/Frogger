#ifndef LABEL
#define LABEL

#include <glm\glm.hpp>
#include <vector>
#include <string>
#include "Texture.h"
#include <map>
#include <string>
#include "Renderer.h"

class Label {
	static std::map<char, Texture*>* charCollection;

	std::vector<Texture*>* chars;
	std::vector<glm::vec2>* charPositions;

	float scale = 1.0f;
	glm::vec2 position;

	void alignPosition();
	glm::vec2 getSize(int index);

public:
	Label(std::string text);
	~Label();

	void setPosition(glm::vec2 position);
	glm::vec2 getPosition();
	
	void setScale(float scale);
	void draw(Renderer* renderer);
	void setText(std::string text);

	static std::map<char, Texture*>* initTextures();
};

#endif LABEL