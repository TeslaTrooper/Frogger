#include "Frog.h"

void Frog::moveTo(Direction direction) {
	vec2 movement;

	switch (direction) {
		case LEFT: movement = vec2(-getSpeed(), 0.0f); break;
		case UP: movement = vec2(0.0f, -getSpeed()); break;
		case RIGHT: movement = vec2(getSpeed(), 0.0f); break;
		case DOWN: movement = vec2(0.0f, getSpeed()); break;
		default: movement = vec2(0.0f, 0.0f);
	}

	if (!validMovement(movement) || !stateMachine->doTransition(Event::ARROW_KEYS)) {
		return;
	}

	this->vectors[0] = movement;

	this->targetPosition = getPosition() + (getResultingVector() * this->getSize().x / getSpeed());
}

void Frog::move(GLfloat dt) {
	if (targetPositionReached(dt)) {
		return;
	}

	setPosition(this->getPosition() + (this->getResultingVector() * dt));
}

void Frog::doLogic(GLfloat dt, CollisionStruct* collisionStruct) {
	this->stateMachine->doTransition(collisionStruct->effect);
	
	switch (this->stateMachine->getState()) {
		case State::DIEING: {
			die(dt);
		}; break;
		case State::KILLED: {
			reset();
		}; break;
		case State::MOVING: {
			//if (!targetPositionReached(dt)) {
				move(dt);
			//}
		}; break;
		case State::MOVE_TRANSPORT: {
			//if (!targetPositionReached(dt)) {
				move(dt);
			//}
		}; break;
		case State::TRANSPORT: {
			vectors[1] = collisionStruct->movement;
			move(dt);
		}; break;
		case State::NAVIGATING: {
			float length = sqrt(pow(getResultingVector().x, 2) + pow(getResultingVector().y, 2));
			vec2 r = collisionStruct->movement - this->getPosition();
			r *= 1.0f / (sqrt(pow(r.x, 2) + pow(r.y, 2)));
			r *= length;
			this->resetMovement();
			vectors[0] = r;
			targetPosition = collisionStruct->movement;
		}; break;
	}
}

Rectangle Frog::getCriticalHitBox() {
	return { this->getPosition(), this->getSize() };
}

void Frog::resetMovement() {
	vectors[0] = vec2(0.0f, 0.0f);
	vectors[1] = vec2(0.0f, 0.0f);
}

void Frog::reset() {
	this->setPosition(homePosition);
	this->stateMachine->doTransition(Event::DIE_SEQUENCE_EXPIRED);
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
	if (stateMachine->getState() == State::TRANSPORT) {
		return false;
	}

	this->movingDuration += dt;

	if (movingDuration > this->getSize().x / getSpeed()) {
		this->movingDuration = 0.0f;
		this->setPosition(targetPosition);
		this->resetMovement();
		this->stateMachine->doTransition(Event::TARGET_POSITION_REACHED);

		return true;
	}

	return false;
}

bool Frog::validMovement(vec2 movement) {
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

Frog::~Frog() {}