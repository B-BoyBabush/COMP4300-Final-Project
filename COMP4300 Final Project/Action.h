#pragma once
#include "Vec2.h"

#include <string>

class Action
{
public:
	std::string name{ "" }; // Walk, Jump, Attack, etc
	std::string type{ "" }; // Start or End
	Vec2		pos{ 0.0f, 0.0f };

	Action(const std::string& n, const std::string& t, const Vec2& p = { 0.0f, 0.0f })
		: name{ n }
		, type{ t }
		, pos{ p }
	{ }

	Action()
	{}
};