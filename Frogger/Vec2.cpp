#include "Vec2.h"

Vec2::Vec2() {
	x = 0.0f;
	y = 0.0f;
}

Vec2::Vec2(float x, float y) {
	this->x = x;
	this->y = y;
}

Vec2 Vec2::add(Vec2 vec) {
	return Vec2(this->x + vec.x, this->y + vec.y);
}

Vec2 Vec2::sub(Vec2 vec) {
	return Vec2(this->x - vec.x, this->y - vec.y);
}

Vec2 Vec2::mul(float scalar) {
	return Vec2(this->x * scalar, this->y * scalar);
}

Vec2 Vec2::norm() {
	return Vec2(this->x / length(), this->y / length());
}

Vec2 Vec2::rotateTo(Vec2 vec, float length) {
	Vec2 res = vec.sub(*this).norm().mul(length);

	return Vec2(res.x, res.y);
}

float Vec2::length() {
	return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

void Vec2::clear() {
	this->x = 0.0f;
	this->y = 0.0f;
}

Vec2::~Vec2() {}