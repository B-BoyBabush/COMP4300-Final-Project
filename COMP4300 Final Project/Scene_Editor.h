#pragma once

#include "Scene.h"
#include "EntityManager.h"

class Scene_Editor : public Scene
{
public:
	struct Room { int x{}, y{}; };
	
	sf::VertexArray m_tileMap{ sf::PrimitiveType::Triangles, 1320 };
	EntityManager m_entities{};

	sf::View m_entityView{};
	sf::View m_levelView{};
	
	bool m_freeCamera{ true };
	Vec2 m_center{};
	Vec2 m_cameraVel{};

	void registerActions();
	void loadEntities();
	void loadEditor();

	Scene_Editor(GameEngine* gamePtr)
		: Scene(gamePtr)
	{
		registerActions();
		loadEditor();
	}

	void highlight();
	void ui();

	void sDoAction(const Action& action);
	void sMovement();
	void sCamera();
	void sRender();
	void sUpdate();
};