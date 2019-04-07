#include "UIManager.h"

UIManager::UIManager() {
	this->fontManager = FontManager();

	scalesOnAlignment[LEFT] = vector<float>();
	scalesOnAlignment[TOP] = vector<float>();
	scalesOnAlignment[RIGHT] = vector<float>();
	scalesOnAlignment[DOWN] = vector<float>();
	scalesOnAlignment[LEFT_DOWN] = vector<float>();
	scalesOnAlignment[RIGHT_DOWN] = vector<float>();
	scalesOnAlignment[RIGHT_TOP] = vector<float>();
	scalesOnAlignment[LEFT_TOP] = vector<float>();
	scalesOnAlignment[CENTER] = vector<float>();
}

void UIManager::createInitialUIElements(GameStats stats) {
	setupUIElement("scoreLabel", "SCORE", true, .5f, UIManager::Alignment::LEFT_DOWN);
	setupUIElement("remainingTriesLabel", "FROGS", true, .5f, UIManager::Alignment::LEFT_DOWN);
	setupUIElement("timeLabel", "TIME", true, .5f, UIManager::Alignment::RIGHT_DOWN);
	getFontManager().alignDescriptionLeft("timeLabel", false);

	setupUIElement("remainingTimeLabel", "TIME LEFT", true, .5f, UIManager::Alignment::CENTER);
	getFontManager().hideAfter("remainingTimeLabel", 2.f);
	getFontManager().hideLabel("remainingTimeLabel");

	setupUIElement("currentLevelLabel", "LEVEL", true, .5f, UIManager::Alignment::CENTER);
	getFontManager().hideAfter("currentLevelLabel", 4.f);
	getFontManager().hideLabel("currentLevelLabel");

	setupUIElement("gameOver", "GAME OVER SPACE TO RESTART", false, .5f, UIManager::Alignment::CENTER);
	getFontManager().hideLabel("gameOver");

	setupUIElement("collectedScore", to_string(stats.getCollectedScore()), false, .3f, UIManager::Alignment::CENTER);
	getFontManager().hideAfter("collectedScore", 2.f);
	getFontManager().hideLabel("collectedScore");

	getFontManager().setText("collectedScore", std::to_string(stats.getCollectedScore()));
}

void UIManager::setupUIElement(string identifier, string text, bool withlabel, float scale, Alignment alignment) {
	createUIElement(identifier, text);
	configureUIElement(identifier, withlabel, scale);
	align(identifier, alignment);
}

void UIManager::createUIElement(string identifier, string text) {
	fontManager.createNewLabel(identifier, text);
}

void UIManager::configureUIElement(string identifier, bool withLabel, float fontSize) {
	if (withLabel)
		fontManager.useStaticLabel(identifier);

	fontManager.setScale(identifier, fontSize);
}

void UIManager::align(string identifier, Alignment alignment) {
	float scale = fontManager.getScale(identifier);
	vector<float> lastScales = scalesOnAlignment.at(alignment);

	float offset = 0;
	if (!lastScales.size() == 0) {
		for (int i = 0; i < lastScales.size(); i++) {
			offset += lastScales.at(i) * Y_TILE_SIZE;
		}
	}

	Vec2 position;
	switch (alignment) {
		case LEFT_DOWN:
		{
			position = Vec2(10.f, WINDOW_HEIGHT - 10.f - offset - Y_TILE_SIZE * scale);
		}; break;
		case RIGHT_DOWN:
		{
			int length = fontManager.getLength(identifier);

			position = Vec2(WINDOW_WIDTH - (length * X_TILE_SIZE), WINDOW_HEIGHT - 10.f - offset - Y_TILE_SIZE * scale);
		}; break;
		case CENTER:
		{
			int length = fontManager.getLength(identifier);
			float x = (WINDOW_WIDTH / 2) - ((length * X_TILE_SIZE * scale) / 2);
			float y = ((WINDOW_HEIGHT / 2) - OFFSET_Y) - ((scale * Y_TILE_SIZE) / 2);

			position = Vec2(x, y);
		}; break;
	}

	fontManager.setPosition(identifier, position);
	scalesOnAlignment.at(alignment).push_back(scale);
}

void UIManager::showLabelsForCurrentState(GameStats stats, Vec2 position) {
	if (stats.getCollectedScore() > 0) {
		fontManager.setText("collectedScore", std::to_string(stats.getCollectedScore()));
		fontManager.setPosition("collectedScore", position);
		fontManager.showLabel("collectedScore");
	}

	fontManager.showLabel("remainingTimeLabel");
	fontManager.setText("remainingTimeLabel", std::to_string((int) stats.getTime()));
}