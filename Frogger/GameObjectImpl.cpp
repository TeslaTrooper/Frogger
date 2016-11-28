#include "GameObject.h"

GameObject::GameObject(Vec2 position, const vector<TransitionElement>& transitionSet) 
	: position(position), stateMachine(transitionSet) {

	this->setState(State::MOVING);
}

GameObject::GameObject(Rectangle textureRegion, const vector<TransitionElement>& transitionSet) 
	: GameObject(Vec2(0.0f, 0.0f), transitionSet) {

	this->textureRegion = textureRegion;
	this->setSize(Vec2(getTextureRegion().size.x*X_TILE_SIZE, getTextureRegion().size.y*Y_TILE_SIZE));
}

GameObject::GameObject(Vec2 position, Vec2 size, Rectangle textureRegion, const vector<TransitionElement>& transitionSet) 
	: GameObject(position, transitionSet) {

	this->setSize(size);
	this->textureRegion = textureRegion;
}

GameObject::~GameObject() {}

void GameObject::move(GLfloat dt) {
	if (targetPositionReached(dt)) {
		return;
	}

	setPosition(this->getPosition().add((getCurrentMovement().mul(dt))));
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

void GameObject::setMovement(Vec2 movement) {
	resetMovement();
	vectors[0] = movement;
}

void GameObject::resetMovement() {
	for (int i = 0; i < sizeof(vectors) / sizeof(Vec2); i++) {
		vectors[i].clear();
	}
}

bool GameObject::doTransition(Event ev) {
	return stateMachine.doTransition(ev);
}

void GameObject::registerEvent(CollisionStruct currentEvent) {
	this->currentEvent = currentEvent;
}

bool GameObject::targetPositionReached(GLfloat dt) {
	return false;
}