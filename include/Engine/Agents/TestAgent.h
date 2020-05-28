#pragma once

#include "Engine/Agents/Agent.h"
#include <string>

class TestAgent : public Agent {
public:
	TestAgent(int x, int y);
	bool step() override;
	char get_icon() override;
	std::string get_type() override;
	Agent *clone() override;
	Agent *clone(int x, int y) override;
};