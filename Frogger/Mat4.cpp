#include "Mat4.h"

Mat4 Mat4::ortho(float left, float right, float bottom, float top, float zNear, float zFar) {
	Mat4 mat = Mat4();

	mat.elements.at(0).at(0) = 2.0f / (right - left);
	mat.elements.at(1).at(1) = 2.0f / (top - bottom);
	mat.elements.at(3).at(0) = - (right + left) / (right - left);
	mat.elements.at(3).at(1) = - (top + bottom) / (top - bottom);

	mat.elements.at(2).at(2) = - 2.0f / (zFar - zNear);
	mat.elements.at(3).at(2) = - (zFar + zNear) / (zFar - zNear);

	return mat;
}

const float* Mat4::ptr(Mat4 mat) {
	return &(mat.elements.at(0).at(0));
}

Mat4::Mat4() {
	elements.at(0) = { 1.0f, 0.0f, 0.0f, 0.0f };
	elements.at(1) = { 0.0f, 1.0f, 0.0f, 0.0f };
	elements.at(2) = { 0.0f, 0.0f, 1.0f, 0.0f };
	elements.at(3) = { 0.0f, 0.0f, 0.0f, 1.0f };
}

Mat4::Mat4(array<array<float, 4>, 4> elements) {
	this->elements = elements;
}

Mat4 Mat4::translate(Vec2 vec) {
	elements.at(3).at(0) = vec.x;
	elements.at(3).at(1) = vec.y;
	elements.at(3).at(2) = 0.0f;
	elements.at(3).at(3) = 1.0f;

	return *this;
}

Mat4 Mat4::scale(Vec2 vec) {
	elements.at(0).at(0) *= vec.x;
	elements.at(1).at(1) *= vec.y;
	elements.at(2).at(2) *= 1.0f;
	elements.at(3).at(3) *= 1.0f;

	return *this;
}

Mat4::~Mat4() {}

