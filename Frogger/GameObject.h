#ifndef GAME_OBJECT
#define GAME_OBJECT

#include "Direction.h"
#include "State.h"
#include "CollisionStruct.h"
#include "Objects.h"
#include "Structs.h"
#include "Constants.h"
#include "Drawable.h"

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

	// Die Textur, die für das Zeichnen des Objektes verwendet wird
	Texture* texture;

	// Die Geschwindigkeit, mit der sich das Objekt bewegen kann
	float speed;

	// Der aktuelle Zustand des Objektes
	State state;

	// Stellt den aktuellen Bewegungsvektor dar
	Vec2 movement;

	// Enthält Informationen darüber, was eine Kollision mit einem anderen Objekt 
	// für Auswirkungen auf das andere Objekt hat.
	CollisionStruct collisionStruct;

public:

	struct Initializer {
		Vec2 movement;
		Texture* texture;
		CollisionStruct collisionStruct;
	};

	/*
		Erzeugt ein neues Objekt mit den gegebenen Parametern.
		@param position gibt die initiale Position des Objektes an.
		@param color ist die Farbe, die zum Zeichnen verwendet werden soll.
	*/
	GameObject(Vec2 position);

	GameObject(Texture* texture);

	/*
		Erzeugt ein neues Objekt mit den gegebenen Parametern.
		@param position gibt die initiale Position des Objektes an.
		@param color ist die Farbe, die zum Zeichnen verwendet werden soll.
		@param texture ist die Textur, mit der das Objekt gezeichnet werden soll.
	*/
	GameObject(Vec2 position, Texture* texture);

	/*
		Erzeugt ein neues Objekt mit den gegebenen Parametern.
		@param position gibt die initiale Position des Objektes an.
		@param size ist die Größe des Objektes.
		@param color ist die Farbe, die zum Zeichnen verwendet werden soll.
		@param texture ist die Textur, mit der das Objekt gezeichnet werden soll.
	*/
	GameObject(Vec2 position, Vec2 size, Texture* texture);
	
	

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
		@returns Gibt die Texture des Objektes zurück.
	*/
	Texture* getTexture() { return texture; };

	/*
		@returns Gibt die Geschwindigkeit zurück, mit der sich das
				 Objekt fortbewegen kann.
	*/
	float getSpeed() { return speed; };

	/*
		@returns Gibt den aktuellen Zustand, in dem sich das Objekt
				 befindet, zurück.
	*/
	State getState() { return state; };

	/*
		@returns Gibt den Bewegungsvektor zurück, mit dem sich das
				 Objekt fortbewegt.
	*/
	Vec2 getCurrentMovement() { return movement; };

	/*
		Diese Methode liefert Informationen darüber, welchen
		Auswirkungen bei einer Kollision das andere Objekt, mit 
		dem Dieses kollidiert, ausgesetzt ist.
		@returns Gibt ein struct zurück, welches die entsprechenden
				 Informationen liefert.
	*/
	CollisionStruct getCollisionStruct() { return collisionStruct; };

	Drawable getDrawable();

	void setPosition(Vec2 position) { this->position = position; };
	void setSpeed(float speed) { this->speed = speed; };
	void setState(State state) { this->state = state; };
	void setMovement(Vec2 movement) { this->movement = movement; };
	void move(GLfloat dt);
	void setTexture(Texture* texture) { this->texture = texture; };
	void setSize(Vec2 size) { this->size = size; };
	void setCollisionStruct(CollisionStruct collisionStruct) { this->collisionStruct = collisionStruct; };
	void resetMovement() { this->movement = Vec2(0.0f, 0.0f); };

	/*
		@returns Gibt das Rechteck des Objektes zurück.
	*/
	Rectangle getCriticalHitBox();

	/*
		Über diese Methode werden alle logischen Prozeduren eines
		Objektes gesteuert.
		@param dt ist die Zeit, die seit dem letzten game loop vergangen ist.
	*/
	void doLogic(GLfloat dt);
};

#endif GAME_OBJECT