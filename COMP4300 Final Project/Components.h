#pragma once

class Component
{
public:
	bool has{ false };
};

class CTransform : public Component
{
public:
	int pos{};
	int prevPos{};
	int vel{};

	CTransform(int p, int v)
		: pos{ p }
		, prevPos{ p }
		, vel{ v }
	{}

	CTransform() {}
};

class CBoundingBox : public Component
{
public:
	int size{};
	int halfSize{};

	CBoundingBox(int s, int hs)
		: size{ s }
		, halfSize{ hs }
	{}

	CBoundingBox() {}
};