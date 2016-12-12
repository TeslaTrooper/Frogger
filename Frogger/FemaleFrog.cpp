#include "FemaleFrog.h"
#include <iostream>

const map<Direction, Rectangle> FemaleFrog::textureSet = {
	{ Direction::UP,{ Vec2(1, 6), Vec2(1, 1) } },
	{ Direction::RIGHT,{ Vec2(5, 6), Vec2(1, 1) } },
	{ Direction::LEFT,{ Vec2(6, 6), Vec2(1, 1) } }
};

FemaleFrog::FemaleFrog(Vec2 position) : Opponent(position, textureSet.at(Direction::UP), textureSet, transitionSet) {
	this->movingDuration = 0.0f;
	this->idleTimer = 0;
	this->setSpeed(FROG_SPEED);
	this->setCollisionInfo({ Event::COLLECTING, 6 });
}

void FemaleFrog::doLogic(GLfloat dt) {
	doTransition(getCurrentInteraction().collisionInfo.effect);

	switch (getState()) {
		case State::TRANSPORT: {
			idle(dt);
		}; break;
		case State::MOVE_TRANSPORT: {
			move(dt);
		}; break;
		case State::COLLECTED: {
			setExpired(true);
		}; return;
	}

	increaseLivingTime(dt);
	setExpired(Opponent::isOutsideOfBorders());
}

void FemaleFrog::idle(GLfloat dt) {
	idleTimer += dt;

	setTextureRegion(getTextureRegionFor(Direction::UP));
	setMovement(getCurrentInteraction().movement);

	if (idleTimer > 0.5f) {
		doTransition(Event::START_MOVING);
		idleTimer = 0;

		setValidMovement(dt);

		Vec2 movement = directions.at(getDirection());
		movement = movement.mul(getSpeed());

		setTextureRegion(getTextureRegionFor(getDirection()));
		setMovement(movement.add(getCurrentInteraction().movement));
		this->targetPosition = getPosition().add((getCurrentMovement().mul(this->getSize().x / getSpeed())));

		return;
	}

	move(dt);
}

void FemaleFrog::setValidMovement(GLfloat dt) {
	Vec2 movement = directions.at(getDirection());

	Vec2 tmpTargetPosition = getPosition().add(movement.mul(getSize().x));
	tmpTargetPosition = tmpTargetPosition.add({ getSize().x / 2, 0.0f });

	GLfloat currentTransportPosition = getHomePosition().x + (getCurrentInteraction().movement.x * getLivingTime());
	Rectangle transporterHitBox = { Vec2(currentTransportPosition, getHomePosition().y), getCurrentInteraction().textureRegion.size.mul(X_TILE_SIZE) };

	if (getDirection() == Direction::RIGHT) {
		if (tmpTargetPosition.x > currentTransportPosition + transporterHitBox.size.x) {
			setDirection(Direction::LEFT);
		}
	}

	if (getDirection() == Direction::LEFT) {
		if (tmpTargetPosition.x < currentTransportPosition) {
			setDirection(Direction::RIGHT);
		}
	}
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