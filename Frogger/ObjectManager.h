#ifndef OBJECT_MANAGER
#define OBJECT_MANAGER

#include <vector>
#include <map>

#include "Constants.h"
#include "Tree.h"
#include "Car.h"

class ObjectManager {

protected:
	typedef std::map<int, std::vector<GameObject*>*>::iterator it_type;
	std::map<int, std::vector<GameObject*>*>* rowObjMap;

public:
	ObjectManager();
	~ObjectManager();

	vec2 alignInRow(int row, bool centered);
	int getRowCount() { return rowObjMap->size(); };
	std::vector<GameObject*> getAll();
	void increaseSpeedInRow(int row);
	std::vector<GameObject*>* getObjects(int row) { return rowObjMap->at(row); };

	void createTrees(int row, TreeType treeType, int count, int space, int startX);
	void createCars(int row, CarType carType, int count, int space, int startX);

};

#endif OBJECT_MANAGER