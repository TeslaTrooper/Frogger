#ifndef VEC2
#define VEC2

#include <math.h>

class Vec2 {

public:
	/*
		Ist die x-Komponente des Vektors.
	*/
	float x;


	/*
		Ist die y-Komponente des Vektors.
	*/
	float y;


	/*
		Erzeugt einen neuen Vektor.
	*/
	Vec2();


	/*
		Erzeugt einen neuen Vektor.
		@param x ist die x-Komponente.
		@param y ist die x-Komponente.
	*/
	Vec2(float x, float y);

	~Vec2();


	/*
		Addiert zu diesem Vektor einen anderen Vektor.
		@pararm der Vektor, um den addiert wird.
		@return gibt die Summe aus beiden Vektoren zur�ck.
	*/
	Vec2 add(Vec2 vec);


	/*
		Subtrahiert von diesem Vektor einen anderen Vektor.
		@pararm der Vektor, um den subtrahiert wird.
		@return gibt die Differenz aus beiden Vektoren zur�ck.
	*/
	Vec2 sub(Vec2 vec);


	/*
		Multipliziert von diesem Vektor um einen anderen Vektor.
		@pararm der Vektor, um den multipliziert wird.
		@return gibt das Produkt aus beiden Vektoren zur�ck.
	*/
	Vec2 mul(float scalar);


	/*
		L�scht alle Elemente des Vektors.
	*/
	void clear();


	/*
		F�hrt eine 2D-Rotation durch. Dabei wird dieser Vektor als Startpunkt verwedent.
		@param vec ist der Zielpunkt, auf den der neue Vektor zeigen soll.
		@length gibt die L�nge des neuen Vektors an.
		@return gibt einen Vektor zur�ck, der auf vec zeigt und die gegebene L�nge besitzt.
	*/
	Vec2 rotateTo(Vec2 vec, float length);


	/*
		@return gibt den normierten Vektor zur�ck.
	*/
	Vec2 norm();


	/*
		@return gibt die L�nge des Vektors zur�ck.
	*/
	float length();


	/*
		Vergleicht die xy-Komponenten zweier Vektoren auf Gleichheit.
		@return gibt true zur�ck, wenn die Komponenten gleich sind.
	*/
	bool operator==(const Vec2& vec) {
		return vec.x == x && vec.y == y;
	};

};

#endif VEC2