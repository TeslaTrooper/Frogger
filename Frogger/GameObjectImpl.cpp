#include "GameObject.h"

GameObject::GameObject(Vec2 position) : position(position) {
	this->setState(State::MOVING);
}

GameObject::GameObject(Rectangle textureRegion) : GameObject(Vec2(0.0f, 0.0f)) {
	this->textureRegion = textureRegion;
	this->setSize(Vec2(getTextureRegion().size.x*X_TILE_SIZE, getTextureRegion().size.y*Y_TILE_SIZE));
}

GameObject::GameObject(Vec2 position, Rectangle textureRegion) : GameObject(position) {
	this->textureRegion = textureRegion;
	this->setSize(Vec2(getTextureRegion().size.x*X_TILE_SIZE, getTextureRegion().size.y*Y_TILE_SIZE));
}

GameObject::GameObject(Vec2 position, Vec2 size, Rectangle textureRegion) : GameObject(position, textureRegion) {
	this->setSize(size);
}

GameObject::~GameObject() {
	//delete texture;
}

void GameObject::move(GLfloat dt) {
	Vec2 pos = getPosition();
	Vec2 newPos = Vec2(pos.x + getCurrentMovement().x * dt, pos.y + getCurrentMovement().y * dt);
	setPosition(newPos);
}

Drawable GameObject::getDrawable() {
	return { getPosition(), getSize(), getTextureRegion() };
}

Rectangle GameObject::getCriticalHitBox() {
	return { this->getPosition(), this->getSize() };
}
void GameObject::doLogic(GLfloat dt) {
	if (getState() == State::MOVING) {
		move(dt);
	}
}