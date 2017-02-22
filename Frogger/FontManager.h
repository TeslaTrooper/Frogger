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
		@param identifier ist der Name, über den das Label identifiziert werden kann.
		@param text ist der Text, der für das label verwendet werden soll.
	*/
	void createNewLabel(string identifier, string text);


	/*
		Erstellt ein neues Label mit Text, Position und Schriftgröße.
		@param identifier ist der Name, über den das Label identifiziert werden kann.
		@param text ist der Text, der für das label verwendet werden soll.
		@param position ist die Position, die das Label erhalten soll.
		@param useAsDescription gibt an, dass das Label aus zwei teilen besteht:
				- Einem beschreibenden Text, der sich nicht ändert und
				- einem Wert, der verändert werden kann.
		@param scale gibt die Schriftgröße an. Dabei ist der Wert 1.0f die originale Größe.
			   Ein kleinerer Wert, verkleinert auch die Schrift.
	*/
	void createNewLabel(string identifier, string text, Vec2 position, bool useAsDescription, float scale);


	/*
		Setzt den Text eines Label neu.
		@param identifier ist der Name des Labels, für das der Text geändert werden soll.
		@param text ist der neue Text.
	*/
	void setText(string identifier, string text);


	/*
		Lässt das Label verschwinden.
		@param identifier ist der Name des Labels, das ausgeblendet werden soll.
	*/
	void hideLabel(string identifier);


	/*
		Zeigt das Label an.
		@param identifier ist der Name des Labels, das angezeigt werden soll.
	*/
	void showLabel(string identifier);


	/*
		Prüft, ob das Label sichtbar ist, oder nicht
		@param identifier ist der Name des Labels, das geprüft werden soll.
		@return gibt true zurück, wenn das Label sichtbar ist.
	*/
	bool isVisible(string identifier);


	/*
		Setzt die Position eines Labels.
		@param identifier ist der Name des Labels, für das die Position gesetzt werden soll.
		@param position ist die neue Position für das Label.
	*/
	void setPosition(string identifier, Vec2 position);


	/*
		Diese Funktion ermöglicht das Verschwinden eines Labels nach einer bestimmten Zeit.
		@param identifier ist der Name des Labels, für das die Konfiguration gilt.
		@param duration ist der Zeitwert in Sekunden, nach dem das Label wieder verschwinden soll.
	*/
	void hideAfter(string identifier, float duration);


	/*
		Konfiguriert den Beschreibenden Text eines Labels hinsichtlich der Position.
		@param identifier ist der Name des Labels, für das die Konfiguration gilt.
		@param value gibt an, ob der beschreibende Text links ausgerichtet sein soll.
	*/
	void alignDescriptionLeft(string identifier, bool value);


	/*
		Diese Funktion setzt den beschreibenden Text als statisch. D.h. die Funcktion
		setText(...) ändert den beschreibenden Text nicht.
		@param identifier ist der Name des Labels, für das die Konfiguration gilt.
	*/
	void useStaticLabel(string identifier);


	/*
		Setzt die Schriftgröße eines Labels.
		@param identifier ist der Name des Labels, für das die Schriftgröße gesetzt werden soll.
	*/
	void setScale(string identifier, float scale);


	/*
		@return gibt die Schriftgröße eines Labels zurück.
	*/
	float getScale(string identifier);


	/*
		@return gibt die Anzahl an Zeichen eines Labels zurück.
	*/
	int getLength(string identifier);


	/*
		Über diese Funktion werden alle Timer, die über die Funktion hideAfter(...)
		konfiguriert wurden, aktualisiert.
		@param dt ist die vergangene Zeit.
	*/
	void update(float dt);


	/*
		Diese Funktion liefert alle Informationen zum Zeichnen aller Labels.
		@return gibt eine Liste aller Labels mit Drawables zurück.
	*/
	vector<Drawable> getDrawables();
};

#endif FONT_MANAGER