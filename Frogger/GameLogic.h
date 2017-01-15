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

using namespace std;
using namespace util;

class GameLogic {
	int overAllScore;
	int collectedScore;
	int lastRow;
	int currentPoolIndex;
	float time;
	int remainingTries;
	bool isGameOver;
	float remainingTimeLabelDuration;
	float currentLevelLabelDuration;
	int currentLevel;
	float opponentCreationCounter;
	float insectCounter;

	const Rectangle riverHitBox = { Vec2(0.0f, OFFSET_Y), Vec2(TILES_X * X_TILE_SIZE, 6 * Y_TILE_SIZE-1) };
	Rectangle insectHitBox = { Vec2(0.0f, 0.0f), Vec2(X_TILE_SIZE, Y_TILE_SIZE) };

	vector<Pool> pools;
	ObjectManager objectManager;
	UIManager uiManager;
	LevelManager levelManager;

	vector<Rectangle> getPoolHitBoxes();

	ObjectInfo checkForCollision(Frog* frog, GameObject* obj);
	ObjectInfo checkForRiverCollision();
	ObjectInfo checkForPoolCollision();
	ObjectInfo checkForInsectCollision();
	ObjectInfo evaluateCollisions(vector<GameObject*> objs, Frog* frog);

	void init();
	void setupObjects();
	void setupLabels();
	void createPools();
	void manageFrogs(Frog* activeFrog, float dt);
	void updateUIElements(float dt);
	void increaseCollectedScoreBy(Event ev);
	void reset(bool resetAll);
	void gameOver(Frog* activeFrog);
	void updateGameRules(Frog* activeFrog, float dt);
	void updateLevelDifficulty();
	void generateOpponents();
	void setupUIElement(string identifier, string text, bool withlabel, float scale, UIManager::Alignment alignment);

public:
	GameLogic();
	~GameLogic();

	void create();


	/*
		Über diese Methode können alle Informationen zum Anzeigen
		der Objekte geholt werden.
		@return Gibt ein Drawable zurück, das alle nötige Informationen
				zum Anzeigen der Objekte enthält.
	*/
	map<DrawableType, vector<Drawable>> getDrawables();


	/*
		Beim Aufruf dieser Methode werden alle Objekte für den nächsten
		Schritt berechnet. Dies ist die zentrale Stelle, an der alle
		Berechnungen im Model stattfinden.
		@param dt ist die Zeit, die seit dem letzten Aufruf vergangen ist.
	*/
	void gameLoop(const float dt);


	/*
		Über diese Methode kann der Frosch des Spielers gesteuert werden.
		@param direction gibt die Richtung an, in die sich der Frosch
			   Bewegen soll.
	*/
	void moveFrog(const Direction direction);


	void restart();
};

#endif GAME_LOGIC