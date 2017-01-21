#ifndef _CROCODILE_HEAD
#define _CROCODILE_HEAD

#include "Opponent.h"

class CrocodileHead : public Opponent {
	static const map<Direction, util::Rectangle> textureSet;

public:
	CrocodileHead(Vec2 position);
	~CrocodileHead() {}

	// @Override
	virtual void doLogic(float dt);
};

#endif _CROCODILE_HEAD