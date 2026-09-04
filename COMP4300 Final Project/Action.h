#pragma once

#include <string>

class Action
{
public:
	std::string action{}; // Walk, Jump, Attack, etc
	std::string type{}; // Start or End

	Action(const std::string& a, const std::string& t)
		: action{ a }
		, type{ t }
	{ }

	Action()
	{}
};