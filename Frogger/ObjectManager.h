#ifndef OBJECT_MANAGER
#define OBJECT_MANAGER

#include <vector>
#include <map>

#include "Constants.h"
#include "GameObject.h"

using namespace std;

class ObjectManager {

protected:
	typedef map<int, vector<GameObject*>*>::iterator it_type;
	map<int, vector<GameObject*>*>* rowObjMap;

	const map<Objects, GameObject::Initializer> objDefinitions = {
		{ Objects::CAR_YELLOW,
			{ Vec2(-30.0f, 0.0f), new Texture("../textures/carRed.jpg"), { Event::COLL_LETHAL_OBJECTS, Vec2(0.0f, 0.0f) } }
		},
		{ Objects::CAR_WHITE,
			{ Vec2(80.0f, 0.0f), new Texture("../textures/carOrange.jpg"), { Event::COLL_LETHAL_OBJECTS, Vec2(0.0f, 0.0f) } }
		},
		{ Objects::CAR_PINK,
			{ Vec2(-45.0f, 0.0f), new Texture("../textures/carYellow.jpg"), { Event::COLL_LETHAL_OBJECTS, Vec2(0.0f, 0.0f) } }
		},
		{ Objects::TRUCK,
			{ Vec2(-60.0f, 0.0f), new Texture("../textures/truck.jpg"), { Event::COLL_LETHAL_OBJECTS, Vec2(0.0f, 0.0f) } }
		},
		{ Objects::HARVESTER,
			{ Vec2(50.0f, 0.0f), new Texture("../textures/carWhite.jpg"), { Event::COLL_LETHAL_OBJECTS, Vec2(0.0f, 0.0f) } }
		},
		{ Objects::LARGE_TREE,
			{ Vec2(90.0f, 0.0f), new Texture("../textures/stammLarge.jpg"), { Event::COLL_TREE_TURTLE, Vec2(90.0f, 0.0f) } }
		},
		{ Objects::MEDIUM_TREE,
			{ Vec2(60.0f, 0.0f), new Texture("../textures/stammMedium.jpg"), { Event::COLL_TREE_TURTLE, Vec2(60.0f, 0.0f) } }
		},
		{ Objects::SMALL_TREE,
			{ Vec2(40.0f, 0.0f), new Texture("../textures/stammSmall.jpg"), { Event::COLL_TREE_TURTLE, Vec2(40.0f, 0.0f) } }
		},
		{ Objects::TWO_ELEMENT_CHAIN,
			{ Vec2(-50.0f, 0.0f), new Texture("../textures/smallTurtleChain.jpg"), { Event::COLL_TREE_TURTLE, Vec2(-50.0f, 0.0f) } }
		},
		{ Objects::THREE_ELEMENT_CHAIN,
			{ Vec2(-50.0f, 0.0f), new Texture("../textures/largeTurtleChain.jpg"), { Event::COLL_TREE_TURTLE, Vec2(-50.0f, 0.0f) } }
		}
	};

public:
	ObjectManager();
	~ObjectManager();

	Vec2 alignInRow(int row, bool centered);
	int getRowCount() { return rowObjMap->size(); };
	vector<GameObject*> getAll();
	void increaseSpeedInRow(int row);
	vector<GameObject*>* getObjects(int row) { return rowObjMap->at(row); };
	vector<Drawable> getDrawables();

	void createObject(int row, Objects objType, int count, int space, int startX);

};

#endif OBJECT_MANAGER