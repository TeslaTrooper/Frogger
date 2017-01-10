#include "Frog.h"

const map<Direction, Rectangle> Frog::textureSet = {
	{ Direction::UP,{ Vec2(0, 8), Vec2(1,1) } },
	{ Direction::RIGHT,{ Vec2(1, 8), Vec2(1,1) } },
	{ Direction::LEFT,{ Vec2(3, 8), Vec2(1,1) } },
	{ Direction::DOWN,{ Vec2(2, 8), Vec2(1,1) } }
};

Frog::Frog(Vec2 position) 
	: GameObject(position, textureSet.at(Direction::UP), textureSet, transitionSet) {

	this->setState(State::IDLE);
	this->setSpeed(FROG_SPEED);
	this->homePosition = position;
	this->movingDuration = 0.0f;
	this->decaeseTimer = 0;
	this->setCollisionInfo({ Event::COLLECTING, 6});
	textureOffset = 0;
}

Frog::Frog(Vec2 position, State initialState) : Frog(position) {
	this->setState(initialState);
}

void Frog::moveTo(Direction direction) {
	Vec2 movement = directions.at(direction);
	movement = movement.mul(getSpeed());

	if (!validMovement(movement) || !doTransition(Event::ARROW_KEYS)) {
		return;
	}

	Rectangle textureRegion = getTextureRegionFor(direction);
	textureRegion.position.y += textureOffset;

	this->setTextureRegion(textureRegion);
	this->setMovement(movement.add(getCurrentInteraction().movement));

	this->targetPosition = getPosition().add((getCurrentMovement().mul(this->getSize().x / getSpeed())));
}

void Frog::doLogic(GLfloat dt) {
	doTransition(getCurrentInteraction().collisionInfo.effect);
	
	switch (getState()) {
		case State::DIEING: {
			die(dt);
		}; break;
		case State::KILLED: {
			reset();
		}; break;
		case State::MOVING: {
			move(dt);
		}; break;
		case State::MOVE_TRANSPORT: {
			move(dt);

			if (isOutsideOfBorders()) {
				registerInteraction({ Rectangle(), Rectangle(), Vec2(),{ Event::COLL_LETHAL_OBJECTS, 0 } });
			}
		}; break;
		case State::TRANSPORT: {
			vectors[1] = getCurrentInteraction().movement;
			move(dt);

			if (isOutsideOfBorders()) {
				doTransition(Event::COLL_LETHAL_OBJECTS);
			}
		}; break;
		case State::ALIGNING: {
			float length = getCurrentMovement().length();
			this->resetMovement();
			vectors[0] = this->getPosition().rotateTo(getCurrentInteraction().hitBox.position, length);
			targetPosition = getCurrentInteraction().hitBox.position;
		}; break;
		case State::NAVIGATING: {
			move(dt);
		}; break;
		case State::COLLECTED: {
			textureOffset = 1;
			Rectangle textureRegion = getTextureRegion();
			textureRegion.position.y += textureOffset;

			this->setTextureRegion(textureRegion);
			gotoPreviousState();
			move(dt);
		}; break;
	}
}

void Frog::reset() {
	doTransition(Event::RESET);

	this->setTextureRegion(objectTextureRegions.at(Objects::PLAYER));
	this->setPosition(homePosition);
	this->resetMovement();
	this->decaeseTimer = 0;
	this->movingDuration = 0;
	this->textureOffset = 0;
}

void Frog::die(GLfloat dt) {
	resetMovement();
	this->setTextureRegion({ Vec2(9, 3), Vec2(1, 1) });

	decaeseTimer += dt;
	if (decaeseTimer > 1) {
		doTransition(Event::DIE_SEQUENCE_EXPIRED);
	}
}

bool Frog::targetPositionReached(GLfloat dt) {
	if (getState() == State::TRANSPORT) {
		return false;
	}

	this->movingDuration += dt;

	if (movingDuration > this->getSize().x / getSpeed()) {
		this->movingDuration = 0.0f;
		this->setPosition(targetPosition);
		this->resetMovement();
		doTransition(Event::TARGET_POSITION_REACHED);

		return true;
	}

	return false;
}

bool Frog::validMovement(Vec2 movement) {
	float dX = movement.x * (this->getSize().x / getSpeed());
	float dY = movement.y * (this->getSize().y / getSpeed());


	if (this->getPosition().x + this->getSize().x + dX > X_TILE_SIZE * TILES_X) {
		return false;
	}
	if (this->getPosition().x + dX < 0) {
		return false;
	}
	if (this->getPosition().y + this->getSize().y + dY > 14 * Y_TILE_SIZE) {
		return false;
	}
	if (this->getPosition().y + dY < OFFSET_Y) {
		return false;
	}

	return true;
}

bool Frog::isOutsideOfBorders() {
	if (this->getPosition().x + this->getSize().x > X_TILE_SIZE * TILES_X) {
		return true;
	}

	if (this->getPosition().x < 0) {
		return true;
	}

	return false;
}

Frog::~Frog() {}