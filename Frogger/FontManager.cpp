#include "FontManager.h"

FontManager::FontManager() {
	labels = new map<string, Label*>();
}

FontManager::~FontManager() {
	labels->clear();
	delete labels;
}

void FontManager::createNewLabel(string identifer, string text, glm::vec2 position, float scale) {
	(*labels)[identifer] = new Label(text);

	setPosition(identifer, position);
	setScale(identifer, scale);
}

void FontManager::drawLabels(Renderer* renderer) {
	for (it_type iterator = labels->begin(); iterator != labels->end(); iterator++) {
		iterator->second->draw(renderer);
	}
}

void FontManager::setPosition(string identifier, glm::vec2 position) {
	labels->at(identifier)->setPosition(position);
}

void FontManager::setScale(string identifier, float scale) {
	labels->at(identifier)->setScale(scale);
}

void FontManager::setText(string indentifier, string text) {
	labels->at(indentifier)->setText(text);
}