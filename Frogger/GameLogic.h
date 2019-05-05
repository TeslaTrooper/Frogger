#ifndef GAME_LOGIC
#define GAME_LOGIC

#include <vector>
#include <math.h>
#include <iostream>

#include "GameObject.h"
#include "Frog.h"
#include "ObjectManager.h"
#include "UIManager.h"
#include "LevelManager.h"
#include "PhysicsEngine.h"
#include "GameStats.h"
#include "SoundPlayer.h"
#include "Game.h"

using namespace std;
using namespace util;

class GameLogic : public Game {

	GameStats stats;

	const util::Rectangle riverHitBox = { Vec2(0.0f, OFFSET_Y), Vec2(TILES_X * X_TILE_SIZE, 6 * Y_TILE_SIZE - 1) };
	util::Rectangle insectHitBox = { Vec2(0.0f, 0.0f), Vec2(X_TILE_SIZE, Y_TILE_SIZE) };

	vector<Pool> pools;
	ObjectManager objectManager;
	UIManager uiManager;
	LevelManager levelManager;
	PhysicsEngine physicsEngine;
	SoundPlayer soundPlayer;

	vector<util::Rectangle> getPoolHitBoxes();

	vector<GameObject*>* currentCollisions;

	ObjectInfo checkForCollision(Frog* frog, GameObject* obj);
	ObjectInfo checkForRiverCollision();
	ObjectInfo checkForPoolCollision();
	ObjectInfo checkForInsectCollision();
	ObjectInfo evaluateCollisions(vector<GameObject*> objs, Frog* frog);

	void init();
	void setupObjects();
	void setupLabels() {};
	void createPools();
	void manageFrogs(Frog* activeFrog, float dt);
	void updateUIElements(float dt);
	void increaseCollectedScoreBy(Event ev);
	void reset(bool resetAll);
	void gameOver(Frog* activeFrog);
	void updateGameRules(Frog* activeFrog, float dt);
	void updateLevelDifficulty();
	void generateOpponents();

public:
	GameLogic();
	~GameLogic();

	map<DrawableType, vector<Drawable>> getDrawables() override;
	void update(const float dt) override;
	void moveFrog(const Direction direction) override;
	void restart() override;
	void resolveCollision(Entity* e1, Entity* e2, const Vec2& location) const override;
};

#endif GAME_LOGIC