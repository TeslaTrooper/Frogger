#include "GameObject.h"

GameObject::GameObject(Vec2 position) : position(position) {
	this->setState(State::MOVING);
}

GameObject::GameObject(Texture* texture) : GameObject(Vec2(0.0f, 0.0f)) {
	this->texture = texture;
	this->setSize(Vec2(getTexture()->getWidth(), Y_TILE_SIZE));
}

GameObject::GameObject(Vec2 position, Texture* texture) : GameObject(position) {
	this->texture = texture;
	this->setSize(Vec2(getTexture()->getWidth(), Y_TILE_SIZE));
}

GameObject::GameObject(Vec2 position, Vec2 size, Texture* texture) : GameObject(position, texture) {
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

Drawable GameObject::getDrawable() {
	return { getPosition(), getSize(), getTexture() };
}

Rectangle GameObject::getCriticalHitBox() {
	return { this->getPosition(), this->getSize() };
}
void GameObject::doLogic(GLfloat dt) {
	if (getState() == State::MOVING) {
		move(dt);
	}
}