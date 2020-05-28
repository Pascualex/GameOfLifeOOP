#include "GrassAgent.h"
#include "Board.h"
#include "Auxiliar.h"

GrassAgent::GrassAgent(int x, int y):
AgeCountingAgent(x, y) { }

bool GrassAgent::step() {
	if (!AgeCountingAgent::step()) return false;

	if (age >= 5) {
		for (auto direction : Auxiliar::all_random_directions()) {
			int target_x = x + direction[0];
			int target_y = y + direction[1];

			if (!board->check_valid_coordinates(target_x, target_y)) continue;
			if (!board->is_empty_at(target_x, target_y)) continue;

			if (rand() % 10 == 0) {
				(new GrassAgent(target_x, target_y))->spawn_in_board(board);
			}
		}
	}

	if (age >= 10) {
		kill();
	}

	return true;
}

char GrassAgent::get_icon() {
	if (age < 5) {
		return 'g';
	} else {
		return 'G';
	}
}

std::string GrassAgent::get_type() {
	return "grass";
}

Agent *GrassAgent::clone() {
	return new GrassAgent(x, y);
}

Agent *GrassAgent::clone(int x, int y) {
	return new GrassAgent(x, y);
}