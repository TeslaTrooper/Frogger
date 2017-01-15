#ifndef STATE_MACHINE
#define STATE_MACHINE

#include <vector>
#include "Util.h"

using namespace std;
using namespace util;

/*
	Die Klasse StateMachine hat einen aktuellen Zustand, eine Definition eines Zustandswechels 
	und eine Menge gültiger Zustände, die dieser Zustandautomat beschreibt.
*/
class StateMachine {
	State currentState;
	State prevState;

	const vector<TransitionElement>& transitionSet;

public:
	StateMachine();

	StateMachine(const vector<TransitionElement>& transitionSet);

	~StateMachine();

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

	void gotoPreviousState();

	void setInitialState(State state);

};

#endif STATE_MACHINE