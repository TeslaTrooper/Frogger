#ifndef OPPONENT
#define OPPONENT

#include <vector>

#include "GameObject.h"
#include "Util.h"

class Opponent : public GameObject {
	GLfloat livingTime;
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
	
	void increaseLivingTime(GLfloat dt) { this->livingTime += dt; };
	GLfloat getLivingTime() { return livingTime; };

	void setDirection(Direction direction) { this->currentDirection = direction; };
	Direction getDirection() { return currentDirection; };

	void useAsNewHomePosition(Vec2 pos) { this->homePosition = pos; };
	Vec2 getHomePosition() { return homePosition; };

	// @Override
	virtual void doLogic(GLfloat dt);
};

#endif OPPONENT