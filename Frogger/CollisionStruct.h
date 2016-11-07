#ifndef COLLISION_STRUCT
#define COLLISION_STRUCT

#include "CollisionEffect.h"
#include <glm/glm.hpp>
#include "Event.h"

struct CollisionStruct {
	Event effect;
	glm::vec2 movement;
};

#endif COLLISION_STRUCT