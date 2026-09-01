#pragma once

#include "Scene.h"

#include <SFML/Graphics.hpp>

class GameEngine
{
	// Assets
	sf::RenderWindow		m_window{ sf::VideoMode{sf::Vector2u{ 1280, 720 }}, {} };
	std::unique_ptr<Scene>	currentScene{};

public:
	// changeScene

	GameEngine()
	{
		m_window.setFramerateLimit(60);

	}

	// sUserInput
	void run();
};