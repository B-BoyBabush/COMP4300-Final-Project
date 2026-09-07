#pragma once
#include "Vec2.h"
#include "Animation.h"

class Component
{
public:
	bool has{ false };
};

class CTransform : public Component
{
public:
	Vec2 pos{};
	Vec2 prevPos{};
	Vec2 vel{};

	CTransform(Vec2 p, Vec2 v)
		: pos{ p }
		, prevPos{ p }
		, vel{ v }
	{}

	CTransform() {}
};

class CBoundingBox : public Component
{
public:
	Vec2 size{};
	Vec2 halfSize{};

	CBoundingBox(Vec2 s)
		: size{ s }
		, halfSize{ s / 2.0f }
	{}

	CBoundingBox() {}
};

class CAnimation : public Component
{
public:
	Animation animation{};
	bool repeat{};
	bool flip{};
	bool pause{};

	CAnimation(const Animation& a, bool r)
		: animation{ a }
		, repeat{ r }
	{ }

	CAnimation() {}
};

class CDraggable : public Component
{
public:
	bool beingDragged{ false };

	CDraggable() {}
};