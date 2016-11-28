#ifndef GAME_OBJECT
#define GAME_OBJECT

#include "Util.h"
#include "StateMachine.h"

using namespace std;

/*
	Das GameObject repräsentiert ein beliebiges Objekt des Spieles. Es wird 
	bestimmt durch seine Position, Größe, Texture, den aktuellen Zustand und dem
	Bewegungsvektor, mit sich das Objekt fortbewegt.
*/
class GameObject {
	
	// Enthält die aktuelle Position des Objektes
	Vec2 position;

	// Enthält die Größe des Objektes (ist nicht Abhängig von der Texture)
	Vec2 size;

	// Steuert den Zustandsablauf eines Objektes
	StateMachine stateMachine;

	// Gibt den Bereich an, aus dem die Textur innerhlb des tilesets stammt
	Rectangle textureRegion;

	// Die Geschwindigkeit, mit der sich das Objekt bewegen kann
	float speed;

	// Enthält Informationen darüber, was eine Kollision mit einem anderen Objekt 
	// für Auswirkungen auf das andere Objekt hat.
	CollisionStruct collisionStruct;

	// Ist das aktuelle Event, das für dieses Objekt eingetreten ist
	CollisionStruct currentEvent;

	// Ist die Zustandsübergangsmenge
	const vector<TransitionElement> transitionSet;

protected:
	// Aus den 2 Vektoren wird der resultierende Vektor gebildet
	Vec2 vectors[2];

	virtual bool targetPositionReached(GLfloat dt);

public:

	/*
		Erzeugt ein neues Objekt mit den gegebenen Parametern.
		@param position gibt die initiale Position des Objektes an.
		@param transitionSet ist die Zustandsübergangsmenge.

	*/
	GameObject(Vec2 position, const vector<TransitionElement>& transitionSet);


	/*
		Erzeugt ein neues Objekt mit den gegebenen Parametern.
		@param textureRegion gibt die Position und Größe der Textur an.
		@param transitionSet ist die Zustandsübergangsmenge.
	*/
	GameObject(Rectangle textureRegion, const vector<TransitionElement>& transitionSet);


	/*
		Erzeugt ein neues Objekt mit den gegebenen Parametern.
		@param position gibt die initiale Position des Objektes an.
		@param size ist die Größe des Objektes.
		@param textureRegion gibt die Position und Größe der Textur an.
		@param transitionSet ist die Zustandsübergangsmenge.
	*/
	GameObject(Vec2 position, Vec2 size, Rectangle textureRegion, const vector<TransitionElement>& transitionSet);


	~GameObject();


	/*
		@returns Gibt die aktuelle Position als des Objektes zurück.
	*/
	Vec2 getPosition() { return position; };


	/*
		@returns Gibt die Größe als des Objektes zurück.
	*/
	Vec2 getSize() { return size; };


	/*
		@returns Gibt die Geschwindigkeit zurück, mit der sich das
				 Objekt fortbewegen kann.
	*/
	float getSpeed() { return speed; };


	/*
		@returns Gibt den aktuellen Zustand, in dem sich das Objekt
				 befindet, zurück.
	*/
	State getState() { return stateMachine.getState(); };


	/*
		@returns Gibt den Bewegungsvektor zurück, mit dem sich das
				 Objekt fortbewegt.
	*/
	Vec2 getCurrentMovement() { return vectors[0].add(vectors[1]); };


	/*
		Diese Methode liefert Informationen darüber, welchen
		Auswirkungen bei einer Kollision das andere Objekt, mit 
		dem Dieses kollidiert, ausgesetzt ist.
		@returns Gibt ein struct zurück, welches die entsprechenden
				 Informationen liefert.
	*/
	CollisionStruct getCollisionStruct() { return collisionStruct; };


	/*
		Löst einen Zustandsübergang aus.
		@param ev ist das Event, mit dem der Zustandsübergang durchgeführt
				  werden soll.
		@return Gibt true zurück, sofern ein neuer Zustand eingenommen wurde.
	*/
	bool doTransition(Event ev);


	/*
		Über diese Funktion können alle nötigen Informationen zum Zeichnen
		des Objektes erhalten werden.
		@return Gibt ein Drawable zurück, das die Informationen enthält.
	*/
	Drawable getDrawable();

	void setPosition(Vec2 position) { this->position = position; };
	void setSpeed(float speed) { this->speed = speed; };
	void setState(State state) { stateMachine.setInitialState(state); };
	void setSize(Vec2 size) { this->size = size; };
	void setCollisionStruct(CollisionStruct collisionStruct) { this->collisionStruct = collisionStruct; };

	Rectangle getTextureRegion() { return this->textureRegion; };
	CollisionStruct getCurrentEvent() { return currentEvent; };

	void setMovement(Vec2 movement);
	void resetMovement();
	void move(GLfloat dt);


	/*
		Registriert ein neues Event.
	*/
	void registerEvent(CollisionStruct currentEvent);
	

	/*
		@returns Gibt das Rechteck des Objektes zurück.
	*/
	Rectangle getCriticalHitBox();


	/*
		Über diese Methode werden alle logischen Prozeduren eines
		Objektes gesteuert.
		@param dt ist die Zeit, die seit dem letzten game loop vergangen ist.
	*/
	virtual void doLogic(GLfloat dt);
};

#endif GAME_OBJECT