#include "Tree.h"

Tree::Tree(TreeType type, vec2 position, vec3 color) : GameObject(position, color) {
	this->setState(State::MOVING);

	switch (type) {
		case LARGE: {
			initTree(vec2(80.0f, 0.0f), new Texture("../textures/stammLarge.jpg"));
			break;
		}
		case MEDIUM: {
			initTree(vec2(60.0f, 0.0f), new Texture("../textures/stammMedium.jpg"));
			break;
		}
		case SMALL: {
			initTree(vec2(100.0f, 0.0f), new Texture("../textures/stammSmall.jpg"));
			break;
		}
	}

	this->setCollisionStruct({ Event::COLL_TREE_TURTLE, this->getCurrentMovement() });
	setSize(vec2(getTexture()->getWidth(), Y_TILE_SIZE));
}

Tree::~Tree() {}

void Tree::doLogic(GLfloat dt) {
	if (getState() == State::MOVING) {
		move(dt);
	}
}

GameObject::Rectangle Tree::getCriticalHitBox() {
	struct Rectangle r = { this->getPosition(), this->getSize() };
	return r;
}

void Tree::initTree(vec2 movement, Texture* texture) {
	this->setTexture(texture);
	this->setMovement(movement);
	this->setSize(vec2(X_TILE_SIZE, Y_TILE_SIZE));
}