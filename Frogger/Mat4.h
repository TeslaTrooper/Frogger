#ifndef MAT4
#define MAT4

#include <array>
#include "Vec2.h"

using namespace std;

class Mat4 {
	array<array<float, 4>, 4> elements;

public:
	Mat4();
	Mat4(array<array<float, 4>, 4> elements);

	Mat4 translate(Vec2 vec);
	Mat4 scale(Vec2 vec);

	static Mat4 ortho(float left, float right, float bottom, float top, float zNear, float zFar);
	static const float* ptr(Mat4 mat);

	~Mat4();
};

#endif MAT4