#pragma once

#include <vector>

typedef std::vector<std::vector<int>> IntVector2D;

class Auxiliar {
private:
	static IntVector2D directions;
	static IntVector2D all_directions;
public:
	static IntVector2D random_directions();
	static IntVector2D all_random_directions();
};