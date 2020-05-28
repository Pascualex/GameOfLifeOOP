#pragma once

#include "Agent.h"
#include "Spawner.h"
#include "Board.h"
#include <vector>
#include <queue>
#include <utility>
#include <chrono>

typedef std::pair<int, Agent *> DelayedSpawn;

class Engine {
private:
	std::chrono::system_clock::duration step_duration;
	int current_step;
	std::chrono::time_point<std::chrono::system_clock> next_step_time;
	bool stop_called;
	std::priority_queue<DelayedSpawn, std::vector<DelayedSpawn>, std::greater<DelayedSpawn>> delayed_spawns;
	std::vector<Spawner *> spawners;
	Board board;
	void step();
	void check_delayed_spawns();
	void check_spawners();
	void print_frame();
public:
	Engine(int width, int height, std::chrono::system_clock::duration step_duration);
	~Engine();
	void run();
	void spawn_agent(Agent *agent, int delay = 0);
	void add_spawner(Spawner *spawner);
	void stop();
};