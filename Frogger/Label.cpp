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
	charPositions = new std::vector<Vec2>();

	setScale(1.0f);

	setText(text);
}

Label::~Label() {
	chars->clear();
	delete chars;

	charPositions->clear();
	delete charPositions;
}

void Label::setPosition(Vec2 position) {
	this->position = position;
	alignPosition();
}

Vec2 Label::getSize(int index) {
	return Vec2(chars->at(index)->getWidth() * scale, chars->at(index)->getHeight() * scale);
}

Vec2 Label::getPosition() {
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

std::vector<Drawable> Label::getDrawables() {
	std::vector<Drawable> drawables = std::vector<Drawable>();

	for (int i = 0; i < chars->size(); i++) {
		drawables.push_back({ charPositions->at(i), getSize(i), chars->at(i) });
	}

	return drawables;
}

void Label::alignPosition() {
	charPositions->clear();

	int offset = 0;
	for (int i = 0; i < chars->size(); i++) {
		charPositions->push_back(Vec2(position.x + offset, position.y));
		offset += (int) getSize(i).x;
	}
}

int Label::getLength() {
	return chars->size();
}