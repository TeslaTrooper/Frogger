#include "Snake.h"

const map<Direction, Rectangle> Snake::textureSet = {
	{ Direction::LEFT,{ Vec2(8, 6), Vec2(2, 1) } },
	{ Direction::RIGHT,{ Vec2(0, 7), Vec2(2, 1) } }
};

Snake::Snake(Vec2 position) : Opponent(position, SPEED_SNAKE, textureSet.at(Direction::LEFT), textureSet, transitionSet) {
	this->setCollisionInfo({ Event::COLL_LETHAL_OBJECTS, 10 });
}

void Snake::doLogic(float dt) {
	GameObject::doLogic(dt);

	switch (getState()) {
		case State::MOVE_TRANSPORT:
		{
			float currentTransportPosition = getHomePosition().x + (getCurrentInteraction().movement.x * getLivingTime());
			Rectangle transporterHitBox = { Vec2(currentTransportPosition, getHomePosition().y), getCurrentInteraction().textureRegion.size.mul(X_TILE_SIZE) };

			setValidMovement(getPosition().x, getPosition().x + getSize().x);

			Vec2 movement = directions.at(getDirection());
			movement = movement.mul(getVMax());
			setTextureRegion(getTextureRegionFor(getDirection()));
			setMovement(movement.add(getCurrentInteraction().movement));
		}; break;
	}

	increaseLivingTime(dt);
	setExpired(Opponent::isOutsideOfBorders());
}