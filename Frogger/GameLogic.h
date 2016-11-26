#ifndef GAME_LOGIC
#define GAME_LOGIC

#include <vector>
#include <math.h>

#include "GameObject.h"
#include "Frog.h"
#include "Texture.h"
#include "FontManager.h"
#include "ObjectManager.h"

using namespace std;

class GameLogic {
	bool ready = false;

	const Rectangle riverHitBox = { Vec2(0.0f, OFFSET_Y), Vec2(TILES_X * X_TILE_SIZE, 6 * Y_TILE_SIZE-1) };

	const vector<Rectangle> poolHitBoxes = getPoolHitBoxes();
	const map<int, CollisionStruct> poolCollisionStructMap = {
		{0, { Event::COLL_POOL, poolHitBoxes[0].position } },
		{1, { Event::COLL_POOL, poolHitBoxes[1].position } },
		{2, { Event::COLL_POOL, poolHitBoxes[2].position } },
		{3, { Event::COLL_POOL, poolHitBoxes[3].position } },
		{4, { Event::COLL_POOL, poolHitBoxes[4].position } },
	};

	vector<Pool> pools = {
		{ poolCollisionStructMap.at(0), poolHitBoxes.at(0), false},
		{ poolCollisionStructMap.at(1), poolHitBoxes.at(1), false },
		{ poolCollisionStructMap.at(2), poolHitBoxes.at(2), false },
		{ poolCollisionStructMap.at(3), poolHitBoxes.at(3), false },
		{ poolCollisionStructMap.at(4), poolHitBoxes.at(4), false },
	};

	int score;
	int currentPoolIndex;

	ObjectManager objectManager;
	FontManager fontManager;

	vector<Frog*> frogs;



	vector<Rectangle> getPoolHitBoxes();

	CollisionStruct getExistingCollisionStruct(Frog* frog, GameObject* obj);
	CollisionStruct checkRiverCollision();
	CollisionStruct checkPoolCollision();
	CollisionStruct evaluateCollisions(vector<GameObject*> objs, Frog* frog);

	Frog* getActiveFrog();

	void setupObjects();
	void setupLabels();
	void repeatObjectPosition(GameObject* obj);

	

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
	void gameLoop(const GLfloat dt);

	/*
		Über diese Methode kann der Frosch des Spielers gesteuert werden.
		@param direction gibt die Richtung an, in die sich der Frosch
			   Bewegen soll.
	*/
	void moveFrog(const Direction direction);
};

#endif GAME_LOGIC