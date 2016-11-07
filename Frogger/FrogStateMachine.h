#ifndef FROG_STATE_MACHINE
#define FROG_STATE_MACHINE

#include "State.h"
#include "Event.h"
#include <vector>

/*
	Die Klasse FrogStateMachine hat einen aktuellen Zustand, eine Definition eines Zustandswechels 
	und eine Menge gültiger Zustände, die dieser Zustandautomat beschreibt.
*/
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

	/*
		Diese Methode führt einen Zustandsübergang mit dem gegebenen Transitionselement durch.
		@param transitionUnit repräsentiert den Übergang zwischen 2 Zuständen.
		@return Gibt true zurück, wenn der Automat in einen neuen Zustand gewechselt hat. Wenn
				kein neuer Zustand eingenommen wurde, also die Kombination aus aktuellem Zustand
				und Übergangselement nicht in der Zustansmenge enthalten ist, wird false
				zurückgegeben.
	*/
	bool doTransition(Event transitionUnit);

	/*
		Gibt den aktuellen Zustand, in dem sich der Automat befindet, zurück.
		@return aktueller Zustand.
	*/
	State getState();
};

#endif FROG_STATE_MACHINE