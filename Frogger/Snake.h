#ifndef _SNAKE
#define _SNAKE

#include "Opponent.h"
#include "Util.h"

class Snake : public Opponent {
	vector<TransitionElement> transitionSet = {
		{ State::IDLE, Event::COLL_TREE_TURTLE, State::MOVE_TRANSPORT }
	};

	static const map<Direction, util::Rectangle> textureSet;

public:
	Snake(Vec2 position);
	~Snake() {};

	virtual void doLogic(float dt) override;

};

#endif _SNAKE