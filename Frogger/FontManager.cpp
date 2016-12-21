#include "FontManager.h"

FontManager::FontManager() {
	labels = map<string, Label*>();
}

FontManager::~FontManager() {
	labels.clear();
}

void FontManager::createNewLabel(string identifier, string text) {
	createNewLabel(identifier, text, Vec2(), false, 1.f);
}

void FontManager::createNewLabel(string identifer, string text, Vec2 position, bool useAsDescription, float scale) {
	labels[identifer] = new Label(text, useAsDescription);

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

void FontManager::hideAfter(string indentifier, float duration) {
	labels.at(indentifier)->hideAfter(duration);
}

void FontManager::update(float dt) {
	for (it_type iterator = labels.begin(); iterator != labels.end(); iterator++) {
		Label* label = iterator->second;

		if (label->isAutoHiding()) {
			label->update(dt);
		}
	}
}

void FontManager::alignDescriptionLeft(string identifier, bool value) {
	labels.at(identifier)->alignDescriptionLeft(value);
}

void FontManager::useStaticLabel(string identifier) {
	labels.at(identifier)->useStaticLabel();
}

float FontManager::getScale(string identifier) {
	return labels.at(identifier)->getScale();
}

int FontManager::getLength(string identifier) {
	return labels.at(identifier)->getLength();
}