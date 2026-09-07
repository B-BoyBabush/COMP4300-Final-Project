#include "Scene_Menu.h"
#include "GameEngine.h"
#include "Scene_Editor.h"

#include <fstream>
#include <string>
#include <vector>

void Scene_Menu::loadMenu(const std::string& filepath)
{
	std::ifstream fileInput{ filepath };

	m_pages.clear();

	while (fileInput.is_open())
	{
		std::string page{};
		fileInput >> page;

		if (page == "Page")
		{
			size_t pageIndex{};
			int itemNumber{};
			fileInput >> pageIndex >> itemNumber;

			m_pages.emplace_back(Page{});

			for (int i{ 0 }; i < itemNumber; i++)
			{
				std::string string{};
				unsigned int size{};
				float x{};
				float y{};
				bool selectable{};

				fileInput >> string >> size >> x >> y >> selectable;

				sf::Text text{ m_font, string, size };
				text.setFillColor(sf::Color::Magenta);
				text.setPosition(sf::Vector2f{ x, y });

				if (selectable)
					m_pages[pageIndex].selectable.emplace_back(text);
				else
					m_pages[pageIndex].decorative.emplace_back(text);
			}
		}
		
		if (fileInput.eof())
			fileInput.close();
	}
}

void Scene_Menu::sRegisterActions()
{
	m_actions[sf::Keyboard::Scancode::Escape] = "CLOSE";
	m_actions[sf::Keyboard::Scancode::W] = "UP";
	m_actions[sf::Keyboard::Scancode::S] = "DOWN";
	m_actions[sf::Keyboard::Scancode::D] = "SELECT";
	m_actions[sf::Keyboard::Scancode::A] = "BACK";
}

void Scene_Menu::sDoAction(const Action& action)
{
	if (action.type == "START")
	{
		if (action.name == "CLOSE")
			m_gamePtr->getWindow().close();
		if (action.name == "UP")
		{
			if (m_selectableIndex == 0)
				m_selectableIndex = m_pages[m_pageIndex].selectable.size() - 1;
			else
				m_selectableIndex--;
		}
		if (action.name == "DOWN")
		{
			if (m_selectableIndex == m_pages[m_pageIndex].selectable.size() - 1)
				m_selectableIndex = 0;
			else
				m_selectableIndex++;
		}
		if (action.name == "SELECT")
		{
			sf::Text& text{ m_pages[m_pageIndex].selectable[m_selectableIndex] };
			if (text.getString() == "Play")
			{
				// m_gamePtr->changeScene(Scene_Play{});
			}
			if (text.getString() == "Editor")
			{
				m_gamePtr->changeScene(std::make_unique<Scene_Editor>(m_gamePtr));
			}
			if (text.getString() == "Settings") 
			{
				m_pageIndex = 1; 
				m_selectableIndex = 0;
			}
			if (text.getString() == "Quit") m_gamePtr->getWindow().close();
		}
		if (action.name == "BACK")
		{
			if (m_pageIndex == 1) m_pageIndex = 0;
		}
	}
}

void Scene_Menu::sRender()
{
	m_gamePtr->getWindow().clear(sf::Color::Black);

	// Change selected text to blue before drawing
	m_pages[m_pageIndex].selectable[m_selectableIndex].setFillColor(sf::Color::Blue);
	
	for (sf::Text& dec : m_pages[m_pageIndex].decorative)
		m_gamePtr->getWindow().draw(dec);
	for (sf::Text& sel : m_pages[m_pageIndex].selectable)
		m_gamePtr->getWindow().draw(sel);

	// Change selected text back to purple
	m_pages[m_pageIndex].selectable[m_selectableIndex].setFillColor(sf::Color::Magenta);
	
	m_gamePtr->getWindow().display();
}

void Scene_Menu::sUpdate()
{
	sRender();
}