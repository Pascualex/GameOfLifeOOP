#include "Spawner.h"
#include <stdexcept>

Spawner::Spawner(Agent *agent, int interval, int first_step, bool random, bool force) {
	if (agent == NULL) throw std::invalid_argument("Spawner (constructor): agent can't be null");
	if (interval < 0) throw std::invalid_argument("Spawner (constructor): interval can't be negative");
	if (first_step <= 0) throw std::invalid_argument("Spawner (constructor): initial delay must be higher than zero");
	this->agent = agent;
	this->board = NULL;
	this->steps_until_spawn = first_step;
	this->interval = interval;
	this->random = random;
	this->force = force;
}

Spawner::~Spawner() {
	delete this->agent;
}

void Spawner::set_board(Board *board) {
	this->board = board;
}

void Spawner::step() {
	if (board == NULL) throw std::logic_error("Spawner (step): board can't be null");

	steps_until_spawn--;
	if (steps_until_spawn == 0 && (force || board->is_empty_at(agent->getX(), agent->getY()))) {
		spawn();
		steps_until_spawn = interval;
	}
}

void Spawner::spawn() {
	if (random) {
		int x = rand() % board->get_width();
		int y = rand() % board->get_height();
		agent->clone(x, y)->spawn_in_board(board);
	} else {
		agent->clone()->spawn_in_board(board);
	}
}