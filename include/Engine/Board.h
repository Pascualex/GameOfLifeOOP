#pragma once

#include <vector>
#include <string>

class Agent;

class Board {
private:
	std::vector<std::vector<Agent *>> grid;
	std::vector<Agent *> agents;
public:
	Board(int width, int height);
	~Board();
	int get_width();
	int get_height();
	std::vector<Agent *> *get_agents();
	void spawn_agent_at(int x, int y, Agent *agent);
	void move_agent_from_to(int from_x, int from_y, int to_x, int to_y);
	void kill_agent_at(int x, int y);
	bool check_valid_coordinates(int x, int y);
	std::string get_type_at(int x, int y);
	bool is_empty_at(int x, int y);
	void clear_killed();
	void print();
};