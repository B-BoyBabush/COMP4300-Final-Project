#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class ParticleSystem
{
	struct Particle
	{
		sf::Vector2f velocity{};
		int lifetime{ 0 };
	};

	std::vector<Particle>	m_particles{}; // Contains the physics data of the particles
	sf::VertexArray			m_vertices{}; // Contains the color and position data of the particles
	sf::Vector2u			m_window{};
	float					m_size{ 8.0f };

	void resetParticles(size_t count = 1024, float size = 8.0f)
	{
		m_particles = std::vector<Particle>(count);
		m_vertices = sf::VertexArray{ sf::PrimitiveType::Points, 1024 };
		m_size = size;

		for (size_t p{ 0 }; p < m_particles.size(); p++)
		{
			resetParticle(p);
		}
	}

	void resetParticle(size_t particle)
	{
		// set pos
		m_vertices[particle].position = sf::Vector2f{ m_window.x / 2.0f, m_window.y / 2.0f };

		// set color
		sf::Color color{ 255, 0, 255, 255 };

		//m_vertices


		// set lifespan


		// set velocity

	}

};