#pragma once

#include "Engine/Agents/Agent.h"
#include "Engine/Board.h"

class Spawner {
private:
	Agent *agent;
	Board *board;
	int steps_until_spawn;
	int interval;
	bool random;
	bool force;
	void spawn();
public:
	Spawner(Agent *agent, int interval, int first_step = 1, bool random = false, bool force = true);
	~Spawner();
	void set_board(Board *board);
	void step();
};