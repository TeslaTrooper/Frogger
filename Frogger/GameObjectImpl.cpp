#include "GameObject.h"

const int GameObject::X_TILE_SIZE = 40;
const int GameObject::Y_TILE_SIZE = 40;

GameObject::~GameObject() {
	delete texture;
}

void GameObject::move(GLfloat dt) {
	vec2 pos = getPosition();
	vec2 newPos = vec2(pos.x + getCurrentMovement().x * dt, pos.y + getCurrentMovement().y * dt);
	setPosition(newPos);
}

void GameObject::draw(Renderer* renderer) {
	renderer->draw(this->getTexture(), this->getPosition(), this->getSize(), this->getColor());
}