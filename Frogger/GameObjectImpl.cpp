#include "GameObject.h"

GameObject::GameObject(Vec2 position, vec3 color) : position(position), color(color) {
	this->setState(State::MOVING);
}

GameObject::GameObject(vec3 color, Texture* texture) : GameObject(Vec2(0.0f, 0.0f), color) {
	this->texture = texture;
	this->setSize(Vec2(getTexture()->getWidth(), Y_TILE_SIZE));
}

GameObject::GameObject(Vec2 position, Vec2 size, vec3 color) : GameObject(position, color) {
	this->color = color;
}

GameObject::GameObject(Vec2 position, vec3 color, Texture* texture) : GameObject(position, color) {
	this->texture = texture;
	this->setSize(Vec2(getTexture()->getWidth(), Y_TILE_SIZE));
}

GameObject::GameObject(Vec2 position, Vec2 size, vec3 color, Texture* texture) : GameObject(position, color, texture) {
	this->setSize(size);
}

GameObject::~GameObject() {
	delete texture;
}

void GameObject::move(GLfloat dt) {
	Vec2 pos = getPosition();
	Vec2 newPos = Vec2(pos.x + getCurrentMovement().x * dt, pos.y + getCurrentMovement().y * dt);
	setPosition(newPos);
}

void GameObject::draw(Renderer* renderer) {
	renderer->draw(this->getTexture(), this->getPosition(), this->getSize(), this->getColor());
}

Rectangle GameObject::getCriticalHitBox() {
	return { this->getPosition(), this->getSize() };
}
void GameObject::doLogic(GLfloat dt) {
	if (getState() == State::MOVING) {
		move(dt);
	}
}