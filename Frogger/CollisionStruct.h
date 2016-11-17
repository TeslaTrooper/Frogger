#ifndef COLLISION_STRUCT
#define COLLISION_STRUCT

#include "Event.h"

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

#endif COLLISION_STRUCT