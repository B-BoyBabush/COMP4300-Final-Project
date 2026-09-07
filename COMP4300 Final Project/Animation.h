#pragma once

#include "SFML/Graphics.hpp"

#include <iostream>

class Animation
{
public:
	std::string			m_name{ "none" };
	unsigned int		m_animFrame{ 0 };
	unsigned int		m_totalFrames{ 1 };
	unsigned int		m_speed{ 10 };
	unsigned int		m_gameFrame{ 0 };

	const sf::Texture*	m_txtrPtr{};
	sf::IntRect			m_txtrRect{};

	Animation() {}

	Animation(const std::string& name, const sf::Texture* texture, const unsigned int& totalFrames, const unsigned int& speed)
		: m_name{ name }
		, m_txtrPtr{ texture }
		, m_totalFrames{ totalFrames }
		, m_speed{ speed }
	{
		m_txtrRect = sf::IntRect{ sf::Vector2i{ 0, 0 },
			sf::Vector2i{ static_cast<int>(m_txtrPtr->getSize().x / m_totalFrames), static_cast<int>(m_txtrPtr->getSize().y)} };
	}
};