#ifndef TREE
#define TREE

#include "GameObject.h"
#include "TreeType.h"

class Tree : public GameObject {

	void initTree(vec2 movement, Texture* texture);

public:
	Tree(TreeType type, vec2 position, vec3 color);
	~Tree();

	void doLogic(GLfloat dt);
	Rectangle getCriticalHitBox();
};

#endif TREE