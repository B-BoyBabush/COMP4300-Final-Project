#include "Scene_Editor.h"
#include "GameEngine.h"
#include "Vec2.h"

#include <iostream>

void Scene_Editor::registerActions()
{
	m_actions[sf::Keyboard::Scancode::Escape] = "CLOSE";
	m_actions[sf::Keyboard::Scancode::F] = "SWITCH_CAMERA";
	m_actions[sf::Keyboard::Scancode::W] = "MOVE_UP";
	m_actions[sf::Keyboard::Scancode::A] = "MOVE_LEFT";
	m_actions[sf::Keyboard::Scancode::S] = "MOVE_DOWN";
	m_actions[sf::Keyboard::Scancode::D] = "MOVE_RIGHT";
}

void Scene_Editor::loadEditor()
{
	// Load the tiles (only needed once)
	for (size_t i{ 0 }; i < (m_tileMap.getVertexCount() / 6); i++)
	{
		size_t j{ i * 6 };
		size_t row{ i / 25 }; // 0 0 0 0 1 1 1 1
		size_t col{ i % 25 }; // 0 1 2 3

		m_tileMap[j].position =	{ col * 64.0f, row * 64.0f }; // Top left
		m_tileMap[j + 1].position = { col * 64.0f, row * 64.0f + 64.0f }; // Bottom left
		m_tileMap[j + 2].position = { col * 64.0f + 64.0f, row * 64.0f }; // Top right
		m_tileMap[j + 3].position = { col * 64.0f + 64.0f, row * 64.0f }; // Top right
		m_tileMap[j + 4].position = { col * 64.0f, row * 64.0f + 64.0f }; // Bottom left
		m_tileMap[j + 5].position = { col * 64.0f + 64.0f, row * 64.0f + 64.0f }; // Bottom right

		m_tileMap[j].texCoords = { 0, 0 }; // Top left
		m_tileMap[j + 1].texCoords = { 0, 64 }; // Bottom left
		m_tileMap[j + 2].texCoords = { 64, 0 }; // Top right
		m_tileMap[j + 3].texCoords = { 64, 0 }; // Top right
		m_tileMap[j + 4].texCoords = { 0, 64 }; // Bottom left
		m_tileMap[j + 5].texCoords = { 64, 64 }; // Bottom right
	}

	// Load the starting entities
	
	// Update center of view
	m_center = { static_cast<float>(m_gamePtr->getWindow().getSize().x / 2), static_cast<float>(m_gamePtr->getWindow().getSize().y / 2) };

	// Load the views
	m_levelView = m_gamePtr->getWindow().getView();
	m_entityView = m_gamePtr->getWindow().getView();

	m_levelView.setViewport(sf::FloatRect{ {0.0f, 0.0f}, { 0.8f, 1.0f } });
	m_entityView.setViewport(sf::FloatRect{ {0.8f, 0.0f}, { 0.2f, 1.0f } });
}

void Scene_Editor::highlight()
{
	sf::Vector2f mousePos{ m_gamePtr->getWindow().mapPixelToCoords(sf::Mouse::getPosition(m_gamePtr->getWindow())) };

	int tx{ static_cast<int>(mousePos.x / 64.0f) };
	int ty{ static_cast<int>(mousePos.y / 64.0f) };

	sf::RectangleShape highlight{ { 64.0f, 64.0f } };
	highlight.setPosition(sf::Vector2f{ tx * 64.0f, ty * 64.0f });
	highlight.setFillColor(sf::Color{ 255U, 255U, 255U, 80U });

	m_gamePtr->getWindow().draw(highlight);
}

void Scene_Editor::ui()
{
	sf::RectangleShape menu{ static_cast<sf::Vector2f>(m_gamePtr->getWindow().getSize()) };
	menu.setPosition({ 0.0f, 0.0f });
	menu.setFillColor(sf::Color::Black);

	sf::RectangleShape s{ {300.0f, 300.0f} }; // Square is drawn as rectangle
	s.setFillColor(sf::Color::Blue);

	m_gamePtr->getWindow().draw(menu);
	m_gamePtr->getWindow().draw(s);
}

void Scene_Editor::sDoAction(const Action& action)
{
	if (action.type == "START")
	{
		if (action.name == "CLOSE")
			m_gamePtr->getWindow().close();
		if (action.name == "SWITCH_CAMERA")
			m_freeCamera = !m_freeCamera;

		if (m_freeCamera)
		{
			if (action.name == "MOVE_UP")
				m_cameraVel.y = -8.0f;
			if (action.name == "MOVE_LEFT")
				m_cameraVel.x = -8.0f;
			if (action.name == "MOVE_DOWN")
				m_cameraVel.y = 8.0f;
			if (action.name == "MOVE_RIGHT")
				m_cameraVel.x = 8.0f;
		}
		else if (m_freeCamera == false)
		{
			if (action.name == "MOVE_UP")
				m_center.y -= m_gamePtr->getWindow().getSize().y;
			if (action.name == "MOVE_LEFT")
				m_center.x -= m_gamePtr->getWindow().getSize().x;
			if (action.name == "MOVE_DOWN")
				m_center.y += m_gamePtr->getWindow().getSize().y;
			if (action.name == "MOVE_RIGHT")
				m_center.x += m_gamePtr->getWindow().getSize().x;
		}
	}
	if (action.type == "END")
	{
		if (m_freeCamera)
		{
			if (action.name == "MOVE_UP")
				m_cameraVel.y = 0.0f;
			if (action.name == "MOVE_LEFT")
				m_cameraVel.x = 0.0f;
			if (action.name == "MOVE_DOWN")
				m_cameraVel.y = 0.0f;
			if (action.name == "MOVE_RIGHT")
				m_cameraVel.x = 0.0f;
		}
	}
}

void Scene_Editor::sCamera()
{
	m_center += m_cameraVel;
	
	if (m_freeCamera)
		m_levelView.setCenter(m_center);
	if (m_freeCamera == false)
	{
		// Room position
		int rx{ static_cast<int>(m_center.x / m_gamePtr->getWindow().getSize().x) };
		int ry{ static_cast<int>(m_center.y / m_gamePtr->getWindow().getSize().y) };
		
		// Window size and half size
		Vec2 w{ m_gamePtr->getWindow().getSize() };
		Vec2 hw{ w * 0.5f };

		if (m_center.x < 0) hw.x = -hw.x;
		if (m_center.y < 0) hw.y = -hw.y;

		m_levelView.setCenter({ rx * w.x + hw.x, ry * w.y + hw.y });
	}
}

void Scene_Editor::sRender()
{
	m_gamePtr->getWindow().clear(sf::Color::Green);

	// Display level view, tiles, and highlighting
	m_gamePtr->getWindow().setView(m_levelView);
	m_gamePtr->getWindow().draw(m_tileMap, &m_gamePtr->getAssets().getTexture("TexGround"));
	highlight();

	// Display entities and UI
	m_gamePtr->getWindow().setView(m_entityView);
	ui();

	m_gamePtr->getWindow().display();
}

void Scene_Editor::sUpdate()
{
	sCamera();
	sRender();
}