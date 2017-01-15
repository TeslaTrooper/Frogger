#ifndef OPPONENT
#define OPPONENT

#include <vector>

#include "GameObject.h"
#include "Util.h"

class Opponent : public GameObject {
	float livingTime;
	Vec2 homePosition;
	Direction currentDirection;

	bool expired;

protected:
	bool isOutsideOfBorders();
	void setValidMovement(float leftThreshold, float rightThreshold);

public:
	Opponent(Vec2 position, const Rectangle& textureRegion, map<Direction, Rectangle> textureSet, const vector<TransitionElement>& transitionSet);
	~Opponent() {};

	void setExpired(bool value) { this->expired = value; };
	bool isExpired() { return expired; };
	
	void increaseLivingTime(float dt) { this->livingTime += dt; };
	float getLivingTime() { return livingTime; };

	void setDirection(Direction direction) { this->currentDirection = direction; };
	Direction getDirection() { return currentDirection; };

	void useAsNewHomePosition(Vec2 pos) { this->homePosition = pos; };
	Vec2 getHomePosition() { return homePosition; };

	// @Override
	virtual void doLogic(float dt);

	// @Override
	virtual Rectangle getCriticalHitBox();
};

#endif OPPONENT