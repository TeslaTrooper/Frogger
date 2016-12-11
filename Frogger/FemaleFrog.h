#ifndef _FEMALE_FROG
#define _FEMALE_FROG

#include <vector>

#include "Opponent.h"
#include "Util.h"

using namespace std;

class FemaleFrog : public Opponent {
	GLfloat movingDuration;
	GLfloat idleTimer;
	Vec2 targetPosition;

	const vector<TransitionElement> transitionSet = {
		{ State::IDLE, Event::COLL_TREE_TURTLE, State::TRANSPORT },
		{ State::TRANSPORT, Event::START_MOVING, State::MOVE_TRANSPORT },
		{ State::MOVE_TRANSPORT, Event::TARGET_POSITION_REACHED, State::TRANSPORT },
		{ State::TRANSPORT, Event::COLLECTING, State::COLLECTED },
		{ State::MOVE_TRANSPORT, Event::COLLECTING, State::COLLECTED }
	};

protected:
	// @Override
	bool targetPositionReached(GLfloat dt);

public:
	FemaleFrog(Vec2 position);

	// @Override
	virtual void doLogic(GLfloat dt);
};

#endif _FEMALE_FROG