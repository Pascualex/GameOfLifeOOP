#include "Engine/Agents/TestAgent.h"
#include "Engine/Board.h"

TestAgent::TestAgent(int x, int y):
Agent(x, y) { }

bool TestAgent::step() {
	if (!Agent::step()) return false;
	if (board->check_valid_coordinates(x + 1, y)) {
		board->move_agent_from_to(x, y, x + 1, y);
		x++;
	}
	return true;
}

char TestAgent::get_icon() {
	return 'T';
}

std::string TestAgent::get_type() {
	return "test";
}

Agent *TestAgent::clone() {
	return new TestAgent(x, y);
}

Agent * TestAgent::clone(int x, int y) {
	return new TestAgent(x, y);
}