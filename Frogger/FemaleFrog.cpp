#include "FemaleFrog.h"
#include <iostream>

const map<Direction, Rectangle> FemaleFrog::textureSet = {
	{ Direction::UP,{ Vec2(1, 6), Vec2(1, 1) } },
	{ Direction::RIGHT,{ Vec2(2, 6), Vec2(1, 1) } },
	{ Direction::LEFT,{ Vec2(3, 6), Vec2(1, 1) } }
};

FemaleFrog::FemaleFrog(Vec2 position) : Opponent(position, FROG_SPEED, textureSet.at(Direction::UP), textureSet, transitionSet) {
	this->movingDuration = 0.0f;
	this->idleTimer = 0;
	this->setCollisionInfo({ Event::COLLECTING, 6 });
}

void FemaleFrog::doLogic(float dt) {
	GameObject::doLogic(dt);

	switch (getState()) {
		case State::TRANSPORT:
		{
			idle(dt);
		}; break;
		case State::MOVE_TRANSPORT:
		{
			targetPositionReached(dt);
		}; break;
		case State::COLLECTED:
		{
			setExpired(true);
		}; return;
	}

	increaseLivingTime(dt);
	setExpired(Opponent::isOutsideOfBorders());
}

void FemaleFrog::idle(float dt) {
	idleTimer += dt;

	//setDirection(Direction::UP);
	setTextureRegion(getTextureRegionFor(Direction::UP));
	// Übernehme v von interacting object (tree)
	setMovement(getCurrentInteraction().movement);

	if (idleTimer > 0.5f) {
		doTransition(Event::START_MOVING);
		idleTimer = 0;

		Vec2 currentMovement = directions.at(getDirection()) * getVMax();
		Vec2 tmpTargetPosition = getPosition().add(Vec2(X_TILE_SIZE, 0));

		setValidMovement(tmpTargetPosition.x, tmpTargetPosition.x);

		Vec2 movement = directions.at(getDirection());
		movement = movement.mul(getVMax());

		setTextureRegion(getTextureRegionFor(getDirection()));
		setMovement(movement.add(getCurrentInteraction().movement));
		this->targetPosition = getPosition().add((getMovement().mul(X_TILE_SIZE / getVMax())));

		return;
	}

	//move(dt);
}

bool FemaleFrog::targetPositionReached(float dt) {
	if (getState() == State::TRANSPORT)
		return false;

	this->movingDuration += dt;

	if (movingDuration > X_TILE_SIZE / getVMax()) {
		this->movingDuration = 0.0f;
		this->setPosition(targetPosition);
		this->setMovement(Vec2());
		doTransition(Event::TARGET_POSITION_REACHED);

		return true;
	}

	return false;
}