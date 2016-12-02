#include "Util.h"

bool intersects(Rectangle rect1, Rectangle rect2) {
	if ((int)rect1.position.x >= (int)(rect2.position.x + rect2.size.x) || 
		(int)rect2.position.x >= (int)(rect1.position.x + rect1.size.x)) {
		return false;
	}

	if ((int)rect1.position.y >= (int)(rect2.position.y + rect2.size.y) || 
		(int)rect2.position.y >= (int)(rect1.position.y + rect1.size.y)) {
		return false;
	}

	return true;
}