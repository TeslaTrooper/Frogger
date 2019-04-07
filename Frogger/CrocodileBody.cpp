#include "CrocodileBody.h"

const map<Direction, Rectangle> CrocodileBody::textureSet = {
	{ Direction::RIGHT,{ Vec2(4, 6), Vec2(4, 1) } }
};

CrocodileBody::CrocodileBody(Vec2 position) : Opponent(position, SPEED_MEDIUM_TREE, textureSet.at(Direction::RIGHT), textureSet, {}) {
	//this->setMovement(Vec2(getSpeed(), 0.0f));
	setMovement(Vec2(getVMax(), 0.0f));
	Entity::setDirection(getMovement().norm());
	this->setCollisionInfo({ Event::COLL_TREE_TURTLE, 5 });
}

void CrocodileBody::doLogic(float dt) {
	GameObject::doLogic(dt);

	//move(dt);
	setExpired(false);
}