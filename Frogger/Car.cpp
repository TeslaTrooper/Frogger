#include "Car.h"

Car::Car(CarType carType, vec2 position, vec3 color) : GameObject(position, color) {
	this->setState(State::MOVING);
	this->setCollisionStruct({ Event::COLL_LETHAL_OBJECTS, glm::vec2(0.0f, 0.0f) });

	switch (carType) {
		case CarType::CAR_YELLOW: {
			initCar(vec2(-30.0f, 0.0f), new Texture("../textures/wall.jpg"));
		}; break;
		case CarType::CAR_WHITE: {
			initCar(vec2(80.0f, 0.0f), new Texture("../textures/wall.jpg"));
		}; break;
		case CarType::CAR_PINK: {
			initCar(vec2(-45.0f, 0.0f), new Texture("../textures/wall.jpg"));
		}; break;
		case CarType::HARVESTER: {
			initCar(vec2(50.0f, 0.0f), new Texture("../textures/wall.jpg"));
		}; break;
		case CarType::TRUCK: {
			initCar(vec2(-60.0f, 0.0f), new Texture("../textures/wall.jpg"));
			this->setSize(vec2(X_TILE_SIZE * 2, Y_TILE_SIZE));
		}; break;
	}
}

Car::~Car() {}

void Car::doLogic(GLfloat dt) {
	if (getState() == State::MOVING) {
		move(dt);
	}
}

GameObject::Rectangle Car::getCriticalHitBox() {
	struct Rectangle r = { this->getPosition(), this->getSize() };
	return r;
} 

void Car::initCar(vec2 movement, Texture* texture) {
	this->setTexture(texture);
	this->setMovement(movement);
	this->setSize(vec2(X_TILE_SIZE, Y_TILE_SIZE));
}