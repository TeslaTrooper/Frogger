#include "CrocodileBody.h"

const map<Direction, Rectangle> CrocodileBody::textureSet = {
	{ Direction::RIGHT,{ Vec2(7, 7), Vec2(4, 1) } }
};

CrocodileBody::CrocodileBody(Vec2 position) : Opponent(position, textureSet.at(Direction::RIGHT), textureSet, {}) {
	this->setSpeed(SPEED_MEDIUM_TREE);
	this->setMovement(Vec2(getSpeed(), 0.0f));
	this->setCollisionInfo({ Event::COLL_TREE_TURTLE, 5 });
}

void CrocodileBody::doLogic(GLfloat dt) {
	move(dt);
	setExpired(false);
}