#include "ObjectManager.h"

ObjectManager::ObjectManager() {
	this->rowObjMap = new map<int, vector<GameObject*>*>();
}

ObjectManager::~ObjectManager() {
	frogs.clear();

	for (it_type iterator = rowObjMap->begin(); iterator != rowObjMap->end(); iterator++) {
		vector<GameObject*>* objsInRow = iterator->second;

		for (int i = 0; i < objsInRow->size(); i++) {
			delete objsInRow->at(i);
		}

		delete objsInRow;
	}

	delete rowObjMap;
}

Vec2 ObjectManager::alignInRow(int row, bool centered) {
	if (!centered) {
		return Vec2(0.0f, OFFSET_Y + (TILES_Y - row) * Y_TILE_SIZE);
	}

	return Vec2(320.0f, OFFSET_Y + (TILES_Y - row) * Y_TILE_SIZE);
}

vector<GameObject*> ObjectManager::getAll() {
	vector<GameObject*> objs = vector<GameObject*>();

	for (it_type iterator = rowObjMap->begin(); iterator != rowObjMap->end(); iterator++) {
		vector<GameObject*>* objsInRow = iterator->second;

		for (int i = 0; i < objsInRow->size(); i++) {
			objs.push_back(objsInRow->at(i));
		}
	}

	return objs;
}

void ObjectManager::increaseSpeedInRow(int row) {
	vector<GameObject*>* objsInRow = this->rowObjMap->at(row);

	for (int i = 0; i < objsInRow->size(); i++) {
		GameObject* obj = objsInRow->at(i);
		obj->setMovement(Vec2(obj->getCurrentMovement().x * 1.1, 0.0f));
	}
}

vector<Drawable> ObjectManager::getDrawables() {
	vector<Drawable> drawables = vector<Drawable>();

	for (it_type iterator = rowObjMap->begin(); iterator != rowObjMap->end(); iterator++) {
		for (int i = 0; i < iterator->second->size(); i++) {
			drawables.push_back(iterator->second->at(i)->getDrawable());
		}
	}

	for (int i = 0; i < frogs.size(); i++) {
		drawables.push_back(frogs.at(i)->getDrawable());
	}

	return drawables;
}

void ObjectManager::createObject(int row, Objects objType, int count, int space, int startX) {
	vector<GameObject*>* objsInRow = new vector<GameObject*>();

	Vec2 pos = alignInRow(row, false);
	Initializer initializer = objDefinitions.at(objType);

	for (int i = 0; i < count; i++) {
		GameObject* obj = new GameObject(initializer.textureRegion);

		obj->setMovement(initializer.movement);
		obj->setCollisionStruct(initializer.collisionStruct);
		obj->setPosition(Vec2(startX + (i * (obj->getSize().x + space)), pos.y));

		objsInRow->push_back(obj);
	}

	(*rowObjMap)[row] = objsInRow;
}

void ObjectManager::createFrog() {
	frogs.push_back(new Frog(alignInRow(FROG_START_ROW, true)));
}

Frog* ObjectManager::getActiveFrog() {
	for (int i = 0; i < frogs.size(); i++) {
		if (frogs.at(i)->getState() != State::INACTIVE) {
			return frogs.at(i);
		}
	}
}

int ObjectManager::getFrogsCount() {
	return frogs.size();
}

void ObjectManager::clearFrogs() {
	frogs.clear();
}

void ObjectManager::repeatObject(GameObject* obj) {
	if (obj->getPosition().x < -obj->getSize().x) {
		obj->setPosition(Vec2(700 + obj->getSize().x, obj->getPosition().y));
	}
	if (obj->getPosition().x > 700 + obj->getSize().x) {
		obj->setPosition(Vec2(-obj->getSize().x, obj->getPosition().y));
	}
}