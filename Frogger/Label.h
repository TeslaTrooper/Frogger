#ifndef LABEL
#define LABEL

#include "Util.h"

using namespace std;

class Label {
	static map<char, Rectangle>* charCollection;

	vector<Rectangle>* chars;
	vector<Vec2>* charPositions;

	string descriptionText;

	float scale = 1.0f;
	float duration, durationValue;

	Vec2 position;

	void alignPosition();
	Vec2 getSize(int index);

	bool visible, descriptionLeftAligned, isStaticLabel;

public:
	Label(string text, bool useAsDescription);

	~Label();

	void setPosition(Vec2 position);
	Vec2 getPosition();
	vector<Drawable> getDrawables();
	int getLength();
	
	void setScale(float scale);
	void setText(string text);
	void hide() {this->visible = false;};
	void show() { this->visible = true; };
	bool isVisible() { return this->visible; };
	void hideAfter(float duration);
	bool isAutoHiding() { return durationValue > 0; };
	void alignDescriptionLeft(bool value) { this->descriptionLeftAligned = value; };
	float getScale() { return this->scale; };
	void useStaticLabel();

	void update(float dt);

	static map<char, Rectangle>* initTextures();
};

#endif LABEL