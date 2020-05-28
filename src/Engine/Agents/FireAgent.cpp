#include "Engine/Agents/FireAgent.h"
#include "Engine/Board.h"
#include "Auxiliar/Auxiliar.h"

FireAgent::FireAgent(int x, int y):
AgeCountingAgent(x, y) { }

bool FireAgent::step() {
	if (!AgeCountingAgent::step()) return false;

	for (auto direction : Auxiliar::all_random_directions()) {
		int target_x = x + direction[0];
		int target_y = y + direction[1];

		if (!board->check_valid_coordinates(target_x, target_y)) continue;
		if (board->is_empty_at(target_x, target_y)) continue;
		if (board->get_type_at(target_x, target_y) != "grass") continue;

		if (rand() % 3 == 0) {
			(new FireAgent(target_x, target_y))->spawn_in_board(board);
		}
	}

	if (age >= 3) {
		kill();
	}

	return true;
}

char FireAgent::get_icon() {
	return 'F';
}

std::string FireAgent::get_type() {
	return "fire";
}

Agent *FireAgent::clone() {
	return new FireAgent(x, y);
}

Agent *FireAgent::clone(int x, int y) {
	return new FireAgent(x, y);
}
