#include "Label.h"

std::map<char, util::Rectangle>* Label::charCollection;

std::map<char, util::Rectangle>* Label::initTextures() {
	std::map<char, util::Rectangle>* nums = new std::map<char, util::Rectangle>();

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

Label::Label(string text, bool useAsDescription) {
	visible = true;
	durationValue = 0;
	descriptionLeftAligned = true;
	isStaticLabel = useAsDescription;

	if (charCollection == nullptr) {
		charCollection = initTextures();
	}

	chars = new vector<util::Rectangle>();
	charPositions = new vector<Vec2>();

	setScale(1.0f);

	setText(text);

	this->descriptionText = text;
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

void Label::setText(string text) {
	chars->clear();

	string tmpString;

	if (isStaticLabel) {
		if (descriptionLeftAligned) {
			tmpString.append(descriptionText).append(" ").append(text);
		} else {
			tmpString.append(text).append(" ").append(descriptionText);
		}
	} else {
		tmpString = text;
	}

	for (int i = 0; i < tmpString.length(); i++) {
		char c = tmpString.at(i);
		chars->push_back(charCollection->at(c));
	}

	alignPosition();
}

vector<Drawable> Label::getDrawables() {
	vector<Drawable> drawables = std::vector<Drawable>();

	for (int i = 0; i < chars->size(); i++) {
		if (visible)
			drawables.push_back({ Mat4::getTransformation(charPositions->at(i), getSize(i)), chars->at(i) });
		else
			drawables.push_back({ Mat4::getTransformation(charPositions->at(i).sub(Vec2(0.0f, 1000.f)), getSize(i)), chars->at(i) });
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

void Label::hideAfter(float duration) {
	if (duration <= 0) return;

	this->duration = duration;
	this->durationValue = duration;
}

void Label::update(float dt) {
	if (!isVisible()) return;

	this->duration -= dt;
	if (duration < 0) {
		hide();
		duration = durationValue;
	}
}

void Label::useStaticLabel() {
	isStaticLabel = true;
}