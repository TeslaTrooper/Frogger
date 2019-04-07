#ifndef GAME_ENTITY
#define GAME_ENTITY

#include "Entity.h"
#include "StateMachine.h"

class GameEntity : public Entity {

	Vec2 size;
	StateMachine stateMachine;
	Rectangle textureRegion;
	vector<TransitionElement> transitionSet;
	map<Direction, Rectangle> textureSet;

public:

	GameEntity(Vec2 position, const vector<TransitionElement>& transitionSet);
	GameEntity(Vec2 position, map<Direction, Rectangle> textureSet, const vector<TransitionElement>& transitionSet);

	~GameEntity() {};

	virtual void update(const float dt);

	void gotoPreviousState();
	bool doTransition(Event ev);

	bool canCollide() const override;
	bool canCollideWith(const Entity* const e) const override;
	void updateTransformation() override;
	VertexData getVertexData() const override;
	IndexData getTriangulatedIndexData() const override;

	Vec2 getSize() { return size; };
	State getState() { return stateMachine.getState(); };
	Rectangle getTextureRegion() { return this->textureRegion; };
	Drawable getDrawable() { return { getTransformation(), getTextureRegion() }; };

	void setInitialState(State state) { stateMachine.setInitialState(state); };
	void setTextureRegion(Rectangle textureRegion) { this->textureRegion = textureRegion; };

};

#endif GAME_ENTITY