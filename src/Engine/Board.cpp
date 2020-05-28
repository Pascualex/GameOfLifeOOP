#include "Engine/Board.h"
#include "Engine/Agents/Agent.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>

Board::Board(int width, int height):
grid(height, std::vector<Agent *>(width, NULL)) {
	if (width <= 0) throw std::invalid_argument("Board (constructor): width must be higher that zero");
	if (height <= 0) throw std::invalid_argument("Board (constructor): height must be higher that zero");
}

Board::~Board() {
	for (auto agent : agents) {
		delete agent;
	}
}

int Board::get_width() {
	return (int) grid[0].size();
}

int Board::get_height() {
	return (int) grid.size();
}

std::vector<Agent *> *Board::get_agents() {
	return &agents;
}

void Board::spawn_agent_at(int x, int y, Agent *agent) {
	if (agent == NULL) {
		throw std::invalid_argument("Board (spawn_at): agent can't be null");
	}

	if (!check_valid_coordinates(x, y)) {
		throw std::invalid_argument("Board (spawn_at): x and y must be inside the board");
	}

	if (!is_empty_at(x, y)) {
		grid[y][x]->kill();
	}
	
	agents.push_back(agent);
	grid[y][x] = agent;
}

void Board::move_agent_from_to(int from_x, int from_y, int to_x, int to_y) {
	if (!check_valid_coordinates(from_x, from_y)) {
		throw std::invalid_argument("Board (move_from): x and y must be inside the board");
	}

	if (!check_valid_coordinates(to_x, to_y)) {
		throw std::invalid_argument("Board (move_to): x and y must be inside the board");
	}
	
	if (is_empty_at(from_x, from_y)) {
		throw std::invalid_argument("Board (move_to): there must be an agent in (x, y)");
	}

	if (!is_empty_at(to_x, to_y)) {
		grid[to_y][to_x]->kill();
	}

	grid[to_y][to_x] = grid[from_y][from_x];
	grid[from_y][from_x] = NULL;
}

void Board::kill_agent_at(int x, int y) {
	if (!check_valid_coordinates(x, y)) {
		throw std::invalid_argument("Board (kill): x and y must be inside the board");
	}

	if (is_empty_at(x, y)) {
		throw std::invalid_argument("Board (kill): there must be an agent in (x, y)");
	}

	grid[y][x] = NULL;
}

bool Board::check_valid_coordinates(int x, int y) {
	return x >= 0 && x < get_width() && y >= 0 && y < get_height();
}

std::string Board::get_type_at(int x, int y) {
	if (!check_valid_coordinates(x, y)) {
		throw std::invalid_argument("Board (type_at): x and y must be inside the board");
	}

	if (is_empty_at(x, y)) {
		throw std::invalid_argument("Board (type_at): there must be an agent in (x, y)");
	}

	return grid[y][x]->get_type();
}

bool Board::is_empty_at(int x, int y) {
	if (!check_valid_coordinates(x, y)) {
		throw std::invalid_argument("Board (is_empty): x and y must be inside the board");
	}

	return grid[y][x] == NULL;
}

void Board::clear_killed() {
	auto a = agents.begin();
	while (a != agents.end()) {
		if ((*a)->is_dead()) {
			delete *a;
			a = agents.erase(a);
		} else {
			a++;
		}
	}
}

void Board::print() {
	std::cout << '+' << ' ';
	for (int i = 0; i < get_width(); i++) {
		std::cout << '-' << ' ';
	}
	std::cout << '+' << std::endl;

	for (auto row : grid) {
		std::cout << '|' << ' ';
		for (auto tile : row) {
			if (tile == NULL) {
				std::cout << ' ' << ' ';
			} else {
				std::cout << tile->get_icon() << ' ';
			}
		}
		std::cout << '|' << std::endl;
	}

	std::cout << '+' << ' ';
	for (int i = 0; i < get_width(); i++) {
		std::cout << '-' << ' ';
	}
	std::cout << '+' << std::endl;
}