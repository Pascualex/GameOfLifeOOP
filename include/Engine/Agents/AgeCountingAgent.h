#pragma once

#include "Engine/Agents/Agent.h"

class AgeCountingAgent : public Agent {
protected:
	int age;
public:
	AgeCountingAgent(int x, int y);
	virtual bool step() override;
};