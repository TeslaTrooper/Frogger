#include "FontManager.h"

FontManager::FontManager() {
	labels = map<string, Label*>();
}

FontManager::~FontManager() {
	labels.clear();
}

void FontManager::createNewLabel(string identifer, string text, Vec2 position, float scale) {
	labels[identifer] = new Label(text);

	setPosition(identifer, position);
	setScale(identifer, scale);
}

void FontManager::setPosition(string identifier, Vec2 position) {
	labels.at(identifier)->setPosition(position);
}

void FontManager::setScale(string identifier, float scale) {
	labels.at(identifier)->setScale(scale);
}

void FontManager::setText(string indentifier, string text) {
	labels.at(indentifier)->setText(text);
}

vector<Drawable> FontManager::getDrawables() {
	vector<Drawable> drawables = vector<Drawable>();

	for (it_type iterator = labels.begin(); iterator != labels.end(); iterator++) {
		vector<Drawable> tmpDrawables = iterator->second->getDrawables();

		for (int i = 0; i < iterator->second->getLength(); i++) {
			drawables.push_back(tmpDrawables.at(i));
		}
	}

	return drawables;
}

void FontManager::hideLabel(string identifier) {
	labels.at(identifier)->hide();
}

void FontManager::showLabel(string identifier) {
	labels.at(identifier)->show();
}

bool FontManager::isVisible(string identifier) {
	return labels.at(identifier)->isVisible();
}