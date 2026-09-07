#include "Assets.h"

sf::Texture& Assets::addTexture(const std::string& txtrName, const std::string& filename)
{
	sf::Texture texture{};
	if (texture.loadFromFile(filename, false))
	{
		m_textures.emplace(txtrName, texture);
		std::cout << "Texture loaded: " << txtrName << '\n';
	}
	else
		std::cout << "Texture failed to load: " << txtrName << '\n';

	return m_textures[txtrName];
}

sf::Texture& Assets::getTexture(const std::string& txtrName)
{
	return m_textures[txtrName];
}

Animation& Assets::addAnimation(const std::string& animName, const Animation& animation)
{
	if (animation.m_txtrPtr->getSize() == sf::Vector2u{ 0, 0 })
		std::cout << "Animation failed to load: " << animName << '\n';
	else
		std::cout << "Animation loaded: " << animName << '\n';

	m_animations.emplace(animName, animation);

	return m_animations[animName];
}

Animation& Assets::getAnimation(const std::string& animName)
{
	return m_animations[animName];
}

sf::Font& Assets::addFont(const std::string& fontName, const std::string& filename)
{
	sf::Font font{};
	if (font.openFromFile(filename))
	{
		m_fonts.emplace(fontName, font);
		std::cout << "Font loaded: " << fontName << '\n';
	}

	return m_fonts[fontName];
}

sf::Font& Assets::getFont(const std::string& fontName)
{
	return m_fonts[fontName];
}