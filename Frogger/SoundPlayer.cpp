#include "SoundPlayer.h"

SoundPlayer::SoundPlayer() : elapsedTime(0) {
	soundDriver.load(SOUND_EXTRA_FROG, SoundFiles::extraFrog);
	soundDriver.load(SOUND_FROG_COLLECTED, SoundFiles::frogCollected);
	soundDriver.load(SOUND_HOP, SoundFiles::hop);
	soundDriver.load(SOUND_PLUNK, SoundFiles::plunk);
	soundDriver.load(SOUND_SQUASH, SoundFiles::squash);
	soundDriver.load(SOUND_TIME, SoundFiles::time);
}

void SoundPlayer::update(float dt) {
	this->elapsedTime += dt;
}

void SoundPlayer::playExtraFrog() const {
	soundDriver.play(SOUND_EXTRA_FROG, PLAY_MODE_ONCE, false);
}

void SoundPlayer::playFrogCollected() const {
	soundDriver.play(SOUND_FROG_COLLECTED, PLAY_MODE_ONCE, false);
}

void SoundPlayer::playHop() const {
	soundDriver.play(SOUND_HOP, PLAY_MODE_ONCE, true);
}

void SoundPlayer::playPlunk() const {
	soundDriver.play(SOUND_PLUNK, PLAY_MODE_ONCE, false);
}

void SoundPlayer::playSquash() const {
	soundDriver.play(SOUND_SQUASH, PLAY_MODE_ONCE, false);
}

void SoundPlayer::playTime() const {
	soundDriver.play(SOUND_TIME, PLAY_MODE_ONCE, false);
}