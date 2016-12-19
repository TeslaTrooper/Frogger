#include "FemaleFrog.h"
#include <iostream>

const map<Direction, Rectangle> FemaleFrog::textureSet = {
	{ Direction::UP,{ Vec2(1, 6), Vec2(1, 1) } },
	{ Direction::RIGHT,{ Vec2(2, 6), Vec2(1, 1) } },
	{ Direction::LEFT,{ Vec2(3, 6), Vec2(1, 1) } }
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

		Vec2 currentMovement = directions.at(getDirection());

		Vec2 tmpTargetPosition = getPosition().add(currentMovement.mul(getSize().x));
		tmpTargetPosition = tmpTargetPosition.add({ getSize().x / 2, 0.0f });

		setValidMovement(tmpTargetPosition.x, tmpTargetPosition.x);

		Vec2 movement = directions.at(getDirection());
		movement = movement.mul(getSpeed());

		setTextureRegion(getTextureRegionFor(getDirection()));
		setMovement(movement.add(getCurrentInteraction().movement));
		this->targetPosition = getPosition().add((getCurrentMovement().mul(this->getSize().x / getSpeed())));

		return;
	}

	move(dt);
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