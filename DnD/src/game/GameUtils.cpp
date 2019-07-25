#include "GameUtils.h"

#include <cmath>

GameUtils::GameUtils()
{
}


GameUtils::~GameUtils()
{
}

int GameUtils::getDistanceTo(const Point<int>& pos1, const Point<int>& pos2)
{
	return	std::abs(pos1.x - pos2.x) + std::abs(pos1.y - pos2.y);
}

double GameUtils::getEuclideanDistanceTo(const Point<int>& pos1, const Point<int>& pos2)
{
	return	std::sqrt(std::pow(pos1.x - pos2.x, 2) + std::pow(pos1.y - pos2.y, 2));
}