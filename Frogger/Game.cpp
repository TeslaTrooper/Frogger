#include "Game.h"


Game::Game() : physicsEngine(this) {}

void Game::create() {
	init();
	setupObjects();
	createPools();
	uiManager.createInitialUIElements(stats);

	insectHitBox.position = Vec2((float) -X_TILE_SIZE, pools.at(0).objInfo.hitBox.position.y);
	currentCollisions = new vector<GameObject*>();
}

map<DrawableType, vector<Drawable>> Game::getDrawables() {
	map<DrawableType, vector<Drawable>> drawables = map<DrawableType, vector<Drawable>>();

	vector<Drawable> objDrawables = this->objectManager.getDrawables();
	objDrawables.push_back({ Mat4::getTransformation(insectHitBox.position, insectHitBox.size), {Vec2(2, 4), Vec2(1, 1)} });

	vector<Drawable> fontDrawables = this->uiManager.getFontManager().getDrawables();

	drawables[DrawableType::OBJECT] = objDrawables;
	drawables[DrawableType::FONT] = fontDrawables;

	return drawables;
}

void Game::gameLoop(const float dt) {
	currentCollisions->clear();

	vector<Entity*> entities = objectManager.getAllAsEntities();

	physicsEngine.update(entities, dt);





	vector<GameObject*> objs = objectManager.getAll();
	Frog* activeFrog = objectManager.getActiveFrog();

	ObjectInfo interactingObject = evaluateCollisions(*currentCollisions, activeFrog);

	if (stats.getTime() <= 0.0f) {
		interactingObject = { Rectangle(), Rectangle(), Vec2(),{ Event::COLL_LETHAL_OBJECTS, 0 } };
	}

	activeFrog->registerInteraction(interactingObject);

	if (interactingObject.collisionInfo.effect == Event::COLLECTING) {
		increaseCollectedScoreBy(interactingObject.collisionInfo.effect);
		objectManager.registerInteractionOnFemaleFrog(interactingObject);
	}

	for (int i = 0; i < objs.size(); i++) {
		objs.at(i)->doLogic(dt);
		objectManager.repeatObject(objs.at(i));
	}

	manageFrogs(activeFrog, dt);

	updateGameRules(activeFrog, dt);

	if (stats.increaseOpponentCounter(dt)) {
		generateOpponents();
	}

	if (insectHitBox.position.x > 0) {
		if (stats.increaseInsectCounter(dt)) {
			insectHitBox.position.x = -X_TILE_SIZE;
		}
	}

	updateUIElements(dt);
}

void Game::moveFrog(const Direction direction) {
	if (stats.isGameOver()) return;

	objectManager.getActiveFrog()->moveTo(direction);
}

void Game::restart() {
	if (!stats.isGameOver()) return;

	reset(true);
}


// ------ private methods ------------

void Game::init() {
	levelManager.reset();
	//levelManager.setLevel(stats.getCurrentLevel());
}

void Game::setupObjects() {
	objectManager.createFrog();

	//objectManager.createStaticObject(2, Objects::CAR_YELLOW, 3, 200, 100);
	//objectManager.createStaticObject(3, Objects::CAR_ORANGE, 3, 150, 50);
	//objectManager.createStaticObject(4, Objects::CAR_RED, 3, 175, 125);
	//objectManager.createStaticObject(5, Objects::CAR_WHITE, 3, 200, 75);
	//objectManager.createStaticObject(6, Objects::TRUCK, 3, 150, 0);

	objectManager.createStaticObject(9, Objects::SMALL_TREE, 3, 200, 100);
	objectManager.createStaticObject(10, Objects::LARGE_TREE, 3, 50, 30);
	objectManager.createStaticObject(12, Objects::MEDIUM_TREE, 3, 100, 10);

	objectManager.createTurtle(11, Objects::TWO_ELEMENT_CHAIN, 4, 80, 0);
	objectManager.createTurtle(8, Objects::THREE_ELEMENT_CHAIN, 4, 40, 0);
}

void Game::resolveCollision(Entity* e1, Entity* e2, const Vec2& location) const {
	// We don't want to insert frog instances as we treat frogs seperatly
	Frog* e1IsFrog = dynamic_cast<Frog*>(e1);
	Frog* e2IsFrog = dynamic_cast<Frog*>(e2);

	if (e1IsFrog == nullptr)
		currentCollisions->push_back(dynamic_cast<GameObject*>(e1));

	if (e2IsFrog == nullptr)
		currentCollisions->push_back(dynamic_cast<GameObject*>(e2));
}

ObjectInfo Game::evaluateCollisions(vector<GameObject*> objs, Frog* frog) {
	ObjectInfo objInfo = EMPTY_OBJECT_INFO;

	// Iterate over all colliding objects
	// and retrieve the one with highest priority
	int lastPriority = 0;
	for (int i = 0; i < objs.size(); i++) {
		//ObjectInfo currentObjInfo = checkForCollision(frog, objs.at(i));
		//Event collEffect = currentObjInfo.collisionInfo.effect;
		ObjectInfo currentObjInfo = objs.at(i)->getObjectInfo();
		Event collEffect = currentObjInfo.collisionInfo.effect;
		int priority = currentObjInfo.collisionInfo.priority;

		if (collEffect != Event::COLL_NONE && priority > lastPriority) {
			objInfo = currentObjInfo;
			lastPriority = currentObjInfo.collisionInfo.priority;
		}
	}

	// Check for river, insect and pool collision seperately
	ObjectInfo riverInfo = checkForRiverCollision();
	ObjectInfo poolInfo = checkForPoolCollision();
	ObjectInfo insectInfo = checkForInsectCollision();

	// Increase score, if frog jumps into pool with insect
	if (insectInfo.collisionInfo.effect == Event::COLL_INSECT && poolInfo.collisionInfo.effect == Event::COLL_POOL) {
		increaseCollectedScoreBy(insectInfo.collisionInfo.effect);
		insectHitBox.position = Vec2(-X_TILE_SIZE, 0.0f);
	}

	// Group priorities together and return object info with highest prio
	int priorities[3] = { objInfo.collisionInfo.priority, riverInfo.collisionInfo.priority, poolInfo.collisionInfo.priority };

	int last = 0;
	for (int i = 0; i < sizeof(priorities) / sizeof(int); i++) {
		if (priorities[i] > last) last = priorities[i];
	}

	if (objInfo.collisionInfo.priority == last) return objInfo;
	if (riverInfo.collisionInfo.priority == last) return riverInfo;
	if (poolInfo.collisionInfo.priority == last) return poolInfo;

	return EMPTY_OBJECT_INFO;
}

ObjectInfo Game::checkForCollision(Frog* frog, GameObject* obj) {
	Rectangle frogHitbox = frog->getCriticalHitBox();
	Rectangle objHitbox = obj->getCriticalHitBox();

	if (intersects(frogHitbox, objHitbox)) {
		return obj->getObjectInfo();
	}

	return EMPTY_OBJECT_INFO;
}

ObjectInfo Game::checkForRiverCollision() {
	Rectangle frogHitbox = objectManager.getActiveFrog()->getCriticalHitBox();

	if (intersects(frogHitbox, riverHitBox)) {
		return { Rectangle(), riverHitBox, Vec2(), {Event::COLL_LETHAL_OBJECTS, 4 } };
	}

	return EMPTY_OBJECT_INFO;
}

ObjectInfo Game::checkForPoolCollision() {
	Frog* activeFrog = objectManager.getActiveFrog();

	for (int i = 0; i < pools.size(); i++) {
		if (intersects(activeFrog->getCriticalHitBox(), pools.at(i).objInfo.hitBox)) {
			if (pools.at(i).ocupied) {
				return { Rectangle(), pools.at(i).objInfo.hitBox, Vec2(), {Event::COLL_LETHAL_OBJECTS, 10 } };
			}

			float frogMiddle = activeFrog->getPosition().x + activeFrog->getSize().x / 2;
			float poolMiddle = pools.at(i).objInfo.hitBox.position.x + pools.at(i).objInfo.hitBox.size.x / 2;

			if (abs(frogMiddle - poolMiddle) <= X_TILE_SIZE * POOL_VALID_INTERSECTION) {
				stats.setCurrentPoolIndex(i);

				return pools.at(i).objInfo;
			}

			break;
		}
	}

	return EMPTY_OBJECT_INFO;
}

ObjectInfo Game::checkForInsectCollision() {
	Frog* activeFrog = objectManager.getActiveFrog();

	if (intersects(activeFrog->getCriticalHitBox(), insectHitBox)) {
		return { Rectangle(), insectHitBox, Vec2(), { Event::COLL_INSECT, 8 } };
	}

	return EMPTY_OBJECT_INFO;
}

vector<Rectangle> Game::getPoolHitBoxes() {
	vector<Rectangle> hitBoxes = vector<Rectangle>(POOLS_COUNT);

	for (int i = 0; i < POOLS_COUNT; i++) {
		Vec2 position(i * POOL_SPACE + OFFSET_X + i * X_TILE_SIZE, OFFSET_Y);
		Vec2 size(X_TILE_SIZE, Y_TILE_SIZE);

		hitBoxes[i] = { position, size };
	}

	return hitBoxes;
}

void Game::createPools() {
	vector<Rectangle> poolHitBoxes = getPoolHitBoxes();

	for (int i = 0; i < POOLS_COUNT; i++) {
		ObjectInfo info = EMPTY_OBJECT_INFO;
		info.hitBox = poolHitBoxes.at(i);
		info.collisionInfo = { Event::COLL_POOL, 7 };
		pools.push_back({ info, false });
	}
}

void Game::manageFrogs(Frog* activeFrog, float dt) {
	FontManager fontManager = uiManager.getFontManager();

	activeFrog->doLogic(dt);

	if (activeFrog->getState() == State::INACTIVE) {
		stats.increaseScoreByCollectedScore();
		stats.increaseScoreByRemainingTime();
		//stats.overAllScore += stats.collectedScore;
		//stats.overAllScore += (int) stats.time * 10;

		uiManager.showLabelsForCurrentState(stats, pools.at(stats.getCurrentPoolIndex()).objInfo.hitBox.position.sub(Vec2(0.f, 15.f)));

		reset(false);

		pools.at(stats.getCurrentPoolIndex()).ocupied = true;

		if (objectManager.getFrogsCount() > 4) {
			objectManager.clearFrogs();

			for (int i = 0; i < pools.size(); i++) {
				pools.at(i).ocupied = false;
			}

			stats.increaseScoreByNextLevelBonus();
			//stats.overAllScore += 1000;
			updateLevelDifficulty();

			fontManager.setText("currentLevelLabel", std::to_string((int) stats.getCurrentLevel()));
			fontManager.showLabel("currentLevelLabel");
		}

		objectManager.createFrog();
	}
}

void Game::updateGameRules(Frog* activeFrog, float dt) {
	if (stats.isGameOver()) return;

	//stats.time -= dt;
	stats.decreaseTime(dt);

	if (activeFrog->getState() != State::INACTIVE && objectManager.getCurrentRowOf(activeFrog) > stats.getLastRow()) {
		stats.increaseScoreByPassedRow();
		//stats.overAllScore += 10;
		//stats.lastRow = objectManager.getCurrentRowOf(activeFrog);
		stats.setLastRow(objectManager.getCurrentRowOf(activeFrog));
	}

	if (activeFrog->getState() == State::KILLED) {
		reset(false);
		//stats.remainingTries--;
		gameOver(activeFrog);
		stats.consumeRemainingTry();
	}

}

void Game::updateUIElements(float dt) {
	FontManager fontManager = uiManager.getFontManager();

	fontManager.setText("scoreLabel", std::to_string(stats.getScore()));
	fontManager.setText("timeLabel", std::to_string((int) stats.getTime()));
	fontManager.setText("remainingTriesLabel", std::to_string(stats.getRemainingTries()));

	fontManager.update(dt);
}

void Game::increaseCollectedScoreBy(Event ev) {
	switch (ev) {
		case Event::COLLECTING:
			stats.increaseCollectedScoreBy(GameStats::CollectionType::FEMALE_FROG);
			break;
			//stats.collectedScore += 200; break;
		case Event::COLL_INSECT:
			stats.increaseCollectedScoreBy(GameStats::CollectionType::INSECT);
			break;
			//stats.collectedScore += 200; break;
	}
}

void Game::reset(bool resetAll) {
	if (resetAll) {
		stats = GameStats();
		uiManager.getFontManager().hideLabel("gameOver");
		levelManager.reset();
	}

	stats.reset();
	//stats.time = 60;
	//stats.collectedScore = 0;
	//stats.lastRow = 1;
}

void Game::gameOver(Frog* activeFrog) {
	if (stats.getRemainingTries() > 0)
		return;

	stats.gameOver();
	uiManager.getFontManager().showLabel("gameOver");
	objectManager.clearFrogs();
	objectManager.createFrog();

	for (int i = 0; i < pools.size(); i++)
		pools.at(i).ocupied = false;
}

void Game::updateLevelDifficulty() {
	vector<int> rows = levelManager.setLevel(stats.getCurrentLevel());
	for (int i = 0; i < rows.size(); i++) {
		objectManager.increaseSpeedInRow(rows.at(i));
	}
}

void Game::generateOpponents() {
	bool ocupiedPools[5];
	for (int i = 0; i < POOLS_COUNT; i++) {
		ocupiedPools[i] = pools.at(i).ocupied;
	}

	levelManager.initData(ocupiedPools, insectHitBox.position.x);
	map<Objects, int> objects = levelManager.getObjects();


	for (map<Objects, int>::iterator it = objects.begin(); it != objects.end(); it++) {
		Objects type = it->first;
		int row = it->second;

		if (type == Objects::INSECT) {
			insectHitBox.position = pools.at(row).objInfo.hitBox.position;
			continue;
		}

		objectManager.createOpponent({ type, row });
	}
}

Game::~Game() {}