#ifndef FROG
#define FROG

#include "GameObject.h"
#include "FrogStateMachine.h"

class Frog : public GameObject {

	GLfloat movingDuration;
	GLfloat decaeseTimer;

	bool validMovement(vec2 movement);

	vec2 targetPosition;

	glm::vec2 homePosition;

	void die(GLfloat dt);

	FrogStateMachine* stateMachine;

	virtual void move(GLfloat dt);

	bool targetPositionReached(GLfloat dt);

	vec2 vectors[2];

public:
	Frog(vec2 position, vec3 color) : GameObject(position, vec2(X_TILE_SIZE, Y_TILE_SIZE), color, new Texture("../textures/frog.png")) {
		this->homePosition = position;
		this->setState(State::IDLE);
		this->setSpeed(180.0f);
		this->stateMachine = new FrogStateMachine();
		vectors[0] = vec2(0.0f, 0.0f);
		vectors[1] = vec2(0.0f, 0.0f);
	};

	~Frog();

	void moveTo(Direction direction);
	Rectangle getCriticalHitBox();
	void reset();
	State getState() { return this->stateMachine->getState(); };
	vec2 getResultingVector() { return vectors[0] + vectors[1]; };
	void resetMovement();

	void doLogic(GLfloat dt) {};
	
	virtual void doLogic(GLfloat dt, CollisionStruct* currentEvent);
};

#endif FROG