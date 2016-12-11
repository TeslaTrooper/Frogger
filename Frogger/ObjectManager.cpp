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

int ObjectManager::fromYToRow(float y) {
	return ((y - OFFSET_Y) / -Y_TILE_SIZE) + TILES_Y;
}

vector<GameObject*> ObjectManager::getAll() {
	vector<GameObject*> objs = vector<GameObject*>();

	for (it_type iterator = rowObjMap->begin(); iterator != rowObjMap->end(); iterator++) {
		vector<GameObject*>* objsInRow = iterator->second;

		for (int i = 0; i < objsInRow->size(); i++) {
			if (Opponent* opp = dynamic_cast<Opponent*>(objsInRow->at(i))) {
				if (opp->isExpired()) continue;
			}

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
			if (Opponent* opp = dynamic_cast<Opponent*>(iterator->second->at(i))) {
				if (opp->isExpired()) continue;
			}

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

void ObjectManager::createOpponent(OpponentInfo opponentInfo) {
	waitingOpponents.push_back(opponentInfo);
}

Frog* ObjectManager::getActiveFrog() {
	for (int i = 0; i < frogs.size(); i++) {
		if (frogs.at(i)->getState() != State::INACTIVE) {
			return frogs.at(i);
		}
	}
}

void ObjectManager::registerInteractionOnFemaleFrog(const ObjectInfo& objInfo) {
	int row = fromYToRow(objInfo.hitBox.position.y);

	vector<GameObject*>* objs = rowObjMap->at(row);

	for (int i = 0; i < objs->size(); i++) {
		if (objs->at(i)->getObjectInfo() == objInfo) {
			objs->at(i)->registerInteraction(objInfo);
			return;
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
	if (Opponent* opp = dynamic_cast<Opponent*>(obj)) {
		return;
	}


	if (obj->getPosition().x < -obj->getSize().x) {
		obj->setPosition(Vec2(700 + obj->getSize().x, obj->getPosition().y));

		createWaitingOpponent(obj->getObjectInfo());
	}

	if (obj->getPosition().x > 700 + obj->getSize().x) {
		obj->setPosition(Vec2(-obj->getSize().x, obj->getPosition().y));

		createWaitingOpponent(obj->getObjectInfo());
	}
}

void ObjectManager::createWaitingOpponent(const ObjectInfo& objInfo) {
	if (waitingOpponents.size() == 0) {
		return;
	}

	OpponentInfo opponentInfo = waitingOpponents.front();

	Vec2 pos = alignInRow(opponentInfo.row, false);
	pos.x = -X_TILE_SIZE;

	if (pos.y != objInfo.hitBox.position.y) {
		return;
	}

	Opponent* opponent;
	switch (opponentInfo.objectType) {
		case Objects::SNAKE: opponent = new Snake(pos); break;
		case Objects::FEMALE_FROG: opponent = new FemaleFrog(pos); break;
	}

	opponent->setPosition(Vec2(objInfo.hitBox.position.x, opponent->getPosition().y));
	opponent->useAsNewHomePosition(Vec2(objInfo.hitBox.position.x, opponent->getPosition().y));
	opponent->registerInteraction(objInfo);

	rowObjMap->at(opponentInfo.row)->push_back(opponent);

	vector<OpponentInfo>::iterator it = find_if(waitingOpponents.begin(), waitingOpponents.end(),
		[&](const OpponentInfo& info) -> bool { return opponentInfo.objectType == info.objectType && opponentInfo.row == info.row; });
	waitingOpponents.erase(it);
}