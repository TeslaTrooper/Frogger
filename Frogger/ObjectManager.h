#ifndef OBJECT_MANAGER
#define OBJECT_MANAGER

#include <vector>
#include <map>

#include "GameObject.h"

using namespace std;

class ObjectManager {

protected:
	typedef map<int, vector<GameObject*>*>::iterator it_type;
	map<int, vector<GameObject*>*>* rowObjMap;

public:
	ObjectManager();
	~ObjectManager();

	Vec2 alignInRow(int row, bool centered);
	int getRowCount() { return rowObjMap->size(); };
	vector<GameObject*> getAll();
	void increaseSpeedInRow(int row);
	vector<GameObject*>* getObjects(int row) { return rowObjMap->at(row); };
	vector<Drawable> getDrawables();

	void createObject(int row, Objects objType, int count, int space, int startX);

};

#endif OBJECT_MANAGER