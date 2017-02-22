#ifndef LABEL
#define LABEL

#include "Util.h"

using namespace std;
using namespace util;

class Label {
	static map<char, util::Rectangle>* charCollection;

	vector<util::Rectangle>* chars;
	vector<Vec2>* charPositions;

	string descriptionText;

	float scale = 1.0f;
	float duration, durationValue;

	Vec2 position;

	void alignPosition();
	Vec2 getSize(int index);

	bool visible, descriptionLeftAligned, isStaticLabel;

public:

	/*
		Erzeugt ein neue Instanz der Klasse mit einem Text.
		@param text ist der Text, der f�r das label verwendet werden soll.
		@param useAsDescription gibt an, ob der Text ein beschreibender Text ist.
	*/
	Label(string text, bool useAsDescription);

	~Label();


	/*
		Setzt die Position des Labels.
		@param die neue Position.
	*/
	void setPosition(Vec2 position);


	/*
		@return gibt die aktuelle Position des Labels zur�ck.
	*/
	Vec2 getPosition();


	/*
		@return gibt eine Liste von Drawables aller Schriftzeichen zur�ck.
	*/
	vector<Drawable> getDrawables();


	/*
		@return gibt die Anzahl an Schriftzeichen zur�ck.
	*/
	int getLength();
	

	/*
		@param scale ist die Schriftgr��e.
	*/
	void setScale(float scale);


	/*
		@param text ist der neue Text des Labels.
	*/
	void setText(string text);


	/*
		L�sst das Label verschwinden.
	*/
	void hide() {this->visible = false;};


	/*
		Zeigt das Label an.
	*/
	void show() { this->visible = true; };


	/*
		@return gibt true zur�ck, wenn das Label sichtbar ist.
	*/
	bool isVisible() { return this->visible; };


	/*
		Setzt die Dauer, nach der das Label automatisch verschwinden soll.
		@param die Dauer in Sekunden.
	*/
	void hideAfter(float duration);


	/*
		@return gibt true zur�ck, wenn f�r dieses Label ein Timer konfiguriert wurde.
	*/
	bool isAutoHiding() { return durationValue > 0; };


	/*
		Richtet den beschreibenden Text aus.
		@param f�r true, wird der Text links ausgerichtet.
	*/
	void alignDescriptionLeft(bool value) { this->descriptionLeftAligned = value; };


	/*
		@return gibt die Schriftgr��e zur�ck.
	*/
	float getScale() { return this->scale; };


	/*
		Setzt den beschreibenden Text, sodass dieser bei setText(...) nicht �berschrieben wird.
	*/
	void useStaticLabel();


	/*
		Aktualisiert den konfigurierten Timer.
	*/
	void update(float dt);

	static map<char, util::Rectangle>* initTextures();
};

#endif LABEL