#include "Engine/Agents/AgeCountingAgent.h"

AgeCountingAgent::AgeCountingAgent(int x, int y):
Agent(x, y) {
	age = 0;
}

bool AgeCountingAgent::step() {
	if (!Agent::step()) return false;
	age++;
	return true;
}