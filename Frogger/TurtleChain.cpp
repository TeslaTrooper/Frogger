#include "TurtleChain.h"

TurtleChain::TurtleChain(ChainType chainType, glm::vec2 position, glm::vec3 color) : GameObject(position, color) {
	this->setState(State::MOVING);

	switch (chainType) {
		case ChainType::TWO_ELEMENT_CHAIN: {
			initChain(glm::vec2(-30.0f, 0.0f), new Texture("../textures/stammMedium.jpg"));
		}; break;
		case ChainType::THREE_ELEMENT_CHAIN: {
			initChain(glm::vec2(-30.0f, 0.0f), new Texture("../textures/stammLarge.jpg"));
		}; break;
	}

	this->setCollisionStruct({ Event::COLL_TREE_TURTLE, this->getCurrentMovement() });
	setSize(vec2(getTexture()->getWidth(), Y_TILE_SIZE));
}

TurtleChain::~TurtleChain() {}

void TurtleChain::doLogic(GLfloat dt) {
	if (getState() == State::MOVING) {
		move(dt);
	}
}

GameObject::Rectangle TurtleChain::getCriticalHitBox() {
	struct Rectangle r = { this->getPosition(), this->getSize() };
	return r;
}

void TurtleChain::initChain(vec2 movement, Texture* texture) {
	this->setTexture(texture);
	this->setMovement(movement);
	this->setSize(vec2(X_TILE_SIZE, Y_TILE_SIZE));
}