#ifndef GAME_OBJECT
#define GAME_OBJECT

#include "Util.h"
#include "StateMachine.h"

using namespace std;
using namespace util;

/*
	Das GameObject repr�sentiert ein beliebiges Objekt des Spieles. Es wird 
	bestimmt durch seine Position, Gr��e, Texture, den aktuellen Zustand und dem
	Bewegungsvektor, mit sich das Objekt fortbewegt.
*/
class GameObject {
	
	// Enth�lt die aktuelle Position des Objektes
	Vec2 position;

	// Enth�lt die Gr��e des Objektes (ist nicht Abh�ngig von der Texture)
	Vec2 size;

	// Steuert den Zustandsablauf eines Objektes
	StateMachine stateMachine;

	// Gibt den Bereich an, aus dem die Textur innerhlb des tilesets stammt
	util::Rectangle textureRegion;

	// Die Geschwindigkeit, mit der sich das Objekt bewegen kann
	float speed;


	ObjectInfo objectInfo;
	ObjectInfo interactingObjectInfo;


	// Ist die Zustands�bergangsmenge
	const vector<TransitionElement> transitionSet;

	map<Direction, util::Rectangle> textureSet;

protected:
	// Aus den 2 Vektoren wird der resultierende Vektor gebildet
	Vec2 vectors[2];

	virtual bool targetPositionReached(float dt);

	util::Rectangle getTextureRegionFor(Direction direction) { return this->textureSet.at(direction); };
	void setTextureRegion(util::Rectangle textureRegion) { this->textureRegion = textureRegion; };

public:

	/*
		Erzeugt ein neues Objekt mit den gegebenen Parametern.
		@param position gibt die initiale Position des Objektes an.
		@param transitionSet ist die Zustands�bergangsmenge.

	*/
	GameObject(Vec2 position, const vector<TransitionElement>& transitionSet);


	/*
		Erzeugt ein neues Objekt mit den gegebenen Parametern.
		@param position gibt die initiale Position des Objektes an.
		@param size ist die Gr��e des Objektes.
		@param textureRegion gibt die Position und Gr��e der Textur an.
		@param transitionSet ist die Zustands�bergangsmenge.
	*/
	GameObject(Vec2 position, util::Rectangle textureRegion, map<Direction, util::Rectangle> textureSet, const vector<TransitionElement>& transitionSet);


	/*
		Erzeugt ein neues Objekt mit den gegebenen Parametern.
		@param objectInfo enth�lt vordefinierte Werte, die dieses GameObject annimmt.
		@param transitionSet ist die Zustands�bergangsmenge.
	*/
	GameObject(ObjectInfo objectInfo, const vector<TransitionElement>& transitionSet);


	~GameObject();


	/*
		@returns Gibt die aktuelle Position als des Objektes zur�ck.
	*/
	Vec2 getPosition() { return position; };


	/*
		@returns Gibt die Gr��e als des Objektes zur�ck.
	*/
	Vec2 getSize() { return size; };


	/*
		@returns Gibt die Geschwindigkeit zur�ck, mit der sich das
				 Objekt fortbewegen kann.
	*/
	float getSpeed() { return speed; };


	/*
		@returns Gibt den aktuellen Zustand, in dem sich das Objekt
				 befindet, zur�ck.
	*/
	State getState() { return stateMachine.getState(); };


	/*
		@returns Gibt den Bewegungsvektor zur�ck, mit dem sich das
				 Objekt fortbewegt.
	*/
	Vec2 getCurrentMovement() { return vectors[0].add(vectors[1]); };


	/*
		L�st einen Zustands�bergang aus.
		@param ev ist das Event, mit dem der Zustands�bergang durchgef�hrt
				  werden soll.
		@return Gibt true zur�ck, sofern ein neuer Zustand eingenommen wurde.
	*/
	bool doTransition(Event ev);


	/*
		Versetzt den Zustandsautomaten dieses Objektes in den vorherigen Zustand.
	*/
	void gotoPreviousState();


	/*
		�ber diese Funktion k�nnen alle n�tigen Informationen zum Zeichnen
		des Objektes erhalten werden.
		@return Gibt ein Drawable zur�ck, das die Informationen enth�lt.
	*/
	Drawable getDrawable();


	/*
		Setzt die Position des Objektes.
		@param position ist die neue Position.
	*/
	void setPosition(Vec2 position) { this->position = position; };


	/*
		Setzt die Geschwindigkeit des Objektes.
		@param speed ist die neue Geschwindigkeit.
	*/
	void setSpeed(float speed) { this->speed = speed; };


	/*
		Setzt den intialen Zustand des Objektes.
		@param state ist der initiale Zustand, der f�r den Zustandsautomaten verwenden werden soll.
	*/
	void setState(State state) { stateMachine.setInitialState(state); };


	/*
		Setzt die Gr��e des Objektes.
		@param size ist die neue Gr��e des Objektes.
	*/
	void setSize(Vec2 size) { this->size = size; };


	/*
		Setzt die Information f�r eine Kollision.
		@param info ist das Collisioninfo Struct, das das andere Objekt, mit dem dieses kolliedert ist, beschreibt.
	*/
	void setCollisionInfo(CollisionInfo info) { this->objectInfo.collisionInfo = info; };


	/*
		@return gibt die Texturkoordinaten zur�ck.
	*/
	util::Rectangle getTextureRegion() { return this->textureRegion; };
	

	/*
		@return gibt das ObjectInfo Struct des Objektes zur�ck, mit dem dieses aktuell kollidiert.
	*/
	ObjectInfo getCurrentInteraction() { return interactingObjectInfo; };


	/*
		Erzeugt aus den aktuellen Informationen dieses Objektes ein ObjectInfo Struct.
		@return gibt das ObjectInfo Struct zur�ck.
	*/
	ObjectInfo getObjectInfo() { return { textureRegion, getCriticalHitBox(), getCurrentMovement(), objectInfo.collisionInfo }; };


	/*
		Erzeugt aus den aktuellen Informationen dieses Objektes ein CollisionInfo Struct.
		@return gibt das CollisionInfo Struct zur�ck.
	*/
	CollisionInfo getCollisionInfo() { return objectInfo.collisionInfo; };


	/*
		@param ist der neue Bewegungsvektor.
	*/
	void setMovement(Vec2 movement);


	/*
		Stopt die Bewegung des Objektes.
	*/
	void resetMovement();


	/*
		L�sst das Objekt in abh�ngigkeit der Zeit bewegen.
		@param dt ist die Zeit, die vergangen ist.
	*/
	void move(float dt);

	/*
		Registriert ein neues Event.
		@param info ist die Information des anderen Objektes, f�r das ein Event registriert wird.
	*/
	void registerInteraction(ObjectInfo info);
	

	/*
		@returns Gibt das Rechteck des Objektes zur�ck.
	*/
	virtual util::Rectangle getCriticalHitBox();


	/*
		�ber diese Methode werden alle logischen Prozeduren eines
		Objektes gesteuert.
		@param dt ist die Zeit, die seit dem letzten game loop vergangen ist.
	*/
	virtual void doLogic(float dt);
};

#endif GAME_OBJECT