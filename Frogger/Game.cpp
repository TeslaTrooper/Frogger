#include "GameLogic.h"


GameLogic::GameLogic() {}

void GameLogic::create() {
	setupObjects();
	createPools();
	setupLabels();
	

	insectHitBox.position = pools.at(0).objInfo.hitBox.position;
}

map<DrawableType, vector<Drawable>> GameLogic::getDrawables() {
	map<DrawableType, vector<Drawable>> drawables = map<DrawableType, vector<Drawable>>();

	vector<Drawable> objDrawables = this->objectManager.getDrawables();
	objDrawables.push_back({insectHitBox.position, insectHitBox.size, { Vec2(6, 7), Vec2(1, 1) } });

	vector<Drawable> fontDrawables = this->fontManager.getDrawables();

	drawables[DrawableType::OBJECT] = objDrawables;
	drawables[DrawableType::FONT] = fontDrawables;

	return drawables;
}

void GameLogic::gameLoop(const GLfloat dt) {
	vector<GameObject*> objs = objectManager.getAll();
	Frog* activeFrog = objectManager.getActiveFrog();

	ObjectInfo interactingObject = evaluateCollisions(objs, activeFrog);

	if (time <= 0.0f) {
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

	updateUIElements(dt);
}

void GameLogic::moveFrog(const Direction direction) {
	if (isGameOver) return;

	objectManager.getActiveFrog()->moveTo(direction);

	
	//objectManager.createOpponent({ Objects::SNAKE, 10 });
	objectManager.createOpponent({ Objects::FEMALE_FROG, 9 });
	if (direction == Direction::RIGHT) {
		//objectManager.createOpponent({ Objects::CROCODILE, 12 });
	}
	else {
		//objectManager.createOpponent({ Objects::FEMALE_FROG, 12 });
	}
	
	//objectManager.createOpponent({ Objects::FEMALE_FROG, 8 });
	//objectManager.createOpponent({ Objects::FEMALE_FROG, 11 });
}

void GameLogic::restart() {
	if (!isGameOver) return;

	reset(true);
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

	objectManager.createObject(8, Objects::THREE_ELEMENT_CHAIN, 4, 40, 0);
	objectManager.createObject(11, Objects::TWO_ELEMENT_CHAIN, 4, 80, 0);
}

void GameLogic::setupLabels() {
	overAllScore = 0;
	collectedScore = 0;
	lastRow = 1;
	time = 60.0f;
	remainingTries = 3;
	isGameOver = false;
	remainingTimeLabelDuration = 0;
	currentLevelLabelDuration = 0;
	currentLevel = 1;

	fontManager.createNewLabel("scoreLabel", "SCORE", Vec2(10.0f, 545.f), 0.5f);
	fontManager.createNewLabel("score", to_string(overAllScore), Vec2(120.0f, 545.f), 0.5f);
	fontManager.createNewLabel("timeLabel", "TIME", Vec2(480.0f, 565.f), 0.5f);
	fontManager.createNewLabel("time", to_string((int)time), Vec2(430.0f, 565.f), 0.5f);
	fontManager.createNewLabel("remainingTriesLabel", "FROGS", Vec2(10.0f, 565.f), 0.5f);
	fontManager.createNewLabel("remainingTries", to_string(remainingTries), Vec2(120.0f, 565.f), 0.5f);
	fontManager.createNewLabel("remainingTimeLabel", "TIME", Vec2(WINDOW_WIDTH / 2 - 60, WINDOW_HEIGHT / 2 - 25), 0.5f);
	fontManager.createNewLabel("remainingTime", to_string((int)time), Vec2(WINDOW_WIDTH / 2 + 20, WINDOW_HEIGHT / 2 - 25), 0.5f);
	fontManager.hideLabel("remainingTimeLabel");
	fontManager.hideLabel("remainingTime");
	fontManager.createNewLabel("collectedScore", to_string(collectedScore), pools.at(0).objInfo.hitBox.position.sub(Vec2(0.f, 20.f)), 0.3f);
	fontManager.hideLabel("collectedScore");
	fontManager.createNewLabel("currentLevelLabel", "LEVEL", Vec2(WINDOW_WIDTH / 2 - 60, WINDOW_HEIGHT / 2 - 25), 0.5f);
	fontManager.createNewLabel("currentLevel", to_string(currentLevel), Vec2(WINDOW_WIDTH / 2 + 40, WINDOW_HEIGHT / 2 - 25), 0.5f);
	fontManager.hideLabel("currentLevelLabel");
	fontManager.hideLabel("currentLevel");
	fontManager.createNewLabel("gameOver", "GAME OVER SPACE TO RESTART", Vec2(WINDOW_WIDTH / 2 - 260, WINDOW_HEIGHT / 2 - 25), 0.5f);
	fontManager.hideLabel("gameOver");
}

ObjectInfo GameLogic::evaluateCollisions(vector<GameObject*> objs, Frog* frog) {
	ObjectInfo objInfo;

	int lastPriority = 0;
	for (int i = 0; i < objs.size(); i++) {
		ObjectInfo currentObjInfo = checkForCollision(frog, objs.at(i));
		Event collEffect = currentObjInfo.collisionInfo.effect;
		int priority = currentObjInfo.collisionInfo.priority;

		if (collEffect != Event::COLL_NONE && priority > lastPriority) {
			objInfo = currentObjInfo;
			lastPriority = currentObjInfo.collisionInfo.priority;
		}
	}

	ObjectInfo riverInfo = checkForRiverCollision();
	ObjectInfo poolInfo = checkForPoolCollision();
	ObjectInfo insectInfo = checkForInsectCollision();

	if (insectInfo.collisionInfo.effect == Event::COLL_INSECT && poolInfo.collisionInfo.effect == Event::COLL_POOL) {
		increaseCollectedScoreBy(insectInfo.collisionInfo.effect);
		insectHitBox.position = Vec2(-X_TILE_SIZE, 0.0f);
	}

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

ObjectInfo GameLogic::checkForCollision(Frog* frog, GameObject* obj) {
	Rectangle frogHitbox = frog->getCriticalHitBox();
	Rectangle objHitbox = obj->getCriticalHitBox();

	if (intersects(frogHitbox, objHitbox)) {
		return obj->getObjectInfo();
	}

	return EMPTY_OBJECT_INFO;
}

ObjectInfo GameLogic::checkForRiverCollision() {
	Rectangle frogHitbox = objectManager.getActiveFrog()->getCriticalHitBox();

	if (intersects(frogHitbox, riverHitBox)) {
		return { Rectangle(), riverHitBox, Vec2(), {Event::COLL_LETHAL_OBJECTS, 4 } };
	}

	return EMPTY_OBJECT_INFO;
}

ObjectInfo GameLogic::checkForPoolCollision() {
	Frog* activeFrog = objectManager.getActiveFrog();

	for (int i = 0; i < pools.size(); i++) {
		if (intersects(activeFrog->getCriticalHitBox(), pools.at(i).objInfo.hitBox)) {
			if (pools.at(i).ocupied) {
				return { Rectangle(), pools.at(i).objInfo.hitBox, Vec2(), {Event::COLL_LETHAL_OBJECTS, 10 } };
			}

			float frogMiddle = activeFrog->getPosition().x + activeFrog->getSize().x / 2;
			float poolMiddle = pools.at(i).objInfo.hitBox.position.x + pools.at(i).objInfo.hitBox.size.x / 2;

			if (abs(frogMiddle - poolMiddle) <= X_TILE_SIZE * POOL_VALID_INTERSECTION) {
				currentPoolIndex = i;

				return pools.at(i).objInfo;
			}

			break;
		}
	}

	return EMPTY_OBJECT_INFO;
}

ObjectInfo GameLogic::checkForInsectCollision() {
	Frog* activeFrog = objectManager.getActiveFrog();

	if (intersects(activeFrog->getCriticalHitBox(), insectHitBox)) {
		return { Rectangle(), insectHitBox, Vec2(), { Event::COLL_INSECT, 8 } };
	}

	return EMPTY_OBJECT_INFO;
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

	for (int i = 0; i < POOLS_COUNT; i++) {
		ObjectInfo info = EMPTY_OBJECT_INFO;
		info.hitBox = poolHitBoxes.at(i);
		info.collisionInfo = { Event::COLL_POOL, 7 };
		pools.push_back({ info, false });
	}
}

void GameLogic::manageFrogs(Frog* activeFrog, float dt) {
	activeFrog->doLogic(dt);

	if (activeFrog->getState() == State::INACTIVE) {
		overAllScore += collectedScore;
		overAllScore += (int)time * 10;

		if (collectedScore > 0) {
			fontManager.setText("collectedScore", std::to_string(collectedScore));
			fontManager.setPosition("collectedScore", pools.at(currentPoolIndex).objInfo.hitBox.position.sub(Vec2(0.f, 15.f)));
			fontManager.showLabel("collectedScore");
		}

		fontManager.setText("remainingTime", std::to_string((int)time));
		fontManager.showLabel("remainingTimeLabel");
		fontManager.showLabel("remainingTime");
		

		reset(false);

		pools.at(currentPoolIndex).ocupied = true;

		if (objectManager.getFrogsCount() > 4) {
			objectManager.clearFrogs();

			for (int i = 0; i < pools.size(); i++) {
				pools.at(i).ocupied = false;
			}

			overAllScore += 1000;
			currentLevel++;
			fontManager.setText("currentLevel", std::to_string((int)currentLevel));
			fontManager.showLabel("currentLevelLabel");
			fontManager.showLabel("currentLevel");
		}

		objectManager.createFrog();
	}
}

void GameLogic::updateGameRules(Frog* activeFrog, GLfloat dt) {
	if (isGameOver) return;

	time -= dt;

	if (activeFrog->getState() != State::INACTIVE && objectManager.getCurrentRowOf(activeFrog) > lastRow) {
		overAllScore += 10;
		lastRow = objectManager.getCurrentRowOf(activeFrog);
	}

	if (activeFrog->getState() == State::KILLED) {
		reset(false);
		remainingTries--;
	}

	gameOver(activeFrog);
}

void GameLogic::updateUIElements(float dt) {
	time = time < 0 ? 0 : time;
	remainingTries = remainingTries < 0 ? 0 : remainingTries;

	fontManager.setText("score", std::to_string(overAllScore));
	fontManager.setText("time", std::to_string((int)time));
	fontManager.setText("remainingTries", std::to_string(remainingTries));

	if (fontManager.isVisible("remainingTime")) {
		remainingTimeLabelDuration += dt;
		if (remainingTimeLabelDuration > 2) {
			fontManager.hideLabel("remainingTimeLabel");
			fontManager.hideLabel("remainingTime");
			fontManager.hideLabel("collectedScore");
			remainingTimeLabelDuration = 0;
		}
	}

	if (fontManager.isVisible("currentLevel")) {
		currentLevelLabelDuration += dt;
		if (currentLevelLabelDuration > 4) {
			fontManager.hideLabel("currentLevelLabel");
			fontManager.hideLabel("currentLevel");
			currentLevelLabelDuration = 0;
		}
	}
}

void GameLogic::increaseCollectedScoreBy(Event ev) {
	switch (ev) {
		case Event::COLLECTING: 
			collectedScore += 200; break;
		case Event::COLL_INSECT: 
			collectedScore += 200; break;
	}
}

void GameLogic::reset(bool resetAll) {
	if (resetAll) {
		isGameOver = false;
		fontManager.hideLabel("gameOver");
		remainingTries = 3;
		overAllScore = 0;
	}
	
	time = 60;
	collectedScore = 0;
	lastRow = 1;
}

void GameLogic::gameOver(Frog* activeFrog) {
	if (remainingTries < 0) {
		isGameOver = true;
		fontManager.showLabel("gameOver");
	}
}

GameLogic::~GameLogic() {}