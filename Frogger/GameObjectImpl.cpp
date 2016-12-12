#include "GameObject.h"

GameObject::GameObject(Vec2 position, const vector<TransitionElement>& transitionSet) 
	: position(position), stateMachine(transitionSet) {

	this->setState(State::MOVING);
}

/*GameObject::GameObject(Rectangle textureRegion, const vector<TransitionElement>& transitionSet) 
	: GameObject(Vec2(0.0f, 0.0f), transitionSet) {

	this->textureRegion = textureRegion;
	this->setSize(Vec2(getTextureRegion().size.x*X_TILE_SIZE, getTextureRegion().size.y*Y_TILE_SIZE));
	this->objectInfo.textureRegion = textureRegion;
}*/

// Wird von Frog verwendet
GameObject::GameObject(Vec2 position, Rectangle textureRegion, map<Direction, Rectangle> textureSet, const vector<TransitionElement>& transitionSet)
	: GameObject(position, transitionSet) {

	this->setSize(textureRegion.size.mul(X_TILE_SIZE));
	this->textureRegion = textureRegion;
	this->textureSet = textureSet;
}

// Wird vom ObjectMnagaer verwendet
GameObject::GameObject(ObjectInfo objectInfo, const vector<TransitionElement>& transitionSet)
	: GameObject(objectInfo.hitBox.position, objectInfo.textureRegion, {}, transitionSet) {
	this->objectInfo = objectInfo;
	this->setMovement(objectInfo.movement);
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

void GameObject::gotoPreviousState() {
	stateMachine.gotoPreviousState();
}

void GameObject::registerInteraction(ObjectInfo objectInfo) {
	this->interactingObjectInfo = objectInfo;
}

bool GameObject::targetPositionReached(GLfloat dt) {
	return false;
}