#include "Label.h"

std::map<char, Texture*>* Label::charCollection;

std::map<char, Texture*>* Label::initTextures() {
	std::map<char, Texture*>* nums = new std::map<char, Texture*>();

	for (int i = 0; i < 10; i++) {
		(*nums)[*std::to_string(i).c_str()] = new Texture("../textures/" + std::to_string(i) + ".png");
	}

	for (int i = 65; i < 91; i++) {
		(*nums)[i] = new Texture("../textures/" + std::to_string(i) + ".png");
	}

	return nums;
}

// ---------- static -------------

Label::Label(std::string text) {
	if (charCollection == nullptr) {
		charCollection = initTextures();
	}

	chars = new std::vector<Texture*>();
	charPositions = new std::vector<glm::vec2>();

	setScale(1.0f);

	setText(text);
}

Label::~Label() {
	chars->clear();
	delete chars;

	charPositions->clear();
	delete charPositions;
}

void Label::setPosition(glm::vec2 position) {
	this->position = position;
	alignPosition();
}

glm::vec2 Label::getSize(int index) {
	return glm::vec2(chars->at(index)->getWidth() * scale, chars->at(index)->getHeight() * scale);
}

glm::vec2 Label::getPosition() {
	return position;
}

void Label::setScale(float scale) {
	this->scale = scale;
	alignPosition();
}

void Label::setText(std::string text) {
	chars->clear();

	for (int i = 0; i < text.length(); i++) {
		char c = text.at(i);
		Texture* t = charCollection->at(c);

		chars->push_back(charCollection->at(c));
	}

	alignPosition();
}

void Label::draw(Renderer* renderer) {
	for (int i = 0; i < this->chars->size(); i++) {
		renderer->draw(chars->at(i), charPositions->at(i), getSize(i), glm::vec3(0.0f, 0.0f, 0.0f));
	}
}

void Label::alignPosition() {
	charPositions->clear();

	int offset = 0;
	for (int i = 0; i < chars->size(); i++) {
		charPositions->push_back(glm::vec2(position.x + offset, position.y));
		offset += (int) getSize(i).x;
	}
}
