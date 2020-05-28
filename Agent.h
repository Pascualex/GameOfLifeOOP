#pragma once

#include <string>

class Board;

class Agent {
protected:
	int x;
	int y;
	bool dead;
	Board *board;
public:
	Agent(int x, int y);
	virtual bool step();
	int getX();
	int getY();
	virtual char get_icon() = 0;
	virtual std::string get_type() = 0;
	bool is_dead();
	void spawn_in_board(Board *board);
	void move_to(int x, int y);
	void kill();
	virtual Agent *clone() = 0;
	virtual Agent* clone(int x, int y) = 0;
};