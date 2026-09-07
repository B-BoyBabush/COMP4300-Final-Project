#pragma once

#include "Scene.h"

class Scene_Menu : public Scene
{
	struct Page 
	{ 
		std::vector<sf::Text> selectable{};
		std::vector<sf::Text> decorative{};

		Page() {}
	};

	sf::Font			m_font{ "Assets/pixel_font.ttf" };
	std::vector<Page>	m_pages{};
	size_t				m_pageIndex{ 0 };
	size_t				m_selectableIndex{ 0 };

public:
	void loadMenu(const std::string& filepath);
	void sRegisterActions();
	
	Scene_Menu(GameEngine* gamePtr)
		: Scene(gamePtr)
	{
		loadMenu("Assets/menu_config.txt");
		sRegisterActions();
	}
	
	void sDoAction(const Action& action);
	void sRender();
	void sUpdate();
};