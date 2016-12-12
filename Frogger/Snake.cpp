#include "Snake.h"

const map<Direction, Rectangle> Snake::textureSet = {
	{ Direction::LEFT,{ Vec2(7, 6), Vec2(2, 1) } },
	{ Direction::RIGHT,{ Vec2(0, 7), Vec2(2, 1) } }
};

Snake::Snake(Vec2 position) : Opponent(position, textureSet.at(Direction::LEFT), textureSet, transitionSet) {
	this->setSpeed(SPEED_SNAKE);
	this->setCollisionInfo({ Event::COLL_LETHAL_OBJECTS, 10 });
}

void Snake::doLogic(GLfloat dt) {
	doTransition(getCurrentInteraction().collisionInfo.effect);

	switch (getState()) {
		case State::MOVE_TRANSPORT: {
			float currentTransportPosition = getHomePosition().x + (getCurrentInteraction().movement.x * getLivingTime());
			Rectangle transporterHitBox = { Vec2(currentTransportPosition, getHomePosition().y), getCurrentInteraction().textureRegion.size.mul(X_TILE_SIZE) };

			if (getDirection() == Direction::LEFT) {
				if (getPosition().x < transporterHitBox.position.x) {
					setDirection(Direction::RIGHT);
				}
			}

			if (getDirection() == Direction::RIGHT) {
				if (getPosition().x + getSize().x > transporterHitBox.position.x + transporterHitBox.size.x) {
					setDirection(Direction::LEFT);
				}
			}

			Vec2 movement = directions.at(getDirection());
			movement = movement.mul(getSpeed());
			setTextureRegion(getTextureRegionFor(getDirection()));
			setMovement(movement.add(getCurrentInteraction().movement));

			move(dt);
		}; break;
	}

	increaseLivingTime(dt);
	setExpired(Opponent::isOutsideOfBorders());
}