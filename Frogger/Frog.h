#ifndef FROG
#define FROG

#include <map>

#include "GameObject.h"
#include "StateMachine.h"

class Frog : public GameObject {

	GLfloat movingDuration;
	GLfloat decaeseTimer;

	Vec2 targetPosition;
	Vec2 homePosition;

	void die(GLfloat dt);

	bool validMovement(Vec2 movement);

	bool isOutsideOfBorders();

	const vector<TransitionElement> transitionSet = {
		{ State::IDLE, Event::ARROW_KEYS, State::MOVING },
		{ State::MOVING, Event::TARGET_POSITION_REACHED, State::IDLE },
		{ State::IDLE, Event::COLL_TREE_TURTLE, State::TRANSPORT },
		{ State::MOVING, Event::COLL_LETHAL_OBJECTS, State::DIEING },
		{ State::TRANSPORT, Event::COLL_NONE, State::IDLE },
		{ State::TRANSPORT, Event::ARROW_KEYS, State::MOVE_TRANSPORT },
		{ State::MOVE_TRANSPORT, Event::TARGET_POSITION_REACHED, State::TRANSPORT },
		{ State::TRANSPORT, Event::COLL_LETHAL_OBJECTS, State::DIEING },
		{ State::MOVE_TRANSPORT, Event::COLL_LETHAL_OBJECTS, State::DIEING },
		{ State::IDLE, Event::COLL_LETHAL_OBJECTS, State::DIEING },
		{ State::DIEING, Event::DIE_SEQUENCE_EXPIRED, State::KILLED },
		{ State::KILLED, Event::RESET, State::IDLE },
		{ State::MOVE_TRANSPORT, Event::COLL_POOL, State::ALIGNING },
		{ State::ALIGNING, Event::COLL_POOL, State::NAVIGATING },
		{ State::NAVIGATING, Event::TARGET_POSITION_REACHED, State::INACTIVE },
		{ State::TRANSPORT, Event::COLLECTING, State::COLLECTED },
		{ State::MOVE_TRANSPORT, Event::COLLECTING, State::COLLECTED }
	};

	static const map<Direction, Rectangle> textureSet;

protected:
	// @Override
	bool targetPositionReached(GLfloat dt);

public:
	Frog(Vec2 position);
	Frog(Vec2 position, State initialState);

	~Frog();

	void moveTo(Direction direction);
	void reset();

	// @Override
	void doLogic(GLfloat dt);
};

#endif FROG