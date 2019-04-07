#include "CrocodileHead.h"

const map<Direction, Rectangle> CrocodileHead::textureSet = {
	{ Direction::RIGHT,{ Vec2(7, 6), Vec2(1, 1) } }
};

CrocodileHead::CrocodileHead(Vec2 position) : Opponent(position, SPEED_MEDIUM_TREE, textureSet.at(Direction::RIGHT), textureSet, {}) {
	//this->setMovement(Vec2(getSpeed(), 0.0f));
	setMovement(Vec2(getVMax(), 0.0f));
	Entity::setDirection(getMovement().norm());
	this->setCollisionInfo({ Event::COLL_LETHAL_OBJECTS, 10 });
}

void CrocodileHead::doLogic(float dt) {
	GameObject::doLogic(dt);

	//move(dt);
	setExpired(false);
}