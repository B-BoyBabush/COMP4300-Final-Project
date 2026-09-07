#pragma once

#include "Action.h"

#include <SFML/Graphics.hpp>

#include <map>

class GameEngine;

class Scene
{
public:
	GameEngine*										m_gamePtr{};
	std::map<sf::Keyboard::Scancode, std::string>	m_actions{};
	size_t											m_currentFrame{ 0 };

	Scene(GameEngine* gamePtr)
		: m_gamePtr{ gamePtr }
	{ }

	// Mandatory systems defined by derived Scene classes
	virtual void sRegisterActions() = 0;
	virtual void sDoAction(const Action& action) = 0;
	virtual void sRender() = 0;
	virtual void sUpdate() = 0;
};