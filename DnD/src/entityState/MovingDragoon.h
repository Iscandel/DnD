#pragma once
#include "EntityState.h"

class Dragoon;
class GameState;

class MovingDragoon :
	public EntityState<Dragoon>
{
public:
	MovingDragoon();
	~MovingDragoon();

	void init(Dragoon& parent);
	void free(Dragoon& parent);
	void update(Dragoon& parent, GameState& state, const Game& game, unsigned int elapsedTime);
};

