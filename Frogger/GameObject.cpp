#include "GameObject.h"

GameObject::GameObject(Vec2 position, const vector<TransitionElement>& transitionSet)
	: Entity(), stateMachine(transitionSet) {

	this->setState(State::MOVING);
	setPosition(position);
}

/*GameObject::GameObject(Rectangle textureRegion, const vector<TransitionElement>& transitionSet)
	: GameObject(Vec2(0.0f, 0.0f), transitionSet) {

	this->textureRegion = textureRegion;
	this->setSize(Vec2(getTextureRegion().size.x*X_TILE_SIZE, getTextureRegion().size.y*Y_TILE_SIZE));
	this->objectInfo.textureRegion = textureRegion;
}*/

// Wird von Frog verwendet
GameObject::GameObject(Vec2 position, float speed, Rectangle textureRegion, map<Direction, Rectangle> textureSet, const vector<TransitionElement>& transitionSet)
	: GameObject(position, transitionSet) {

	setVMax(speed);
	this->setSize(textureRegion.size.mul(X_TILE_SIZE).sub(Vec2(1, 1)));
	this->textureRegion = textureRegion;
	this->textureSet = textureSet;
}

// Wird vom ObjectMnagaer verwendet
GameObject::GameObject(ObjectInfo objectInfo, const vector<TransitionElement>& transitionSet)
	: GameObject(objectInfo.hitBox.position, objectInfo.movement.length(), objectInfo.textureRegion, {}, transitionSet) {
	this->objectInfo = objectInfo;
	this->setMovement(objectInfo.movement);
	this->setDirection(objectInfo.movement.norm());

	updateTransformation();
}

GameObject::~GameObject() {}

void GameObject::doLogic(float dt) {
	updateTransformation();
	doTransition(getCurrentInteraction().collisionInfo.effect);
}

Drawable GameObject::getDrawable() {
	return { getTransformation(), getTextureRegion() };
}

Rectangle GameObject::getCriticalHitBox() {
	return { this->getPosition(), this->getSize() };
}

void GameObject::setAcceleration(const float value) {
	if (value == 0) {
		Entity::setAcceleration(0);
	} else {
		Entity::setAcceleration(getVMax() / value);
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

bool GameObject::targetPositionReached(float dt) {
	return false;
}

// TODO Implement

bool GameObject::canCollide() const {
	return true;
}

bool GameObject::canCollideWith(const Entity* const e) const {
	return true;
}

void GameObject::updateTransformation() {
	setTransformation(Mat4::getTransformation(getPosition(), size));
}

VertexData GameObject::getVertexData() const {
	return VertexData(ModelData::vertices, 4, 4);
}

IndexData GameObject::getTriangulatedIndexData() const {
	return IndexData(ModelData::indices, 6);
}