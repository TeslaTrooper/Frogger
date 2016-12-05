#ifndef FEMALE_FROG
#define FEMALE_FROG

#include <vector>

#include "GameObject.h"
#include "Util.h"

using namespace std;

class FemaleFrog : public GameObject {
	GLfloat movingDuration;
	GLfloat idleTimer;
	GLfloat livingTime;

	Vec2 targetPosition;
	Vec2 homePosition;

	Direction currentDirection;

	bool expired;

	bool isOutsideOfBorders();

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

	bool isExpired() { return expired; };

	void useAsNewHomePosition(Vec2 pos);

	// @Override
	void doLogic(GLfloat dt);
};

#endif FEMALE_FROG