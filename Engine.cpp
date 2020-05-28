#include "Engine.h"
#include "SystemAux.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <stdexcept>

Engine::Engine(int width, int height, std::chrono::system_clock::duration step_duration):
board(width, height) {
	if (width <= 0) throw std::invalid_argument("Engine (constructor): width must be higher that zero");
	if (height <= 0) throw std::invalid_argument("Engine (constructor): height must be higher that zero");
	this->step_duration = step_duration;
	current_step = 0;
	next_step_time = std::chrono::system_clock::now();
	stop_called = false;
}

Engine::~Engine() {
	while (!delayed_spawns.empty()) {
		delete delayed_spawns.top().second;
		delayed_spawns.pop();
	}

	for (auto spawner : spawners) {
		delete spawner;
	}
}

void Engine::run() {
	for (current_step = 0; current_step < 10000; current_step++) {
		if (stop_called) {
			std::cout << std::endl;
			std::cout << "The engine received an interruption and successfully stopped";
			return;
		}

		step();

		print_frame();

		next_step_time += step_duration;
		std::this_thread::sleep_until(next_step_time);
	}

	std::cout << std::endl;
	std::cout << "The engine reached the maximum step";
}

void Engine::step() {
	check_delayed_spawns();
	check_spawners();

	std::vector<Agent *> *agents = board.get_agents();
	std::vector<Agent *> shuffed_agents(agents->size());
	std::copy(agents->begin(), agents->end(), shuffed_agents.begin());
	std::random_shuffle(shuffed_agents.begin(), shuffed_agents.end());

	for (auto agent : shuffed_agents) {
		agent->step();
	}

	board.clear_killed();
}

void Engine::check_delayed_spawns() {
	while (!delayed_spawns.empty() && delayed_spawns.top().first <= current_step) {
		delayed_spawns.top().second->spawn_in_board(&board);
		delayed_spawns.pop();
	}
}

void Engine::check_spawners() {
	for (auto spawner : spawners) {
		spawner->step();
	}
}

void Engine::spawn_agent(Agent *agent, int delay) {
	if (agent == NULL) throw std::invalid_argument("Engine (spawn_agent): agent can't be null");
	if (delay < 0) throw std::invalid_argument("Engine (spawn_agent): delay can't be negative");

	if (delay == 0) {
		agent->spawn_in_board(&board);
	} else {
		delayed_spawns.push(std::make_pair(delay, agent));
	}
}

void Engine::add_spawner(Spawner *spawner) {
	if (spawner == NULL) throw std::invalid_argument("Engine (add_spawner): spawner can't be null");

	spawner->set_board(&board);
	spawners.push_back(spawner);
}

void Engine::stop() {
	stop_called = true;
}

void Engine::print_frame() {
	std::chrono::time_point<std::chrono::system_clock> current_time = std::chrono::system_clock::now();
	int current_step_delay = (current_time - next_step_time) / step_duration;

	SystemAux::reset_cursor();
	SystemAux::clear_line();
	std::cout << "Step count: " << current_step << std::endl;
	std::cout << "Step delay: " << current_step_delay << std::endl;
	SystemAux::clear_line();
	std::cout << "Agents: " << board.get_agents()->size() << std::endl;
	SystemAux::clear_line();
	std::cout << "Delayed spawns: " << delayed_spawns.size() << std::endl;
	board.print();
}