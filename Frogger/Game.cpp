#include "GameLogic.h"


GameLogic::GameLogic() {
	this->textures = new vector<Texture>();
	this->objectManager = new ObjectManager();
	this->fontManager = new FontManager();

	setupObjects();
	setupLabels();
	initPoolHitBoxes();
}

map<DrawableType, vector<Drawable>> GameLogic::getDrawables() {
	map<DrawableType, vector<Drawable>> drawables = map<DrawableType, vector<Drawable>>();

	vector<Drawable> objDrawables = this->objectManager->getDrawables();
	for (int i = 0; i < runningFrogs; i++) {
		objDrawables.push_back(frog[i]->getDrawable());
	}
	

	vector<Drawable> fontDrawables = this->fontManager->getDrawables();

	drawables[DrawableType::OBJECT] = objDrawables;
	drawables[DrawableType::FONT] = fontDrawables;

	return drawables;
}

void GameLogic::gameLoop(GLfloat dt) {
	std::vector<GameObject*> objs = objectManager->getAll();
	CollisionStruct collisionStruct = { Event::COLL_NONE, Vec2(0.0f, 0.0f) };

	Frog* activeFrog = getActiveFrog();

	for (int i = 0; i < objs.size(); i++) {
		GameObject* obj = objs.at(i);

		obj->doLogic(dt);
		repeatObjectPosition(obj);

		if (checkCollision(obj)) {
			collisionStruct = obj->getCollisionStruct();
		}
	}

	int poolIndex = checkPoolCollision();
	if (poolIndex > -1) {
		collisionStruct = { Event::COLL_POOL, poolHitBoxes[poolIndex].position };
	} else if (poolIndex < 0 && activeFrog->getPosition().y < OFFSET_Y + Y_TILE_SIZE) {
		collisionStruct.effect = Event::COLL_LETHAL_OBJECTS;
	}

	if (collisionStruct.effect == Event::COLL_NONE) {
		if (checkRiverCollision()) {
			collisionStruct.effect = Event::COLL_LETHAL_OBJECTS;
		}
	}

	activeFrog->doLogic(dt, &collisionStruct);

	if (activeFrog->getState() == State::INACTIVE) {
		runningFrogs++;

		if (runningFrogs > 4) {
			// Alle Teiche sind besetzt
		} else {
			frog[runningFrogs-1] = new Frog(objectManager->alignInRow(1, true));
		}
	}
}

void GameLogic::moveFrog(Direction direction) {
	getActiveFrog()->moveTo(direction);
	score+=1000;
	fontManager->setText("score", std::to_string(score));
}

void GameLogic::setupObjects() {
	this->frog[0] = new Frog(objectManager->alignInRow(1, true));

	objectManager->createObject(2, Objects::CAR_YELLOW, 3, 200, 100);
	objectManager->createObject(3, Objects::HARVESTER, 3, 150, 50);
	objectManager->createObject(4, Objects::CAR_PINK, 3, 200, 275);
	objectManager->createObject(5, Objects::CAR_WHITE, 3, 200, 75);
	objectManager->createObject(6, Objects::TRUCK, 3, 300, 280);

	objectManager->createObject(9, Objects::SMALL_TREE, 3, 200, 100);
	objectManager->createObject(10, Objects::LARGE_TREE, 3, 50, 30);
	objectManager->createObject(12, Objects::MEDIUM_TREE, 3, 100, 10);

	objectManager->createObject(8, Objects::THREE_ELEMENT_CHAIN, 5, 40, 0);
	objectManager->createObject(11, Objects::TWO_ELEMENT_CHAIN, 4, 80, 0);
}

void GameLogic::setupLabels() {
	fontManager->createNewLabel("scoreLabel", "SCORE", Vec2(10.0f, 545.f), 0.5f);
	fontManager->createNewLabel("score", std::to_string(score), Vec2(100.0f, 545.f), 0.5f);
	fontManager->createNewLabel("timeLabel", "TIME", Vec2(490.0f, 565.f), 0.5f);
}

bool GameLogic::checkCollision(GameObject* obj) {
	Rectangle frogHitbox = getActiveFrog()->getCriticalHitBox();
	Rectangle objHitbox = obj->getCriticalHitBox();

	return intersects(frogHitbox, objHitbox);
}

bool GameLogic::checkRiverCollision() {
	Rectangle frogHitbox = getActiveFrog()->getCriticalHitBox();

	return intersects(frogHitbox, riverHitBox);
}

int GameLogic::checkPoolCollision() {
	Frog* activeFrog = getActiveFrog();


	for (int i = 0; i < sizeof(poolHitBoxes) / sizeof(Rectangle); i++) {
		if(intersects(activeFrog->getCriticalHitBox(), poolHitBoxes[i])) {
			float frogMiddle = activeFrog->getPosition().x + activeFrog->getSize().x / 2;
			float poolMiddle = poolHitBoxes[i].position.x + poolHitBoxes[i].size.x / 2;

			if (abs(frogMiddle - poolMiddle) <= X_TILE_SIZE * 0.75) {
				return i;
			}

			break;
		}
	}

	return -1;
}

bool GameLogic::intersects(Rectangle rect1, Rectangle rect2) {
	if ((int)rect1.position.x >= (int)(rect2.position.x + rect2.size.x) || (int)rect2.position.x >= (int)(rect1.position.x + rect1.size.x)) {
		return false;
	}

	if ((int)rect1.position.y >= (int)(rect2.position.y + rect2.size.y) || (int)rect2.position.y >= (int)(rect1.position.y + rect1.size.y)) {
		return false;
	}

	return true;
}

void GameLogic::repeatObjectPosition(GameObject* obj) {
	if (obj->getPosition().x < -obj->getSize().x) {
		obj->setPosition(Vec2(700 + obj->getSize().x, obj->getPosition().y));
	}
	if (obj->getPosition().x > 700 + obj->getSize().x) {
		obj->setPosition(Vec2(-obj->getSize().x, obj->getPosition().y));
	}
}

void GameLogic::initPoolHitBoxes() {
	for (int i = 0; i < POOLS_COUNT; i++) {
		Vec2 position = Vec2(i * POOL_SPACE + OFFSET_X + i * X_TILE_SIZE, OFFSET_Y);
		Vec2 size = Vec2(X_TILE_SIZE, Y_TILE_SIZE);

		poolHitBoxes[i] = { position, size };
	}
}

Frog* GameLogic::getActiveFrog() {
	for (int i = 0; i < runningFrogs; i++) {
		if (frog[i]->getState() != State::INACTIVE) {
			return frog[i];
		}
	}
}

GameLogic::~GameLogic() {
	textures->clear();
	delete textures;
	delete objectManager;

	for (int i = 0; i < sizeof(frog) / sizeof(Frog*); i++) {
		delete frog[i];
	}
}