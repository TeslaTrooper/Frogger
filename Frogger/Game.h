#ifndef GAME
#define GAME

#include <InternalLogic.h>
#include <map>
#include <PhysicsEngine.h>

#include "Util.h"

using namespace util;

struct Game : public InternalLogic, CollisionCallback {

	/*
		Über diese Methode können alle Informationen zum Anzeigen
		der Objekte geholt werden.
		@return Gibt ein Drawable zurück, das alle nötige Informationen
				zum Anzeigen der Objekte enthält.
	*/
	virtual map<DrawableType, vector<Drawable>> getDrawables() = 0;


	/*
		Über diese Methode kann der Frosch des Spielers gesteuert werden.
		@param direction gibt die Richtung an, in die sich der Frosch
			   Bewegen soll.
	*/
	virtual void moveFrog(const Direction direction) = 0;


	/*
		Setzt alle Felder zurück und startet das Spiel neu.
	*/
	virtual void restart() = 0;

};

#endif GAME