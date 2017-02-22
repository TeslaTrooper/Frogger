#ifndef FONT_MANAGER
#define FONT_MANAGER

#include "Label.h"

using namespace std;

/*
	Diese Klasse verwaltet alle Labels und stellt unterschiedliche Operationen bereit, um Labels zu erstellen und zu konfigurieren.
*/
class FontManager {
	map<string, Label*> labels;

	typedef map<string, Label*>::iterator it_type;
public:
	FontManager();
	~FontManager();

	/*
		Erstellt ein neues Label mit Text.
		@param identifier ist der Name, �ber den das Label identifiziert werden kann.
		@param text ist der Text, der f�r das label verwendet werden soll.
	*/
	void createNewLabel(string identifier, string text);


	/*
		Erstellt ein neues Label mit Text, Position und Schriftgr��e.
		@param identifier ist der Name, �ber den das Label identifiziert werden kann.
		@param text ist der Text, der f�r das label verwendet werden soll.
		@param position ist die Position, die das Label erhalten soll.
		@param useAsDescription gibt an, dass das Label aus zwei teilen besteht:
				- Einem beschreibenden Text, der sich nicht �ndert und
				- einem Wert, der ver�ndert werden kann.
		@param scale gibt die Schriftgr��e an. Dabei ist der Wert 1.0f die originale Gr��e.
			   Ein kleinerer Wert, verkleinert auch die Schrift.
	*/
	void createNewLabel(string identifier, string text, Vec2 position, bool useAsDescription, float scale);


	/*
		Setzt den Text eines Label neu.
		@param identifier ist der Name des Labels, f�r das der Text ge�ndert werden soll.
		@param text ist der neue Text.
	*/
	void setText(string identifier, string text);


	/*
		L�sst das Label verschwinden.
		@param identifier ist der Name des Labels, das ausgeblendet werden soll.
	*/
	void hideLabel(string identifier);


	/*
		Zeigt das Label an.
		@param identifier ist der Name des Labels, das angezeigt werden soll.
	*/
	void showLabel(string identifier);


	/*
		Pr�ft, ob das Label sichtbar ist, oder nicht
		@param identifier ist der Name des Labels, das gepr�ft werden soll.
		@return gibt true zur�ck, wenn das Label sichtbar ist.
	*/
	bool isVisible(string identifier);


	/*
		Setzt die Position eines Labels.
		@param identifier ist der Name des Labels, f�r das die Position gesetzt werden soll.
		@param position ist die neue Position f�r das Label.
	*/
	void setPosition(string identifier, Vec2 position);


	/*
		Diese Funktion erm�glicht das Verschwinden eines Labels nach einer bestimmten Zeit.
		@param identifier ist der Name des Labels, f�r das die Konfiguration gilt.
		@param duration ist der Zeitwert in Sekunden, nach dem das Label wieder verschwinden soll.
	*/
	void hideAfter(string identifier, float duration);


	/*
		Konfiguriert den Beschreibenden Text eines Labels hinsichtlich der Position.
		@param identifier ist der Name des Labels, f�r das die Konfiguration gilt.
		@param value gibt an, ob der beschreibende Text links ausgerichtet sein soll.
	*/
	void alignDescriptionLeft(string identifier, bool value);


	/*
		Diese Funktion setzt den beschreibenden Text als statisch. D.h. die Funcktion
		setText(...) �ndert den beschreibenden Text nicht.
		@param identifier ist der Name des Labels, f�r das die Konfiguration gilt.
	*/
	void useStaticLabel(string identifier);


	/*
		Setzt die Schriftgr��e eines Labels.
		@param identifier ist der Name des Labels, f�r das die Schriftgr��e gesetzt werden soll.
	*/
	void setScale(string identifier, float scale);


	/*
		@return gibt die Schriftgr��e eines Labels zur�ck.
	*/
	float getScale(string identifier);


	/*
		@return gibt die Anzahl an Zeichen eines Labels zur�ck.
	*/
	int getLength(string identifier);


	/*
		�ber diese Funktion werden alle Timer, die �ber die Funktion hideAfter(...)
		konfiguriert wurden, aktualisiert.
		@param dt ist die vergangene Zeit.
	*/
	void update(float dt);


	/*
		Diese Funktion liefert alle Informationen zum Zeichnen aller Labels.
		@return gibt eine Liste aller Labels mit Drawables zur�ck.
	*/
	vector<Drawable> getDrawables();
};

#endif FONT_MANAGER