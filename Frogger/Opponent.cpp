#include "Opponent.h"

Opponent::Opponent(Vec2 position, const Rectangle& textureRegion, map<Direction, Rectangle> textureSet, const vector<TransitionElement>& transitionSet)
	: GameObject(position, textureRegion, textureSet, transitionSet) {

	this->setState(State::IDLE);
	this->homePosition = position;
	this->expired = false;
	this->livingTime = 0;
	this->currentDirection = Direction::LEFT;
}

bool Opponent::isOutsideOfBorders() {
	if (this->getPosition().x > X_TILE_SIZE * TILES_X && homePosition.x < 0) {
		return true;
	}

	if (this->getPosition().x + this->getSize().x < 0 && homePosition.x > 0) {
		return true;
	}

	return false;
}

void Opponent::setValidMovement(float leftThreshold, float rightThreshold) {
	float currentTransportPosition = getHomePosition().x + (getCurrentInteraction().movement.x * getLivingTime());
	Rectangle transporterHitBox = { Vec2(currentTransportPosition, getHomePosition().y), getCurrentInteraction().textureRegion.size.mul(X_TILE_SIZE) };

	if (getDirection() == Direction::RIGHT) {
		if (rightThreshold > currentTransportPosition + transporterHitBox.size.x) {
			setDirection(Direction::LEFT);
		}
	}

	if (getDirection() == Direction::LEFT) {
		if (leftThreshold < currentTransportPosition) {
			setDirection(Direction::RIGHT);
		}
	}
}

void Opponent::doLogic(float dt) {
	GameObject::doLogic(dt);
}

Rectangle Opponent::getCriticalHitBox() {
	return GameObject::getCriticalHitBox();
}