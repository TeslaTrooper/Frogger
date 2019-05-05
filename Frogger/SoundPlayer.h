#ifndef SOUND_PLAYER
#define SOUND_PLAYER

#define SOUND_EXTRA_FROG		1
#define SOUND_FROG_COLLECTED	2
#define SOUND_HOP				3
#define SOUND_PLUNK				4
#define SOUND_SQUASH			5
#define SOUND_TIME				6

#include <SoundDriver.h>
#include "Util.h"

class SoundPlayer {

	SoundDriver soundDriver;

	float elapsedTime;

public:

	SoundPlayer();

	void update(float dt);

	void playExtraFrog() const;
	void playFrogCollected() const;
	void playHop() const;
	void playPlunk() const;
	void playSquash() const;
	void playTime() const;
};

#endif SOUND_PLAYER
