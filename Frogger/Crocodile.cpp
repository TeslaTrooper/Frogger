#include "Crocodile.h"

const map<Direction, Rectangle> Crocodile::textureSet = {
	{ Direction::RIGHT,{ Vec2(2, 7), Vec2(3, 1) } }
};

Crocodile::Crocodile(Vec2 position) : Opponent(position, textureSet.at(Direction::RIGHT), textureSet, {}) {
	this->setSpeed(SPEED_MEDIUM_TREE);
	this->setMovement(Vec2(getSpeed(), 0.0f));
	this->setCollisionInfo({ Event::COLL_TREE_TURTLE, 10 });
}

void Crocodile::doLogic(GLfloat dt) {
	move(dt);
	setExpired(false);
}

Rectangle Crocodile::getCriticalHitBox() {
	return { this->getPosition(), this->getSize() };
}