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

	void setupObjects();
	void setupLabels();

	int score;

public:
	GameLogic();
	~GameLogic();

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
	void gameLoop(GLfloat dt);

	/*
		Über diese Methode kann der Frosch des Spielers gesteuert werden.
		@param direction gibt die Richtung an, in die sich der Frosch
			   Bewegen soll.
	*/
	void moveFrog(Direction direction);
};

#endif GAME_LOGIC