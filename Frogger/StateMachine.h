#ifndef STATE_MACHINE
#define STATE_MACHINE

#include <vector>
#include "Util.h"

using namespace std;
using namespace util;

/*
	Die Klasse StateMachine hat einen aktuellen Zustand, eine Definition eines Zustandswechels 
	und eine Menge g�ltiger Zust�nde, die dieser Zustandautomat beschreibt.
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
		Diese Methode f�hrt einen Zustands�bergang mit dem gegebenen Transitionselement durch.
		@param transitionUnit repr�sentiert den �bergang zwischen 2 Zust�nden.
		@return Gibt true zur�ck, wenn der Automat in einen neuen Zustand gewechselt hat. Wenn
				kein neuer Zustand eingenommen wurde, also die Kombination aus aktuellem Zustand
				und �bergangselement nicht in der Zustansmenge enthalten ist, wird false
				zur�ckgegeben.
	*/
	bool doTransition(Event transitionUnit);

	/*
		Gibt den aktuellen Zustand, in dem sich der Automat befindet, zur�ck.
		@return aktueller Zustand.
	*/
	State getState();

	void gotoPreviousState();

	void setInitialState(State state);

};

#endif STATE_MACHINE