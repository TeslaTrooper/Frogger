#include "GameLogic.h"


GameLogic::GameLogic() {
	setupObjects();
	setupLabels();
	getPoolHitBoxes();
}

map<DrawableType, vector<Drawable>> GameLogic::getDrawables() {
	map<DrawableType, vector<Drawable>> drawables = map<DrawableType, vector<Drawable>>();

	vector<Drawable> objDrawables = this->objectManager.getDrawables();
	for (int i = 0; i < frogs.size(); i++) {
		objDrawables.push_back(frogs.at(i)->getDrawable());
	}
	

	vector<Drawable> fontDrawables = this->fontManager.getDrawables();

	drawables[DrawableType::OBJECT] = objDrawables;
	drawables[DrawableType::FONT] = fontDrawables;

	return drawables;
}

void GameLogic::gameLoop(const GLfloat dt) {
	vector<GameObject*> objs = objectManager.getAll();
	Frog* activeFrog = getActiveFrog();

	for (int i = 0; i < objs.size(); i++) {
		objs.at(i)->doLogic(dt);
		repeatObjectPosition(objs.at(i));
	}

	activeFrog->doLogic(dt, &evaluateCollisions(objs, activeFrog));

	if (activeFrog->getState() == State::INACTIVE) {
		if (frogs.size() > 4) {
			frogs.clear();
		}

		frogs.push_back(new Frog(objectManager.alignInRow(1, true)));
	}
}

void GameLogic::moveFrog(const Direction direction) {
	getActiveFrog()->moveTo(direction);
	score+=1000;
	fontManager.setText("score", std::to_string(score));
}


// ------ private methods ------------

void GameLogic::setupObjects() {
	this->frogs.push_back(new Frog(objectManager.alignInRow(1, true)));

	objectManager.createObject(2, Objects::CAR_YELLOW, 3, 200, 100);
	objectManager.createObject(3, Objects::HARVESTER, 3, 150, 50);
	objectManager.createObject(4, Objects::CAR_PINK, 3, 200, 275);
	objectManager.createObject(5, Objects::CAR_WHITE, 3, 200, 75);
	objectManager.createObject(6, Objects::TRUCK, 3, 300, 280);

	objectManager.createObject(9, Objects::SMALL_TREE, 3, 200, 100);
	objectManager.createObject(10, Objects::LARGE_TREE, 3, 50, 30);
	objectManager.createObject(12, Objects::MEDIUM_TREE, 3, 100, 10);

	objectManager.createObject(8, Objects::THREE_ELEMENT_CHAIN, 5, 40, 0);
	objectManager.createObject(11, Objects::TWO_ELEMENT_CHAIN, 4, 80, 0);
}

void GameLogic::setupLabels() {
	fontManager.createNewLabel("scoreLabel", "SCORE", Vec2(10.0f, 545.f), 0.5f);
	fontManager.createNewLabel("score", std::to_string(score), Vec2(100.0f, 545.f), 0.5f);
	fontManager.createNewLabel("timeLabel", "TIME", Vec2(490.0f, 565.f), 0.5f);
}

CollisionStruct GameLogic::evaluateCollisions(vector<GameObject*> objs, Frog* frog) {
	CollisionStruct resultingCollision = { Event::COLL_NONE, Vec2(0.0f, 0.0f) };

	CollisionStruct objCollision = { Event::COLL_NONE, Vec2(0.0f, 0.0f) };
	for (int i = 0; i < objs.size(); i++) {
		if (objCollision.effect != Event::COLL_NONE) {
			break;
		}

		objCollision = getExistingCollisionStruct(frog, objs.at(i));
	}

	CollisionStruct riverCollision = checkRiverCollision();
	CollisionStruct poolCollision = checkPoolCollision();

	if (objCollision.effect == Event::COLL_LETHAL_OBJECTS || riverCollision.effect == Event::COLL_LETHAL_OBJECTS) {
		resultingCollision.effect = Event::COLL_LETHAL_OBJECTS;
	}
	if (objCollision.effect == Event::COLL_TREE_TURTLE) {
		resultingCollision = objCollision;
	}
	if (objCollision.effect == Event::COLL_TREE_TURTLE && poolCollision.effect == Event::COLL_POOL) {
		resultingCollision = poolCollision;
	}

	return resultingCollision;
}

CollisionStruct GameLogic::getExistingCollisionStruct(Frog* frog, GameObject* obj) {
	Rectangle frogHitbox = frog->getCriticalHitBox();
	Rectangle objHitbox = obj->getCriticalHitBox();

	if (intersects(frogHitbox, objHitbox)) {
		return obj->getCollisionStruct();
	}

	return{ Event::COLL_NONE, Vec2(0.0f, 0.0f) };
}

CollisionStruct GameLogic::checkRiverCollision() {
	Rectangle frogHitbox = getActiveFrog()->getCriticalHitBox();

	if (intersects(frogHitbox, riverHitBox)) {
		return{ Event::COLL_LETHAL_OBJECTS, Vec2(0.0f, 0.0f) };
	}

	return{ Event::COLL_NONE, Vec2(0.0f, 0.0f) };
}

CollisionStruct GameLogic::checkPoolCollision() {
	Frog* activeFrog = getActiveFrog();


	for (int i = 0; i < poolHitBoxes.size(); i++) {
		if (intersects(activeFrog->getCriticalHitBox(), poolHitBoxes.at(i))) {
			float frogMiddle = activeFrog->getPosition().x + activeFrog->getSize().x / 2;
			float poolMiddle = poolHitBoxes.at(i).position.x + poolHitBoxes.at(i).size.x / 2;

			if (abs(frogMiddle - poolMiddle) <= X_TILE_SIZE * POOL_VALID_INTERSECTION) {
				return poolCollisionStructMap.at(i);
			}

			break;
		}
	}

	return{ Event::COLL_NONE, Vec2(0.0f, 0.0f) };
}

void GameLogic::repeatObjectPosition(GameObject* obj) {
	if (obj->getPosition().x < -obj->getSize().x) {
		obj->setPosition(Vec2(700 + obj->getSize().x, obj->getPosition().y));
	}
	if (obj->getPosition().x > 700 + obj->getSize().x) {
		obj->setPosition(Vec2(-obj->getSize().x, obj->getPosition().y));
	}
}

vector<Rectangle> GameLogic::getPoolHitBoxes() {
	vector<Rectangle> hitBoxes = vector<Rectangle>(POOLS_COUNT);

	for (int i = 0; i < POOLS_COUNT; i++) {
		Vec2 position = Vec2(i * POOL_SPACE + OFFSET_X + i * X_TILE_SIZE, OFFSET_Y);
		Vec2 size = Vec2(X_TILE_SIZE, Y_TILE_SIZE);

		hitBoxes[i] = { position, size };
	}

	return hitBoxes;
}

Frog* GameLogic::getActiveFrog() {
	for (int i = 0; i < frogs.size(); i++) {
		if (frogs.at(i)->getState() != State::INACTIVE) {
			return frogs.at(i);
		}
	}
}

GameLogic::~GameLogic() {
	frogs.clear();
}