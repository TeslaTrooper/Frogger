#ifndef FONT_MANAGER
#define FONT_MANAGER

#include <map>
#include <vector>
#include <string>

#include "Texture.h"
#include "Label.h"

using namespace std;

class FontManager {
	map<string, Label*>* labels;

	typedef map<string, Label*>::iterator it_type;

	void setPosition(string identifier, Vec2 position);
	void setScale(string identifier, float scale);
public:
	FontManager();
	~FontManager();

	void createNewLabel(string identifier, string text, Vec2 position, float scale);
	void setText(string identifier, string text);

	vector<Drawable> getDrawables();
};

#endif FONT_MANAGER