#include "Label.h"

std::map<char, Rectangle>* Label::charCollection;

std::map<char, Rectangle>* Label::initTextures() {
	std::map<char, Rectangle>* nums = new std::map<char, Rectangle>();

	for (int i = 0; i < 10; i++) {
		char current = *std::to_string(i).c_str();

		(*nums)[current] = numbers.at(current);
	}

	for (int i = 65; i < 91; i++) {
		(*nums)[i] = characters.at(i);
	}

	(*nums)[32] = characters.at(' ');

	return nums;
}

// ---------- static -------------

Label::Label(std::string text) {
	visible = true;

	if (charCollection == nullptr) {
		charCollection = initTextures();
	}

	chars = new std::vector<Rectangle>();
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
	return Vec2(chars->at(index).size.x * X_TILE_SIZE * scale, chars->at(index).size.y * X_TILE_SIZE * scale);
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
		chars->push_back(charCollection->at(c));
	}

	alignPosition();
}

std::vector<Drawable> Label::getDrawables() {
	std::vector<Drawable> drawables = std::vector<Drawable>();

	for (int i = 0; i < chars->size(); i++) {
		if(visible)
			drawables.push_back({ charPositions->at(i), getSize(i), chars->at(i) });
		else
			drawables.push_back({ charPositions->at(i).sub(Vec2(0.0f, 1000)), getSize(i), chars->at(i) });
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