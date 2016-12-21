#include "GameLogic.h"


GameLogic::GameLogic() {}

void GameLogic::create() {
	init();
	setupObjects();
	createPools();
	setupLabels();
	
	insectHitBox.position = pools.at(0).objInfo.hitBox.position;
}

map<DrawableType, vector<Drawable>> GameLogic::getDrawables() {
	map<DrawableType, vector<Drawable>> drawables = map<DrawableType, vector<Drawable>>();

	vector<Drawable> objDrawables = this->objectManager.getDrawables();
	objDrawables.push_back({insectHitBox.position, insectHitBox.size, { Vec2(2, 4), Vec2(1, 1) } });

	vector<Drawable> fontDrawables = this->uiManager.getFontManager().getDrawables();

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

	opponentCreationCounter += dt;
	if (opponentCreationCounter > 1.0f) {
		opponentCreationCounter = 0;
		generateOpponents();
	}

	if (insectHitBox.position.x > 0) {
		insectCounter += dt;
		if (insectCounter > 50.f) {
			insectHitBox.position.x = -X_TILE_SIZE;
			insectCounter = 0;
		}
	}
	

	updateUIElements(dt);
}

void GameLogic::moveFrog(const Direction direction) {
	if (isGameOver) return;

	objectManager.getActiveFrog()->moveTo(direction);
}

void GameLogic::restart() {
	if (!isGameOver) return;

	reset(true);
}


// ------ private methods ------------

void GameLogic::init() {
	overAllScore = 0;
	collectedScore = 0;
	lastRow = 1;
	time = 60.0f;
	remainingTries = 3;
	isGameOver = false;
	remainingTimeLabelDuration = 0;
	currentLevelLabelDuration = 0;
	currentLevel = 1;
	opponentCreationCounter = 0;
	insectCounter = 0;

	appearingObjectProbabilities[Objects::CROCODILE] = 0;
	appearingObjectProbabilities[Objects::INSECT] = 0;
	appearingObjectProbabilities[Objects::SNAKE] = 0;
	appearingObjectProbabilities[Objects::FEMALE_FROG] = 0;
}

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

	objectManager.createTurtle(11, Objects::TWO_ELEMENT_CHAIN, 4, 80, 0);
	objectManager.createTurtle(8, Objects::THREE_ELEMENT_CHAIN, 4, 40, 0);
}

void GameLogic::setupLabels() {
	setupUIElement("scoreLabel", "SCORE", true, .5f, UIManager::Alignment::LEFT_DOWN);
	setupUIElement("remainingTriesLabel", "FROGS", true, .5f, UIManager::Alignment::LEFT_DOWN);
	setupUIElement("timeLabel", "TIME", true, .5f, UIManager::Alignment::RIGHT_DOWN);
	uiManager.getFontManager().alignDescriptionLeft("timeLabel", false);

	setupUIElement("remainingTimeLabel", "TIMES", true, .5f, UIManager::Alignment::CENTER);
	uiManager.getFontManager().hideAfter("remainingTimeLabel", 2.f);
	uiManager.getFontManager().hideLabel("remainingTimeLabel");

	setupUIElement("currentLevelLabel", "LEVEL", true, .5f, UIManager::Alignment::CENTER);
	uiManager.getFontManager().hideAfter("currentLevelLabel", 4.f);
	uiManager.getFontManager().hideLabel("currentLevelLabel");

	setupUIElement("gameOver", "GAME OVER SPACE TO RESTART", false, .5f, UIManager::Alignment::CENTER);
	uiManager.getFontManager().hideLabel("gameOver");

	setupUIElement("collectedScore", to_string(collectedScore), false, .3f, UIManager::Alignment::CENTER);
	uiManager.getFontManager().hideAfter("collectedScore", 2.f);
	uiManager.getFontManager().hideLabel("collectedScore");

	uiManager.getFontManager().setText("collectedScore", std::to_string(collectedScore));
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
	FontManager fontManager = uiManager.getFontManager();

	activeFrog->doLogic(dt);

	if (activeFrog->getState() == State::INACTIVE) {
		overAllScore += collectedScore;
		overAllScore += (int)time * 10;

		if (collectedScore > 0) {
			fontManager.setText("collectedScore", std::to_string(collectedScore));
			fontManager.setPosition("collectedScore", pools.at(currentPoolIndex).objInfo.hitBox.position.sub(Vec2(0.f, 15.f)));
			fontManager.showLabel("collectedScore");
		}

		fontManager.showLabel("remainingTimeLabel");
		fontManager.setText("remainingTimeLabel", std::to_string((int)time));
		

		reset(false);

		pools.at(currentPoolIndex).ocupied = true;

		if (objectManager.getFrogsCount() > 4) {
			objectManager.clearFrogs();

			for (int i = 0; i < pools.size(); i++) {
				pools.at(i).ocupied = false;
			}

			overAllScore += 1000;
			updateLevelDifficulty();

			fontManager.setText("currentLevelLabel", std::to_string((int)currentLevel));
			fontManager.showLabel("currentLevelLabel");
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
	FontManager fontManager = uiManager.getFontManager();

	time = time < 0 ? 0 : time;
	remainingTries = remainingTries < 0 ? 0 : remainingTries;

	fontManager.setText("scoreLabel", std::to_string(overAllScore));
	fontManager.setText("timeLabel", std::to_string((int)time));
	fontManager.setText("remainingTriesLabel", std::to_string(remainingTries));

	fontManager.update(dt);
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
		uiManager.getFontManager().hideLabel("gameOver");
		remainingTries = 3;
		overAllScore = 0;
		currentLevel = 1;
		appearingObjectProbabilities[Objects::CROCODILE] = 0;
		appearingObjectProbabilities[Objects::INSECT] = 0;
		appearingObjectProbabilities[Objects::SNAKE] = 0;
		appearingObjectProbabilities[Objects::FEMALE_FROG] = 0;
	}
	
	time = 60;
	collectedScore = 0;
	lastRow = 1;
}

void GameLogic::gameOver(Frog* activeFrog) {
	if (remainingTries < 0) {
		isGameOver = true;
		uiManager.getFontManager().showLabel("gameOver");
		objectManager.clearFrogs();
		objectManager.createFrog();

		for (int i = 0; i < pools.size(); i++) {
			pools.at(i).ocupied = false;
		}
	}
}

void GameLogic::updateLevelDifficulty() {
	switch (++currentLevel) {
		case 2: {
			setObjectProbability(Objects::FEMALE_FROG, 5);
			setObjectProbability(Objects::INSECT, 5);

			int randomStreet = randomNumber(2, 6);
			objectManager.increaseSpeedInRow(randomStreet);
			int randomRiver = randomNumber(8, 12);
			objectManager.increaseSpeedInRow(randomRiver);
		}; break;
		case 3: {
			setObjectProbability(Objects::FEMALE_FROG, 8);
			setObjectProbability(Objects::INSECT, 8);
			setObjectProbability(Objects::SNAKE, 5);

			int randomStreet = randomNumber(2, 6);
			objectManager.increaseSpeedInRow(randomStreet);
			int randomRiver = randomNumber(8, 12);
			objectManager.increaseSpeedInRow(randomRiver);
		}; break;
		case 4: {
			setObjectProbability(Objects::FEMALE_FROG, 12);
			setObjectProbability(Objects::INSECT, 12);
			setObjectProbability(Objects::SNAKE, 10);
			setObjectProbability(Objects::CROCODILE, 5);

			int randomStreet = randomNumber(2, 6);
			objectManager.increaseSpeedInRow(randomStreet);
			int randomRiver = randomNumber(8, 12);
			objectManager.increaseSpeedInRow(randomRiver);
		}; break;
		case 5: {
			setObjectProbability(Objects::FEMALE_FROG, 20);
			setObjectProbability(Objects::INSECT, 15);
			setObjectProbability(Objects::SNAKE, 20);
			setObjectProbability(Objects::CROCODILE, 10);

			int randomStreet = randomNumber(2, 6);
			objectManager.increaseSpeedInRow(randomStreet);
			int randomRiver = randomNumber(8, 12);
			objectManager.increaseSpeedInRow(randomRiver);
		}; break;
	}
}

void GameLogic::generateOpponents() {
	map<Objects, int>::iterator it;
	for (it = appearingObjectProbabilities.begin(); it != appearingObjectProbabilities.end(); it++) {
		Objects type = it->first;
		int probability = it->second;

		if (!random(probability))
			continue;

		int randomRow;

		switch (type) {
			case Objects::FEMALE_FROG: randomRow = randomNumber(8, 12); break;
			case Objects::CROCODILE: randomRow = 12; break;
			case Objects::INSECT: {
				if (insectHitBox.position.x > 0) 
					continue;

				randomRow = randomNumber(0, 4);
				while (pools.at(randomRow).ocupied) {
					randomRow = randomNumber(0, 4);
				}
				insectHitBox.position = pools.at(randomRow).objInfo.hitBox.position;
			}; continue;
			case Objects::SNAKE: {
				randomRow = randomNumber(8, 12);
				while (randomRow == 11) {
					randomRow = randomNumber(8, 12);
				}
			}; break;
		}

		objectManager.createOpponent({ type, randomRow });
	}
}

int GameLogic::randomNumber(int min, int max) {
	return rand() % (max - min + 1) + min;
}

bool GameLogic::random(int probability) {
	return randomNumber(0, 100) < probability;
}

void GameLogic::setObjectProbability(Objects key, int value) {
	appearingObjectProbabilities[key] = value;
}

void GameLogic::setupUIElement(string identifier, string text, bool withlabel, float scale, UIManager::Alignment alignment) {
	uiManager.createUIElement(identifier, text);
	uiManager.configureUIElement(identifier, withlabel, scale);
	uiManager.align(identifier, alignment);
}

GameLogic::~GameLogic() {}