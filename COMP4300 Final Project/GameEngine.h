#pragma once

#include "Scene.h"
#include "Scene_Menu.h"

#include <SFML/Graphics.hpp>

class GameEngine
{
	// Assets
	sf::RenderWindow		m_window{ sf::VideoMode{sf::Vector2u{ 1280, 720 }}, {} };
	std::unique_ptr<Scene>	m_currentScene{}; // Pointer so that it can take in any object with the base class

public:
	// Load assets
	void changeScene(std::unique_ptr<Scene> scene);

	GameEngine()
	{
		m_window.setFramerateLimit(60);
		// Call load assets function
		changeScene(std::move(std::make_unique<Scene_Menu>(this)));
	}

	void sUserInput();
	void run();

	sf::RenderWindow& getWindow() { return m_window; };
};