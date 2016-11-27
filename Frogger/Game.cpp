#include "GameLogic.h"


GameLogic::GameLogic() {}

void GameLogic::create() {
	setupObjects();
	setupLabels();
	createPools();
}

map<DrawableType, vector<Drawable>> GameLogic::getDrawables() {
	map<DrawableType, vector<Drawable>> drawables = map<DrawableType, vector<Drawable>>();

	vector<Drawable> objDrawables = this->objectManager.getDrawables();
	vector<Drawable> fontDrawables = this->fontManager.getDrawables();

	drawables[DrawableType::OBJECT] = objDrawables;
	drawables[DrawableType::FONT] = fontDrawables;

	return drawables;
}

void GameLogic::gameLoop(const GLfloat dt) {
	vector<GameObject*> objs = objectManager.getAll();
	Frog* activeFrog = objectManager.getActiveFrog();

	for (int i = 0; i < objs.size(); i++) {
		objs.at(i)->doLogic(dt);
		objectManager.repeatObject(objs.at(i));
	}

	CollisionStruct collisionStruct = evaluateCollisions(objs, activeFrog);

	activeFrog->doLogic(dt, &collisionStruct);

	if (activeFrog->getState() == State::INACTIVE) {
		pools.at(currentPoolIndex).ocupied = true;

		if (objectManager.getFrogsCount() > 4) {
			objectManager.clearFrogs();

			for (int i = 0; i < pools.size(); i++) {
				pools.at(i).ocupied = false;
			}
		}

		objectManager.createFrog();
	}
}

void GameLogic::moveFrog(const Direction direction) {
	objectManager.getActiveFrog()->moveTo(direction);
	score+=1000;
	fontManager.setText("score", std::to_string(score));
}


// ------ private methods ------------

void GameLogic::setupObjects() {
	objectManager.createFrog();

	objectManager.createObject(2, Objects::CAR_YELLOW, 3, 200, 100);
	objectManager.createObject(3, Objects::CAR_ORANGE, 3, 150, 50);
	objectManager.createObject(4, Objects::CAR_RED, 3, 200, 275);
	objectManager.createObject(5, Objects::CAR_WHITE, 3, 200, 75);
	objectManager.createObject(6, Objects::TRUCK, 3, 300, 280);

	objectManager.createObject(9, Objects::SMALL_TREE, 3, 200, 100);
	objectManager.createObject(10, Objects::LARGE_TREE, 3, 50, 30);
	objectManager.createObject(12, Objects::MEDIUM_TREE, 3, 100, 10);

	objectManager.createObject(8, Objects::THREE_ELEMENT_CHAIN, 5, 40, 0);
	objectManager.createObject(11, Objects::TWO_ELEMENT_CHAIN, 4, 80, 0);
}

void GameLogic::setupLabels() {
	score = 0;

	fontManager.createNewLabel("scoreLabel", "SCORE", Vec2(10.0f, 545.f), 0.5f);
	fontManager.createNewLabel("score", to_string(score), Vec2(120.0f, 545.f), 0.5f);
	fontManager.createNewLabel("timeLabel", "TIME", Vec2(480.0f, 565.f), 0.5f);
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
	Rectangle frogHitbox = objectManager.getActiveFrog()->getCriticalHitBox();

	if (intersects(frogHitbox, riverHitBox)) {
		return{ Event::COLL_LETHAL_OBJECTS, Vec2(0.0f, 0.0f) };
	}

	return{ Event::COLL_NONE, Vec2(0.0f, 0.0f) };
}

CollisionStruct GameLogic::checkPoolCollision() {
	Frog* activeFrog = objectManager.getActiveFrog();


	for (int i = 0; i < pools.size(); i++) {
		if (intersects(activeFrog->getCriticalHitBox(), pools.at(i).hitBox)) {
			if (pools.at(i).ocupied) {
				return { Event::COLL_LETHAL_OBJECTS, Vec2(0.0f, 0.0f) };
			}

			float frogMiddle = activeFrog->getPosition().x + activeFrog->getSize().x / 2;
			float poolMiddle = pools.at(i).hitBox.position.x + pools.at(i).hitBox.size.x / 2;

			if (abs(frogMiddle - poolMiddle) <= X_TILE_SIZE * POOL_VALID_INTERSECTION) {
				currentPoolIndex = i;

				return pools.at(i).collisionStruct;
			}

			break;
		}
	}

	return{ Event::COLL_NONE, Vec2(0.0f, 0.0f) };
}

vector<Rectangle> GameLogic::getPoolHitBoxes() {
	vector<Rectangle> hitBoxes = vector<Rectangle>(POOLS_COUNT);

	for (int i = 0; i < POOLS_COUNT; i++) {
		Vec2 position(i * POOL_SPACE + OFFSET_X + i * X_TILE_SIZE, OFFSET_Y);
		Vec2 size(X_TILE_SIZE, Y_TILE_SIZE);

		hitBoxes[i] = { position, size };
	}

	return hitBoxes;
}

void GameLogic::createPools() {
	vector<Rectangle> poolHitBoxes = getPoolHitBoxes();
	map<int, CollisionStruct> collisionStructs = map<int, CollisionStruct>();

	for (int i = 0; i < POOLS_COUNT; i++) {
		pools.push_back({ { Event::COLL_POOL, poolHitBoxes[i].position }, poolHitBoxes.at(i), false });
	}
}

GameLogic::~GameLogic() {}