#include "GameEngine.h"
#include "Scene.h"
#include "Action.h"
#include "Assets.h"

#include <fstream>
#include <memory>
#include <utility>

void GameEngine::loadAssets(const std::string& filepath)
{
	std::ifstream fileInput{ filepath };
	std::string type{};

	while (fileInput.is_open())
	{
		fileInput >> type;
		
		if (type == "Texture")
		{
			std::string name{};
			std::string file{};

			fileInput >> name >> file;

			m_assets.addTexture(name, file);
		}

		if (type == "Animation")
		{
			std::string name{};
			std::string txtrName{};
			unsigned int totalFrames{};
			unsigned int speed{};

			fileInput >> name >> txtrName >> totalFrames >> speed;

			Animation anim{ name, &m_assets.getTexture(txtrName), totalFrames, speed };

			m_assets.addAnimation(name, anim);
		}

		if (fileInput.eof())
			fileInput.close();
	}
}

void GameEngine::changeScene(std::unique_ptr<Scene> scene)
{
	m_currentScene = std::move(scene);
}

void GameEngine::sUserInput()
{
	while (const std::optional<sf::Event> event = m_window.pollEvent())
	{
		if (event->getIf<sf::Event::Closed>())
			m_window.close();
		
		if (const sf::Event::KeyPressed* keyPress{ event->getIf<sf::Event::KeyPressed>() })
		{
			Action action{ m_currentScene->m_actions[keyPress->scancode], "START" };
			m_currentScene->sDoAction(action); 
		}

		if (const sf::Event::KeyReleased* keyRelease{ event->getIf<sf::Event::KeyReleased>() })
		{
			Action action{ m_currentScene->m_actions[keyRelease->scancode], "END" };
			m_currentScene->sDoAction(action);
		}
	}
}

void GameEngine::run()
{
	while (m_window.isOpen())
	{
		sUserInput();
		m_currentScene->sUpdate();
	}
}