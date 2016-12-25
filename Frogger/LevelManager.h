#ifndef LEVEL_MANAGER
#define LEVEL_MANAGER

#include <map>
#include <vector>

#include "Util.h"

using namespace std;

class LevelManager {
	int currentLevel;
	map<Objects, int> objectProbabilities;
	bool ocupiedPools[5];
	float insectXPos;
	bool dataIsUpToDate;

	int calculateRow(Objects type);
	vector<int> increaseSpeed();

public:
	LevelManager();
	~LevelManager() {};


	/*
		Aktualisiert das Level, in dem sich das Spiel befindet.
		@param level ist das neue Level.
		@return Gibt eine Liste von rows zurück, in denen die 
				Geschw. erhöht werden soll.
	*/
	vector<int> setLevel(int level);


	/*
		Über diese Methode werden notwendige Informationen dieser Instanz
		bekannt gemacht. Diese Infos sind notwendig, damit getObjects() korrekte
		Werte zurückliefert.
		Diese Methode muss immer vor dem Aufruf von getObjects() erfolgen,
		andernfall wird eine Exception geworfen.
		@param ocupiedPools[] enthält die Zustände der einzelnen Pools.
		@param insectXPos ist die x Position des Insect Rectangles.
	*/
	void initData(bool ocupiedPools[], float insectXPos);


	/*
		Über diese Methode wird für alle Objekttypen ermittelt, ob der
		Typ in Abhängigkeit einer Wahrscheinlichkeit für diesen Methodenaufruf
		als Opponent auf dem Spielfeld erscheinen kann.
		@return Gibt eine Liste aller Objekttypen zurück, bei denen für diesen
				Methodenaufruf die Wahrscheinlichkeit zur Erzeugen eingetroffen ist.
	*/
	map<Objects, int> getObjects();


	/*
		Versetzt den Manager in den ursprünglichen Zustand.
	*/
	void reset();
};

#endif LEVEL_MANAGER