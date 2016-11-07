#ifndef FROG_STATE_MACHINE
#define FROG_STATE_MACHINE

#include "State.h"
#include "Event.h"
#include <vector>

class FrogStateMachine {
	State currentState;

	struct TransitionElement {
		State currentState;
		Event transitionUnit;
		State newState;
	};

	std::vector<TransitionElement> transitions = {
		{State::IDLE, Event::ARROW_KEYS, State::MOVING},
		{State::MOVING, Event::TARGET_POSITION_REACHED, State::IDLE},
		{State::IDLE, Event::COLL_TREE_TURTLE, State::TRANSPORT},
		{State::MOVING, Event::COLL_LETHAL_OBJECTS, State::DIEING},
		{State::TRANSPORT, Event::COLL_NONE, State::IDLE},
		{State::TRANSPORT, Event::ARROW_KEYS, State::MOVE_TRANSPORT},
		{State::MOVE_TRANSPORT, Event::TARGET_POSITION_REACHED, State::TRANSPORT},
		{State::TRANSPORT, Event::COLL_LETHAL_OBJECTS, State::DIEING},
		{State::MOVE_TRANSPORT, Event::COLL_LETHAL_OBJECTS, State::DIEING},
		{State::IDLE, Event::COLL_LETHAL_OBJECTS, State::DIEING},
		{State::DIEING, Event::DIE_SEQUENCE_EXPIRED, State::IDLE}
	};

public:
	FrogStateMachine();
	~FrogStateMachine();

	bool doTransition(Event transitionUnit);
	State getState();
};

#endif FROG_STATE_MACHINE