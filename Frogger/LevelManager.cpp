#include "LevelManager.h"

LevelManager::LevelManager() {
	reset();
}

map<Objects, int> LevelManager::getObjects() {
	if (!dataIsUpToDate)
		throw "Data is deprecated! Call initData() before.";

	map<Objects, int> objects = map<Objects, int>();

	map<Objects, int>::iterator it;
	for (it = objectProbabilities.begin(); it != objectProbabilities.end(); it++) {
		Objects type = it->first;
		int probability = it->second;

		if (!random(probability))
			continue;

		int randomRow;

		if (type == Objects::INSECT && insectXPos > 0)
			continue;

		randomRow = calculateRow(type);

		objects[type] = randomRow;
	}

	dataIsUpToDate = false;

	return objects;
}

void LevelManager::reset() {
	objectProbabilities[Objects::CROCODILE] = 20;
	objectProbabilities[Objects::INSECT] = 10;
	objectProbabilities[Objects::SNAKE] = 20;
	objectProbabilities[Objects::FEMALE_FROG] = 50;

	dataIsUpToDate = false;
}

vector<int> LevelManager::setLevel(int level) {
	this->currentLevel = level;

	switch (this->currentLevel) {
		case 2: {
			objectProbabilities[Objects::FEMALE_FROG] = 5;
			objectProbabilities[Objects::INSECT] = 5;
		}; break;
		case 3: {
			objectProbabilities[Objects::FEMALE_FROG] = 8;
			objectProbabilities[Objects::INSECT] = 8;
			objectProbabilities[Objects::SNAKE] = 5;
		}; break;
		case 4: {
			objectProbabilities[Objects::FEMALE_FROG] = 12;
			objectProbabilities[Objects::INSECT] = 12;
			objectProbabilities[Objects::SNAKE] = 10;
			objectProbabilities[Objects::CROCODILE] = 5;
		}; break;
		case 5: {
			objectProbabilities[Objects::FEMALE_FROG] = 20;
			objectProbabilities[Objects::INSECT] = 15;
			objectProbabilities[Objects::SNAKE] = 20;
			objectProbabilities[Objects::CROCODILE] = 10;
		}; break;
	}

	return increaseSpeed();
}

void LevelManager::initData(bool ocupiedPools[], float insectXPos) {
	for (int i = 0; i < POOLS_COUNT; i++) {
		this->ocupiedPools[i] = ocupiedPools[i];
	}
	this->insectXPos = insectXPos;

	dataIsUpToDate = true;
}

int LevelManager::calculateRow(Objects type) {
	int randomRow;

	switch (type) {
	case Objects::FEMALE_FROG: randomRow = randomNumber(8, 12); break;
	case Objects::CROCODILE: randomRow = 12; break;
	case Objects::INSECT: {
		randomRow = randomNumber(0, 4);

		while (ocupiedPools[randomRow]) {
			randomRow = randomNumber(0, 4);
		}
	}; break;
	case Objects::SNAKE: {
		randomRow = randomNumber(8, 12);
		while (randomRow == 11) {
			randomRow = randomNumber(8, 12);
		}
	}; break;
	}

	return randomRow;
}

vector<int> LevelManager::increaseSpeed() {
	vector<int> rows = vector<int>(2);

	rows.push_back(randomNumber(2, 6));
	rows.push_back(randomNumber(8, 12));

	return rows;
}