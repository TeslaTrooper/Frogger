#ifndef MAT3
#define MAT3

#include <array>
#include "Vec2.h"

using namespace std;

class Mat3 {
	array<array<float, 3>, 3> elements;

public:

	/*
		Erzeugt eine 3x3 Einheitsmatrix.
	*/
	Mat3();


	/*
		Erzeugt eine 3x3 Matrix mit den gegeben Elementen.
	*/
	Mat3(array<array<float, 3>, 3> elements);


	/*
		Erzeugt eine Translationsmatrix.
		@param vec ist der Vektor, der die Translation angibt.
		@return gibt die Translationsmatrix zurück.
	*/
	Mat3 translate(Vec2 vec);


	/*
		Erzeugt eine Skalierungsmatrix.
		@param vec ist der Vektor, der die Skalierung angibt.
		@return gibt die Skalierungsmatrix zurück.
	*/
	Mat3 scale(Vec2 vec);


	/*
		@return gibt den Pointer, der auf das 1. Element zeigt, zurück.
	*/
	static const float* ptr(Mat3 mat);

	~Mat3();
};

#endif MAT3