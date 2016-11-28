#include "StateMachine.h"

StateMachine::StateMachine() : transitionSet(vector<TransitionElement>()) {}

StateMachine::StateMachine(const vector<TransitionElement>& transitionSet) : transitionSet(transitionSet) {
	this->currentState = State::IDLE;
}

StateMachine::~StateMachine() {}

bool StateMachine::doTransition(Event transitionUnit) {
	for (int i = 0; i < transitionSet.size(); i++) {
		TransitionElement transition = transitionSet.at(i);

		if (transition.currentState == this->currentState && transition.transitionUnit == transitionUnit) {
			this->currentState = transition.newState;

			return true;
		}
	}

	return false;
}

State StateMachine::getState() {
	return this->currentState;
}

void StateMachine::setInitialState(State state) {
	this->currentState = state;
}