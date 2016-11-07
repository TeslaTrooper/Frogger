#include "ObjectManager.h"

ObjectManager::ObjectManager() {
	this->rowObjMap = new std::map<int, std::vector<GameObject*>*>();
}

ObjectManager::~ObjectManager() {}

vec2 ObjectManager::alignInRow(int row, bool centered) {
	if (!centered) {
		return vec2(0.0f, OFFSET_Y + (TILES_Y - row) * GameObject::Y_TILE_SIZE);
	}

	return vec2(320.0f, OFFSET_Y + (TILES_Y - row) * GameObject::Y_TILE_SIZE);
}

std::vector<GameObject*> ObjectManager::getAll() {
	std::vector<GameObject*> objs = std::vector<GameObject*>();

	for (it_type iterator = rowObjMap->begin(); iterator != rowObjMap->end(); iterator++) {
		std::vector<GameObject*>* objsInRow = iterator->second;

		for (int i = 0; i < objsInRow->size(); i++) {
			objs.push_back(objsInRow->at(i));
		}
	}

	return objs;
}

void ObjectManager::increaseSpeedInRow(int row) {
	std::vector<GameObject*>* objsInRow = this->rowObjMap->at(row);

	for (int i = 0; i < objsInRow->size(); i++) {
		GameObject* obj = objsInRow->at(i);
		obj->setMovement(vec2(obj->getCurrentMovement().x * 1.1, 0.0f));

		std::cout << obj->getCurrentMovement().x;
	}
}

void ObjectManager::createTrees(int row, TreeType treeType, int count, int space, int startX) {
	std::vector<GameObject*>* objsInRow = new std::vector<GameObject*>();

	vec2 pos = alignInRow(row, false);
	for (int i = 0; i < count; i++) {
		Tree* tree = new Tree(treeType, vec2(0.0f, pos.y), vec3(1.0f, 1.0f, 1.0f));
		tree->setPosition(vec2(startX + (i * (tree->getSize().x + space)), pos.y));

		objsInRow->push_back(tree);
	}

	(*rowObjMap)[row] = objsInRow;
}

void ObjectManager::createCars(int row, CarType carType, int count, int space, int startX) {
	std::vector<GameObject*>* objsInRow = new std::vector<GameObject*>();

	vec2 pos = alignInRow(row, false);
	for (int i = 0; i < count; i++) {
		Car* car = new Car(carType, vec2(startX + (i*space), pos.y), vec3(1.0f, 1.0f, 1.0f));

		objsInRow->push_back(car);
	}

	(*rowObjMap)[row] = objsInRow;
}