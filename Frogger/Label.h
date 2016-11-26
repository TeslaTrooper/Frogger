#ifndef LABEL
#define LABEL

#include <vector>
#include <string>
#include <map>
#include <string>

#include "Vec2.h"
#include "Util.h"

class Label {
	static std::map<char, Rectangle>* charCollection;

	std::vector<Rectangle>* chars;
	std::vector<Vec2>* charPositions;

	float scale = 1.0f;
	Vec2 position;

	void alignPosition();
	Vec2 getSize(int index);

public:
	Label(std::string text);
	~Label();

	void setPosition(Vec2 position);
	Vec2 getPosition();
	std::vector<Drawable> getDrawables();
	int getLength();
	
	void setScale(float scale);
	void setText(std::string text);

	static std::map<char, Rectangle>* initTextures();
};

#endif LABEL