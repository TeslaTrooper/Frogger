#ifndef UTIL
#define UTIL

#include <map>

#include "Vec2.h"
#include "Constants.h"
#include "Texture.h"

using namespace std;

enum Event {
	ARROW_KEYS,
	TIME_OUT,
	TARGET_POSITION_REACHED,
	DIE_SEQUENCE_EXPIRED,
	COLL_TREE_TURTLE,
	COLL_LETHAL_OBJECTS,
	COLL_NONE,
	NEUTRAL,
	COLL_POOL
};

enum Direction {
	LEFT,
	UP,
	RIGHT,
	DOWN,
	NONE
};

enum Objects {
	CAR_YELLOW,
	CAR_WHITE,
	CAR_PINK,
	TRUCK,
	HARVESTER,
	LARGE_TREE,
	MEDIUM_TREE,
	SMALL_TREE,
	TWO_ELEMENT_CHAIN,
	THREE_ELEMENT_CHAIN
};

enum State {
	IDLE,
	MOVING,
	TRANSPORTING_RIGHT,
	TRANSPORTING_LEFT,
	TRANSPORT,
	MOVE_TRANSPORT,
	CARRYING,
	DIEING,
	KILLED,
	ALIGNING,
	NAVIGATING,
	INACTIVE
};

enum DrawableType {
	OBJECT,
	FONT
};

/*
Definiert Auswirkungen bei einer Kollision zweier Objekte.
effect gibt an, was bei einer Kollision hinsichtlich der Spielogik
passieren soll.
movement gibt in Abhängigkeit von effect an, in wie weit die Kollision
Auswirkungen auf den aktuellen Bewegungsvektor hat.
*/
struct CollisionStruct {
	Event effect;
	Vec2 movement;
};

struct Rectangle {
	Vec2 position;
	Vec2 size;
};

struct Drawable {
	Vec2 position;
	Vec2 size;
	Texture* texture;
};

const map<Direction, Vec2> directions = {
	{ Direction::LEFT, Vec2(-FROG_SPEED, 0.0f) },
	{ Direction::UP, Vec2(0.0f, -FROG_SPEED) },
	{ Direction::RIGHT, Vec2(FROG_SPEED, 0.0f) },
	{ Direction::DOWN, Vec2(0.0f, FROG_SPEED) }
};

bool intersects(Rectangle rect1, Rectangle rect2);

#endif UTIL