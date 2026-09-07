#include "Scene_Editor.h"
#include "GameEngine.h"

#include <iostream>

void Scene_Editor::sRegisterActions()
{
	m_actions[sf::Keyboard::Scancode::Escape] = "CLOSE";
}

void Scene_Editor::sDoAction(const Action& action)
{
	if (action.name == "CLOSE")
		m_gamePtr->getWindow().close();
}

void Scene_Editor::sRender()
{
	m_gamePtr->getWindow().clear(sf::Color{ 38U, 23U, 25U });



	m_gamePtr->getWindow().display();
}

void Scene_Editor::sUpdate()
{
	sRender();
}