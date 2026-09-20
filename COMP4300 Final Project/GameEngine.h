#pragma once

#include "Assets.h"
#include "Scene.h"
#include "Scene_Menu.h"

#include <SFML/Graphics.hpp>

class GameEngine
{
	Assets					m_assets{};
	sf::RenderWindow		m_window{ sf::VideoMode{sf::Vector2u{ 1280, 704 }}, {} };
	std::unique_ptr<Scene>	m_currentScene{}; // Pointer so that it can take in any object with the base class

public:
	// Load assets
	void loadAssets(const std::string& filepath);
	void changeScene(std::unique_ptr<Scene> scene);

	GameEngine()
	{
		m_window.setFramerateLimit(60);
		m_window.setKeyRepeatEnabled(false);
		loadAssets("Assets/assets_config.txt");
		changeScene(std::make_unique<Scene_Menu>(this));
	}

	void sUserInput();
	void run();

	sf::RenderWindow& getWindow() { return m_window; };
	Assets& getAssets() { return m_assets; };
};