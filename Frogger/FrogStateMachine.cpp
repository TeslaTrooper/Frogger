#include "FrogStateMachine.h"

FrogStateMachine::FrogStateMachine() {
	this->currentState = State::IDLE;
}

FrogStateMachine::~FrogStateMachine() {}

bool FrogStateMachine::doTransition(Event transitionUnit) {
	for (int i = 0; i < transitions.size(); i++) {
		TransitionElement transition = transitions.at(i);

		if (transition.currentState == this->currentState && transition.transitionUnit == transitionUnit) {
			this->currentState = transition.newState;

			return true;
		}
	}

	return false;
}

State FrogStateMachine::getState() {
	return this->currentState;
}