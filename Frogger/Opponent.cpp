#include "Opponent.h"

Opponent::Opponent(Vec2 position, const vector<TransitionElement>& transitionSet, const Rectangle& textureRegion)
	: GameObject(position, textureRegion, transitionSet) {

	this->setState(State::IDLE);
	this->homePosition = position;
	this->expired = false;
	this->livingTime = 0;
	this->currentDirection = Direction::RIGHT;
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

void Opponent::doLogic(GLfloat dt) {
	GameObject::doLogic(dt);
}