#include "FemaleFrog.h"
#include <iostream>

FemaleFrog::FemaleFrog(Vec2 position) 
	: GameObject(position, Vec2(X_TILE_SIZE, Y_TILE_SIZE), objectTextureRegions.at(Objects::PLAYER), transitionSet) {

	this->setState(State::IDLE);
	this->setSpeed(FROG_SPEED);
	this->movingDuration = 0.0f;
	this->idleTimer = 0;
	this->homePosition = position;
	this->expired = false;
	this->livingTime = 0;
	this->currentDirection = Direction::RIGHT;
	this->setCollisionStruct({ Event::COLLECTING, Vec2(0.0f, 0.0f), Rectangle(), 6 });
}

void FemaleFrog::doLogic(GLfloat dt) {
	doTransition(getCurrentEvent().effect);

	switch (getState()) {
		case State::TRANSPORT: {
			idleTimer += dt;
			livingTime += dt;

			setMovement(getCurrentEvent().movement);

			if (idleTimer > 0.2) {
				doTransition(Event::START_MOVING);
				idleTimer = 0;

				Vec2 movement = directions.at(currentDirection);

				setMovement(movement.add(getCurrentEvent().movement));
				this->targetPosition = getPosition().add((getCurrentMovement().mul(this->getSize().x / getSpeed())));
			}

			move(dt);
		}; break;
		case State::MOVE_TRANSPORT: {
			livingTime += dt;

			GLfloat currentTransportPosition = homePosition.x + (getCurrentEvent().movement.x * livingTime);

			Rectangle targetPositionHitBox = { targetPosition, Vec2(1, 1) };
			Rectangle transporterHitBox = { Vec2(currentTransportPosition, homePosition.y), getCurrentEvent().textureRegion.size.mul(X_TILE_SIZE) };

			if (!(intersects(targetPositionHitBox, transporterHitBox))) {
				if (currentDirection == Direction::RIGHT) {
					currentDirection = Direction::LEFT;
				} else {
					currentDirection = Direction::RIGHT;
				}

				Vec2 movement = directions.at(currentDirection);

				setMovement(movement.add(getCurrentEvent().movement));
				this->targetPosition = getPosition().add((getCurrentMovement().mul(this->getSize().x / getSpeed())));
			}

			move(dt);
		}; break;
		case State::COLLECTED: {
			this->expired = true;
		}; return;
	}

	
	this->expired = isOutsideOfBorders();
}

void FemaleFrog::useAsNewHomePosition(Vec2 position) {
	homePosition = position;
}

bool FemaleFrog::isOutsideOfBorders() {
	if (this->getPosition().x > X_TILE_SIZE * TILES_X && homePosition.x < 0) {
		return true;
	}

	if (this->getPosition().x < 0 && homePosition.x > 0) {
		return true;
	}

	return false;
}

bool FemaleFrog::targetPositionReached(GLfloat dt) {
	if (getState() == State::TRANSPORT) {
		return false;
	}

	this->movingDuration += dt;

	if (movingDuration > this->getSize().x / getSpeed()) {
		this->movingDuration = 0.0f;
		this->setPosition(targetPosition);
		this->resetMovement();
		doTransition(Event::TARGET_POSITION_REACHED);

		return true;
	}

	return false;
}