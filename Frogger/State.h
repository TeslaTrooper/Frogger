#ifndef STATE
#define STATE

enum State {
	IDLE,
	MOVING,
	TRANSPORTING_RIGHT,
	TRANSPORTING_LEFT,
	TRANSPORT,
	MOVE_TRANSPORT,
	CARRYING,
	DIEING,
	KILLED
};

#endif STATE