#ifndef GAME
#define GAME

#include <InternalLogic.h>
#include <map>
#include <PhysicsEngine.h>

#include "Util.h"

using namespace util;

struct Game : public InternalLogic, CollisionCallback {

	/*
		�ber diese Methode k�nnen alle Informationen zum Anzeigen
		der Objekte geholt werden.
		@return Gibt ein Drawable zur�ck, das alle n�tige Informationen
				zum Anzeigen der Objekte enth�lt.
	*/
	virtual map<DrawableType, vector<Drawable>> getDrawables() = 0;


	/*
		�ber diese Methode kann der Frosch des Spielers gesteuert werden.
		@param direction gibt die Richtung an, in die sich der Frosch
			   Bewegen soll.
	*/
	virtual void moveFrog(const Direction direction) = 0;


	/*
		Setzt alle Felder zur�ck und startet das Spiel neu.
	*/
	virtual void restart() = 0;

};

#endif GAME