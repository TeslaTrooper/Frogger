#include "GameLogic.h"


GameLogic::GameLogic() {
	this->textures = new std::vector<Texture>();
	this->objectManager = new ObjectManager();
	fontManager = new FontManager();

	initPoolHitBoxes();

	this->frog = new Frog(objectManager->alignInRow(1, true), vec3(0.0f, 0.0f, 0.0f));

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


	fontManager->createNewLabel("scoreLabel", "SCORE", Vec2(10.0f, 545.f), 0.5f);
	fontManager->createNewLabel("score", std::to_string(score), Vec2(100.0f, 545.f), 0.5f);
	fontManager->createNewLabel("timeLabel", "TIME", Vec2(490.0f, 565.f), 0.5f);
}

std::vector<GameObject*> GameLogic::getObjects() {
	std::vector<GameObject*> objs = this->objectManager->getAll();
	objs.push_back(frog);

	return objs;
}

void GameLogic::drawLabels(Renderer* renderer) { 
	fontManager->drawLabels(renderer);
}

void GameLogic::doLogic(GLfloat dt) {
	std::vector<GameObject*> objs = objectManager->getAll();
	CollisionStruct collisionStruct = { Event::COLL_NONE, Vec2(0.0f, 0.0f) };


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
	} else if (poolIndex < 0 && frog->getPosition().y < OFFSET_Y + Y_TILE_SIZE) {
		collisionStruct.effect = Event::COLL_LETHAL_OBJECTS;
	}

	if (collisionStruct.effect == Event::COLL_NONE) {
		if (checkRiverCollision()) {
			collisionStruct.effect = Event::COLL_LETHAL_OBJECTS;
		}
	}

	frog->doLogic(dt, &collisionStruct);
}

void GameLogic::moveFrog(Direction direction) {
	this->frog->moveTo(direction);
	score+=1000;
	fontManager->setText("score", std::to_string(score));
}

bool GameLogic::checkCollision(GameObject* obj) {
	Rectangle frogHitbox = this->frog->getCriticalHitBox();
	Rectangle objHitbox = obj->getCriticalHitBox();

	return intersects(frogHitbox, objHitbox);
}

bool GameLogic::checkRiverCollision() {
	Rectangle frogHitbox = this->frog->getCriticalHitBox();

	return intersects(frogHitbox, riverHitBox);
}

int GameLogic::checkPoolCollision() {
	for (int i = 0; i < sizeof(poolHitBoxes) / sizeof(Rectangle); i++) {
		if(intersects(frog->getCriticalHitBox(), poolHitBoxes[i])) {
			float frogMiddle = frog->getPosition().x + frog->getSize().x / 2;
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

GameLogic::~GameLogic() {
	textures->clear();
	delete textures;
	delete objectManager;
	delete frog;
}