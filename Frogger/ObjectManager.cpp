#include "ObjectManager.h"

ObjectManager::ObjectManager() {
	this->rowObjMap = new map<int, vector<GameObject*>*>();
	femaleFrog = nullptr;
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

	if (femaleFrog != nullptr && femaleFrog->isExpired()) {
		femaleFrog = nullptr;
	} else if (femaleFrog != nullptr) {
		objs.push_back(femaleFrog);
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

	if (femaleFrog != nullptr) {
		drawables.push_back(femaleFrog->getDrawable());
	}

	return drawables;
}

void ObjectManager::createObject(int row, Objects objType, int count, int space, int startX) {
	vector<GameObject*>* objsInRow = new vector<GameObject*>();

	Vec2 pos = alignInRow(row, false);
	ObjectInfo objectInfo = objectInitializer.at(objType);

	for (int i = 0; i < count; i++) {
		Vec2 objSize = objectInfo.textureRegion.size.mul(X_TILE_SIZE);
		objectInfo.hitBox = { Vec2(startX + (i * (objSize.x + space)), pos.y), objSize };

		objsInRow->push_back(new GameObject(objectInfo, emptyTransitionSet));
	}

	(*rowObjMap)[row] = objsInRow;
}

void ObjectManager::createFrog() {
	frogs.push_back(new Frog(alignInRow(FROG_START_ROW, true)));
}

void ObjectManager::createFemaleFrog(int row) {
	if (femaleFrog != nullptr) {
		return;
	}

	Vec2 pos = alignInRow(row, false);
	pos.x = -X_TILE_SIZE;

	femaleFrog = new FemaleFrog(pos);
	femaleFrog->registerInteraction(EMPTY_OBJECT_INFO);
}

Frog* ObjectManager::getActiveFrog() {
	for (int i = 0; i < frogs.size(); i++) {
		if (frogs.at(i)->getState() != State::INACTIVE) {
			return frogs.at(i);
		}
	}
}

void ObjectManager::registerInteractionOnFemaleFrog(ObjectInfo objInfo) {
	if (femaleFrog != nullptr) {
		femaleFrog->registerInteraction(objInfo);
	}
}

int ObjectManager::getFrogsCount() {
	return frogs.size();
}

void ObjectManager::clearFrogs() {
	frogs.clear();
}

void ObjectManager::repeatObject(GameObject* obj) {
	if (FemaleFrog* femaleFrog = dynamic_cast<FemaleFrog*>(obj)) {
		return;
	}


	if (obj->getPosition().x < -obj->getSize().x) {
		obj->setPosition(Vec2(700 + obj->getSize().x, obj->getPosition().y));
	}

	if (obj->getPosition().x > 700 + obj->getSize().x) {
		obj->setPosition(Vec2(-obj->getSize().x, obj->getPosition().y));

		if (femaleFrog != nullptr && femaleFrog->getPosition().y == obj->getPosition().y) {
			if (femaleFrog->getState() == State::IDLE) {
				femaleFrog->setPosition(Vec2(-obj->getSize().x, femaleFrog->getPosition().y));
				femaleFrog->useAsNewHomePosition(Vec2(-obj->getSize().x, femaleFrog->getPosition().y));
				femaleFrog->registerInteraction(obj->getObjectInfo());
			}
		}
	}
}