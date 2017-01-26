#pragma once

#include "tools/Point.h"
#include "tools/WithSmartPtr.h"

class Game;
class GameState;

template<class T>
class EntityState : public WithSmartPtr<EntityState<T>>
{
public:
	EntityState(void) {}
	~EntityState(void) {}

	virtual void init(T& parent) = 0;
	virtual void free(T& parent) = 0;
	virtual void update(T& parent, GameState& state, const Game& game, unsigned int elapsedTime) = 0;
};
