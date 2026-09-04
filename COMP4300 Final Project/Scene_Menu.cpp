#include "Scene_Menu.h"
#include "GameEngine.h"

void Scene_Menu::sRegisterActions()
{
	m_actions[sf::Keyboard::Scancode::Escape] = "CLOSE";
	m_actions[sf::Keyboard::Scancode::W] = "UP";
	m_actions[sf::Keyboard::Scancode::D] = "DOWN";
}

void Scene_Menu::sDoAction(const Action& action)
{
	if (action.action == "CLOSE")
		m_gamePtr->getWindow().close();

}

void Scene_Menu::sRender()
{
	m_gamePtr->getWindow().clear();
	
	// Draw everything
	m_gamePtr->getWindow().draw(sf::RectangleShape{ sf::Vector2f{ 300.0f, 200.0f } });
	
	m_gamePtr->getWindow().display();
}

void Scene_Menu::sUpdate()
{
	sRender();
}