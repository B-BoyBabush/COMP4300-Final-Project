#include "GameEngine.h"
#include "Scene.h"
#include "Action.h"

#include <memory>
#include <utility>

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