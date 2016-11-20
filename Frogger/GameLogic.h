#ifndef GAME_LOGIC
#define GAME_LOGIC

#include <vector>
#include <math.h>

#include "GameObject.h"
#include "Frog.h"
#include "Texture.h"
#include "FontManager.h"
#include "ObjectManager.h"

class GameLogic {
	int runningFrogs = 1;
	Frog* frog[5];
	std::vector<Texture>* textures;
	GLfloat dt;
	ObjectManager* objectManager;
	FontManager* fontManager;

	const Rectangle riverHitBox = { Vec2(0.0f, OFFSET_Y), Vec2(TILES_X * X_TILE_SIZE, 6 * Y_TILE_SIZE) };
	Rectangle poolHitBoxes[POOLS_COUNT];

	void initPoolHitBoxes();

	bool intersects(Rectangle rect1, Rectangle rect2);

	void repeatObjectPosition(GameObject* obj);

	bool checkCollision(GameObject* obj);
	bool checkRiverCollision();
	int checkPoolCollision();
	Frog* getActiveFrog();

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