#ifndef UI_MANAGER
#define UI_MANAGER

#include "FontManager.h"

using namespace std;

class UIManager {

	FontManager fontManager;

public:
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

	void createUIElement(string identifier, string text);
	void configureUIElement(string identifier, bool withLabel, float fontSize);
	void align(string identifier, Alignment alignment);
	FontManager getFontManager() { return this->fontManager; };
};

#endif UI_MANAGER