#ifndef FROG
#define FROG

#include <map>

#include "GameObject.h"
#include "FrogStateMachine.h"

class Frog : public GameObject {

	GLfloat movingDuration;
	GLfloat decaeseTimer;

	Vec2 targetPosition;
	Vec2 homePosition;

	FrogStateMachine stateMachine;

	void die(GLfloat dt);

	virtual void move(GLfloat dt);

	bool targetPositionReached(GLfloat dt);

	bool validMovement(Vec2 movement);

	bool isOutsideOfBorders();

	Vec2 vectors[2];

public:
	Frog(Vec2 position);

	~Frog();

	void moveTo(Direction direction);
	Rectangle getCriticalHitBox();
	void reset();
	State getState() { return this->stateMachine.getState(); };
	Vec2 getResultingVector() { return vectors[0].add(vectors[1]); };
	void resetMovement();

	void doLogic(GLfloat dt) {};
	
	virtual void doLogic(GLfloat dt, CollisionStruct* currentEvent);
};

#endif FROG