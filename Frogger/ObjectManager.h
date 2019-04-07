#ifndef OBJECT_MANAGER
#define OBJECT_MANAGER

#include <vector>
#include <map>
#include <algorithm>

#include "Frog.h"
#include "FemaleFrog.h"
#include "CrocodileHead.h"
#include "CrocodileBody.h"
#include "Snake.h"
#include "Util.h"
#include "Turtle.h"

using namespace std;
using namespace util;

class ObjectManager {

protected:
	typedef map<int, vector<GameObject*>*>::iterator it_type;

	map<int, vector<GameObject*>*>* rowObjMap;
	vector<Frog*> frogs;
	vector<OpponentInfo> waitingOpponents;

	OpponentInfo createWaitingOpponent(const ObjectInfo& objInfo);

	int fromYToRow(float y);

	OpponentInfo getNextOpponentInfo(const ObjectInfo& objInfo);
	Opponent* initOpponentWithObjectInfo(Opponent* opponent, const ObjectInfo& objInfo);
	Opponent* initOpponent(Opponent* opponent, float x);

public:
	ObjectManager();
	~ObjectManager();

	/*
		Erzeugt ein neues GameObject.
		@param row ist die Zeile auf dem Spielfeld, in der das Objekt positioniert werden soll.
		@param objType gibt an, was für ein Objekt erzeugt werden soll.
		@param count gibt die Anzahl der zu erzeugenden Objekten an.
		@param space gibt den Abstand zwischen den Objekten an.
		@param startX gibt den x Startwert an, ab dem die Objekte mit dem gegebenen
					  Abstand und der Anazhl positioniert werden.
	*/
	void createObject(int row, Objects objType, int count, int space, int startX);

	void createStaticObject(int row, Objects objType, int count, int space, int startX);


	/*
		Erzeugt einen neuen Frosch.
	*/
	void createFrog();


	/*
		Erzeugt einen neuen Opponent.
		@param opponentInfo enthält alle benötigten Werte.
	*/
	void createOpponent(OpponentInfo opponentInfo);


	/*
		Erzeug eine neue Schildkröte.
		@param row, gibt die Reihe an, in der die Schildkröte platziert werden soll.
		@param objType gibt an, ob es sich um eine 2er, oder 3er Kette handelt.
		@param count gibt an, wie viele Instanzen in dieser Reihe erzeugt werden sollen.
		@param gibt den Zwischenabstand der Instanzen an.
		@param startX gibt den Startwert der Positionierung an.
	*/
	void createTurtle(int row, Objects objType, int count, int space, int startX);


	/*
		Regisiert eine neue Interaktion auf dem FemaleFrog Objekt.
		@param objInfo stellt die Interkation dar.
	*/
	void registerInteractionOnFemaleFrog(const ObjectInfo& objInfo);


	/*
		Diese Funktion liefert die Koordinaten für eine bestimmte Zeile zurück.
		@param centered gibt an, ob die x Koordinate in der Zeile zentriert werden soll.
		@return Gibt einen Vektor zurück, der die Koordinaten enthält.
	*/
	Vec2 alignInRow(int row, bool centered);


	/*
		Über diese Funktion kann die Geschwindigkeit, mit der sich ein Objekt bewegt,
		in einer Zeile erhöht werden.
		@param row gibt die Zeile an, in der für alle in dieser Zeile existenten Objekte
				   die Geschwindigkeit erhöht werden soll.
	*/
	void increaseSpeedInRow(int row);


	/*
		Löscht alle existierenden Frösche.
	*/
	void clearFrogs();


	/*
		Platziert ein Objekt wieder an den Anfang der Zeile, sofern es sich aus
		dem Bildschirmrand hinaus bewegt.
	*/
	void repeatObject(GameObject* obj);


	/*
		Gibt alle Objekt-Referenzen zurück.
		@return Gibt in einem Vektor alle Objekt-Referenzen zurück.
	*/
	vector<GameObject*> getAll();

	vector<Entity*> getAllAsEntities();


	/*
		@return Gibt von allen existenten Objekten das zugehörige Drawable als Liste zurück.
	*/
	vector<Drawable> getDrawables();


	/*
		@return Gibt den vom Spieler aktuell steuerbaren Frosch zurück.
	*/
	Frog* getActiveFrog();


	/*
		@return Gibt die Anzahl an Froschobjekten zurück.
	*/
	int getFrogsCount();


	/*
		@return Gibt die Reihe eines Objektes zurück.
	*/
	int getCurrentRowOf(GameObject* obj);
};

#endif OBJECT_MANAGER