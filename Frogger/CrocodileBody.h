#ifndef _CROCODILE_BODY
#define _CROCODILE_BODY

#include "Opponent.h"

class CrocodileBody : public Opponent {
	static const map<Direction, util::Rectangle> textureSet;

public:
	CrocodileBody(Vec2 position);
	~CrocodileBody() {}

	// @Override
	virtual void doLogic(float dt);
};

#endif _CROCODILE_BODY