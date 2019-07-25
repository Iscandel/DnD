#pragma once

#include "tools/Point.h"

class GameUtils
{
public:
	GameUtils();
	~GameUtils();

	static int getDistanceTo(const Point<int>& pos1, const Point<int>& pos2);

	static double getEuclideanDistanceTo(const Point<int>& pos1, const Point<int>& pos2);
};

