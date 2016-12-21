#ifndef FONT_MANAGER
#define FONT_MANAGER

#include "Label.h"

using namespace std;

class FontManager {
	map<string, Label*> labels;

	typedef map<string, Label*>::iterator it_type;
public:
	FontManager();
	~FontManager();

	void createNewLabel(string identifier, string text);
	void createNewLabel(string identifier, string text, Vec2 position, bool useAsDescription, float scale);

	void setText(string identifier, string text);
	void hideLabel(string identifier);
	void showLabel(string identifier);
	bool isVisible(string identifier);
	void setPosition(string identifier, Vec2 position);
	void hideAfter(string identifier, float duration);
	void alignDescriptionLeft(string identifier, bool value);
	void useStaticLabel(string identifier);
	void setScale(string identifier, float scale);
	float getScale(string identifier);
	int getLength(string identifier);
	void update(float dt);

	vector<Drawable> getDrawables();
};

#endif FONT_MANAGER