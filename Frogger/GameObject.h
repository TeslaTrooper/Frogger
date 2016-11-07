#ifndef GAME_OBJECT
#define GAME_OBJECT

#include "Renderer.h"
#include "Direction.h"
#include "State.h"
#include "CollisionStruct.h"

using namespace glm;

class GameObject {
	vec2 position;
	vec2 size;
	vec3 color;
	Texture* texture;
	float speed;
	State state;
	vec2 movement;
	CollisionStruct collisionStruct;

public:

	static const int X_TILE_SIZE;
	static const int Y_TILE_SIZE;

	struct Rectangle {
		vec2 position;
		vec2 size;
	};

	GameObject(vec2 position, vec2 size, vec3 color, Texture* texture) : position(position), size(size), color(color), texture(texture) {}
	GameObject(vec2 position, vec2 size, vec3 color) : position(position), size(size), color(color) {}
	GameObject(vec2 position, vec3 color) : position(position), color(color) {}

	~GameObject();

	vec2 getPosition() { return position; };
	vec2 getSize() { return size; };
	vec3 getColor() { return color; };
	Texture* getTexture() { return texture; };
	float getSpeed() { return speed; };
	virtual State getState() { return state; };
	vec2 getCurrentMovement() { return movement; };
	CollisionStruct getCollisionStruct() { return collisionStruct; };

	void setPosition(vec2 position) { this->position = position; };
	void setSpeed(float speed) { this->speed = speed; };
	void setState(State state) { this->state = state; };
	void setMovement(vec2 movement) { this->movement = movement; };
	void move(GLfloat dt);
	void draw(Renderer* renderer);
	void setTexture(Texture* texture) { this->texture = texture; };
	void setSize(vec2 size) { this->size = size; };
	void setCollisionStruct(CollisionStruct collisionStruct) { this->collisionStruct = collisionStruct; };
	void resetMovement() { this->movement = vec2(0.0f, 0.0f); };

	virtual Rectangle getCriticalHitBox() = 0;
	virtual void doLogic(GLfloat dt) = 0;
};

#endif GAME_OBJECT