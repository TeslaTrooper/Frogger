#ifndef DRAWABLE
#define DRAWABLE

#include "Texture.h"
#include "Vec2.h"

struct Drawable {
	Vec2 position;
	Vec2 size;
	Texture* texture;
};

enum DrawableType {
	OBJECT,
	FONT
};

#endif DRAWABLE