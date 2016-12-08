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
	int score;
	int currentPoolIndex;

	const Rectangle riverHitBox = { Vec2(0.0f, OFFSET_Y), Vec2(TILES_X * X_TILE_SIZE, 6 * Y_TILE_SIZE-1) };
	vector<Pool> pools;
	ObjectManager objectManager;
	FontManager fontManager;

	vector<Rectangle> getPoolHitBoxes();

	ObjectInfo checkForCollision(Frog* frog, GameObject* obj);
	ObjectInfo checkForRiverCollision();
	ObjectInfo checkForPoolCollision();
	ObjectInfo evaluateCollisions(vector<GameObject*> objs, Frog* frog);

	void setupObjects();
	void setupLabels();
	void createPools();
	void manageFrogs(Frog* activeFrog, float dt);

public:
	GameLogic();
	~GameLogic();

	void create();

	/*
		�ber diese Methode k�nnen alle Informationen zum Anzeigen
		der Objekte geholt werden.
		@return Gibt ein Drawable zur�ck, das alle n�tige Informationen
				zum Anzeigen der Objekte enth�lt.
	*/
	map<DrawableType, vector<Drawable>> getDrawables();

	/*
		Beim Aufruf dieser Methode werden alle Objekte f�r den n�chsten
		Schritt berechnet. Dies ist die zentrale Stelle, an der alle
		Berechnungen im Model stattfinden.
		@param dt ist die Zeit, die seit dem letzten Aufruf vergangen ist.
	*/
	void gameLoop(const GLfloat dt);

	/*
		�ber diese Methode kann der Frosch des Spielers gesteuert werden.
		@param direction gibt die Richtung an, in die sich der Frosch
			   Bewegen soll.
	*/
	void moveFrog(const Direction direction);
};

#endif GAME_LOGIC