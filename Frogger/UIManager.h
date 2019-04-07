#ifndef UI_MANAGER
#define UI_MANAGER

#include "FontManager.h"
#include "GameStats.h"

using namespace std;

class UIManager {

public:

	/*
	Stellt die Ausrichtung dar, die ein Label haben kann.
	*/
	enum Alignment {
		LEFT,
		RIGHT,
		TOP,
		DOWN,
		LEFT_DOWN,
		RIGHT_DOWN,
		RIGHT_TOP,
		LEFT_TOP,
		CENTER
	};

private:

	FontManager fontManager;

	/*
	Erzeugt ein neues UIElement.
	@param identifier ist der Name des Elementes.
	@param text ist der Text, der für das Element verwendet werden soll.
	*/
	void createUIElement(string identifier, string text);


	/*
	Bietet konfigurationsmöglichkeiten an.
	@param identifier ist das Label, das konfiguriert werden soll.
	@param withLabel gibt an, ob es einen beschreibenden Text gibt.
	@param gibt die Schriftgröße an.
	*/
	void configureUIElement(string identifier, bool withLabel, float fontSize);


	/*
	Richtet ein Label neu aus.
	@param identifier ist das Label, das ausgerichtet werden soll.
	@param alignment gibt die Ausrichtung an.
	*/
	void align(string identifier, Alignment alignment);

public:

	map<Alignment, vector<float>> scalesOnAlignment;

	UIManager();
	~UIManager() {};

	void createInitialUIElements(GameStats stats);

	void setupUIElement(string identifier, string text, bool withlabel, float scale, Alignment alignment);

	void showLabelsForCurrentState(GameStats stats, Vec2 position);

	/*
		@return gibt den FontManager zurück.
	*/
	FontManager getFontManager() { return this->fontManager; };
};

#endif UI_MANAGER