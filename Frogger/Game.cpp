#include "GameLogic.h"


GameLogic::GameLogic() {
	this->textures = new std::vector<Texture>();
	this->objectManager = new ObjectManager();
	fontManager = new FontManager();

	this->frog = new Frog(objectManager->alignInRow(1, true), vec3(0.0f, 0.0f, 0.0f));

	objectManager->createCars(2, CarType::CAR_YELLOW, 3, 200, 100);
	objectManager->createCars(3, CarType::HARVESTER, 3, 150, 50);
	objectManager->createCars(4, CarType::CAR_PINK, 3, 200, 275);
	objectManager->createCars(5, CarType::CAR_WHITE, 3, 200, 75);
	objectManager->createCars(6, CarType::TRUCK, 2, 300, 280);

	objectManager->createTrees(9, TreeType::SMALL, 3, 200, 100);
	objectManager->createTrees(10, TreeType::LARGE, 3, 50, 30);
	objectManager->createTrees(12, TreeType::MEDIUM, 3, 100, 10);

	objectManager->createTurtles(8, ChainType::THREE_ELEMENT_CHAIN, 5, 40, 0);

	fontManager->createNewLabel("scoreLabel", "SCORE", glm::vec2(10.0f, 545.f), 0.5f);
	fontManager->createNewLabel("score", std::to_string(score), glm::vec2(100.0f, 545.f), 0.5f);
	fontManager->createNewLabel("timeLabel", "TIME", glm::vec2(490.0f, 565.f), 0.5f);
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
	CollisionStruct collisionStruct = { Event::NEUTRAL, glm::vec2(0.0f, 0.0f) };

	//std::cout << frog->getState() << std::endl;

	for (int i = 0; i < objs.size(); i++) {
		GameObject* obj = objs.at(i);

		obj->doLogic(dt);
		repeatObjectPosition(obj);

		//if (frog->getState() != State::DIEING && checkCollision(obj)) {
		if (checkCollision(obj)) {
			collisionStruct = obj->getCollisionStruct();
			//frog->reactOnCollision(obj->getCollisionStruct());
		}
		//}
	}

	frog->doLogic(dt, collisionStruct);
}

void GameLogic::moveFrog(Direction direction) {
	this->frog->moveTo(direction);
	score+=1000;
	fontManager->setText("score", std::to_string(score));
}

bool GameLogic::checkCollision(GameObject* obj) {
	if (isFrog(obj)) {
		return false;
	}

	GameObject::Rectangle frogHitbox = this->frog->getCriticalHitBox();
	GameObject::Rectangle objHitbox = obj->getCriticalHitBox();

	if ((int) frogHitbox.position.x >= (int) (objHitbox.position.x + objHitbox.size.x) || (int) objHitbox.position.x >= (int) (frogHitbox.position.x + frogHitbox.size.x)) {
		return false;
	}

	if ((int) frogHitbox.position.y >= (int) (objHitbox.position.y + objHitbox.size.y) || (int) objHitbox.position.y >= (int) (frogHitbox.position.y + frogHitbox.size.y)) {
		return false;
	}

	return true;
}

void GameLogic::repeatObjectPosition(GameObject* obj) {
	if (obj->getPosition().x < -obj->getSize().x) {
		obj->setPosition(vec2(700 + obj->getSize().x, obj->getPosition().y));
	}
	if (obj->getPosition().x > 700 + obj->getSize().x) {
		obj->setPosition(vec2(-obj->getSize().x, obj->getPosition().y));
	}
}

bool GameLogic::isFrog(GameObject* obj) {
	if (Frog* f = dynamic_cast<Frog*>(obj)) {
		return true;
	}

	return false;
}

GameLogic::~GameLogic() {
	textures->clear();
	delete textures;
	delete objectManager;
	delete frog;
}