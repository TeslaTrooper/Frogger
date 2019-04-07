#ifndef TURTLE
#define TURTLE

#include "Opponent.h"

class Turtle : public Opponent {
	map<Direction, util::Rectangle> textureSet;

	const vector<TransitionElement> transitionSet = {
		{ State::MOVING, Event::START_DIVING, State::DESCENDING },
		{ State::DESCENDING, Event::DESCENDING_FINISHED, State::DIVING },
		{ State::DIVING, Event::START_MOVING, State::TURNING_UP },
		{ State::TURNING_UP, Event::TURNING_UP_FINISHED, State::MOVING }
	};

	float movingTimer, divingTimer, animationTimer;
	int textureRegionOffset;
	Objects type;
	bool animating;
public:
	Turtle(Objects type, Vec2 position, util::Rectangle textureRegion, bool animating);
	~Turtle() {}

	bool isAnimating() { return this->animating; };

	virtual void doLogic(float dt) override;
};

#endif TURTLE
