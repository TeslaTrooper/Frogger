#ifndef UTIL
#define UTIL

#include <string>
#include <map>
#include <vector>

#include "Vec2.h"
#include "Constants.h"
#include "Mat4.h"
#include "Mat3.h"

using namespace std;

#define CALC_PIXEL_RGB(data,pixel) {\
pixel[0] = (((data[0] - 33) << 2) | ((data[1] - 33) >> 4)); \
pixel[1] = ((((data[1] - 33) & 0xF) << 4) | ((data[2] - 33) >> 2)); \
pixel[2] = ((((data[2] - 33) & 0x3) << 6) | ((data[3] - 33))); \
data += 4; \
}

namespace util {
	/*
		Enth�lt alle Events, die im Program unterschieden werden m�ssen.
	*/
	enum Event {
		ARROW_KEYS,
		TIME_OUT,
		TARGET_POSITION_REACHED,
		DIE_SEQUENCE_EXPIRED,
		COLL_TREE_TURTLE,
		COLL_LETHAL_OBJECTS,
		COLL_NONE,
		NEUTRAL,
		COLL_POOL,
		START_MOVING,
		COLLECTING,
		COLL_INSECT,
		RESET,
		START_DIVING,
		DESCENDING_FINISHED,
		TURNING_UP_FINISHED
	};


	/*
		Stellt eine Menge von m�glichen Richtungen dar, die ein Objekt haben kann.
	*/
	enum Direction {
		LEFT,
		UP,
		RIGHT,
		DOWN,
		NONE
	};


	/*
		Enth�lt alle Objekttypen, die die Logik unterscheiden muss.
	*/
	enum Objects {
		CAR_YELLOW,
		CAR_WHITE,
		CAR_RED,
		TRUCK,
		CAR_ORANGE,
		LARGE_TREE,
		MEDIUM_TREE,
		SMALL_TREE,
		TWO_ELEMENT_CHAIN,
		THREE_ELEMENT_CHAIN,
		PLAYER,
		FEMALE_FROG,
		SNAKE,
		FROG_CARRIYING,
		CROCODILE,
		CROCODILE_BODY,
		CROCODILE_HEAD,
		INSECT
	};


	/*
		Enth�lt alle Zust�nde, in denen ein Objekt sein kann.
	*/
	enum State {
		IDLE,
		MOVING,
		TRANSPORTING_RIGHT,
		TRANSPORTING_LEFT,
		TRANSPORT,
		MOVE_TRANSPORT,
		CARRYING,
		DIEING,
		KILLED,
		ALIGNING,
		NAVIGATING,
		INACTIVE,
		COLLECTED,
		DESCENDING,
		DIVING,
		TURNING_UP
	};


	/*
		Kategorisiert die Menge an Drawables.
	*/
	enum DrawableType {
		OBJECT,
		FONT
	};


	/*
		Stellt ein Rechteck mit Position und Gr��e dar.
	*/
	struct Rectangle {
		Vec2 position;
		Vec2 size;

		bool operator==(const Rectangle& rect) {
			return position == rect.position && size == rect.size;
		}
	};

	struct Drawable {
		Mat4 transformation;
		Rectangle textureRegion;
	};


	/*
		Definiert Auswirkungen bei einer Kollision zweier Objekte.
		effect gibt an, was bei einer Kollision hinsichtlich der Spielogik
		passieren soll.
		movement gibt in Abh�ngigkeit von effect an, in wie weit die Kollision
		Auswirkungen auf den aktuellen Bewegungsvektor hat.
	*/
	struct CollisionInfo {
		Event effect;
		int priority;

		bool operator==(const CollisionInfo& collInfo) {
			return collInfo.effect == effect &&
				collInfo.priority == priority;
		}
	};


	/*
		Abstrahiert die f�r die Objektinteraktion relevanten Daten.
	*/
	struct ObjectInfo {
		Rectangle textureRegion;
		Rectangle hitBox;
		Vec2 movement;
		CollisionInfo collisionInfo;

		bool operator==(const ObjectInfo& objInfo) {
			return collisionInfo == objInfo.collisionInfo &&
				movement == objInfo.movement &&
				hitBox == objInfo.hitBox &&
				textureRegion == objInfo.textureRegion;
		}
	};


	/*
		Enth�lt zu einer ObjectInfo noch die Reihe, in der sich das Objekt befindet.
	*/
	struct OpponentInfo {
		Objects objectType;
		int row;
	};


	/*
		Enth�lt zu einer ObjectInfo noch die Info, ob der Pool bereits besetzt ist.
	*/
	struct Pool {
		ObjectInfo objInfo;
		bool ocupied;
	};


	/*
		Stellt einen �bergang im Zustandsautomaten dar.
	*/
	struct TransitionElement {
		State currentState;
		Event transitionUnit;
		State newState;
	};


	/*
		Weist jeder Richtung aus Direction einen Vektor zu.
	*/
	const map<Direction, Vec2> directions = {
		{ Direction::LEFT, Vec2(-1.0f, 0.0f) },
		{ Direction::UP, Vec2(0.0f, -1.0f) },
		{ Direction::RIGHT, Vec2(1.0f, 0.0f) },
		{ Direction::DOWN, Vec2(0.0f, 1.0f) },
		{ Direction::NONE, Vec2(0.0f, 0.0f) }
	};


	/*
		Texturkoordinaten der Zahlen im Tileset.
	*/
	const map<char, Rectangle> numbers = {
		{ '0',{ Vec2(0, 0), Vec2(1,1) } },
		{ '1',{ Vec2(1, 0), Vec2(1,1) } },
		{ '2',{ Vec2(2, 0), Vec2(1,1) } },
		{ '3',{ Vec2(3, 0), Vec2(1,1) } },
		{ '4',{ Vec2(0, 6), Vec2(1,1) } },
		{ '5',{ Vec2(4, 0), Vec2(1,1) } },
		{ '6',{ Vec2(5, 0), Vec2(1,1) } },
		{ '7',{ Vec2(6, 0), Vec2(1,1) } },
		{ '8',{ Vec2(7, 0), Vec2(1,1) } },
		{ '9',{ Vec2(8, 0), Vec2(1,1) } },
	};


	/*
		Texturkoordinaten aller Buchstaben im Tileset.
	*/
	const map<char, Rectangle> characters = {
		{ 'A',{ Vec2(9, 0), Vec2(1,1) } },
		{ 'B',{ Vec2(0, 1), Vec2(1,1) } },
		{ 'C',{ Vec2(1, 1), Vec2(1,1) } },
		{ 'D',{ Vec2(2, 1), Vec2(1,1) } },
		{ 'E',{ Vec2(3, 1), Vec2(1,1) } },
		{ 'F',{ Vec2(4, 1), Vec2(1,1) } },
		{ 'G',{ Vec2(5, 1), Vec2(1,1) } },
		{ 'H',{ Vec2(6, 1), Vec2(1,1) } },
		{ 'I',{ Vec2(7, 1), Vec2(1,1) } },
		{ 'J',{ Vec2(8, 1), Vec2(1,1) } },
		{ 'K',{ Vec2(9, 1), Vec2(1,1) } },
		{ 'L',{ Vec2(0, 2), Vec2(1,1) } },
		{ 'M',{ Vec2(1, 2), Vec2(1,1) } },
		{ 'N',{ Vec2(2, 2), Vec2(1,1) } },
		{ 'O',{ Vec2(3, 2), Vec2(1,1) } },
		{ 'P',{ Vec2(4, 2), Vec2(1,1) } },
		{ 'Q',{ Vec2(5, 2), Vec2(1,1) } },
		{ 'R',{ Vec2(6, 2), Vec2(1,1) } },
		{ 'S',{ Vec2(7, 2), Vec2(1,1) } },
		{ 'T',{ Vec2(8, 2), Vec2(1,1) } },
		{ 'U',{ Vec2(9, 2), Vec2(1,1) } },
		{ 'V',{ Vec2(0, 3), Vec2(1,1) } },
		{ 'W',{ Vec2(1, 3), Vec2(1,1) } },
		{ 'X',{ Vec2(2, 3), Vec2(1,1) } },
		{ 'Y',{ Vec2(3, 3), Vec2(1,1) } },
		{ 'Z',{ Vec2(4, 3), Vec2(1,1) } },
		{ ' ',{ Vec2(9, 9), Vec2(1,1) } },
	};


	/*
		Texturkoordinaten aller Grafiken im Tileset.
	*/
	const map<Objects, Rectangle> objectTextureRegions = {
		{ CAR_ORANGE,{ Vec2(5, 3), Vec2(1,1) } },
		{ CAR_RED,{ Vec2(6, 3), Vec2(1,1) } },
		{ CAR_WHITE,{ Vec2(7, 3), Vec2(1,1) } },
		{ CAR_YELLOW,{ Vec2(8, 3), Vec2(1,1) } },
		{ TRUCK,{ Vec2(0, 4), Vec2(2,1) } },
		{ PLAYER,{ Vec2(0, 8), Vec2(1,1) } },
		{ LARGE_TREE,{ Vec2(3, 4), Vec2(5,1) } },
		{ TWO_ELEMENT_CHAIN,{ Vec2(8, 4), Vec2(2,1) } },
		{ MEDIUM_TREE,{ Vec2(0, 5), Vec2(4,1) } },
		{ SMALL_TREE,{ Vec2(4, 5), Vec2(3,1) } },
		{ THREE_ELEMENT_CHAIN,{ Vec2(7, 5), Vec2(3,1) } },
		{ FEMALE_FROG,{ Vec2(1, 6), Vec2(1, 1) } },
		{ SNAKE,{ Vec2(7, 6), Vec2(2, 1) } },
		{ FROG_CARRIYING,{ Vec2(9, 6), Vec2(1, 1) } }
	};


	/*
		Enth�lt eine Menge an vordefinierten Initialisierungen f�r unterschiedliche Objekttypen.
	*/
	const map<Objects, ObjectInfo> objectInitializer = {
		{ CAR_ORANGE,{
			objectTextureRegions.at(CAR_ORANGE), Rectangle(), Vec2(SPEED_CAR_ORANGE, 0.0f),{ Event::COLL_LETHAL_OBJECTS, 10 }
		} },
		{ CAR_RED,{
			objectTextureRegions.at(CAR_RED), Rectangle(), Vec2(SPEED_CAR_RED, 0.0f),{ Event::COLL_LETHAL_OBJECTS, 10 }
		} },
		{ CAR_WHITE,{
			objectTextureRegions.at(CAR_WHITE), Rectangle(), Vec2(SPEED_CAR_WHITE, 0.0f),{ Event::COLL_LETHAL_OBJECTS, 10 }
		} },
		{ CAR_YELLOW,{
			objectTextureRegions.at(CAR_YELLOW), Rectangle(), Vec2(SPEED_CAR_YELLOW, 0.0f),{ Event::COLL_LETHAL_OBJECTS, 10 }
		} },
		{ TRUCK,{
			objectTextureRegions.at(TRUCK), Rectangle(), Vec2(SPEED_TRUCK, 0.0f),{ Event::COLL_LETHAL_OBJECTS, 10 }
		} },
		{ LARGE_TREE,{
			objectTextureRegions.at(LARGE_TREE), Rectangle(), Vec2(SPEED_LARGE_TREE, 0.0f),{ Event::COLL_TREE_TURTLE, 5 }
		} },
		{ TWO_ELEMENT_CHAIN,{
			objectTextureRegions.at(TWO_ELEMENT_CHAIN), Rectangle(), Vec2(SPEED_TURTLE, 0.0f),{ Event::COLL_TREE_TURTLE, 5 }
		} },
		{ MEDIUM_TREE,{
			objectTextureRegions.at(MEDIUM_TREE), Rectangle(), Vec2(SPEED_MEDIUM_TREE, 0.0f),{ Event::COLL_TREE_TURTLE, 5 }
		} },
		{ SMALL_TREE,{
			objectTextureRegions.at(SMALL_TREE), Rectangle(), Vec2(SPEED_SMALL_TREE, 0.0f),{ Event::COLL_TREE_TURTLE, 5 }
		} },
		{ THREE_ELEMENT_CHAIN,{
			objectTextureRegions.at(THREE_ELEMENT_CHAIN), Rectangle(), Vec2(SPEED_TURTLE, 0.0f),{ Event::COLL_TREE_TURTLE, 5 }
		} }
	};

	const ObjectInfo EMPTY_OBJECT_INFO = { Rectangle(), Rectangle(), Vec2(),{ Event::COLL_NONE, 0 } };
	const vector<TransitionElement> emptyTransitionSet = {};
};

namespace ModelData {

	const int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	const float vertices[] = {
		// pos			texture
		1.0f, 1.0f,		1.0f, 1.0f, // top right
		1.0f, 0.0f,		1.0f, 0.0f, // bottom right
		0.0f, 0.0f,		0.0f, 0.0f, // bottom left
		0.0f, 1.0f,		0.0f, 1.0f  // top left
	};

	const int sizes[] = {
		2, 2
	};

}

namespace SoundFiles {

	static const char* const extraFrog = "sounds/extraFrog.wav";
	static const char* const frogCollected = "sounds/femaleFrog.wav";
	static const char* const hop = "sounds/hop.wav";
	static const char* const plunk = "sounds/plunk.wav";
	static const char* const squash = "sounds/squash.wav";
	static const char* const time = "sounds/time.wav";

}

bool intersects(util::Rectangle rect1, util::Rectangle rect2);
int randomNumber(int min, int max);
bool random(int probability);

#endif UTIL