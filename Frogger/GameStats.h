#ifndef GAME_STATS
#define GAME_STATS

#define TIME 60
#define LIFES 3

#define REMAINING_TIME_MULTIPLIER 10
#define NEXT_LEVEL_BONUS 1000
#define PASSED_ROW_BONUS 10
#define COLLECTING_FROG_BONUS 200
#define COLLECTING_INSECT_BONUS 200

class GameStats {

	struct Values {
		int overAllScore;
		int collectedScore;
		int lastRow;
		int currentPoolIndex;
		float time;
		int remainingTries;
		bool isGameOver;
		float remainingTimeLabelDuration;
		float currentLevelLabelDuration;
		int currentLevel;
		float opponentCreationCounter;
		float insectCounter;

		Values() : overAllScore(0), collectedScore(0), lastRow(1),
			time(TIME), remainingTries(LIFES), isGameOver(false),
			remainingTimeLabelDuration(0), currentLevelLabelDuration(0),
			currentLevel(1), opponentCreationCounter(0), insectCounter(0) {}
	};

	Values values;

	void increaseScore(float value) { values.overAllScore += value; };
	void increaseCollectedScore(float value) { values.collectedScore += value; };

public:

	enum CollectionType {
		INSECT, FEMALE_FROG
	};

	GameStats() {};

	void increaseScoreByCollectedScore() { increaseScore(values.collectedScore); };
	void increaseScoreByRemainingTime() { increaseScore(values.time * REMAINING_TIME_MULTIPLIER); };
	void increaseScoreByNextLevelBonus() { increaseScore(NEXT_LEVEL_BONUS); };
	void increaseScoreByPassedRow() { increaseScore(PASSED_ROW_BONUS); };

	void increaseCollectedScoreBy(CollectionType type) { increaseCollectedScore(type == INSECT ? COLLECTING_INSECT_BONUS : COLLECTING_FROG_BONUS); };
	bool increaseOpponentCounter(float dt) {
		values.opponentCreationCounter += dt;

		if (values.opponentCreationCounter > 1.f) {
			values.opponentCreationCounter = 0;
			return true;
		}

		return false;
	};

	bool increaseInsectCounter(float dt) {
		values.insectCounter += dt;

		if (values.insectCounter > 5.f) {
			values.insectCounter = 0;
			return true;
		}

		return false;
	};

	void decreaseTime(float dt) { values.time -= dt; };
	void setLastRow(int value) { values.lastRow = value; };
	void gameOver() { values.isGameOver = true; };
	void consumeRemainingTry() { values.remainingTries--; };
	void setCurrentPoolIndex(int value) { values.currentPoolIndex = value; };

	bool isGameOver() { return values.isGameOver; };
	int getCurrentLevel() { return values.currentLevel; };
	int getCurrentPoolIndex() { return values.currentPoolIndex; };
	float getTime() { return values.time < 0 ? 0 : values.time; };
	int getRemainingTries() { return values.remainingTries < 0 ? 0 : values.remainingTries; };
	int getScore() { return values.overAllScore; };
	int getLastRow() { return values.lastRow; };
	int getCollectedScore() { return values.collectedScore; };
	float getOpponentCounter() { values.opponentCreationCounter; };
	float getInsectCounter() { values.insectCounter; };

	void reset() {
		values.time = TIME;
		values.collectedScore = 0;
		values.lastRow = 1;
	}
};

#endif GAME_STATS