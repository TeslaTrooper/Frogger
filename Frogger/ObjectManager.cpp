#include "ObjectManager.h"

ObjectManager::ObjectManager() {
	this->rowObjMap = new map<int, vector<GameObject*>*>();

	for (int i = 1; i <= TILES_Y; i++) {
		(*rowObjMap)[i] = new vector<GameObject*>();
	}

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
		obj->setMovement(Vec2(obj->getCurrentMovement().x * 1.1f, 0.0f));
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
	vector<GameObject*>* objsInRow = rowObjMap->at(row);

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

void ObjectManager::createTurtle(int row, Objects objType, int count, int space, int startX) {
	vector<GameObject*>* objsInRow = rowObjMap->at(row);
	Vec2 pos = alignInRow(row, false);

	Vec2 objSize = objectTextureRegions.at(objType).size;
	objSize = objSize.mul(X_TILE_SIZE);

	for (int i = 0; i < count; i++) {
		Vec2 position = Vec2(startX + (i * (objSize.x + space)), pos.y); 
		objsInRow->push_back(new Turtle(objType, position, objectTextureRegions.at(objType), i == 0 ? true : false));
	}
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

int ObjectManager::getCurrentRowOf(GameObject* obj) {
	return fromYToRow(obj->getPosition().y);
}

void ObjectManager::clearFrogs() {
	frogs.clear();
}

void ObjectManager::repeatObject(GameObject* obj) {
	CrocodileBody* crocodile = nullptr;
	Turtle* turtle = nullptr;

	if (Opponent* opp = dynamic_cast<Opponent*>(obj)) {
		crocodile = dynamic_cast<CrocodileBody*>(opp);
		turtle = dynamic_cast<Turtle*>(opp);

		if (!crocodile && !turtle) {
			return;
		}
	}

	if (obj->getPosition().x < -obj->getSize().x) {
		obj->setPosition(Vec2(WINDOW_WIDTH, obj->getPosition().y));

		if (turtle && turtle->isAnimating())
			return;

		createWaitingOpponent(obj->getObjectInfo());
	}

	if (obj->getPosition().x > WINDOW_WIDTH + obj->getSize().x) {
		obj->setPosition(Vec2(-obj->getSize().x, obj->getPosition().y));

		ObjectInfo objInfo = obj->getObjectInfo();
		if (getNextOpponentInfo(obj->getObjectInfo()).objectType == Objects::CROCODILE) {
			obj->resetMovement();
		}

		if (crocodile) {
			Objects objType = Objects::MEDIUM_TREE;
			int row = fromYToRow(obj->getObjectInfo().hitBox.position.y);

			createObject(row, objType, 1, 0, obj->getPosition().x);
			objInfo = rowObjMap->at(row)->back()->getObjectInfo();

			obj->resetMovement();
		}

		createWaitingOpponent(objInfo);
	}
}

OpponentInfo ObjectManager::createWaitingOpponent(const ObjectInfo& objInfo) {
	OpponentInfo opponentInfo = getNextOpponentInfo(objInfo);
	if (opponentInfo.row == -1) return opponentInfo;

	Vec2 pos = alignInRow(opponentInfo.row, false);

	switch (opponentInfo.objectType) {
		case Objects::SNAKE: {
			rowObjMap->at(opponentInfo.row)->push_back(initOpponentWithObjectInfo(new Snake(pos), objInfo));
		}; break;
		case Objects::FEMALE_FROG: {
			rowObjMap->at(opponentInfo.row)->push_back(initOpponentWithObjectInfo(new FemaleFrog(pos), objInfo));
		}; break;
		case Objects::CROCODILE: {
			rowObjMap->at(opponentInfo.row)->push_back(initOpponent(new CrocodileHead(pos), -X_TILE_SIZE));
			rowObjMap->at(opponentInfo.row)->push_back(initOpponent(new CrocodileBody(pos), -4*X_TILE_SIZE));
		}; break;
	}

	vector<OpponentInfo>::iterator it = find_if(waitingOpponents.begin(), waitingOpponents.end(),
		[&](const OpponentInfo& info) -> bool { return opponentInfo.objectType == info.objectType && opponentInfo.row == info.row; });
	waitingOpponents.erase(it);

	return opponentInfo;
}

OpponentInfo ObjectManager::getNextOpponentInfo(const ObjectInfo& objInfo) {
	OpponentInfo opponentInfo = { Objects::PLAYER, -1 };

	if (waitingOpponents.size() == 0) {
		return opponentInfo;
	}

	for (int i = 0; i < waitingOpponents.size(); i++) {
		int y = (int) alignInRow(waitingOpponents.at(i).row, false).y;

		if (y == (int) objInfo.hitBox.position.y) {
			opponentInfo = waitingOpponents.at(i);
			break;
		}
	}

	return opponentInfo;
}

Opponent* ObjectManager::initOpponentWithObjectInfo(Opponent* opponent, const ObjectInfo& objInfo) {
	opponent->setPosition(Vec2(objInfo.hitBox.position.x, opponent->getPosition().y));
	opponent->useAsNewHomePosition(Vec2(objInfo.hitBox.position.x, opponent->getPosition().y));
	opponent->registerInteraction(objInfo);

	return opponent;
}

Opponent* ObjectManager::initOpponent(Opponent* opponent, float x) {
	opponent->setPosition(Vec2(x, opponent->getPosition().y));

	return opponent;
}