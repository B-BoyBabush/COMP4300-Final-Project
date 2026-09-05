#pragma once

#include <string>

class Action
{
public:
	std::string name{}; // Walk, Jump, Attack, etc
	std::string type{}; // Start or End

	Action(const std::string& n, const std::string& t)
		: name{ n }
		, type{ t }
	{ }

	Action()
	{}
};