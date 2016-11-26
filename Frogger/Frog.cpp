#include "Frog.h"

Frog::Frog(Vec2 position) : GameObject(position, Vec2(X_TILE_SIZE, Y_TILE_SIZE), objetcs.at(Objects::PLAYER)) {
	this->setState(State::IDLE);
	this->setSpeed(FROG_SPEED);
	this->homePosition = position;
	this->movingDuration = 0.0f;
	this->decaeseTimer = 0;
};

void Frog::moveTo(Direction direction) {
	Vec2 movement = directions.at(direction);

	if (!validMovement(movement) || !stateMachine.doTransition(Event::ARROW_KEYS)) {
		return;
	}

	this->vectors[0] = movement;

	this->targetPosition = getPosition().add((getResultingVector().mul(this->getSize().x / getSpeed())));
}

void Frog::move(GLfloat dt) {
	if (targetPositionReached(dt)) {
		return;
	}

	setPosition(this->getPosition().add((this->getResultingVector().mul(dt))));
}

void Frog::doLogic(GLfloat dt, CollisionStruct* collisionStruct) {
	this->stateMachine.doTransition(collisionStruct->effect);
	
	switch (this->stateMachine.getState()) {
		case State::DIEING: {
			die(dt);
		}; break;
		case State::KILLED: {
			reset();
		}; break;
		case State::MOVING: {
			move(dt);
		}; break;
		case State::MOVE_TRANSPORT: {
			move(dt);

			if (isOutsideOfBorders()) {
				die(dt);
			}
		}; break;
		case State::TRANSPORT: {
			vectors[1] = collisionStruct->movement;
			move(dt);

			if (isOutsideOfBorders()) {
				die(dt);
			}
		}; break;
		case State::ALIGNING: {
			float length = getResultingVector().length();
			this->resetMovement();
			vectors[0] = this->getPosition().rotateTo(collisionStruct->movement, length);
			targetPosition = collisionStruct->movement;
		}; break;
		case State::NAVIGATING: {
			move(dt);
		}; break;
	}
}

Rectangle Frog::getCriticalHitBox() {
	return { this->getPosition(), this->getSize() };
}

void Frog::resetMovement() {
	vectors[0].clear();
	vectors[1].clear();
}

void Frog::reset() {
	this->setPosition(homePosition);
	this->stateMachine.doTransition(Event::DIE_SEQUENCE_EXPIRED);
	this->resetMovement();
	this->decaeseTimer = 0;
	this->movingDuration = 0;
}

void Frog::die(GLfloat dt) {
	decaeseTimer += dt;
	if (decaeseTimer > 1) {
		reset();
	}
}

bool Frog::targetPositionReached(GLfloat dt) {
	if (stateMachine.getState() == State::TRANSPORT) {
		return false;
	}

	this->movingDuration += dt;

	if (movingDuration > this->getSize().x / getSpeed()) {
		this->movingDuration = 0.0f;
		this->setPosition(targetPosition);
		this->resetMovement();
		this->stateMachine.doTransition(Event::TARGET_POSITION_REACHED);

		return true;
	}

	return false;
}

bool Frog::validMovement(Vec2 movement) {
	float dX = movement.x * (this->getSize().x / getSpeed());
	float dY = movement.y * (this->getSize().y / getSpeed());


	if (this->getPosition().x + this->getSize().x + dX > X_TILE_SIZE * TILES_X) {
		return false;
	}
	if (this->getPosition().x + dX < 0) {
		return false;
	}
	if (this->getPosition().y + this->getSize().y + dY > 14 * Y_TILE_SIZE) {
		return false;
	}
	if (this->getPosition().y + dY < OFFSET_Y) {
		return false;
	}

	return true;
}

bool Frog::isOutsideOfBorders() {
	if (this->getPosition().x + this->getSize().x > X_TILE_SIZE * TILES_X) {
		return true;
	}

	if (this->getPosition().x < 0) {
		return true;
	}

	return false;
}

Frog::~Frog() {}