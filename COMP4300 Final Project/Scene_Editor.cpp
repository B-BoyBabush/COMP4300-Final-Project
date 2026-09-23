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

void Scene_Editor::loadEntities()
{
	std::vector<std::string> tiles{
		"Fern1", "Fern2", "Fern3", "Foliage",
		"Leaves1", "Leaves2", "Leaves3", "Leaves4",
		"Leaves5", "Leaves6", "Leaves7", "Leaves8",
		"Leaves9", "Leaves10", "Leaves11", "Scullclaw",
		"Dragoyle", "Anhur", "Set"
	};

	// Creates 3 columns and draws from the tiles container
	// to autopopulate the entities downward
	for (int i{ 0 }; i < tiles.size(); i++)
	{
		int col{ i % 3 };
		int row{ i / 3 };

		Entity e = m_entities.addEntity(tiles[i]);
		e.addComponent<CTransform>(Vec2{ col * 80.0f + 48.0f, row * 100.0f + 48.0f }, Vec2{ 0.0f, 0.0f });
		e.addComponent<CAnimation>(m_gamePtr->getAssets().getAnimation(tiles[i]), true);
		e.addComponent<CBoundingBox>(Vec2{ e.getComponent<CAnimation>().animation.m_txtrRect.size });
		e.addComponent<CDraggable>();
	}
}

void Scene_Editor::loadEditor()
{
	// Load the tiles (only needed once)
	for (size_t i{ 0 }; i < (m_tileMap.getVertexCount() / 6); i++)
	{
		size_t j{ i * 6 };
		size_t col{ i % 20 };
		size_t row{ i / 20 };

		m_tileMap[j].position = { col * 64.0f, row * 64.0f }; // Top left
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

	float wx{ static_cast<float>(m_gamePtr->getWindow().getSize().x) };
	float wy{ static_cast<float>(m_gamePtr->getWindow().getSize().y) };

	// Update center of view
	m_center = { wx * 0.5f, wy * 0.5f };

	// Load the level view
	m_levelView = m_gamePtr->getWindow().getView();
	m_levelView.setViewport(sf::FloatRect{ {0.0f, 0.0f}, { 0.8f, 1.0f } });
	
	// Load the entity view
	m_entityView = m_gamePtr->getWindow().getView();
	m_entityView.setSize({ wx * 0.2f, wy });
	m_entityView.setCenter({ m_entityView.getSize().x * 0.5f, m_entityView.getSize().y * 0.5f });
	m_entityView.setViewport(sf::FloatRect{ {0.8f, 0.0f}, { 0.2f, 1.0f } });

	loadEntities();
}

void Scene_Editor::highlight()
{
	sf::Vector2f mousePos{ m_gamePtr->getWindow().mapPixelToCoords(sf::Mouse::getPosition(m_gamePtr->getWindow())) };

	int tx{ static_cast<int>(mousePos.x / 64.0f) };
	int ty{ static_cast<int>(mousePos.y / 64.0f) };

	sf::RectangleShape highlight{ { 64.0f, 64.0f } };

	Vec2 pos{ tx * 64.0f, ty * 64.0f };
	if (pos.x < 0) pos.x -= 64.0f;
	if (pos.y < 0) pos.y -= 64.0f;

	highlight.setPosition(pos);
	highlight.setFillColor(sf::Color{ 255U, 255U, 255U, 80U });

	m_gamePtr->getWindow().draw(highlight);
}

void Scene_Editor::ui()
{
	sf::RectangleShape menu{ static_cast<sf::Vector2f>(m_gamePtr->getWindow().getSize()) };
	menu.setPosition({ 0.0f, 0.0f });
	menu.setFillColor(sf::Color::Black);

	m_gamePtr->getWindow().draw(menu);
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

void Scene_Editor::sMovement()
{
	static Vec2 prevCenter{ m_center };

	if (prevCenter != m_center)
	{
		Vec2 offset{ m_center - prevCenter };
		
		for (size_t i{ 0 }; i < m_tileMap.getVertexCount(); i++)
		{
			m_tileMap[i].position += sf::Vector2f{ offset };
		}

		prevCenter = m_center;
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

	// Display entity view and UI
	m_gamePtr->getWindow().setView(m_entityView);
	ui();

	// Draw entities
	for (Entity entity : m_entities.getEntities())
	{
		if (entity.hasComponent<CAnimation>() && entity.hasComponent<CTransform>())
		{
			CAnimation anim{ entity.getComponent<CAnimation>() };
			CTransform trans{ entity.getComponent<CTransform>() };

			sf::Sprite sprite{ *anim.animation.m_txtrPtr, anim.animation.m_txtrRect };
			sprite.setOrigin(sf::Vector2f{ anim.animation.m_txtrRect.size.x * 0.5f, anim.animation.m_txtrRect.size.y * 0.5f });
			sprite.setPosition(trans.pos);
			m_gamePtr->getWindow().draw(sprite);
		}
	}

	m_gamePtr->getWindow().display();
}

void Scene_Editor::sUpdate()
{
	m_entities.update();
	
	sMovement();
	sCamera();
	sRender();
}