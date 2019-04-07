#ifndef _CROCODILE_HEAD
#define _CROCODILE_HEAD

#include "Opponent.h"

class CrocodileHead : public Opponent {
	static const map<Direction, util::Rectangle> textureSet;

public:
	CrocodileHead(Vec2 position);
	~CrocodileHead() {}

	virtual void doLogic(float dt) override;
};

#endif _CROCODILE_HEAD