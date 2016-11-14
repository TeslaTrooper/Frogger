#ifndef OBJECT_MANAGER
#define OBJECT_MANAGER

#include <vector>
#include <map>

#include "Constants.h"
#include "GameObject.h"

class ObjectManager {

protected:
	typedef std::map<int, std::vector<GameObject*>*>::iterator it_type;
	std::map<int, std::vector<GameObject*>*>* rowObjMap;

	const std::map<Objects, GameObject::Initializer> objDefinitions = {
		{ Objects::CAR_YELLOW,
			{ vec2(-30.0f, 0.0f), new Texture("../textures/carRed.jpg"), { Event::COLL_LETHAL_OBJECTS, vec2(0.0f, 0.0f) } } 
		},
		{ Objects::CAR_WHITE,
			{ vec2(80.0f, 0.0f), new Texture("../textures/carOrange.jpg"), { Event::COLL_LETHAL_OBJECTS, vec2(0.0f, 0.0f) } } 
		},
		{ Objects::CAR_PINK,
			{ vec2(-45.0f, 0.0f), new Texture("../textures/carYellow.jpg"), { Event::COLL_LETHAL_OBJECTS, vec2(0.0f, 0.0f) } } 
		},
		{ Objects::TRUCK,
			{ vec2(-60.0f, 0.0f), new Texture("../textures/truck.jpg"), { Event::COLL_LETHAL_OBJECTS, vec2(0.0f, 0.0f) } } 
		},
		{ Objects::HARVESTER,
			{ vec2(50.0f, 0.0f), new Texture("../textures/carWhite.jpg"), { Event::COLL_LETHAL_OBJECTS, vec2(0.0f, 0.0f) } } 
		},
		{ Objects::LARGE_TREE,
			{ vec2(90.0f, 0.0f), new Texture("../textures/stammLarge.jpg"), { Event::COLL_TREE_TURTLE, vec2(90.0f, 0.0f) } } 
		},
		{ Objects::MEDIUM_TREE,
			{ vec2(60.0f, 0.0f), new Texture("../textures/stammMedium.jpg"), { Event::COLL_TREE_TURTLE, vec2(60.0f, 0.0f) } } 
		},
		{ Objects::SMALL_TREE,
			{ vec2(40.0f, 0.0f), new Texture("../textures/stammSmall.jpg"), { Event::COLL_TREE_TURTLE, vec2(40.0f, 0.0f) } }
		},
		{ Objects::TWO_ELEMENT_CHAIN,
			{ vec2(-50.0f, 0.0f), new Texture("../textures/smallTurtleChain.jpg"), { Event::COLL_TREE_TURTLE, vec2(-50.0f, 0.0f) } }
		},
		{ Objects::THREE_ELEMENT_CHAIN,
			{ vec2(-50.0f, 0.0f), new Texture("../textures/largeTurtleChain.jpg"), { Event::COLL_TREE_TURTLE, vec2(-50.0f, 0.0f) } }
		}
	};

public:
	ObjectManager();
	~ObjectManager();

	vec2 alignInRow(int row, bool centered);
	int getRowCount() { return rowObjMap->size(); };
	std::vector<GameObject*> getAll();
	void increaseSpeedInRow(int row);
	std::vector<GameObject*>* getObjects(int row) { return rowObjMap->at(row); };

	void createObject(int row, Objects objType, int count, int space, int startX);

};

#endif OBJECT_MANAGER