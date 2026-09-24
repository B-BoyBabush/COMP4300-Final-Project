#include "Scene_Editor.h"
#include "GameEngine.h"
#include "Vec2.h"

#include <iostream>
#include <sstream>

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

	m_font = m_gamePtr->getAssets().getFont("Evermore");
}

void Scene_Editor::highlight()
{
	// Get mouse coordinates
	sf::Vector2f mousePos{ m_gamePtr->getWindow().mapPixelToCoords(sf::Mouse::getPosition(m_gamePtr->getWindow())) };

	// Determine what tile they are on
	int tx{ static_cast<int>(mousePos.x / 64.0f) };
	int ty{ static_cast<int>(mousePos.y / 64.0f) };

	// Create the tile highlighter
	sf::RectangleShape highlight{ { 64.0f, 64.0f } };

	// Determine the real position the highlighter square should be at
	Vec2 pos{ tx * 64.0f, ty * 64.0f };
	if (mousePos.x < 0.0f) pos.x -= 64.0f;
	if (mousePos.y < 0.0f) pos.y -= 64.0f;

	highlight.setPosition(pos);
	highlight.setFillColor(sf::Color{ 255U, 255U, 255U, 80U });

	m_gamePtr->getWindow().draw(highlight);
}

void Scene_Editor::ui()
{
	// Draw the menu UI
	m_gamePtr->getWindow().setView(m_entityView);
	
	sf::RectangleShape menu{ static_cast<sf::Vector2f>(m_gamePtr->getWindow().getSize()) };
	menu.setPosition({ 0.0f, 0.0f });
	menu.setFillColor(sf::Color::Black);

	m_gamePtr->getWindow().draw(menu);

	// Draw the room coordinate text
	m_gamePtr->getWindow().setView(m_levelView);

	// Create a text and string buffer
	sf::Text roomCoord{ m_font, "", 20U };
	std::ostringstream stringBuffer{};

	// Input the room numbers into a string format
	stringBuffer << "Room(" << m_room.x << ", " << m_room.y << ")";

	// Set the text to this string buffer
	roomCoord.setString(stringBuffer.str());
	roomCoord.setPosition(sf::Vector2f{ m_center.x - 640.0f, m_center.y - 352.0f });

	// Clear the buffer
	stringBuffer.clear();

	m_gamePtr->getWindow().draw(roomCoord);
}

void Scene_Editor::sDoAction(const Action& action)
{
	if (action.type == "START")
	{
		if (action.name == "CLOSE")
			m_gamePtr->getWindow().close();
		if (action.name == "SWITCH_CAMERA")
			m_follow = !m_follow;

		if (m_follow)
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
		else if (m_follow == false)
		{
			if (action.name == "MOVE_UP")
				m_room.y -= 1;
			if (action.name == "MOVE_LEFT")
				m_room.x -= 1;
			if (action.name == "MOVE_DOWN")
				m_room.y += 1;
			if (action.name == "MOVE_RIGHT")
				m_room.x += 1;
		}
	}
	if (action.type == "END")
	{
		if (m_follow)
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
	// Check the previous center
	static Vec2 prevCenter{ m_center };

	// Move the camera
	m_center += m_cameraVel;

	// If the center has moved, check the room position
	if (prevCenter != m_center)
	{
		// Update the room position
		int rx{ static_cast<int>(m_center.x / m_gamePtr->getWindow().getSize().x) };
		int ry{ static_cast<int>(m_center.y / m_gamePtr->getWindow().getSize().y) };

		if (m_center.x < 0.0f) rx -= 1;
		if (m_center.y < 0.0f) ry -= 1;

		m_room = Room{ rx, ry };
	}

	// Still calculates unnecessarily every frame
	// If the camera is set to room
	if (m_follow == false)
	{
		// Find window size and half size
		Vec2 w{ m_gamePtr->getWindow().getSize() };
		Vec2 hw{ w * 0.5f };

		// Set center with room coordinates
		m_center = Vec2{ m_room.x * w.x + hw.x, m_room.y * w.y + hw.y };
	}

	// If the center of the view has moved
	if (prevCenter != m_center)
	{
		// Find the offset
		Vec2 offset{ m_center - prevCenter };

		// Move the tilemap by that offset
		for (size_t i{ 0 }; i < m_tileMap.getVertexCount(); i++)
		{
			m_tileMap[i].position += sf::Vector2f{ offset };
		}

		// And set the center record to the current center
		prevCenter = m_center;
	}

	// Set the center of the view to m_center
	m_levelView.setCenter(m_center);
}

void Scene_Editor::sRender()
{
	m_gamePtr->getWindow().clear(sf::Color::Green);

	// Display level view, tiles, and highlighting
	m_gamePtr->getWindow().setView(m_levelView);
	m_gamePtr->getWindow().draw(m_tileMap, &m_gamePtr->getAssets().getTexture("TexGround"));

	highlight();
	ui();

	m_gamePtr->getWindow().setView(m_entityView);

	// Draw entities
	for (Entity entity : m_entities.getEntities())
	{
		if (entity.hasComponent<CAnimation>() && entity.hasComponent<CTransform>())
		{
			CAnimation anim{ entity.getComponent<CAnimation>() };
			CTransform transform{ entity.getComponent<CTransform>() };

			sf::Sprite sprite{ *anim.animation.m_txtrPtr, anim.animation.m_txtrRect };
			sprite.setOrigin(sf::Vector2f{ anim.animation.m_txtrRect.size.x * 0.5f, anim.animation.m_txtrRect.size.y * 0.5f });
			sprite.setPosition(transform.pos);
			m_gamePtr->getWindow().draw(sprite);
		}
	}

	m_gamePtr->getWindow().display();
}

void Scene_Editor::sUpdate()
{
	m_entities.update();
	
	sCamera();
	sRender();
}