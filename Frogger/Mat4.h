#ifndef MAT4
#define MAT4

#include <array>
#include "Vec2.h"

using namespace std;

class Mat4 {
	array<array<float, 4>, 4> elements;

public:

	/*
		Erzeugt eine 4x4 Einheitsmatrix.
	*/
	Mat4();


	/*
		Erzeugt eine 4x4 Matrix mit den gegeben Elementen.
	*/
	Mat4(array<array<float, 4>, 4> elements);


	/*
		Erzeugt eine Translationsmatrix.
		@param vec ist der Vektor, der die Translation angibt.
		@return gibt die Translationsmatrix zurück.
	*/
	Mat4 translate(Vec2 vec);


	/*
		Erzeugt eine Skalierungsmatrix.
		@param vec ist der Vektor, der die Skalierung angibt.
		@return gibt die Skalierungsmatrix zurück.
	*/
	Mat4 scale(Vec2 vec);


	/*
		Erzeugt eine orthographische Projektionsmatrix.
		@param left ist linke Rand.
		@param right ist der rechte Rand.
		@param bottom ist der untere Rand.
		@param top ist der obere Rand.
		@param zNear gibt den minimalen Z-Wert an, für den ein Objekt noch sichtbar ist.
		@param zFar gibt den maximalen Z-Wert an, für den ein Objekt noch sichtbar ist.
		@return gibt eine orthographische Projektionsmatrix zurück.
	*/
	static Mat4 ortho(float left, float right, float bottom, float top, float zNear, float zFar);


	/*
		@return gibt den Pointer, der auf das 1. Element zeigt, zurück.
	*/
	static const float* ptr(Mat4 mat);

	~Mat4();
};

#endif MAT4