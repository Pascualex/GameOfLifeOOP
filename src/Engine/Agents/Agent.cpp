#include "Engine/Agents/Agent.h"
#include "Engine/Board.h"
#include <stdexcept>

Agent::Agent(int x, int y) {
	this->x = x;
	this->y = y;
	dead = false;
	board = NULL;
}

int Agent::getX() {
	return x;
}

int Agent::getY() {
	return y;
}

bool Agent::step() {
	if (dead) return false;
	return true;
}

bool Agent::is_dead() {
	return dead;
}

void Agent::spawn_in_board(Board *board) {
	if (this->board != NULL) {
		throw std::logic_error("Agent (spawn): can only be spawned once");
	}

	if (board == NULL) {
		throw std::invalid_argument("Agent (spawn): board can't be null");
	}

	board->spawn_agent_at(x, y, this);

	this->board = board;
}

void Agent::kill() {
	board->kill_agent_at(x, y);
	dead = true;
}

void Agent::move_to(int x, int y) {
	if (this->board == NULL) {
		throw std::logic_error("Agent (move_to): can only move once spawned");
	}

	if (x < 0 || x >= board->get_width() || y < 0 || y >= board->get_height()) {
		throw std::invalid_argument("Agent (move_to): x and y must be inside the board");
	}

	board->move_agent_from_to(this->x, this->y, x, y);

	this->x = x;
	this->y = y;
}