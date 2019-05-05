#pragma once

#include "GameLogic.h"

class APIFactory {

	static Game* game;

	APIFactory() {}

public:

	static Game* getInstance() {
		static Game* instance = new GameLogic();

		return instance;
	}

};