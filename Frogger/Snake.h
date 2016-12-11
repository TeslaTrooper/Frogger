#ifndef _SNAKE
#define _SNAKE

#include "Opponent.h"
#include "Util.h"

class Snake : public Opponent {
	vector<TransitionElement> transitionSet = {
		{ State::IDLE, Event::COLL_TREE_TURTLE, State::MOVE_TRANSPORT }
	};

public:
	Snake(Vec2 position);
	~Snake() {};

	// @Override
	virtual void doLogic(GLfloat dt);

};

#endif _SNAKE