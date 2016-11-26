#ifndef MAT3
#define MAT3

#include <array>
#include "Vec2.h"

using namespace std;

class Mat3 {
	array<array<float, 3>, 3> elements;

public:
	Mat3();
	Mat3(array<array<float, 3>, 3> elements);

	Mat3 translate(Vec2 vec);
	Mat3 scale(Vec2 vec);

	static const float* ptr(Mat3 mat);

	~Mat3();
};

#endif MAT3