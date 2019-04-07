#ifndef OPPONENT
#define OPPONENT

#include <vector>

#include "GameObject.h"
#include "Util.h"

class Opponent : public GameObject {
	float livingTime;
	Vec2 homePosition;
	Direction currentDirection;

	bool expired;

protected:
	bool isOutsideOfBorders();
	void setValidMovement(float leftThreshold, float rightThreshold);

public:
	/*
		Erzeugt einen neuen Opponent.
		@param position ist die Position, an der der Opponent platziert wird.
		@param textureRegion ist die texturkoordinate.
		@param textureSet ist eine Menge von Texturkoordinaten, die bei einer Animation verwendet werden.
		@param transitionSet ist die Zustandsübergangsmenge.
	*/
	Opponent(Vec2 position, float speed, const util::Rectangle& textureRegion, map<Direction, util::Rectangle> textureSet, const vector<TransitionElement>& transitionSet);
	~Opponent() {};


	/*
		@param value gibt an, ob die Lebensdauer des Objektes abgelaufen ist.
	*/
	void setExpired(bool value) { this->expired = value; };


	/*
		@return gibt true zurück, wenn die Lebensdauer des Objektes abgelaufen ist.
	*/
	bool isExpired() { return expired; };


	/*
		Lässt das Objekt altern.
		@param dt ist der Wert, um den das Objekt altern soll.
	*/
	void increaseLivingTime(float dt) { this->livingTime += dt; };


	/*
		@return gibt das aktuelle Alter des Objektes zurück.
	*/
	float getLivingTime() { return livingTime; };


	/*
		@param ist die neue Richtung des Objektes.
	*/
	void setDirection(Direction direction) { this->currentDirection = direction; };


	/*
		@return gibt die aktuelle Richtung des Objektes zurück.
	*/
	Direction getDirection() { return currentDirection; };


	/*
		Setzt die neue Heimatposition. Diese wird beim reset eingenommen.
		@param pos ist die neue Heimatposition.
	*/
	void useAsNewHomePosition(Vec2 pos) { this->homePosition = pos; };


	/*
		@return gibt die aktuelle Heimatposition zurück.
	*/
	Vec2 getHomePosition() { return homePosition; };

	// @Override
	virtual util::Rectangle getCriticalHitBox();
};

#endif OPPONENT