#ifndef GAME_OBJECT
#define GAME_OBJECT

#include "Util.h"
#include "StateMachine.h"

using namespace std;

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
	Rectangle textureRegion;

	// Die Geschwindigkeit, mit der sich das Objekt bewegen kann
	float speed;


	ObjectInfo objectInfo;
	ObjectInfo interactingObjectInfo;


	// Ist die Zustands�bergangsmenge
	const vector<TransitionElement> transitionSet;

protected:
	// Aus den 2 Vektoren wird der resultierende Vektor gebildet
	Vec2 vectors[2];

	virtual bool targetPositionReached(GLfloat dt);

public:

	/*
		Erzeugt ein neues Objekt mit den gegebenen Parametern.
		@param position gibt die initiale Position des Objektes an.
		@param transitionSet ist die Zustands�bergangsmenge.

	*/
	GameObject(Vec2 position, const vector<TransitionElement>& transitionSet);


	/*
		Erzeugt ein neues Objekt mit den gegebenen Parametern.
		@param textureRegion gibt die Position und Gr��e der Textur an.
		@param transitionSet ist die Zustands�bergangsmenge.
	*/
	GameObject(Rectangle textureRegion, const vector<TransitionElement>& transitionSet);


	/*
		Erzeugt ein neues Objekt mit den gegebenen Parametern.
		@param position gibt die initiale Position des Objektes an.
		@param size ist die Gr��e des Objektes.
		@param textureRegion gibt die Position und Gr��e der Textur an.
		@param transitionSet ist die Zustands�bergangsmenge.
	*/
	GameObject(Vec2 position, Vec2 size, Rectangle textureRegion, const vector<TransitionElement>& transitionSet);

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
		Diese Methode liefert Informationen dar�ber, welchen
		Auswirkungen bei einer Kollision das andere Objekt, mit 
		dem Dieses kollidiert, ausgesetzt ist.
		@returns Gibt ein struct zur�ck, welches die entsprechenden
				 Informationen liefert.
	*/


	/*
		L�st einen Zustands�bergang aus.
		@param ev ist das Event, mit dem der Zustands�bergang durchgef�hrt
				  werden soll.
		@return Gibt true zur�ck, sofern ein neuer Zustand eingenommen wurde.
	*/
	bool doTransition(Event ev);

	void gotoPreviousState();


	/*
		�ber diese Funktion k�nnen alle n�tigen Informationen zum Zeichnen
		des Objektes erhalten werden.
		@return Gibt ein Drawable zur�ck, das die Informationen enth�lt.
	*/
	Drawable getDrawable();

	void setPosition(Vec2 position) { this->position = position; };
	void setSpeed(float speed) { this->speed = speed; };
	void setState(State state) { stateMachine.setInitialState(state); };
	void setSize(Vec2 size) { this->size = size; };
	void setCollisionInfo(CollisionInfo info) { this->objectInfo.collisionInfo = info; };
	void setTextureRegion(Rectangle textureRegion) { this->textureRegion = textureRegion; };

	Rectangle getTextureRegion() { return this->textureRegion; };

	ObjectInfo getCurrentInteraction() { return interactingObjectInfo; };
	ObjectInfo getObjectInfo() { return { textureRegion, getCriticalHitBox(), getCurrentMovement(), objectInfo.collisionInfo }; };
	CollisionInfo getCollisionInfo() { return objectInfo.collisionInfo; };

	void setMovement(Vec2 movement);
	void resetMovement();
	void move(GLfloat dt);

	/*
		Registriert ein neues Event.
	*/
	void registerInteraction(ObjectInfo info);
	

	/*
		@returns Gibt das Rechteck des Objektes zur�ck.
	*/
	Rectangle getCriticalHitBox();


	/*
		�ber diese Methode werden alle logischen Prozeduren eines
		Objektes gesteuert.
		@param dt ist die Zeit, die seit dem letzten game loop vergangen ist.
	*/
	virtual void doLogic(GLfloat dt);
};

#endif GAME_OBJECT