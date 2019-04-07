#ifndef GAME_OBJECT
#define GAME_OBJECT

#include "Util.h"
#include "StateMachine.h"
#include "Entity.h"

using namespace std;
using namespace util;

/*
	Das GameObject repräsentiert ein beliebiges Objekt des Spieles. Es wird
	bestimmt durch seine Position, Größe, Texture, den aktuellen Zustand und dem
	Bewegungsvektor, mit sich das Objekt fortbewegt.
*/
class GameObject : public Entity {

	// Enthält die Größe des Objektes (ist nicht Abhängig von der Texture)
	Vec2 size;

	// Steuert den Zustandsablauf eines Objektes
	StateMachine stateMachine;

	// Gibt den Bereich an, aus dem die Textur innerhlb des tilesets stammt
	util::Rectangle textureRegion;


	ObjectInfo objectInfo;
	ObjectInfo interactingObjectInfo;


	// Ist die Zustandsübergangsmenge
	const vector<TransitionElement> transitionSet;

	map<Direction, util::Rectangle> textureSet;

protected:
	virtual bool targetPositionReached(float dt);

	util::Rectangle getTextureRegionFor(Direction direction) { return this->textureSet.at(direction); };
	void setTextureRegion(util::Rectangle textureRegion) { this->textureRegion = textureRegion; };

public:

	/*
		Erzeugt ein neues Objekt mit den gegebenen Parametern.
		@param position gibt die initiale Position des Objektes an.
		@param transitionSet ist die Zustandsübergangsmenge.

	*/
	GameObject(Vec2 position, const vector<TransitionElement>& transitionSet);


	/*
		Erzeugt ein neues Objekt mit den gegebenen Parametern.
		@param position gibt die initiale Position des Objektes an.
		@param size ist die Größe des Objektes.
		@param textureRegion gibt die Position und Größe der Textur an.
		@param transitionSet ist die Zustandsübergangsmenge.
	*/
	GameObject(Vec2 position, float speed, util::Rectangle textureRegion, map<Direction, util::Rectangle> textureSet, const vector<TransitionElement>& transitionSet);


	/*
		Erzeugt ein neues Objekt mit den gegebenen Parametern.
		@param objectInfo enthält vordefinierte Werte, die dieses GameObject annimmt.
		@param transitionSet ist die Zustandsübergangsmenge.
	*/
	GameObject(ObjectInfo objectInfo, const vector<TransitionElement>& transitionSet);


	~GameObject();


	/*
		@returns Gibt die Größe als des Objektes zurück.
	*/
	Vec2 getSize() { return size; };


	/*
		@returns Gibt den aktuellen Zustand, in dem sich das Objekt
				 befindet, zurück.
	*/
	State getState() { return stateMachine.getState(); };


	/*
		Löst einen Zustandsübergang aus.
		@param ev ist das Event, mit dem der Zustandsübergang durchgeführt
				  werden soll.
		@return Gibt true zurück, sofern ein neuer Zustand eingenommen wurde.
	*/
	bool doTransition(Event ev);


	/*
		Versetzt den Zustandsautomaten dieses Objektes in den vorherigen Zustand.
	*/
	void gotoPreviousState();

	Drawable getDrawable();


	/*
		Setzt den intialen Zustand des Objektes.
		@param state ist der initiale Zustand, der für den Zustandsautomaten verwenden werden soll.
	*/
	void setState(State state) {
		if (state == State::DIEING) {
			printf("kk");
		}

		stateMachine.setInitialState(state);
	};


	/*
		Setzt die Größe des Objektes.
		@param size ist die neue Größe des Objektes.
	*/
	void setSize(Vec2 size) { this->size = size; };


	/*
		Setzt die Information für eine Kollision.
		@param info ist das Collisioninfo Struct, das das andere Objekt, mit dem dieses kolliedert ist, beschreibt.
	*/
	void setCollisionInfo(CollisionInfo info) { this->objectInfo.collisionInfo = info; };


	/*
		@return gibt die Texturkoordinaten zurück.
	*/
	util::Rectangle getTextureRegion() { return this->textureRegion; };


	/*
		@return gibt das ObjectInfo Struct des Objektes zurück, mit dem dieses aktuell kollidiert.
	*/
	ObjectInfo getCurrentInteraction() { return interactingObjectInfo; };


	/*
		Erzeugt aus den aktuellen Informationen dieses Objektes ein ObjectInfo Struct.
		@return gibt das ObjectInfo Struct zurück.
	*/
	ObjectInfo getObjectInfo() { return { textureRegion, getCriticalHitBox(), getMovement(), objectInfo.collisionInfo }; };


	/*
		Erzeugt aus den aktuellen Informationen dieses Objektes ein CollisionInfo Struct.
		@return gibt das CollisionInfo Struct zurück.
	*/
	CollisionInfo getCollisionInfo() { return objectInfo.collisionInfo; };

	/*
		Registriert ein neues Event.
		@param info ist die Information des anderen Objektes, für das ein Event registriert wird.
	*/
	void registerInteraction(ObjectInfo info);


	/*
		@returns Gibt das Rechteck des Objektes zurück.
	*/
	virtual util::Rectangle getCriticalHitBox();


	/*
		Über diese Methode werden alle logischen Prozeduren eines
		Objektes gesteuert.
		@param dt ist die Zeit, die seit dem letzten game loop vergangen ist.
	*/
	virtual void doLogic(float dt);

	void setAcceleration(float value) override;

	bool canCollide() const override;
	bool canCollideWith(const Entity* const e) const override;
	void updateTransformation() override;
	VertexData getVertexData() const override;
	IndexData getTriangulatedIndexData() const override;
};

#endif GAME_OBJECT