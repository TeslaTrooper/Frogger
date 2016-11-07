#ifndef GAME_LOGIC
#define GAME_LOGIC

#include <vector>
#include <math.h>
#include "GameObject.h"
#include "Frog.h"
#include "Car.h"
#include "Texture.h"
#include "FontManager.h"
#include "ObjectManager.h"

class GameLogic {
	Frog* frog;
	std::vector<Texture>* textures;
	GLfloat dt;
	ObjectManager* objectManager;
	FontManager* fontManager;

	void repeatObjectPosition(GameObject* obj);

	bool checkCollision(GameObject* obj);
	bool isFrog(GameObject* obj);

	int score;

public:
	GameLogic();
	~GameLogic();

	std::vector<GameObject*> getObjects();
	void doLogic(GLfloat dt);
	void moveFrog(Direction direction);
	void drawLabels(Renderer* renderer);
};

#endif GAME_LOGIC