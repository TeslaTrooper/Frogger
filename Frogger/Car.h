#ifndef CAR
#define CAR

#include "GameObject.h"
#include "CarType.h"

class Car : public GameObject {

	void initCar(vec2 movement, Texture* texture);

public:
	Car(CarType carType, vec2 position, vec3 color);

	~Car();

	void doLogic(GLfloat dt);
	Rectangle getCriticalHitBox();
};

#endif CAR