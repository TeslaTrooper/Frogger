#include "ObjectManager.h"

ObjectManager::ObjectManager() {
	this->rowObjMap = new std::map<int, std::vector<GameObject*>*>();
}

ObjectManager::~ObjectManager() {}

Vec2 ObjectManager::alignInRow(int row, bool centered) {
	if (!centered) {
		return Vec2(0.0f, OFFSET_Y + (TILES_Y - row) * Y_TILE_SIZE);
	}

	return Vec2(320.0f, OFFSET_Y + (TILES_Y - row) * Y_TILE_SIZE);
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
		obj->setMovement(Vec2(obj->getCurrentMovement().x * 1.1, 0.0f));

		std::cout << obj->getCurrentMovement().x;
	}
}

void ObjectManager::createObject(int row, Objects objType, int count, int space, int startX) {
	std::vector<GameObject*>* objsInRow = new std::vector<GameObject*>();

	Vec2 pos = alignInRow(row, false);
	GameObject::Initializer initializer = objDefinitions.at(objType);
	

	for (int i = 0; i < count; i++) {
		GameObject* obj = new GameObject(initializer.texture);

		obj->setMovement(initializer.movement);
		obj->setCollisionStruct(initializer.collisionStruct);
		obj->setPosition(Vec2(startX + (i * (obj->getSize().x + space)), pos.y));

		objsInRow->push_back(obj);
	}

	(*rowObjMap)[row] = objsInRow;
}