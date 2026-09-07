#pragma once

#include "Animation.h"

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <map>
#include <iostream>

class Assets
{
private:
	std::map<std::string, sf::Texture>	m_textures{};
	std::map<std::string, Animation>	m_animations{};
	std::map<std::string, sf::Font>		m_fonts{};
	std::map<std::string, sf::Sound>	m_sounds{};
	std::map<std::string, sf::Music>	m_music{};

public:
	sf::Texture& addTexture(const std::string& txtrName, const std::string& filename);
	sf::Texture& getTexture(const std::string& txtrName);

	Animation& addAnimation(const std::string& animName, const Animation& animation);
	Animation& getAnimation(const std::string& animName);

	sf::Font& addFont(const std::string& fontName, const std::string& filename);
	sf::Font& getFont(const std::string& fontName);
};
