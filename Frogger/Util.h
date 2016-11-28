#ifndef UTIL
#define UTIL

#include <GL/glew.h>
#include <string>
#include <map>
#include <vector>

#include "Vec2.h"
#include "Constants.h"

using namespace std;

#define CALC_PIXEL_RGB(data,pixel) {\
pixel[0] = (((data[0] - 33) << 2) | ((data[1] - 33) >> 4)); \
pixel[1] = ((((data[1] - 33) & 0xF) << 4) | ((data[2] - 33) >> 2)); \
pixel[2] = ((((data[2] - 33) & 0x3) << 6) | ((data[3] - 33))); \
data += 4; \
}

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
	CAR_RED,
	TRUCK,
	CAR_ORANGE,
	LARGE_TREE,
	MEDIUM_TREE,
	SMALL_TREE,
	TWO_ELEMENT_CHAIN,
	THREE_ELEMENT_CHAIN,
	PLAYER
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
	Rectangle textureRegion;
};

struct Pool {
	CollisionStruct collisionStruct;
	Rectangle hitBox;
	bool ocupied;
};

struct Initializer {
	Vec2 movement;
	Rectangle textureRegion;
	CollisionStruct collisionStruct;
};

struct TransitionElement {
	State currentState;
	Event transitionUnit;
	State newState;
};

const map<Direction, Vec2> directions = {
	{ Direction::LEFT, Vec2(-FROG_SPEED, 0.0f) },
	{ Direction::UP, Vec2(0.0f, -FROG_SPEED) },
	{ Direction::RIGHT, Vec2(FROG_SPEED, 0.0f) },
	{ Direction::DOWN, Vec2(0.0f, FROG_SPEED) }
};

const map<char, Rectangle> numbers = {
	{ '0',{ Vec2(0, 0), Vec2(1,1) } },
	{ '1',{ Vec2(1, 0), Vec2(1,1) } },
	{ '2',{ Vec2(2, 0), Vec2(1,1) } },
	{ '3',{ Vec2(3, 0), Vec2(1,1) } },
	{ '4',{ Vec2(0, 6), Vec2(1,1) } },
	{ '5',{ Vec2(4, 0), Vec2(1,1) } },
	{ '6',{ Vec2(5, 0), Vec2(1,1) } },
	{ '7',{ Vec2(6, 0), Vec2(1,1) } },
	{ '8',{ Vec2(7, 0), Vec2(1,1) } },
	{ '9',{ Vec2(8, 0), Vec2(1,1) } },
};

const map<char, Rectangle> characters = {
	{ 'A',{ Vec2(9, 0), Vec2(1,1) } },
	{ 'B',{ Vec2(0, 1), Vec2(1,1) } },
	{ 'C',{ Vec2(1, 1), Vec2(1,1) } },
	{ 'D',{ Vec2(2, 1), Vec2(1,1) } },
	{ 'E',{ Vec2(3, 1), Vec2(1,1) } },
	{ 'F',{ Vec2(4, 1), Vec2(1,1) } },
	{ 'G',{ Vec2(5, 1), Vec2(1,1) } },
	{ 'H',{ Vec2(6, 1), Vec2(1,1) } },
	{ 'I',{ Vec2(7, 1), Vec2(1,1) } },
	{ 'J',{ Vec2(8, 1), Vec2(1,1) } },
	{ 'K',{ Vec2(9, 1), Vec2(1,1) } },
	{ 'L',{ Vec2(0, 2), Vec2(1,1) } },
	{ 'M',{ Vec2(1, 2), Vec2(1,1) } },
	{ 'N',{ Vec2(2, 2), Vec2(1,1) } },
	{ 'O',{ Vec2(3, 2), Vec2(1,1) } },
	{ 'P',{ Vec2(4, 2), Vec2(1,1) } },
	{ 'Q',{ Vec2(5, 2), Vec2(1,1) } },
	{ 'R',{ Vec2(6, 2), Vec2(1,1) } },
	{ 'S',{ Vec2(7, 2), Vec2(1,1) } },
	{ 'T',{ Vec2(8, 2), Vec2(1,1) } },
	{ 'U',{ Vec2(9, 2), Vec2(1,1) } },
	{ 'V',{ Vec2(0, 3), Vec2(1,1) } },
	{ 'W',{ Vec2(1, 3), Vec2(1,1) } },
	{ 'X',{ Vec2(2, 3), Vec2(1,1) } },
	{ 'Y',{ Vec2(3, 3), Vec2(1,1) } },
	{ 'Z',{ Vec2(4, 3), Vec2(1,1) } },
};

const map<Objects, Rectangle> objetcs = {
	{ CAR_ORANGE,{ Vec2(5, 3), Vec2(1,1) } },
	{ CAR_RED,{ Vec2(6, 3), Vec2(1,1) } },
	{ CAR_WHITE,{ Vec2(7, 3), Vec2(1,1) } },
	{ CAR_YELLOW,{ Vec2(8, 3), Vec2(1,1) } },
	{ TRUCK,{ Vec2(0, 4), Vec2(2,1) } },
	{ PLAYER,{ Vec2(2, 4), Vec2(1,1) } },
	{ LARGE_TREE,{ Vec2(3, 4), Vec2(5,1) } },
	{ TWO_ELEMENT_CHAIN,{ Vec2(8, 4), Vec2(2,1) } },
	{ MEDIUM_TREE,{ Vec2(0, 5), Vec2(4,1) } },
	{ SMALL_TREE,{ Vec2(4, 5), Vec2(3,1) } },
	{ THREE_ELEMENT_CHAIN,{ Vec2(7, 5), Vec2(3,1) } },
};

const map<Objects, Initializer> objDefinitions = {
	{ Objects::CAR_YELLOW,
	{ Vec2(-30.0f, 0.0f), objetcs.at(Objects::CAR_YELLOW),{ Event::COLL_LETHAL_OBJECTS, Vec2(0.0f, 0.0f) } }
	},
	{ Objects::CAR_WHITE,
	{ Vec2(80.0f, 0.0f), objetcs.at(Objects::CAR_WHITE),{ Event::COLL_LETHAL_OBJECTS, Vec2(0.0f, 0.0f) } }
	},
	{ Objects::CAR_RED,
	{ Vec2(-45.0f, 0.0f), objetcs.at(Objects::CAR_RED),{ Event::COLL_LETHAL_OBJECTS, Vec2(0.0f, 0.0f) } }
	},
	{ Objects::TRUCK,
	{ Vec2(-60.0f, 0.0f), objetcs.at(Objects::TRUCK),{ Event::COLL_LETHAL_OBJECTS, Vec2(0.0f, 0.0f) } }
	},
	{ Objects::CAR_ORANGE,
	{ Vec2(50.0f, 0.0f), objetcs.at(Objects::CAR_ORANGE),{ Event::COLL_LETHAL_OBJECTS, Vec2(0.0f, 0.0f) } }
	},
	{ Objects::LARGE_TREE,
	{ Vec2(90.0f, 0.0f), objetcs.at(Objects::LARGE_TREE),{ Event::COLL_TREE_TURTLE, Vec2(90.0f, 0.0f) } }
	},
	{ Objects::MEDIUM_TREE,
	{ Vec2(60.0f, 0.0f), objetcs.at(Objects::MEDIUM_TREE),{ Event::COLL_TREE_TURTLE, Vec2(60.0f, 0.0f) } }
	},
	{ Objects::SMALL_TREE,
	{ Vec2(40.0f, 0.0f), objetcs.at(Objects::SMALL_TREE),{ Event::COLL_TREE_TURTLE, Vec2(40.0f, 0.0f) } }
	},
	{ Objects::TWO_ELEMENT_CHAIN,
	{ Vec2(-50.0f, 0.0f), objetcs.at(Objects::TWO_ELEMENT_CHAIN),{ Event::COLL_TREE_TURTLE, Vec2(-50.0f, 0.0f) } }
	},
	{ Objects::THREE_ELEMENT_CHAIN,
	{ Vec2(-50.0f, 0.0f), objetcs.at(Objects::THREE_ELEMENT_CHAIN),{ Event::COLL_TREE_TURTLE, Vec2(-50.0f, 0.0f) } }
	}
};

const vector<TransitionElement> emptyTransitionSet = {};

bool intersects(Rectangle rect1, Rectangle rect2);

#endif UTIL