#ifndef CONTROLLER
#define CONTROLLER

#include <BaseController.h>
#include "Game.h"

class Controller : public BaseController {

	Game* const game;

public:

	Controller(BaseRenderer* const renderer, Game* const game);

	void checkInput(float dt) override;

};

#endif CONTROLLER