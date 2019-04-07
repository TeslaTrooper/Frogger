#include "Util.h"

bool intersects(util::Rectangle rect1, util::Rectangle rect2) {
	int delta = 20;
	if ((int) rect1.position.x + delta >= (int) (rect2.position.x + delta + rect2.size.x - delta) ||
		(int) rect2.position.x + delta >= (int) (rect1.position.x + delta + rect1.size.x - delta)) {
		return false;
	}

	if ((int) rect1.position.y + delta >= (int) (rect2.position.y + delta + rect2.size.y - delta) ||
		(int) rect2.position.y + delta >= (int) (rect1.position.y + delta + rect1.size.y - delta)) {
		return false;
	}

	return true;
}

int randomNumber(int min, int max) {
	return rand() % (max - min + 1) + min;
}

bool random(int probability) {
	return randomNumber(0, 100) < probability;
}