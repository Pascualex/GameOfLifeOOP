#pragma once

#include "Agent.h"

class AgeCountingAgent : public Agent {
protected:
	int age;
public:
	AgeCountingAgent(int x, int y);
	virtual bool step() override;
};

