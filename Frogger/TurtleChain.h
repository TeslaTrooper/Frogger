#ifndef TURTLE_CHAIN
#define TURTLE_CHAIN

#include "GameObject.h"
#include "ChainType.h"

class TurtleChain : public GameObject {

	void initChain(glm::vec2 movement, Texture* texture);

public:
	TurtleChain(ChainType chainType, glm::vec2 position, glm::vec3 color);
	~TurtleChain();

	void doLogic(GLfloat dt);
	Rectangle getCriticalHitBox();
};

#endif TURTLE_CHAIN