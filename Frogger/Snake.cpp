#include "Snake.h"

Snake::Snake(Vec2 position) : Opponent(position, transitionSet, objectTextureRegions.at(Objects::SNAKE)) {
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
			setMovement(movement.add(getCurrentInteraction().movement));

			move(dt);
		}; break;
	}

	increaseLivingTime(dt);
	setExpired(Opponent::isOutsideOfBorders());
}