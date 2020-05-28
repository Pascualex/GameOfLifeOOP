#include "Auxiliar/Auxiliar.h"
#include <algorithm>

IntVector2D Auxiliar::directions = {
	{ 0,  1},
	{ 1,  0},
	{ 0, -1},
	{-1,  0}
};

IntVector2D Auxiliar::all_directions = {
	{ 0,  1},
	{ 1,  1},
	{ 1,  0},
	{ 1, -1},
	{ 0, -1},
	{-1, -1},
	{-1,  0},
	{-1,  1}
};

IntVector2D Auxiliar::random_directions() {
	std::random_shuffle(directions.begin(), directions.end());
	return directions;
}

IntVector2D Auxiliar::all_random_directions() {
	std::random_shuffle(all_directions.begin(), all_directions.end());
	return all_directions;
}