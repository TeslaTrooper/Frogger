#ifndef VEC2
#define VEC2

#include <math.h>

class Vec2 {

public:
	float x;
	float y;

	Vec2();
	Vec2(float x, float y);

	~Vec2();

	Vec2 add(Vec2 vec);
	Vec2 sub(Vec2 vec);
	Vec2 mul(float scalar);
	void clear();

	// this ist startpunkt; vec2 ist zielpunkt; length ist die länge, die der vektor haben soll
	Vec2 rotateTo(Vec2 vec, float length);
	Vec2 norm();

	float length();

	bool operator==(const Vec2& vec) {
		return vec.x == x && vec.y == y;
	};

};

#endif VEC2