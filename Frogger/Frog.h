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

public:
	Frog(vec2 position, vec3 color) : GameObject(position, vec2(X_TILE_SIZE, Y_TILE_SIZE), color, new Texture("../textures/wall.jpg")) {
		this->homePosition = position;
		this->setState(State::IDLE);
		this->setSpeed(180.0f);
		this->stateMachine = new FrogStateMachine();
	};

	~Frog();

	/// <summary>hhh</summary>
	void moveTo(Direction direction);
	Rectangle getCriticalHitBox();
	void reset();
	State getState() { return this->stateMachine->getState(); };

	void doLogic(GLfloat dt) {};
	
	virtual void doLogic(GLfloat dt, CollisionStruct currentEvent);
};

#endif FROG