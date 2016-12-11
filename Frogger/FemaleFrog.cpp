#include "FemaleFrog.h"
#include <iostream>

FemaleFrog::FemaleFrog(Vec2 position) : Opponent(position, transitionSet, objectTextureRegions.at(Objects::FEMALE_FROG)) {
	this->movingDuration = 0.0f;
	this->idleTimer = 0;
	this->setSpeed(FROG_SPEED);
	this->setCollisionInfo({ Event::COLLECTING, 6 });
}

void FemaleFrog::doLogic(GLfloat dt) {
	doTransition(getCurrentInteraction().collisionInfo.effect);

	switch (getState()) {
		case State::TRANSPORT: {
			idleTimer += dt;

			setMovement(getCurrentInteraction().movement);

			if (idleTimer > 1.0) {
				doTransition(Event::START_MOVING);
				idleTimer = 0;

				Vec2 movement = directions.at(getDirection());
				movement = movement.mul(getSpeed());

				setMovement(movement.add(getCurrentInteraction().movement));
				this->targetPosition = getPosition().add((getCurrentMovement().mul(this->getSize().x / getSpeed())));
			}

			move(dt);
		}; break;
		case State::MOVE_TRANSPORT: {
			GLfloat currentTransportPosition = getHomePosition().x + (getCurrentInteraction().movement.x * getLivingTime());

			Rectangle targetPositionHitBox = { targetPosition, Vec2(1, 1) };
			Rectangle transporterHitBox = { Vec2(currentTransportPosition, getHomePosition().y), getCurrentInteraction().textureRegion.size.mul(X_TILE_SIZE) };

			if (!(intersects(targetPositionHitBox, transporterHitBox))) {
				if (getDirection() == Direction::RIGHT) {
					setDirection(Direction::LEFT);
				} else {
					setDirection(Direction::RIGHT);
				}

				Vec2 movement = directions.at(getDirection());
				movement = movement.mul(getSpeed());

				setMovement(movement.add(getCurrentInteraction().movement));
				this->targetPosition = getPosition().add((getCurrentMovement().mul(this->getSize().x / getSpeed())));
			}

			move(dt);
		}; break;
		case State::COLLECTED: {
			setExpired(true);
		}; return;
	}

	increaseLivingTime(dt);
	setExpired(Opponent::isOutsideOfBorders());
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