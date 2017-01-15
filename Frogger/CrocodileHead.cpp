#include "CrocodileHead.h"

const map<Direction, Rectangle> CrocodileHead::textureSet = {
	{ Direction::RIGHT,{ Vec2(7, 6), Vec2(1, 1) } }
};

CrocodileHead::CrocodileHead(Vec2 position) : Opponent(position, textureSet.at(Direction::RIGHT), textureSet, {}) {
	this->setSpeed(SPEED_MEDIUM_TREE);
	this->setMovement(Vec2(getSpeed(), 0.0f));
	this->setCollisionInfo({ Event::COLL_LETHAL_OBJECTS, 10 });
}

void CrocodileHead::doLogic(float dt) {
	move(dt);
	setExpired(false);
}