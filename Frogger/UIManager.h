#ifndef UI_MANAGER
#define UI_MANAGER

#include "FontManager.h"

using namespace std;

class UIManager {

	FontManager fontManager;

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

	map<Alignment, vector<float>> scalesOnAlignment;

	UIManager();
	~UIManager() {};

	
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


	/*
		@return gibt den FontManager zurück.
	*/
	FontManager getFontManager() { return this->fontManager; };
};

#endif UI_MANAGER