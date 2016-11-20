#ifndef DIRECTION
#define DIRECTION

#include <map>

#include "Constants.h"
#include "Vec2.h"

enum Direction {
	LEFT,
	UP,
	RIGHT,
	DOWN,
	NONE
};

const std::map<Direction, Vec2> directions = {
	{ Direction::LEFT, Vec2(-FROG_SPEED, 0.0f) },
	{ Direction::UP, Vec2(0.0f, -FROG_SPEED) },
	{ Direction::RIGHT, Vec2(FROG_SPEED, 0.0f) },
	{ Direction::DOWN, Vec2(0.0f, FROG_SPEED) }
};

#endif DIRECTION