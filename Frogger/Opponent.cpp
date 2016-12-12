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

void Opponent::doLogic(GLfloat dt) {
	GameObject::doLogic(dt);
}