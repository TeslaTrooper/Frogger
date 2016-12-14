#ifndef _CROCODILE
#define _CROCODILE

#include "Opponent.h"

class Crocodile : public Opponent {
	static const map<Direction, Rectangle> textureSet;

public:
	Crocodile(Vec2 position);
	~Crocodile() {}

	// @Override
	virtual void doLogic(GLfloat dt);

	// @Override
	virtual Rectangle getCriticalHitBox();
};

#endif _CROCODILE