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

	if (!validMovement(movement)) {
		return;
	}

	if(!stateMachine->doTransition(Event::ARROW_KEYS)) {
		return;
	}

	this->targetPosition = getPosition() + (movement * this->getSize().x / getSpeed());
	this->setMovement(movement);
}

void Frog::move(GLfloat dt) {
	vec2 pos = getPosition();
	vec2 newPos = vec2(pos.x + getCurrentMovement().x * dt, pos.y + getCurrentMovement().y * dt);
	setPosition(newPos);
}

void Frog::doLogic(GLfloat dt, CollisionStruct collisionStruct) {
	stateMachine->doTransition(collisionStruct.effect);

	switch (this->stateMachine->getState()) {
		case State::DIEING: {
			die(dt);
		}; break;
		case State::KILLED: {
			reset();
		}; break;
		case State::MOVING: {
			if (!targetPositionReached(dt)) {
				move(dt);
			}
		}; break;
		case State::MOVE_TRANSPORT: {
			if (!targetPositionReached(dt)) {
				move(dt);
			}
		}; break;
		case State::TRANSPORT: {
			this->setMovement(collisionStruct.movement);
			move(dt);
		}; break;
	}
}

GameObject::Rectangle Frog::getCriticalHitBox() {
	return { this->getPosition(), this->getSize() };
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


	if (this->getPosition().x + this->getSize().x + dX > 560) {
		return false;
	}
	if (this->getPosition().x + dX < 0) {
		return false;
	}
	if (this->getPosition().y + this->getSize().y + dY > 14 * Y_TILE_SIZE) {
		return false;
	}
	if (this->getPosition().y + dY < 20) {
		return false;
	}

	return true;
}

Frog::~Frog() {}