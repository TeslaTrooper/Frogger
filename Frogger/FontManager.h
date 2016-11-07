#ifndef FONT_MANAGER
#define FONT_MANAGER

#include <map>
#include <vector>
#include <string>
#include "Texture.h"
#include "Label.h"
#include <glm\glm.hpp>

using namespace std;

class FontManager {
	map<string, Label*>* labels;

	typedef std::map<string, Label*>::iterator it_type;

	void setPosition(string identifier, glm::vec2 position);
	void setScale(string identifier, float scale);
public:
	FontManager();
	~FontManager();

	void createNewLabel(string identifier, string text, glm::vec2 position, float scale);
	void setText(string identifier, string text);

	void drawLabels(Renderer* renderer);
};

#endif FONT_MANAGER