#ifndef FROG
#define FROG

#include "GameObject.h"
#include "FrogStateMachine.h"

class Frog : public GameObject {

	GLfloat movingDuration;
	GLfloat decaeseTimer;

	Vec2 targetPosition;

	Vec2 homePosition;

	void die(GLfloat dt);

	FrogStateMachine* stateMachine;

	virtual void move(GLfloat dt);

	bool targetPositionReached(GLfloat dt);

	bool validMovement(Vec2 movement);

	bool isOutsideOfBorders();

	Vec2 vectors[2];

public:
	Frog(Vec2 position) : GameObject(position, Vec2(X_TILE_SIZE, Y_TILE_SIZE), new Texture("../textures/frog.png")) {
		this->homePosition = position;
		this->setState(State::IDLE);
		this->setSpeed(180.0f);
		this->stateMachine = new FrogStateMachine();
		vectors[0] = Vec2(0.0f, 0.0f);
		vectors[1] = Vec2(0.0f, 0.0f);
	};

	~Frog();

	void moveTo(Direction direction);
	Rectangle getCriticalHitBox();
	void reset();
	State getState() { return this->stateMachine->getState(); };
	Vec2 getResultingVector() { return vectors[0].add(vectors[1]); };
	void resetMovement();

	void doLogic(GLfloat dt) {};
	
	virtual void doLogic(GLfloat dt, CollisionStruct* currentEvent);
};

#endif FROG