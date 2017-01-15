#include "Turtle.h"

Turtle::Turtle(Objects type, Vec2 position, Rectangle textureRegion, bool animating) 
	: Opponent(position, textureRegion, {}, transitionSet) {

	if (type == Objects::TWO_ELEMENT_CHAIN) {
		this->setSpeed(SPEED_TWO_ELEMENT_CHAIN);
		textureSet = {
			{ Direction::LEFT,{ Vec2(8, 4), Vec2(2,1) } }
		};
	} else if(type == Objects::THREE_ELEMENT_CHAIN) {
		this->setSpeed(SPEED_THREE_ELEMENT_CHAIN);
		textureSet = {
			{ Direction::LEFT,{ Vec2(7, 5), Vec2(3,1) } }
		};
	}
	
	this->setMovement(Vec2(getSpeed(), 0.0f));
	this->setCollisionInfo({ Event::COLL_TREE_TURTLE, 5 });

	movingTimer = 0;
	divingTimer = 0;
	animationTimer = 0;
	textureRegionOffset = 0;
	this->type = type;
	this->setState(State::MOVING);
	this->animating = animating;
}

void Turtle::doLogic(float dt) {
	if (type == Objects::THREE_ELEMENT_CHAIN || !animating) {
		move(dt);
		return;
	}

	switch (getState()) {
		case State::MOVING: {
			movingTimer += dt;
			if (movingTimer > 2.f) {
				movingTimer = 0;
				doTransition(Event::START_DIVING);
			}
		}; break;
		case State::DESCENDING: {
			if (animationTimer < 0.2f) {
				setTextureRegion({ Vec2(2, 7), Vec2(2, 1) });
			} else if (animationTimer >= 0.2f && animationTimer < 0.4f) {
				setTextureRegion({ Vec2(4, 7), Vec2(2, 1) });
			} else if (animationTimer >= 0.4f && animationTimer < 0.6f) {
				setTextureRegion({ Vec2(6, 7), Vec2(2, 1) });
			} else if (animationTimer >= 0.6f && animationTimer < 0.8f) {
				setTextureRegion({ Vec2(8, 7), Vec2(2, 1) });
			}
			animationTimer += dt;

			if (animationTimer >= 0.8) {
				doTransition(Event::DESCENDING_FINISHED);
				animationTimer = 0;
			}
		}; break;
		case State::DIVING: {
			this->setCollisionInfo({ Event::COLL_LETHAL_OBJECTS, 10 });

			divingTimer += dt;
			if (divingTimer > 1.f) {
				divingTimer = 0;
				doTransition(Event::START_MOVING);
			}
		}; break;
		case State::TURNING_UP: {
			this->setCollisionInfo({ Event::COLL_TREE_TURTLE, 5 });

			if (animationTimer < 0.2f) {
				setTextureRegion({ Vec2(6, 7), Vec2(2, 1) });
			} else if (animationTimer >= 0.2f && animationTimer < 0.4f) {
				setTextureRegion({ Vec2(4, 7), Vec2(2, 1) });
			} else if (animationTimer >= 0.4f && animationTimer < 0.6f) {
				setTextureRegion({ Vec2(2, 7), Vec2(2, 1) });
			}
			animationTimer += dt;

			if (animationTimer >= 0.6f) {
				setTextureRegion(textureSet.at(Direction::LEFT));
				doTransition(Event::TURNING_UP_FINISHED);
				animationTimer = 0;
			}
		}; break;
	}

	move(dt);
}